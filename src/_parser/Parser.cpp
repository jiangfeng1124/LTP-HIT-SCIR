// Parser.cpp: implementation of the Parser class.
//
//////////////////////////////////////////////////////////////////////

#include "Parser.h"
#include <iostream>
#include <math.h>
#include <algorithm>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParser::CParser()
{
//	Initialize();
//	fout.open("E:/UltraParser/记录过程.txt");
}

CParser::~CParser()
{
}

void CParser::ParseFile(string strInputFile, string strOutputFile)
{
	ifstream fin(strInputFile.c_str() );
	if(!fin)
	{
		cout << "Cannot open input file " << strInputFile << " !" << endl;
		exit(0);
	}

	ofstream fout(strOutputFile.c_str() );
	if(!fout)
	{
		cout << "Cannot open output file " << strOutputFile << " !" << endl;
		exit(0);
	}

	string strLine; 
	vector < string > vecSent;

	int counter = 0;
	while(!fin.eof() )
	{
		getline(fin,strLine);
		while(strLine != "")
		{
			vecSent.push_back(strLine);
			getline(fin,strLine);
		}
		if(vecSent.size() == 0)
			continue;

		cout << ++counter << ' ';
		string strParsed;
		ParseSent(vecSent, strParsed);
		fout << m_strSent1 << endl;
		fout << m_strSent2 << endl;
		fout << strParsed << endl;

		vecSent.clear();
	}
}

int CParser::ParseSent(vector <string> & vecSent, string &strParseResult)
{
	m_strSent1 = "";
	m_strSent2 = "";
	m_strResult = "";

	if (0 != GetRawSent(vecSent)) return -1;
	SetSentInfo(vecSent);

	// Recognize specific structures
	//ShowSent();
	string strResult1 = phrase.RecogVerb(m_vecSent);
	//fout << endl << "strResult1: " << strResult1 << endl;
	//ShowSent();
	string strResult2 = compound.Recognize(m_vecSent);
	//fout << endl << "strResult2: " << strResult2 << endl;
	//ShowSent();
	string strResult3 = phrase.RecogTime(m_vecSent);
	//fout << endl << "strResult3: " << strResult3 << endl;
	//ShowSent();
	string strResult4 = phrase.RecogNumber(m_vecSent);
	//fout << endl << "strResult4: " << strResult4 << endl;
	//ShowSent();
	string strResult5 = phrase.RecogJuxt(m_vecSent);
	//fout << endl << "strResult5: " << strResult5 << endl;
	//ShowSent();
	//fout << endl << "******************************" << endl << endl;

	m_nDataSize = (int)m_vecSent.size();

	Parse();

	m_strResult += strResult1 + strResult2 + strResult3 + strResult4 + strResult5;
	strParseResult = m_strResult;
	return 0;
}

// get raw sentence for show
int CParser::GetRawSent(vector <string> & vecSent)
{
	vector < string > vecTemp;
	unsigned int i;
	for(i = 0; i < vecSent.size(); i++) 
	{
		string strRow = vecSent[i]; // 8	会面	会面	v	vg	_	2	VOB	_	_
		split('\t', strRow, vecTemp);

		if (vecTemp.size() < 5) {
			cerr << "parser format err: " << strRow << endl;
			return -1;
		}

		string id = vecTemp[0];
		string word = vecTemp[1];
		string ctag = vecTemp[3];
		string tag = vecTemp[4];

		m_strSent1 += word;	// the first line for show
		m_strSent2 += '[' + id + ']' + word + '/' + tag + ' ';	// the second line for show
	}
	m_strSent2 += '[' + itos(i+1) + ']' + "<EOS>" + '/' + "<EOS>" + ' ';	// End Of Sentence
	vecTemp.clear();
	return 0;
}

