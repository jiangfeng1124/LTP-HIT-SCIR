 
#include "Parser_dll.h"
#include <iostream>

void Extract(string strPair, int& parent, int& child, string& relation);

int Parser(vector < string >& vecWord, vector < string >& vecPOS, vector < pair<int,string> >& vecParse)
{
	int nChar = 0;
	int i = 0;
	for (; i < vecWord.size(); ++i) {
//		cout << i << "\t" << vecWord[i] << "\t" << strlen(vecWord[i].c_str()) << endl;
		nChar += strlen(vecWord[i].c_str());
	}
	const int SZ = nChar * 2 + vecWord.size() * 32;
	char * csOutput = new char[SZ];

	// Call dll
	if (0 != GetParseResults(vecWord, vecPOS, csOutput)) return -1;
	string strOutput = csOutput;

	// Initialization
	vecParse.clear();
	pair < int, string > myPair;

	myPair.first = -2;			// the parent of punctuation, defined as -1 or -2, 
	myPair.second = "PUN";		// punctuation

	for(i = 0; i < (int)vecWord.size(); i++)
	{
		vecParse.push_back(myPair);
	}
	
	// convert output "[6]遇_[8]铁刷把(VOB)		[5]有_[10]时候(OBJ)		[12]<EOS>_[5]有(HED)		"
	size_t nPos1 = 0;
	size_t nPos2 = strOutput.find("\t\t");
	while(nPos2 != -1)
	{
		int parent, child;
		string relation;

		string strPair = strOutput.substr(nPos1, nPos2-nPos1);
		Extract(strPair,parent,child,relation);
		vecParse[child].first = parent;
		vecParse[child].second = relation;

		nPos1 = nPos2 + 2;
		nPos2 = strOutput.find("\t\t",nPos1);
	}
	delete []csOutput;
	return 0;
}

int Parser_with_postag(vector < string >& vecWord, vector<string> &vecCPOS, vector < string >& vecPOS, vector < pair<int,string> >& vecParse)
{
	int nChar = 0;
	int i = 0;
	for (; i < vecWord.size(); ++i) {
		//		cout << i << "\t" << vecWord[i] << "\t" << strlen(vecWord[i].c_str()) << endl;
		nChar += strlen(vecWord[i].c_str());
	}
	const int SZ = nChar * 2 + vecWord.size() * 32;
	char * csOutput = new char[SZ];

	// Call dll
	if (0 != GetParseResults_with_postag(vecWord, vecCPOS, vecPOS, csOutput)) return -1;
	string strOutput = csOutput;

	// Initialization
	vecParse.clear();
	pair < int, string > myPair;

	myPair.first = -2;			// the parent of punctuation, defined as -1 or -2, 
	myPair.second = "PUN";		// punctuation

	for(i = 0; i < (int)vecWord.size(); i++)
	{
		vecParse.push_back(myPair);
	}

	// convert output "[6]遇_[8]铁刷把(VOB)		[5]有_[10]时候(OBJ)		[12]<EOS>_[5]有(HED)		"
	size_t nPos1 = 0;
	size_t nPos2 = strOutput.find("\t\t");
	while(nPos2 != -1)
	{
		int parent, child;
		string relation;

		string strPair = strOutput.substr(nPos1, nPos2-nPos1);
		Extract(strPair,parent,child,relation);
		vecParse[child].first = parent;
		vecParse[child].second = relation;

		nPos1 = nPos2 + 2;
		nPos2 = strOutput.find("\t\t",nPos1);
	}
	delete []csOutput;
	return 0;
}

void Extract(string strPair, int& parent, int& child, string& relation)
{
	size_t nPos1 = strPair.find('[');
	size_t nPos2 = strPair.find(']',nPos1+1);
	parent = atoi(strPair.substr(nPos1+1,nPos2-nPos1-1).c_str());
	parent--;

	nPos1 = strPair.find("_[", nPos2+1);
	nPos2 = strPair.find(']', nPos1+2);
	child = atoi(strPair.substr(nPos1+2,nPos2-nPos1-2).c_str());
	child--;

	nPos1 = strPair.rfind('(');
	nPos2 = strPair.rfind(')');
	relation = strPair.substr(nPos1+1,nPos2-nPos1-1);
	
	if(strPair.find("EOS") != -1)
	{
		parent = -1;	// parent of root, defined as 0 or -1
	}
}

