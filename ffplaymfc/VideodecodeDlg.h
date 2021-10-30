/* 
 * FFplay for MFC 
 */
#pragma once

//VideodecodeDlg¶Ô»°¿ò
class VideodecodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VideodecodeDlg)

public:
	VideodecodeDlg(CWnd* pParent = NULL);   
	virtual ~VideodecodeDlg();
	enum { IDD = IDD_VIDEODECODE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	
public:
	CListCtrl m_videodecodelist;
	void OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult );
};
