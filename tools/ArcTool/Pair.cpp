 // Pair.cpp: implementation of the CPair class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Pair.h"
#include "MainFrm.h"
#include "wdCheckView.h"
#include "ArcView.h"
#include <algorithm>
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int g_nHead = 0;

CPair::CPair()
{
	m_nNumLeft = -1;
	m_nNumRight = -1;
	bRelation = 0;

//	resultfile=new ofstream("TagRelation_debug.txt");
}

CPair::~CPair()
{

}

CPair::CPair(CString strInput)
{
	//[1]在_[5]中_58413
	int nBegin, nEnd;
	CString strTemp;
	char* pTemp;
	
	nBegin = strInput.Find("[");
	nEnd = strInput.Find("]");
	strTemp = strInput.Mid(nBegin + 1, nEnd - nBegin -1);
	pTemp = strTemp.GetBuffer(strTemp.GetLength());
	m_nNumLeft = ::atoi(pTemp);

	nBegin = nEnd;
	nEnd = strInput.Find("_", nBegin);
	m_strWordLeft = strInput.Mid(nBegin + 1, nEnd - nBegin - 1);
	
	nBegin = strInput.Find("[", nEnd);
	nEnd = strInput.Find("]", nBegin);
	strTemp = strInput.Mid(nBegin + 1, nEnd - nBegin -1 );
	pTemp = strTemp.GetBuffer(strTemp.GetLength());
	m_nNumRight = ::atoi(pTemp);

	nBegin = nEnd;
	nEnd = strInput.Find("_", nBegin);
	if(nEnd != -1){
		m_strWordRight = strInput.Mid(nBegin + 1, nEnd - nBegin -1);
	}else{
		m_strWordRight = strInput.Mid(nBegin + 1);
	}
}

//将依存对与依存关系读入结构中
void CPair::SetPair(CString strInput)
{
	//[1]在_[5]中(POB)
	int nBegin, nEnd;
	CString strTemp;
	char* pTemp;
	
	nBegin = strInput.Find("[");
	nEnd = strInput.Find("]");
	strTemp = strInput.Mid(nBegin + 1, nEnd - nBegin -1);
	pTemp = strTemp.GetBuffer(strTemp.GetLength());
	m_nNumLeft = ::atoi(pTemp);
	m_strTagLeft = FindTag(strTemp);//到句子中找到该词的词性

	nBegin = nEnd;
	nEnd = strInput.Find("_", nBegin);
	m_strWordLeft = strInput.Mid(nBegin + 1, nEnd - nBegin -1);
	
	nBegin = strInput.Find("[", nEnd);
	nEnd = strInput.Find("]", nBegin);
	strTemp = strInput.Mid(nBegin + 1, nEnd - nBegin -1);
	pTemp = strTemp.GetBuffer(strTemp.GetLength());
	m_nNumRight = ::atoi(pTemp);
	m_strTagRight = FindTag(strTemp);//到句子中找到该词的词性

	nBegin = nEnd;
	nEnd = strInput.Find("(", nBegin);
	if(nEnd != -1)
	{
		m_strWordRight = strInput.Mid(nBegin + 1, nEnd - nBegin -1);
		m_strRelation = strInput.Mid(nEnd+1,strInput.GetLength()-nEnd-2);//关系类型
		SetCandidateRelation();
	}
	else//没有关系类型
	{
		m_strWordRight = strInput.Mid(nBegin + 1);
		SetInitRelation();
		SetCandidateRelation();
	}
}

bool CPair::IsPair(int nNumLeft, int nNumRight)
{
	if(m_nNumLeft == nNumLeft && m_nNumRight == nNumRight)
		return TRUE;
	else
		return FALSE;
}

bool CPair::IsReverse(int nNumLeft, int nNumRight)
{
	if(m_nNumLeft == nNumRight && m_nNumRight == nNumLeft)
		return TRUE;
	else
		return FALSE;
}

int CPair::GetLeftNum()
{
	return m_nNumLeft;
}

int CPair::GetRightNum()
{
	return m_nNumRight;
}

bool CPair::IsPair(CPair pair)
{
	if(m_nNumLeft == pair.GetLeftNum() && m_nNumRight == pair.GetRightNum())
		return TRUE;
	else
		return FALSE;
}

bool CPair::IsReverse(CPair pair)
{
	if(m_nNumRight == pair.GetLeftNum() && m_nNumLeft == pair.GetRightNum())
		return TRUE;
	else
		return FALSE;
}

