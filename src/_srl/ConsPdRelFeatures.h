///////////////////////////////////////////////////////////////
//	File Name     :ConsPdRelFeatures.h
//	File Function :
//	Author 	      : Frumes
//	Create Time   : 2006Äê12ÔÂ31ÈÕ
//	Project Name  £ºNewSRLBaseLine
//	Operate System : 
//	Remark        :
//	History£º     : 
///////////////////////////////////////////////////////////////

#ifndef  __CONS_PD_REL_FEATURES__
#define __CONS_PD_REL_FEATURES__

#include "Features.h"

class ConsPdRelFeatures : public virtual Features
{
public:
	ConsPdRelFeatures(const DataPreProcess *dataPreProc,
					  int nodeID,
					  int pdNodeID);
	~ConsPdRelFeatures();

public:
	//Features about the relation between consitituent and predicate
	virtual void ExtractFamilyShip(string& strFS) const;	
	virtual void ExtractPosition(string& strPS) const;	
	virtual void ExtractPath(string& strPath) const;	
	virtual void ExtractPartPath(string& strPPath) const;	
	virtual void ExtractPOSOfRCPOfPdCons(string& strPOSOfRCPOfPdCons) const;
	virtual void ExtractRelOfRCPOfPdCons(string& strRelOfRCPOfPdCons) const;

private:
	void ParsePathEncodeString(string& strPath, 
							   const string& strEncodePath, 
							   const vector<string>& vecProp) const;
	
protected:
	const int m_nodeID;
	const int m_pdNodeID;

private:
};


#endif