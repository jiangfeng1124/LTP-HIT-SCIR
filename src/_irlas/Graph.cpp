/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Graph.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the implementation of class Graph
// Create Time : 2005.5
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "Graph.h"


/////////////////////////////////////////////////////////////////////////////////////
/// output the segment graph to console, just for debug.
/////////////////////////////////////////////////////////////////////////////////////
void Graph::OutputGraph()
{
	cout << "The Segment Graph:" << endl;
	for (unsigned int i = 0; i < graph.size(); i++) 
	{
		if (i < 10) 
		{
			cout << i << "  : ";
		}
		else
		{
			cout << i << " : ";
		}
		
		for (unsigned int j = 0; j < graph[i].size(); j++) 
		{
			cout << "[" << graph[i][j].preNode << " " << graph[i][j].nextNode << "]  "; 
//			cout << "[" << graph[i][j].preNode << " " << graph[i][j].nextNode << " " 
//				 << graph[i][j].wordIndex << " " << graph[i][j].wordProb << "]  ";
		}
		cout << endl;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/// initialize the segment graph, set the size of graph.
/////////////////////////////////////////////////////////////////////////////////////
void Graph::InitGraph(int nodeNum)
{
	for (unsigned int i = 0; i < graph.size(); i++) 
	{
		graph[i].clear();
	}
	graph.resize(nodeNum);
}

/////////////////////////////////////////////////////////////////////////////////////
/// get word probability from the segment graph.
/////////////////////////////////////////////////////////////////////////////////////
float Graph::GetWordProb(int preWordIndex, int curWordIndex, 
						 int preNode, int curNode, int nextNode)
{
	for (unsigned int i = 0; i < graph[curNode].size(); i++) 
	{
		if (graph[curNode][i].preWordIndex == preWordIndex && 
			graph[curNode][i].wordIndex == curWordIndex &&
			graph[curNode][i].preNode == preNode &&
			graph[curNode][i].nextNode == nextNode) 
		{
			return graph[curNode][i].wordProb;
		}
	}
	cout << "error in Graph::GetWordProb" <<endl; //just for debug
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/// get class probability from the segment graph.
/////////////////////////////////////////////////////////////////////////////////////
float Graph::GetClassProb(int begNode, int endNode, int wordIndex)
{
	for (unsigned int i = 0; i < graph[begNode].size(); i++) 
	{
		if (graph[begNode][i].wordIndex == wordIndex && graph[begNode][i].nextNode == endNode) 
		{
			return graph[begNode][i].classProb;
		}
	}
	cout << "error in Graph::GetClassProb" <<endl; //just for debug
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
/// add a atom word to the segment graph, used only in atom segment.
/////////////////////////////////////////////////////////////////////////////////////
void Graph::AddAtom(int atomNode, int atomIndex)
{
	GraphNode node;
	node.wordIndex = atomIndex;
	node.preNode = atomNode - 1;

	if (node.preNode == -1) 
	{
		node.preWordIndex = BEGIndex;
	}
	else
	{
		node.preWordIndex = graph[node.preNode][0].wordIndex;
	}
	
	node.nextNode = atomNode + 1;
	node.wordProb = pBigram->GetContextProb(node.preWordIndex, node.wordIndex);
	node.classProb = 0;
	graph[atomNode].push_back(node);
}

/////////////////////////////////////////////////////////////////////////////////////
/// add a word to the segment graph.
/////////////////////////////////////////////////////////////////////////////////////
void Graph::AddWord(int firstCharIndex, int lastCharIndex, int wordIndex, float classProb)
{
	//the suffix of first and last character of word must be no more than the number of atoms
	assert(firstCharIndex < (int)graph.size() && lastCharIndex < (int)graph.size()); 

	bool isSameTypeWord = false; //the flag that indicate if the same type of word has existed
	for (unsigned int k = 0; k < graph[firstCharIndex].size(); k++) 
	{
		//the same arc has existed in the segment graph
		if (graph[firstCharIndex][k].nextNode == lastCharIndex+1) 
		{
			//if the word has existed in the dictionary, then just return
			if (graph[firstCharIndex][k].wordIndex >= 0 && 
				graph[firstCharIndex][k].wordIndex < WordNum) 
			{
				return;
			}
			//the same type of unknown words has existed in the segment graph
			else if (graph[firstCharIndex][k].wordIndex == wordIndex) 
			{
				isSameTypeWord = true;
				//reserve the better class probability and word probability
				if (graph[firstCharIndex][k].classProb > classProb) 
				{
					graph[firstCharIndex][k].wordProb -= 
						(graph[firstCharIndex][k].classProb - classProb);
					graph[firstCharIndex][k].classProb = classProb;
				}
			}
		}
	}
	//if the same type of unknown words has existed in segment graph, then just return
	if (isSameTypeWord) return;

	DealPreArcs(firstCharIndex, lastCharIndex+1, wordIndex, classProb);
	DealPostArcs(firstCharIndex, lastCharIndex+1, wordIndex, classProb);
}

/////////////////////////////////////////////////////////////////////////////////////
/// deal with preceding arcs, used in AddWord.
/////////////////////////////////////////////////////////////////////////////////////
void Graph::DealPreArcs(int begNode, int endNode, int wordIndex, float classProb)
{
	vector< pair<int, int> > vecPreArcs;
	int preArcNum = GetPreArcs(begNode, vecPreArcs);

	GraphNode node;	
	node.wordIndex = wordIndex;
	node.nextNode = endNode;
	node.classProb = classProb;
	
	for (int i = 0; i < preArcNum; i++) 
	{
		node.preWordIndex = vecPreArcs[i].first;
		node.preNode = vecPreArcs[i].second;
		node.wordProb = pBigram->GetContextProb(node.preWordIndex, wordIndex) + node.classProb;
		graph[begNode].push_back(node);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// deal with posterior arcs, used in AddWord.
/////////////////////////////////////////////////////////////////////////////////////
void Graph::DealPostArcs(int begNode, int endNode, int wordIndex, float classProb)
{
	vector< pair<int, int> > vecPostArcs;
	int postArcNum = GetPostArcs(endNode, vecPostArcs);

	GraphNode node;	
	node.preNode = begNode;
	node.preWordIndex = wordIndex;
	for (int i = 0; i < postArcNum; i++) 
	{
		node.wordIndex = vecPostArcs[i].first;
		node.nextNode = vecPostArcs[i].second;
		node.classProb = GetClassProb(endNode, node.nextNode, node.wordIndex);
		node.wordProb = pBigram->GetContextProb(wordIndex, node.wordIndex) + node.classProb;
		graph[endNode].push_back(node);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// get all the preceding arcs of a node, return the number of arcs.
/////////////////////////////////////////////////////////////////////////////////////
int Graph::GetPreArcs(int curNode, vector< pair<int, int> >& vecPreArcs)
{
	set< pair<int, int> > setPreArcs; //the set of preWordIndex/preNode pair
	for (unsigned int i = 0; i < graph[curNode].size(); i++) 
	{
		setPreArcs.insert(pair<int,int>(graph[curNode][i].preWordIndex,graph[curNode][i].preNode));
	}
	vecPreArcs.resize(setPreArcs.size());
	copy(setPreArcs.begin(), setPreArcs.end(), vecPreArcs.begin());
	return vecPreArcs.size();
}

/////////////////////////////////////////////////////////////////////////////////////
/// get all the posterior arcs of a node, return the number of arcs.
/////////////////////////////////////////////////////////////////////////////////////
int Graph::GetPostArcs(int curNode, vector< pair<int, int> >& vecPostArcs)
{
	set< pair<int, int> > setPostArcs; //the set of wordIndex/nextNode pair
	for (unsigned int i = 0; i < graph[curNode].size(); i++) 
	{
		setPostArcs.insert(pair<int,int>(graph[curNode][i].wordIndex, graph[curNode][i].nextNode));
	}
	vecPostArcs.resize(setPostArcs.size());
	copy(setPostArcs.begin(), setPostArcs.end(), vecPostArcs.begin());
	return vecPostArcs.size();
}

/////////////////////////////////////////////////////////////////////////////////////
/// construct pathList according to the number of paths requested.
/////////////////////////////////////////////////////////////////////////////////////
void Graph::ConstructNBestPathList(int pathNum)
{
	for (unsigned k = 0; k < pathList.size(); k++) 
	{
		pathList[k].clear();
	}
	pathList.resize(graph.size()); 

	PathNode node;
	node.accumProb = 0;
	pathList[0].assign(1, node);
	unsigned int i;
	vector< pair<int, int> > vecPreArcs;

	for (i = 1; i < pathList.size(); i++) //the i-th node array
	{
		vecPreArcs.clear();
		int preArcNum = GetPreArcs(i, vecPreArcs);
		pathList[i].resize(pathNum * preArcNum);
		for (int j = 0; j < preArcNum; j++) //the j-th preNode
		{
			int preWordIndex = vecPreArcs[j].first;
			int preNode = vecPreArcs[j].second;
			for (unsigned int k = 0; k < pathList[preNode].size(); k++) //the k-th node of j-th array
			{
				float maxProb = 0;
				int maxProbIndex;
				//find the suffix of the node that have maximum probability from the i-th node array,
				//the finding range of i-th array relates to the j-th preNode it is dealing with
				for (int l = j*pathNum; l < (j+1)*pathNum; l++) 
				{
					if (pathList[i][l].accumProb > maxProb) 
					{
						maxProb = pathList[i][l].accumProb;
						maxProbIndex = l;
					}
				}

				//as to the nodes except the first node,if the field preNode 
				//is negative, then ignore the operations below
				if (preNode > 0 && pathList[preNode][k].preNode < 0) continue;  

				float curProb = pathList[preNode][k].accumProb + 
					GetWordProb(pathList[preNode][k].preWordIndex, 
					preWordIndex, pathList[preNode][k].preNode, preNode, i);
				//replace the maximum probability node with the new node provided the 
				//probability of new node is less than the maximum probability
				if (curProb < maxProb) 
				{
					pathList[i][maxProbIndex].preNode = preNode;
					pathList[i][maxProbIndex].preSuffix = k;
					pathList[i][maxProbIndex].preWordIndex = preWordIndex;
					pathList[i][maxProbIndex].accumProb = curProb;
				}
			}
		}
	}
	sort(pathList[i-1].begin(), pathList[i-1].end()); //sort the last node array
}

/////////////////////////////////////////////////////////////////////////////////////
/// generate N best word index paths and node paths.
/////////////////////////////////////////////////////////////////////////////////////
void Graph::GenerateNBestPath(int bestPathNum)
{
	for (unsigned int m = 0; m < NBestIndexPath.size(); m++) 
	{
		NBestIndexPath[m].clear();
	}
	for (unsigned int n = 0; n < NBestNodePath.size(); n++) 
	{
		NBestNodePath[n].clear();
	}
	ConstructNBestPathList(bestPathNum);
	//find the path number, it is no more than bestPathNum
	int i;
	for (i = 0; i < bestPathNum; i++) 
	{
		if (pathList[pathList.size()-1][i].accumProb >= FLT_MAX) 
		{
			break;
		}
	}
	int pathNum = i; 
	NBestNodePath.resize(pathNum); 
	NBestIndexPath.resize(pathNum); 
	
	for (int j = 0; j < pathNum; j++) //the j-th best path
	{
		int node = pathList.size()-1;
		int suffix = j;
		do //put the nodes of N best paths into NBestNodePath
		{
			NBestNodePath[j].push_back(node);
			NBestIndexPath[j].push_back(pathList[node][suffix].preWordIndex);
			int tempNode = node;
			int tempSuffix = suffix;
			node = pathList[tempNode][tempSuffix].preNode;
			suffix = pathList[tempNode][tempSuffix].preSuffix;
		} while(node >= 0);

		reverse(NBestNodePath[j].begin(), NBestNodePath[j].end());
		//the size of NBestIndexPath[j] is one smaller than NBestNodePath[j]
		NBestIndexPath[j].pop_back(); 
		reverse(NBestIndexPath[j].begin(), NBestIndexPath[j].end());
	}
}


