// Word.cpp: implementation of the CWord class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Word.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWord::CWord()
{
	m_nPos = -1;
	m_strWord = "";
	m_strAttr = "";
}

CWord::CWord(CString strInput)
{
	//[1]дк/p
	int nBegin;
	int nEnd;
	CString strTemp;
	char* pTemp;

	nBegin = strTemp.Find("[");
	nEnd = strTemp.Find("]");
	if(nBegin != -1){
		strTemp = strInput.Mid(nBegin + 1, nEnd - nBegin - 1);
		pTemp = strTemp.GetBuffer(strTemp.GetLength());
		m_nPos = ::atoi(pTemp);
		
		nBegin = nEnd;
		nEnd = strInput.Find("/", nBegin);
		m_strWord = strInput.Mid(nBegin + 1, nEnd - nBegin - 1);
		
		nBegin = nEnd;
		m_strAttr = strInput.Mid(nBegin + 1);
	}
}

void CWord::SetWord(CString strInput)
{
	//[1]дк/p
	int nBegin;
	int nEnd;
	CString strTemp;
	char* pTemp;

	nBegin = strInput.Find("[");
	nEnd = strInput.Find("]");
	if(nBegin != -1){
		strTemp = strInput.Mid(nBegin + 1, nEnd - nBegin - 1);
		pTemp = strTemp.GetBuffer(strTemp.GetLength());
		m_nPos = ::atoi(pTemp);
		
		nBegin = nEnd;
		nEnd = strInput.Find("/", nBegin);
		m_strWord = strInput.Mid(nBegin + 1, nEnd - nBegin - 1);

		nBegin = nEnd;
		m_strAttr = strInput.Mid(nBegin + 1);
	}
}

void CWord::SetWord(CString strInput, int nIndex)
{
	//[1]дк/p
	int nBegin;
	int nEnd;
	
	nBegin = strInput.Find("[");
	nEnd = strInput.Find("]");
	if(nBegin != -1){
		m_nPos = nIndex;
		
		nBegin = nEnd;
		nEnd = strInput.Find("/", nBegin);
		m_strWord = strInput.Mid(nBegin + 1, nEnd - nBegin - 1);

		nBegin = nEnd;
		m_strAttr = strInput.Mid(nBegin + 1);
	}
}

CWord::~CWord()
{

}

CString CWord::GetWord()
{
	return m_strWord;
}
