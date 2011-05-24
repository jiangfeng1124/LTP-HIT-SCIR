#include "Features.h"

Features::Features(const DataPreProcess *dataPreProc)
				  :m_dataPreProc(dataPreProc)
{		
}

Features::~Features()
{
}

//----------------funciton interface--------------------//
//Features about Constituent
void Features::ExtractType(string& strType) const
{
}
void Features::ExtractHeadword(string& strHW) const
{
}
void Features::ExtractDepword(string& strDW) const
{
}
void Features::ExtractPosOfHW(string& strPosOfHW) const
{
}
void Features::ExtractPosOfDW(string& strPosOfDW) const
{
}
void Features::ExtractNe(string& strNE) const
{
}
void Features::ExtractPreWord(string& strPW) const
{
}
void Features::ExtractNextWord(string& strNW) const
{
}
void Features::ExtractFirstWord(string& strFW) const
{
}
void Features::ExtractLastWord(string& LW) const
{
}
void Features::ExtractPosOfPW(string& strPosOfPW) const
{
}
void Features::ExtractPosOfNW(string& strPosOfNW) const
{
}
void Features::ExtractPosOfFW(string& strPosOfFW) const
{
}
void Features::ExtractPosOfLW(string& strPosOfLW) const
{
}
void Features::ExtractRelOfRightSib(string& strRelOfRS) const
{
}
void Features::ExtractRelOfLeftSib(string& strRelOfLS) const
{
}
//Features about Constituent - add
void Features::ExtractRelOfPW(string& strRelOfPW) const	
{
}

void Features::ExtractRelOfNW(string& strRelOfNW) const	
{
}

void Features::ExtractRelOfFW(string& strRelOfFW) const	
{
}

void Features::ExtractRelOfLW(string& strRelOfLW) const	
{
}

void Features::ExtractWordOfRightSib(string& strWdOfRS) const
{
}
void Features::ExtractPosOfRightSib(string& strPosOfRS) const
{
}
void Features::ExtractWordOfLeftSib(string& strWdOfLS) const
{
}
void Features::ExtractPosOfLeftSib(string& strPosOfLS) const
{
}
void Features::ExtractBegEndPosPattern(string& strBEPosPt) const
{
}
void Features::ExtractBegEndRelPattern(string& strBERelPt) const
{
}


//Features about predicate
void Features::ExtractPosPatternOfPdChildren(string& strPosPatOfPC) const
{
}
void Features::ExtractRelPatternOfPdChildren(string& strRelPatOfPC) const
{
}
void Features::ExtractPosPatternOfPdSibs(string& strPosPatOfPS) const
{
}
void Features::ExtractRelPatternOfPdSibs(string& trstrRelPatOfPS) const
{
}
void Features::ExtractPdClass(string& strPdClass) const
{
}
void Features::ExtractPredicate(string& strPD) const
{
}
//Features about predicate - add
void Features::ExtractPosSimpPatOfPdChildren(string& strPosSimpPatOfPC) const
{
}
void Features::ExtractRelSimpPatOfPdChildren(string& strRelSimpPatOfPC) const
{
}
void Features::ExtractPosSimpPatOfPdSibs(string& strPosSimpPatOfPS) const
{
}
void Features::ExtractRelSimpPatOfPdSibs(string& strRelSimpPatOfPS) const
{
}


//Features about the relation between consitituent and predicate
void Features::ExtractFamilyShip(string& strFS) const
{
}
void Features::ExtractPosition(string& strPS) const
{
}
void Features::ExtractPath(string& strPath) const
{
}
void Features::ExtractPartPath(string& strPPath) const
{
}
void Features::ExtractPOSOfRCPOfPdCons(string& strPOSOfRCPOfPdCons) const
{
}
void Features::ExtractRelOfRCPOfPdCons(string& strRelOfRCPOfPdCons) const
{
}
//Features about the relation between consitituent and predicate - add
void Features::ExtractDistance(string& strDis) const
{
}
void Features::ExtractDisRelativeLen(string& strDisRLen) const
{
}
void Features::ExtractSimpRelPathPattern(string& strSimpRelPath) const
{
}
void Features::ExtractSimpPosPathPattern(string& strSimpPosPath) const
{
}

