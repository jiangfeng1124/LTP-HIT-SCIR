#ifndef  __SRL_BASELINE_EXT__
#define __SRL_BASELINE_EXT__

#include "SRLBaseline.h"
#include "Configuration.h"
#include "FeatureExtractor.h"

class SRLBaselineExt : public SRLBaseline
{
public:
	SRLBaselineExt(const DataPreProcess* dataPreProc, 
				   const FeaturesMethod* featMethod);
	~SRLBaselineExt();

public:
	void ExtractFeatures(VecFeatForSent& vecAllFeatures, 
						 VecPosForSent& vecAllPos) const;
    //following four method is for feature extracting, used in CoNLL2009
	void conll_ExtractFeatures(
		VecFeatForSent& vecAllFeatures,
		VecPosForSent& vecAllPos
		) const;
	void construct_lines(
		vector<string>& lines
		) const;
	void get_feature_config(
		FeatureCollection& feature_collection,
		vector<int>& feature_numbers,
		vector<string>& feature_prefixes,
		const Configuration& configuration
		) const;
	void open_select_config(
		const string& select_config, 
		vector< vector<string> >& m_select_features
		) const;

protected:
	bool IsFilter(int nodeID, 
				  int intCurPd) const;

	//extract features
	void ExtractConsFeatures(VecFeatForVerb& vecFeatAllCons) const;
	void ExtractPdFeatures(VecFeatForVerb& vecFeatAllPd) const;

};

#endif
