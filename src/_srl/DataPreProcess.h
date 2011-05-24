///////////////////////////////////////////////////////////////
//	File Name     :DataPreProcess.h
//	File Function : 
//	Author 	      : Frumes
//	Create Time   : 2006��12��31��
//	Project Name  ��NewSRLBaseLine
//	Operate System : 
//	Remark        : get data from IR-LTP platform
//	History��     : 
///////////////////////////////////////////////////////////////

#ifndef __LTP_PROPRECESS__
#define __LTP_PROPRECESS__

#include "MyTree.h"
#include "SRLDictionary.h"

class DataPreProcess
{
public:
	DataPreProcess(const LTPData* ltpData,
				   const SRLDictionary* srlDic);
	~DataPreProcess();

private:
	void BuildStruct(const LTPData* ltpData);
	void DestroyStruct();
	void MapNEToCons();

private:
	string SingleNE(int intBeg, 
					int intEnd) const;
	string ExternNE(int intBeg, 
					int intEnd) const;

public:
	
	const LTPData *m_ltpData;
	const SRLDictionary *m_srlDic;
	MyTree *m_myTree;
	vector<string> m_vecNE;
	int m_intItemNum; //the Chinese word numbers after segmentation
};

#endif