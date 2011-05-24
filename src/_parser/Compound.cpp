#include ".\compound.h"
#include "MyLib.h"
#include <algorithm>

CCompound::CCompound(void)
{
//	fout.open("E:/UltraParser/Compound.txt");
}
 
CCompound::~CCompound(void)
{
}

string CCompound::Recognize(vector < DATA* > & vecSent)
{
	m_strResult = "";
	m_vecSent = vecSent;

	//int size = m_vecSent.size();
	//fout << endl << "sentence size is: " << size << endl;
	//for(int j = 0; j < size; j++)
	//	fout << m_vecSent[j]->word << ' ';
	//fout << endl;

	int nBeg = 1;
	int nEnd = (int)m_vecSent.size() - 1;
	for(int i = nEnd; i >= nBeg; i--)
	{
		int nLeft = i;				// left position of NC
		int nRight = i;				// right position of NC
		if(IsHead(i) )				// found possible head word
		{
			i--;
			while(i >= nBeg && IsModifier(i) )
			{
				nLeft = i;
				i--;
			}
			if(nLeft < nRight)
			{
				Analyze(nLeft,nRight);
				if(IsLeftPunct(nLeft-1) && IsRightPunct(nRight+1) )
				{
					m_vecSent[nLeft-1]->mark = 1;	// adjacent symmetry punctuntions will be erased
					m_vecSent[nRight+1]->mark = 1;
				}
			}
		}
	}

	Delete();

	vecSent = m_vecSent;
	m_vecSent.clear();

	return m_strResult;
}

bool CCompound::IsHead(int i)
{
	string tag = m_vecSent[i]->tag;
	if(tag == "n" || tag == "nh" || tag == "ns" || tag == "ni" || tag == "j" || tag == "vn")
		return 1;
	else
		return 0;
}

bool CCompound::IsModifier(int i)
{
	string tag = m_vecSent[i]->tag;
	if(tag[0] == 'n' || tag == "b" || tag == "j" || tag == "ws" || tag == "vn")	// tag == "vg"
		return 1;
	else
		return 0;
}


bool CCompound::IsLeftPunct(int i)
{
	string word = m_vecSent[i]->tag;
	if(word == "¡°" || word == "¡¶" || word == "£¨" || word == "¡®")
		return 1;
	else
		return 0;
}

bool CCompound::IsRightPunct(int i)
{
	string word = m_vecSent[i]->tag;
	if(word == "¡±" || word == "¡·" || word == "£©" || word == "¡¯")
		return 1;
	else
		return 0;
}

void CCompound::Analyze(int nLeft, int nRight)
{
	for(int i = nLeft; i < nRight; i++)
	{
		PrintPair(i+1,i,"ATT");
	}
}

//output the dependecy pair
void CCompound::PrintPair(int parent, int child, string strRelation)
{
	m_vecSent[child]->mark = 1;	// the node is reduced

	int id1 = m_vecSent[parent]->id;
	int id2 = m_vecSent[child]->id;
	string first = '[' + itos(id1) + ']' + m_vecSent[parent]->word;
	string second = '[' + itos(id2) + ']' + m_vecSent[child]->word;
	string relation = '(' + strRelation + ')' + "\t\t";
	m_strResult += first + '_' + second + relation;
}

// delete the reduced nodes which are marked with 1
void CCompound::Delete()
{
	m_vecSent.erase(remove_if(m_vecSent.begin(), m_vecSent.end(), IsMarked), m_vecSent.end() );
}