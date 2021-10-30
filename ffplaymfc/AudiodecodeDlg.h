/* 
 * FFplay for MFC
 */
#pragma once


//AudiodecodeDlg¶Ô»°¿ò
class AudiodecodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AudiodecodeDlg)

public:
	AudiodecodeDlg(CWnd* pParent = NULL);   
	virtual ~AudiodecodeDlg();

	enum { IDD = IDD_AUDIODECODE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_audiodecodelist;

};
