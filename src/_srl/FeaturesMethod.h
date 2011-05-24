#ifndef _FEATUES_METHOD_
#define _FEATUES_METHOD_

#include "FeaturesPack.h"
#include "AllTypesFeatures.h"
#include "SRLConfig.h"

//some typedef
typedef void (*EXTRACTFEAT)(string& strFeat, const Features* feat);
typedef map<string, EXTRACTFEAT>::value_type valNameToFuncType;


class FeaturesMethod
{
public:
	FeaturesMethod(const SRLConfig* srlConf);
	~FeaturesMethod();
	
	virtual void ExtractConsFeat(vector<string>& vecFeat, const Features* feat) const;
	virtual void ExtrcatPdFeat(vector<string>& vecFeat, const Features* feat) const;
	virtual void ExtractConsPdRelFeat(vector<string>& vecFeat, const Features* feat) const;
	virtual void ExtractCombFeat(vector<string>& vecFeat, const Features* feat) const;

protected:
	void MapFeatNameToFeatFunc();
	void ExtractTypeFeat(vector<string>& vecFeat, 
						 const Features* feat, 
						 const vector<string>& vecConf) const;

protected:
	map<string, EXTRACTFEAT> m_mapStr2FeatFunc;
	const SRLConfig *m_srlConf;
};

#endif