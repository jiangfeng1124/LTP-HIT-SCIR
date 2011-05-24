//Copyright (c) 2005,HIT-IRLab. All Rights Reserved.

#define STL_USING_ALL
#include "stl.h"

#ifndef _HASH_FIND_
#define  _HASH_FIND_
#define FAIL -1

///////////////////////////////////////////////////////////////
//	��    �� : CHash
//	��    �� : ��
//	��    �� : ����ΪӢ��ƴд���д�Ĵʱ���Һ�����Version6.02���޸ģ�
//				��Ϊ���ҹؼ������ԣ����ʣ���Hash����
//	��    �� : ����Ŀ����Hash���У�Ȼ����Բ��ҹؼ����Ƿ���ڣ�
//				Ȼ�󷵻ض�Ӧ�����ݣ������������ͻ
//	ʹ��˵�� : �ȳ�ʼ����Ȼ����Ŀ���η�����У�Ȼ����Բ�ѯ
//	��    �� : ���ɽ
//	ʱ    �� : 2006��6��17���޸�
//	��    ע :��1��ɾ�����ҵȳ��ʵĹ���
//			  ��2����Ϊ�����ؼ�����ͬ�Ĵ���
///////////////////////////////////////////////////////////////
typedef int BOOL;
typedef unsigned int UINT;

struct ITEM			// hash�����Ŀ
{
	char* key;		// �ؼ���
	char* relation;	// ��ϵ����
	float prob;		// �ؼ��ֵ�����
    ITEM* pNext;
};

class CHash  
{
public:
	CHash();
	virtual ~CHash();
	void InitHashTable(int nTableSize);			//��ʼ��hash������Ϊ���ִ��ڻ���ڲ���Ĺؼ��ָ���
	void SetAt(const char* key, const char* relation, float prob);	//���ؼ��ֲ���hash����
	ITEM* Lookup(const char* key);//���ҹؼ����Ƿ���ڣ����ڷ���ture�����򷵻�false
	BOOL Remove(const char* key);				//ɾ�����еĹؼ��֣���������ڣ�ɾ��������1���粻���ڣ�����0
	void RemoveAll();							//�ͷ��ڴ�


private:
	inline int HashKey(const char* key) const;		//����ؼ��ֵļ�ֵ
	ITEM* GetPosition(const char* key);				//��ȡ�ؼ�����hash���е�λ��
	int NextPrime(int N);							//��ȡ����N�ĵ�һ������
	int IsPrime(int N);								//�ж�һ�����Ƿ�Ϊ����

	UINT m_nHashTableSize;
	ITEM** m_pHashTable;
};

#endif

