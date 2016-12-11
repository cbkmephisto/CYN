// MemList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <TCHAR.H>
#include <tlhelp32.h>   

BOOL ShowProcMemInfo(HANDLE hProcess)
{
//	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,
//		FALSE,
//		dwPID);
	if(hProcess == NULL)
		return FALSE;
	MEMORY_BASIC_INFORMATION mbi;
	PBYTE pAddress = NULL;
	TCHAR szInfo[200] = _T("BaseAddr Size Type State Protect \n");
	_tprintf(szInfo);
	while(TRUE)
	{
		if(VirtualQueryEx(hProcess, pAddress, &mbi, sizeof(mbi)) != sizeof(mbi))
		{
			break;
		}
		if((mbi.AllocationBase != mbi.BaseAddress) && (mbi.State != MEM_FREE))
		{
			_stprintf_s(szInfo, _T(" %08X %8dK "), 
				mbi.BaseAddress,
				mbi.RegionSize>>10);
		}
		else
		{
			_stprintf_s(szInfo, _T("%08X %8dK "), 
				mbi.BaseAddress,
				mbi.RegionSize>>10);
		}
		LPTSTR pStr = _T("");
		switch(mbi.Type)
		{
		case MEM_IMAGE: pStr = _T("MEM_IMAGE "); break;
		case MEM_MAPPED: pStr = _T("MEM_MAPPED "); break;
		case MEM_PRIVATE: pStr = _T("MEM_PRIVATE"); break;
		default: pStr = _T("-----------"); break;
		}
		_tcscat_s(szInfo, pStr);
		_tcscat_s(szInfo, _T(" "));
		switch(mbi.State)
		{
		case MEM_COMMIT: pStr = _T("MEM_COMMIT "); break;
		case MEM_RESERVE: pStr = _T("MEM_RESERVE"); break;
		case MEM_FREE: pStr = _T("MEM_FREE "); break;
		default: pStr = _T("-----------"); break;
		}
		_tcscat_s(szInfo, pStr);
		_tcscat_s(szInfo, _T(" "));
		switch(mbi.AllocationProtect)
		{
		case PAGE_READONLY: pStr = _T("PAGE_READONLY "); break; 
		case PAGE_READWRITE: pStr = _T("PAGE_READWRITE "); break; 
		case PAGE_WRITECOPY: pStr = _T("PAGE_WRITECOPY "); break; 
		case PAGE_EXECUTE: pStr = _T("PAGE_EXECUTE "); break; 
		case PAGE_EXECUTE_READ: pStr = _T("PAGE_EXECUTE_READ "); break; 
		case PAGE_EXECUTE_READWRITE: pStr = _T("PAGE_EXECUTE_READWRITE"); break; 
		case PAGE_EXECUTE_WRITECOPY: pStr = _T("PAGE_EXECUTE_WRITECOPY"); break; 
		case PAGE_GUARD: pStr = _T("PAGE_GUARD "); break; 
		case PAGE_NOACCESS: pStr = _T("PAGE_NOACCESS "); break; 
		case PAGE_NOCACHE: pStr = _T("PAGE_NOCACHE "); break; 
		default: pStr = _T("----------------------"); break;
		}
		_tcscat_s(szInfo, pStr);
		_tcscat_s(szInfo, _T("\n"));
		_tprintf(szInfo);
		pAddress = ((PBYTE)mbi.BaseAddress + mbi.RegionSize);
	}
	CloseHandle(hProcess);
	return TRUE;
} 


int _tmain(int argc, _TCHAR* argv[])
{
	printf("Hello World!\n");
	
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |TOKEN_QUERY, &hToken);
	LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue);
	tkp.PrivilegeCount = 1;tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);
	CloseHandle(hToken);

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	// 寻找浩方主程序
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		MessageBox(NULL, L"不能打开系统进程列表。程序不能继续。", NULL, 0);
		return NULL;
	}
	HANDLE pHandle=NULL;
	PROCESSENTRY32 pe = { sizeof(pe) };
	BOOL fOk;
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe)) {
//		if (!_tcscmp(pe.szExeFile, L"MainProgram.exe")) {
		if (!_tcscmp(pe.szExeFile, L"gameclient.exe")) {
			CloseHandle(hSnapshot);
			pHandle=OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);		// 获取到浩方进程的handle
			break;
		}
	}
//	ShowProcMemInfo( GetCurrentProcessId() );
	ShowProcMemInfo(pHandle);
//	if(pHandle != NULL) CloseHandle(pHandle);
	return 0;
}

// 显示一个进程的内存状态 dwPID为进程ID
