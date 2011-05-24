/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Dictionary.h
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Time        : 2005.9
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
#include "MyLib.h"

/////////////////////////////////////////////////////////////////////////////////////
/// definition of some constants.
/// there are two kinds of constants, one kind is index, the other is number(WordNum
/// and GramNum).
/////////////////////////////////////////////////////////////////////////////////////
enum SomeConstants
{
	ASCIIStringIndex = -3, ///< the word that consists of ASCII chars
	GBStringIndex = -2, ///< the word that consists of GB chars 
	OOVWordIndex = -1, ///< the word that can't find an entry in the unigram and bigram structure
	WordNum = 107749, ///< the number of words in the core dictionary
	PersonIndex = WordNum, ///< the constants below(including this) are 5 types of named entities
	LocationIndex,
	OrganizationIndex,
	NumberIndex,
	TimeIndex,
	BEGIndex, ///< the virtual word before the first word of a sentence
	WordClassNum = WordNum + 5, ///< the number of word classes(WordNum + 5 types of named entities)
	GramNum = WordNum + 6, ///< the number of unigrams and bigrams
	WsWordIndex = WordClassNum, ///< the word with POS tag "ws", unsed in POSTag
	OtherOOVWordIndex = WordClassNum + 1, ///< other OOV words, used in POSTag
	ExtendWordNum = 9572
};

//////////////////////////////////////////////////////
//Function:It used to keep the word and its index
//Author: taozi
//Time:   2006-03-11
//////////////////////////////////////////////////////
struct Wordnode
{
	char* pw;
	int index;
};
typedef struct Wordnode WORDNODE;

/////////////////////////////////////////////////////////////////////////////////////
/// this class provides the index of a word in core dictonary.
/// it holds two data resources: core dictionary and extended dictionary.
/////////////////////////////////////////////////////////////////////////////////////
class Dictionary
{
public:
	Dictionary(int isExtendedDict, const char *resPathName, int& flag);
	~Dictionary();
	int GetWordIndex(string& word); 
	void releaseMemory();

private:
	int LoadDictionary(const char *resPathName);
	int LoadExtendWords(const char *resPathName);
	char *m_buf;
	const char *m_word[WordNum];  //add by taozi

	char *m_buf_extend;
	struct SZCmp
	{
		bool operator()(const char *str1, const char *str2) const
		{
			return strcmp(str1, str2) < 0;
		}
	};
	map<const char *, int, SZCmp> m_mapExtendWords;
	map<string, int> m_mapPOS2Givenword; ///< the map from dictionary word to its index
										//将某一词性如(m)，映射到某一个代表词在此词典中的index (七：58018)
	int m_isExtendDic;
};

#endif


