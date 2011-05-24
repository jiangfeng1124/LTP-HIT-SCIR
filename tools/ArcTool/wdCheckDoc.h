// wdCheckDoc.h : interface of the CWdCheckDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WDCHECKDOC_H__63F5EB24_4C2A_4D2E_B3CF_18C2C5BBEBD7__INCLUDED_)
#define AFX_WDCHECKDOC_H__63F5EB24_4C2A_4D2E_B3CF_18C2C5BBEBD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWdCheckDoc : public CDocument
{
protected: // create from serialization only
	CWdCheckDoc();
	DECLARE_DYNCREATE(CWdCheckDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWdCheckDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWdCheckDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWdCheckDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WDCHECKDOC_H__63F5EB24_4C2A_4D2E_B3CF_18C2C5BBEBD7__INCLUDED_)
