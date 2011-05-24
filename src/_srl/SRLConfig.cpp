#include <vector>
#include <string.h>
#include "SRLConfig.h"

///////////////////////////////////////////////////////////////
//	Function Name 	: SRLConfig
//	Belong to Class : SRLConfig
//	Function  	: 
//	Processing 	: Constructor
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: 
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
SRLConfig::SRLConfig()
{

}

///////////////////////////////////////////////////////////////
//	Function Name 	: ~SRLConfig
//	Belong to Class : SRLConfi
//	Function  	: 
//	Processing 	: Destructor
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: 
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
SRLConfig::~SRLConfig()
{

}

//-----------------------------------------------------------------------//
///////////////////////////////////////////////////////////////
//	Function Name 	: LoadFeatConf
//	Belong to Class : SRLConfig
//	Function  	: 
//	Processing 	: load the features configuration information, and bind the info
//				  to the function pointer
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: void
//	Parameter Comment : const char* fileName,
//				           const FEATFUNCPRO funcFeatProcess(
///////////////////////////////////////////////////////////////
bool SRLConfig::LoadFeatSelConf(const char* fileName)
							 
{
	vector<string> vecLine;
	vector<string>::iterator itLine;
	int featTypeFlag;
	char word[I_WORD_LEN];

	// read the file
	ReadFileToVector(fileName, vecLine);

	//process the comment and featrues type


	featTypeFlag = 0;
	itLine = vecLine.begin();
	while (itLine != vecLine.end())
	{
		strcpy(word, (*itLine).c_str());
		if (word[0] == C_COMMENT_CHAR)
		{	//the common begin with '#'
			itLine++;	
			continue;
		}
		else if (word[0] == C_FEATTYPE_COMMENT)
		{	//the common begin with '$'
			featTypeFlag++;
		}
		else
		{			
			if (featTypeFlag == 1)
			{	//comment: #depNode feat
				m_vecConsFeatSelConf.push_back(word);
			}
			else if (featTypeFlag == 2)
			{	//comment: #Pd feat
				m_vecPdFeatSelConf.push_back(word);
			}
			else if (featTypeFlag == 3)
			{	//comment: #Relation feat
				m_vecConsPdRelFeatSelConf.push_back(word);
			}
		}

		itLine++;		
	}

	return 1;
}

//////////////////////////////////////////////////////////////////////////
bool SRLConfig::LoadFeatCombConf(const char* fileName)
{
	vector<string> vecLine;
	vector<string>::iterator itLine;
	char word[I_WORD_LEN];

	// read the file
	ReadFileToVector(fileName, vecLine);

	//process the comment
	itLine = vecLine.begin();
	while (itLine != vecLine.end())
	{
		strcpy(word, (*itLine).c_str());
		if ( (word[0] == C_COMMENT_CHAR) ||
			 (word[0] == C_FEATTYPE_COMMENT) )
		{	////the common begin with '#'
			itLine++;
			continue;
		}
		else
		{
			m_vecFeatCombConf.push_back(word);
		}

		itLine++;
	}
	
	return 1;
}
