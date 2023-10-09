#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <Windows.h>

DWORD GetWindowsVersionNumber() {
    // 获取操作系统信息
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);

    // 返回版本号
    return osvi.dwBuildNumber;
}

std::string ReceiveTcp(const std::string& ipAddress, const std::string& port) {
    //检测版本号
    if (GetWindowsVersionNumber() < 2474)
    {
        return "最低要求Windows XP以运行EasyTCP";
    }

    // 构建命令字符串
    std::string command = "telnet " + ipAddress + " " + port;

    // 执行命令并获取输出
    FILE* fp = popen(command.c_str(), "r");
    if (!fp) {
        return "无法执行telnet命令。";
    }

    char buffer[256];
    std::string response;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        response += buffer;
    }

    // 关闭流
    pclose(fp);

    // 返回输出结果
    return response;
}

std::string CreateTcp(const std::string& ipAddress, const std::string& port, const std::string& message) {
    //检测版本号
    if (GetWindowsVersionNumber() < 2474)
    {
        return "最低要求Windows XP以运行EasyTCP";
    }

    // 构建命令字符串
    std::string command = "echo " + message + " | telnet " + ipAddress + " " + port;

    // 执行命令并获取输出
    FILE* fp = popen(command.c_str(), "r");
    if (!fp) {
        return "无法执行telnet命令。";
    }

    char buffer[256];
    std::string response;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        response += buffer;
    }

    // 关闭流
    pclose(fp);

    // 返回输出结果
    return response;
}