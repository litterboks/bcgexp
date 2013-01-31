//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// chicdial.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSDialog dialog

CCSDialog::CCSDialog(UINT nIDTemplate, CWnd* pParentWnd)
	: CDialog(nIDTemplate, pParentWnd)
{
}

CCSDialog::CCSDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
	: CDialog(lpszTemplateName, pParentWnd)
{
}

CCSDialog::CCSDialog() : CDialog()
{
}

BEGIN_MESSAGE_MAP(CCSDialog, CDialog)
	//{{AFX_MSG_MAP(CCSDialog)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HELP, OnHelp)
	ON_MESSAGE(WM_CONTEXTMENU, OnHelpContextMenu)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCSDialog message handlers

LRESULT CCSDialog::OnHelp(WPARAM, LPARAM lParam)
{
	::WinHelp( (HWND)((LPHELPINFO)lParam)->hItemHandle, AfxGetApp()->m_pszHelpFilePath,
		HELP_WM_HELP, (DWORD_PTR)(LPVOID)GetHelpIDs());
	return 0;
}

LRESULT CCSDialog::OnHelpContextMenu(WPARAM wParam, LPARAM)
{
	::WinHelp((HWND)wParam, AfxGetApp()->m_pszHelpFilePath,
		HELP_CONTEXTMENU, (DWORD_PTR)(LPVOID)GetHelpIDs());
	return 0;
}

BOOL CCSDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0, WS_EX_CONTEXTHELP);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CCSPropertyPage

CCSPropertyPage::CCSPropertyPage(UINT nIDTemplate, UINT nIDCaption)
	: CPropertyPage(nIDTemplate, nIDCaption)
{
}

CCSPropertyPage::CCSPropertyPage(LPCTSTR lpszTemplateName,
	UINT nIDCaption) : CPropertyPage(lpszTemplateName, nIDCaption)
{
}

BEGIN_MESSAGE_MAP(CCSPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCSPropertyPage)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HELP, OnHelp)
	ON_MESSAGE(WM_CONTEXTMENU, OnHelpContextMenu)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCSPropertyPage message handlers

LRESULT CCSPropertyPage::OnHelp(WPARAM, LPARAM lParam)
{
	::WinHelp( (HWND)((LPHELPINFO)lParam)->hItemHandle, AfxGetApp()->m_pszHelpFilePath,
		HELP_WM_HELP, (DWORD_PTR)(LPVOID)GetHelpIDs());
	return 0;
}

LRESULT CCSPropertyPage::OnHelpContextMenu(WPARAM wParam, LPARAM)
{
	::WinHelp((HWND)wParam, AfxGetApp()->m_pszHelpFilePath,
		HELP_CONTEXTMENU, (DWORD_PTR)(LPVOID)GetHelpIDs());
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CCSPropertySheet

BEGIN_MESSAGE_MAP(CCSPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CCSPropertySheet)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HELP, OnHelp)
	ON_MESSAGE(WM_CONTEXTMENU, OnHelpContextMenu)
END_MESSAGE_MAP()

CCSPropertySheet::CCSPropertySheet(UINT nIDCaption, CWnd *pParentWnd,
	UINT iSelectPage) : CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CCSPropertySheet::CCSPropertySheet(LPCTSTR pszCaption, CWnd *pParentWnd,
	UINT iSelectPage) : CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCSPropertySheet message handlers

LRESULT CCSPropertySheet::OnHelp(WPARAM wParam, LPARAM lParam)
{
	GetActivePage()->SendMessage(WM_HELP, wParam, lParam);
	return 0;
}

LRESULT CCSPropertySheet::OnHelpContextMenu(WPARAM wParam, LPARAM lParam)
{
	GetActivePage()->SendMessage(WM_CONTEXTMENU, wParam, lParam);
	return 0;
}

BOOL CCSPropertySheet::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle |= WS_EX_CONTEXTHELP;
	return CPropertySheet::PreCreateWindow(cs);
}
