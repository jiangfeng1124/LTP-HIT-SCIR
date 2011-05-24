#pragma once
#define STL_USING_ALL
#include "stl.h"
#include "Node.h"
#include <iostream>

extern string g_strDataPath;

class CPhrase
{ 
public:
	CPhrase(void);
	~CPhrase(void);

	void LoadVerb();
	string RecogJuxt(vector < DATA* > & vecSent);	// Recognize simple juxtaposing structures
	string RecogVerb(vector < DATA* > & vecSent);	// Recognize new verbs such as ·´ ºË
	string RecogTime(vector < DATA* > & vecSent);	// Recognize temporal phrase
	string RecogNumber(vector < DATA* > & vecSent);	// Recognize numeral phrase

private:
	void PrintPair(int parent, int child, string strRelation);
	void Mark(int parent, int child);
	void Delete();

	//Recognize simple coordination structures
	bool IsConjunction(int i);
	bool Recognize(int nLeft, int nRight);
	bool IsBoundary(int i);
	bool Like(int nLeft, int nRight);

	//Recognize new verbs such as ·´ ºË
	bool IsFreqVerb(string word);

	vector < DATA* > m_vecSent;
	map < string, int > m_mapVerb;
	string m_strResult;
};
