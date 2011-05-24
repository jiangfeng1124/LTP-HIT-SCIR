///////////////////////////////////////////////////////////////
//	File Name     :SRLDictionary.h
//	File Function :
//	Author 	      : Frumes
//	Create Time   : 2006��12��31��
//	Project Name  ��NewSRLBaseLine
//	Operate System : 
//	Remark        :
//	History��     : 
///////////////////////////////////////////////////////////////

#ifndef __SRL_DICTIONARY__
#define __SRL_DICTIONARY__

#include <map>
#include <string>
#include <iostream>
#include "ConstVar.h"
using namespace std;

typedef map<string, string>::value_type valType;

class SRLDictionary
{
public:
	SRLDictionary();
	~SRLDictionary();
	bool LoadPdClassDic(const char* fileName);

public:
	map<string, string> m_mapPd2Code;

};

#endif