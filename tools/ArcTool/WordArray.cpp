// WordArray.cpp: implementation of the CWordsArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "WordArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWordsArray::CWordsArray()
{

}

CWordsArray::~CWordsArray()
{

}

CWordsArray::CWordsArray(CString strInput)
{
	//[1]在/p [2]人们/r [3]日常/b [4]生活/ng [5]中/f [6]，/wo 
	int nBegin;
	int nEnd;
	CString strTemp;
	CWord word;

	nBegin = strInput.Find("[");
	while(nBegin != -1){
		nEnd = strInput.Find(" ", nBegin);
		strTemp = strInput.Mid(nBegin, nEnd - nBegin);
		word.SetWord(strTemp);
		m_Words.Add(word);
		nBegin = strInput.Find("[", nBegin);
	}
}

void CWordsArray::SetWordArray(CString strInput)
{
	m_Words.RemoveAll();
	//[1]在/p [2]人们/r [3]日常/b [4]生活/ng [5]中/f [6]，/wo 
	int nBegin;
	int nEnd;
	CString strTemp;
	CWord word;

	nBegin = strInput.Find("[");
	while(nBegin != -1){
		nEnd = strInput.Find(" ", nBegin);
		strTemp = strInput.Mid(nBegin, nEnd - nBegin);
		word.SetWord(strTemp);
		m_Words.Add(word);
		nBegin = strInput.Find("[", nEnd);
	}
}

int CWordsArray::GetSize()
{
	return m_Words.GetSize();
}

CWord CWordsArray::GetWord(int i)
{
	return m_Words[i];
}

CWord CWordsArray::GetWord(CString strWord)
{
	for(int i = 0; i < GetSize(); i++)
	{
		if(GetWord(i).m_strWord == strWord)
			return m_Words[i];//如果句子中多次出现同一个词，则只能匹配第一个
	}
	CWord word;
	return word;
}

void CWordsArray::ReSetWordArray(CString strInput)
{
	m_Words.RemoveAll();
	//[1]在/p [2]人们/r [3]日常/b [4]生活/ng [5]中/f [6]，/wo 
	int nBegin;
	int nEnd;
	CString strTemp;
	CWord word;
	int nIndex = 1;

	nBegin = strInput.Find("[");
	while(nBegin != -1){
		nEnd = strInput.Find(" ", nBegin);
		strTemp = strInput.Mid(nBegin, nEnd - nBegin);
		word.SetWord(strTemp, nIndex);
		m_Words.Add(word);
		nBegin = strInput.Find("[", nEnd);
		nIndex++;
	}
}

bool CWordsArray::InWords(CString strWord)
{
	for(int i = 0; i < GetSize(); i++){
		if(strWord == GetWord(i).m_strWord)
			return TRUE;
	}
	return FALSE;
}

CString CWordsArray::GetAttr(int nPos)
{
	if(nPos >=0 && nPos < GetSize()){
		return GetWord(nPos).m_strAttr;
	}else{
		return "";
	}
}
