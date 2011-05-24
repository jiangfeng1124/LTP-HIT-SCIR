#include "FeaturesPack.h"

//--------- Features about Constituent begin -------------------------------//
void ExtractType(string& strType, 
				 const Features* feat)
{
	feat->ExtractType(strType);
}

void ExtractHeadword(string& strHW, 
					 const Features* feat)
{
	feat->ExtractHeadword(strHW);
}

void ExtractDepword(string& strDW, 
					const Features* feat)	
{
	feat->ExtractDepword(strDW);
}

void ExtractPosOfHW(string& strPosOfHW, 
					const Features* feat)	
{
	feat->ExtractPosOfHW(strPosOfHW);
}

void ExtractPosOfDW(string& strPosOfDW, 
					const Features* feat)	
{
	feat->ExtractPosOfDW(strPosOfDW);
}

void ExtractNe(string& strNE, 
			   const Features* feat)	
{
	feat->ExtractNe(strNE);
}

void ExtractPreWord(string& strPW, 
					const Features* feat)	
{
	feat->ExtractPreWord(strPW);
}

void ExtractNextWord(string& strNW, 
					 const Features* feat)	
{
	feat->ExtractNextWord(strNW);
}

void ExtractFirstWord(string& strFW, 
					  const Features* feat)	
{
	feat->ExtractFirstWord(strFW);
}

void ExtractLastWord(string& strLW, 
					 const Features* feat)	
{
	feat->ExtractLastWord(strLW);
}

void ExtractPosOfPW(string& strPosOfPW, 
					const Features* feat)	
{
	feat->ExtractPosOfPW(strPosOfPW);
}

void ExtractPosOfNW(string& strPosOfNW, 
					const Features* feat)	
{
	feat->ExtractPosOfNW(strPosOfNW);
}

void ExtractPosOfFW(string& strPosOfFW, 
					const Features* feat)	
{
	feat->ExtractPosOfFW(strPosOfFW);
}
void ExtractPosOfLW(string& strPosOfLW, 
					const Features* feat)	
{
	feat->ExtractPosOfLW(strPosOfLW);
}

void ExtractRelOfRightSib(string& strRelOfRS, 
						  const Features* feat)	
{
	feat->ExtractRelOfRightSib(strRelOfRS);
}

void ExtractRelOfLeftSib(string& strRelOfLS, 
						 const Features* feat)
{
	feat->ExtractRelOfLeftSib(strRelOfLS);
}
//--------- Features about Constituent end -------------------------------//
//--------- Features about Constituent add begin -------------------------------//
void ExtractRelOfPW(string& strRelOfPW,
					const Features* feat)
{
	feat->ExtractRelOfPW(strRelOfPW);
}

void ExtractRelOfNW(string& strRelOfNW,
					const Features* feat)
{
	feat->ExtractRelOfNW(strRelOfNW);
}

void ExtractRelOfFW(string& strRelOfFW,
					const Features* feat)
{
	feat->ExtractRelOfFW(strRelOfFW);
}

void ExtractRelOfLW(string& strRelOfLW,
					const Features* feat)
{
	feat->ExtractRelOfLW(strRelOfLW);
}

void ExtractWordOfRightSib(string& strWdOfRS,
						   const Features* feat)
{
	feat->ExtractWordOfRightSib(strWdOfRS);
}

void ExtractPosOfRightSib(string& strPosOfRS,
						  const Features* feat)
{
	feat->ExtractPosOfRightSib(strPosOfRS);
}

void ExtractWordOfLeftSib(string& strWdOfLS,
						  const Features* feat)
{
	feat->ExtractWordOfLeftSib(strWdOfLS);
}

void ExtractPosOfLeftSib(string& strPosOfLS,
						 const Features* feat)
{
	feat->ExtractPosOfLeftSib(strPosOfLS);
}

void ExtractBegEndPosPattern(string& strBEPosPt,
							 const Features* feat)
{
	feat->ExtractBegEndPosPattern(strBEPosPt);
}

void ExtractBegEndRelPattern(string& strBERelPt,
							 const Features* feat)
{
	feat->ExtractBegEndRelPattern(strBERelPt);
}
//--------- Features about Constituent add end -------------------------------//


