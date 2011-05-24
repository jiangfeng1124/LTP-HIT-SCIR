/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Bigram.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Create Time : 2005.5
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _BIGRAM_H_
#define _BIGRAM_H_
#include "Dictionary.h"

/////////////////////////////////////////////////////////////////////////////////////
/// this class compute the word's context probability, which is used by the class
/// Graph when construct the segment graph. 
/// it holds two data resources: unigram and bigram.
/////////////////////////////////////////////////////////////////////////////////////
class Bigram
{
public:
	Bigram(int isBigram, const char* resPathName, int& flagBig);
	~Bigram();
	float GetContextProb(int preWordIndex, int curWordIndex); 

private:
	/////////////////////////////////////////////////////////////////////////////////////
	/// the node in the bigram node array.
	/////////////////////////////////////////////////////////////////////////////////////
	struct BigramNode 
	{
		int wordIndex; ///< the index of word in dictionary
		int wordNum; ///< the times this word appears before BigramHead word in training data
	};

	/////////////////////////////////////////////////////////////////////////////////////
	/// head node of the bigram node array.
	/// it reserves the number of node in the array and points to the first node of it.
	/////////////////////////////////////////////////////////////////////////////////////
	struct BigramHead 
	{
		int bigramNum; ///< the number of bigram node in the array
		BigramNode* pBigram; ///< points to the first node of bigram array
	};

private:
	int FindBigramIndex(int wordIndex, BigramHead& head); 
	int LoadBigram(const char* resPathName); 
	int LoadUnigram(const char* resPathName); 

private:
	BigramHead* bigram; ///< the data structure of bigram, it's an adjacent array
	int unigram[GramNum]; ///< the array of unigram
	int totalUnigram; ///< the sum of all unigrams
	float lamed1; ///< the coefficient for the interpolation between bigram and unigram
	float lamed2; ///< see lamed1
	int is_bigram; ///< if bigram will be used 
};

#endif

