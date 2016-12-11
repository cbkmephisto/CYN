// CYN.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "CYN.h"
#pragma comment(lib,"comctl32")

#define MAX_LOADSTRING 100
#define LABHEIGHT 16
#define LABSTYLE WS_CHILD|WS_VISIBLE|SS_CENTER
#define LEDSTYLE WS_CHILD|WS_VISIBLE

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
HWND				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	//	if(false==checkMutex()) return 47;
	promoteP();
	InitCommonControls();
	// TODO: 在此放置代码。
	MSG msg;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CYN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	HWND hWnd=InitInstance (hInstance, nCmdShow);
	if ((HWND)-1==hWnd)
		return FALSE;
	// 主消息循环:
	hWndMain=hWnd;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if(msg.message == WM_KEYDOWN &&	msg.wParam == 13)	// 回车
			SendMessage(hWnd, WM_COMMAND, FUCKING_CN, 0);
		else if(msg.message == WM_KEYDOWN &&	msg.wParam == 27)	// Esc
			SendMessage(hWnd, WM_COMMAND, FUCKING_EX, 0);
		else if(msg.message == WM_SYSKEYDOWN &&	(msg.wParam == 'a' || msg.wParam== 'A' ) && GetKeyState(VK_MENU)<0 && GetKeyState(VK_CONTROL)>=0
			&& GetKeyState(VK_SHIFT)>=0)	// Alt+A
			SendMessage(hWnd, WM_COMMAND, FUCKING_AB, 0);
		else// if (!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	writeToReg();
	return (int) msg.wParam;
}


