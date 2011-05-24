// wdCheckDoc.cpp : implementation of the CWdCheckDoc class
//

#include "stdafx.h"
#include "wdCheck.h"

#include "wdCheckDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWdCheckDoc

IMPLEMENT_DYNCREATE(CWdCheckDoc, CDocument)

BEGIN_MESSAGE_MAP(CWdCheckDoc, CDocument)
	//{{AFX_MSG_MAP(CWdCheckDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWdCheckDoc construction/destruction

CWdCheckDoc::CWdCheckDoc()
{
	// TODO: add one-time construction code here

}

CWdCheckDoc::~CWdCheckDoc()
{
}

BOOL CWdCheckDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWdCheckDoc serialization

void CWdCheckDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWdCheckDoc diagnostics

#ifdef _DEBUG
void CWdCheckDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWdCheckDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWdCheckDoc commands
