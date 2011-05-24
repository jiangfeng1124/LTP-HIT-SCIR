#include "SRLBaseline.h"

///////////////////////////////////////////////////////////////
//	Function Name 	: SRLBaseline
//	Belong to Class : SRLBaselin
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2007��1��4��
//	Return Value 	: 
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
SRLBaseline::SRLBaseline(const DataPreProcess* dataPreProc, 
						 const FeaturesMethod* featMethod)
						 :m_dataPreProc(dataPreProc),
						  m_featMethod(featMethod)						 
{

}
///////////////////////////////////////////////////////////////
//	�� �� �� : ~SRLBaseline
//	�������� : SRLBaselin
//	�������� : The Class Destructor
//	������� : 
//	��    ע : 
//	��    �� : hjliu
//	ʱ    �� : 2006��6��21��
//	�� �� ֵ : 
//	����˵�� : 
///////////////////////////////////////////////////////////////
SRLBaseline::~SRLBaseline()
{
}

///////////////////////////////////////////////////////////////
//	�� �� �� : ExtractFeatures
//	�������� : SRLBaseline
//	�������� : 
//	������� : 
//	��    ע : 
//	��    �� : hjliu
//	ʱ    �� : 2006��6��21��
//	�� �� ֵ : void
//	����˵�� : vector<VecFeatForVerb>& vecAllFeatures, 
//				vector<ArgPos>& vecConsPos
///////////////////////////////////////////////////////////////
void SRLBaseline::ExtractFeatures(VecFeatForSent& vecAllFeatures, 
								  VecPosForSent& vecAllPos)	 const
{
	//first: extract the ConsFeatures for all the nodes
	//--------------------------------------//
	// node 1: feat1 feat2 feat3 ... featm
	// node 2: feat1 feat2 feat3 ... featm
	// ...
	// node n: feat1 feat2 feat3 ... featm
	//-------------------------------------//
	VecFeatForVerb vecFeatAllCons;	
	ExtractConsFeatures(vecFeatAllCons);

	//second:extract the PdFeatures for all the predicate
	//--------------------------------------//
	// predicate 1: feat1 feat2 feat3 ... featm
	// predicate 2: feat1 feat2 feat3 ... featm
	// ...
	// predicate n: feat1 feat2 feat3 ... featm
	//--------------------------------------//
	VecFeatForVerb vecFeatAllPd;
	ExtractPdFeatures(vecFeatAllPd);

	//finally: extract the ConsPdRelFeatures for the unFiltered nodes
	int pdIndex;
	vector<int>::const_iterator itPredicate;

	pdIndex = 0;
	itPredicate = m_vecPredicate.begin();
	while (itPredicate != m_vecPredicate.end())
	{
		int predID;
		VecFeatForVerb vecFeatVerb;
		VecPosForVerb vecPosVerb;

		predID = *itPredicate;
		for (int nodeID = 0; nodeID < m_dataPreProc->m_intItemNum; nodeID++)
		{
			if (!IsFilter(nodeID, predID))
			{
				//1. extract the ConsPdRelFeatures for the unFiltered nodes
				VecFeatForCons vecFeatConsPd;
				ConsPdRelFeatures consPdRelFeat(m_dataPreProc, nodeID, predID);

				m_featMethod->ExtractConsPdRelFeat(vecFeatConsPd, &consPdRelFeat);

				//1.5. extract the combine features, add by hjliu at 2007-4.23
				AllTypesFeatures allTypeFeat(m_dataPreProc, nodeID, predID);
				VecFeatForCons vecFeatComb;
				m_featMethod->ExtractCombFeat(vecFeatComb, &allTypeFeat);

				//2. add the ConsFeatures of unFiltered node to the vector - vecFeatVerb
				vecFeatConsPd.insert(vecFeatConsPd.end(), vecFeatAllCons.at(nodeID).begin(), vecFeatAllCons.at(nodeID).end());

				//3. add the PdFeatures of unFiltered node to the vector - vecFeatVerb
				vecFeatConsPd.insert(vecFeatConsPd.end(), vecFeatAllPd.at(pdIndex).begin(), vecFeatAllPd.at(pdIndex).end());

				//3.5 add the combine features of unFiltered node to the vector
				vecFeatConsPd.insert(vecFeatConsPd.end(), vecFeatComb.begin(), vecFeatComb.end());
				
				//4. push_back the vecFeatCons to vecFeatVerb
				vecFeatVerb.push_back(vecFeatConsPd);

				//5. get position of unFiltered nodes, and push_back to vecPosVerb
				DepNode curNode;
				m_dataPreProc->m_myTree->GetNodeValue(curNode, nodeID);
				vecPosVerb.push_back(curNode.constituent);
			}
		} //for - for each node corresponding to the predicate

		//features and position of the nodes corresponding to the predicate
		vecAllFeatures.push_back(vecFeatVerb);
		vecAllPos.push_back(vecPosVerb);

		pdIndex++;
		itPredicate++;
	} //while - for each predicate

}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractConsFeatures
//	Belong to Class : SRLBaseline
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2007��1��4��
//	Return Value 	: void
//	Parameter Comment : VecFeatForVerb& vecFeatAllCons
///////////////////////////////////////////////////////////////
void SRLBaseline::ExtractConsFeatures(VecFeatForVerb& vecFeatAllCons) const
{
	int depNodeNum;
	int index;	
	
	depNodeNum = m_dataPreProc->m_intItemNum;
	index = 0;
	while (index < depNodeNum)
	{
		VecFeatForCons vecFeatCons;
		ConsFeatures consFeat(m_dataPreProc, index);

		m_featMethod->ExtractConsFeat(vecFeatCons, &consFeat);
		vecFeatAllCons.push_back(vecFeatCons);
		index++;
	}
}


