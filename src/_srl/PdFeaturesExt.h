#ifndef __PD_FEATURES_EXT__
#define __PD_FEATURES_EXT__

#include "PdFeatures.h"

class PdFeaturesExt : public PdFeatures
{
public:
	PdFeaturesExt(const DataPreProcess *dataPreProc,
			      int pdNodeID);
	~PdFeaturesExt();

public:
	virtual void ExtractPosSimpPatOfPdChildren(string& strPosSimpPatOfPC) const;	
	virtual void ExtractRelSimpPatOfPdChildren(string& strRelSimpPatOfPC) const;	
	virtual void ExtractPosSimpPatOfPdSibs(string& strPosSimpPatOfPS) const;	
	virtual void ExtractRelSimpPatOfPdSibs(string& strRelSimpPatOfPS) const;	

};

#endif