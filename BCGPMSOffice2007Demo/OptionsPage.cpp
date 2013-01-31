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
// OptionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "bcgpmsoffice2007demo.h"
#include "OptionsPage.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COptionsPropSheet::COptionsPropSheet (CWnd* pWndParent, UINT nSelectedPage) :
		CBCGPPropertySheet (_T("Options"), pWndParent, nSelectedPage)
{
	m_Icons.SetImageSize (CSize (32, 32));
	m_Icons.Load (IDB_OPTIONS);

	CBCGPControlRendererParams params((UINT)0, CLR_DEFAULT, 
		CRect (0, 0, 350, 60), CRect (83, 58, 266, 1), 
		CRect (0, 0, 0, 0), CRect (0, 0, 0, 0), FALSE);

	params.m_uiBmpResID = IDB_HEADERPAT_1;
	m_Pat[0].Create (params);
	params.m_uiBmpResID = IDB_HEADERPAT_2;
	m_Pat[1].Create (params);
	params.m_uiBmpResID = IDB_HEADERPAT_3;
	m_Pat[2].Create (params);
	params.m_uiBmpResID = IDB_HEADERPAT_4;
	m_Pat[3].Create (params);
}

BOOL COptionsPropSheet::OnInitDialog() 
{
	if (theApp.m_bIsRTL)
	{
		ModifyStyleEx (0, WS_EX_LAYOUTRTL);
	}

	return CBCGPPropertySheet::OnInitDialog();
}

void COptionsPropSheet::OnDrawPageHeader (CDC* pDC, int nPage, CRect rectHeader)
{
	CSize sizeIcon = m_Icons.GetImageSize ();

	CBCGPDrawManager dm (*pDC);

	COLORREF clrFill = globalData.clrBarFace;

	CBCGPControlRenderer* pRenderer = NULL;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2007_1:
		pRenderer = &m_Pat[1];
		break;
	case ID_VIEW_APPLOOK_2007_2:
		pRenderer = &m_Pat[2];
		break;
	case ID_VIEW_APPLOOK_2007_3:
		pRenderer = &m_Pat[0];
		break;
	case ID_VIEW_APPLOOK_2007_4:
		pRenderer = &m_Pat[3];
		break;
	}

	if (pRenderer != NULL)
	{
		pRenderer->Draw (pDC, rectHeader);
	}
	else
	{
		dm.FillGradient (rectHeader, 
			pDC->GetPixel (rectHeader.left, rectHeader.bottom),
			clrFill);
	}

	rectHeader.bottom -= 10;

	CRect rectIcon = rectHeader;
	
	rectIcon.left += 20;
	rectIcon.right = rectIcon.left + sizeIcon.cx;

	m_Icons.DrawEx (pDC, rectIcon, nPage, 
		CBCGPToolBarImages::ImageAlignHorzLeft, CBCGPToolBarImages::ImageAlignVertCenter);

	CString strText;

	switch (nPage)
	{
	case 0:
		strText = _T("Change the most popular options");
		break;

	case 1:
		strText = _T("Customize the Quick Access Toolbar and keyboard shortcuts");
		break;

	case 2:
		strText = _T("Contact BCGSoft, find online resources and obtain additional information regarding our products and services");
		break;
	}

	CRect rectText = rectHeader;
	rectText.left = rectIcon.right + 10;
	rectText.right -= 20;

	CFont* pOldFont = pDC->SelectObject (&globalData.fontBold);
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (globalData.clrBarText);

	UINT uiFlags = DT_SINGLELINE | DT_VCENTER;

	CRect rectTextCalc = rectText;
	pDC->DrawText (strText, rectTextCalc, uiFlags | DT_CALCRECT);

	if (rectTextCalc.right > rectText.right)
	{
		rectText.DeflateRect (0, 10);
		uiFlags = DT_WORDBREAK;
	}

	pDC->DrawText (strText, rectText, uiFlags);

	pDC->SelectObject (pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// COptionsPage property page

IMPLEMENT_DYNCREATE(COptionsPage, CBCGPPropertyPage)

COptionsPage::COptionsPage() : CBCGPPropertyPage(COptionsPage::IDD),
	m_wndColor (TRUE)
{
	//{{AFX_DATA_INIT(COptionsPage)
	m_nColorScheme = theApp.m_nAppLook - ID_VIEW_APPLOOK_2007_1;
	m_nTooltipStyle = -1;
	m_bShowDevTab = theApp.m_bShowDevTab;
	m_bShowFloaty = theApp.m_bShowFloaty;
	m_bShowKeyTips = theApp.m_bShowKeyTips;
	//}}AFX_DATA_INIT

	if (!theApp.m_bShowToolTips)
	{
		m_nTooltipStyle = 2;
	}
	else
	{
		m_nTooltipStyle = theApp.m_bShowToolTipDescr ? 0 : 1;
	}
}

COptionsPage::~COptionsPage()
{
}

void COptionsPage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsPage)
	DDX_Control(pDX, IDC_CUSTOM_COLOR, m_wndColor);
	DDX_Control(pDX, IDC_BANER, m_wndBanner);
	DDX_Control(pDX, IDC_COLOR_SCHEME, m_wndColorScheme);
	DDX_CBIndex(pDX, IDC_COLOR_SCHEME, m_nColorScheme);
	DDX_CBIndex(pDX, IDC_SCREENTIP_STYLE, m_nTooltipStyle);
	DDX_Check(pDX, IDC_SHOW_DEV_TAB, m_bShowDevTab);
	DDX_Check(pDX, IDC_SHOW_FLOATY, m_bShowFloaty);
	DDX_Check(pDX, IDC_SHOW_KEY_TIPS, m_bShowKeyTips);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsPage, CBCGPPropertyPage)
	//{{AFX_MSG_MAP(COptionsPage)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COLOR_SCHEME, OnSelchangeColorScheme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsPage message handlers

