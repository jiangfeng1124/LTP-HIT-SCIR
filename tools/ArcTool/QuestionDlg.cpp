// QuestionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wdCheck.h"
#include "QuestionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuestionDlg dialog


CQuestionDlg::CQuestionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuestionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuestionDlg)
	m_question = _T("");
	//}}AFX_DATA_INIT
}


void CQuestionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuestionDlg)
	DDX_Text(pDX, IDC_QUESTION, m_question);
	DDV_MaxChars(pDX, m_question, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuestionDlg, CDialog)
	//{{AFX_MSG_MAP(CQuestionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuestionDlg message handlers
