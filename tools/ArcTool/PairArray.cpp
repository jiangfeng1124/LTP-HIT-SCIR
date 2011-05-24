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
	//[1]��_[5]��_58413  [5]��_[4]����_3803  [4]����_[3]�ճ�_1093  [4]����_[2]����_1027 
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
	//[1]��_[5]��(POB)  [5]��_[4]����(DIR)  [4]����_[3]�ճ�(ATT)  [4]����_[2]����(ATT) 
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

//���ӡ�ת���ɾ��һ����
void CPairArray::DoPair(CPair& mpair)
{
	for(int i = 0; i < myPairArray.GetSize(); i++)
	{
		//����������������У�ɾ�������еĸû�
		/*if(mpair.IsPair(myPairArray[i]))
		{
			myPairArray[i].Reverse();//���ڸı��˻��ķ����׼����ɾ������
			myPairArray[i].SetInitRelation();
			myPairArray[i].SetCandidateRelation();
			return;
		}
		//������Ժ������е�һ��˳���෴���ı������еĸû��ķ���
		else if(mpair.IsReverse(myPairArray[i]))
		{
			myPairArray.RemoveAt(i);//��ת�򽻻�
			return;
		}*/
		if(mpair.IsPair(myPairArray[i]))
		{
			myPairArray.RemoveAt(i);//ɾ��
			return;
		}
		//������Ժ������е�һ��˳���෴���ı������еĸû��ķ���
		else if(mpair.IsReverse(myPairArray[i]))
		{
			myPairArray[i].Reverse();//�ı��˻��ķ���
			myPairArray[i].SetInitRelation();
			myPairArray[i].SetCandidateRelation();
			return;
		}
	}
	//���������У�����
	//mpair.Reverse();//���ڸı��˻��ķ����׼����ת��
	mpair.SetInitRelation();
	mpair.SetCandidateRelation();
	myPairArray.Add(mpair);//����
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
			pair.m_strRelation = myPairArray[i].m_strRelation;//����ԭ���������ϵ
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
