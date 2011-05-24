/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Location.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the implementation of the class Location
// Time        : 2005.6
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "Location.h"

// extern HMM* pHmm[3];

/////////////////////////////////////////////////////////////////////////////////////
/// location recognition.
/////////////////////////////////////////////////////////////////////////////////////
void Location::LocationRecg(Graph& graph, vector<string>& vecAtoms)
{
	int pathNum = graph.NBestIndexPath.size();
	vector<int> outIndexPath;

	for (int i = 0; i < pathNum; i++) 
	{
		outIndexPath.clear();
		ConvertIndexPath(graph.NBestIndexPath[i], outIndexPath, vecAtoms, graph.NBestNodePath[i]);
		bestRoleSequence.clear();
		
		pHmm[1]->HMMTag(outIndexPath, bestRoleSequence);
		
		//erase the last period which we add in function ConvertIndexPath
		bestRoleSequence.erase(bestRoleSequence.end()-1);
		outIndexPath.erase(outIndexPath.end()-1);
//		output_vector(bestRoleSequence); //just for debug
		AddLocation(outIndexPath, graph.NBestNodePath[i], graph);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// convert the word index path to index path used in location recognition.
/// the word index path comes from the class Graph.
/////////////////////////////////////////////////////////////////////////////////////
void Location::ConvertIndexPath(vector<int>& inIndexPath, vector<int>& outIndexPath, 
							    vector<string>& vecAtoms, vector<int>& nodePath)
{
	//assert(outIndexPath.empty());
	string atom;
	for (unsigned int i = 0; i < inIndexPath.size(); i++) 
	{
		atom = vecAtoms[nodePath[i]];
		
		if (inIndexPath[i] >= 0 && inIndexPath[i] < WordNum) //is in dictionary
		{
			outIndexPath.push_back(inIndexPath[i]);
		}
		else if (inIndexPath[i] == OOVWordIndex && atom.size() == 2) //single char OOV word
		{
			outIndexPath.push_back(WordNum);
		}
		else if (inIndexPath[i] < 0 || inIndexPath[i] == NumberIndex 
			|| inIndexPath[i] == TimeIndex) //OOV word, number and time
		{
			outIndexPath.push_back(WordNum+1);
		}
		else
		{
			cout << "error in Location::ConvertIndexPath!" <<endl; //just for debug
		}
	}

	outIndexPath.push_back(11); //add a "¡£" at the end of sentence
}

/////////////////////////////////////////////////////////////////////////////////////
/// add all locations to segment graph.
/////////////////////////////////////////////////////////////////////////////////////
void Location::AddLocation(vector<int>& indexPath, vector<int>& nodePath, Graph& graph)
{
	int senRoleNum = bestRoleSequence.size();
	for (int i = 0; i < senRoleNum-1; i++) 
	{
		int endIndex;
		float classProb;
		if (bestRoleSequence[i] == "F") 
		{
			int j;
			for (j = i+1; j < senRoleNum; j++) 
			{
				if (bestRoleSequence[j] != "M") 
					break;
			}
			
			if (j < senRoleNum && bestRoleSequence[j] == "") 
			{
				if (j+1 < senRoleNum && bestRoleSequence[j+1] == "H") //has a postfix
					endIndex = j+1;
				else
					endIndex = j;
				classProb = ComputeClassProb(indexPath, i, endIndex);
				graph.AddWord(nodePath[i], nodePath[endIndex], LocationIndex, classProb);
			}
			else if (j < senRoleNum && bestRoleSequence[j] == "H") 
			{
				classProb = ComputeClassProb(indexPath, i, j);
				graph.AddWord(nodePath[i], nodePath[j], LocationIndex, classProb);
			}
		}
		else if (bestRoleSequence[i] == "Q") 
		{
			if (i+1 < senRoleNum && bestRoleSequence[i+1] == "H") 
				endIndex = i+1;
			else
				endIndex = i;
			classProb = ComputeClassProb(indexPath, i, endIndex);
			graph.AddWord(nodePath[i], nodePath[endIndex], LocationIndex, classProb);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// compute class probability, which is the probability of the string as a location.
/////////////////////////////////////////////////////////////////////////////////////
float Location::ComputeClassProb(vector<int>& indexPath, int begIdx, int& endIdx)
{
	float classProb = 0;
	for (int i = begIdx; i <= endIdx; i++) 
	{
		classProb += pHmm[1]->GetEmitProb(indexPath[i], bestRoleSequence[i]);
		if (i+1 <= endIdx) 
		{
			classProb += pHmm[1]->GetTransProb(bestRoleSequence[i], bestRoleSequence[i+1]);
		}
	}
	return classProb;
}



