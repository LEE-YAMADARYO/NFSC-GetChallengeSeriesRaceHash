// Copyright(C) 2025 YAMADA RYO
// 此 ASI 插件用于查找 Need for Speed Carbon 挑战赛哈希值
// 该代码根据 MIT 许可证发布
// 著作权所有
#include "pch.h"
#include <windows.h>
#include "MinHook\include\MinHook.h" // 请自行获取 MinHook
#include <cstdio>

// 定义原始函数的类型
// 函数地址: 0x004AA000
// 函数签名: char __stdcall DALChallenge::GetChallengeEventHashByIndex(_DWORD *, int)
typedef char(__stdcall* GetChallengeEventHashByIndex_t)(unsigned int* EventHash, int BinIndex);

// 保存原始函数地址的指针
GetChallengeEventHashByIndex_t fpOriginalGetChallengeEventHashByIndex = NULL;

// 需要查找的挑战赛索引
const int TARGET_CHALLENGE_INDEX = 0;

// Hook 函数
char __stdcall DetourGetChallengeEventHashByIndex(unsigned int* EventHash, int BinIndex) {

    // 调用原始函数获取哈希值
    char result = fpOriginalGetChallengeEventHashByIndex(EventHash, BinIndex); // Corrected this line

    // 打印获取的哈希值
    printf("已获取索引为 %d 挑战赛的哈希值, 返回的哈希值为: 0x%X\n", BinIndex, *EventHash);

    // 打印指定索引的哈希值
    // if (BinIndex == TARGET_CHALLENGE_INDEX) {
        // printf("索引为 %d 的挑战赛哈希值: 0x%X ---\n", BinIndex, *EventHash);
    // }

    // 返回原始函数的结果
    return result;
}

// 初始化 Hook
void InitializeHook() {
    AllocConsole();
    FILE* pDummyFile;
    if (freopen_s(&pDummyFile, "CONOUT$", "w", stdout) != 0) {
        MessageBoxA(NULL, "控制台重定向失败", "错误", MB_ICONERROR);
        return;
    }

    printf("挑战赛哈希值获取器: 正在初始化\n");

    if (MH_Initialize() != MH_OK) {
        MessageBoxA(NULL, "MinHook 初始化失败", "错误", MB_ICONERROR);
        printf("MinHook 初始化失败\n");
        return;
    }

    // 获取原始函数的地址
    LPVOID pTarget = (LPVOID)0x004AA000;

    // 创建 Hook
    if (MH_CreateHook(pTarget, DetourGetChallengeEventHashByIndex, (LPVOID*)&fpOriginalGetChallengeEventHashByIndex) != MH_OK) { // Corrected this line
        MessageBoxA(NULL, "创建 Hook 失败", "错误", MB_ICONERROR);
        printf("创建 Hook 失败\n");
        return;
    }

    // 启用 Hook
    if (MH_EnableHook(pTarget) != MH_OK) {
        MessageBoxA(NULL, "启用 Hook 失败", "错误", MB_ICONERROR);
        printf("启用 Hook 失败\n");
    }
    else {
        printf("挑战赛哈希值获取器: 启用 Hook 成功\n", pTarget);
    }
}

// DLL 入口点
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        InitializeHook();
        break;
    case DLL_PROCESS_DETACH:
        MH_Uninitialize();
        break;
    }
    return TRUE;
}