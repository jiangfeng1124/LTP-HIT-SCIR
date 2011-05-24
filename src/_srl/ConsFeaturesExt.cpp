#include "ConsFeaturesExt.h"

//////////////////////////////////////////////////////////////////////////
ConsFeaturesExt::ConsFeaturesExt(const DataPreProcess *dataPreProc, 
								 int nodeID)
								 : ConsFeatures(dataPreProc, nodeID),Features(dataPreProc)
{

}

//////////////////////////////////////////////////////////////////////////
ConsFeaturesExt::~ConsFeaturesExt()
{

}

//////////////////////////////////////////////////////////////////////////
// features extract method
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractRelOfPW(string& strRelOfPW) const
{
	int begin = m_depNode.constituent.first;
	if (begin > 0)
	{
		strRelOfPW = "pwrel_" + m_dataPreProc->m_ltpData->vecRelation.at(begin - 1);
	}
	else
	{
		strRelOfPW = "pwrel_" + string(S_NULL_REL);
	}
}

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractRelOfNW(string& strRelOfNW) const
{
	int end = m_depNode.constituent.second;
	if (end < (m_dataPreProc->m_intItemNum - 1))
	{
		strRelOfNW = "nwrel_" + m_dataPreProc->m_ltpData->vecRelation.at(end + 1);
	}
	else
	{
		strRelOfNW = "nwrel_" + string(S_NULL_REL);
	}
}

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractRelOfFW(string& strRelOfFW) const
{
		strRelOfFW ="fwrel_" + m_dataPreProc->m_ltpData->vecRelation.at(m_depNode.constituent.first);
}

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractRelOfLW(string& strRelOfLW) const
{
	strRelOfLW = "lwrel_" + m_dataPreProc->m_ltpData->vecRelation.at(m_depNode.constituent.second);
}

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractWordOfRightSib(string& strWdOfRS) const
{
	int rightSibID = m_dataPreProc->m_myTree->GetRightSib(m_nodeID);
	if (rightSibID == I_NULL_RIGHT)
	{
		strWdOfRS = "rightsib_word_" + string(S_NULL_WORD);
	}
	else
	{
		strWdOfRS = "rightsib_word_" + m_dataPreProc->m_ltpData->vecWord.at(rightSibID);
	}
}

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractPosOfRightSib(string& strPosOfRS) const
{
	int rightSibID = m_dataPreProc->m_myTree->GetRightSib(m_nodeID);
	if (rightSibID == I_NULL_RIGHT)
	{
		strPosOfRS = "rightsib_pos_" + string(S_NULL_POS);
	}
	else
	{
		strPosOfRS = "rightsib_pos_" + m_dataPreProc->m_ltpData->vecPos.at(rightSibID);
	}
}

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractWordOfLeftSib(string& strWdOfLS) const
{
	int leftSibID = m_dataPreProc->m_myTree->GetLeftSib(m_nodeID);
	if (leftSibID == I_NULL_ID)
	{
		strWdOfLS = "leftsib_word_" + string(S_NULL_WORD);
	}
	else
	{
		strWdOfLS = "leftsib_word_" + m_dataPreProc->m_ltpData->vecWord.at(leftSibID);
	}
}

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractPosOfLeftSib(string& strPosOfLS) const
{
	int leftSibID = m_dataPreProc->m_myTree->GetLeftSib(m_nodeID);
	if (leftSibID == I_NULL_ID)
	{
		strPosOfLS = "leftsib_pos_" + string(S_NULL_POS);
	}
	else
	{
		strPosOfLS = "leftsib_pos_" + m_dataPreProc->m_ltpData->vecPos.at(leftSibID);
	}
}

//////////////////////////////////////////////////////////////////////////
// pattern: BegPos-MiddlePosPattern-EndPos
//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractBegEndPosPattern(string& strBEPosPt) const
{
	int begin;
	int end;
	string strInnerPat;
	vector<string> vecPos;
	vector<string> vecNSamePos;

	begin = m_depNode.constituent.first;
	end = m_depNode.constituent.second;

	//find the middle pos pattern - map
	if (begin == end)
	{
		strBEPosPt = "BEPosP_" + m_dataPreProc->m_ltpData->vecPos.at(begin);
	}
	else
	{
		for (int index = begin + 1; index < end; index++)
		{
			vecPos.push_back(m_dataPreProc->m_ltpData->vecPos.at(index));
		}

		//get the pattern
		strBEPosPt = "BEPosP_" + string(S_NULL_STR);
		strBEPosPt += m_dataPreProc->m_ltpData->vecPos.at(begin) + S_HYPHEN_TAG;
		RemoveSameItem(vecNSamePos, vecPos);
		JoinVecToStrByChar(strInnerPat, vecNSamePos, C_NE_SEP);
		strBEPosPt.append(strInnerPat);
		strBEPosPt += S_HYPHEN_TAG + m_dataPreProc->m_ltpData->vecPos.at(end);
	}
}

//////////////////////////////////////////////////////////////////////////
void ConsFeaturesExt::ExtractBegEndRelPattern(string& strBERelPt) const
{
	int begin;
	int end;
	string strInnerPat;
	vector<string> vecRel;
	vector<string> vecNSameRel;

	begin = m_depNode.constituent.first;
	end = m_depNode.constituent.second;

	//find the middle pos pattern - map
	if(begin == end)
	{
		strBERelPt = "BERelPt_" + m_dataPreProc->m_ltpData->vecRelation.at(begin);
	}
	else
	{
		for (int index = begin + 1; index < end; index++)
		{
			vecRel.push_back(m_dataPreProc->m_ltpData->vecRelation.at(index));
		}

		//get the pattern
		strBERelPt = "BERelPt_" + string(S_NULL_STR);
		strBERelPt += m_dataPreProc->m_ltpData->vecRelation.at(begin) + S_HYPHEN_TAG;
		RemoveSameItem(vecNSameRel, vecRel);
		JoinVecToStrByChar(strInnerPat, vecNSameRel, C_NE_SEP);
		strBERelPt.append(strInnerPat);	
		strBERelPt += S_HYPHEN_TAG + m_dataPreProc->m_ltpData->vecRelation.at(end);
	}
}
