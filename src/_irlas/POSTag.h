/////////////////////////////////////////////////////////////////////////////////////
// File Name   : POSTag.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Time        : 2005.7
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _POSTAG_H_
#define _POSTAG_H_
#include "HMM.h"

/////////////////////////////////////////////////////////////////////////////////////
/// POS tagging, generate the best POS tag sequence.
/////////////////////////////////////////////////////////////////////////////////////
extern HMM* pHmm[3];

class POSTag
{
public:
	// POSTag(HMM* p) : pHmm(p) {}
	POSTag(){}
	void POSTagging(Graph& graph, vector<string>& bestTagSequence);

private:
	void ConvertIndexPath(vector<int>& inIndexPath, vector<int>& outIndexPath);
	//HMM* pHmm; ///< points to the class HMM
};

#endif



