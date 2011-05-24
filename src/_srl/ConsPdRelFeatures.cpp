#include "ConsPdRelFeatures.h"

//-----------------------------------------------------------------------//
//--        Define the constructor and destructor                      --//

///////////////////////////////////////////////////////////////
//	Function Name 	: ConsPdRelFeatures
//	Belong to Class : ConsPdRelFeature
//	Function  	:
//	Processing 	:
//	Remark 		:
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	:
//	Parameter Comment : const DataPreProcess *dataPreProc,
//				             int nodeID,
//				             int pdNodeID
///////////////////////////////////////////////////////////////
ConsPdRelFeatures::ConsPdRelFeatures(const DataPreProcess *dataPreProc,
									 int nodeID,
									 int pdNodeID)
									:Features(dataPreProc),
									 m_nodeID(nodeID),
									 m_pdNodeID(pdNodeID)
{
}

ConsPdRelFeatures::~ConsPdRelFeatures()
{
}

//-----------------------------------------------------------------------//
//--        Define the function of the class	                      --//
///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractFamilyShip
//	Belong to Class : ConsPdRelFeatures
//	Function  	:
//	Processing 	:
//	Remark 		:
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strFS
///////////////////////////////////////////////////////////////
void ConsPdRelFeatures::ExtractFamilyShip(string& strFS) const
{
	m_dataPreProc->m_myTree->GetFamilyShip(strFS, m_nodeID, m_pdNodeID);
    strFS = "familyship_" + strFS;
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPosition
//	Belong to Class : ConsPdRelFeatures
//	Function  	:
//	Processing 	:
//	Remark 		:
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPS
///////////////////////////////////////////////////////////////
void ConsPdRelFeatures::ExtractPosition(string& strPS) const
{
	if (m_nodeID < m_pdNodeID)
	{
		strPS = S_PS_BEFORE;
	}
	else if (m_nodeID > m_pdNodeID)
	{
		strPS = S_PS_AFTER;
	}
	else
	{
		strPS = S_PS_PD;
	}

    strPS = "position_" + strPS;
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPath
//	Belong to Class : ConsPdRelFeatures
//	Function  	:
//	Processing 	:
//	Remark 		:
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPath
///////////////////////////////////////////////////////////////
void ConsPdRelFeatures::ExtractPath(string& strPath) const
{
	vector<string> vecPath;
	m_dataPreProc->m_myTree->GetAllNodePath(m_pdNodeID, vecPath);

	strPath = S_NULL_STR;
	ParsePathEncodeString(strPath, vecPath.at(m_nodeID), m_dataPreProc->m_ltpData->vecRelation);

    strPath = "path_" + strPath;
}

///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPartPath
//	Belong to Class : ConsPdRelFeatures
//	Function  	:
//	Processing 	:
//	Remark 		:
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : string& strPPath
///////////////////////////////////////////////////////////////
void ConsPdRelFeatures::ExtractPartPath(string& strPPath) const
{
	//first get path features
	string strPath;
	vector<string> vecPath;
	m_dataPreProc->m_myTree->GetAllNodePath(m_pdNodeID, vecPath);

	strPath = S_NULL_STR;
	strPPath = S_NULL_STR;
	ParsePathEncodeString(strPath, vecPath.at(m_nodeID), m_dataPreProc->m_ltpData->vecRelation);

	//get partpath from path
	strPPath = strPath;
	string::size_type posUp;
	string::size_type posDown;
	posUp = strPath.find_first_of(C_UP, 0); //find first '>' and '<'
	posDown = strPath.find_first_of(C_DOWN, 0);

	//if '>' or '<' not found, then the partpath = path
	if ( (posUp != string::npos) &&
		(posDown != string::npos) )
	{
		if (posUp > posDown)
		{	//the path first '<' then '>'
			strPPath.replace(strPPath.begin() + posUp, strPPath.end(), S_NULL_STR);
		}
		else
		{	//the path first '>' then '<'
			strPPath.replace(strPPath.begin() + posDown, strPPath.end(), S_NULL_STR);
		}
	}

    strPPath = "partpath_" + strPPath;
}


///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractPOSOfRCPOfPdCons
//	Belong to Class : ConsPdRelFeatures
//	Function  	:
//	Processing 	:
//	Remark 		:
//	Author 		: Frumes
//	Time 		: 2007年1月2日
//	Return Value 	: void
//	Parameter Comment : string& strPOSOfRCPOfPdCons
///////////////////////////////////////////////////////////////
void ConsPdRelFeatures::ExtractPOSOfRCPOfPdCons(string& strPOSOfRCPOfPdCons) const
{
	int intRCPOfPdCons = m_dataPreProc->m_myTree->GetRCParent(m_nodeID, m_pdNodeID);
	if (intRCPOfPdCons == I_NULL_RCP)
	{
		strPOSOfRCPOfPdCons = S_NULL_POS;
	}

	strPOSOfRCPOfPdCons = "POSOfRCPOfPdCons_" + m_dataPreProc->m_ltpData->vecPos.at(intRCPOfPdCons);
}


///////////////////////////////////////////////////////////////
//	Function Name 	: ExtractRelPatternOfPdSibs
//	Belong to Class : ConsPdRelFeatures
//	Function  	:
//	Processing 	:
//	Remark 		:
//	Author 		: Frumes
//	Time 		: 2007年1月2日
//	Return Value 	: void
//	Parameter Comment : string& strRelOfRCPOfPdCons
///////////////////////////////////////////////////////////////
void ConsPdRelFeatures::ExtractRelOfRCPOfPdCons(string& strRelOfRCPOfPdCons) const
{
	int intRCPOfPdCons = m_dataPreProc->m_myTree->GetRCParent(m_nodeID, m_pdNodeID);
	if (intRCPOfPdCons == I_NULL_RCP)
	{
		strRelOfRCPOfPdCons = S_NULL_REL;
	}

	strRelOfRCPOfPdCons = "RelOfRCPOfPdCons_" + m_dataPreProc->m_ltpData->vecRelation.at(intRCPOfPdCons);

}

///////////////////////////////////////////////////////////////
//	Function Name 	: ParsePathEncodeString
//	Belong to Class : ConsPdRelFeatures
//	Function  	:
//	Processing 	:
//	Remark 		:
//	Author 		: Frumes
//	Time 		: 2007年1月2日
//	Return Value 	: void
//	Parameter Comment : string& strPath,
//				                const string& strEncodePath,
//				                const vector<string>& vecProp
///////////////////////////////////////////////////////////////
void ConsPdRelFeatures::ParsePathEncodeString(string& strPath,
											  const string& strEncodePath,
											  const vector<string>& vecProp) const
{
	char num[I_WORD_LEN];
	int nodeID;
	int strLength = strEncodePath.length();
	int index = 0;
	int i = 0;
	strPath.append(S_NULL_STR);

	while (index < strLength)
	{
		switch(strEncodePath.at(index))
		{
		case C_UP:
			{
				num[i] = C_END_CHAR;
				i = 0;

				//append the proportion in the end
				nodeID = atoi(num);
				strPath.append(vecProp.at(nodeID));
				strPath.append(S_PATH_UP);
			}

			break;
		case C_DOWN:
			{
				num[i] = C_END_CHAR;
				i = 0;

				//append the proportion in the end
				nodeID = atoi(num);
				strPath.append(vecProp.at(nodeID));
				strPath.append(S_PATH_DOWN);
			}

		    break;
		default:
			num[i] = strEncodePath.at(index);
			i++;
		    break;
		}
		index++;
	}

	//append the last
	num[i] = C_END_CHAR;
	nodeID = atoi(num);
	strPath.append(vecProp.at(nodeID));

	// delete shared parent node' relation
	size_t find_up = strPath.find_last_of(">");
	size_t find_down = strPath.find_first_of("<");
	if ( string::npos != find_up && string::npos != find_down && find_up < find_down)
	{
		strPath = strPath.substr(0,find_up+1) + strPath.substr(find_down);
	}
	else if (string::npos != find_up)
	{
		strPath = strPath.substr(0,find_up+1);
	}
}
