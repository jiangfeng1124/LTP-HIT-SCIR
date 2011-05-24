#include "PdFeatures.h"
#include "SRLDictionary.h"

//-----------------------------------------------------------------------//
//--        Define the constructor and destructor                      --//
///////////////////////////////////////////////////////////////
//	Function Name 	: PdFeatures
//	Belong to Class : PdFeature
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: 
//	Parameter Comment : const DataPreProcess *dataPreProc,
//				           int pdNodeID
///////////////////////////////////////////////////////////////
PdFeatures::PdFeatures(const DataPreProcess *dataPreProc, 
					   int pdNodeID)
					  :Features(dataPreProc),
					   m_pdNodeID(pdNodeID)
{
	dataPreProc->m_myTree->GetNodeValue(m_pdDepNode, m_pdNodeID);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ~PdFeatures
//	Belong to Class : PdFeature
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: 
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
PdFeatures::~PdFeatures()
{
}

//-----------------------------------------------------------------------//
//--        Define the function of the class	                      --//
///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosPatternOfPdChildren
//	Belong to Class : PdFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPosPatOfPC
///////////////////////////////////////////////////////////////
void PdFeatures::ExtractPosPatternOfPdChildren(string& strPosPatOfPC) const	
{
	//note: the children is ordered when tree is initial
	string strPos;
	deque<int> dequeChildren; 
	deque<int>::iterator itDequeChildren;

	dequeChildren = m_pdDepNode.dequeChildren;
	itDequeChildren = dequeChildren.begin();
	strPosPatOfPC = S_NULL_STR;

	if (itDequeChildren == dequeChildren.end())
	{	//no children
		strPosPatOfPC = S_NULL_POSPAT_PDCHR;
		return;
	}

	while(itDequeChildren != (dequeChildren.end() - 1))
	{   //add child POS until the one before last
		strPos = m_dataPreProc->m_ltpData->vecPos.at(*itDequeChildren);
		strPosPatOfPC.append(strPos);
		strPosPatOfPC.append(S_HYPHEN_TAG);

		itDequeChildren++;		
	}
	//add POS of last child
	strPos = m_dataPreProc->m_ltpData->vecPos.at(*itDequeChildren);
	strPosPatOfPC.append(strPos);

}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractRelPatternOfPdChildren
//	Belong to Class : PdFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strRelPatOfPC
///////////////////////////////////////////////////////////////
void PdFeatures::ExtractRelPatternOfPdChildren(string& strRelPatOfPC) const	
{
	//note: the children is ordered when tree is initial
	string strRel;
	deque<int> dequeChildren; 
	deque<int>::iterator itDequeChildren;

	dequeChildren = m_pdDepNode.dequeChildren;
	itDequeChildren = dequeChildren.begin();
	strRelPatOfPC = S_NULL_STR;

	if (itDequeChildren == dequeChildren.end())
	{	//no children
		strRelPatOfPC = S_NULL_RELPAT_PDCHR;
		return;
	}

	while(itDequeChildren != (dequeChildren.end() - 1))
	{   //add child Rel until the one before last
		strRel = m_dataPreProc->m_ltpData->vecRelation.at(*itDequeChildren);
		strRelPatOfPC.append(strRel);
		strRelPatOfPC.append(S_HYPHEN_TAG);

		itDequeChildren++;		
	}
	//add POS of last child
	strRel = m_dataPreProc->m_ltpData->vecRelation.at(*itDequeChildren);
	strRelPatOfPC.append(strRel);

}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosPatternOfPdSibs
//	Belong to Class : PdFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPosPatOfPS
///////////////////////////////////////////////////////////////
void PdFeatures::ExtractPosPatternOfPdSibs(string& strPosPatOfPS) const	
{
	string strPos;
	deque<int> dequeSibs;
	deque<int>::iterator itDequeSibs;

	strPosPatOfPS = S_NULL_STR;
	m_dataPreProc->m_myTree->GetAllSibs(m_pdNodeID, dequeSibs);
	itDequeSibs = dequeSibs.begin();	
	
	if (itDequeSibs == dequeSibs.end())
	{	//no siblings
		strPosPatOfPS = S_NULL_POSPAT_PDSIBS;
		return;
	}

	while (itDequeSibs != (dequeSibs.end() - 1))
	{	//add child POS until the one before last
		strPos = m_dataPreProc->m_ltpData->vecPos.at(*itDequeSibs);
		strPosPatOfPS.append(strPos);
		strPosPatOfPS.append(S_HYPHEN_TAG);

		itDequeSibs++;
	}
	strPos = m_dataPreProc->m_ltpData->vecPos.at(*itDequeSibs);
	strPosPatOfPS.append(strPos);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractRelPatternOfPdSibs
//	Belong to Class : PdFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strRelPatOfPS
///////////////////////////////////////////////////////////////
void PdFeatures::ExtractRelPatternOfPdSibs(string& strRelPatOfPS) const	
{
	string strRel;
	deque<int> dequeSibs;
	deque<int>::iterator itDequeSibs;

	strRelPatOfPS = S_NULL_STR;
	m_dataPreProc->m_myTree->GetAllSibs(m_pdNodeID, dequeSibs);
	itDequeSibs = dequeSibs.begin();

	if (itDequeSibs == dequeSibs.end())
	{	//no siblings
		strRelPatOfPS= S_NULL_RELPAT_PDSIBS;
		return;
	}

	while (itDequeSibs != (dequeSibs.end() - 1))
	{	//add child Rel until the one before last
		strRel = m_dataPreProc->m_ltpData->vecRelation.at(*itDequeSibs);
		strRelPatOfPS.append(strRel);
		strRelPatOfPS.append(S_HYPHEN_TAG);

		itDequeSibs++;
	}
	strRel = m_dataPreProc->m_ltpData->vecRelation.at(*itDequeSibs);
	strRelPatOfPS.append(strRel);
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPdClass
//	Belong to Class : PdFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPdClass
///////////////////////////////////////////////////////////////
void PdFeatures::ExtractPdClass(string& strPdClass) const	
{
	string strPdWord = m_dataPreProc->m_ltpData->vecWord.at(m_pdNodeID);
	map<string, string>::const_iterator itPdClass;

	itPdClass = m_dataPreProc->m_srlDic->m_mapPd2Code.find(strPdWord);
	if (itPdClass == m_dataPreProc->m_srlDic->m_mapPd2Code.end())
	{
		strPdClass = S_NULL_PD_CLASS;
		return;
	}

	strPdClass = (*itPdClass).second;
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPredicate
//	Belong to Class : PdFeatures
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPD
///////////////////////////////////////////////////////////////
void PdFeatures::ExtractPredicate(string& strPD) const
{
	strPD = m_dataPreProc->m_ltpData->vecWord.at(m_pdNodeID);
}
