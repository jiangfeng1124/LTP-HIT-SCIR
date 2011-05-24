#include "ConsFeatures.h"

///////////////////////////////////////////////////////////////
//	Function Name 	: ConsFeatures
//	Belong to Class : ConsFeature
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: 
//	Parameter Comment : const DataPreProcess *dataPreProc,
//				           int nodeID
///////////////////////////////////////////////////////////////
ConsFeatures::ConsFeatures(const DataPreProcess *dataPreProc,
						   int nodeID)
						  :Features(dataPreProc),
						   m_nodeID(nodeID)
{
	dataPreProc->m_myTree->GetNodeValue(m_depNode, m_nodeID);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ~ConsFeatures
//	Belong to Class : ConsFeature
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: 
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
ConsFeatures::~ConsFeatures()
{
}

//-----------------------------------------------------------------------//
//--        Define the function of the class	                      --//

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractType
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strType
///////////////////////////////////////////////////////////////
 void ConsFeatures::ExtractType(string& strType) const
{
	strType = "type_" + m_depNode.relation;
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractHeadword
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strHW
///////////////////////////////////////////////////////////////
 void ConsFeatures::ExtractHeadword(string& strHW) const
{
	int parentID = m_depNode.parent;
	if(parentID < 0)
	{	//process the punctuation and root
		strHW = S_NULL_WORD;
		return;
	}
	
	strHW = "headword_" + m_dataPreProc->m_ltpData->vecWord.at(parentID);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractDepword
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strDW
///////////////////////////////////////////////////////////////
 void ConsFeatures::ExtractDepword(string& strDW) const
{
	strDW = "depword_" + m_dataPreProc->m_ltpData->vecWord.at(m_nodeID);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosOfHW
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPosOfHW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractPosOfHW(string& strPosOfHW) const
{
	int parentID = m_depNode.parent;
	if(parentID < 0)
	{	//process the punctuation and root
		strPosOfHW = S_NULL_POS;
		return;
	}

	strPosOfHW = "headpos_" + m_dataPreProc->m_ltpData->vecPos.at(parentID);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosOfDW
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPosOfDW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractPosOfDW(string& strPosOfDW) const
{
	strPosOfDW = "dwpos_" + m_dataPreProc->m_ltpData->vecPos.at(m_nodeID);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractNe
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strNE
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractNe(string& strNE) const
{
	strNE = "ne_" + m_dataPreProc->m_vecNE.at(m_nodeID);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPreWord
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumesj
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractPreWord(string& strPW) const
{
	int begin = m_depNode.constituent.first;
	if (begin > 0)
	{
		strPW = "preword_" + m_dataPreProc->m_ltpData->vecWord.at(begin - 1);
	}
	else
	{
		strPW = "preword_" + string(S_NULL_WORD);
	}
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractNextWord
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strNW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractNextWord(string& strNW) const	
{
	int end = m_depNode.constituent.second;
	if (end < (m_dataPreProc->m_intItemNum - 1))
	{
		strNW = "nextword_" + m_dataPreProc->m_ltpData->vecWord.at(end + 1);
	}
	else
	{
		strNW = "nextword_" + string(S_NULL_WORD);
	}
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractFirstWord
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strFW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractFirstWord(string& strFW) const	
{
	strFW = "firstword_" + m_dataPreProc->m_ltpData->vecWord.at(m_depNode.constituent.first);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractLastWord
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strLW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractLastWord(string& strLW) const	
{
	strLW = "lastword_" + m_dataPreProc->m_ltpData->vecWord.at(m_depNode.constituent.second);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosOfPW
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPosOfPW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractPosOfPW(string& strPosOfPW) const	
{
	int begin = m_depNode.constituent.first;
	if (begin > 0)
	{
		strPosOfPW = "pwpos_" + m_dataPreProc->m_ltpData->vecPos.at(begin - 1);
	}
	else
	{
		strPosOfPW = "pwpos_" + string(S_NULL_POS);
	}
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosOfNW
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPosOfNW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractPosOfNW(string& strPosOfNW) const	
{
	int end = m_depNode.constituent.second;
	if (end < (m_dataPreProc->m_intItemNum - 1))
	{
		strPosOfNW = "nwpos_" + m_dataPreProc->m_ltpData->vecPos.at(end + 1);
	}
	else
	{
		strPosOfNW = "nwpos_" + string(S_NULL_POS);
	}
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosOfFW
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPosOfFW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractPosOfFW(string& strPosOfFW) const	
{
	strPosOfFW = "fwpos_" + m_dataPreProc->m_ltpData->vecPos.at(m_depNode.constituent.first);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosOfLW
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPosOfLW
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractPosOfLW(string& strPosOfLW) const	
{
	strPosOfLW = "lwpos_" + m_dataPreProc->m_ltpData->vecPos.at(m_depNode.constituent.second);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractRelOfRightSib
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strRelOfRS
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractRelOfRightSib(string& strRelOfRS) const	
{
	int rightSibID = m_dataPreProc->m_myTree->GetRightSib(m_nodeID);
	if (rightSibID == I_NULL_RIGHT)
	{
		strRelOfRS = "rightsib_rel_" + string(S_NULL_REL);
	}
	else
	{
		strRelOfRS = "rightsib_rel_" + m_dataPreProc->m_ltpData->vecRelation.at(rightSibID);
	}
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractRelOfLeftSib
//	Belong to Class : ConsFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strRelOfLS
///////////////////////////////////////////////////////////////
void ConsFeatures::ExtractRelOfLeftSib(string& strRelOfLS) const
{
	int leftSibID = m_dataPreProc->m_myTree->GetLeftSib(m_nodeID);
	if (leftSibID == I_NULL_ID)
	{
		strRelOfLS = "leftsib_rel_" + string(S_NULL_REL);
	} 
	else
	{
		strRelOfLS = "leftsib_rel_" + m_dataPreProc->m_ltpData->vecRelation.at(leftSibID);
	}
}
