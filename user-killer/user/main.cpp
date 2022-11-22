#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <vector>
#include<string>


int main() {
    STARTUPINFO si = {sizeof(si)};
    SECURITY_ATTRIBUTES saProcess,
            saThread;
    PROCESS_INFORMATION piProcess;

    saProcess.nLength = sizeof(saProcess);
    saProcess.lpSecurityDescriptor = NULL;
    saProcess.bInheritHandle = FALSE;

    saThread.nLength = sizeof(saThread);
    saThread.lpSecurityDescriptor = NULL;
    saThread.bInheritHandle = FALSE;

    DWORD dwPID = 3264;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,TRUE,dwPID);
    char szHANDLE[100];
    sprintf(szHANDLE,"%d",hProcess);
    SetEnvironmentVariable("PROC_TO_KILL", szHANDLE);

    TCHAR szInput[1000];
    std::string forCMD = "--name Telegram.exe --name Discord.exe";
    lstrcpyA(szInput, forCMD.c_str());

    if(CreateProcess(R"("D:\work\OS\killer1\cmake-build-debug\killer1.exe")",
                     szInput,&saProcess, &saThread,
                     FALSE,0,NULL,NULL, &si, &piProcess)){
        WaitForSingleObject(piProcess.hProcess, INFINITE);
        CloseHandle(piProcess.hThread);
        CloseHandle(piProcess.hProcess);
    }
    SetEnvironmentVariable("PROC_TO_KILL", NULL);
}