// set information of sentence into vector
void CParser::SetSentInfo(vector <string> & vecSent)
{
	int id = 0;
	vector < string > vecTemp;
	DATA* data = new DATA;

	// put the head of sentence into vector
	data->id = id;
	data->word = "BEG";
	data->ctag = "BEG";
	data->tag = "BEG";
	data->mark = 0;
	m_vecSent.push_back(data);

	unsigned int i;
	for(i = 0; i < vecSent.size(); i++) 
	{
		string strRow = vecSent[i]; // 8	会面	会面	v	vg	_	2	VOB	_	_
		split('\t', strRow, vecTemp);

		id = atoi(vecTemp[0].c_str() );
		data = new DATA;
		data->id = id;
		data->word = vecTemp[1];
		data->ctag = vecTemp[3];
		data->tag = vecTemp[4];
		data->mark = 0;
		data->relation = "";
		m_vecSent.push_back(data);
	}

	//put the end of sentence into vector
	data = new DATA;
	data->id = id+1;
	data->word = "<EOS>";
	data->ctag = "<EOS>";
	data->tag = "<EOS>";
	data->mark = 0;
	data->relation = "";
	m_vecSent.push_back(data);

	vecTemp.clear();
}

void CParser::Parse()
{
	ReduceLeaf();

	int nEnd = (int)m_vecSent.size()-1;
	for(int i = 1; i < nEnd; i++)
	{
		if(m_vecSent[i]->mark == 0 && m_vecSent[i]->tag != "wp")
		{
			PrintPair(nEnd, i, "HED");
		}
	}

	vector < DATA* > ::iterator it;
	for(it = m_vecSent.begin(); it != m_vecSent.end(); it++)
	{
		delete *it;
	}
	m_vecSent.clear();
	m_vecPair.clear();
}

void CParser::ResetSentInfo()
{
	vector < DATA* > ::iterator it;
	for( it = m_vecSent.end()-1; it >= m_vecSent.begin(); it-- )
	{	
		if( (*it)->mark == 1) // this element has been reduced, erase it
		{
			delete *it;
			m_vecSent.erase(it);
		}
	}
}

// Reduce the most possible node
void CParser::ReduceLeaf()
{
	string strRelation = "";
	float fProb = 0;
	PAIR myPair;
	unsigned int i;

	for(i = 0; i < m_vecSent.size()-3; i++)
	{
		if(m_vecSent[i+1]->tag != "wp")
		{
			int index1 = i+1; // the first word
			while(m_vecSent[i+2]->tag == "wp" && i+3 < m_vecSent.size()-1)
				i++;							// i+2 is punctuation, and i+3 is not EOS 
			if(m_vecSent[i+2]->tag == "wp" && i+3 >= m_vecSent.size()-1 )
				break;
 
			int index2 = i+2; // the second word
			GetPair(index1,index2,myPair);
			m_vecPair.push_back(myPair);
		}
	}
	
	sort (m_vecPair.begin(), m_vecPair.end() );
//	OutputVector();

	for(i = 0; i < m_vecPair.size(); i++)
	{
		if(Check(i) )
		{
			CreateLeaf(i);
			i = -1;
		}
		else if (i == m_vecPair.size() - 1)	// 第一个将后面的全部阻塞，规约第二个
		{
			int n = FindPair();
			CreateLeaf(n);
			i = -1;
		}
//		OutputVector();
	}
}


void CParser::CreateLeaf(int i)
{
	int nPos_Child;//nPos_Head, 
	PAIR myPair;
	int index1 = m_vecPair[i].index1;
	int index2 = m_vecPair[i].index2;
	string strRelation = m_vecPair[i].relation;
	m_nPreDirect = GetDirect(strRelation);

	vector < PAIR > ::iterator iter = m_vecPair.begin();
	m_vecPair.erase(iter+i);

	// Add by LZH 2007-1-16
	// After erase(), iter is undefined. In VC2005, this turns out a bug.
	iter = m_vecPair.begin();

	int nDirect = GetDirect(strRelation);
	if(nDirect == LEFT)
	{
		PrintPair(index1, index2, strRelation);
		index2 = FindRightNode(index2,nPos_Child);
	}
	else
	{
		PrintPair(index2, index1, strRelation);
		index1 = FindLeftNode(index1,nPos_Child);
	}

	// delete the pair linked with child node
	if(nPos_Child >= 0)
	{
		m_vecPair.erase(iter+nPos_Child);

		GetPair(index1,index2,myPair);
		iter = lower_bound(m_vecPair.begin(), m_vecPair.end(),myPair);

		m_vecPair.insert(iter, myPair);
	}
}

