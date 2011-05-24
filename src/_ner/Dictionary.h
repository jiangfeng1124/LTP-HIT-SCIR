/**************************************************************
	�� �� �� : Dictionary.h
	�ļ����� : CDictionary��������ļ�
	��    �� : Truman
	����ʱ�� : 2003��10��27��
	��Ŀ���� : NBestHMM
	���뻷�� : Visual C++ 6.0
	��    ע : 
	��ʷ��¼ :  
**************************************************************/

#ifndef IR_CDICTIONARY_H
#define IR_CDICTIONARY_H

// #define STL_USING_ALL
// #include <STL.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

const int MAX_STATE_NUM = 120;	//HMM��״̬�������ֵ

using namespace std;

namespace HMM_Dic
{

///////////////////////////////////////////////////////////////
//	�ṹ���� : DicState
//	��    �� : ����һ��״̬������Ӧ�ķ���Ƶ��
//	��ʷ��¼ : 
//	ʹ��˵�� : 
//	��    �� : Truman
//	ʱ    �� : 2003��10��27��
//	��    ע : 
///////////////////////////////////////////////////////////////
struct DicState
{
	int stateIndex;			//״̬���
	double emitProb;		//��stateIndex״̬�µķ���Ƶ��
};

///////////////////////////////////////////////////////////////
//	�ṹ���� : DicWord
//	��    �� : ����۲�ֵ��źʹ˹۲�ֵ��Ӧ��״̬������״̬����
//	��ʷ��¼ : 
//	ʹ��˵�� : 
//	��    �� : Truman
//	ʱ    �� : 2003��10��27��
//	��    ע : stateArrayָ�����һ��new���������飬��CDictionary��
//				���������н���delete
///////////////////////////////////////////////////////////////
struct DicWord
{
	int wordIndex;		//�۲�ֵ���
	int stateNum;		//�˹۲�ֵ�ڵ��״̬����
	DicState *stateArray;	//״̬�ڵ������ͷָ��
};

class CDictionary  
{
public:
	long GetFileLength(const string &fileName);
	CDictionary();
	virtual ~CDictionary();
	bool Initialize(const string &startFile,
					const string &transFile,
					const string &emitFile);	//�������ļ�������г�ʼ��
	DicState *GetEmitProb(int wordIndex, int &returnStateNum) {
		returnStateNum = wordArray[wordIndex].stateNum;
		return wordArray[wordIndex].stateArray;
	};	
		//����wordIndex�ʵ�״̬������׵�ַ��״̬��������returnStateNum�з���
	double GetTransProb(int stateIndex1, int stateIndex2) {
		return transProb[stateIndex1][stateIndex2];
	};
		//ȡstateIndex1״̬��stateIndex2��ת��Ƶ��
	double GetStartProb(int stateIndex) {
		return startProb[stateIndex];
	};
		//ȡstateIndex�ĳ�ʼƵ��
	void DestoryData(void);
	int totalWordNum;	//�ֵ���۲�ֵ��������
private:
	DicWord *wordArray;		//�۲�ֵ�����ͷָ��
	int totalStateNum;	//��HMMģ���е�״̬����
	double transProb[MAX_STATE_NUM][MAX_STATE_NUM];
						//ת�Ƹ��ʾ���
	double startProb[MAX_STATE_NUM];
						//��ʼ��������
	bool ReadEmitFile(const string &emitFileName);
	bool ReadTransFile(const string &transFileName);
	bool ReadStartFile(const string &startFileName);
};
}

#endif
