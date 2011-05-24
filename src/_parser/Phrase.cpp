#include ".\phrase.h"
#include "MyLib.h"
#include <algorithm>

CPhrase::CPhrase(void)
{
}

CPhrase::~CPhrase(void)
{
}

string CPhrase::RecogJuxt(vector < DATA* > & vecSent)
{
	m_strResult = "";
	m_vecSent = vecSent;

	int nBeg = 2;
	int nEnd = (int)m_vecSent.size() - 2;
	for(int i = nBeg; i < nEnd; i++)
	{
		int nLeft = i - 2;			//left position of COO 
		int nRight = 0;				//right position of COO
		while(i < nEnd && IsConjunction(i) && IsBoundary(i))
		{
			i += 2;					//i denotes the label of Conjunctuon:、 和 与 或 及 并且... 
			nRight = i;
		}

		if( nRight > 0 )
			Recognize(nLeft,nRight); // Is it coordinating structure?
	}

	Delete();

	vecSent = m_vecSent;
	m_vecSent.clear();

	return m_strResult;
}

//判断并列结构标记的左右边界是否存在不合理
bool CPhrase::IsBoundary(int i)
{
	//标记旁边是标点，不合理
	if(m_vecSent[i-1]->tag == "wp" || m_vecSent[i+1]->tag == "wp")
		return 0;

	//标记的隔一个位置是标点，合理
	if(m_vecSent[i-2]->tag == "wp" || m_vecSent[i+2]->tag == "wp")
		return 1;

	int nEnd = (int)m_vecSent.size() - 2;
	if( i-3 >= 2 && m_vecSent[i-3]->word == "、" )	//检查并列结构标记前面第3个位置，如果还有并列标记
		return 0;									//不是简单并列结构: AB、CD和EF
	if( i+3 <= nEnd && IsConjunction(i+3) )			//检查并列结构标记后面第3个位置，如果还有并列标记
		return 0;									//不是简单并列结构

	return 1;
}