void CParser::GetPair(int index1, int index2, PAIR& myPair)
{
	float fProb;
	string strRelation = GetRelation(index1,index2,fProb); // 获得当前的依存关系

	myPair.index1 = index1;
	myPair.index2 = index2;
	myPair.relation = strRelation;
	myPair.prob = fProb;
	myPair.wait = 0;
	myPair.delay = 0;
	myPair.block = 0;
	myPair.level = GetLevel(strRelation);
	//if(strRelation == "VOB" || strRelation == "VV")
	//{
	//	myPair.delay = 3;
	//}
}

string CParser::GetRelation(int index1, int index2, float& fProb)
{
	string ww, wt, tw, tt, tttt, td;
	GetSequence(ww,wt,tw,tt,tttt,td,index1,index2);

	fProb = -log(MINPROB);
	string relation = "NOT";
	float fProb_Relation = MAXPROB;

	vector < PROB > vecProb;
	FindCandidate(vecProb,td,1);
	FindCandidate(vecProb,tt,2);
	FindCandidate(vecProb,tttt,3);
	FindCandidate(vecProb,tw,4);
	FindCandidate(vecProb,wt,5);
	FindCandidate(vecProb,ww,6);

//	fout << "==============" << ww << "====================" << endl;
	vector < PROB > ::iterator it;
	for(it = vecProb.begin(); it!= vecProb.end(); it++)
	{
		string curRelation = it->relation;
		float fCurProb = Smoothen(it->ftd,it->ftt,it->ftttt,it->ftw,it->fwt,it->fww);
		float fCurProb_Relation = GetProb(fCurProb,curRelation,index1,index2);
		if(fCurProb_Relation < fProb_Relation)
		{
			fProb_Relation = fCurProb_Relation;
			relation = curRelation;
			fProb = -log(fCurProb);
		}
	}

//	fout << "***********" << relation << "**" << fProb << "***************" << endl << endl;
	return relation;
}

void CParser::GetSequence(string& ww, string& wt, string& tw, string& tt, string& tttt, string& td,
						  int index1, int index2)
{
	string word1,ctag1,tag1,word2,ctag2,tag2,pretag,nexttag;

	ctag1 = m_vecSent[index1]->ctag;
	tag1 = m_vecSent[index1]->tag;
	word1 = m_vecSent[index1]->word;
	pretag = GetPreTag(index1);

	ctag2 = m_vecSent[index2]->ctag;
	tag2 = m_vecSent[index2]->tag;
	word2 = m_vecSent[index2]->word;
	nexttag = GetNextTag(index2);

	string strDist = GetDistance(index1, index2);		// 搭配之间的距离
	string strPunct = GetPunct(index1, index2);		// 搭配之间的标点信息

	ww = word1 + '_' + word2;
	wt = word1 + '_' + strPunct +'_' + tag2;
	tw = tag1 + '_' + strPunct + '_' + word2;
	tt = tag1 + '_' + strPunct + '_' + tag2;
	td = ctag1 + '_' + strPunct + '_' + ctag2 + '_' + strDist;
	tttt = pretag + '_' + ctag1 + '_' + strPunct + '_' + ctag2 + '_' + nexttag;
}

