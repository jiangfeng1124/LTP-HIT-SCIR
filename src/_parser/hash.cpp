#include "Hash.h"

//////////////////////////////////////////////////////////////////////
// implementation of the CHash class
//////////////////////////////////////////////////////////////////////


CHash::CHash()
{
	m_nHashTableSize = 17;  // default size
}


CHash::~CHash()
{
	RemoveAll();
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
	ASSERT(nHashSize >= 0);

	if(nHashSize > 17)	// ����С��17��ȡĬ��ֵ17
		m_nHashTableSize = NextPrime(nHashSize);

	m_pHashTable = new ITEM*[m_nHashTableSize];
	memset(m_pHashTable, 0, sizeof(ITEM*)*m_nHashTableSize);
}

///////////////////////////////////////////////////////////////
//	�� �� �� : SetAt
//	�������� : CHash
//	�������� : ���ؼ��ֲ���Hash������ؼ����ظ�
//	������� : 
//	��    ע : 
//	��    �� : mjs
//	ʱ    �� : 2005��6��23��
//	�� �� ֵ : void
//	����˵�� : const char* key, ������еĹؼ���
//			   int property, �ؼ��ֵ�����
///////////////////////////////////////////////////////////////
void CHash::SetAt(const char* key, const char* relation, float prob)
{
	//�����½ڵ�
	ITEM* pItem = new ITEM;
	int nLen = strlen(key);
	pItem->key = new char[nLen+1];	// ��̬�����ڴ�
	pItem->key[nLen] = '\0';
	strcpy(pItem->key,key);

	nLen = strlen(relation);
	pItem->relation = new char[nLen+1];
	pItem->relation[nLen] = '\0';
	strcpy(pItem->relation,relation);

	pItem->prob = prob;
	pItem->pNext = NULL;

	//���õ��ʼ���hash����
	UINT nHash = HashKey(key);
	ITEM* pTemp = m_pHashTable[nHash];
	if(pTemp == NULL)				// the first position is vacant
		m_pHashTable[nHash] = pItem;// put into hash table
	else
	{
		while(pTemp->pNext != NULL)
			pTemp = pTemp->pNext;	// �����������β���
		pTemp->pNext = pItem;
	}
}

ITEM* CHash::Lookup(const char* key)
{
	ITEM* pItem = GetPosition(key);
	return pItem;
}

///////////////////////////////////////////////////////////////
//	�� �� �� : GetPosition
//	�������� : CHash
//	�������� : ���ҹؼ�����hash���е�λ��
//	������� : 
//	��    ע : 
//	��    �� : mjs
//	ʱ    �� : 2006��6��23��
//	�� �� ֵ : key�ڱ��У����عؼ��ֵ�ָ�룬����NULL
//	����˵�� : const char* key,�ؼ���
///////////////////////////////////////////////////////////////
ITEM* CHash::GetPosition(const char* key)
{
	ASSERT(m_nHashTableSize > 0);  // make sure we don't underflow

	UINT nHash = HashKey(key);

	ITEM* pItem = m_pHashTable[nHash];
	while(pItem != NULL && strcmp(pItem->key,key) != 0)
		pItem = pItem->pNext; //��ͻʱ�������������β���

	return pItem;
}

///////////////////////////////////////////////////////////////
//	�� �� �� : Remove
//	�������� : CHash
//	�������� : ɾ�����еĹؼ���
//	������� : 
//	��    ע : 
//	��    �� : mjs
//	ʱ    �� : 2005��10��31��
//	�� �� ֵ : BOOL�����д��ڸùؼ��֣�����1���粻���ڣ�����0
//	����˵�� : const char* key
///////////////////////////////////////////////////////////////
BOOL CHash::Remove(const char* key)
{
	//��hash����ɾ��
	UINT nHash = HashKey(key);

	ITEM* pItem = m_pHashTable[nHash];
	if(pItem == NULL)
		return false;
	ITEM* pFirstItem = pItem;	//��¼��һ���ڵ�ָ��
	ITEM* pPreItem = pItem;		//��¼ǰһ�ڵ�ָ��
	while(pItem != NULL && strcmp(pItem->key,key) != 0)
	{
		pPreItem = pItem;
		pItem = pItem->pNext; //��ͻʱ�������������β���
	}

	if(pItem == NULL)				//�˹ؼ��ֲ��ڱ���
		return false;
	else if(pItem == pFirstItem)	//Ҫɾ���Ľڵ�������ĵ�һ��λ��
		m_pHashTable[nHash] = pItem->pNext;
	else
		pPreItem->pNext = pItem->pNext;//delete the found item

	//free memory
	delete [] pItem->key;
	delete [] pItem->relation;
	delete pItem;

	return true; //found
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
				delete [] pItem->relation;
				pItem = pItem->pNext;
				delete pTemp;
			}
		}

		// free hash table
		delete [] m_pHashTable;
		m_pHashTable = NULL;// free hash table
	}
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



