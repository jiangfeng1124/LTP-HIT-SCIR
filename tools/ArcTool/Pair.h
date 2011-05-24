// Pair.h: interface for the CPair class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAIR_H__C73B9CFF_671D_4E18_9F9A_11B8EA20EE42__INCLUDED_)
#define AFX_PAIR_H__C73B9CFF_671D_4E18_9F9A_11B8EA20EE42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Relation.h"

//int g_nHead;

class CPair  
{
public:
	int m_nNumLeft;
	CString m_strWordLeft;

	int m_nNumRight;
	CString m_strWordRight;

	CString m_strTagLeft;
	CString m_strTagRight;
	CString m_strTagRule;
	CString m_strWordRule;
	CString m_strRelation;
	
	CRect rect;
	bool bRelation;//标记关系是否被鼠标点中
	vector < CString > candidate;

	bool bHead;
	bool bPuntuation;
//	struct RELATION
//	{
//		string lefttag,righttag,direction,relation;
		CString strUnit,relation;
		vector < CString > other;
//	};
//	vector< RELATION > vecTagRelation,vecWordRelation;
	vector < CString > allLeftRelation;//全部的左向依存关系
	vector < CString > allRightRelation;//全部的右向依存关系
	
//	CRelation m_relation;
//	ofstream *resultfile;

public:
	void SetCandidateRelation();
	void SetInitRelation();
	void SaveRelationToFile();
	void GetCandidate();
	void SaveRelation();
	void InitRelation();
	bool Verify();
	void FindPunctuation();
	void CopyRect(CRect rect);
	CPair();
	CPair(CString strInput);
	virtual ~CPair();
	
//	int FindRelation(int m_nNumLeft,int m_nNumRight,bool &bTag);
//	void SetRelation();
	void SetPair(CString strInput);
	void SetLeft(int nNum, CString strWord,CString strTag);
	void SetRight(int nNum, CString strWord,CString strTag);
	void Reverse();
	bool IsPair(int nNumLeft, int nNumRight);
	bool IsPair(CPair pair);
	bool IsReverse(int nNumLeft, int nMunRight);
	bool IsReverse(CPair pair);
	int GetLeftNum();
	int GetRightNum();
	CString FindTag(CString strTemp);
	CString ModifyTag(CString strTag);
};

#endif // !defined(AFX_PAIR_H__C73B9CFF_671D_4E18_9F9A_11B8EA20EE42__INCLUDED_)