//--------- Features about predicate begin ------------------------------//
void ExtractPosPatternOfPdChildren(string& strPosPatOfPC, 
								   const Features* feat)	
{
	feat->ExtractPosPatternOfPdChildren(strPosPatOfPC);
}

void ExtractRelPatternOfPdChildren(string& strRelPatOfPC, 
								   const Features* feat)	
{
	feat->ExtractRelPatternOfPdChildren(strRelPatOfPC);
}

void ExtractPosPatternOfPdSibs(string& strPosPatOfPS, 
							   const Features* feat)	
{
	feat->ExtractPosPatternOfPdSibs(strPosPatOfPS);
}

void ExtractRelPatternOfPdSibs(string& strRelPatOfPS, 
							   const Features* feat)	
{
	feat->ExtractRelPatternOfPdSibs(strRelPatOfPS);;
}
void ExtractPdClass(string& strPdClass, 
					const Features* feat)	
{
	feat->ExtractPdClass(strPdClass);
}

void ExtractPredicate(string& strPD, 
					  const Features* feat)	
{
	feat->ExtractPredicate(strPD);
}
//--------- Features about predicate end ------------------------------//
//--------- Features about predicate add begin ------------------------------//
void ExtractPosSimpPatOfPdChildren(string& strPosSimpPatOfPC,
								   const Features* feat)	
{
	feat->ExtractPosSimpPatOfPdChildren(strPosSimpPatOfPC);
}

void ExtractRelSimpPatOfPdChildren(string& strRelSimpPatOfPC,
								   const Features* feat)
{
	feat->ExtractRelSimpPatOfPdChildren(strRelSimpPatOfPC);
}
void ExtractPosSimpPatOfPdSibs(string& strPosSimpPatOfPS,
							   const Features* feat)	
{
	feat->ExtractPosSimpPatOfPdSibs(strPosSimpPatOfPS);
}

void ExtractRelSimpPatOfPdSibs(string& strRelSimpPatOfPS,
							   const Features* feat)	
{
	feat->ExtractRelSimpPatOfPdSibs(strRelSimpPatOfPS);
}
//--------- Features about predicate add end ------------------------------//


//-----Features about the relation between consitituent and predicate begin -----//
void ExtractFamilyShip(string& strFS, 
					   const Features* feat)	
{
	feat->ExtractFamilyShip(strFS);
}

void ExtractPosition(string& strPS, 
					 const Features* feat)	
{
	feat->ExtractPosition(strPS);
}

void ExtractPath(string& strPath, 
				 const Features* feat)	
{
	feat->ExtractPath(strPath);
}

void ExtractPartPath(string& strPPath, 
					 const Features* feat)	
{
	feat->ExtractPartPath(strPPath);
}

void ExtractPOSOfRCPOfPdCons(string& strPOSOfRCPOfPdCons, 
							 const Features* feat)
{
	feat->ExtractPOSOfRCPOfPdCons(strPOSOfRCPOfPdCons);
}

void ExtractRelOfRCPOfPdCons(string& strRelOfRCPOfPdCons, 
							 const Features* feat)
{
	feat->ExtractRelOfRCPOfPdCons(strRelOfRCPOfPdCons);
}
//-----Features about the relation between consitituent and predicate end -----//
//-----Features about the relation between consitituent and predicate add begin -----//
void ExtractDistance(string& strDis,
					 const Features* feat)
{
	feat->ExtractDistance(strDis);
}

void ExtractDisRelativeLen(string& strDisRLen,
						   const Features* feat)
{
	feat->ExtractDisRelativeLen(strDisRLen);
}

void ExtractSimpRelPathPattern(string& strSimpRelPath,
							   const Features* feat)
{
	feat->ExtractSimpRelPathPattern(strSimpRelPath);
}

void ExtractSimpPosPathPattern(string& strSimpPosPath,
							   const Features* feat)
{
	feat->ExtractSimpPosPathPattern(strSimpPosPath);
}
//-----Features about the relation between consitituent and predicate add end -----//

