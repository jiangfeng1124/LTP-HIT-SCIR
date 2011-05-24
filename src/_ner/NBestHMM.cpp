/**************************************************************
	�� �� �� : NBestHMM.cpp
	�ļ����� : ������ģ�����к�����ʵ��
	��    �� : Truman
	����ʱ�� : 2003��10��25��
	��Ŀ���� : ������ɷ�ģ��N������·������ͨ���㷨ģ��
	���뻷�� : Visual C++ 6.0
	��    ע : 
	��ʷ��¼ :  
**************************************************************/
//#include "StdAfx.h"
#include "NBestHMM.h"

PathNode::PathNode()
{
	accuProb = 0;	//·���ۼ�Ȩֵ��0
	preStateIndex = -1;	//-1��ʾǰһ���ڵ��״̬Ϊ��
	preNode = NULL;	
	next = NULL;
	prev = NULL;
	curStateIndex = -1;
}

PathNode::~PathNode()
{
}

CNBestHMM::CNBestHMM()
{
// 	headPath = NULL;
}

CNBestHMM::~CNBestHMM()
{
//	PathNode *p = headPath;
//	while(p != NULL)
//	{
//		PathNode *p1 = p;
//		p = p->next;
//		delete p1;
//	}
//	headPath = NULL;
}

///////////////////////////////////////////////////////////////
//	�� �� �� : Initialize
//	�������� : CNBestHMM
//	�������� : ��CNBestHMM����г�ʼ���������ʼ��ʧ���򷵻�false
//	��    ע : 
//	��    �� : Truman
//	ʱ    �� : 2003��10��26��
//	�� �� ֵ : bool
//	����˵�� : const string &startFile,
//				          const string &transFile,
//				          const string &emitFile
///////////////////////////////////////////////////////////////
int CNBestHMM::Initialize(const string &startFile, 
					  const string &transFile, 
					  const string &emitFile)
{

	if(!dic.Initialize(startFile, transFile, emitFile))
		return 0;
	return 1;
}

///////////////////////////////////////////////////////////////
//	�� �� �� : NBestSearch
//	�������� : CNBestHMM
//	�������� : N Best Search�㷨
//	��    ע : 
//	��    �� : Truman
//	ʱ    �� : 2003��10��28��
//	�� �� ֵ : void
//	����˵�� : int word[],�۲�ֵ����
//				 int wordNum,�۲�ֵ����
///////////////////////////////////////////////////////////////
void CNBestHMM::NBestSearch(int word[], int wordNum)
{
	/*** add by Zhu Huijia 2006-10-30 ***/
	pathNum = 0; 
	if (wordNum <= 0)
	{
		return;
	}
	/************************************/

	int wordNo = 0, stateNum = 0;		//�۲�ֵ�ڵ��������
	int i = 0;
	HMM_Dic::DicState *statePtr = dic.GetEmitProb(word[wordNo], stateNum);
	PathNode *headPathNode, *curNode, *lastNode;		//·���ڵ������ͷ�ڵ�ָ��
	for(i=0;i<stateNum;i++)
	{
		curNode = new PathNode;
		int pos = statePtr[i].stateIndex;
		curNode->curStateIndex = pos;
		curNode->accuProb = statePtr[i].emitProb + dic.GetStartProb(pos);
		if(i == 0)
		{
			lastNode = headPathNode = curNode;
		}
		else
		{
			lastNode->next = curNode;
			lastNode = lastNode->next;
		}
	}
// 	this->headPath = headPathNode;
	PathNode *preFirst = headPathNode, *preLast = curNode , *prePtr;
			//�ֱ����ǰһ���۲�ֵ��·���ڵ������ͷָ�룬βָ�룬����ָ��
	PathNode *curFirst = headPathNode, *curLast = headPathNode;
			//��ǰ�۲�ֵ�ڵ��·�������ͷָ��,βָ��
	for(i = 1; i < wordNum; i++)	//�۲�ֵѭ��
	{
		int curPathNum = 0;
		PathNode *newHead = NULL, *newEnd = NULL;//, *newPtr = NULL;
			//�ֱ����ǰ״̬��N��·���ڵ��ͷָ�룬βָ�룬�����½ڵ��ָ�룬����ָ��
			//��ǰ״̬�ڵ��µ�·������
		statePtr = dic.GetEmitProb(word[i], stateNum);
		for(int j = 0; j < stateNum; j++)	//״̬ѭ��
		{
			for(prePtr = preFirst; prePtr != NULL; prePtr = prePtr->next) 
				//ǰһ���۲�ֵ�ڵ������·���ڵ��ѭ��
			{
				double tempProb = prePtr->accuProb + statePtr[j].emitProb
							+ dic.GetTransProb(prePtr->curStateIndex, 
									statePtr[j].stateIndex);
				NewPath paths = InsertPathToTop(prePtr, newHead, newEnd, tempProb, 
								statePtr[j].stateIndex, curPathNum);
				if(paths.first != NULL)
				{
					newHead = paths.first;
					newEnd = paths.second;
				}
			}
			
			if(j == 0)
			{
				curFirst = newHead;
			}
			else
			{
				curLast->next = newHead;
				newHead->prev = curLast;
			}
			curLast = newEnd;					
			newEnd = NULL;
			newHead = NULL;
			curPathNum = 0;
		}
		preLast->next = curFirst;
		curFirst->prev = preLast;
		preFirst = curFirst;
		preLast = curLast;
	}
	SearchBack(curFirst, curLast, wordNum);
	FreeMem(headPathNode);
}

