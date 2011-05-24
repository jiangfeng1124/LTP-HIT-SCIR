/**************************************************************
	�� �� �� : NBestHMM.h
	�ļ����� : ������ģ���������ݽṹ�������ͳ�������
	��    �� : Truman
	����ʱ�� : 2003��10��25��
	��Ŀ���� : ������ɷ�ģ��N������·������ͨ���㷨ģ��
	���뻷�� : Visual C++ 6.0
	��    ע : 
	��ʷ��¼ :  
**************************************************************/
#ifndef IR_NBESTHMM_H
#define IR_NBESTHMM_H

// #define STL_USING_ALL
//#include <STL.h>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include "Dictionary.h"
// #include "MemPool.h"

const int MAX_N = 1;		//N Best Search��N�����ֵ
const int MAX_WORDS = 2000;	//һ�������Ĺ۲�ֵ���������
using namespace std;

///////////////////////////////////////////////////////////////
//	�ṹ���� : PathNode
//	��    �� : 
//	��ʷ��¼ : 
//	ʹ��˵�� : 
//	��    �� : Truman
//	ʱ    �� : 2003��10��25��
//	��    ע : 
///////////////////////////////////////////////////////////////
struct PathNode
{
	PathNode();
	~PathNode();
	double accuProb;	//·�����˽ڵ���ۼ�Ȩֵ
	int preStateIndex;	//��ǰ·����ǰһ���ڵ��״ֵ̬
	int curStateIndex;	//��ǰ�ڵ��״ֵ̬
	PathNode *preNode;	//��ǰ·����ǰһ��·���ڵ�ĵ�ַ
	PathNode *next;		//ָ��·���ڵ����һ���ڵ�
	PathNode *prev;		//·���ڵ��������е�ǰһ���ڵ�
};

typedef pair<PathNode *, PathNode *> NewPath;
///////////////////////////////////////////////////////////////
//	��    �� : CNBestHMM
//	��    �� : 
//	��    �� : ��װHMM N Best Search�㷨����
//	��ʷ��¼ : 
//	ʹ��˵�� : 
//	��    �� : Truman
//	ʱ    �� : 2003��10��25��
//	��    ע : 
///////////////////////////////////////////////////////////////
class CNBestHMM
{
public:
	CNBestHMM(); //"DATA\\start.dat", "DATA\\trans.dat", "DATA\\emit.dat"
	virtual ~CNBestHMM();
	int Initialize(const string &startFile,
					const string &transFile,
					const string &emitFile);	//�������ļ�������г�ʼ��
	void NBestSearch(int word[], int wordNum);
		//word[]�д�Ź۲�ֵ���У�wordNumΪ�۲�ֵ�����й۲�ֵ������
// 	int GetResult(int **path, double weight[]);
	unsigned int GetWordsNum(void) { return dic.totalWordNum;};    

public:
	int resultPath[MAX_N][MAX_WORDS];
	double pathWeight[MAX_N];
	int pathNum;

private:
	void FreeMem(PathNode *head);
//	PathNode *headPath;	//·������ͷָ��
	void SearchBack(PathNode *pathStart, PathNode *pathEnd, int wordNum);
	HMM_Dic::CDictionary dic;
	inline NewPath InsertPathToTop(PathNode *prePtr,			
							PathNode *newFirst,
							PathNode *newLast,
							double weight,
							int state,
							int &curPathNum);
};

#endif

