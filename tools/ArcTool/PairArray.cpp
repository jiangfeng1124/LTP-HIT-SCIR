// PairArray.cpp: implementation of the CPairArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PairArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPairArray::CPairArray()
{

}

CPairArray::~CPairArray()
{

}

CPairArray::CPairArray(CString strInput)
{
	//[1]在_[5]中_58413  [5]中_[4]生活_3803  [4]生活_[3]日常_1093  [4]生活_[2]人们_1027 
	CString strTemp;
	int nBegin, nEnd;
	CPair pairTemp;
	nBegin = strInput.Find("[");
	while(nBegin != -1){
		nEnd = strInput.Find("\t\t", nBegin);
		strTemp = strInput.Mid(nBegin, nEnd - nBegin);
		pairTemp.SetPair(strTemp);
		myPairArray.Add(pairTemp);
		nBegin = strInput.Find("[", nEnd);
	}
}

void CPairArray::SetPairArray(CString strInput)
{
	//[1]在_[5]中(POB)  [5]中_[4]生活(DIR)  [4]生活_[3]日常(ATT)  [4]生活_[2]人们(ATT) 
	myPairArray.RemoveAll();

	CString strTemp;
	int nBegin, nEnd;
	CPair pairTemp;
//	pairTemp.InitRelation();
	nBegin = strInput.Find("[");
	while(nBegin != -1){
		nEnd = strInput.Find("\t\t", nBegin);
		strTemp = strInput.Mid(nBegin, nEnd - nBegin);
		pairTemp.SetPair(strTemp);
		myPairArray.Add(pairTemp);
		nBegin = strInput.Find("[", nEnd);
	}
}

//增加、转向或删除一条弧
void CPairArray::DoPair(CPair& mpair)
{
	for(int i = 0; i < myPairArray.GetSize(); i++)
	{
		//该依存对如在数组中，删除数组中的该弧
		/*if(mpair.IsPair(myPairArray[i]))
		{
			myPairArray[i].Reverse();//由于改变了弧的方向标准，和删除交换
			myPairArray[i].SetInitRelation();
			myPairArray[i].SetCandidateRelation();
			return;
		}
		//该依存对和数组中的一个顺序相反，改变数组中的该弧的方向
		else if(mpair.IsReverse(myPairArray[i]))
		{
			myPairArray.RemoveAt(i);//和转向交换
			return;
		}*/
		if(mpair.IsPair(myPairArray[i]))
		{
			myPairArray.RemoveAt(i);//删除
			return;
		}
		//该依存对和数组中的一个顺序相反，改变数组中的该弧的方向
		else if(mpair.IsReverse(myPairArray[i]))
		{
			myPairArray[i].Reverse();//改变了弧的方向
			myPairArray[i].SetInitRelation();
			myPairArray[i].SetCandidateRelation();
			return;
		}
	}
	//不在数组中，加入
	//mpair.Reverse();//由于改变了弧的方向标准，先转向
	mpair.SetInitRelation();
	mpair.SetCandidateRelation();
	myPairArray.Add(mpair);//增加
}

void CPairArray::AddPair(CPair pair)
{
	for(int i = 0; i < myPairArray.GetSize(); i++){
		if(pair.IsPair(myPairArray[i])){
			return;
		}
	}
	myPairArray.Add(pair);
}

void CPairArray::DeletePair(CPair pair)
{
	for(int i = 0; i < myPairArray.GetSize(); i++){
		if(pair.IsPair(myPairArray[i])){
			myPairArray.RemoveAt(i);
			return;
		}
	}
}

int CPairArray::GetSize()
{
	return myPairArray.GetSize();
}

CPair CPairArray::GetPair(int i)
{
	return myPairArray[i];
}

void CPairArray::ReSetPairArray(CWordsArray& wordsarray)
{
	CPair pair;
	for(int i = 0; i < myPairArray.GetSize(); i++)
	{
		if(!wordsarray.InWords(myPairArray[i].m_strWordLeft) ||
			!wordsarray.InWords(myPairArray[i].m_strWordRight))
		{
			pair.SetLeft(-1, "","");
			pair.SetRight(-1, "","");
		} 
		else 
		{
			CWord word = wordsarray.GetWord(myPairArray[i].m_strWordLeft);
			pair.SetLeft(word.m_nPos, word.m_strWord,word.m_strAttr);
			word = wordsarray.GetWord(myPairArray[i].m_strWordRight);
			pair.SetRight(word.m_nPos, word.m_strWord,word.m_strAttr);
			pair.m_strRelation = myPairArray[i].m_strRelation;//保留原来的依存关系
		}
		myPairArray.SetAt(i, pair);
	}
}


void CPairArray::ChangeRect(int i, CPair &mpair)
{
	myPairArray[i].rect = mpair.rect;
}

void CPairArray::ChangeRelation(int i, CString &strRelation)
{
	myPairArray[i].m_strRelation = strRelation;
}

void CPairArray::ChangeMark(int i, bool bRelation)
{
	myPairArray[i].bRelation = bRelation;
}
