#ifndef __FEATURES__
#define __FEATURES__

#include "DataPreProcess.h"
#include "MyLib.h"

class Features
{
public:
	Features(const DataPreProcess *dataPreProc);
	virtual ~Features();

public:
	//--------- Features about Constituent old begin -------------------------------//
	virtual void ExtractType(string& strType) const;	
	virtual void ExtractHeadword(string& strHW) const;	
	virtual void ExtractDepword(string& strDW) const;	
	virtual void ExtractPosOfHW(string& strPosOfHW) const;	
	virtual void ExtractPosOfDW(string& strPosOfDW) const;	
	virtual void ExtractNe(string& strNE) const;	
	virtual void ExtractPreWord(string& strPW) const;	
	virtual void ExtractNextWord(string& strNW) const;	
	virtual void ExtractFirstWord(string& strFW) const;	
	virtual void ExtractLastWord(string& strLW) const;	
	virtual void ExtractPosOfPW(string& strPosOfPW) const;	
	virtual void ExtractPosOfNW(string& strPosOfNW) const;	
	virtual void ExtractPosOfFW(string& strPosOfFW) const;	
	virtual void ExtractPosOfLW(string& strPosOfLW) const;	
	virtual void ExtractRelOfRightSib(string& strRelOfRS) const;	
	virtual void ExtractRelOfLeftSib(string& strRelOfLS) const;	
	//--------- Features about Constituent old end -------------------------------//
	//--------- Features about Constituent add begin -------------------------------//
	virtual void ExtractRelOfPW(string& strRelOfPW) const;	
	virtual void ExtractRelOfNW(string& strRelOfNW) const;	
	virtual void ExtractRelOfFW(string& strRelOfFW) const;	
	virtual void ExtractRelOfLW(string& strRelOfLW) const;	
	virtual void ExtractWordOfRightSib(string& strWdOfRS) const;
	virtual void ExtractPosOfRightSib(string& strPosOfRS) const;
	virtual void ExtractWordOfLeftSib(string& strWdOfLS) const;
	virtual void ExtractPosOfLeftSib(string& strPosOfLS) const;
	virtual void ExtractBegEndPosPattern(string& strBEPosPt) const;
	virtual void ExtractBegEndRelPattern(string& strBERelPt) const;
	//--------- Features about Constituent add end -------------------------------//


public:
	//--------- Features about predicate old begin ------------------------------//
	virtual void ExtractPosPatternOfPdChildren(string& strPosPatOfPC) const;	
	virtual void ExtractRelPatternOfPdChildren(string& strRelPatOfPC) const;	
	virtual void ExtractPosPatternOfPdSibs(string& strPosPatOfPS) const;	
	virtual void ExtractRelPatternOfPdSibs(string& strRelPatOfPS) const;	
	virtual void ExtractPdClass(string& strPdClass) const;	
	virtual void ExtractPredicate(string& strPD) const;	
	//--------- Features about predicate old end ------------------------------//	
	//--------- Features about predicate add begin------------------------------//
	virtual void ExtractPosSimpPatOfPdChildren(string& strPosSimpPatOfPC) const;	
	virtual void ExtractRelSimpPatOfPdChildren(string& strRelSimpPatOfPC) const;	
	virtual void ExtractPosSimpPatOfPdSibs(string& strPosSimpPatOfPS) const;	
	virtual void ExtractRelSimpPatOfPdSibs(string& strRelSimpPatOfPS) const;	
	//--------- Features about predicate add end------------------------------//

public:
	//-----Features about the relation between consitituent and predicate old begin -----//
	virtual void ExtractFamilyShip(string& strFS) const;	
	virtual void ExtractPosition(string& strPS) const;	
	virtual void ExtractPath(string& strPath) const;	
	virtual void ExtractPartPath(string& strPPath) const;	
	virtual void ExtractPOSOfRCPOfPdCons(string& strPOSOfRCPOfPdCons) const;
	virtual void ExtractRelOfRCPOfPdCons(string& strRelOfRCPOfPdCons) const;
	//-----Features about the relation between consitituent and old predicate end -----//
	//-----Features about the relation between consitituent and predicate add begin -----//
	virtual void ExtractDistance(string& strDis) const;
	virtual void ExtractDisRelativeLen(string& strDisRLen) const;
	virtual void ExtractSimpRelPathPattern(string& strSimpRelPath) const;
	virtual void ExtractSimpPosPathPattern(string& strSimpPosPath) const;
	//-----Features about the relation between consitituent and predicate add end -----//
	

protected:
	const DataPreProcess *m_dataPreProc;

};

#endif