//找到某一序列的所有可能关系及其概率，加入候选关系概率表中
void CParser::FindCandidate(vector < PROB >& vecProb, string sequence, int num)
{
	vector < PROB > ::iterator it_Prob;
	vector < pair < string, float> > ::iterator it_Rel;

	ITEM *pItem = hash.Lookup(sequence.c_str() );
	while(pItem != NULL && strcmp(pItem->key,sequence.c_str() ) == 0)
	{
		string relation = pItem->relation;
		float prob = pItem->prob;
		pItem = pItem->pNext;

		it_Prob = find(vecProb.begin(), vecProb.end(), relation);
		if(it_Prob == vecProb.end())
		{
			PROB myProb(relation);
			myProb.SetProb(num,prob);
			vecProb.push_back(myProb);
		}
		else
		{
			it_Prob->SetProb(num,prob);
		}
	}
}

float CParser::Smoothen(float ftd, float ftt, float ftttt, float ftw, float fwt, float fww)
{
	//int n = (ftttt > 0) + (ftw > 0) + (fwt > 0) + (fww > 0) + (ftt > 0) + (ftd > 0);
	//float fProb = (ftttt+ftw+fwt+fww+ftt+ftd)/n;
	//float fProb = (ftttt+ftw+fwt+fww+ftt+ftd)/6;
	float fProb = 0.3f*ftt + 0.25f*ftttt + 0.15f*ftw + 0.15f*fwt + 0.15f*fww;
	if (fProb <= 0.00000001) fProb = 0.00000001;
	return fProb;
}

float CParser::GetProb(float fProb, string relation, int index1, int index2)
{
//	if(index2-index1 == 1 || index1-index2 == 1) // 两个节点相邻，还未有其他节点生成，不考虑二元关系概率
		return -log(fProb);
/*
	float fprob_lchild, fprob_rchild, fprob_head;
	int nDirect = GetDirect(relation);
	if(nDirect == LEFT)
	{
		GetChildBigram(index2,relation,fprob_lchild,fprob_rchild);
		GetHeadBigram(index1,relation,nDirect,fprob_head);
	}
	else
	{
		GetChildBigram(index1,relation,fprob_lchild,fprob_rchild);
        GetHeadBigram(index2,relation,nDirect,fprob_head);
	}

	if(fprob_lchild == 0)
		fprob_lchild = MINPROB;
	if(fprob_rchild == 0)
		fprob_rchild = MINPROB;
	if(fprob_head == 0)
		fprob_head = MINPROB;

	fProb = -log(fProb) - log(fprob_lchild) - log(fprob_rchild) - log(fprob_head);
	return fProb;
*/
}

// check the validiity of the ith element in the vector 
bool CParser::Check(int i)
{
	int index1 = m_vecPair[i].index1;
	int index2 = m_vecPair[i].index2;
	float prob = m_vecPair[i].prob;
	string relation = m_vecPair[i].relation;
	string tag1 = m_vecSent[index1]->tag;
	string tag2 = m_vecSent[index2]->tag;

	int nLeftDegree1, nRightDegree1;
	int nLeftDegree2, nRightDegree2;
	GetGovernDegree(index1, nLeftDegree1, nRightDegree1);
	GetGovernDegree(index2, nLeftDegree2, nRightDegree2);

	int nPos_Left, nPos_Right;
	FindLeftNode(index1,nPos_Left);
	FindRightNode(index2,nPos_Right);

	int nDirect = GetDirect(relation);
	if(nDirect == RIGHT)
	{
		if(nPos_Left >= 0)						// there is a unredunced node between 0 and i 
		{
			float preProb = m_vecPair[nPos_Left].prob;
			if(prob > preProb)				// previous pair is blocked, stopping current pair
				return 0;

			string preRelation = m_vecPair[nPos_Left].relation;
			int preDirect = GetDirect(preRelation);
			if(preDirect == RIGHT && prob > 0.75*preProb)	// the prob of pre pair is a bit less than current 
				return 0;
		}
		if(tag1 == "p" && nRightDegree1 == 0 && nPos_Right >= 0)
			return 0;
		if(tag1 == "ue" && nLeftDegree1 == 0)
			return 0;
	}
	else
	{
		if( (tag2 == "ue" || tag2 == "p") && nPos_Right >= 0 )
			return 0;
	}

	return 1;
}


