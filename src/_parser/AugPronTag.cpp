// AugPronTag.cpp: implementation of the AugPronTag class.
//
//////////////////////////////////////////////////////////////////////

#include "AugPronTag.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AugPronTag::AugPronTag()
{
//	Initialize();	
}

AugPronTag::~AugPronTag()
{

}

void AugPronTag::TagAug(string& strSent)
{
	size_t pos = strSent.find("/u");
	string word, tag;
	map < string, string > ::iterator it;

	while(pos != -1)
	{
		size_t pos1 = strSent.rfind(" ",pos);
		word = strSent.substr(pos1+1,pos-pos1-1);
		it = mapAug.find(word);
		if(it != mapAug.end() )
			tag = (*it).second;
		else
			tag = "ur";			// 词表中不存在的词，缺省为ur
		strSent.replace(pos+1,1,tag);
		pos = strSent.find("/u",pos+1);
	}
}

void AugPronTag::TagPron(string& strSent)
{
	map < string, string > ::iterator it;
	size_t pos = strSent.find("/r");
	string word, tag;

	while(pos != -1)
	{
		size_t pos1 = strSent.rfind(" ",pos);
		word = strSent.substr(pos1+1,pos-pos1-1);
		it = mapPron.find(word);
		if(it != mapPron.end() )
			tag = (*it).second;
		else
			tag = "rs";		// 词表中不存在的词，缺省为rs
		strSent.replace(pos+1,1,tag);
		pos = strSent.find("/r",pos+1);
	}
}

void AugPronTag::Initialize()
{
	ifstream fAug( (g_strDataPath+"Augxiliary.txt").c_str() );
	ifstream fPron( (g_strDataPath+"Pronoun.txt").c_str() );
	if(!fAug || !fPron)
	{
		cout << "Cannot open Aug or Pron files!" << endl;
		exit(0);
	}

	string strline, word, tag;
	while(getline(fAug,strline) )
	{
		size_t pos = strline.find(' ');
		word = strline.substr(0,pos);
		tag = strline.substr(pos+1);
		mapAug[word] = tag;
	}

	while(getline(fPron,strline) )
	{
		size_t pos = strline.find(' ');
		word = strline.substr(0,pos);
		tag = strline.substr(pos+1);
		mapPron[word] = tag;
	}

	fAug.close();
	fPron.close();
}

void AugPronTag::Release()
{
	mapAug.clear();
	mapPron.clear();
}