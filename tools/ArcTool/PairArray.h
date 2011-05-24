// PairArray.h: interface for the CPairArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAIRARRAY_H__C4CB2D20_C5BC_45CF_B210_FD0C905E53F1__INCLUDED_)
#define AFX_PAIRARRAY_H__C4CB2D20_C5BC_45CF_B210_FD0C905E53F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Pair.h"
#include <afxtempl.h>
#include "WordArray.h"

class CPairArray  
{
private:
	CArray<CPair, CPair> myPairArray;
public:
	void ChangeMark(int i, bool bRelation);
	void ChangeRelation(int i, CString &strRelation);
	void ChangeRect(int i,CPair &mpair);
	CPairArray();
	CPairArray(CString strInput);
	virtual ~CPairArray();
	void DoPair(CPair& mpair);
	void DeletePair(CPair pair);
	void AddPair(CPair pair);
	void SetPairArray(CString strInput);
	void ReSetPairArray(CWordsArray& wordsarray);
	int GetSize();
	CPair GetPair(int i);
};

#endif // !defined(AFX_PAIRARRAY_H__C4CB2D20_C5BC_45CF_B210_FD0C905E53F1__INCLUDED_)
