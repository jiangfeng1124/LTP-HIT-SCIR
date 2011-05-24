// goDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wdCheck.h"
#include "goDialog.h"
#include "wdCheckView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CgoDialog dialog


CgoDialog::CgoDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CgoDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CgoDialog)
	m_numsen = 0;
	//}}AFX_DATA_INIT
}


void CgoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CgoDialog)
	DDX_Text(pDX, IDC_UNMSENTENCE, m_numsen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CgoDialog, CDialog)
	//{{AFX_MSG_MAP(CgoDialog)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CgoDialog message handlers

