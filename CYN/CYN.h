#pragma once

#include "resource.h"
//#include <string.h>
//#include "stdlib.h"
#include <stdio.h>

#define FUCKING_CN	199
#define FUCKING_AB	198
#define FUCKING_EX	197
#define FUCKING_LL	196
#define FUCKING_LR	195

#define BFSZ	128

int margin=20;
int mWidth=285;
//int mHeight=257;
int mHeight=577;
int left = 50;//GetSystemMetrics(SM_CXSCREEN)/2 -mWidth/2 -margin;
int top = GetSystemMetrics(SM_CYSCREEN)/2 -mHeight/2 -2*margin;
char wtrName[16];

COLORREF bgc = RGB(255, 255, 255);

#include <windows.h>
#include <malloc.h>
#include <tlhelp32.h>
#include <math.h>
#include <commctrl.h>

//#define ADDR_OF_ADDR_OF_NAME 0x5FA014		//	since v0.5
//#define ADDR_OF_ADDR_OF_NAME 0x5FA024		//	since v0.62: for HF 5.3.6.1126
//#define ADDR_OF_ADDR_OF_NAME 0x5BCA24		//	since v0.63: for HF 5.4.4.422
#define ADDR_OF_ADDR_OF_NAME 0x5AB544		//				 for HF 5.5.3.126

//#define ADDR_OF_GRADE 0x10085E10			//	��ȡ���ֵĵ�ַ
//#define ADDR_OF_GRADE 0x1007BEF8			//	since v0.63: for HF 5.4.4.422
#define ADDR_OF_GRADE 0x100753B8			//				 for HF 5.5.3.126

/*
#define ADDR_OF_FIRST_LV 0x06C4D340		//	since v0.64: for Lv -x
#define ADDR_OF_LAST_LV0x06C5C640	//?

#define ADDR_OF_FIRST_NAME 0x06C60040	// every 0x100
#define OFFSET_OF_LV_NAME0x12D00
*/
// http://www.vckbase.com/document/viewdoc/?id=1223
// http://tech.e800.com.cn/articles/2009/1023/1256260553203_1.html
// http://zhidao.baidu.com/question/146925087
// �ںƷ����������ڴ�ռ䣬�������б� since v0.64 for Lv-

#define M(m) MessageBoxA(NULL, m, "MSG", 0)
#define MW(m) MessageBoxW(NULL, m, L"MSG", 0)

HANDLE hMutex;
HANDLE pHandle;
HWND hWndMain;

void promoteP()
{
	// ��ȨΪDEBUGGER
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |TOKEN_QUERY, &hToken);
	LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &sedebugnameValue);
	tkp.PrivilegeCount = 1;tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);
	CloseHandle(hToken);
}

void MessageInteger(DWORD ix)
{
	char s[10]; 
	_itoa_s(ix,s,10); 
	MessageBoxA(NULL,s, " ",MB_OK);
}

bool checkMutex()
{
	hMutex = CreateMutex(NULL, FALSE, L"HFNameChangerV0.63");
	DWORD dw = WaitForSingleObject(hMutex, 0);
	if (WAIT_FAILED == dw)
	{
		MessageBox(NULL, L"����������ʧ�ܡ�", L"CYN", 0);
		CloseHandle(hMutex); // �ͷž������ָ��ͬһϵͳ��������о���ͷź󣬸ö��󽫱�ɾ����
		return false;
	}
	else if (WAIT_TIMEOUT == dw)
	{
		// ����һ��ʵ����������
		CloseHandle(hMutex);
		//		X("�����Ѿ����С�");
		HWND hwndMain=FindWindow(L"CYN_CLASS",NULL);
		SetForegroundWindow(hwndMain);
		return false;
	}
	return true;
}

char* getLastName()
{
	char* lastName=new char[16];
	lastName="��������";
	HKEY hk;
	LPBYTE bLastName=new BYTE[32];
	LPCTSTR REGPATH=L"SOFTWARE";
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGPATH,0,KEY_READ,&hk) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		DWORD read = 32;
		if(ERROR_SUCCESS==RegQueryValueExA(hk, "CYNLASTNAME", 0, &dwType, bLastName, &read))
			lastName=(char*)bLastName;
	}
	RegCloseKey(hk);
	return lastName;
}

