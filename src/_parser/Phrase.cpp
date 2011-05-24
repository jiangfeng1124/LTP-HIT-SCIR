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
			i += 2;					//i denotes the label of Conjunctuon:�� �� �� �� �� ����... 
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

//�жϲ��нṹ��ǵ����ұ߽��Ƿ���ڲ�����
bool CPhrase::IsBoundary(int i)
{
	//����Ա��Ǳ�㣬������
	if(m_vecSent[i-1]->tag == "wp" || m_vecSent[i+1]->tag == "wp")
		return 0;

	//��ǵĸ�һ��λ���Ǳ�㣬����
	if(m_vecSent[i-2]->tag == "wp" || m_vecSent[i+2]->tag == "wp")
		return 1;

	int nEnd = (int)m_vecSent.size() - 2;
	if( i-3 >= 2 && m_vecSent[i-3]->word == "��" )	//��鲢�нṹ���ǰ���3��λ�ã�������в��б��
		return 0;									//���Ǽ򵥲��нṹ: AB��CD��EF
	if( i+3 <= nEnd && IsConjunction(i+3) )			//��鲢�нṹ��Ǻ����3��λ�ã�������в��б��
		return 0;									//���Ǽ򵥲��нṹ

	return 1;
}

bool CPhrase::IsConjunction(int i)
{
	string word = m_vecSent[i]->word;
	string tag = m_vecSent[i]->tag;

	//�ų�ת�����ʣ�Ϊ/p ׬Ǯ/v ��/c ����/v
	if(word == "��" && m_vecSent[i+1]->tag[0] == 'v')
		return 0;
	if(word == "��" || (tag == "c" && (word == "��" || word == "��" || word == "��" 
		|| word == "��" || word == "��" || word == "��" || word == "����") ) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//�жϺ�ѡ�ɷ��Ƿ�Ϊ�򵥲��нṹ
bool CPhrase::Recognize(int nLeft, int nRight)
{
	//left A �� B �� C right
	string left = m_vecSent[nLeft]->tag;
	string right = m_vecSent[nRight]->tag;

	//���㲢�гɷֵ����ƶ�
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

//�жϺ�ѡ�Ĳ��гɷ��Ƿ�����
bool CPhrase::Like(int nLeft, int nRight)
{
	//first constituent
	string tag1 = m_vecSent[nLeft+1]->tag;
	string word1 = m_vecSent[nLeft+1]->word;

	//last constituent
	string tag2 = m_vecSent[nRight-1]->tag;
	string word2 = m_vecSent[nRight-1]->word;

	if( nRight - nLeft > 4 )					//����ɷֲ���
		return 1;
	if( m_vecSent[nRight]->tag == "wp" )		//�����Ǳ��
		return 1;

	//�ǲ��д��飬�Ǽ򵥽ṹ
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
							// such form as ��/vg ��/n ѳ��/vg
							if( nLen1 == 4 && m_vecSent[i+2]->tag == "vg" )
							{
								PrintPair(i,i+2,"VV");
								i += 2;
							}
							if( nLen1 == 2 && nLen2 == 2 )
							{	
								// such form as ˳/vg ��/n ��/c ��/vq
								if(	m_vecSent[i+2]->tag == "c" && m_vecSent[i+3]->tag[0] == 'v' )
								{
									PrintPair(i+3,i+2,"CNJ");
									PrintPair(i,i+3,"VV");
									i += 3;
								}
								// such form as ��/vg ��/n ��/vg ��/n
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
				PrintPair(i+1,i,"ATT");//recognize such form as ����/nt ����/nt
			else if(m_vecSent[i+2]->tag == "nt" && m_vecSent[i+1]->word.find("��") != -1)
			{	
				PrintPair(i+2,i,"ATT");//recognize such form as ����/nt ��/wp ����/nt
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
				PrintPair(i,i+1,"RAD");	//the form: 5�� �࣬8% ����
				if(i+2 <= nEnd && m_vecSent[i+2]->tag == "m")
				{
					PrintPair(i+2,i,"ATT");//the form: 10 �� ��
					i += 2;
				}
				else
				{
					i++;
				}
			}
			else if(m_vecSent[i+2]->tag == "m" && m_vecSent[i+1]->word.find("��") != -1)
			{	
				PrintPair(i+2,i,"RAD");//the form: 7%/m ��/wp 8%/m
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