#include "PdFeaturesExt.h"

//////////////////////////////////////////////////////////////////////////
// constructor and destructor
//////////////////////////////////////////////////////////////////////////
PdFeaturesExt::PdFeaturesExt(const DataPreProcess *dataPreProc, 
							 int pdNodeID)
							: PdFeatures(dataPreProc, pdNodeID), Features(dataPreProc)
{

}

PdFeaturesExt::~PdFeaturesExt()
{

}

//////////////////////////////////////////////////////////////////////////
// features extract method
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void PdFeaturesExt::ExtractPosSimpPatOfPdChildren(string& strPosSimpPatOfPC) const
{
	string strPos;
	vector<string> vecChiPos;
	vector<string> vecSimpPos;
	deque<int>::const_iterator itChildren;


	// 1. get the children	
	if (m_pdDepNode.dequeChildren.empty())
	{	//no children
		strPosSimpPatOfPC = S_NULL_POSPAT_PDCHR;
		return;
	}

	itChildren = m_pdDepNode.dequeChildren.begin();
	while (itChildren != m_pdDepNode.dequeChildren.end())
	{
		strPos = m_dataPreProc->m_ltpData->vecPos.at(*itChildren);
		vecChiPos.push_back(strPos);
		itChildren++;
	}
	
	// 2. remove the same neighboring pos, and add end
	RemoveNeighboringSameItem(vecSimpPos, vecChiPos);
	JoinVecToStrByChar(strPosSimpPatOfPC, vecSimpPos, C_NE_SEP);
	
}

//////////////////////////////////////////////////////////////////////////
void PdFeaturesExt::ExtractRelSimpPatOfPdChildren(string& strRelSimpPatOfPC) const
{
	string strRel;
	vector<string> vecChiRel;
	vector<string> vecSimpRel;
	deque<int>::const_iterator itDequeChildren;


	// 1. get the children		
	if (m_pdDepNode.dequeChildren.empty())
	{	//no children
		strRelSimpPatOfPC = S_NULL_RELPAT_PDCHR;
		return;
	}

	itDequeChildren = m_pdDepNode.dequeChildren.begin();
	while (itDequeChildren != m_pdDepNode.dequeChildren.end())
	{
		strRel = m_dataPreProc->m_ltpData->vecRelation.at(*itDequeChildren);
		vecChiRel.push_back(strRel);

		itDequeChildren++;
	}

	// 2. remove the same neighboring Rel, and add
	RemoveNeighboringSameItem(vecSimpRel, vecChiRel);
	JoinVecToStrByChar(strRelSimpPatOfPC, vecSimpRel, C_NE_SEP);

}

//////////////////////////////////////////////////////////////////////////
void PdFeaturesExt::ExtractPosSimpPatOfPdSibs(string& strPosSimpPatOfPS) const
{
	string strPos;
	deque<int> dequeSibs;
	deque<int>::iterator itDequeSibs;
	vector<string> vecSibsPos;
	vector<string> vecSimpPos;	

	// 1. get siblings	
	m_dataPreProc->m_myTree->GetAllSibs(m_pdNodeID, dequeSibs);
	if (dequeSibs.empty())
	{	//no siblings
		strPosSimpPatOfPS = S_NULL_POSPAT_PDSIBS;
		return;
	}

	itDequeSibs = dequeSibs.begin();	
	while (itDequeSibs != dequeSibs.end())
	{
		strPos = m_dataPreProc->m_ltpData->vecPos.at(*itDequeSibs);
		vecSibsPos.push_back(strPos);
		itDequeSibs++;
	}


	// 2. remove the same neighboring Pos
	RemoveNeighboringSameItem(vecSimpPos, vecSibsPos);
	JoinVecToStrByChar(strPosSimpPatOfPS, vecSimpPos);
}

//////////////////////////////////////////////////////////////////////////
void PdFeaturesExt::ExtractRelSimpPatOfPdSibs(string& strRelSimpPatOfPS) const
{
	string strRel;
	deque<int> dequeSibs;
	deque<int>::iterator itDequeSibs;
	vector<string> vecSibsRel;
	vector<string> vecSimpRel;

	// 1. get siblings	
	m_dataPreProc->m_myTree->GetAllSibs(m_pdNodeID, dequeSibs);
	if (dequeSibs.empty())
	{	//no siblings
		strRelSimpPatOfPS = S_NULL_RELPAT_PDSIBS;
		return;
	}

	itDequeSibs = dequeSibs.begin();	
	while (itDequeSibs != dequeSibs.end())
	{
		strRel = m_dataPreProc->m_ltpData->vecRelation.at(*itDequeSibs);
		vecSibsRel.push_back(strRel);
		itDequeSibs++;
	}

	// 2. remove the same neighboring Rel
	RemoveNeighboringSameItem(vecSimpRel, vecSibsRel);
	JoinVecToStrByChar(strRelSimpPatOfPS, vecSimpRel);
}
