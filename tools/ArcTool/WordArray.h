// WordArray.h: interface for the CWordsArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORDARRAY_H__103B5411_6ECB_450C_B1AA_F392E2990E32__INCLUDED_)
#define AFX_WORDARRAY_H__103B5411_6ECB_450C_B1AA_F392E2990E32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Word.h"
#include <afxtempl.h>
class CWordsArray
{
public:
	CArray<CWord, CWord> m_Words;
public:
	CWordsArray();
	CWordsArray(CString strInput);
	void SetWordArray(CString strInput);
	void ReSetWordArray(CString strInput);
	virtual ~CWordsArray();
	int GetSize();
	CString GetAttr(int nPos);
	bool InWords(CString strWord);
	CWord GetWord(int i);
	CWord GetWord(CString strWord);
};

#endif // !defined(AFX_WORDARRAY_H__103B5411_6ECB_450C_B1AA_F392E2990E32__INCLUDED_)