void CPair::Reverse()
{
	int nTemp;
	CString strTemp;

	nTemp = m_nNumLeft;
	m_nNumLeft = m_nNumRight;
	m_nNumRight = nTemp;

	strTemp = m_strWordLeft;
	m_strWordLeft = m_strWordRight;
	m_strWordRight = strTemp;

	strTemp = m_strTagLeft;
	m_strTagLeft = m_strTagRight;
	m_strTagRight = strTemp;
}

void CPair::SetLeft(int nNum, CString strWord,CString strTag)
{
	m_nNumLeft = nNum;
	m_strWordLeft = strWord;
	m_strTagLeft = strTag;
}

void CPair::SetRight(int nNum, CString strWord,CString strTag)
{
	m_nNumRight = nNum;
	m_strWordRight = strWord;
	m_strTagRight = strTag;
}

//找出该词的词性
CString CPair::FindTag(CString strNum)
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString strSent = pMainFrame->m_DoingBlock[pMainFrame->m_nCurrentRow].m_strSentence;
	strNum = "[" + strNum + "]";
	int pos1,pos2;
	pos1 = strSent.Find(strNum);
	pos1 = strSent.Find("/",pos1);
	pos2 = strSent.Find(" ",pos1);
	CString strTag = strSent.Mid(pos1+1,pos2-pos1-1);

	strTag = ModifyTag(strTag);
	return strTag;
}

//两个词之间是否有标点间隔
void CPair::FindPunctuation()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString strSent = pMainFrame->m_DoingBlock[pMainFrame->m_nCurrentRow].m_strSentence;

	int pos1,pos2;
	CString strNum;

	strNum.Format("%d",m_nNumLeft);
	strNum = "[" + strNum + "]";
	pos1 = strSent.Find(strNum);
	strNum.Format("%d",m_nNumRight);
	strNum = "[" + strNum + "]";
	pos2 = strSent.Find(strNum);

	if(pos1 > pos2)//交换
	{
		int nTemp = pos1;
		pos1 = pos2;
		pos2 = nTemp;
	}
	strSent = strSent.Mid(pos1,pos2-pos1);//两个词之间的部分
	if(strSent.Find("/w") != -1)
		bPuntuation = 1;
	else
		bPuntuation = 0;
}

//验证依存弧是否合法
bool CPair::Verify()
{
	if(m_nNumRight == g_nHead)
	{
		AfxMessageBox(m_strWordRight+"是核心词！");
		return 0;
	}

	if(m_strTagRight == "<EOS>")
	{
		AfxMessageBox("方向标反了！");
		return 0;
	}
	
	if(m_strTagLeft == "wp" || m_strTagRight == "wp")	// || m_strTagRight == "ws" || m_strTagLeft == "ws"
	{
		AfxMessageBox("标点！");
		return 0;
	}

	//是否是核心词
	if(m_nNumLeft == g_nHead)
		bHead = 1;
	else
		bHead = 0;

	return 1;
}

//为依存弧设置初始关系类型
void CPair::SetInitRelation()
{
	if(!Verify())
		return;
	FindPunctuation();
	
	CString ltag = ModifyTag(m_strTagLeft);
	CString rtag = ModifyTag(m_strTagRight);

	m_strRelation = "";
	if(m_strWordLeft == "的" && ltag == "u")
		m_strRelation = "DE";
	else if(m_strWordLeft == "地" && ltag == "u")
		m_strRelation = "DI";
	else if(m_strWordLeft == "得" && ltag == "u")
		m_strRelation = "DEI";
	else if(m_strWordRight == "把" && rtag == "p")
		m_strRelation = "BA";
	else if(m_strWordRight == "被" && rtag == "p")
		m_strRelation = "BEI";
	else if(m_strWordRight == "和" && rtag == "c")
		m_strRelation = "LAD";
/*	else if(m_strWordRight == "所" && rtag == "u" )
		m_strRelation = "SUO";
	else if(m_strWordRight == "等" && rtag == "u" )
		m_strRelation = "ADJ";
	else if(m_strWordRight == "兼" && rtag == "v" )
		m_strRelation = "ADJ";
	else if(m_strWordLeft == "说" && ltag == "v" )
		m_strRelation = "COB";
*/	else if(m_strWordLeft == "<EOS>")
		m_strRelation = "HED";

	if(m_strRelation != "")
		return;

	CMainFrame *pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	m_strTagRule = ltag + ' ' + rtag;
	if(m_nNumLeft < m_nNumRight)//弧的方向向左
	{
		int size = pMainFrame->m_relation.vecLeft.size();
		int i;
		for(i = 0; i < size; i++)
		{
			if(m_strTagRule == pMainFrame->m_relation.vecLeft[i].strRule)
			{
				m_strRelation = pMainFrame->m_relation.vecLeft[i].strRelation;
				break;
			}
		}
		if(i == size)			//该词性对未出现过
			m_strRelation = "NO";//缺省关系类型
	}
	else//弧的方向向右
	{
		int size = pMainFrame->m_relation.vecRight.size();
		int i;
		for(i = 0; i < size; i++)
		{
			if(m_strTagRule == pMainFrame->m_relation.vecRight[i].strRule)
			{
				m_strRelation = pMainFrame->m_relation.vecRight[i].strRelation;
				break;
			}
		}
		if(i == size)			//该词性对未出现过
			m_strRelation = "NO";//缺省关系类型
	}
}