HANDLE GetProcessHandle(int nID)
{
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, nID);
}

bool IsInRoom(HANDLE pHandle)
{
	DWORD read;
	LPTSTR lpBuffer = (LPTSTR)malloc(4);
	ReadProcessMemory(pHandle, (LPVOID)ADDR_OF_GRADE, lpBuffer, 4, &read);
	if(strlen((char*)lpBuffer)==0)
	{
		free(lpBuffer);
		//		MessageBox(NULL, "û�������䣬û��(�����)������Ϣ", NULL, 0);
		return false;
	}
	free(lpBuffer);
	return true;
}

DWORD GetAddrOfNameInGame(HANDLE pHandle)
{
	//	I("��ADDR_OF_ADDR_OF_NAME����ADDR_OF_NAME");
	DWORD read;
	//	LPTSTR lpBuffer = (LPTSTR)malloc(8);
	char lpBuffer[8];
	ReadProcessMemory(pHandle, (LPVOID)ADDR_OF_ADDR_OF_NAME, (LPVOID)lpBuffer, 8, &read);
	if(read==0)
	{
		free(lpBuffer);
		MessageBoxA(NULL, "�޷���ADDR_OF_ADDR_OF_NAME����ȡ�������ֵĵ�ַ������ϵ���ߡ�", "CYN", 0);
		return 0;
	}
	DWORD addrOfNameInGame=0;
	unsigned char i=0;
	unsigned char c=0;
	for(; i<8; i++)
	{
		c=(unsigned char)(lpBuffer[i]);
		addrOfNameInGame=addrOfNameInGame+(unsigned int)(c*pow(256.0, (double)i));
	}
	//	free(lpBuffer);
	return addrOfNameInGame;
}

typedef struct _WND_INFO
{
	HWND hWnd;
	int listCount;
	bool rev;
}WNDINFO, *PWNDINFO;


bool hasl(wchar_t* str)
{
	int i=0;
	do
	{
		if(str[i]=='|')
			return true;
	}
	while(str[i++]);
	return false;
}

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{

	//��鵱ǰö�ٵ�hWnd��className�Ƿ�ΪSysListView32
	//Ȼ���ж��б����Ƿ�С��255
	//���Ŷ�ȡ��һ���б�ĵ��������ݣ���������ַ�'|'��ô����б��ھ������������ȡ�Ķ���
	WNDINFO* pInfo = (WNDINFO*)lParam;

	wchar_t className[64];
	GetClassNameW(hWnd, className, 64);

	int lc = ListView_GetItemCount(hWnd);

	if( 0 == _wcsicmp(className, L"SysListView32") && lc < 251)
	{
		DWORD read=0;
		LVITEM lvi, *_lvi, lvItem;
		wchar_t item[BFSZ], *_item;

		ZeroMemory(item, sizeof(wchar_t[BFSZ]));
		ZeroMemory(&lvItem, sizeof(LV_ITEM));
		// �����ڴ�ռ�
		_lvi=(LVITEM*)VirtualAllocEx(pHandle, NULL, sizeof(LVITEM),MEM_COMMIT, PAGE_READWRITE);
		_item =(wchar_t*)VirtualAllocEx(pHandle, NULL, sizeof(wchar_t[BFSZ]), MEM_COMMIT,PAGE_READWRITE);

		lvi.cchTextMax=BFSZ;
		lvItem.mask=LVIF_TEXT;

		// ��ȡ������Ϣ
		lvi.iSubItem=2;	// ��3�е��ַ�
		lvi.pszText=_item;
		WriteProcessMemory(pHandle, _lvi, &lvi, sizeof(LVITEM), NULL);
		SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)0, (LPARAM)_lvi);
		// ��ȡ�����ڴ�
		ReadProcessMemory(pHandle, _item, item, BFSZ, NULL);
		// �ͷ��ڴ�ռ�
		VirtualFreeEx(pHandle, _lvi,0, MEM_RELEASE);
		VirtualFreeEx(pHandle, _item,0, MEM_RELEASE);
		if(hasl(item))
		{
			pInfo->hWnd = hWnd;//�Ǿ��������������
			pInfo->listCount = lc;
//			MW(item);
			return FALSE;//ֹͣö��.
		}
	}
	return TRUE;
}

