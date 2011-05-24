/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Person.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Time        : 2005.6
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _PERSON_H_
#define _PERSON_H_
#include "HMM.h"

/////////////////////////////////////////////////////////////////////////////////////
/// recognize persons in a sentence and add them to the segment graph.
/////////////////////////////////////////////////////////////////////////////////////
extern HMM* pHmm[3];

class Person
{
public:	
	//Person(HMM* p) : pHmm(p) {}
	Person(){}
	void PersonRecg(Graph& graph, vector<string>& vecAtoms);
	
private:
	void AddPerson(vector<int>& indexPath, vector<int>& nodePath, 
				   Graph& graph, vector<string>& vecAtoms);
	void ConvertIndexPath(vector<int>& inIndexPath, vector<int>& outIndexPath, 
		                  vector<string>& vecAtoms, vector<int>& nodePath);
	float ComputeClassProb(vector<int>& indexPath, int begIdx, int& endIdx);
	int IsChineseName(int begIdx, int& endIdx);
	int IsForeignName(int begIdx, int& endIdx, vector<int>& nodePath, vector<string>& vecAtoms);

private:
	//HMM* pHmm; ///< points to the class HMM
	vector<string> bestRoleSequence; ///< the best person role sequence, from which we can
									 ///< find all the persons in the sentence
};

#endif