int CParser::FindPair()
{
	int delay = -1;
	int wait = -1;
	int block = -1;
	int i;
	for(i = 0; i < (int)m_vecPair.size(); i++)
	{
		if(block != 1 && m_vecPair[i].block == 1)
			block = i;
		if(wait != 0 && m_vecPair[i].wait == 1)
			wait = i;
		if(delay != 1 && m_vecPair[i].delay == 1)
			delay = i;
	}
	if(delay >= 0)
		return delay;
	if(wait >= 0)
		return wait;
	if(block >= 0)
		return block;
	else
		return 0;
}

void CParser::GetGovernDegree(int index, int& nLeftDegree, int& nRightDegree)
{
	nLeftDegree = (int)m_vecSent[index]->lchild.size();
	nRightDegree = (int)m_vecSent[index]->rchild.size();
}

//output the dependecy pair
void CParser::PrintPair(int parent, int child, string strRelation)
{
	int id1 = m_vecSent[parent]->id;
	int id2 = m_vecSent[child]->id;
	string first = '[' + itos(id1) + ']' + m_vecSent[parent]->word;
	string second = '[' + itos(id2) + ']' + m_vecSent[child]->word;

	int pos = strRelation.find("=");
	strRelation = strRelation.substr(0,pos);
	string relation = '(' + strRelation + ')' + "\t\t";
	m_strResult += first + '_' + second + relation;

	// label the symmetric punctuation
	SetSymmetryPunct(child);
	SetSymmetryPunct(parent);

	m_vecSent[child]->relation = strRelation;
	m_vecSent[child]->mark = 1;		// this node has been recognized
	
	if(parent > child)
	{
		//child node is left, link it with its parent
		m_vecSent[parent]->lchild.push_back(m_vecSent[child]);
		SetPunct(child,parent);
	}
	else
	{
		//child node is right, link it with its parent
		m_vecSent[parent]->rchild.push_back(m_vecSent[child]);
		SetPunct(parent,child);
	}
}

// label the symmetric punctuation besides the index
void CParser::SetSymmetryPunct(int index)
{
	int i = index-1;
	while(i > 0 && m_vecSent[i]->mark == 1)
		i--;
	if(IsLeftPunct(m_vecSent[i]->word) )
	{
		unsigned int j = index+1;
		while(j < m_vecSent.size() && m_vecSent[j]->mark == 1)
			j++;
		if(j < m_vecSent.size() && IsRightPunct(m_vecSent[j]->word) )
		{
			m_vecSent[i]->mark = 1;
			m_vecSent[j]->mark = 1;
		}
	}
}

// label the punctuations between parent and child
void CParser::SetPunct(int beg, int end)
{
	for(int i = beg+1; i < end; i++)
	{
		//mark the punctuation between two recognized nodes, to remove it
		if(m_vecSent[i]->tag == "wp")
			m_vecSent[i]->mark = 1;
	}
}

int CParser::GetDirect(string relation)
{
	int pos = relation.find("=");
	string direction = relation.substr(pos+1);
	if(direction == "R")
		return RIGHT;
	else
		return LEFT;
}

int CParser::GetLevel(string relaiton)
{
	string level_1 = "LAD RAD SIM MT QUN DE DI DEI CNJ";
	string level_2 = "ATT ADV APP COO BA BEI POB CMP";
	string level_3 = "SBV VOB VV";
	string level_4 = "IC DC IS";

	//if(level_1.find(relaiton) != -1)
	//	return 0;
	//if(level_2.find(relaiton) != -1)
	//	return 1;
	//if(level_3.find(relaiton) != -1)
	//	return 2;
	//if(level_4.find(relaiton) != -1)
	//	return 3;
	//else
		return 0;
}

string CParser::IntToStr(int number)
{
	char buf[4];
	itoa(number,buf,10);
	return buf;
}

