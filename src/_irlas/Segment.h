/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Segment.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Time		   : 2005.5
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _SEGMENT_H_
#define _SEGMENT_H_
#include "Graph.h"

/////////////////////////////////////////////////////////////////////////////////////
/// this class do three things:
/// 1. it do basic segmentation and add them into segment graph.
/// 2. it add atom path to segment graph before person and location recognition.
/// 3. it generate the best word sequence before POS tagging.
/////////////////////////////////////////////////////////////////////////////////////
class Segment
{
public:
	Segment(Dictionary* p) : pDict(p) {}
	void BasicSegment(const string& sentence, Graph& graph);
	void AddAtomPath(Graph& graph); 
	void GenerateBestWordSequence(Graph& graph, vector<string>& bestWordSequence);

private:
	void AtomSegment(const string& sentence); 
	void CompleteSegment(Graph& graph); 
	void GBStringRecg(Graph& graph);

public:
	vector<string> vecAtoms; ///< the vector of atoms
private:
	Dictionary* pDict; ///< points to the class Dictionary
};

#endif


