#include "ConsPdRelFeaturesExt.h"

//////////////////////////////////////////////////////////////////////////
// constructor and destructor
//////////////////////////////////////////////////////////////////////////
ConsPdRelFeaturesExt::ConsPdRelFeaturesExt(const DataPreProcess *dataPreProc, 
										   int nodeID, 
										   int pdNodeID)
										   : ConsPdRelFeatures(dataPreProc, nodeID, pdNodeID), Features(dataPreProc)
{

}

ConsPdRelFeaturesExt::~ConsPdRelFeaturesExt()
{

}


//////////////////////////////////////////////////////////////////////////
// features extract method
//////////////////////////////////////////////////////////////////////////
void ConsPdRelFeaturesExt::ExtractDistance(string& strDis) const
{
	int dis;
	ostrstream ostrDis;

	dis = (m_nodeID - m_pdNodeID)/5;
	ostrDis << dis << C_END_CHAR;
	strDis = "distance_" + string( ostrDis.str() );
}

//////////////////////////////////////////////////////////////////////////
void ConsPdRelFeaturesExt::ExtractDisRelativeLen(string& strDisRLen) const
{
	int disRL;
	ostrstream ostrDisRL;
	DepNode depCurNode;

	m_dataPreProc->m_myTree->GetNodeValue(depCurNode, m_nodeID);
	disRL = (m_nodeID - m_pdNodeID) / (depCurNode.constituent.second - depCurNode.constituent.first + 1);
	ostrDisRL << disRL << C_END_CHAR;
	strDisRLen = "disrlen_" + string(ostrDisRL.str() );
}

//////////////////////////////////////////////////////////////////////////
void ConsPdRelFeaturesExt::ExtractSimpRelPathPattern(string& strSimpRelPath) const
{
	string strTemp;
	vector<int> vecPathSeq;
	vector<string> vecPath;
	vector<string> vecRel;
	vector<string> vecSimpRel;

	m_dataPreProc->m_myTree->GetAllNodePath(m_pdNodeID, vecPath);
	GetPathIDSequence(vecPathSeq, vecPath.at(m_nodeID));
	for (int index = 1; index < vecPathSeq.size() -1; index++)
	{
		vecRel.push_back(m_dataPreProc->m_ltpData->vecRelation.at(vecPathSeq.at(index)));
	}
	strSimpRelPath = S_NULL_STR;
	strSimpRelPath.append(m_dataPreProc->m_ltpData->vecRelation.at(vecPathSeq.at(0)));
	strSimpRelPath.append(1, C_NE_SEP);
	RemoveNeighboringSameItem(vecSimpRel, vecRel);
	JoinVecToStrByChar(strTemp, vecSimpRel, C_NE_SEP);
	strSimpRelPath.append(strTemp); //remove the predicate relation or pos

    strSimpRelPath = "simpRelPath_" + strSimpRelPath;
}

//////////////////////////////////////////////////////////////////////////
void ConsPdRelFeaturesExt::ExtractSimpPosPathPattern(string& strSimpPosPath) const
{
	string strTemp;
	vector<int> vecPathSeq;
	vector<string> vecPath;
	vector<string> vecPos;
	vector<string> vecSimpPos;

	m_dataPreProc->m_myTree->GetAllNodePath(m_pdNodeID, vecPath);
	GetPathIDSequence(vecPathSeq, vecPath.at(m_nodeID));
	for (int index = 1; index < vecPathSeq.size() -1; index++)
	{
		vecPos.push_back(m_dataPreProc->m_ltpData->vecPos.at(vecPathSeq.at(index)));
	}

	strSimpPosPath = S_NULL_STR;
	strSimpPosPath.append(m_dataPreProc->m_ltpData->vecPos.at(vecPathSeq.at(0)));
	strSimpPosPath.append(1, C_NE_SEP);
	RemoveNeighboringSameItem(vecSimpPos, vecPos);
	JoinVecToStrByChar(strTemp, vecSimpPos, C_NE_SEP);
	strSimpPosPath.append(strTemp);

    strSimpPosPath = "simpPosPath_" + strSimpPosPath;
}

//////////////////////////////////////////////////////////////////////////
/*void ConsPdRelFeaturesExt::ExtractPath(string& strPath) const
{
	vector<string> vecPath;
	m_dataPreProc->m_myTree->GetAllNodePath(m_pdNodeID, vecPath);

	strPath = S_NULL_STR;
	ParsePathEncodeString(strPath, vecPath.at(m_nodeID), m_dataPreProc->m_ltpData->vecRelation);
}

//////////////////////////////////////////////////////////////////////////
void ConsPdRelFeaturesExt::ExtractPartPath(string& strPPath) const
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
}
*/

//////////////////////////////////////////////////////////////////////////
void ConsPdRelFeaturesExt::GetPathIDSequence(vector<int>& vecPathSeq, 
											 const string& strPath) const
{
	char num[I_WORD_LEN];
	int nodeID;
	int strLength = strPath.length();	
	int index = 0;
	int i = 0;

	vecPathSeq.clear();
	while (index < strLength)
	{
		switch(strPath.at(index))
		{
		case C_UP:
			{
				num[i] = C_END_CHAR;
				i = 0;

				//append the proportion in the end
				nodeID = atoi(num);
				vecPathSeq.push_back(nodeID);
			}

			break;
		case C_DOWN:
			{
				num[i] = C_END_CHAR;
				i = 0;

				//append the proportion in the end
				nodeID = atoi(num);
				vecPathSeq.push_back(nodeID);
			}

			break;
		default:
			num[i] = strPath.at(index);
			i++;
			break;
		}
		index++;
	}

	//append the last
	num[i] = C_END_CHAR;
	nodeID = atoi(num);
	vecPathSeq.push_back(nodeID);
}

//////////////////////////////////////////////////////////////////////////
/*void ConsPdRelFeaturesExt::ParsePathEncodeString(string& strPath, const string& strEncodePath, const vector<string>& vecProp) const
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
}
*/