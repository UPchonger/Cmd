#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>

using namespace std;

int main() {
    char c[100], Cf[10], ym[1000];
    int ca, cb;
    cout << "Cmd++" << "[版本 2.114.514]" << endl << "制作人:虫二。保留所有权利。" << endl << "使用command获取命令..." <<endl;
    while (1) {
        cout << "Users/chonger>>";
        cin.getline(c, 100);
        if (strcmp(c, "") == 0) {
            cout << "Users/chonger>>";
            cin.getline(c, 100);
        }
        if (strcmp(c, "command") == 0) {
            cout << "command:获取命令" << endl << "version:获取版本号" << endl << "compute:进行加减乘除的运算（只支持一级）" <<endl<<"ping:测试某个域名是否可用"<<endl;
            c[0] = '\0';
        } else if (strcmp(c, "version") == 0) {
            cout << "版本:v1.810.975" << endl;
            c[0] = '\0';
        } else if (strcmp(c, "compute") == 0) {
            // ... 代码略去 ...
        } else if (strcmp(c, "ping") == 0) {
            cout << "Users/chonger>>";
            cout << "请输入要测试的域名:";
            cin >> ym;
            cin.ignore(); // 忽略换行符
            string cmdLine = "ping " + string(ym);
            char buffer[1024];
            DWORD bytesRead;

            SECURITY_ATTRIBUTES securityAttributes;
            securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
            securityAttributes.lpSecurityDescriptor = NULL;
            securityAttributes.bInheritHandle = TRUE;

            HANDLE hReadPipe, hWritePipe;
            if (CreatePipe(&hReadPipe, &hWritePipe, &securityAttributes, 0)) {
                STARTUPINFO startupInfo;
                ZeroMemory(&startupInfo, sizeof(startupInfo));
                startupInfo.cb = sizeof(startupInfo);
                startupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
                startupInfo.wShowWindow = SW_HIDE;
                startupInfo.hStdInput = NULL;
                startupInfo.hStdOutput = hWritePipe;
                startupInfo.hStdError = hWritePipe;

                PROCESS_INFORMATION processInformation;
                ZeroMemory(&processInformation, sizeof(processInformation));

                if (CreateProcess(NULL, (LPSTR)cmdLine.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInformation)) {
                    WaitForSingleObject(processInformation.hProcess, INFINITE);
                    CloseHandle(hWritePipe);

                    while (ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead != 0) {
                        buffer[bytesRead] = '\0';
                        cout << buffer << endl;
                        ZeroMemory(buffer, sizeof(buffer));
                    }

                    CloseHandle(hReadPipe);
                    CloseHandle(processInformation.hProcess);
                    CloseHandle(processInformation.hThread);
                } else {
                    cout << "CreateProcess failed" << endl;
                    return 0;
                }
            } else {
                cout << "CreatePipe failed" << endl;
                return 0;
            }
        } else {
            cout << "未知命令..." << endl;
            c[0] = '\0';
        }
    }

    return 0;
}