///////////////////////////////////////////////////////////////
//	�� �� �� : InsertPathToTop
//	�������� : CNBestHMM
//	�������� : ���Ȩֵweight�ܷ���뵱ǰ�����ŵ�Top N�У�����ܣ�
//				����ڵ㣬���򷵻�(NULL, NULL)
//	��    ע : inline����
//	��    �� : Truman
//	ʱ    �� : 2003��11��4��
//	�� �� ֵ : NewPath (pair<PathNode*, PathNode*>) �µ�Top N���׵�ַ��β��ַ
//	����˵�� : PathNode *prePtr,	�˽ڵ�������·��֮�е�ǰһ���ڵ�ָ��
//             PathNode& *newFirst, TopN�����׵�ַ
//             PathNode& *newLast,	TopN����β��ַ
//             double weight,		�˽ڵ��Ȩ��
// 			   int state,			�˽ڵ�Ĵ���
//             int &curPathNum		TopN�еĽڵ��������˴�Ϊ���ã�
///////////////////////////////////////////////////////////////
NewPath CNBestHMM::InsertPathToTop(PathNode *prePtr, 
								   PathNode *newFirst,
								   PathNode *newLast,
								   double weight,
								   int state,
								   int &curPathNum)
{
	NewPath returnPath(NULL, NULL);
	
	if(newLast != NULL && curPathNum >= MAX_N && newLast->accuProb < weight)
		return returnPath;
	//�����µ�·���ڵ�
	PathNode *newPtr = new PathNode;
	newPtr->accuProb = weight;
	newPtr->curStateIndex = state;
	newPtr->preStateIndex = prePtr->curStateIndex;
	newPtr->preNode = prePtr;
	if(curPathNum == 0)
	{
		newFirst = newPtr;
		newLast = newPtr;
		curPathNum = 1;
	}
	else
	{
		//Ѱ�Һ��ʵ�λ�ò���
		PathNode *curPtr;
		for(curPtr = newFirst;curPtr != newLast->next; curPtr = curPtr->next)
		{
			if(newPtr->accuProb < curPtr->accuProb)
			{
				if(curPtr == newFirst)	//����ͷ�ڵ����
				{
					newFirst = newPtr;
				}
				else
				{
					curPtr->prev->next = newPtr;
					newPtr->prev = curPtr->prev;
				}
				newPtr->next = curPtr;
				curPtr->prev = newPtr;
				break;
			}
		}
		if(curPtr == newLast->next)
		{
			newLast->next = newPtr;
			newPtr->prev = newLast;
			newLast = newPtr;
		}
		if(curPathNum >= MAX_N)	//·�����Ƿ��ѴﵽԤ������
			newLast = newLast->prev;
		else
			curPathNum++;							
	}
	PathNode *p = newLast->next;
	while(p != NULL)		//�ͷŵ�û����ѡǰN��·���ڵ�
	{
		PathNode *p1 = p;
		p = p->next;
		delete p1;
	}
	newLast->next = NULL;
	returnPath.first = newFirst;
	returnPath.second = newLast;
	return returnPath;
}

void CNBestHMM::SearchBack(PathNode *pathStart, PathNode *pathEnd, int wordNum)
{
	this->pathNum = 0;		//·��������0
	PathNode *ptr, *newStart = NULL, *newEnd = NULL;
	NewPath paths;
	int curPathNum = 0;

	for(ptr = pathStart; ptr != NULL; ptr = ptr->next)
	{
		double temp = ptr->accuProb;
		int state = ptr->curStateIndex;
		paths = InsertPathToTop(ptr, newStart, newEnd, temp, -1, curPathNum);
		if(paths.first != NULL)
		{
			newStart = paths.first;
			newEnd = paths.second;
		}
	}

	//��ʼ���λ���
	for(ptr = newStart; ptr != NULL; ptr = ptr->next)
	{
		PathNode *p = ptr->preNode;
		int n = wordNum;
		while(p != NULL)
		{
			this->resultPath[pathNum][--n] = p->curStateIndex;
			p = p->preNode;
		}
		this->pathWeight[pathNum] = ptr->accuProb;
		this->pathNum++;
	}
	
	/*** add by Zhu Huijia 2006-10-30 ***/
	FreeMem(newStart);
	/************************************/
}

void CNBestHMM::FreeMem(PathNode *head)
{
	PathNode *p = head;
	while(p != NULL)
	{
		PathNode *p1 = p;
		p = p->next;
		delete p1;
	}
}
