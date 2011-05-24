#ifndef __CONS_PD_REL_FEATURES_EXT__
#define __CONS_PD_REL_FEATURES_EXT__

#include "ConsPdRelFeatures.h"

class ConsPdRelFeaturesExt : public ConsPdRelFeatures
{
public:
	ConsPdRelFeaturesExt(const DataPreProcess *dataPreProc,
						 int nodeID,
						 int pdNodeID);
	~ConsPdRelFeaturesExt();

public:
	virtual void ExtractDistance(string& strDis) const;
	virtual void ExtractDisRelativeLen(string& strDisRLen) const;
	virtual void ExtractSimpRelPathPattern(string& strSimpRelPath) const;
	virtual void ExtractSimpPosPathPattern(string& strSimpPosPath) const;
	//virtual void ExtractPath(string& strPath) const;
	//virtual void ExtractPartPath(string& strPPath) const;

protected:
	void GetPathIDSequence(vector<int>& vecPathSeq, const string& strPath) const;

private:
	//void ParsePathEncodeString(string& strPath, const string& strEncodePath, const vector<string>& vecProp) const;


};


#endif