void TrimItem2Name(wchar_t* item, wchar_t* dstBuffer, int size)
{
	//HF.�ʺ�
	//����
	int i, indexOfg=0, inx=0;
	for(i=0; i< size; i++)	// ����ַ�����
		if(item[i]=='\n')	//	����Ƿָ�������ô�����ַ������ǵ�ǰ�±�+1
		{
			indexOfg++;
			if(indexOfg==1)
				inx=i+1;
			else if(indexOfg==2)
			{
				item[i-1]=L'\0';
				memcpy_s(dstBuffer, size, &item[inx], size);
				return;
			}
		}
}

bool TrimItem2Grade(wchar_t* item, wchar_t* dstBuffer, int size)
{
	//52|12|-1���ؾ�
	int i, indexOfg=0, inx=0;
	for(i=0; i< size; i++)	// ����ַ�����
	{
		if(item[i]=='|')	//	����Ƿָ������͸���������1
		{
			indexOfg++;
			if(indexOfg==2)	//	�������Σ���ô�ȼ��ַ������ǵ�ǰ�±�+1
			{
//				if(item[i+1]=='-')
					inx=i+1;
//				else
//					return false;
			} else if (indexOfg==3)
			{
				item[i]=L'\0';
				memcpy_s(dstBuffer, size, &item[inx], size);
				return true;
			}
		}
	}
	return false;
}

