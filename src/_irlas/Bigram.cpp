/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Bigram.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the implementation of class Bigram
// Create Time : 2005.5
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "Bigram.h"
//#include <conio.h>
//#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////
/// load unigram file and bigram file(if necessary), set lamed1, lamed2 and is_bigram.
/////////////////////////////////////////////////////////////////////////////////////
Bigram::Bigram(int isBigram, const char* resPathName, int& flag)
{
	is_bigram = isBigram;

	flag = 1;
//	printf("before Bigram::LoadUnigram. Enter key...\n");
//	_getch();
//	clock_t start = clock();
	if (!LoadUnigram(resPathName))
		flag = 0;
//	printf("after Bigram::LoadUnigram. time: %f. Enter key...\n", float(clock()-start)/CLOCKS_PER_SEC);
//	_getch();
	if (isBigram)
	{
		if (!LoadBigram(resPathName))
			flag = 0;
		lamed1 = 0.8f;
		lamed2 = 0.1f;
	}
	else
	{
		bigram = NULL;
		lamed1 = 0.0f;
		lamed2 = 0.9f;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// release the bigram's memory.
/////////////////////////////////////////////////////////////////////////////////////
Bigram::~Bigram()
{
	if (bigram != NULL)
	{
		for (int i =0; i < GramNum; i++) 
		{
			delete[] bigram[i].pBigram;
		}
		delete[] bigram;
		bigram = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// get the current word's bigram probability. 
/// according to the preceding word index and current word index.
/////////////////////////////////////////////////////////////////////////////////////
float Bigram::GetContextProb(int preWordIndex, int curWordIndex)
{
	int index;
	int preWordNum;
	int curWordNum;
	int bigramNum;
	float bigramProb;
	float unigramProb;
	float wordProb;

	//both the two words are dictionary word, 
	//number, time, person, location or organization or virtual begin word
	if (curWordIndex >= 0 && preWordIndex >= 0) 
	{
		if (is_bigram)
		{
			index = FindBigramIndex(preWordIndex, bigram[curWordIndex]);
			bigramNum = (index == -1) ? 0 : bigram[curWordIndex].pBigram[index].wordNum; 
			preWordNum = unigram[preWordIndex];
			bigramProb = (preWordNum == 0) ? 0 : (float)bigramNum / (float)preWordNum;	
		}
		else
		{
			bigramProb = 0;
		}
		curWordNum = unigram[curWordIndex];
		unigramProb = (float)curWordNum / (float)totalUnigram;
		wordProb = (float)(lamed1 * bigramProb 
			+ lamed2 * unigramProb + (1-lamed1-lamed2) / WordNum);
	}
	else if (curWordIndex >= 0 && preWordIndex < 0) //the preceding word is OOV word
	{
		curWordNum = unigram[curWordIndex];
		unigramProb = (float)curWordNum / (float)totalUnigram;
		wordProb = (float)(lamed2 * unigramProb + (1-lamed1-lamed2) / WordNum);
	}
	else if (curWordIndex < 0) //the current word is OOV word
	{
		wordProb = (float)((1-lamed1-lamed2) / WordNum);
	}
	return (float)-log(wordProb);
}

/////////////////////////////////////////////////////////////////////////////////////
/// find wordIndex's position in a bigram node array. 
/// if there is not such a wordIndex in the array, then just return -1.
/// the searching algorithm used is binary search. 
/////////////////////////////////////////////////////////////////////////////////////
int Bigram::FindBigramIndex(int wordIndex, BigramHead& head)
{
	BigramNode* p = head.pBigram;
	int low = 0;
	int up = head.bigramNum;
	int mid;
	while (low <= up) 
	{
		mid = (low + up) / 2;
		if (head.pBigram[mid].wordIndex == wordIndex) 
			return mid;
		else if (head.pBigram[mid].wordIndex > wordIndex) 
			up = mid - 1;
		else 
			low = mid + 1;
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////
/// load the file "bigram.dat".
/////////////////////////////////////////////////////////////////////////////////////
int Bigram::LoadBigram(const char* resPathName)
{
	string pathName(resPathName);
	bigram = new BigramHead[GramNum];
	FILE* fp = fopen((pathName+"/bigram.dat").c_str(), "rb");
	if (fp == NULL) 
	{
		cerr<<"can't open the file bigram.dat!"<<endl;
		return 0;
	}

	int lineNum;
	fread(&lineNum, sizeof(int), 1, fp); //lineNum equals to GramNum
	for (int i = 0; i < lineNum; i++) 
	{
		int bigramNum;
		fread(&bigramNum, sizeof(int), 1, fp); //read the number of nodes in a bigram array
		bigram[i].bigramNum = bigramNum;
		bigram[i].pBigram = new BigramNode[bigramNum];
		for (int j = 0; j < bigramNum; j++) //read a bigram node
		{
			fread(&bigram[i].pBigram[j], sizeof(BigramNode), 1, fp);
		}
	}
	fclose(fp);
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////
/// load the file "unigram.dat".
/////////////////////////////////////////////////////////////////////////////////////
int Bigram::LoadUnigram(const char* resPathName)
{
	string pathName(resPathName);
	FILE* fp = fopen((pathName+"/unigram.dat").c_str(), "rb");
	if (fp == NULL) 
	{
		cerr<<"can't open the file unigram.dat!"<<endl;
		return 0;
	}
	int unigramNum;
	fread(&unigramNum, sizeof(int), 1, fp); //read the number of unigram which is GramNum
	fread(&totalUnigram, sizeof(int), 1, fp); //set the value of totalUnigram
	for (int i = 0; i < unigramNum; i++) 
	{
		fread(unigram+i, sizeof(int), 1, fp); //set the value of an item in the array unigram
	}
	fclose(fp);

	return 1;
}

