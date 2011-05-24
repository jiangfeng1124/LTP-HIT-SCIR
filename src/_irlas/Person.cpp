/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Person.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the implementation of the class Person
// Time        : 2005.6
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "Person.h"
//extern HMM* pHmm[3];

/////////////////////////////////////////////////////////////////////////////////////
/// person recognition.
/////////////////////////////////////////////////////////////////////////////////////
void Person::PersonRecg(Graph& graph, vector<string>& vecAtoms)
{
	int pathNum = graph.NBestIndexPath.size();
	vector<int> outPath;

	for (int i = 0; i < pathNum; i++) 
	{
		outPath.clear();
		ConvertIndexPath(graph.NBestIndexPath[i], outPath, vecAtoms, 
			             graph.NBestNodePath[i]);
		bestRoleSequence.clear();
		pHmm[0]->HMMTag(outPath, bestRoleSequence);
		//erase the last period which we add in function ConvertIndexPath
		bestRoleSequence.erase(bestRoleSequence.end()-1);
		outPath.erase(outPath.end()-1);
//		output_vector(bestRoleSequence); //just for debug
		AddPerson(outPath, graph.NBestNodePath[i], graph, vecAtoms);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// convert the word index path to index path used in person recognition.
/// the word index path comes from the class Graph.
/////////////////////////////////////////////////////////////////////////////////////
void Person::ConvertIndexPath(vector<int>& inIndexPath, vector<int>& outIndexPath, 
							  vector<string>& vecAtoms, vector<int>& nodePath)
{
	//assert(outIndexPath.empty());
	
	for (unsigned int i = 0; i < inIndexPath.size(); i++) 
	{
		string atom = vecAtoms[nodePath[i]];
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
			cout << "error in Person::ConvertIndexPath!" <<endl; //just for debug
		}
	}
	outIndexPath.push_back(11); //add a "¡£" at the end of sentence
}

/////////////////////////////////////////////////////////////////////////////////////
/// add all persons to segment graph.
/////////////////////////////////////////////////////////////////////////////////////
void Person::AddPerson(vector<int>& indexPath, vector<int>& nodePath, 
					   Graph& graph, vector<string>& vecAtoms)
{
	int endIndex;
	int firstCharIndex;
	int lastCharIndex;
	float classProb;
	int senRoleNum = bestRoleSequence.size();
	
	for (int i = 0; i < senRoleNum-1; i++) 
	{
		if (bestRoleSequence[i] == "X" || bestRoleSequence[i] == "B") 
		{
			if (IsChineseName(i, endIndex)) 
			{
				classProb = ComputeClassProb(indexPath, i, endIndex);
				if (bestRoleSequence[i] == "B") 
					firstCharIndex = nodePath[i] + 1;
				else
					firstCharIndex = nodePath[i];

				if (bestRoleSequence[endIndex] == "I") 
					lastCharIndex = nodePath[endIndex]+1; 
				else
					lastCharIndex = nodePath[endIndex]; 

				graph.AddWord(firstCharIndex, lastCharIndex, PersonIndex, classProb);
			}
		}
		else if (bestRoleSequence[i] == "F" || bestRoleSequence[i] == "B") 
		{
			if (IsForeignName(i, endIndex, nodePath, vecAtoms)) 
			{
				classProb = ComputeClassProb(indexPath, i, endIndex);
				firstCharIndex = nodePath[i];
				lastCharIndex = nodePath[endIndex];
				graph.AddWord(firstCharIndex, lastCharIndex, PersonIndex, classProb);
			}
		}
		else if (bestRoleSequence[i] == "Q") 
		{
			if (bestRoleSequence[i+1] == "X") 
			{
				endIndex = i+1;
				firstCharIndex = nodePath[i];
				lastCharIndex = nodePath[endIndex];
				classProb = ComputeClassProb(indexPath, i, endIndex);
				graph.AddWord(firstCharIndex, lastCharIndex, PersonIndex, classProb);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// compute class probability, which is the probability of the string as a person.
/////////////////////////////////////////////////////////////////////////////////////
float Person::ComputeClassProb(vector<int>& indexPath, int begIdx, int& endIdx)
{
	float classProb = 0;
	for (int i = begIdx; i <= endIdx; i++) 
	{
		if (i+1 <= endIdx) 
		{
			classProb += pHmm[0]->GetTransProb(bestRoleSequence[i], bestRoleSequence[i+1]);
		}
		
		classProb += pHmm[0]->GetEmitProb(indexPath[i], bestRoleSequence[i]);
	}
	return classProb;
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if the rols between begIdx and endIdx compose a Chinese person name. 
/////////////////////////////////////////////////////////////////////////////////////
int Person::IsChineseName(int begIdx, int& endIdx)
{
	int senRoleNum = bestRoleSequence.size();
	if (bestRoleSequence[begIdx+1] == "D" || bestRoleSequence[begIdx+1] == "H" ||
		bestRoleSequence[begIdx+1] == "I") 
	{
		endIdx = begIdx + 1;
		return 1;
	}
	else if (bestRoleSequence[begIdx+1] == "S" && begIdx+2 < senRoleNum &&
		(bestRoleSequence[begIdx+2] == "W" || bestRoleSequence[begIdx+2] == "A")) 
	{
		endIdx = begIdx + 2;
		return 1;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/// judge if the rols between begIdx and endIdx compose a foreign person name. 
/////////////////////////////////////////////////////////////////////////////////////
int Person::IsForeignName(int begIdx, int& endIdx, vector<int>& nodePath, vector<string>& vecAtoms)
{
	int senRoleNum = bestRoleSequence.size();
	int i;
	for (i = begIdx+1; i < senRoleNum; i++) 
	{
		if (bestRoleSequence[i] != "M") 
		{
			if (i+2 < senRoleNum && bestRoleSequence[i+1] == "C" && 
				vecAtoms[nodePath[i+1]] == "¡¤" && bestRoleSequence[i+2] == "F") 
				i += 2;
			else
				break;
		}
	}
	//i is the first char that isn't middle transliteration char
	if (i < senRoleNum && (bestRoleSequence[i] == "" || bestRoleSequence[i] == "A")) 
	{
		endIdx = i;
		return 1;
	}
	return 0;
}