// ��SysListView32������ ѡȡ������������ҵ��б� 20110203 for 0.64
void InsertTheList(HANDLE pHandle, HWND LL)//, HWND LR)
{

	WNDINFO info = {0};
	info.hWnd = 0;
	info.listCount = 0;
	//GetTheListHWNDByProcessId(&info, pID);
	//	MessageInteger((DWORD)info.hWnd);
	HWND hfMain = FindWindowA(NULL, "�Ʒ��羺ƽ̨ - 5.5.3.126");
	if(hfMain==NULL)	// ��ȡʧ��
	{
		MessageBoxA(NULL, "û���ҵ��Ʒ�5.5.3.126�����ڡ�", "��Ǹ", 0);
		//MessageInteger(pID);
		return;
	}

	EnumChildWindows(hfMain,EnumChildProc,(LPARAM)&info);
	if(info.hWnd==NULL)	// ��ȡʧ��
	{
		MessageBoxA(NULL, "�޷���ȡ��ǰ�����û��б�Ҳ���ǵ�ǰ��������������50��������Ӱ���ֶ�������", "��Ǹ", 0);
		//MessageInteger(pID);
		return;
	}
	hfMain=info.hWnd;
	int lc = info.listCount;

	int i;
	//	char j;
	//	bool bFind;

	DWORD read=0;
	LVITEM lvi, *_lvi, lvItem;
//	char item1[32], item2[32];//, item3[32];
	wchar_t item[BFSZ], grade[BFSZ];
//	char *_item1, *_item2;//,*_item3;
	wchar_t *_item;

	ZeroMemory(item, sizeof(wchar_t[BFSZ]));
	ZeroMemory(&lvItem, sizeof(LV_ITEM));
//	memset(item1,0,32);
//	memset(item3,0,32);
//	memset(item2,0,32);

	// �����ڴ�ռ�
//	_lvi=(LVITEMA*)VirtualAllocEx(pHandle, NULL, sizeof(LVITEM),MEM_COMMIT, PAGE_READWRITE);
//	_item1 =(char*)VirtualAllocEx(pHandle, NULL, 32, MEM_COMMIT,PAGE_READWRITE);
//	_item2 =(char*)VirtualAllocEx(pHandle, NULL, 32, MEM_COMMIT,PAGE_READWRITE);
//	_item3 =(char*)VirtualAllocEx(pHandle, NULL, 32, MEM_COMMIT,PAGE_READWRITE);
	_lvi=(LVITEM*)VirtualAllocEx(pHandle, NULL, sizeof(LVITEM),MEM_COMMIT, PAGE_READWRITE);
	_item =(wchar_t*)VirtualAllocEx(pHandle, NULL, sizeof(wchar_t[BFSZ]), MEM_COMMIT,PAGE_READWRITE);

	lvi.cchTextMax=BFSZ;
	lvItem.mask=LVIF_TEXT;

		/*/ ��ȡ������Ϣ
		lvi.iSubItem=1;	// ��2�е��ַ�
		lvi.pszText=_item;
		WriteProcessMemory(pHandle, _lvi, &lvi, sizeof(LVITEM), NULL);
		SendMessage(hfMain, LVM_GETITEMTEXT, (WPARAM)1, (LPARAM)_lvi);
		// ��ȡ�����ڴ�
		ReadProcessMemory(pHandle, _item, item, BFSZ, NULL);
		MW(item);

		lvi.iSubItem=1;	// ��2�е��ַ�
		WriteProcessMemory(pHandle, _lvi, &lvi, sizeof(LVITEM), NULL);
		SendMessage(hfMain, LVM_GETITEMTEXT, (WPARAM)0, (LPARAM)_lvi);
		// ��ȡ�����ڴ�
		ReadProcessMemory(pHandle, _item, item, BFSZ, NULL);
		MW(item);
	*///* ����Ӧ�õݼ������������������һ��˳��
	for(i=lc-1; i>=0; i--)
	{
		// ��ȡ������Ϣ
		lvi.iSubItem=2;	// �����е��ַ�
		lvi.pszText=_item;
		WriteProcessMemory(pHandle, _lvi, &lvi, sizeof(LVITEM), NULL);
		SendMessage(hfMain, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);
		// ��ȡ�����ڴ�
		ReadProcessMemory(pHandle, _item, item, BFSZ, NULL);

		// ���ӵ��б�
//		if(TrimItem2Grade(item, item, BFSZ))	// ����Ǹ�����
		TrimItem2Grade(item, item, BFSZ);
		{
			memcpy_s(grade, BFSZ, item, BFSZ); //������

			// ��ȡ��2�м�¼
			lvi.iSubItem=1;
			lvi.pszText=_item;
			WriteProcessMemory(pHandle, _lvi, &lvi, sizeof(LVITEM), NULL);
			SendMessage(hfMain, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);
			// ��ȡ�����ڴ�
			ReadProcessMemory(pHandle, _item, item, BFSZ, NULL);

			// ���ӵ��б�
			TrimItem2Name(item, item, BFSZ);
			// ��������
			lvItem.pszText = item;
			lvItem.iSubItem = 0; 
			ListView_InsertItem(LL, &lvItem);
			// ���Ļ���
			lvItem.pszText = grade;
			lvItem.iSubItem = 1;			//	���ȼ���Ϣ�����б�ĵڶ���
			ListView_SetItem(LL, &lvItem);
		}
//		else								//	������Ǹ����ģ�������
//			continue;

		// ��ȡ�����м�¼
//		lvi.iSubItem=2;
		//lvi.pszText=_item3;
		//WriteProcessMemory(pHandle, _lvi, &lvi, sizeof(LVITEM), NULL);
		//::SendMessage(info.hWnd, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);

		// ��ȡ�����ڴ�
//		ReadProcessMemory(pHandle, _item1, item1, 32, NULL);
		//ReadProcessMemory(pHandle, _item2, item2, 32, NULL);
//		ReadProcessMemory(pHandle, _item3, item3, 32, NULL);

		// ���ӵ��б�
			// �ȼ����ұ��б�
//		SendMessageA(LR, LB_ADDSTRING, 0, (LPARAM)(LPCSTR)item1);
		// �ȼ�������б�
//		SendMessageA(LL, LB_ADDSTRING, 0, (LPARAM)(LPCSTR)item2);
//		ListView_InsertItem(LL, item1);
//		ListView_InsertItem(LL, item2);
	}

	// �ͷ��ڴ�ռ�
	VirtualFreeEx(pHandle, _lvi,0, MEM_RELEASE);
	VirtualFreeEx(pHandle, _item,0, MEM_RELEASE);
//	VirtualFreeEx(pHandle, _lvi,0, MEM_RELEASE);
//	VirtualFreeEx(pHandle, _item1,0, MEM_RELEASE);
//	VirtualFreeEx(pHandle, _item2,0, MEM_RELEASE);
//	VirtualFreeEx(pHandle, _item3,0, MEM_RELEASE);

	/*	for(i=0; i<info.listCount; i++)
	{
	ListView_GetItemText(info.hWnd, i, 0, lBuffer, 64);
	//		SendMessageA(LL, LB_ADDSTRING, 0, (LPARAM)(LPCSTR)lBuffer);
	ReadProcessMemory(pHandle, (LPVOID)i, lBuffer, 64, &read);	//	��ǰ�ȼ�
	j=0; bFind=false;
	while(j<60)	// ����û��-��
	{
	if(lBuffer[j++]==45)
	{
	bFind=true;
	break;
	}
	}
	if(bFind)								// ����� ���뵽�б���
	{
	// �ȼ����ұ��б�
	SendMessageA(LR, LB_ADDSTRING, 0, (LPARAM)(LPCSTR)lBuffer);
	// �ȼ�������б�
	ReadProcessMemory(pHandle, (LPVOID)(i+OFFSET_OF_LV_NAME), lBuffer, 64, &read);
	SendMessageA(LL, LB_ADDSTRING, 0, (LPARAM)(LPCSTR)lBuffer);
	}
	}
	*/
}


