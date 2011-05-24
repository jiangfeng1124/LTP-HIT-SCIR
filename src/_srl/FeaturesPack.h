///////////////////////////////////////////////////////////////
//	File Name     :FeaturesPack.h
//	File Function :
//	Author 	      : Frumes
//	Create Time   : 2006Äê12ÔÂ31ÈÕ
//	Project Name  £ºNewSRLBaseLine
//	Operate System : 
//	Remark        : the packaging of the features extract function
//	History£º     : 
///////////////////////////////////////////////////////////////

#ifndef __FEATURES_PACK__
#define __FEATURES_PACK__

#include "Features.h"

//--------- Features about Constituent begin -------------------------------//
void ExtractType(string& strType, 
				 const Features* feat);	
void ExtractHeadword(string& strHW, 
					 const Features* feat);	
void ExtractDepword(string& strDW, 
					const Features* feat);	
void ExtractPosOfHW(string& strPosOfHW, 
					const Features* feat);	
void ExtractPosOfDW(string& strPosOfDW, 
					const Features* feat);	
void ExtractNe(string& strNE, 
			   const Features* feat);	
void ExtractPreWord(string& strPW, 
					const Features* feat);	
void ExtractNextWord(string& strNW, 
					 const Features* feat);	
void ExtractFirstWord(string& strFW, 
					  const Features* feat);	
void ExtractLastWord(string& strLW, 
					 const Features* feat);	
void ExtractPosOfPW(string& strPosOfPW, 
					const Features* feat);	
void ExtractPosOfNW(string& strPosOfNW, 
					const Features* feat);	
void ExtractPosOfFW(string& strPosOfFW, 
					const Features* feat);	
void ExtractPosOfLW(string& strPosOfLW, 
					const Features* feat);	
void ExtractRelOfRightSib(string& strRelOfRS, 
						  const Features* feat);	
void ExtractRelOfLeftSib(string& strRelOfLS, 
						 const Features* feat);
//--------- Features about Constituent end -------------------------------//
//--------- Features about Constituent add begin -------------------------------//
void ExtractRelOfPW(string& strRelOfPW,
					const Features* feat);	
void ExtractRelOfNW(string& strRelOfNW,
					const Features* feat);	
void ExtractRelOfFW(string& strRelOfFW,
					const Features* feat);	
void ExtractRelOfLW(string& strRelOfLW,
					const Features* feat);	
void ExtractWordOfRightSib(string& strWdOfRS,
						   const Features* feat);
void ExtractPosOfRightSib(string& strPosOfRS,
						  const Features* feat);
void ExtractWordOfLeftSib(string& strWdOfLS,
						  const Features* feat);
void ExtractPosOfLeftSib(string& strPosOfLS,
						 const Features* feat);
void ExtractBegEndPosPattern(string& strBEPosPt,
							 const Features* feat);
void ExtractBegEndRelPattern(string& strBERelPt,
							 const Features* feat);
//--------- Features about Constituent add end -------------------------------//


//--------- Features about predicate begin ------------------------------//
void ExtractPosPatternOfPdChildren(string& strPosPatOfPC, 
								   const Features* feat);	
void ExtractRelPatternOfPdChildren(string& strRelPatOfPC, 
								   const Features* feat);	
void ExtractPosPatternOfPdSibs(string& strPosPatOfPS, 
							   const Features* feat);	
void ExtractRelPatternOfPdSibs(string& strRelPatOfPS, 
							   const Features* feat);	
void ExtractPdClass(string& strPdClass, 
					const Features* feat);	
void ExtractPredicate(string& strPD, 
					  const Features* feat);	
//--------- Features about predicate end ------------------------------//	
//--------- Features about predicate add begin ------------------------------//	
void ExtractPosSimpPatOfPdChildren(string& strPosSimpPatOfPC,
								   const Features* feat);	
void ExtractRelSimpPatOfPdChildren(string& strRelSimpPatOfPC,
								   const Features* feat);	
void ExtractPosSimpPatOfPdSibs(string& strPosSimpPatOfPS,
							   const Features* feat);	
void ExtractRelSimpPatOfPdSibs(string& strRelSimpPatOfPS,
							   const Features* feat);	
//--------- Features about predicate add end ------------------------------//	


//-----Features about the relation between consitituent and predicate begin -----//
void ExtractFamilyShip(string& strFS, 
					   const Features* feat);	
void ExtractPosition(string& strPS, 
					 const Features* feat);	
void ExtractPath(string& strPath, 
				 const Features* feat);	
void ExtractPartPath(string& strPPath, 
					 const Features* feat);	
void ExtractPOSOfRCPOfPdCons(string& strPOSOfRCPOfPdCons, 
							 const Features* feat);
void ExtractRelOfRCPOfPdCons(string& strRelOfRCPOfPdCons, 
							 const Features* feat);
//-----Features about the relation between consitituent and predicate end -----//
//-----Features about the relation between consitituent and predicate add begin -----//
void ExtractDistance(string& strDis,
					 const Features* feat);
void ExtractDisRelativeLen(string& strDisRLen,
						   const Features* feat);
void ExtractSimpRelPathPattern(string& strSimpRelPath,
							   const Features* feat);
void ExtractSimpPosPathPattern(string& strSimpPosPath,
							   const Features* feat);
//-----Features about the relation between consitituent and predicate add end -----//

#endif