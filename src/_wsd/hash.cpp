#include "hash.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// implementation of the CHash class
//////////////////////////////////////////////////////////////////////


CHash::CHash()
{
	m_nHashTableSize = 17;  // default size
}


CHash::~CHash()
{
	// RemoveAll();
}

///////////////////////////////////////////////////////////////
//	�� �� �� : SetAt
//	�������� : CHash
//	�������� : ���ؼ��ֲ���Hash��
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��24��
//	�� �� ֵ : void
//	����˵�� : const char* key,����
//				 int property,������Ӧ��id��
//				 vector<wordPsk> psk���ʹ�����Ӧ�������Ĵʻ�Ĺ�����Ϣ
///////////////////////////////////////////////////////////////
void CHash::SetAt(const char* key, int property, vector<wordPsk> psk)
{
	UINT nHash;
	if (GetPosition(key, nHash) == FAIL)// the key is not in map
	{
		//�����½ڵ�
		ITEM* pItem = new ITEM;
		int nLen = strlen(key);
		pItem->key = new char[nLen+1];//��̬�����ڴ�
		pItem->key[nLen] = '\0';
		strcpy(pItem->key,key);
		pItem->property = property;
		pItem->psk= psk;
		pItem->pNext = NULL;
        

		//���õ��ʼ���hash����
		ITEM* pTemp = m_pHashTable[nHash];
		if(pTemp == NULL)	//the first position is vacant
			m_pHashTable[nHash] = pItem;// put into hash table
		else
		{
			while(pTemp->pNext != NULL)
				pTemp = pTemp->pNext; //�����������β���
			pTemp->pNext = pItem;
		}
		
	}
}

///////////////////////////////////////////////////////////////
//	�� �� �� : Lookup
//	�������� : CHash
//	�������� : �õ�hash�ṹ��nhashλ�õ�ָ��
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��22��
//	�� �� ֵ : ITEM*
//	����˵�� : UINT& nHash
///////////////////////////////////////////////////////////////
ITEM* CHash::Lookup(UINT& nHash)
{
	return m_pHashTable[nHash];
}


///////////////////////////////////////////////////////////////
//	�� �� �� : InitHashTable
//	�������� : CHash
//	�������� : ��hash����г�ʼ��
//	������� : 
//	��    ע : 
//	��    �� : mjs
//	ʱ    �� : 2005��10��23��
//	�� �� ֵ : 
//	����˵�� : �û�ָ����hash���ȣ�Ӧ�ô��ڵ��ڴʱ���
///////////////////////////////////////////////////////////////
void CHash::InitHashTable(int nHashSize)
{
	// ASSERT(nHashSize >= 0);
	
	if(nHashSize > 17)	// ����С��17��ȡĬ��ֵ17
		m_nHashTableSize = NextPrime(nHashSize);

	m_pHashTable = new ITEM*[m_nHashTableSize];
	memset(m_pHashTable, 0, sizeof(ITEM*)*m_nHashTableSize);
}

///////////////////////////////////////////////////////////////
//	�� �� �� : RemoveAll
//	�������� : CHash
//	�������� : ɾ��hash���ͷ�ȫ���ڴ�
//	������� : 
//	��    ע : 
//	��    �� : mjs
//	ʱ    �� : 2005��10��24��
//	�� �� ֵ : void
//	����˵�� : 
///////////////////////////////////////////////////////////////
void CHash::RemoveAll()
{
	if (m_pHashTable != NULL)
	{
		// destroy elements
		for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
		{
			ITEM* pItem;
			ITEM* pTemp;
			for (pItem = m_pHashTable[nHash]; pItem != NULL; )
			{
				pTemp = pItem;
				delete [] pItem->key;  // free up string data
				pItem = pItem->pNext;
				delete pTemp;
			}
		}

		// free hash table
		delete [] m_pHashTable;
		m_pHashTable = NULL;// free hash table
	}

}
///////////////////////////////////////////////////////////////
//	�� �� �� : GetPosition
//	�������� : CHash
//	�������� : ���ҹؼ�����hash���е�λ�ã���ͨ������nHash����
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��24��
//	�� �� ֵ : int, key�ڱ��У����عؼ��ֵ�����1�����򷵻�-1
//	����˵�� : const char* key,�ؼ��֣�UINT& nHash��key�ڱ��е�λ��
///////////////////////////////////////////////////////////////
int CHash::GetPosition(const char* key, UINT& nHash)
{
	// ASSERT(m_nHashTableSize > 0);  // make sure we don't underflow

	nHash = HashKey(key);

	ITEM* pItem = m_pHashTable[nHash];
	if(pItem == NULL)
		return FAIL;
	while(pItem != NULL && strcmp(pItem->key,key) != 0)
		pItem = pItem->pNext; //��ͻʱ�������������β���

	if(pItem == NULL)//not in map
		return FAIL;
	else
		return 1; //found
}

inline int CHash::HashKey(const char* key) const
{
	unsigned int nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;//���MFC�еķ���
	
	int nHashValue = nHash % m_nHashTableSize;
	return nHashValue;
}

int CHash::NextPrime(int N)
{
	if(N%2==0) 
		N++;
	for(;!IsPrime(N);N+=2);
	return N;
}


int CHash::IsPrime(int N)
{
	for(int i=3;i*i<=N;i+=2)
		if(N%i==0) 
			return 0;
	return 1;
}



