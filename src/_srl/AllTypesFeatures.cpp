#include "AllTypesFeatures.h"

//////////////////////////////////////////////////////////////////////////
AllTypesFeatures::AllTypesFeatures(const DataPreProcess *dataPreProc, 
								   int nodeID, 
								   int pdNodeID)
								   : Features(dataPreProc),
									 ConsFeaturesExt(dataPreProc, nodeID),
									 PdFeaturesExt(dataPreProc, pdNodeID),
									 ConsPdRelFeaturesExt(dataPreProc, nodeID, pdNodeID)
{

}

//////////////////////////////////////////////////////////////////////////
AllTypesFeatures::~AllTypesFeatures()
{

}