/* 
 * FFplay for MFC 
 */

#include "stdafx.h"
#include "ffplaymfc.h"
#include "ffplaymfcDlg.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//CffplaymfcApp
BEGIN_MESSAGE_MAP(CffplaymfcApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CffplaymfcApp::CffplaymfcApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

//the only one 
CffplaymfcApp theApp;

BOOL CffplaymfcApp::InitInstance()
{
	// 如果一个运行在Windows XP上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	//多国语言设置
	//SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT));
	LoadLaguage();

	CffplaymfcDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		// “取消”来关闭对话框的代码
	}

	//删除上面创建的shell管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	//由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//而不是启动应用程序的消息泵。
	return FALSE;
}

void CffplaymfcApp::LoadLaguage()
{
	//配置文件路径
	char conf_path[300]={0};

	//获得exe绝对路径
	GetModuleFileNameA(NULL,(LPSTR)conf_path,300);//

	//获得exe文家夹路径
	strrchr( conf_path, '\\')[0]= '\0';//
	strcat(conf_path,"\\configure.ini");

	//存储属性的字符串
	char conf_val[300]={0};

	if((_access(conf_path, 0 )) == -1 )
	{  
		//配置文件不存在，直接返回
	}
	else
	{
		GetPrivateProfileStringA("Settings","language",NULL,conf_val,300,conf_path);
		if(strcmp(conf_val,"Chinese")==0)
		{
			SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_DEFAULT));
		}
		else if(strcmp(conf_val,"English")==0)
		{
			SetThreadUILanguage(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT));
		}

	}
	return;
}