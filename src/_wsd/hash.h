//Copyright (c) 2005,HIT-IRLab. All Rights Reserved.

// #define STL_USING_ALL
// #include "stl.h"

#ifndef _HASH_FIND_
#define  _HASH_FIND_
#define FAIL -1

#include <vector>

using namespace std;

typedef int BOOL;
typedef unsigned int UINT;

struct wordPsk//�����������Ϣ
{
public:
	char IDs[5];
	float  Psk;
	float  P_LAM;
	int   begin;
	int   end;
};

struct ITEM			// hash�����Ŀ
{
	char* key;		// �ؼ���
	int property;	// �ؼ��ֵ�ID
	vector<wordPsk> psk;
	ITEM* pNext;
};


///////////////////////////////////////////////////////////////
//	��    �� : CHash
//	��    �� : 
//	��    �� : 
//	��    �� : 
//	��ʷ��¼ : 
//	ʹ��˵�� : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��24��
//	��    ע : Ϊ����������ٶȣ�������hash��Ľṹ
///////////////////////////////////////////////////////////////
class CHash  
{

public:
	CHash();
	virtual ~CHash();
	void InitHashTable(int nTableSize);			//��ʼ��hash������Ϊ���ִ��ڻ���ڲ���Ĺؼ��ָ���
	void SetAt(const char* key, int property,vector<wordPsk> psk);	//���ؼ��ֲ���hash����
	int GetPosition(const char* key, UINT& nHash);	//��ȡ�ؼ�����hash���е�λ��
	ITEM* Lookup(UINT& nHash);//����hash����nHash����λ�õ�ָ��
	void RemoveAll();							//�ͷ��ڴ�
	


private:
	inline int HashKey(const char* key) const;		//����ؼ��ֵļ�ֵ
	
	int NextPrime(int N);							//��ȡ����N�ĵ�һ������
	int IsPrime(int N);								//�ж�һ�����Ƿ�Ϊ����

	UINT m_nHashTableSize;
	ITEM** m_pHashTable;
};

#endif