///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPdFeatures
//	Belong to Class : SRLBaseline
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2007��1��4��
//	Return Value 	: void
//	Parameter Comment : VecFeatForVerb& vecFeatAllPd
///////////////////////////////////////////////////////////////
void SRLBaseline::ExtractPdFeatures(VecFeatForVerb& vecFeatAllPd) const
{
	vector<int>::const_iterator itPredicate;
	itPredicate = m_vecPredicate.begin();
	while (itPredicate != m_vecPredicate.end())
	{
		VecFeatForCons vecFeatPd;
		PdFeatures pdFeat(m_dataPreProc, *itPredicate);

		m_featMethod->ExtrcatPdFeat(vecFeatPd, &pdFeat);
		vecFeatAllPd.push_back(vecFeatPd);
		itPredicate++;
	}
}

///////////////////////////////////////////////////////////////
//	�� �� �� : IsFilter
//	�������� : SRLBaseline
//	�������� : Check if the node will be filtered: only when the node 
//			   is predicate and punctation
//	������� : 
//	��    ע : 
//	��    �� : hjliu
//	ʱ    �� : 2006��7��14��
//	�� �� ֵ : void
//	����˵�� : const int nodeID
///////////////////////////////////////////////////////////////
inline bool SRLBaseline::IsFilter(int nodeID, 
								  int intCurPd) const
{
	DepNode depNode;
	m_dataPreProc->m_myTree->GetNodeValue(depNode, nodeID);

	//the punctuation nodes, current predicate node
	//changed for PTBtoDep, only filter the current predicate
	if(nodeID == intCurPd)
	{
		return 1;
	}
	else
	{
		return 0;
	}

	//return 0;
}


//for now used
///////////////////////////////////////////////////////////////
//	Function Name 	: setPredicate
//	Belong to Class : SRLBaseline
//	Function  	: 
//	Processing 	: 
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2007��1��5��
//	Return Value 	: void
//	Parameter Comment : const vector<int>& vecPred
///////////////////////////////////////////////////////////////
void SRLBaseline::SetPredicate(const vector<int>& vecPred)
{
	m_vecPredicate = vecPred;
}
