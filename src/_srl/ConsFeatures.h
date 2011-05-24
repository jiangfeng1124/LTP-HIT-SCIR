///////////////////////////////////////////////////////////////
//	File Name     :ConsFeatures.h
//	File Function :
//	Author 	      : Frumes
//	Create Time   : 2006Äê12ÔÂ31ÈÕ
//	Project Name  £ºNewSRLBaseLine
//	Operate System : 
//	Remark        :
//	History£º     : 
///////////////////////////////////////////////////////////////

#ifndef  __CONS_FEATURES__
#define __CONS_FEATURES__

#include <string>
#include "Features.h"

class ConsFeatures : public virtual Features
{
public:
	ConsFeatures(const DataPreProcess *dataPreProc,
				 int nodeID);
	~ConsFeatures();

public:
	virtual void ExtractType(string& strType) const;	
	virtual void ExtractHeadword(string& strHW) const;	
	virtual void ExtractDepword(string& strDW) const;	
	virtual void ExtractPosOfHW(string& strPosOfHW) const;	
	virtual void ExtractPosOfDW(string& strPosOfDW) const;	
	virtual void ExtractNe(string& strNE) const;	
	virtual void ExtractPreWord(string& strPW) const;	
	virtual void ExtractNextWord(string& strNW) const;	
	virtual void ExtractFirstWord(string& strFW) const;	
	virtual void ExtractLastWord(string& strLW) const;	
	virtual void ExtractPosOfPW(string& strPosOfPW) const;	
	virtual void ExtractPosOfNW(string& strPosOfNW) const;	
	virtual void ExtractPosOfFW(string& strPosOfFW) const;	
	virtual void ExtractPosOfLW(string& strPosOfLW) const;	
	virtual void ExtractRelOfRightSib(string& strRelOfRS) const;	
	virtual void ExtractRelOfLeftSib(string& strRelOfLS) const;
	
	
protected:
	const int m_nodeID;

protected:
	DepNode m_depNode;
};

#endif