// Relation.cpp: implementation of the CRelation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wdCheck.h"
#include "Relation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CRelation::CRelation()
{
	InitRelation();
}

CRelation::~CRelation()
{

}

//初始化可能的依存关系
void CRelation::InitRelation()
{
	CString strline,strUnit,strRel,strDirect;
	string strTemp;
	int pos;

	ifstream fin1("TagRelation.txt");
	ifstream fin2("AllLeftRelation.txt");
	ifstream fin3("AllRightRelation.txt");
	if(!fin1 || !fin2 || !fin3)
	{
		AfxMessageBox("Cannot open relation file!");
	}


	//到词性关系规则文件中查找
	while(getline(fin1,strTemp))
	{
		RELATION relation;
		strline = strTemp.c_str();
		
		pos = strline.ReverseFind(' ');
		strDirect = strline.Mid(pos-1,1);
		strUnit = strline.Mid(0,pos-2);
		relation.strRule = strUnit;
		
		strline = strline.Right(strline.GetLength()-pos-1);
		pos = strline.Find('\t');
		strRel = strline.Mid(0,pos);
		relation.strRelation = strRel;

		strline = strline.Right(strline.GetLength()-pos-1);
		pos = strline.Find('\t');
		while(pos != -1)
		{
			strRel = strline.Mid(0,pos);
			strline = strline.Right(strline.GetLength()-pos-1);
			relation.candidate.push_back(strRel);
			pos = strline.Find('\t');
		}

		if(strDirect == "0")//弧的方向向左
			vecLeft.push_back(relation);
		else			//弧的方向向右
			vecRight.push_back(relation);
	}

	//全部的左向依存关系
	allLeftRelation.clear();
	while(getline(fin2,strTemp))
	{
		strline = strTemp.c_str();
		allLeftRelation.push_back(strline);
	}
	//全部的右向依存关系
	allRightRelation.clear();
	while(getline(fin3,strTemp))
	{
		strline = strTemp.c_str();
		allRightRelation.push_back(strline);
	}

	fin1.close();
	fin2.close();
	fin3.close();
}
