// Relation.h: interface for the CRelation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RELATION_H__0757BE4C_D207_4DF6_BE5B_EC1615ED0061__INCLUDED_)
#define AFX_RELATION_H__0757BE4C_D207_4DF6_BE5B_EC1615ED0061__INCLUDED_

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRelation  
{
public:
	CRelation();
	virtual ~CRelation();
	
	struct RELATION
	{
		CString strRule;
		CString strRelation;
		CString strLeftRelation,strRightRelation;
		vector < CString > candidate;
	};
	vector < RELATION > vecLeft,vecRight;
	vector < CString > allLeftRelation,allRightRelation;

private:
	void InitRelation();
};

#endif // !defined(AFX_RELATION_H__0757BE4C_D207_4DF6_BE5B_EC1615ED0061__INCLUDED_)
