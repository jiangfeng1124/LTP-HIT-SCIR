/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Parser.h
// Author      : Ma Jinshan (mjs@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Time        : 2006.6
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2006, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////

#ifndef _DEPENDENCY_PARSER_
#define _DEPENDENCY_PARSER_

#define LEFT 1
#define RIGHT -1
#define MINPROB 0.00001f
#define MAXPROB 1000
#define THRESHOLD 0.6f
#define TABLESIZE 2000000
#define LAMDA  0.3f
#define LAMDA1 0.8f
#define LAMDA2 0.2f
#define LAMDA3 0.1f
#define LAMDA4 0.1f

#define STL_USING_ALL
#include "stl.h"
#include "MyLib.h"
#include "Hash.h"
#include "Phrase.h"
#include "Compound.h"
#include "Node.h"

extern string g_strDataPath;

class CParser
{
public:
	CParser();
	virtual ~CParser();
	void Initialize();
	void ParseFile(string strInputFile, string strOutputFile);
	int ParseSent(vector <string> & vecSent, string &strParseResult);
	void Release();
	string m_strSent1, m_strSent2, m_strResult;

private:
	void Parse();
	int GetRawSent(vector <string> & vecSent);
	void SetSentInfo(vector <string> & vecSent);
	void SetGovernDegree(DATA *data, string tag);
	void ResetSentInfo();
	void LoadModel();
	void LoadUnigram(string strFileName, map < string, vector < pair < string,float > > >& m_mapRelation);
	void LoadBigram(string strFileName, map < string, float >& myMap);
	void LoadDegree(string strFileDegree, map < string, pair < int, float > >& mapDegree);
	void PrintPair(int parent, int child, string strRelation);
	void SetPunct(int beg, int end);
	void SetSymmetryPunct(int index);
	string IntToStr(int number);

	//Recognize terminal nodes
	void CreateLeaf(int i);
	void ReduceLeaf();
	bool Check(int i);
	int FindPair();
	string GetRelation(int index1, int index2, float& fProb);
	float GetProb(float fProb, string relation, int index1, int index2);
//	void GetChildBigram(int index, string relation, float& lprob, float& rprob);
//	void GetHeadBigram(int index, string relation, int nDirect, float& prob);
	void GetGovernDegree(int index, int& nLeftDegree, int& nRightDegree);
	void GetPair(int index1, int index2, PAIR& myPair);
	int GetDirect(string relation);
	int GetLevel(string relaiton);
	void GetSequence(string& ww, string& wt, string& tw, string& tt, string& tttt, string& td, int index1, int index2);
	string Combine(string first, int nPunct, string second);
	float Smoothen(float td, float ftt, float ftttt, float ftw, float fwt, float fww);
	int FindLeftNode(int index, int& nPos);
	int FindRightNode(int index, int& nPos);
	int FindPunct(int index1, int index2);
	void FindCandidate(vector < PROB >& vecProb, string sequence, int num);
	bool IsUnknown(string tag);
	bool IsLeftPunct(string word);
	bool IsRightPunct(string word);
	bool IsBlock(int i);

	void OutputVector();
	void ShowSent();

	string GetDistance(int index1, int index2);
	string GetPunct(int index1, int index2);
	string GetPreTag(int index1);
	string GetNextTag(int index2);
	string GetRelation(int index1, int index2);

	bool IsPunct(int id);
	bool IsCommonWord(string tag);


	//reference to other class
	CPhrase phrase;
	CCompound compound;
	CHash hash;
	
	int m_nPreDirect;
	int m_nDataSize;

	vector < DATA* > m_vecSent;
	vector < PAIR > m_vecPair;
	vector < pair < int, int > > m_vecNc;
//	map < string, vector < pair < string,float > > > m_mapRelation;
	map < string, vector < pair < string,float > > > m_mapRelation_TD;
	map < string, vector < pair < string,float > > > m_mapRelation_TT;
	map < string, vector < pair < string,float > > > m_mapRelation_4T;
	map < string, vector < pair < string,float > > > m_mapRelation_TW;
	map < string, vector < pair < string,float > > > m_mapRelation_WT;
	map < string, vector < pair < string,float > > > m_mapRelation_WW;
	map < string, pair < int, float > > m_mapLeftDegree, m_mapRightDegree;

	map < string, float > m_mapHead;
	map < string, float > m_mapLeftChild;
	map < string, float > m_mapRightChild;
	ofstream fout; 
};


#endif