//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CYN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_CYN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中
	long wStyle=WS_OVERLAPPED;
	hWnd = CreateWindow(szWindowClass, szTitle, wStyle,
		left, top, mWidth, mHeight, NULL, NULL, hInstance, NULL);

	if (!hWnd)
		return (HWND)-1;

	SetWindowPos(hWnd, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	/////////////////////////////////////////////////////////////   DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
	return hWnd;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//

HWND EDITCN, EDIT1, EDIT2, EDIT3, EDIT4, THE_LIST;//_L, THE_LIST_R;
	DWORD lStyle;
	LOGBRUSH logbrush;
	HBRUSH hbrush;
	HFONT hFont;
	char * ln;
	NMITEMACTIVATE* nInfo;
	NMLISTVIEW* nLv;
	WNDINFO wInfo;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:

		wInfo.rev=true;
		ln=getLastName();
		//		THE_LIST_L

		THE_LIST
//			=CreateWindowEx(WS_EX_STATICEDGE, L"ListBox", L"未检测", WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_DISABLENOSCROLL|LBS_NOTIFY|LBS_MULTICOLUMN,
			=CreateWindowEx(WS_EX_STATICEDGE, L"SysListView32", L"THE_LIST",
				WS_VISIBLE|WS_VSCROLL|WS_CHILD | LVS_SHOWSELALWAYS|LVS_SINGLESEL |LVS_REPORT,
				//			margin/2, margin*3+100, 150, 320,
				margin/2, margin*3+100, 260, 315,
				hWnd, (HMENU)FUCKING_LL, NULL, NULL);

		lStyle = ListView_GetExtendedListViewStyle(THE_LIST);  
		lStyle |=  LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
		ListView_SetExtendedListViewStyle(THE_LIST, lStyle);
		LV_COLUMN column;
//		LV_ITEM lvItem; 
//		ZeroMemory(&lvItem, sizeof(LV_ITEM));
		ZeroMemory(&column, sizeof(LV_COLUMN));
		column.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_FMT|LVCF_SUBITEM;
		column.fmt = LVCFMT_CENTER;
		column.pszText = L"他的名字";
		column.cx = 160;

		ListView_InsertColumn(THE_LIST, 0, &column);

		column.pszText = L"他的等级";
		column.cx = 79;

		ListView_InsertColumn(THE_LIST, 1, &column);


/*		LVCOLUMN column[2]; 
		column[0].mask = LVCF_TEXT|LVCF_FMT|LVCF_WIDTH; 
		column[0].pszText = L"A"; 
		column[0].fmt = LVCFMT_CENTER; 
		column[0].cx = 80; 

		column[1].mask = LVCF_TEXT|LVCF_FMT|LVCF_WIDTH; 
		column[1].pszText = L"B"; 
		column[1].fmt = LVCFMT_CENTER; 
		column[1].cx = 80; 

		SendMessage(THE_LIST, LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column[0]);
		SendMessage(THE_LIST, LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column[1]);
///		
		wchar_t buff[16];
		int i;
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = ListView_GetItemCount(THE_LIST); //这一行表示要从当前已有列表增加item
		for(i=30; i>=1; i--)
		{
			_itow_s(i, buff, 16);
			swprintf_s(buff, L"item%d");
			lvItem.pszText = (LPTSTR)buff;
			if(i % 2 ==0)
			{
				lvItem.iSubItem = 0; 
				ListView_InsertItem(THE_LIST, &lvItem);
			} else {
				lvItem.iSubItem = 1; 
				ListView_SetItem(THE_LIST, &lvItem);
			}
		}

		/*		THE_LIST_R
		=CreateWindowEx(WS_EX_STATICEDGE, L"LISTBOX", L"未检测", WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_DISABLENOSCROLL|LBS_NOTIFY,
		margin/2+155, margin*3+100, 105, 320,
		hWnd, (HMENU)FUCKING_LR, NULL, NULL);
		*/
		hFont=(HFONT)SendMessage(THE_LIST, WM_GETFONT, 0, 0);

		EDITCN=CreateWindow(L"button", L"ESC=退出", WS_CHILD|WS_VISIBLE,
			mWidth-margin-75, mHeight-int(margin*1.5)-40, 80, 30,
			hWnd,(HMENU)FUCKING_EX, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindow(L"button", L"Alt+A=关于", WS_CHILD|WS_VISIBLE,
			mWidth-margin*2-235,mHeight-int(margin*1.5)-40, 80, 30,
			hWnd,(HMENU)FUCKING_AB, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindow(L"button", L"回车=改名", WS_CHILD|WS_VISIBLE,
			mWidth-int(margin*1.5)-155, mHeight-int(margin*1.5)-40, 80, 30,
			hWnd,(HMENU)FUCKING_CN, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindowEx(WS_EX_STATICEDGE, L"static", L"魔兽进程", LABSTYLE,
			margin/2, margin/2, 125, LABHEIGHT,
			hWnd, NULL, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDIT1=CreateWindowEx(WS_EX_STATICEDGE, L"static", L"未检测", LEDSTYLE,
			margin+125, margin/2, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDIT1,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindowEx(WS_EX_STATICEDGE, L"static", L"浩方进程",LABSTYLE,
			margin/2, margin+20, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDIT2=CreateWindowEx(WS_EX_STATICEDGE, L"static", L"未检测", LEDSTYLE,
			margin+125, margin+20, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDIT2,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindowEx(WS_EX_STATICEDGE, L"static", L"房间测试", LABSTYLE,
			margin/2, margin*3/2+40, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));
				
		EDIT3=CreateWindowEx(WS_EX_STATICEDGE, L"static", L"未检测", LEDSTYLE,
			margin+125, margin*3/2+40, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDIT3,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindowEx(WS_EX_STATICEDGE, L"static", L"上次储存", LABSTYLE,
			margin/2, margin*2+60, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindowExA(WS_EX_STATICEDGE, "EDIT", ln, LEDSTYLE|ES_READONLY,
			margin+125, margin*2+60, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindowEx(WS_EX_STATICEDGE, L"static", L"当前名字", LABSTYLE,
			margin/2, margin*5/2+80, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDIT4=CreateWindowEx(WS_EX_STATICEDGE, L"EDIT", L"未检测", LEDSTYLE|ES_READONLY,
			margin+125, margin*5/2+80, 125, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDIT4,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		EDITCN=CreateWindowExA(WS_EX_STATICEDGE,"EDIT", ln, ES_CENTER|WS_CHILD|WS_VISIBLE|ES_NOHIDESEL,
			margin/2, mHeight-int(margin*1.5)-64, mWidth-margin*4/3, LABHEIGHT,
			hWnd,NULL, NULL, NULL);
		SendMessage(EDITCN,WM_SETFONT,(WPARAM)hFont,MAKELONG(0,0));

		checkWindows(EDIT1, EDIT2, EDIT3, EDIT4, EDITCN, THE_LIST, false);//_L, THE_LIST_R, false);	// update界面

		SendMessage (EDITCN, EM_SETSEL, 0, -1);
		SendMessage (EDITCN, EM_LIMITTEXT, 15, 0);

		wInfo.hWnd=THE_LIST;
		wInfo.listCount=1;
		ListView_SortItemsEx(THE_LIST, ListViewCompareProc, &wInfo);

		SetFocus(EDITCN);
		break;
	case WM_SETFOCUS:
		SendMessage (EDITCN, EM_SETSEL, 0, -1);
		SendMessage (EDITCN, EM_LIMITTEXT, 15, 0);
		SetFocus(EDITCN);
		break;
	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLOREDIT:
		SetBkColor((HDC)wParam,bgc);
		logbrush.lbColor = bgc;
		hbrush = CreateBrushIndirect(&logbrush);
		return (long)hbrush;
		break;
	case WM_NOTIFY:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if(wmId==FUCKING_LL && ListView_GetItemCount(THE_LIST)>0 )
			switch( ((LPNMHDR) lParam)->code )
			{
			case NM_CLICK:
				//			M("LLED");
				nInfo = (LPNMITEMACTIVATE)lParam;
				wchar_t lpBuff[BFSZ];
				ListView_GetItemText(THE_LIST, nInfo->iItem, 0, lpBuff, BFSZ);
				SetWindowText(EDITCN, lpBuff);
				break;
			case NM_DBLCLK:
				nInfo = (LPNMITEMACTIVATE)lParam;
				ListView_GetItemText(THE_LIST, nInfo->iItem, 0, lpBuff, BFSZ);
				SetWindowText(EDITCN, lpBuff);
				SendMessage(hWnd, WM_COMMAND, FUCKING_CN, 0);
				SendMessage(hWnd, WM_COMMAND, FUCKING_EX, 0);
				break;
			case LVN_COLUMNCLICK:
				nLv=(NMLISTVIEW*)lParam;
				wInfo.hWnd=THE_LIST;
				wInfo.listCount=nLv->iSubItem;
				wInfo.rev=!wInfo.rev;
				ListView_SortItemsEx(THE_LIST, ListViewCompareProc, &wInfo);
				break;
			}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case FUCKING_CN:
			checkWindows(EDIT1, EDIT2, EDIT3, EDIT4, EDITCN, THE_LIST, true);//_L, THE_LIST_R, true);
			break;
		case FUCKING_AB:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case FUCKING_EX:
			DestroyWindow(hWnd);
			break;
/*		case FUCKING_LL:
			/*			if(wmEvent==LBN_SELCHANGE)
			{
			int index = SendMessage(THE_LIST_L, LB_GETCURSEL, 0, 0);
			SendMessage(THE_LIST_R, LB_SETCURSEL, index, 0);
			}
			else if (wmEvent==LBN_DBLCLK)
			{
				WCHAR bf[16];
				//				int index = SendMessage(THE_LIST_L, LB_GETCURSEL, 0, 0);
				int index = SendMessage(THE_LIST, LB_GETCURSEL, 0, 0);
				//				SendMessage(THE_LIST_L, LB_GETTEXT, index, (LPARAM)bf);
				SendMessage(THE_LIST, LB_GETTEXT, index, (LPARAM)bf);
				SetWindowText(EDITCN, bf);
			}
			break;
			/*		case FUCKING_LR:
			if(wmEvent==LBN_SELCHANGE)
			{
			int index = SendMessage(THE_LIST_R, LB_GETCURSEL, 0, 0);
			SendMessage(THE_LIST_L, LB_SETCURSEL, index, 0);
			}
			else if (wmEvent==LBN_DBLCLK)
			MessageBoxA(NULL, "RRRr", "DBed", 0);
			break;*/
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

#include "AboutDlg.h"

/*			if(flori==-147)
VirtualProtectEx(pHandle, (LPVOID)0x6a657af8, 1, PAGE_READONLY, &flori);
else
VirtualProtectEx(pHandle, (LPVOID)0x6a657af8, 1, PAGE_READONLY, &oldPfl);
*/