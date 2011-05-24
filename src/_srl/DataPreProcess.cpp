#include "DataPreProcess.h"

///////////////////////////////////////////////////////////////
//	�� �� �� : DataPreProcess
//	�������� : DataPreProcess
//	�������� : Constructor of class
//	������� : 
//	��    ע : 
//	��    �� : Frumes
//	ʱ    �� : 2006��11��23��
//	�� �� ֵ : 
//	����˵�� : const LTPData& ltpData
///////////////////////////////////////////////////////////////
DataPreProcess::DataPreProcess(const LTPData* ltpData,
							   const SRLDictionary *srlDic)
							   :m_srlDic(srlDic)
{
	BuildStruct(ltpData);
}

///////////////////////////////////////////////////////////////
//	�� �� �� : DataPreProcess
//	�������� : ~DataPreProcess
//	�������� : Destructor of class
//	������� : 
//	��    ע : 
//	��    �� : Frumes
//	ʱ    �� : 2006��11��23��
//	�� �� ֵ : 
//	����˵�� : 
///////////////////////////////////////////////////////////////
DataPreProcess::~DataPreProcess()
{
	DestroyStruct();
}

///////////////////////////////////////////////////////////////
//	Function Name 	: BuildStruct
//	Belong to Class : DataPreProcess
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006��12��31��
//	Return Value 	: void
//	Parameter Comment : const LTPData *ltpData
///////////////////////////////////////////////////////////////
void DataPreProcess::BuildStruct(const LTPData* ltpData)
{
	m_ltpData = ltpData;
	m_myTree = new MyTree(m_ltpData);
	m_intItemNum = m_myTree->m_depTree.nodeNum;

	MapNEToCons(); //note: changed for PTBtoDep
}

///////////////////////////////////////////////////////////////
//	Function Name 	: DestroyStruct
//	Belong to Class : DataPreProcess
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006��12��31��
//	Return Value 	: void
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
void DataPreProcess::DestroyStruct()
{
	delete m_myTree;
	m_vecNE.clear();
}

///////////////////////////////////////////////////////////////
//	Function Name 	: MapNEToCons
//	Belong to Class : DataPreProcess
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006��12��31��
//	Return Value 	: void
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
void DataPreProcess::MapNEToCons()
{
	string strSingleNE;
	string strExternNE;
	DepNode dnNode;

	int index;
	index = 0;
	while (index < m_myTree->m_depTree.nodeNum)
	{
		m_myTree->GetNodeValue(dnNode, index);

		strSingleNE = SingleNE(dnNode.constituent.first, dnNode.constituent.second);
		strExternNE = ExternNE(dnNode.constituent.first, dnNode.constituent.second);
		if(strSingleNE.compare(S_NULL_NE))
		{
			m_vecNE.push_back(strSingleNE);
		}
		else if(strExternNE.compare(S_NULL_NE))
		{
			m_vecNE.push_back(strExternNE);
		}
		else
		{
			m_vecNE.push_back(S_NULL_NE);
		}

		index++;
	}

}

///////////////////////////////////////////////////////////////
//	�� �� �� : SingleNE
//	�������� : Constituent
//	�������� : Check if the constituent is a single NE
//	������� : 
//	��    ע : 
//	��    �� : hjliu
//	ʱ    �� : 2006��6��29��
//	�� �� ֵ : String&
//	����˵�� : const int intBeg,
//				 const int intEnd,
//				 const vector<string>& strNE
///////////////////////////////////////////////////////////////
string DataPreProcess::SingleNE(int intBeg, 
							    int intEnd) const
{
	string strNETMP;
	string strNE = S_NULL_STR;
	string strNullNE = S_NULL_NE;

	strNE.resize(I_NE_SIZE);
	if(intBeg == intEnd)
	{
		strNETMP = m_ltpData->vecNe.at(intBeg);
		//match with "S-Nx"
		if((strNETMP.length() == I_NE_LENGTH) &&
			(strNETMP[I_NE_FIRSTPS] == C_NE_SINGLE) &&
			(strNETMP[I_NE_SEPPS] == C_NE_SEP))
		{
			strNE = strNETMP.substr(I_NE_BEGINPS, I_NE_SIZE);
			return strNE;
		}
		else
		{
			return strNullNE;
		}
	}
	else
	{
		return strNullNE;
	}
}

///////////////////////////////////////////////////////////////
//	�� �� �� : ExternNE
//	�������� : Constituent
//	�������� : 
//	������� : 
//	��    ע : 
//	��    �� : hjliu
//	ʱ    �� : 2006��6��29��
//	�� �� ֵ : String&
//	����˵�� : const int intBeg,
//				 const int intEnd,
//				 const vector<string>& strNE
///////////////////////////////////////////////////////////////
string DataPreProcess::ExternNE(int intBeg, 
							    int intEnd) const
{
	string strNETMPB;
	string strNETMPE;
	string strNETMP;
	string strNE;
	string strNullNE = S_NULL_NE;

	//being match "B-Nx" and end match "E-Nx", and other match "I-Nx"
	strNETMPB = m_ltpData->vecNe.at(intBeg);
	strNETMPE = m_ltpData->vecNe.at(intEnd);
	strNE.resize(I_NE_SIZE);
	if((strNETMPB.length() == I_NE_LENGTH) &&				//length = 4
		(strNETMPE.length() == I_NE_LENGTH) &&			
		(strNETMPB[I_NE_FIRSTPS] == C_NE_BEGIN) &&		//first char: B
		(strNETMPE[I_NE_FIRSTPS] == C_NE_END) &&		//first char: E
		(!strNETMPB.substr(I_NE_BEGINPS, I_NE_SIZE).compare(strNETMPE.substr(I_NE_BEGINPS, I_NE_SIZE))) //the Nx is the same
		) //if end
	{
		//check the innr item
		int i;
		for(i = intBeg + 1 ; i < intEnd; i++)
		{
			strNETMP = m_ltpData->vecNe.at(i);
			if(strNETMP[I_NE_FIRSTPS] != C_NE_IN)
			{
				return strNullNE;
			}
		}

		//asign ne type
		strNE = strNETMPB.substr(I_NE_BEGINPS, I_NE_SIZE);
		return strNE;
	}
	else
	{
		return strNullNE;
	}
}