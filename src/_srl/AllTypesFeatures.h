#ifndef  _ALL_TYPES_FEATURES_
#define _ALL_TYPES_FEATURES_

#include "ConsFeaturesExt.h"
#include "PdFeaturesExt.h"
#include "ConsPdRelFeaturesExt.h"

class AllTypesFeatures : 
	  public ConsFeaturesExt, public PdFeaturesExt, public ConsPdRelFeaturesExt
{
public:
	AllTypesFeatures(const DataPreProcess *dataPreProc,
					 int nodeID,
					 int pdNodeID);
	~AllTypesFeatures();

public:


};

#endif