/*
Copyright (c) 2016 Hailin Su
MIT LISENCE, see the file named 'LISENCE'
*/

#define I(m) InsertLog(txtEdit, m)
void InsertLog(HWND txtEdit, LPTSTR log)
{
	static bool isFirst=true;
	if(isFirst)
	{
		SetFocus(txtEdit);
		isFirst=false;
		SetWindowText(txtEdit, log);
	} else {
		SetFocus(txtEdit);
		SendMessage(txtEdit, EM_SETSEL, -2, -1);
		SendMessage(txtEdit, EM_REPLACESEL, false, (LPARAM)L"\r\n");
		SendMessage(txtEdit, EM_SETSEL, -2, -1);
		SendMessage(txtEdit, EM_REPLACESEL, false, (LPARAM)log);
	}
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND txtEdit=NULL;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hDlg, szTitle);
//		SetWindowPos(hDlg, HWND_TOP, left-mWidth,top-mHeight,0,0, SWP_NOSIZE);
		SetWindowPos(hDlg, HWND_TOP, left+30,top+30,0,0, SWP_NOSIZE);
		txtEdit=GetDlgItem(hDlg, IDC_EDITLOG);

		I(L"Compiled via");
		I(L"  Microsoft Visual C++ 2010 Express on Windows XP");
		I(L"");

		I(L"Project web site");
		I(L"  http://code.google.com/p/cyn/");
		I(L"");

		I(L"附：生成随机合法身份证号");
		I(L"  http://202.194.133.72/cbk/id.jsp");
		I(L"");

		I(L"问题和其他未实现功能");
		I(L"    “自定义改名”和“借壳上市”。");
		I(L"    “自定义改名”结果不显示等级和位置。");
		I(L"    “借壳上市”显示等级和位置但是不能自定义。");
		I(L"");

		I(L"v0.65 2011-02-07");
		I(L"    修正了SysListView32窗口的判断方法。");
		I(L"    可通过选择列表中的名字获得所有名字，并能排序。");
		I(L"    双击列表即可改名并退出。");
		I(L"");

		I(L"v0.64 * Milestone 2011-02-04");
		I(L"    针对浩方5.5.3.126升级了新的改名地址。");
		I(L"    “画皮”版，可通过选择列表中的名字获得负级名字。");
		I(L"    修正了创建窗口的加粗字体。");
		I(L"");

		I(L"v0.63 * Milestone");
		I(L"    针对浩方5.4.4.422升级了新的改名地址。");
		I(L"    “借壳上市”版，功能可行。");
		I(L"");

		I(L"v0.62");
		I(L"    无论原名多长，改名均可接受15个字节长度的字符串。");
		I(L"    针对浩方5.3.6.1126升级了新的改名地址。");
		I(L"");
		I(L"v0.61");
		I(L"    修改回基于窗口的程序。");
		I(L"    唾弃MFC，代码完全使用Win32 API编写，简洁，高效。");
		I(L"    通过VS2008 Express C++在Win7下编写/编译。");
		I(L"");
		I(L"v0.60");
		I(L"    使用控制台作为交互界面。");
		I(L"");

		I(L"v0.52");
		I(L"    判断进程名的时候不区分大小写。");
		I(L"");
		I(L"v0.51");
		I(L"    使用幽鬼之刃作为图标。");
		I(L"    窗口总在最前面。");
		I(L"    最小化到系统托盘。");
		I(L"");
		I(L"v0.50 * Milestone");
		I(L"    增加拖动主窗口任意非控件区移动的机制。");
		I(L"    侦测是否已经进入房间。");
		I(L"    确认改名系统的加入。");
		I(L"    重写地址定位过程，不用读很大的内存区块进行搜索，更实现\"秒改\"。");
		I(L"    退出前写入注册表减少操作次数。");
		I(L"");

		I(L"v0.41");
		I(L"    允许二次改名。");
		I(L"    暂时取消浩方昵称的修改以防出错。");
		I(L"");
		I(L"v0.4");
		I(L"    加入互斥体，只允许运行一个程序。");
		I(L"    加入注册表读写功能，记录上一个名字。");
		I(L"    加入是否已经改名的判断，多次改名是无效的。");
		I(L"    界面稍做修改，为以后多次改名做准备。");
		I(L"");

		I(L"v0.3 * Milestone");
		I(L"    实现秒改，只写3处内存，搜索也变成了字符串搜索，提高速度。");
		I(L"    关闭/换房间不会造成浩方程序出错。");
		I(L"");

		I(L"v0.2");
		I(L"    修改部分内存读写方法提高速度。");
		I(L"    昵称库，随机获得昵称，从总共64个随机抽1个用。");
		I(L"");

		return (INT_PTR)TRUE;
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

/* wiki
=Change Your Name=

----

*Compiled via*
  Microsoft Visual C++ 2010 Express on Windows XP

*Project web site*
  http://code.google.com/p/cyn/

*问题和其他未实现功能*
  * “自定义改名”和“借壳上市”。
  * “自定义改名”结果不显示等级和位置。
  * “借壳上市”显示等级和位置但是不能自定义。

*v0.64 `*` Milestone 2011-02-04*
  * 针对浩方5.5.3.126升级了新的改名地址。
  * “画皮”版，可通过选择列表中的名字获得负级名字。
  * 修正了创建窗口的加粗字体。

*v0.63 `*` Milestone*
  * 针对浩方5.4.4.422升级了新的改名地址。
  * “借壳上市”版，功能可行。

*v0.62*
  * 无论原名多长，改名均可接受15个字节长度的字符串。
  * 针对浩方5.3.6.1126升级了新的改名地址。

*v0.61*
  * 修改回基于窗口的程序。
  * 唾弃MFC，代码完全使用Win32 API编写，简洁，高效。
  * 通过VS2008 Express C++在Win7下编写/编译。

*v0.60*
  * 使用控制台作为交互界面。

*v0.52*
  * 判断进程名的时候不区分大小写。

*v0.51*
  * 使用幽鬼之刃作为图标。
  * 窗口总在最前面。
  * 最小化到系统托盘。

*v0.50 `*` Milestone*
  * 增加拖动主窗口任意非控件区移动的机制。
  * 侦测是否已经进入房间。
  * 确认改名系统的加入。
  * 重写地址定位过程，不用读很大的内存区块进行搜索，更实现"秒改"。
  * 退出前写入注册表减少操作次数。

*v0.41*
  * 允许二次改名。
  * 暂时取消浩方昵称的修改以防出错。

*v0.4*
  * 加入互斥体，只允许运行一个程序。
  * 加入注册表读写功能，记录上一个名字。
  * 加入是否已经改名的判断，多次改名是无效的。
  * 界面稍做修改，为以后多次改名做准备。

*v0.3 `*` Milestone*
  * 实现秒改，只写3处内存，搜索也变成了字符串搜索，提高速度。
  * 关闭/换房间不会造成浩方程序出错。

*v0.2*
  * 修改部分内存读写方法提高速度。
  * 昵称库，随机获得昵称，从总共64个随机抽1个用。

*/
