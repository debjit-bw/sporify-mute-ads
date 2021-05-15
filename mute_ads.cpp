#include <windows.h>
#include <iostream>
using namespace std;

int flag = 0;
int codeMuted = 0;

string ell = " ...", holder;

void roll()
{
    int i = ell.find(' ');
    ell[i] = '.';
    ell[(i+1)%4] = ' ';
}

void nudgeVolume()
{
    WORD arr[] = {VK_VOLUME_UP, VK_VOLUME_DOWN};
    for (int t=0; t<2; t++)
    {
        INPUT ip={0};
        ip.type = INPUT_KEYBOARD;
        ip.ki.wVk = arr[t];   //or VOLUME_DOWN or MUTE
        SendInput(1, &ip, sizeof(INPUT));
        ip.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &ip, sizeof(INPUT));
    }
}

void muteVolume()
{
    nudgeVolume();

    INPUT ip={0};
    ip.type = INPUT_KEYBOARD;

    ip.ki.wVk = VK_VOLUME_MUTE;
    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

bool isPresent(string str, string str1)
{
    size_t found = str.find(str1); 
    if (found != string::npos) 
        return true;
    return false;
}

string convertToString(char* a, int size) 
{ 
    int i; 
    string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
 if(IsWindowVisible(hwnd)) // check whether window is visible
 {
    char wnd_title[256];
    GetWindowText(hwnd,wnd_title,sizeof(wnd_title));
    string title = convertToString(wnd_title, sizeof(wnd_title)/sizeof(char));
    if (isPresent(title, "Advertisement"))
        flag = 1;
 }
 return true; // function must return true if you want to continue enumeration
}

void check()
{
    EnumWindows(EnumWindowsProc,0);
}


int barvar = 0;
unsigned char barchar[2] = {219, 176};
void prt_bar(int i = barvar, int steps = 117)
{
    cout<<'\r';
    if (barvar>=steps)
    {
        barvar = barvar % steps;
        unsigned char t = barchar[0];
        barchar[0] = barchar[1];
        barchar[1] = t;
    }
    cout<<'|';
    for (int i = 0; i < steps; i++)
        if (i <= barvar)
            cout<<barchar[0];
        else
            cout<<barchar[1];
    cout<<'|';
    barvar += 1;
}

void prtClr(int n)
{
    for (int i = 0; i < n; i++)
        cout<<' ';
}

int main()
{
    system("Color 02");
    SetConsoleTitle("Running");

    while (true)
    {
        flag = 0;
        check();
        if (flag == 1 && codeMuted == 0)
        {
            muteVolume();
            codeMuted = 1;
            system("Color 4E");
            cout<<"\rMuted";
            prtClr(114);
            SetConsoleTitle("Muted");
            cout<<endl;
        }
        else if (flag == 0 && codeMuted == 1)
        {
            nudgeVolume();
            codeMuted = 0;
            system("Color 02");
            cout<<"\rUnmuted";
            prtClr(112);
            SetConsoleTitle("Running");
            cout<<endl;
        }
        prt_bar();
        Sleep(100);
    }
}
