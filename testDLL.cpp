// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
extern "C" __declspec(dllexport)
DWORD WINAPI MessageBoxThread(LPVOID lpParam) {
    MessageBox(NULL, L"You Ran a DLL!", L"DLL RAN", NULL);

    return 0;
}
DWORD WINAPI dllin(LPVOID lpParam) {
    MessageBox(NULL, L"Look it worked", L"DLL INJECTED", NULL);

    return 0;
}
DWORD WINAPI test(LPVOID lpParam) {
    printf("test");
    return 0;
}

extern "C" __declspec(dllexport)
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CreateThread(NULL, NULL, MessageBoxThread, NULL, NULL, NULL);
        CreateThread(NULL, NULL, dllin, NULL, NULL, NULL);
        CreateThread(NULL, NULL, test, NULL, NULL, NULL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
