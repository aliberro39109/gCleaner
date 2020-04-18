/************************************************************************
Virus cleaner: For svcHost and ground virus
Made by Ali-Berro 4 April 2020
Under the MIT license, i.e. anybody can edit and redistribute this code
but if you could add a reference it would be KO.ol too :)
************************************************************************/
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <thread>
#include <tlhelp32.h>
using namespace std;

unsigned int _Size = 534016; ///The size of the virus in bytes ///Another one  int _Size = 267,776
void clean(const char* x);
bool CheckOneInstance();
HANDLE hProcess = NULL;
bool check_process(string process);
bool kill_process();
void Color(int color);
void cls();
int _v = 0;
int _c = 0;
int _o = 0;
ofstream log;
int main()
{
    log.open("log.txt");
    Color(0xB);
    if(!CheckOneInstance())
    {
        cout << "The Program is Already Running";
        Sleep(2000);
        return 0;
    }
    cout << "Please Run Me In Safe Mode & as an administrator for 100 percent better performance" << endl;
    Sleep(4000);
    cout << "Insert Directory To Clean (C:\\, D:\\, E:\\)\t\t";
    string dir;
    cin>>dir;
    log << "[gCleaner For svcHost Files & Ground]\n";
    log << "[Version::0.1] By [Ali Berro]\n";
    log << "Directory [";
    log << dir;
    log << "]\n";
    cout << "\n\nScanning Started...";
    clean(dir.c_str());
    cls();
    Color(12);
    cout << "Viruses Found:\t" << _v << endl;
    Color(2);
    cout << "Viruses Removed:\t" << _c << endl;
    cout << "Original Files Found & Restored:\t" << _o << endl;
    log << "\n\nViruses Found:\t" << _v;
    log << "\nViruses Removed:\t" << _c;
    log << "\nOriginal Files Found & Restored:\t" << _o;
    log.close();
    cout << "Exiting...";
    Sleep(10000);
    return 0;
}
void cls()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
    {
      return;
    }
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    if( !FillConsoleOutputCharacter( hConsole,(TCHAR) ' ',dwConSize,coordScreen,&cCharsWritten ))
    {
      return;
    }
    if( !GetConsoleScreenBufferInfo( hConsole, &csbi ))
    {
      return;
    }
    if( !FillConsoleOutputAttribute( hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten ))
    {
      return;
    }
    SetConsoleCursorPosition( hConsole, coordScreen );
}
void Color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
bool check_process(string process)
{
    HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(handle == INVALID_HANDLE_VALUE)
    return false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(entry);
    if(!Process32First(handle,&entry))
	{
		CloseHandle(handle);
		return false;
	}
    while (Process32Next(handle, &entry))
    {
        if(!strcmp(entry.szExeFile,process.c_str())){
            CloseHandle(handle);
            hProcess = OpenProcess(PROCESS_ALL_ACCESS,false,entry.th32ProcessID);
            return true;
        }
    }
    CloseHandle(handle);
    return false;
}
bool kill_process()
{
    bool ret=false;
    if(TerminateProcess(hProcess,0))
    {
        ret=true;
    }
    CloseHandle(hProcess);
    return ret;
}
bool CheckOneInstance()
{
    HANDLE  m_hStartEvent = CreateEventW( NULL, FALSE, FALSE, L"bbVADSVHJFIJ$34tuv34vVWE" );
    if(m_hStartEvent == NULL)
    {
    CloseHandle( m_hStartEvent );
        return false;
    }
    if ( GetLastError() == ERROR_ALREADY_EXISTS ) {

        CloseHandle( m_hStartEvent );
        m_hStartEvent = NULL;
        // already exist
        // send message from here to existing copy of the application
        return false;
    }
    // the only instance, start in a usual way
    return true;
}
void clean(const char* x)
{
    char dirnPath[1024];
    sprintf(dirnPath, "%s\\*", x);
    WIN32_FIND_DATA f;
    HANDLE h = FindFirstFile(dirnPath, &f);
    do
    {
        const char * name = f.cFileName;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) { continue; }
        char filePath[1024];
        sprintf(filePath, "%s%s%s", x, "\\", name);
        string t = filePath;
        if(f.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY && t.substr(t.rfind(".")+1) == "exe" && f.nFileSizeLow == _Size)
        {
            log << "Found:";
            log << filePath;
            log << "\t\t";
            _v++;
            string tm = x;
            tm.append("\\g");
            tm.append(f.cFileName);
            ///Taskkill the virus
            if(check_process(f.cFileName))
            {
                log << "Running";
                if(kill_process())
                    log << "Killed...";
                else
                    log << "Virus Still Running...";
            }
            ///Delete it and get original program
            if(DeleteFileA(filePath))
            {
                _c++;
            }
            if(SetFileAttributesA(tm.c_str(),FILE_ATTRIBUTE_NORMAL))
            {
                rename(tm.c_str(),filePath);
                _o++;
                log << "\t\t[Cleaned]";
            }
            log << "\n";
        }
        if(f.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
        {
            clean(filePath);
        }
    } while(FindNextFile(h,&f));
    FindClose(h);
}
