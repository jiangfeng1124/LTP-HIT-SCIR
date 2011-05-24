/**************************************************************
	�� �� �� : Dictionary.cpp
	�ļ����� : CDictionary���ʵ���ļ�
	��    �� : Truman
	����ʱ�� : 2003��10��27��
	��Ŀ���� : NBestHMM
	���뻷�� : Visual C++ 6.0
	��    ע : 
	��ʷ��¼ :  
**************************************************************/
//#include "StdAfx.h"
#include <stdlib.h>
#include "Dictionary.h"

namespace HMM_Dic
{

CDictionary::CDictionary()
{
	totalWordNum = 0;
}

CDictionary::~CDictionary()
{
	DestoryData();
}

///////////////////////////////////////////////////////////////
//	�� �� �� : Initialize
//	�������� : CDictionary
//	�������� : ������г�ʼ����������ȡ�����ļ�
//	��    ע : 
//	��    �� : Truman
//	ʱ    �� : 2003��10��28��
//	�� �� ֵ : bool
//	����˵�� : const string &startFile,
//				         const string &transFile,
//				         const string &emitFile
///////////////////////////////////////////////////////////////
bool CDictionary::Initialize(const string &startFile,
							const string &transFile,
							const string &emitFile)
{
	if(!ReadStartFile(startFile))
		return false;
	if(!ReadTransFile(transFile))
		return false;
	if(!ReadEmitFile(emitFile))
		return false;
	return true;
}

///////////////////////////////////////////////////////////////
//	�� �� �� : ReadEmitFile
//	�������� : CDictionary
//	�������� : ��ȡ��������ļ�
//	��    ע : �����ȡʧ��,�򷵻�false
//	��    �� : Truman
//	ʱ    �� : 2003��10��28��
//	�� �� ֵ : bool
//	����˵�� : const string &emitFileName
///////////////////////////////////////////////////////////////
bool CDictionary::ReadEmitFile(const string &fileName)
{
	long fileSize = GetFileLength(fileName);
	if(fileSize == -1)
		return false;
	char *buf = new char[fileSize];
	FILE *fp;
	fp = fopen(fileName.c_str(), "rb");
	if(fp == NULL)
		return false;
	fread(buf, fileSize, 1, fp);

	int wordIndex = 0;	//�ʵ�����
	int posIndex = 0;
	int prev = 0, pos = 0;
	char tempBuf[20];	//�����ʱ�ַ������������ַ�����
	tempBuf[0] = '\0';
	int tempIndex = 0;	//��ʱ�ַ�����������ָ�����һ���ַ�
	int posNum;
	int status = 0;		//״̬����ǰ�������ʲôֵ��
				//status = 0,	������ǹ۲�ֵ����
				//status = 1,	�������״̬����
				//status = 2,	�������״̬��
				//status = 3,	������Ƿ������
	for(long i = 0; i < fileSize; i++)
	{
		if(buf[i] == 10)	//�س�����
		{
			if(tempIndex == 0)		//����
			{
				continue;
			}
			tempBuf[tempIndex] = '\0';
			tempIndex = 0;
			switch(status)
			{
			case 0:
				this->totalWordNum = atoi(tempBuf);
				this->wordArray = new DicWord[totalWordNum];
				status = 1;
				break;
			case 3:
				wordArray[wordIndex].stateArray[posIndex].emitProb = atof(tempBuf);
				posIndex = 0;
				status = 1;
				wordIndex++;
				if(wordIndex >= this->totalWordNum)
					return true;
				break;
			}
			continue;
		}
		if(buf[i] == 32)		//�ո�
		{
			if(tempIndex == 0)		//����
				continue;
			tempBuf[tempIndex] = '\0';
			tempIndex = 0;
			switch(status) {
			case 1:
				posNum = atoi(tempBuf);
				wordArray[wordIndex].stateNum = posNum;
				wordArray[wordIndex].stateArray = new DicState[posNum];
				status = 2;
				break;
			case 2:
				wordArray[wordIndex].stateArray[posIndex].stateIndex = atoi(tempBuf);
				status = 3;
				break;
			case 3:
				wordArray[wordIndex].stateArray[posIndex].emitProb = atof(tempBuf);
				posIndex++;
				status = 2;
				break;
			default:
				break;
			}
			continue;
		}
		
		tempBuf[tempIndex] = buf[i];
		tempIndex++;
	}
	delete [] buf;
	return true;
}

///////////////////////////////////////////////////////////////
//	�� �� �� : ReadStartFile
//	�������� : CDictionary
//	�������� : ��ȡ��ʼ�����ļ�
//	��    ע : ��ȡ�ļ�ʧ�ܷ���false
//	��    �� : Truman
//	ʱ    �� : 2003��10��28��
//	�� �� ֵ : bool
//	����˵�� : const string &startFileName
///////////////////////////////////////////////////////////////
bool CDictionary::ReadStartFile(const string &startFileName)
{
	ifstream startFile;
	startFile.open(startFileName.c_str());
	if(!startFile)		//Read file error!
		return false;
	int n;
	startFile >> n;
	totalStateNum = n;
	for(int i=0;i<n;i++)
	{
		startFile >> startProb[i];
	}
	startFile.close();
	return true;
}

///////////////////////////////////////////////////////////////
//	�� �� �� : ReadTransFile
//	�������� : CDictionary
//	�������� : ��ȡת�Ƹ����ļ�
//	��    ע : ��ȡ�ļ�ʧ�ܷ���false
//	��    �� : Truman
//	ʱ    �� : 2003��10��28��
//	�� �� ֵ : bool
//	����˵�� : const string &transFileName
///////////////////////////////////////////////////////////////
bool CDictionary::ReadTransFile(const string &transFileName)
{
	ifstream transFile;
	transFile.open(transFileName.c_str());
	if(!transFile)		//Read file error!
		return false;
	for(int i=0;i<totalStateNum;i++)
		for(int j=0;j<totalStateNum;j++)
			transFile >> transProb[i][j] ;
	
	transFile.close();
	return true;
}


///////////////////////////////////////////////////////////////
//	�� �� �� : DestoryData
//	�������� : CDictionary
//	�������� : ����CDictionary���е����ݣ��Ա��ȡ�µ�����
//	��    ע : 
//	��    �� : Truman
//	ʱ    �� : 2003��10��28��
//	�� �� ֵ : void
//	����˵�� : 
///////////////////////////////////////////////////////////////
void CDictionary::DestoryData()
{
	if(totalWordNum != 0)
	{
		for(int i=0;i<totalWordNum;++i)
			delete [] wordArray[i].stateArray;
		delete [] wordArray;
		totalWordNum = 0;
	}
}

///////////////////////////////////////////////////////////////
//	�� �� �� : GetFileLength
//	�������� : CDictionary
//	�������� : ���ļ��ĳ���
//	��    ע : 
//	��    �� : Truman
//	ʱ    �� : 2003��11��8��
//	�� �� ֵ : long	�ļ�����(�ֽ���),�����ȡ�����򷵻�-1
//	����˵�� : const string &fileName	�ļ���
///////////////////////////////////////////////////////////////
long CDictionary::GetFileLength(const string &fileName)
{
	if (fileName.empty()) 
	   return -1; 
	FILE *fp = fopen(fileName.c_str(), "rb"); 
	if (fp == NULL) 
	   return -1; 
	fseek(fp, 0 , SEEK_END); 
	long lResult = ftell(fp); 
	fclose(fp); 
	return lResult; 
}

}


