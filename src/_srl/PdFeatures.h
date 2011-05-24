///////////////////////////////////////////////////////////////
//	File Name     :PdFeatures.h
//	File Function :
//	Author 	      : Frumes
//	Create Time   : 2006Äê12ÔÂ31ÈÕ
//	Project Name  £ºNewSRLBaseLine
//	Operate System : 
//	Remark        :
//	History£º     : 
///////////////////////////////////////////////////////////////

#ifndef __PD_FEATURES__
#define __PD_FEATURES__

#include "Features.h"

class PdFeatures : public virtual Features
{
public:
	PdFeatures(const DataPreProcess *dataPreProc,
			   int pdNodeID);
	~PdFeatures();

public:
	virtual void ExtractPosPatternOfPdChildren(string& strPosPatOfPC) const;	
	virtual void ExtractRelPatternOfPdChildren(string& strRelPatOfPC) const;	
	virtual void ExtractPosPatternOfPdSibs(string& strPosPatOfPS) const;	
	virtual void ExtractRelPatternOfPdSibs(string& strRelPatOfPS) const;	
	virtual void ExtractPdClass(string& strPdClass) const;	
	virtual void ExtractPredicate(string& strPD) const;	

protected:
	const int m_pdNodeID; 

protected:
	DepNode m_pdDepNode;
};

#endif