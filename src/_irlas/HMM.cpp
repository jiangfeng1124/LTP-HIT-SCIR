/////////////////////////////////////////////////////////////////////////////////////
// File Name   : HMM.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the implementation of the class HMM
// Time        : 2005.6
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "HMM.h"
//#include <time.h>
//#include <conio.h>

/////////////////////////////////////////////////////////////////////////////////////
// Function   : HMM
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: load emit, trans, and state file
// Time       : 2005.9
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
/*
HMM::HMM(const char* emitFileName, const char* transFileName, const char* tagsFileName, int tagNum)
{
	LoadEmit(emitFileName);
	LoadTrans(transFileName, tagNum);
	LoadState(tagsFileName, tagNum);
}*/

int HMM::loadHMMSeg(const char* emitFileName, const char* transFileName,
					const char* tagsFileName, int tagNum)
{
//	printf("begin of HMM::loadHMMSeg(%s). Enter key...\n", emitFileName);
//	_getch();
//	clock_t start = clock();
	int flagEmit = LoadEmit(emitFileName);
//	printf("end of HMM::LoadEmit. time: %f. Enter key...\n", float(clock()-start)/CLOCKS_PER_SEC);
//	_getch();
//	start = clock();
    int flagTrans = LoadTrans(transFileName, tagNum);
//	printf("end of HMM::LoadTrans. time: %f. Enter key...\n", float(clock()-start)/CLOCKS_PER_SEC);
//	_getch();
//	start = clock();	
	int flagState = LoadState(tagsFileName, tagNum);
//	printf("end of HMM::LoadState. time: %f. Enter key...\n", float(clock()-start)/CLOCKS_PER_SEC);
//	_getch();	

	if (flagEmit && flagTrans && flagState)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/////////////////////////////////////////////////////////////////////////////////////
// Function   : HMMTag
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: given a word index path, generate the best state sequence according 
//              to HMM model
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
void HMM::HMMTag(vector<int>& wordIndexPath, vector<string>& bestStateSequence)
{
	senWordNum = wordIndexPath.size();
	if (senWordNum > 0) 
	{
		InitHMM(wordIndexPath);
		Viterbi();
		GenerateBestStateSequence(bestStateSequence);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : GetEmitProb
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: 
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
float HMM::GetEmitProb(int wordIndex, string& stateTag)
{
	int stateNum = emit[wordIndex].size();
	for (int i = 0; i < stateNum; i++) 
	{
		int stateIndex = emit[wordIndex][i].stateIndex;
		if (state[stateIndex] == stateTag) 
		{
			return emit[wordIndex][i].emitProb;
		}
	}
	cout << "error in HMM::GetEmitProb!" << endl; //just for debug
	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : GetTransProb
// Class      : HMM
// Author     : Paul Zhang
// Caller     : 
// Description: 
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
float HMM::GetTransProb(string& stateTag1, string& stateTag2)
{
	int stateIndex1 = GetStateIndex(stateTag1);
	int stateIndex2 = GetStateIndex(stateTag2);
	return trans[stateIndex1][stateIndex2];
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : GetStateIndex
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : GetTransProb
// Description: 
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
int HMM::GetStateIndex(string& stateTag)
{
	for (unsigned int i = 0; i < state.size(); i++) 
	{
		if (state[i] == stateTag) 
		{
			return i;
		}
	}
	cout << "error in HMM::GetStateIndex!" << endl;
	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : InitHMM
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: allocte memory for pathList and initialize it
//              NOTE: every item in wordIndexPath must exist in the emit file
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
void HMM::InitHMM(vector<int>& wordIndexPath)
{
	pathList.resize(senWordNum);
	
	for(int i = 0; i < senWordNum; i++) 
	{
		int wordIndex = wordIndexPath[i];
		int stateNum = emit[wordIndex].size(); 
		pathList[i].resize(stateNum);

		for(int j = 0; j < stateNum; j++)
		{
			pathList[i][j].preSuffix = -1; //the initial is -1
			pathList[i][j].stateIndex = emit[wordIndex][j].stateIndex;	
			pathList[i][j].accumProb = emit[wordIndex][j].emitProb;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : Viterbi
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: Viterbi procedure
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
void HMM::Viterbi() 
{
	for (unsigned int t = 0; t < pathList[0].size(); t++) 
	{
		pathList[0][t].accumProb += start[pathList[0][t].stateIndex];
	}
	
	float tempProb;
	float curEmit;
	
	for (int i = 1; i < senWordNum; i++) //the i-th word
	{
		for (unsigned int j = 0; j < pathList[i].size(); j++) //the j-th state of i-th word
		{
			curEmit = pathList[i][j].accumProb;
			pathList[i][j].accumProb = FLT_MAX;

			for (unsigned int k = 0; k < pathList[i-1].size(); k++) 
			{                                            //the k-th state of preceding word
				int preIndex = pathList[i-1][k].stateIndex; 
				int	curIndex = pathList[i][j].stateIndex;

				tempProb = curEmit + pathList[i-1][k].accumProb + trans[preIndex][curIndex];
				if (tempProb < pathList[i][j].accumProb) 
				{
					pathList[i][j].accumProb = tempProb;
					pathList[i][j].preSuffix = k;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : GetLastStateSuffix
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : GenerateBestStateSequence
// Description: find the position that has the minimum accumProb in the last node array
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
int HMM::GetLastStateSuffix() 
{
	float tempProb = FLT_MAX;
	int lastStateSuffix;
	int lastNodeArraySize = pathList[senWordNum-1].size();
	for (int i = 0; i < lastNodeArraySize; i++) 
	{
		if (pathList[senWordNum-1][i].accumProb < tempProb) 
		{
			tempProb = pathList[senWordNum-1][i].accumProb;
			lastStateSuffix = i;
		}
	}
	return lastStateSuffix;
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : GenerateBestStateSequence
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: generate the best state sequence from pathList
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
void HMM::GenerateBestStateSequence(vector<string>& bestStateSequence)
{
	int lastStateSuffix = GetLastStateSuffix();

	for (int i = senWordNum-1, j = lastStateSuffix; i >= 0; i--) 
	{
		int stateIndex = pathList[i][j].stateIndex;
		bestStateSequence.push_back(state[stateIndex]);
		j = pathList[i][j].preSuffix;
	}
	reverse(bestStateSequence.begin(), bestStateSequence.end());
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : LoadState
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: 
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
int HMM::LoadState(const char* fileName, int stateNum)
{
	state.resize(stateNum);
	ifstream in(fileName);
	if (!in) 
	{
		cerr << "can't open the file " << fileName << " !" << endl;
		return 0;
	}
	for (int i = 0; i < stateNum; i++) 
	{
		in >> state[i];
	}
	in.close();

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : LoadTrans
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: 
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
int HMM::LoadTrans(const char* fileName, int stateNum)
{
	trans.resize(stateNum);
	for (int m = 0; m < stateNum; m++) 
	{
		trans[m].resize(stateNum);
	}
	start.resize(stateNum);

	ifstream in(fileName);
	if (!in) 
	{
		cerr << "can't open the file " << fileName << " !" << endl;
		return 0;
	}

	for(int i = 0; i < stateNum; i++) //load trans
	{
		for(int j = 0; j < stateNum; j++)
		{
			in >> trans[i][j] ;
		}		
	}
		
	for (int k = 0; k < stateNum; k++) //load start
	{
		in >> start[k];
	}

	in.close();
	 
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////
// Function   : LoadEmit
// Class      : HMM
// Author     : Huipeng Zhang
// Caller     : 
// Description: 
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
int HMM::LoadEmit(const char* fileName)
{
//	printf("begin of HMM::LoadEmit(%s). Enter key...\n", fileName);
//	_getch();
//	clock_t start = clock();

	FILE* fp = fopen(fileName, "rb");
//	char buf[100];
//	sprintf(buf, "%s_", fileName);
//	FILE* fp2 = fopen(buf, "w");
	if (fp == NULL) 
	{
		cerr << "can't open the file " << fileName << " !" << endl;
		return 0;
	}
	int lineNum;
	fread(&lineNum, sizeof(int), 1, fp); 
//	fprintf(fp2, "%d\n", lineNum);
	emit.resize(lineNum);
	for (int i = 0; i < lineNum; i++)
	{
		short stateNum;
		fread(&stateNum, sizeof(short), 1, fp);
//		fprintf(fp2, "%d: ", stateNum);
		emit[i].resize(stateNum);
		for (int j = 0; j < stateNum; j++) 
		{
			fread(&emit[i][j].stateIndex, sizeof(short), 1, fp); 
			fread(&emit[i][j].emitProb, sizeof(float), 1, fp);
//			fprintf(fp2, "%d_%f ", emit[i][j].stateIndex, emit[i][j].emitProb);
		}
//		fprintf(fp2, "\n");
	}
	fclose(fp);
//	fclose(fp2);

//	printf("end of HMM::LoadEmit. time: %f. Enter key...\n", float(clock()-start)/CLOCKS_PER_SEC);
//	_getch();

	return 1;
}