//为依存弧设置候选关系类型
void CPair::SetCandidateRelation()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	m_strTagRule = ModifyTag(m_strTagLeft) + ' ' + ModifyTag(m_strTagRight);
	if(m_nNumLeft < m_nNumRight)//弧的方向向左
	{
		int size = pMainFrame->m_relation.vecLeft.size();
		for(int i = 0; i < size; i++)
		{
			if(m_strTagRule == pMainFrame->m_relation.vecLeft[i].strRule)
			{
				candidate.clear();
				for(int j = 0; j < (int)pMainFrame->m_relation.vecLeft[i].candidate.size();j++)
						candidate.push_back(pMainFrame->m_relation.vecLeft[i].candidate[j]);
				sort(candidate.begin(),candidate.end());
				break;
			}
		}
		//初始关系和候选关系如果都不对，则显示全部的左向关系
		size = pMainFrame->m_relation.allLeftRelation.size();
		allLeftRelation.clear();
		//for(int i = 0;i < size;i++)
		//	allLeftRelation.push_back(pMainFrame->m_relation.allLeftRelation[i]);
		allLeftRelation.assign(pMainFrame->m_relation.allLeftRelation.begin(), pMainFrame->m_relation.allLeftRelation.end() - 1);
	}
	else//弧的方向向右
	{
		int size = pMainFrame->m_relation.vecRight.size();
		for(int i = 0; i < size; i++)
		{
			if(m_strTagRule == pMainFrame->m_relation.vecRight[i].strRule)
			{
				candidate.clear();
				for(int j = 0; j < (int)pMainFrame->m_relation.vecRight[i].candidate.size();j++)
					candidate.push_back(pMainFrame->m_relation.vecRight[i].candidate[j]);
				sort(candidate.begin(),candidate.end());
				break;
			}
		}
		//初始关系和候选关系如果都不对，则显示全部的右向关系
		size = pMainFrame->m_relation.allRightRelation.size();
		allRightRelation.clear();
		// for(int i = 0;i < size;i++)
		// 	allRightRelation.push_back(pMainFrame->m_relation.allRightRelation[i]);
		allRightRelation.assign(pMainFrame->m_relation.allRightRelation.begin(), pMainFrame->m_relation.allRightRelation.end() - 1);
	}
}

// 针对动词细分类后的句子进行树库标注，还原三种词性为原始词性 by gold on 2008-4-26
CString CPair::ModifyTag(CString strTag)
{
	CString tag = strTag.Mid(0, 1);
	if (tag == "v" || tag == "u" || tag == "r")
	{
//		(*resultfile)<< "原始词性:   " << (LPCTSTR)strTag<<'\n';
		strTag = tag;
//		(*resultfile)<< "替换后词性: " << (LPCTSTR)strTag<<'\n';
	}
	return strTag;
}


