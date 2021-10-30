/* 
 * FFplay for MFC 
 */
#include "stdafx.h"
#include "ffplaymfc.h"
#include "VideodecodeDlg.h"
#include "afxdialogex.h"

//#define SUPPORT_CONSOLE_PRT //调试信息到命令窗口
//项目-->属性-->生成事件-->后期生成事件  输入：editbin /SUBSYSTEM:CONSOLE $(OUTDIR)$(ProjectName).exe
#ifdef SUPPORT_CONSOLE_PRT
#define PRT printf("[codec2021]");printf
#endif

//VideodecodeDlg 视频解码分析对话框
IMPLEMENT_DYNAMIC(VideodecodeDlg, CDialogEx)

VideodecodeDlg::VideodecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(VideodecodeDlg::IDD, pParent)
{

}

VideodecodeDlg::~VideodecodeDlg()
{
}

void VideodecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEODECODE_LIST, m_videodecodelist);
}


BEGIN_MESSAGE_MAP(VideodecodeDlg, CDialogEx)
	ON_NOTIFY ( NM_CUSTOMDRAW,IDC_VIDEODECODE_LIST, VideodecodeDlg::OnCustomdrawMyList )
END_MESSAGE_MAP()


#ifdef SUPPORT_CONSOLE_PRT
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
void InitConsoleWindow()
{
	int nCrt = 0;
	FILE* fp;
	AllocConsole();
	nCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	fp = _fdopen(nCrt, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
}
#endif

//VideodecodeDlg消息处理程序
BOOL VideodecodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	//整行选择；有表格线；表头；单击激活
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE;
	//报表风格；单行选择；高亮显示选择行

	//多国语言支持
	CString resloader;
	resloader.LoadString(IDS_VIDEODECODE);
	SetWindowText(resloader);

	m_videodecodelist.ModifyStyle(0,LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
	m_videodecodelist.SetExtendedStyle(dwExStyle);
	resloader.LoadString(IDS_VIDEODECODE_NUM);

	m_videodecodelist.InsertColumn(0,resloader,LVCFMT_CENTER,60,0);
	
	//frame_type
	resloader.LoadString(IDS_VIDEODECODE_FRAMETYPE);
	m_videodecodelist.InsertColumn(1,resloader,LVCFMT_CENTER,60,0);
	
	//resloader.LoadString(IDS_VIDEODECODE_KEYFRAME);
	//m_videodecodelist.InsertColumn(2,resloader,LVCFMT_CENTER,30,0);
	//resloader.LoadString(IDS_VIDEODECODE_CODENUM);
	//m_videodecodelist.InsertColumn(3,resloader,LVCFMT_CENTER,30,0);

	resloader.LoadString(IDS_VIDEODECODE_PTS);
	m_videodecodelist.InsertColumn(2,resloader,LVCFMT_CENTER,70,0);

	//add by codec2021
	resloader.LoadString(IDS_VIDEODECODE_DTS);
	m_videodecodelist.InsertColumn(3, resloader, LVCFMT_CENTER, 70, 0);

	//add by codec2021 PKT SIZE 
	resloader.LoadString(IDS_VIDEODECODE_PKT_SIZE);
	m_videodecodelist.InsertColumn(4, resloader, LVCFMT_CENTER, 70, 0);

	//add by codec2021
	resloader.LoadString(IDS_VIDEODECODE_TIME);
	m_videodecodelist.InsertColumn(5, resloader, LVCFMT_CENTER, 110, 0);

	//add by codec2021 时间戳差值
	resloader.LoadString(IDS_VIDEODECODE_TIME_STAMP);
	m_videodecodelist.InsertColumn(6, resloader, LVCFMT_CENTER, 90, 0);

	//add by codec2021 帧率
	resloader.LoadString(IDS_VIDEODECODE_FPS);
	m_videodecodelist.InsertColumn(7, resloader, LVCFMT_CENTER, 50, 0);

	//add by codec2021 宽度
	resloader.LoadString(IDS_VIDEODECODE_WIDTH);
	m_videodecodelist.InsertColumn(8, resloader, LVCFMT_CENTER, 50, 0);

	//add by codec2021 宽度
	resloader.LoadString(IDS_VIDEODECODE_HEIGHT);
	m_videodecodelist.InsertColumn(9, resloader, LVCFMT_CENTER, 50, 0);

#if 0
	//add by codec2021 平均码率
	resloader.LoadString(IDS_VIDEODECODE_AVG_RATE);
	m_videodecodelist.InsertColumn(8, resloader, LVCFMT_CENTER, 90, 0);
#endif

#ifdef SUPPORT_CONSOLE_PRT
	//addd by codec2021
	InitConsoleWindow();
	PRT("#########################test\n");
#endif
	return TRUE;
}

//ListCtrl加颜色
void VideodecodeDlg::OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	//This code based on Michael Dunn's excellent article on
	//list control custom draw at http://www.codeproject.com/listctrl/lvcustomdraw.asp

	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

	// Take the default processing unless we set this to something else below.
	*pResult = CDRF_DODEFAULT;

	// First thing - check the draw stage. If it's the control's prepaint
	// stage, then tell Windows we want messages for every item.
	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		// This is the notification message for an item.  We'll request
		// notifications before each subitem's prepaint stage.

		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		COLORREF clrNewTextColor, clrNewBkColor;

		int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

		CString strTemp = m_videodecodelist.GetItemText(nItem,1);
		if(strTemp.Compare(_T("I"))==0)
		{
			clrNewTextColor = RGB(0,0,0);		//Set the text
			clrNewBkColor   = RGB(255,0,0);		//背景设置成红色
		}
		else if(strTemp.Compare(_T("P"))==0)
		{
			clrNewTextColor = RGB(0,0,0);		
			clrNewBkColor   = RGB(0,255,255);	//背景设置成青色
		}
		else if(strTemp.Compare(_T("B"))==0)
		{
			clrNewTextColor = RGB(0,0,0);		
			clrNewBkColor   = RGB(0,255,0);		//背景设置成绿色
		}
		else
		{
			clrNewTextColor = RGB(0,0,0);		
			clrNewBkColor   = RGB(255,255,255);
		}


#if 1   //如果两帧之间的时间戳差值大于150,add by codec2021
		CString strTemp1 = m_videodecodelist.GetItemText(nItem, 6);
		int time_diff = _ttoi(strTemp1);
		if(time_diff > 150)
		{
			clrNewTextColor = RGB(0, 0, 0);		//Set the text
			clrNewBkColor   = RGB(255, 0, 0);	//背景设置成红色
		}
#endif

		pLVCD->clrText   = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;

		//Tell Windows to paint the control itself.
		*pResult = CDRF_DODEFAULT;
	}
}