bool CPhrase::IsConjunction(int i)
{
	string word = m_vecSent[i]->word;
	string tag = m_vecSent[i]->tag;

	//排除转折连词：为/p 赚钱/v 而/c 工作/v
	if(word == "而" && m_vecSent[i+1]->tag[0] == 'v')
		return 0;
	if(word == "、" || (tag == "c" && (word == "和" || word == "及" || word == "与" 
		|| word == "或" || word == "而" || word == "并" || word == "并且") ) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//判断候选成分是否为简单并列结构
bool CPhrase::Recognize(int nLeft, int nRight)
{
	//left A 、 B 和 C right
	string left = m_vecSent[nLeft]->tag;
	string right = m_vecSent[nRight]->tag;

	//计算并列成分的相似度
	bool bSimilar = Like(nLeft,nRight);
	if(!bSimilar)
		return false;

	for(int i = nLeft+3; i <= nRight-1; i+=2)
	{
		PrintPair(nLeft+1,i,"COO");
		if(m_vecSent[i-1]->tag == "c")
			PrintPair(i,i-1,"LAD");
	}

	return true;
}

//判断候选的并列成分是否相似
bool CPhrase::Like(int nLeft, int nRight)
{
	//first constituent
	string tag1 = m_vecSent[nLeft+1]->tag;
	string word1 = m_vecSent[nLeft+1]->word;

	//last constituent
	string tag2 = m_vecSent[nRight-1]->tag;
	string word2 = m_vecSent[nRight-1]->word;

	if( nRight - nLeft > 4 )					//多个成分并列
		return 1;
	if( m_vecSent[nRight]->tag == "wp" )		//后面是标点
		return 1;

	//是并列词组，非简单结构
	if( m_vecSent[nLeft]->tag == tag2 && tag1 == m_vecSent[nRight]->tag )
		return 0;
	if( m_vecSent[nLeft]->word == word2 || m_vecSent[nRight]->word == word1 )
		return 0;

	if( tag1 == tag2 || (tag1 == "n" && tag2 == "vn") || (tag1 == "vn" && tag2 == "n") )
		return 1;
	else
		return 0;
}


string CPhrase::RecogVerb(vector < DATA* > & vecSent)
{
	m_strResult = "";
	m_vecSent = vecSent;

	int nBeg = 1;
	int nEnd = (int)m_vecSent.size() - 2;
	for(int i = nBeg; i < nEnd; i++)
	{
		string::size_type nLen1 = m_vecSent[i]->word.length();
		string::size_type nLen2 = m_vecSent[i+1]->word.length();

		// both words are one-charactor
		if( nLen1 == 2 && nLen2 == 2)
		{	
			// first tag is "vg", and second tag is "n" or "j"
			if( m_vecSent[i]->tag == "vg" && (m_vecSent[i+1]->tag == "n" || m_vecSent[i+1]->tag == "j") )
			{	
				//and the second is not part of coo structure
				if( !IsConjunction(i+2) || (IsConjunction(i+2) && i+3 <= nEnd && m_vecSent[i+3]->tag == "vg") )
				{	
					// not frequent verb
					if( !IsFreqVerb(m_vecSent[i]->word) )
					{
						PrintPair(i,i+1,"VOB");
						if( i+3 <= nEnd )
						{	
							// combine words that consist of four charactors
							nLen1 = m_vecSent[i+2]->word.length();
							nLen2 = m_vecSent[i+3]->word.length();
							// such form as 跳/vg 崖/n 殉国/vg
							if( nLen1 == 4 && m_vecSent[i+2]->tag == "vg" )
							{
								PrintPair(i,i+2,"VV");
								i += 2;
							}
							if( nLen1 == 2 && nLen2 == 2 )
							{	
								// such form as 顺/vg 流/n 而/c 下/vq
								if(	m_vecSent[i+2]->tag == "c" && m_vecSent[i+3]->tag[0] == 'v' )
								{
									PrintPair(i+3,i+2,"CNJ");
									PrintPair(i,i+3,"VV");
									i += 3;
								}
								// such form as 舐/vg 犊/n 护/vg 犊/n
								else if( m_vecSent[i+2]->tag == m_vecSent[i]->tag 
									&& m_vecSent[i+3]->tag == m_vecSent[i+1]->tag
									&& !IsFreqVerb(m_vecSent[i+2]->word) )
								{
									PrintPair(i+2,i+3,"VOB");
									PrintPair(i,i+2,"VV");
									i += 3;
								}
							}
						}
					}
				}
			}
		}
	}

	Delete();

	vecSent = m_vecSent;
	m_vecSent.clear();

	return m_strResult;
}

bool CPhrase::IsFreqVerb(string word)
{
	if(m_mapVerb.find(word) != m_mapVerb.end() )
		return 1;
	else
		return 0;
}

string CPhrase::RecogTime(vector < DATA* > & vecSent)
{
	m_strResult = "";
	m_vecSent = vecSent;

	int nBeg = 1;
	int nEnd = (int)m_vecSent.size() - 2;
	for(int i = nBeg; i < nEnd; i++)
	{
		string tag1 = m_vecSent[i]->tag;
		string tag2 = m_vecSent[i+1]->tag;
		if(tag1 == "nt")
		{	
			if(tag2 == "nt")
				PrintPair(i+1,i,"ATT");//recognize such form as ６月/nt ３日/nt
			else if(m_vecSent[i+2]->tag == "nt" && m_vecSent[i+1]->word.find("—") != -1)
			{	
				PrintPair(i+2,i,"ATT");//recognize such form as ３日/nt —/wp ４日/nt
				i++;
			}
		}
	}

	Delete();

	vecSent = m_vecSent;
	m_vecSent.clear();

	return m_strResult;
}

string CPhrase::RecogNumber(vector < DATA* > & vecSent)
{
	m_strResult = "";
	m_vecSent = vecSent;

	int nBeg = 1;
	int nEnd = (int)m_vecSent.size() - 2;
	for(int i = nBeg; i < nEnd; i++)
	{
		string tag1 = m_vecSent[i]->tag;
		string tag2 = m_vecSent[i+1]->tag;
		if(tag1 == "m")
		{	
			if(tag2 == "m")
			{
				PrintPair(i,i+1,"RAD");	//the form: 5万 多，8% 左右
				if(i+2 <= nEnd && m_vecSent[i+2]->tag == "m")
				{
					PrintPair(i+2,i,"ATT");//the form: 10 多 万
					i += 2;
				}
				else
				{
					i++;
				}
			}
			else if(m_vecSent[i+2]->tag == "m" && m_vecSent[i+1]->word.find("—") != -1)
			{	
				PrintPair(i+2,i,"RAD");//the form: 7%/m —/wp 8%/m
				i += 2;
			}
		}
	}
 
	Delete();

	vecSent = m_vecSent;
	m_vecSent.clear();

	return m_strResult;
}

void CPhrase::LoadVerb()
{
	ifstream fverb( (g_strDataPath+"FreqVerb.txt").c_str() );
	if(!fverb)
	{
		cout << "Parser: Cannot open file FrebVerb.txt!" << endl;
		exit(0);
	}

	string strWord;
	while( getline(fverb,strWord) )
		m_mapVerb[strWord] = 1;

	fverb.close();
}

//output the dependecy pair
void CPhrase::PrintPair(int parent, int child, string strRelation)
{
	Mark(parent, child);

	int id1 = m_vecSent[parent]->id;
	int id2 = m_vecSent[child]->id;
	string first = '[' + itos(id1) + ']' + m_vecSent[parent]->word;
	string second = '[' + itos(id2) + ']' + m_vecSent[child]->word;
	string relation = '(' + strRelation + ')' + "\t\t";
	m_strResult += first + '_' + second + relation;
}

// mark the reduced node and punct
void CPhrase::Mark(int parent, int child)
{
	int index1, index2;
	if(parent < child)
	{
		index1 = parent+1;
		index2 = child-1;
	}
	else
	{
		index1 = child+1;
		index2 = parent-1;
	}
	
	int i;
	for(i = index1; i <= index2; i++)
	{
		if(m_vecSent[i]->tag == "wp")	// the punctuation in the pair
			m_vecSent[i]->mark = 1;
	}

	m_vecSent[child]->mark = 1;	// the node is reduced
}

// delete the reduced nodes which are marked with 1
void CPhrase::Delete()
{
	m_vecSent.erase(remove_if(m_vecSent.begin(), m_vecSent.end(), IsMarked), m_vecSent.end() );
}