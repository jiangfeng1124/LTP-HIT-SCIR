  /////////////////////////////////////////////////////////////////////////////////////
// File Name   : Dictionary.cpp
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the implementation of class Dictionary
// Time        : 2005.9
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "Dictionary.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
//#include <stdio.h>
//#include <conio.h>
//#include <time.h>
#include <utility>
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////
/// load core dictionary and extended dictionary(if necessary).
/////////////////////////////////////////////////////////////////////////////////////
Dictionary::Dictionary(int isExtendedDict, const char *resPathName, int& flag):m_buf(0)
{
	m_isExtendDic = isExtendedDict;
	flag = 1;

//	printf("before load irlas dic. Enter key...\n");
//	_getch();
//	clock_t start = clock();
	if (!LoadDictionary(resPathName))
		flag = 0;
//	printf("after load dic. time: %f. Enter key...\n", float(clock()-start)/CLOCKS_PER_SEC);
//	_getch();
//	start = clock();
	if (isExtendedDict)
		if (!LoadExtendWords(resPathName))
			flag = 0;
//	printf("after load ExtendWords. time: %f. Enter key...\n", float(clock()-start)/CLOCKS_PER_SEC);
//	_getch();
}

Dictionary::~Dictionary()
{
	releaseMemory();
}
///////////////////////////////////////////////////////////////
//	函 数 名 : relaseMemory
//	所属类名 : Dictionary
//	函数功能 : 释放申请的内存
//	处理过程 : 
//	备    注 : 
//	作    者 : taozi
//	时    间 : 2006年3月29日
//	返 回 值 : void
//	参数说明 : 
///////////////////////////////////////////////////////////////
void Dictionary::releaseMemory()
{
	if (m_buf)
	{
		delete [] m_buf;
		m_buf = 0;
	}
	if (m_buf_extend)
	{
		delete [] m_buf_extend;
		m_buf_extend = 0;
	}
	m_mapExtendWords.clear();
	m_mapPOS2Givenword.clear();
}


/////////////////////////////////////////////////////////////////////////////////////
/// get the word's index.
/// if it is in the dictionary, then return the index of it, if not in dictionary but
/// is a string consists of only ASCII char, then return ASCIIStringIndex, else
/// return OOVWordIndex.
/////////////////////////////////////////////////////////////////////////////////////
int Dictionary::GetWordIndex(string& word)
{
   int low = 0;
   int up = WordNum - 1;
   int mid = 0;
   
   while (low <= up)  //search in Word_bin, by taozi 
   {
	   mid = (low+up)/2;
	   int cmp_res = strcmp(m_word[mid], word.c_str());
	   if (cmp_res == 0)
	   {
		   return mid;
	   }
	   else if (cmp_res < 0)
	   {
		   low = mid + 1;
	   }
	   else
	   {
		   up = mid - 1;
	   }
   }

  
   if (m_isExtendDic)
   {   
	   map<const char *, int, SZCmp>::const_iterator it = m_mapExtendWords.find(word.c_str());
	   if (it != m_mapExtendWords.end())
	   {
		   return it->second;
	   }
   }

   if (is_ascii_string(word))
	{
		return ASCIIStringIndex;
	}
	else
	{
		return OOVWordIndex;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
/// load core dictionary.
/////////////////////////////////////////////////////////////////////////////////////
int Dictionary::LoadDictionary(const char *resPathName)
{
	char filename[100];
	sprintf(filename, "%s/words.dat", resPathName);
	FILE *infile = fopen(filename, "rt");
	if (!infile)
	{
		printf("Dictionary::LoadDictionary open file %s error\n", resPathName);
		return -1;
	}
	long fileLen;
	fseek(infile, 0, SEEK_END );	
	fileLen = ftell( infile );
	fseek(infile, 0, SEEK_SET );
	m_buf = new char[fileLen + 1];	// one more to store '\0'
	if (!m_buf)
	{
		printf("Dictionary::LoadDictionary new m_buf failed");
		return -1;
	}

	long readNum = fread( m_buf, 1, fileLen, infile );
	//	printf("readNum: %d, fileLen: %d\n", readNum, fileLen);
	m_buf[readNum] = 0;
	
	char *p = m_buf;
	int i = 0;
	while(*p && i < WordNum)
	{
		while (*p == '\n' || *p == '\r' || *p == ' ' || *p == '\t') *p++ = 0;		
		m_word[i++] = p++;
		while (*p && !(*p == '\n' || *p == '\r' || *p == ' ' || *p == '\t')) ++p;		
	}

	while (i < WordNum)
	{
		m_word[i++] = 0;
	}
	fclose(infile);
	
	// for test
/*	sprintf(filename, "%s_", filename);
	FILE *outf = fopen(filename, "w");
	int j = 0;
	for (; j < WordNum; ++j)
	{
		fprintf(outf, "%s\n", m_word[j]);
	}
	fclose(outf);
*/
	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////
/// load extended dictionary.
/// you can append words and its POS by hand to this file.
/////////////////////////////////////////////////////////////////////////////////////
int Dictionary::LoadExtendWords(const char *resPathName)
{
	string pathName(resPathName);
	
	ifstream posFile((pathName+"/postag_tags.dat").c_str());
	if (!posFile)
	{
		cerr << "can't open the file postag_tags.dat." << endl;
		return 0;
	}
	
	ifstream givenwordFile((pathName+"/pos2givenword.dat").c_str());
	if (!givenwordFile) 
	{
		cerr << "can't open the file pos2givenword.dat." << endl;
		return 0;
	}
	
	string pos;
	int givenWordIndex;
	int i;
	for (i = 0; i < 28; i++)
	{
		posFile >> pos;
		givenwordFile >> givenWordIndex;
		m_mapPOS2Givenword[pos] = givenWordIndex;
	}
	
	posFile.close();
	givenwordFile.close();
			
	string fileName = pathName + "/extend_dict.dat";
	FILE *fp = fopen(fileName.c_str(), "rt");
	if (!fp)
	{
		cerr << "can't open the file extend_dict.dat." << endl;
		return 0;
	}
	
	int filelength = 0;	
	fseek(fp, 0, SEEK_END);
	filelength = ftell(fp);
	m_buf_extend = new char[filelength + 1];
	fseek(fp, 0, SEEK_SET);	
	int readNum = fread(m_buf_extend, 1, filelength, fp);
	m_buf_extend[readNum] = 0;
	fclose(fp);
 
	int index = 0;
	char *p = m_buf_extend;
	while (*p == '\n' || *p == '\r' || *p == ' ' || *p == '\t') *p++ = 0;
	char *p_token = p;
	while(*p)
	{
		p_token = p;
		while (*p && !( *p == '\n' || *p == '\r' || *p == ' ' || *p == '\t') ) p++;
		while (*p == '\n' || *p == '\r' || *p == ' ' || *p == '\t') *p++ = 0;
		if(*p_token == '#' && *(p_token+1) == '#')	// pos
		{
			p_token += 2;
			index = m_mapPOS2Givenword[p_token];
			//cout << "\n##" << p_token << endl;
		}
		else // word
		{
			m_mapExtendWords[p_token] = index;
			//cout << p_token << " ";
		}
	}
	
	return 1;
}

