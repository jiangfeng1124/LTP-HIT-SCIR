#include "SRLDictionary.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////
//	Function Name 	: SRLDictionary
//	Belong to Class : SRLDictionar
//	Function  	: 
//	Processing 	: Constructor
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: 
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
SRLDictionary::SRLDictionary()
{

}

///////////////////////////////////////////////////////////////
//	Function Name 	: ~SRLDictionary
//	Belong to Class : SRLDictionar
//	Function  	: 
//	Processing 	: Destructor
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: 
//	Parameter Comment : 
///////////////////////////////////////////////////////////////
SRLDictionary::~SRLDictionary()
{

}

//-------------------- public interface -----------------------------------//
///////////////////////////////////////////////////////////////
//	Function Name 	: LoadPdClassDic
//	Belong to Class : SRLDictionary
//	Function  	: 
//	Processing 	: load the predicate class encode file
//	Remark 		: 
//	Author 		: Frumes
//	Time 		: 2006年12月31日
//	Return Value 	: bool
//	Parameter Comment : const char *fileName
///////////////////////////////////////////////////////////////
bool SRLDictionary::LoadPdClassDic(const char *fileName)
{
	FILE *fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		cerr << "can't open " << fileName << endl;
		return 0;
	}

	long fileLen;
	fseek(fp, 0, SEEK_END);
	fileLen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *buf = new char[fileLen];
	if (!buf)
	{
		cerr << "new memory error" << endl;
		return 0;
	}
	fread(buf, fileLen, 1, fp);
	fclose(fp);

	//for debug
	int lineID = 0;

	int index = 0;
	int i = 0;
	int flag = 0;
	char word[I_WORD_LEN];
	char code[I_WORD_LEN];
	while (index < fileLen)
	{
		switch(buf[index])
		{
		case 0X09:
			word[i] = C_END_CHAR;
			i = 0;
			flag = 1;

			break;
		case 0X0D:
			code[i] = C_END_CHAR;
			i = 0;
			flag = 0;

		    break;
		case 0X0A:
			m_mapPd2Code.insert(valType(word, code));

			//for debug
			//lineID++;

			break;
		default:
			if (!flag)
			{
				word[i] = buf[index];				
			}
			else
			{
				code[i] = buf[index];
			}

			i++;
		    break;
		}
		index++;
	}

	delete []buf;

	return 1;
}
