/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Location.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Time        : 2005.6
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _LOCATION_H_
#define _LOCATION_H_
#include "HMM.h"

/////////////////////////////////////////////////////////////////////////////////////
/// recognize locations in a sentence and add them to the segment graph.
/////////////////////////////////////////////////////////////////////////////////////

extern HMM* pHmm[3];

class Location
{
public:
	//Location(HMM* p) : pHmm(p) {}
	Location(){}
	void LocationRecg(Graph& graph, vector<string>& vecAtoms);
	
private:
	void AddLocation(vector<int>& indexPath, vector<int>& nodePath, Graph& graph);
	void ConvertIndexPath(vector<int>& inIndexPath, vector<int>& outIndexPath, 
		                  vector<string>& vecAtoms, vector<int>& nodePath);
	float ComputeClassProb(vector<int>& indexPath, int begIdx, int& endIdx);

private:
	// HMM* pHmm; ///< points to the class HMM
	vector<string> bestRoleSequence; ///< the best location role sequence, from which we can
									 ///< find all the locations in the sentence
};

#endif


