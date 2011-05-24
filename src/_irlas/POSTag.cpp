/////////////////////////////////////////////////////////////////////////////////////
// File Name   : POSTag.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Time        : 2005.7
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "POSTag.h"

//extern HMM* pHmm[3];
/////////////////////////////////////////////////////////////////////////////////////
/// POS tagging.
/////////////////////////////////////////////////////////////////////////////////////
void POSTag::POSTagging(Graph& graph, vector<string>& bestTagSequence)
{
	vector<int> outPath;
	ConvertIndexPath(graph.NBestIndexPath[0], outPath);
	pHmm[2]->HMMTag(outPath, bestTagSequence);
	outPath.clear();
}

/////////////////////////////////////////////////////////////////////////////////////
/// convert the word index path to index path used in POS tagging.
/////////////////////////////////////////////////////////////////////////////////////
void POSTag::ConvertIndexPath(vector<int>& inIndexPath, vector<int>& outIndexPath)
{
	assert(outIndexPath.empty());
	for (unsigned int i = 0; i < inIndexPath.size(); i++) 
	{
		if (inIndexPath[i] >= 0 && inIndexPath[i] < WordClassNum) 
		{
			outIndexPath.push_back(inIndexPath[i]);
		}
		else if (inIndexPath[i] == GBStringIndex || inIndexPath[i] == ASCIIStringIndex)
		{
			outIndexPath.push_back(WsWordIndex);
		}
		else 
		{
			outIndexPath.push_back(OtherOOVWordIndex);
		}
	}
}


