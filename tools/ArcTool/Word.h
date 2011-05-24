// Word.h: interface for the CWord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORD_H__0A2F17E2_AAF7_4D2D_ABAA_F8EA178EBE32__INCLUDED_)
#define AFX_WORD_H__0A2F17E2_AAF7_4D2D_ABAA_F8EA178EBE32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWord  
{
public:
	int m_nPos;
	CString m_strWord;
	CString m_strAttr;
public:
	CWord();
	CWord(CString strInput);
	void SetWord(CString strInput);
	void SetWord(CString strInput, int nIndex);
	CString GetWord();
	virtual ~CWord();
};

#endif // !defined(AFX_WORD_H__0A2F17E2_AAF7_4D2D_ABAA_F8EA178EBE32__INCLUDED_)
