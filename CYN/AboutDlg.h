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

// �����ڡ������Ϣ�������
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

		I(L"������������Ϸ����֤��");
		I(L"  http://202.194.133.72/cbk/id.jsp");
		I(L"");

		I(L"���������δʵ�ֹ���");
		I(L"    ���Զ���������͡�������С���");
		I(L"    ���Զ���������������ʾ�ȼ���λ�á�");
		I(L"    ��������С���ʾ�ȼ���λ�õ��ǲ����Զ��塣");
		I(L"");

		I(L"v0.65 2011-02-07");
		I(L"    ������SysListView32���ڵ��жϷ�����");
		I(L"    ��ͨ��ѡ���б��е����ֻ���������֣���������");
		I(L"    ˫���б��ɸ������˳���");
		I(L"");

		I(L"v0.64 * Milestone 2011-02-04");
		I(L"    ��ԺƷ�5.5.3.126�������µĸ�����ַ��");
		I(L"    ����Ƥ���棬��ͨ��ѡ���б��е����ֻ�ø������֡�");
		I(L"    �����˴������ڵļӴ����塣");
		I(L"");

		I(L"v0.63 * Milestone");
		I(L"    ��ԺƷ�5.4.4.422�������µĸ�����ַ��");
		I(L"    ��������С��棬���ܿ��С�");
		I(L"");

		I(L"v0.62");
		I(L"    ����ԭ���೤���������ɽ���15���ֽڳ��ȵ��ַ�����");
		I(L"    ��ԺƷ�5.3.6.1126�������µĸ�����ַ��");
		I(L"");
		I(L"v0.61");
		I(L"    �޸Ļػ��ڴ��ڵĳ���");
		I(L"    ����MFC��������ȫʹ��Win32 API��д����࣬��Ч��");
		I(L"    ͨ��VS2008 Express C++��Win7�±�д/���롣");
		I(L"");
		I(L"v0.60");
		I(L"    ʹ�ÿ���̨��Ϊ�������档");
		I(L"");

		I(L"v0.52");
		I(L"    �жϽ�������ʱ�����ִ�Сд��");
		I(L"");
		I(L"v0.51");
		I(L"    ʹ���Ĺ�֮����Ϊͼ�ꡣ");
		I(L"    ����������ǰ�档");
		I(L"    ��С����ϵͳ���̡�");
		I(L"");
		I(L"v0.50 * Milestone");
		I(L"    �����϶�����������ǿؼ����ƶ��Ļ��ơ�");
		I(L"    ����Ƿ��Ѿ����뷿�䡣");
		I(L"    ȷ�ϸ���ϵͳ�ļ��롣");
		I(L"    ��д��ַ��λ���̣����ö��ܴ���ڴ����������������ʵ��\"���\"��");
		I(L"    �˳�ǰд��ע�����ٲ���������");
		I(L"");

		I(L"v0.41");
		I(L"    ������θ�����");
		I(L"    ��ʱȡ���Ʒ��ǳƵ��޸��Է�����");
		I(L"");
		I(L"v0.4");
		I(L"    ���뻥���壬ֻ��������һ������");
		I(L"    ����ע����д���ܣ���¼��һ�����֡�");
		I(L"    �����Ƿ��Ѿ��������жϣ���θ�������Ч�ġ�");
		I(L"    ���������޸ģ�Ϊ�Ժ��θ�����׼����");
		I(L"");

		I(L"v0.3 * Milestone");
		I(L"    ʵ����ģ�ֻд3���ڴ棬����Ҳ������ַ�������������ٶȡ�");
		I(L"    �ر�/�����䲻����ɺƷ��������");
		I(L"");

		I(L"v0.2");
		I(L"    �޸Ĳ����ڴ��д��������ٶȡ�");
		I(L"    �ǳƿ⣬�������ǳƣ����ܹ�64�������1���á�");
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

*���������δʵ�ֹ���*
  * ���Զ���������͡�������С���
  * ���Զ���������������ʾ�ȼ���λ�á�
  * ��������С���ʾ�ȼ���λ�õ��ǲ����Զ��塣

*v0.64 `*` Milestone 2011-02-04*
  * ��ԺƷ�5.5.3.126�������µĸ�����ַ��
  * ����Ƥ���棬��ͨ��ѡ���б��е����ֻ�ø������֡�
  * �����˴������ڵļӴ����塣

*v0.63 `*` Milestone*
  * ��ԺƷ�5.4.4.422�������µĸ�����ַ��
  * ��������С��棬���ܿ��С�

*v0.62*
  * ����ԭ���೤���������ɽ���15���ֽڳ��ȵ��ַ�����
  * ��ԺƷ�5.3.6.1126�������µĸ�����ַ��

*v0.61*
  * �޸Ļػ��ڴ��ڵĳ���
  * ����MFC��������ȫʹ��Win32 API��д����࣬��Ч��
  * ͨ��VS2008 Express C++��Win7�±�д/���롣

*v0.60*
  * ʹ�ÿ���̨��Ϊ�������档

*v0.52*
  * �жϽ�������ʱ�����ִ�Сд��

*v0.51*
  * ʹ���Ĺ�֮����Ϊͼ�ꡣ
  * ����������ǰ�档
  * ��С����ϵͳ���̡�

*v0.50 `*` Milestone*
  * �����϶�����������ǿؼ����ƶ��Ļ��ơ�
  * ����Ƿ��Ѿ����뷿�䡣
  * ȷ�ϸ���ϵͳ�ļ��롣
  * ��д��ַ��λ���̣����ö��ܴ���ڴ����������������ʵ��"���"��
  * �˳�ǰд��ע�����ٲ���������

*v0.41*
  * ������θ�����
  * ��ʱȡ���Ʒ��ǳƵ��޸��Է�����

*v0.4*
  * ���뻥���壬ֻ��������һ������
  * ����ע����д���ܣ���¼��һ�����֡�
  * �����Ƿ��Ѿ��������жϣ���θ�������Ч�ġ�
  * ���������޸ģ�Ϊ�Ժ��θ�����׼����

*v0.3 `*` Milestone*
  * ʵ����ģ�ֻд3���ڴ棬����Ҳ������ַ�������������ٶȡ�
  * �ر�/�����䲻����ɺƷ��������

*v0.2*
  * �޸Ĳ����ڴ��д��������ٶȡ�
  * �ǳƿ⣬�������ǳƣ����ܹ�64�������1���á�

*/
