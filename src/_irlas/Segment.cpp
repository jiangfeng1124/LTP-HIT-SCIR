/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Segment.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the implementation of class Segment
// Create Time : 2005.5
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "Segment.h"


/////////////////////////////////////////////////////////////////////////////////////
/// do atom segment, complete segment and GB string recognition.
/////////////////////////////////////////////////////////////////////////////////////
void Segment::BasicSegment(const string& sentence, Graph& graph)
{
	assert(!sentence.empty()); //the input sentence must not be empty
	vecAtoms.clear();
	AtomSegment(sentence);

	//--------initialize the segment graph and add every atom to the graph-------
	graph.InitGraph(vecAtoms.size()+1);
	for (unsigned int j = 0; j < vecAtoms.size(); j++) //add every atom 
	{
		graph.AddAtom(j, pDict->GetWordIndex(vecAtoms[j]));
	}
	graph.AddAtom(vecAtoms.size(), -1); //add a virtual atom to the end for other uses

	CompleteSegment(graph);
	GBStringRecg(graph);
}

/////////////////////////////////////////////////////////////////////////////////////
/// add the atom node and index path to segment graph.
/////////////////////////////////////////////////////////////////////////////////////
void Segment::AddAtomPath(Graph& graph)
{
	vector<int> atomNodePath;
	vector<int> atomIndexPath;
	int atomNum = vecAtoms.size();

	for (int i = 0; i < atomNum; i++) 
	{
		atomNodePath.push_back(i);
		atomIndexPath.push_back(pDict->GetWordIndex(vecAtoms[i]));
	}
	
	atomNodePath.push_back(atomNum);
	graph.NBestNodePath.push_back(atomNodePath);
	graph.NBestIndexPath.push_back(atomIndexPath);
}

/////////////////////////////////////////////////////////////////////////////////////
/// split a sentence into atoms and put them in vecAtoms.
/////////////////////////////////////////////////////////////////////////////////////
void Segment::AtomSegment(const string& sentence)
{
	string asciiString;
	for (unsigned int i = 0; i < sentence.size(); i++) 
	{		
		if (sentence[i] < 0) //is a Chinese character
		{	
			if (!asciiString.empty()) //the preceding atom is a ASCII string
			{
				vecAtoms.push_back(asciiString);
				asciiString = "";
			}
			vecAtoms.push_back(sentence.substr(i++, 2)); //push back the Chinese character
		}
		else //is a ASCII character
		{
			string i_char(1, sentence[i]);
			if (i_char == " ")
			{
				if (!asciiString.empty())
				{
					vecAtoms.push_back(asciiString);
					asciiString.erase();
				}
				vecAtoms.push_back(i_char);
			}
			else if (pDict->GetWordIndex(i_char) >= 0)
			{
				if (!asciiString.empty()) //the preceding atom is a ASCII string
				{
					vecAtoms.push_back(asciiString);
					asciiString = "";
				}
				vecAtoms.push_back(i_char);
			}
			else
			{
				asciiString += i_char;
				if (pDict->GetWordIndex(asciiString) >= 0)
				{
					vecAtoms.push_back(asciiString);
					asciiString = "";
				}
			}
		}
	}
	if (!asciiString.empty()) //an ASCII string is at the end of a sentence
	{
		vecAtoms.push_back(asciiString);
	}

//	for (unsigned int j=0; j<vecAtoms.size(); ++j) //for debug
//	{
//		cout << vecAtoms[j]/* << " "*/;
//	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// recognize all the words in the dictionary and add them to segment graph.
/////////////////////////////////////////////////////////////////////////////////////
void Segment::CompleteSegment(Graph& graph)
{
	const int maxLookupAtomNum = 10; //the maximum atom number to look up
	int atomNum = vecAtoms.size();
	string word;
	int wordIndex;

	for (int i = 0; i < atomNum; i++) 
	{
		word.erase();
		int lookupAtomNum = i+maxLookupAtomNum < atomNum ? i+maxLookupAtomNum : atomNum;
		for (int j = i; j < lookupAtomNum; j++) 
		{
			word.append(vecAtoms[j]);
			wordIndex = pDict->GetWordIndex(word);
			if (wordIndex >= 0 && j > i) //word in the dictionary except single char word
			{
				graph.AddWord(i, j, wordIndex, 0);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// recognize all the GB string such as: ＣＤＭＡ.
/////////////////////////////////////////////////////////////////////////////////////
void Segment::GBStringRecg(Graph& graph)
{
	int atomNum = vecAtoms.size();
	for (int i = 0; i < atomNum; i++) 
	{
		string GBString;
		if (!is_chinese_char(vecAtoms[i]) && !is_ascii_string(vecAtoms[i]) 
			&& !is_separator(vecAtoms[i])) //is not a Hanzi or a separator
		{
			GBString.append(vecAtoms[i]);
			int j;
			for (j = i+1; j < atomNum; j++) 
			{
				if (!is_chinese_char(vecAtoms[j]) && !is_ascii_string(vecAtoms[j])
					&& !is_separator(vecAtoms[j])) 
				{
					GBString.append(vecAtoms[j]);
				}
				else
				{
					break;
				}
			}
			graph.AddWord(i, j-1, GBStringIndex, 0); //注意：该函数可能有点bug，将ＣＤＭＡ子串都加入，原因是它没有移动i
			i = j - 1;  //桃子修改06.19
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// generate the best word sequence according to the best node path.
/////////////////////////////////////////////////////////////////////////////////////
void Segment::GenerateBestWordSequence(Graph& graph, vector<string>& bestWordSequence)
{
	vector<int> vecBestNodePath = graph.NBestNodePath[0];
	string word;
	int nodeNum = vecBestNodePath.size();
	vector<string> wordSequence;
	
	for (int i = 0; i < nodeNum-1; i++) 
	{
		word = "";
		for (int j = vecBestNodePath[i]; j < vecBestNodePath[i+1]; j++) 
		{
			word += vecAtoms[j];
		}
		if (!word.empty()) 
		{
			bestWordSequence.push_back(word);
		}
	}
}


