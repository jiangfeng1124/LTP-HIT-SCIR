///////////////////////////////////////////////////////////////
//	File Name     :SRLConfig.h
//	File Function :
//	Author 	      : Frumes
//	Create Time   : 2006��12��31��
//	Project Name  ��NewSRLBaseLine
//	Operate System : 
//	Remark        :
//	History��     : 
///////////////////////////////////////////////////////////////


#ifndef _SRL_CONFIG_
#define _SRL_CONFIG_

#include "MyLib.h"

class SRLConfig
{
public:
	SRLConfig();
	~SRLConfig();

	bool LoadFeatSelConf(const char* fileName);
	bool LoadFeatCombConf(const char* fileName);
		
public:
	vector<string> m_vecConsFeatSelConf;
	vector<string> m_vecPdFeatSelConf;
	vector<string> m_vecConsPdRelFeatSelConf;

	vector<string> m_vecFeatCombConf;

};


#endif