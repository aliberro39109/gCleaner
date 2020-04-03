# gCleaner
Cleans a specific directory from the ground virus and restores your previous apps back.

Ground, a well-known virus by many security specialists, ground is a virus that spreads mostly via USB flash drives, everything inside your USB would become a .lnk (Shortcut), but after you choose an infected location (like C:\,D:\), this app will kill all instances of the virus in this directory and then restore back every affected application.
Some features that one could pull out and use in his own project, based on Windows APIs:
```cpp
void Color(int color); //Change console color, the color is in accordance with the command prompt colors 0x00->0xFF
void cls(); //Clear the screen 
bool checkOneInstance(); //Only run once, returns if the app has one instance or more
bool kill_process();//kill a process through a handle , returns if the process has been terminated or not
bool check_process(string& processname); //Check if a process is active or not
```
