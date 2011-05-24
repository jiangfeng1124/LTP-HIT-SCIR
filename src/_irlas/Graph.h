/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Graph.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Create Time : 2005.5
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "Bigram.h"

/////////////////////////////////////////////////////////////////////////////////////
/// this class constructs a segment graph, other classes add words to the graph by 
/// calling the function AddWord and AddAtom, this class also provides for other classes
/// N best index and node paths.
/////////////////////////////////////////////////////////////////////////////////////
class Graph
{
public:
	Graph(Bigram* p) : pBigram(p) {}
	void OutputGraph(); 
	void InitGraph(int nodeNum);
	void AddAtom(int atomNode, int atomIndex);
	void AddWord(int firstCharIndex, int lastCharIndex, int wordIndex, float classProb);	
	void GenerateNBestPath(int bestPathNum); 

private:
	float GetWordProb(int preWordIndex, int curWordIndex, int preNode, int curNode, int nextNode); 
	float GetClassProb(int begNode, int endNode, int wordIndex);
	void DealPreArcs(int begNode, int endNode, int wordIndex, float classProb);
	void DealPostArcs(int begNode, int endNode, int wordIndex, float classProb);
	int GetPreArcs(int curNode, vector< pair<int, int> >& vecPreArcs);
	int GetPostArcs(int curNode, vector< pair<int, int> >& vecPostArcs);
	void ConstructNBestPathList(int pathNum);
	
private:
/////////////////////////////////////////////////////////////////////////////////////
/// the node of segment graph.
/////////////////////////////////////////////////////////////////////////////////////
	struct GraphNode 
	{
		int preNode; ///< the index of preceding node, the index before the first node is -1
		int preWordIndex; ///< the index of preceding word, the index before the first word is BEGIndex
		int nextNode; ///< the index of posterior node, the index after the last node is -1
		int wordIndex; ///< the word's index in dictionary, named entity's index is its type's index,
		               ///< the index of other OOV word is OOVWordIndex
		float classProb; ///< the word's class probability, P(Word|Class)
		float wordProb; ///< the word's probability, P(Word)
	};

/////////////////////////////////////////////////////////////////////////////////////
/// the node of path list.
/////////////////////////////////////////////////////////////////////////////////////
	struct PathNode 
	{
		int preNode; ///< the index of preceding node, the index before the first node is -1
		int preSuffix; //the node's index in the preNode-th array
		int preWordIndex; ///< the index of preceding word, the index before the first word is BEGIndex
		float accumProb; ///< the accumulate probability from beginning to this node 
		PathNode():preNode(-1),preSuffix(-1),preWordIndex(BEGIndex),accumProb(FLT_MAX){}
		bool operator < (const PathNode& node) const ///< used by the STL algorithm sort
		{
			return accumProb < node.accumProb;
		}
	};

private:
	Bigram* pBigram; ///< points to the class Bigram
	vector< vector<GraphNode> > graph; ///< segment graph
	
public:
	vector< vector<PathNode> > pathList; ///< reserve every path and its total probability
	vector< vector<int> > NBestIndexPath; ///< N best word index paths
	vector< vector<int> > NBestNodePath; ///< N best node paths
};

#endif

