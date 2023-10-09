#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <Windows.h>

DWORD GetWindowsVersionNumber() {
    // ��ȡ����ϵͳ��Ϣ
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);

    // ���ذ汾��
    return osvi.dwBuildNumber;
}

std::string ReceiveTcp(const std::string& ipAddress, const std::string& port) {
    //���汾��
    if (GetWindowsVersionNumber() < 2474)
    {
        return "���Ҫ��Windows XP������EasyTCP";
    }

    // ���������ַ���
    std::string command = "telnet " + ipAddress + " " + port;

    // ִ�������ȡ���
    FILE* fp = popen(command.c_str(), "r");
    if (!fp) {
        return "�޷�ִ��telnet���";
    }

    char buffer[256];
    std::string response;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        response += buffer;
    }

    // �ر���
    pclose(fp);

    // ����������
    return response;
}

std::string CreateTcp(const std::string& ipAddress, const std::string& port, const std::string& message) {
    //���汾��
    if (GetWindowsVersionNumber() < 2474)
    {
        return "���Ҫ��Windows XP������EasyTCP";
    }

    // ���������ַ���
    std::string command = "echo " + message + " | telnet " + ipAddress + " " + port;

    // ִ�������ȡ���
    FILE* fp = popen(command.c_str(), "r");
    if (!fp) {
        return "�޷�ִ��telnet���";
    }

    char buffer[256];
    std::string response;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        response += buffer;
    }

    // �ر���
    pclose(fp);

    // ����������
    return response;
}