void COptionsPage::OnOK() 
{
	UpdateData ();

	theApp.m_bShowFloaty = m_bShowFloaty;
	theApp.m_nAppLook = m_nColorScheme + ID_VIEW_APPLOOK_2007_1;

	if (m_nColorScheme == 4)
	{
		theApp.m_clrCustom = m_wndColor.GetColor ();
	}

	theApp.m_bShowDevTab = m_bShowDevTab;
	theApp.m_bShowKeyTips = m_bShowKeyTips;

	switch (m_nTooltipStyle)
	{
	case 0:
		theApp.m_bShowToolTips = TRUE;
		theApp.m_bShowToolTipDescr = TRUE;
		break;

	case 1:
		theApp.m_bShowToolTips = TRUE;
		theApp.m_bShowToolTipDescr = FALSE;
		break;

	case 2:
		theApp.m_bShowToolTips = FALSE;
		theApp.m_bShowToolTipDescr = FALSE;
		break;
	}
	
	CBCGPPropertyPage::OnOK();
}

BOOL COptionsPage::OnInitDialog() 
{
	CBCGPPropertyPage::OnInitDialog();

	if (((CMainFrame*) GetTopLevelFrame ())->IsPrintPreview ())
	{
		GetDlgItem (IDC_SHOW_DEV_TAB)->EnableWindow (FALSE);
	}

	OnSelchangeColorScheme ();
	
	m_wndColor.SetColor (theApp.m_clrCustom);
	m_wndColor.EnableAutomaticButton (_T("&Automatic"), theApp.m_clrCustomDef, TRUE);

	m_wndColor.GetRibbonButton ().SetColumns (10);
	m_wndColor.GetRibbonButton ().SetColorBoxSize (CSize (17, 17));
	m_wndColor.GetRibbonButton ().EnableAutomaticButton (_T("&Automatic"), theApp.m_clrCustomDef, TRUE, _T("Automatic"));
	m_wndColor.GetRibbonButton ().EnableOtherButton (_T("&More Colors..."), _T("More Colors"));
	m_wndColor.GetRibbonButton ().AddColorsGroup (_T("Presets"), theApp.m_lstCustomColors);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsPage::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPPropertyPage::OnSize(nType, cx, cy);
	
	if (m_wndBanner.GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectBanner;
	m_wndBanner.GetWindowRect (rectBanner);

	CRect rectParent;
	GetParent ()->GetWindowRect (rectParent);

	m_wndBanner.SetWindowPos (NULL, -1, -1, 
		rectParent.right - rectBanner.left - 10, rectBanner.Height (),
		SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COptionsPage::OnSelchangeColorScheme() 
{
	UpdateData ();
	m_wndColor.EnableWindow (m_nColorScheme == 4);
}
