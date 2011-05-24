#ifndef _SRL_BASELINE_
#define _SRL_BASELINE_
#pragma warning(disable:4786)

#include <iostream>
#include "AllTypesFeatures.h"
#include "FeaturesMethod.h"

using namespace std;

class SRLBaseline
{
public:
	SRLBaseline(const DataPreProcess* dataPreProc, 
				const FeaturesMethod* featMethod);
	~SRLBaseline();	

public:

	//for now used
	void SetPredicate(const vector<int>& vecPred);
    void ExtractFeatures(VecFeatForSent& vecAllFeatures, 
						 VecPosForSent& vecAllPos) const;

protected:
	bool IsFilter(int nodeID, 
				  int intCurPd) const;

	//extract features
	void ExtractConsFeatures(VecFeatForVerb& vecFeatAllCons) const;
	void ExtractPdFeatures(VecFeatForVerb& vecFeatAllPd) const;

protected:
	const DataPreProcess *m_dataPreProc;
	const FeaturesMethod *m_featMethod;

	vector<int>    m_vecPredicate;
};

#endif
