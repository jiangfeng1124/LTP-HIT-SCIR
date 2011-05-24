#include "FeaturesMethod.h"

//////////////////////////////////////////////////////////////////////////
FeaturesMethod::FeaturesMethod(const SRLConfig* srlConf)
							  :m_srlConf(srlConf)
{
	MapFeatNameToFeatFunc();
}

//////////////////////////////////////////////////////////////////////////
FeaturesMethod::~FeaturesMethod()
{

}

//////////////////////////////////////////////////////////////////////////
void FeaturesMethod::ExtractConsFeat(vector<string>& vecFeat, const Features* feat) const
{
	ExtractTypeFeat(vecFeat, feat, m_srlConf->m_vecConsFeatSelConf);
}

//////////////////////////////////////////////////////////////////////////
void FeaturesMethod::ExtrcatPdFeat(vector<string>& vecFeat, const Features* feat) const
{
	ExtractTypeFeat(vecFeat, feat, m_srlConf->m_vecPdFeatSelConf);
}

//////////////////////////////////////////////////////////////////////////
void FeaturesMethod::ExtractConsPdRelFeat(vector<string>& vecFeat, const Features* feat) const
{
	ExtractTypeFeat(vecFeat, feat, m_srlConf->m_vecConsPdRelFeatSelConf);
}

//////////////////////////////////////////////////////////////////////////
void FeaturesMethod::ExtractCombFeat(vector<string>& vecFeat, const Features* feat) const
{
	string strFeat;
	vector<string> vecConf;
	vector<string> vecOneFeat;
	vector<string>::iterator itOneFeat;
	vector<string>::const_iterator itCombConf;

	itCombConf = m_srlConf->m_vecFeatCombConf.begin();
	while (itCombConf != m_srlConf->m_vecFeatCombConf.end())
	{
		vecConf.clear();
		split_bychar(*itCombConf, vecConf, C_ADD);
		ExtractTypeFeat(vecOneFeat, feat, vecConf);

		//get the combine feat
		strFeat = S_NULL_STR;
		itOneFeat = vecOneFeat.begin();
		while (itOneFeat != (vecOneFeat.end() - 1) )
		{
			strFeat += *itOneFeat + C_ADD;
			itOneFeat++;
		}
		strFeat += *itOneFeat;

		vecFeat.push_back(strFeat);

		itCombConf++;
	}
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void FeaturesMethod::ExtractTypeFeat(vector<string>& vecFeat, 
									 const Features* feat, 
									 const vector<string>& vecConf) const
{
	string strFeat;
	EXTRACTFEAT ExtractFeatFunc;
	vector<string>::const_iterator itConf;
	map<string, EXTRACTFEAT>::const_iterator itMap;

	vecFeat.clear();
	itConf = vecConf.begin();
	while (itConf != vecConf.end())
	{
		itMap = m_mapStr2FeatFunc.find(*itConf);
		if (itMap != m_mapStr2FeatFunc.end())
		{
			ExtractFeatFunc = (*itMap).second;
			(*ExtractFeatFunc)(strFeat, feat);

			vecFeat.push_back(strFeat);
		}

		itConf++;
	}

}

//////////////////////////////////////////////////////////////////////////
void FeaturesMethod::MapFeatNameToFeatFunc()
{
	//depNode feattures
	m_mapStr2FeatFunc.insert( valNameToFuncType("Type", ExtractType) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("Headword", ExtractHeadword) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("Depword", ExtractDepword) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosOfHW", ExtractPosOfHW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosOfDW", ExtractPosOfDW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("Ne", ExtractNe) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PreWord", ExtractPreWord) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("NextWord", ExtractNextWord) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("FirstWord", ExtractFirstWord) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("LastWord", ExtractLastWord) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosOfPW", ExtractPosOfPW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosOfNW", ExtractPosOfNW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosOfFW", ExtractPosOfFW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosOfLW", ExtractPosOfLW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelOfRightSib", ExtractRelOfRightSib) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelOfLeftSib", ExtractRelOfLeftSib) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("Ne", ExtractNe) );

	//predicate features
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosPatternOfPdChildren", ExtractPosPatternOfPdChildren) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelPatternOfPdChildren", ExtractRelPatternOfPdChildren) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosPatternOfPdSibs", ExtractPosPatternOfPdSibs) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelPatternOfPdSibs", ExtractRelPatternOfPdSibs) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PdClass", ExtractPdClass) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("Predicate", ExtractPredicate) );

	//relation features
	m_mapStr2FeatFunc.insert( valNameToFuncType("FamilyShip", ExtractFamilyShip) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("Position", ExtractPosition) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("Path", ExtractPath) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PartPath", ExtractPartPath) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("POSOfRCPOfPdCons", ExtractPOSOfRCPOfPdCons) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelOfRCPOfPdCons", ExtractRelOfRCPOfPdCons) );

	//add some new features - at 2007.4.29
	//depNode features add
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelOfPW", ExtractRelOfPW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelOfNW", ExtractRelOfNW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelOfFW", ExtractRelOfFW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelOfLW", ExtractRelOfLW) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("WordOfRightSib", ExtractWordOfRightSib) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosOfRightSib", ExtractPosOfRightSib) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("WordOfLeftSib", ExtractWordOfLeftSib) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosOfLeftSib", ExtractPosOfLeftSib) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("BegEndPosPattern", ExtractBegEndPosPattern) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("BegEndRelPattern", ExtractBegEndRelPattern) );

	//predicate features add
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosSimpPatOfPdChildren", ExtractPosSimpPatOfPdChildren) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelSimpPatOfPdChildren", ExtractRelSimpPatOfPdChildren) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("PosSimpPatOfPdSibs", ExtractPosSimpPatOfPdSibs) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("RelSimpPatOfPdSibs", ExtractRelSimpPatOfPdSibs) );
	
	//relation features add
	m_mapStr2FeatFunc.insert( valNameToFuncType("Distance", ExtractDistance) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("DisRelativeLen", ExtractDisRelativeLen) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("SimpRelPathPattern", ExtractSimpRelPathPattern) );
	m_mapStr2FeatFunc.insert( valNameToFuncType("SimpPosPathPattern", ExtractSimpPosPathPattern) );

}