// Loading parsing resource
void CParser::Initialize()
{
	LoadModel();
	phrase.LoadVerb();
}

void CParser::Release()
{
	hash.RemoveAll();
}

void CParser::LoadModel()
{
	ifstream fin( (g_strDataPath+"Model.txt").c_str() );
	if(!fin)
	{
		cout << "Cannot open model file!" << endl;
		exit(0);
	}
	string strLine;

	hash.InitHashTable(TABLESIZE);
	while(!fin.eof() )
	{
		getline(fin, strLine);
		int pos1 = strLine.find('\t');
		string key = strLine.substr(0, pos1);
		int pos2 = strLine.find('\t',pos1+1);
		string relation = strLine.substr(pos1+1, pos2-pos1-1);
		float prob = (float)atof(strLine.substr(pos2+1).c_str() );

		hash.SetAt(key.c_str(), relation.c_str(), prob);
	}
}

void CParser::LoadDegree(string strFileDegree, map < string, pair < int, float > >& mapDegree)
{
	ifstream fin;
	fin.open(strFileDegree.c_str());
	if(!fin)
	{
		cout << "Cannot open input file: " << strFileDegree << endl;
		exit(0);
	}

	string strDegree, tag;
	string::size_type pos = 0;
	while(!fin.eof())
	{
		getline(fin,strDegree);		// Nab 2	0.1119

		pos = strDegree.find(' ');
		tag = strDegree.substr(0,pos);
		strDegree = strDegree.substr(pos+1);

		pos = strDegree.find('\t');
		int nDegree = atoi(strDegree.substr(0,pos).c_str() );
		if(nDegree == 0)
			continue;
		float fProb = (float)atof(strDegree.substr(pos+1).c_str() );

		//if(fProb > 0.90 || fProb > 0.85 && tag[0] != 'V')
		if(fProb > 0.85)
		{
			pair < int, float > myPair(nDegree, fProb);
			mapDegree[tag] = myPair;
		}
	}
}

bool CParser::IsUnknown(string tag)
{
	if(tag == "ws" || tag == "m" || tag == "j" || tag == "ni" 
		|| tag == "nh" || tag == "ns" || tag == "nz" || tag == "nt" || tag == "EOS")
		return true;
	else
		return false;
}


int CParser::FindPunct(int index1, int index2)
{
	for(int i = index1+1; i < index2; i++)
	{
		string word = m_vecSent[i]->word;
		string tag = m_vecSent[i]->tag;

		if(tag != "wp" || m_vecSent[i]->mark)
			continue;
		else if(word == "，")
			return 1;
		else if(word == "：")
			return 2;
		else if(word.find("——") != -1)
			return 3;
		else if(word == "、")
			return 4;
		else if(IsLeftPunct(word) )
			return 6;
		else if(IsRightPunct(word) )
			return 9;
		else
			return 5;
	}

	return 0;
}

bool CParser::IsLeftPunct(string word)
{
	if(word == "“" || word == "《" || word == "（" || word == "‘")
		return 1;
	else
		return 0;
}

bool CParser::IsRightPunct(string word)
{
	if(word == "”" || word == "》" || word == "）" || word == "’")
		return 1;
	else
		return 0;
}

// 寻找节点index的前一个节点并返回，其依存对在向量中的位置放入nPos中
int CParser::FindLeftNode(int index, int& nPos)
{
	unsigned int i = 0;
	for(i = 0; i < m_vecPair.size(); i++)
	{
		if(m_vecPair[i].index2 == index)	// 重叠的位置
		{
			nPos = i;						// 前一个依存对在向量中的位置
			return m_vecPair[i].index1;		// 前一个节点
		}
	}

	nPos = -1;								// 向量中没有同该节点相关联的依存对
	return -1;
}