/*
//生成该依存对可能的依存关系
void CPair::SetRelation()
{
	if(!Verify())
		return;
	FindPunctuation();
	
	int position;
	bool bTag = 0;
	
	CString strDirect;
	if(m_nNumLeft < m_nNumRight)
		strDirect = "0";
	else
		strDirect = "1";

	position = FindRelation(m_nNumLeft,m_nNumRight,bTag);
	if(position == -1)//该词性对未出现过
	{
		if(m_strRelation == "")
			m_strRelation = "NO";//缺省关系类型
		m_strTagRule = m_strTagLeft + ' ' + m_strTagRight + ' ' + strDirect;
		m_strWordRule = m_strWordLeft + '/' + m_strTagLeft + ' ' + m_strTagRight + ' ' + strDirect;
		candidate.clear();
		for(int i = 0;i < (int)allRelation.size();i++)
			candidate.push_back(allRelation[i]);
	}
	if(position >= 0)
	{
		if(bTag)
		{
			if(m_strRelation == "")
				m_strRelation = relation;
			candidate.clear();
			for(int i = 0;i < (int)other.size();i++)
			{
				candidate.push_back(other[i]);
			}
		}
		else
		{
			if(m_strRelation == "")
				m_strRelation = relation;
			candidate.clear();
			for(int i = 0;i < (int)other.size();i++)
			{
				candidate.push_back(other[i]);
			}
		}
	}

}

//寻找可能的依存关系
int CPair::FindRelation(int m_nNumLeft,int m_nNumRight,bool &bTag)
{
	CString strDirect;
	if(m_nNumLeft < m_nNumRight)
		strDirect = "0";
	else
		strDirect = "1";

	CString strWordRelation = m_strWordLeft + '/' + m_strTagLeft + ' ' + m_strTagRight + ' ' + strDirect;
	CString strTagRelation = m_strTagLeft + ' ' + m_strTagRight + ' ' + strDirect;

	ifstream fin1("TagRelation.txt");
	ifstream fin2("WordRelation.txt");
	
	CString strline,strUnit,strRel;
	int pos;
	string strTemp;

	//全部的依存关系
	ifstream fin("RelationList.txt");
	if(!fin)
	{
		AfxMessageBox("Cannot open file RelationList.txt!");
	}
	allRelation.clear();
	while(getline(fin,strTemp))
	{
		strline = strTemp.c_str();
		allRelation.push_back(strline);
	}

	//到词性关系规则文件中查找
	while(getline(fin1,strTemp))
	{
		strline = strTemp.c_str();
		
		pos = strline.ReverseFind(' ');
		strUnit = strline.Mid(0,pos);
		if(strUnit != strWordRelation)
			continue;
		m_strWordRule = strUnit;
		strline = strline.Right(strline.GetLength()-pos-1);
		pos = strline.Find('\t');
		relation = strline.Mid(0,pos);

		strline = strline.Right(strline.GetLength()-pos-1);
		pos = strline.Find('\t');
		while(pos != -1)
		{
			strRel = strline.Mid(0,pos);
			strline = strline.Right(strline.GetLength()-pos-1);
			other.push_back(strRel);
			pos = strline.Find('\t');
		}

		bTag = 0;
		fin1.close();
		return 1;
	}
	//到词汇关系规则文件中查找
	while(getline(fin2,strTemp))
	{
		strline = strTemp.c_str();
		
		pos = strline.ReverseFind(' ');
		strUnit = strline.Mid(0,pos);
		if(strUnit != strTagRelation)
			continue;
		m_strTagRule = strUnit;
		strline = strline.Right(strline.GetLength()-pos-1);
		pos = strline.Find('\t');
		relation = strline.Mid(0,pos);

		strline = strline.Right(strline.GetLength()-pos-1);
		pos = strline.Find('\t');
		while(pos != -1)
		{
			strRel = strline.Mid(0,pos);
			strline = strline.Right(strline.GetLength()-pos-1);
			other.push_back(strRel);
			pos = strline.Find('\t');
		}

		bTag = 1;
		fin2.close();
		return 1;
	}

	fin1.close();
	fin2.close();
	fin.close();
	return -1;//没有找到
}
*/


/*备用
	m_strRelation = "";
	if(m_strWordLeft == "的")
		m_strRelation = "DE";
	else if(m_strWordRight == "的")
		m_strRelation = "ATT";
	else if(m_strWordLeft == "地")
		m_strRelation = "DI";
	else if(m_strWordRight == "地")
		m_strRelation = "ADV";
	else if(m_strWordLeft == "得")
		m_strRelation = "DEI";
	else if(m_strWordRight == "得")
		m_strRelation = "CMP";
	else if(m_strWordLeft == "所")
		m_strRelation = "SUO";
	else if(m_strWordLeft == "EOS")
		m_strRelation = "HED";
	else if(m_strWordRight == "把")
		m_strRelation = "BA";
	else if(m_strWordRight == "被")
		m_strRelation = "DEI";
	else if(m_strWordLeft == "和")
		m_strRelation = "COO";
	else if(m_strWordRight == "和")
		m_strRelation = "COO";
*/
