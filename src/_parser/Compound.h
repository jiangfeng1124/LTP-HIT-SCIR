
#ifndef _NOUN_COMPOUND_
#define  _NOUN_COMPOUND_

#define STL_USING_ALL
#include "stl.h"
#include "Node.h"

class CCompound
{
public:
	CCompound(void);
	~CCompound(void);

	//Recognize Noun Compounds
	string Recognize(vector < DATA* > & vecSent); 

private:
	bool IsHead(int i);
	bool IsModifier(int i);
	bool IsLeftPunct(int i);
	bool IsRightPunct(int i);
	void Analyze(int nLeft, int nRight);
	void PrintPair(int parent, int child, string strRelation);
	void Delete();

	vector < DATA* > m_vecSent;
	string m_strResult;
	ofstream fout;
};

#endif
