#ifndef __CONS_FEATURES_EXT__
#define __CONS_FEATURES_EXT__

#include "ConsFeatures.h"

class ConsFeaturesExt : public ConsFeatures
{
public:
	ConsFeaturesExt(const DataPreProcess *dataPreProc,
					int nodeID);
	~ConsFeaturesExt();

public:
	virtual void ExtractRelOfPW(string& strRelOfPW) const;	
	virtual void ExtractRelOfNW(string& strRelOfNW) const;	
	virtual void ExtractRelOfFW(string& strRelOfFW) const;	
	virtual void ExtractRelOfLW(string& strRelOfLW) const;	
	virtual void ExtractWordOfRightSib(string& strWdOfRS) const;
	virtual void ExtractPosOfRightSib(string& strPosOfRS) const;
	virtual void ExtractWordOfLeftSib(string& strWdOfLS) const;
	virtual void ExtractPosOfLeftSib(string& strPosOfLS) const;
	virtual void ExtractBegEndPosPattern(string& strBEPosPt) const;
	virtual void ExtractBegEndRelPattern(string& strBERelPt) const;

};

#endif