// 寻找节点index的下一个节点并返回，其依存对在向量中的位置放入nPos中
int CParser::FindRightNode(int index, int& nPos)
{
	unsigned int i = 0;
	for(i = 0; i < m_vecPair.size(); i++)
	{
		if(m_vecPair[i].index1 == index)	// 重叠的位置
		{
			nPos = i;						// 下一个依存对在向量中的位置
			return m_vecPair[i].index2;		// 下一个节点
		}
	}

	nPos = -1;								// 向量中没有同该节点相关联的依存对
	return -1;
}

// normalize distance: 1, 2, 3, and 4
// 1: 1
// 2: 2
// 3: 3~6
// 4: 7~, <EOS>
string CParser::GetDistance(int index1, int index2)
{
	assert(index1 < index2);

	int nDist;
	nDist = index2 - index1;
	if(3 <= nDist && nDist <= 6)
		nDist = 3;
	if(nDist > 6 || index2 == m_nDataSize-1)	// 和<EOS>的搭配距离记为“4
		nDist = 4;

	char buffer[4];
	itoa(nDist,buffer,10);
	return buffer;
}

// 两个词之间的标点情况, 句子核心词和EOS之间的标点不计在内
string CParser::GetPunct(int index1, int index2)
{
	assert(index1 < index2);
	if(index2 == m_nDataSize-1)	// EOS
		return "0";

	int i;
	for(i = index1+1; i < index2; i++)
	{
		string word = m_vecSent[i]->word;
		if(word == "：") 
			return "1";
	}

	for(i = index1+1; i < index2; i++)
	{
		string word = m_vecSent[i]->word;
		if(word == "，") 
			return "2";
	}

	for(i = index1+1; i < index2; i++)
	{
		string word = m_vecSent[i]->word;
		if(word == "——") 
			return "3";
	}

	for(i = index1+1; i < index2; i++)
	{
		string word = m_vecSent[i]->word;
		if(word == "、") 
			return "4";
	}

	for(i = index1+1; i < index2; i++)
	{
		string tag = m_vecSent[i]->tag;
		if(tag == "wp")	// 其他标点
			return "5";
	}

	return "0"; // no punct
}


string CParser::GetPreTag(int index1)
{
	assert(index1 >= 1);

	index1--;
	return m_vecSent[index1]->ctag;
}

string CParser::GetNextTag(int index2)
{
	assert(index2 <= m_nDataSize-1);

	index2++;
	if(index2 == m_nDataSize) // the node is EOS
		return "<EOS>";
	else
		return m_vecSent[index2]->ctag;
}

string CParser::GetRelation(int index1, int index2)
{
	return "(HED)";
}

bool CParser::IsCommonWord(string tag)
{
	if(tag == "ws" || tag == "nh" || tag== "ns" || tag== "<EOS>") // || tag=="nz"||tag=="ni"||tag=="m"
		return false;
	else
		return true;
}

bool CParser::IsPunct(int id)
{
	if(m_vecSent[id]->tag == "wp")	
		return true;
	else
		return false;
}

void CParser::OutputVector()
{
	vector < PAIR > ::iterator iter = m_vecPair.begin();
	for(; iter != m_vecPair.end(); iter++)
	{
		string ctag1 = m_vecSent[(*iter).index1]->tag;
		string ctag2 = m_vecSent[(*iter).index2]->tag;
		fout << (*iter).index1 << "--" << m_vecSent[(*iter).index1]->word << "/" << ctag1 << "\t\t" 
			<< (*iter).index2 << "--" << m_vecSent[(*iter).index2]->word << "/" << ctag2 << "\t\t"
			<< (*iter).relation << "\t\t" << (*iter).prob << "\t\t" << "delay is " << iter->delay 
			<< "\t\t" << "wait is " << iter->wait << "\t\t" << "block is " << iter->block << endl;
	}
	fout << endl;
}

void CParser::ShowSent()
{
	fout << endl << "================================" << endl;
	vector < DATA* > ::iterator it;
	for(it = m_vecSent.begin(); it != m_vecSent.end(); it++)
	{
		string word = (*it)->word;
		fout << word << ' ';
	}
}