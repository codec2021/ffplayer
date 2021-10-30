/* 
 * FFplay for MFC
 */

#include "stdafx.h"
#include "ffplaymfc.h"
#include "AudiodecodeDlg.h"
#include "afxdialogex.h"


// AudiodecodeDlg对话框
IMPLEMENT_DYNAMIC(AudiodecodeDlg, CDialogEx)

AudiodecodeDlg::AudiodecodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(AudiodecodeDlg::IDD, pParent)
{

}

AudiodecodeDlg::~AudiodecodeDlg()
{
}

void AudiodecodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUDIODECODE_LIST, m_audiodecodelist);
}

BEGIN_MESSAGE_MAP(AudiodecodeDlg, CDialogEx)

END_MESSAGE_MAP()


BOOL AudiodecodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	//整行选择；有表格线；表头；单击激活
	DWORD dwExStyle=LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE;
	
	//多国语言支持
	CString resloader;
	resloader.LoadString(IDS_AUDIODECODE);
	SetWindowText(resloader);
	
	m_audiodecodelist.ModifyStyle(0,LVS_SINGLESEL|LVS_REPORT|LVS_SHOWSELALWAYS);
	m_audiodecodelist.SetExtendedStyle(dwExStyle);

	resloader.LoadString(IDS_AUDIODECODE_NUM);
	m_audiodecodelist.InsertColumn(0,resloader,LVCFMT_CENTER,50,0);

	resloader.LoadString(IDS_AUDIODECODE_SIZE);
	m_audiodecodelist.InsertColumn(1,resloader,LVCFMT_CENTER,50,0);
	
	
	resloader.LoadString(IDS_AUDIODECODE_PTS);
	m_audiodecodelist.InsertColumn(2,resloader,LVCFMT_CENTER,70,0);
	
	resloader.LoadString(IDS_AUDIODECODE_DTS);
	m_audiodecodelist.InsertColumn(3,resloader,LVCFMT_CENTER,70,0);

	//add by codec2021
	resloader.LoadString(IDS_AUDIODECODE_PKT_DURATION);
	m_audiodecodelist.InsertColumn(4,resloader,LVCFMT_CENTER,90,0);

	//add by codec2021
	resloader.LoadString(IDS_AUDIODECODE_TIME_STAMP);
	m_audiodecodelist.InsertColumn(5,resloader,LVCFMT_CENTER,90,0);

	//add by codec2021
	resloader.LoadString(IDS_AUDIODECODE_DIFF_TIME_STAMP);
	m_audiodecodelist.InsertColumn(6,resloader,LVCFMT_CENTER,90,0);

	return TRUE;
}
