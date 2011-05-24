/////////////////////////////////////////////////////////////////////////////////////
// File Name   : NumTime.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Create Time : 2005.5
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _NUMTIME_H_
#define _NUMTIME_H_
#include "Graph.h"

/////////////////////////////////////////////////////////////////////////////////////
/// recognize numbers and times in a sentence and add them to the segment graph.
/////////////////////////////////////////////////////////////////////////////////////
class NumTime
{
public:
	NumTime();
	void NumTimeRecg(vector<string>& vecAtoms, Graph& graph);
	
private:
	int IsNumPrefix(string& atom); 
	int IsCnNumUnit(string& atom);
	int IsEnNumUnit(string& atom, int& flag); 
	int IsTimeUnit(string str); 
	int IsSepNumUnit(string& str);
	int IsTime(int begIndex, int endIndex, vector<string>& vecAtoms);
	int IsHour(int begIndex, int endIndex, vector<string>& vecAtoms);
	int IsMinuteSecond(int begIndex, int endIndex, vector<string>& vecAtoms);
	int IsYear(int begIndex, int endIndex, vector<string>& vecAtoms);

	int FindNumEndIndex(int begIndex, int& flag, vector<string>& vecAtoms);
	int FindTimeEndIndex(int begIndex, vector<string>& vecAtoms);

	set<string> setNumUnit; 
	set<string> setTimeUnit; 
	set<string> setSepNumUnit; 
};

#endif



