/* 
 * FFplay for MFC 
 */

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h" //������



class CffplaymfcApp : public CWinApp
{
public:
	CffplaymfcApp();

	void LoadLaguage();

//��д
public:
	virtual BOOL InitInstance();

//ʵ��
	DECLARE_MESSAGE_MAP()
};

extern CffplaymfcApp theApp;