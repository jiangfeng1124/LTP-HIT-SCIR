/***
	This file is used only under WIN32, because C++ STL can not be used 
		as parameter of dll interface. The problem exists in the allocation and
		collection of STL memory.
	Under Linux, it's useless.
***/


#include "IRLAS_DLL.h"
//#include "MyLib.h"


void IRLAS(void* pSegger, string& line, vector<string>& vecWords)
{
	if (line.empty()) return;
	int len = line.size()+10;
	char** pWord = new char*[len];
	for (int i = 0; i < len; i++)
	{
		pWord[i] = new char[len];
	}
	int wordNum;
	IRLAS_WordSegment_dll(pSegger, (char*)line.c_str(), pWord, wordNum);
	for (int j = 0; j < wordNum; j++)
	{
		vecWords.push_back(pWord[j]);
//		remove_space(vecWords.back());
	}
	for (int k = 0; k < len; k++)
	{
		delete[] pWord[k];
	}
	delete[] pWord;
}