bool checkWindows(HWND WAR3P, HWND HFP, HWND INROOM, HWND CURNAME, HWND EDITCN, HWND LL, bool check)//, HWND LR, bool check)
{
	//	I("���Ʒ���ħ���������Ƿ���������...");
	SetWindowText(HFP, L"δ���");
	SetWindowText(WAR3P, L"δ���");
	SetWindowText(INROOM, L"δ���");
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);	// Ѱ�ҺƷ�������
	if (INVALID_HANDLE_VALUE == hSnapshot) {
		SetWindowText(HFP, L"�����б��޷�����");
		return false;
	}
	//	HANDLE pHandle=NULL;
	PROCESSENTRY32 pe = { sizeof(pe) };
	BOOL fOk;
	DWORD pID=0;
	wchar_t* GC1=L"GameClient.exe";
	wchar_t* GC2=L"gameclient.exe";
	wchar_t* War3=L"war3.exe";
	wchar_t* War4=L"War3.exe";
	//	WCHAR *tmpStr;
	int retx=0;
	//*
	for (fOk = Process32First(hSnapshot, &pe); fOk; fOk = Process32Next(hSnapshot, &pe))
	{
		if (0==_wcsicmp(GC1, pe.szExeFile) ||
			0==_wcsicmp(GC2, pe.szExeFile))
			//		MessageBox(NULL, pe.szExeFile, pe.szExeFile, 0);
			/*/		if ((pe.szExeFile[0]=='g' || pe.szExeFile[0]=='G')
			&& (pe.szExeFile[1]=='a'|| pe.szExeFile[1]=='A')
			&& (pe.szExeFile[2]=='m'|| pe.szExeFile[2]=='M')
			&& (pe.szExeFile[3]=='e'|| pe.szExeFile[3]=='E')
			&& (pe.szExeFile[4]=='c'|| pe.szExeFile[4]=='C')
			&& (pe.szExeFile[5]=='l'|| pe.szExeFile[5]=='L')
			&& (pe.szExeFile[6]=='i'|| pe.szExeFile[6]=='I')
			&& (pe.szExeFile[7]=='e'|| pe.szExeFile[7]=='E')
			&& (pe.szExeFile[8]=='n'|| pe.szExeFile[8]=='N')
			&& (pe.szExeFile[9]=='t'|| pe.szExeFile[9]=='T')
			|| 0==strcmp(GC1, (char*)pe.szExeFile)
			|| 0==strcmp(GC2, (char*)pe.szExeFile)
			)
			//*/
		{
			//			char s[10]; 
			//			_itoa(pe.th32ProcessID,s,10); 
			//			MessageBoxA(NULL,s, " ",MB_OK); 
			pID=pe.th32ProcessID;
			pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);// ��ȡ���Ʒ����̵�handle
		}
		//		retx=_wcsicmp(War3, (wchar_t*)pe.szExeFile);
		/*/		if ((pe.szExeFile[0]=='w' || pe.szExeFile[0]=='W')
		&& (pe.szExeFile[1]=='a'|| pe.szExeFile[1]=='A')
		&& (pe.szExeFile[2]=='r'|| pe.szExeFile[2]=='R')
		&& (pe.szExeFile[5]=='e'|| pe.szExeFile[5]=='E')
		&& (pe.szExeFile[6]=='x'|| pe.szExeFile[6]=='X')
		&& (pe.szExeFile[7]=='e'|| pe.szExeFile[7]=='E')
		|| 0==strcmp(War3, (char*)pe.szExeFile)
		|| 0==strcmp(War4, (char*)pe.szExeFile)
		)
		//*/
		if (0==_wcsicmp(War3, pe.szExeFile) ||
			0==_wcsicmp(War4, pe.szExeFile))
		{
			SetWindowText(WAR3P, L"ħ��������");
			return false;
		}
	}
	SetWindowText(WAR3P, L"OK");
	//	SendMessage(hWndMain, WM_PAINT, 0, 0);
	CloseHandle(hSnapshot);
	if(pHandle==NULL)
	{
		SetWindowText(HFP, L"�Ʒ�δ����");
		return false;
	}
	SetWindowText(HFP, L"OK");
	DWORD ProcID=0;
	//	LPSTR lpClassName=(LPSTR)malloc(16);
	HWND GameClient=FindWindow(L"#32770", L"�Ʒ��羺ƽ̨");				// �ҵ���¼����˵��û�е�¼
	if(GameClient!=NULL)
	{
		CloseHandle(pHandle);
		SetWindowText(INROOM, L"�Ʒ�δ��¼");
		return false;
	}
	if(!IsInRoom(pHandle))
	{
		CloseHandle(pHandle);
		SetWindowText(INROOM, L"δ���뷿��");
		return false;
	}
	SetWindowText(INROOM, L"OK");
	/*
	#define ADDR_OF_FIRST_LV 0x06C4D340		//	since v0.64: for Lv -x
	#define ADDR_OF_LAST_LV0x06C5C640	//?

	#define ADDR_OF_FIRST_NAME 0x06C60040	// every 0x100
	*/
	if(!check)
		InsertTheList(pHandle, LL);//, LR);

	//*/
	DWORD addrNameInGame=GetAddrOfNameInGame(pHandle);
	DWORD read;
	char nameBuffer[16];
	char limitedLength=0x20;
	GetWindowTextA(EDITCN, nameBuffer, 16);
	if(check)
	{
		WriteProcessMemory(pHandle,(LPVOID)(addrNameInGame-8),&limitedLength,1,NULL);	// 0.62updated��ȡ��ԭ�ַ������ȵ����ƣ����䵽15�ֽ�
		WriteProcessMemory(pHandle,(LPVOID)addrNameInGame,nameBuffer,16,NULL);	// ֱ��д
//		WriteProcessMemory(pHandle,(LPVOID)(addrNameInGame+16),nameBuffer,16,NULL);	// ֱ��д 0.63updated��������еĹ���

	}
	ReadProcessMemory(pHandle, (LPVOID)addrNameInGame, nameBuffer, 16, &read);	//	��ǰ����
	SetWindowTextA(CURNAME, nameBuffer);
	strcpy_s(wtrName, 16, nameBuffer);
	CloseHandle(pHandle);
	return true;
}

void writeToReg()
{
	HKEY hk;
	unsigned char sz[16];
	LPCTSTR REGPATH=L"SOFTWARE";
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGPATH,0,KEY_WRITE,&hk) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		//		DWORD read = 32;

		DWORD sl=16;
		strcpy_s( (char*)sz, 16, wtrName);
		RegSetValueExA(hk,"CYNLASTNAME",NULL,dwType,sz,sl);
	}
	RegCloseKey(hk);
}

int CALLBACK ListViewCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	//�ҵĵ�����������*WINFO
	WNDINFO *px = (PWNDINFO)lParamSort;
	wchar_t str1[16];
	wchar_t str2[16];

	ListView_GetItemText(px->hWnd, lParam1, px->listCount, str1, 16);
	ListView_GetItemText(px->hWnd, lParam2, px->listCount, str2, 16);
	return _wcsicmp(str1, str2)*(px->rev? 1: -1);
}