/////////////////////////////////////////////////////////////////////////////////////
// File Name   : HMM.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Time        : 2005.6
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _HMM_H_
#define _HMM_H_
#include "Graph.h"

/////////////////////////////////////////////////////////////////////////////////////
// Class      : HMM
// Author     : Huipeng Zhang
// Description: this class provides operations related to HMM, for a given word index
//              path, it generates the best state sequence, it also provides emit and
//              trans probability given the state tag and the word index.
// Relations  : class Person, Location and POSTag has a pointer to this class
// Time       : 2005.6
// History    : 
/////////////////////////////////////////////////////////////////////////////////////
class HMM
{
public:
	HMM(){}
	int loadHMMSeg(const char* emitFileName, const char* transFileName,
		           const char* tagsFileName, int tagNum);
	//HMM(const char* emitFileName, const char* transFileName, const char* tagsFileName, int tagNum);
	void HMMTag(vector<int>& wordIndexPath, vector<string>& bestStateSequence);
	float GetEmitProb(int wordIndex, string& stateTag);
	float GetTransProb(string& stateTag1, string& stateTag2);
	
private:
	void InitHMM(vector<int>& wordIndexPath);
	void Viterbi();
	int GetLastStateSuffix();
	void GenerateBestStateSequence(vector<string>& bestStateSequence);
	int GetStateIndex(string& stateTag);
	int LoadTrans(const char* fileName, int stateNum);
	int LoadEmit(const char* fileName);	
	int LoadState(const char* fileName, int stateNum);
	
private:
	struct EmitNode
	{
		short stateIndex;    
		float emitProb;
	};
	
	struct PathNode
	{
		float accumProb; //the accumulate probability to current node
		int preSuffix; //the preceding state node's position in its array, initial it is -1
		int stateIndex; //the index of current state
	};

private:
	int senWordNum; //the number of words in a sentence
	vector< vector<PathNode> > pathList;
	vector<string> state;
	vector<float> start;
	vector< vector<float> > trans;
	vector< vector<EmitNode> > emit;
};

#endif

