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
//	函 数 名 : SetAt
//	所属类名 : CHash
//	函数功能 : 将关键字插入Hash表
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月24日
//	返 回 值 : void
//	参数说明 : const char* key,词条
//				 int property,词条对应的id号
//				 vector<wordPsk> psk，和词条对应的上下文词汇的共现信息
///////////////////////////////////////////////////////////////
void CHash::SetAt(const char* key, int property, vector<wordPsk> psk)
{
	UINT nHash;
	if (GetPosition(key, nHash) == FAIL)// the key is not in map
	{
		//创建新节点
		ITEM* pItem = new ITEM;
		int nLen = strlen(key);
		pItem->key = new char[nLen+1];//动态申请内存
		pItem->key[nLen] = '\0';
		strcpy(pItem->key,key);
		pItem->property = property;
		pItem->psk= psk;
		pItem->pNext = NULL;
        

		//将该单词加入hash表中
		ITEM* pTemp = m_pHashTable[nHash];
		if(pTemp == NULL)	//the first position is vacant
			m_pHashTable[nHash] = pItem;// put into hash table
		else
		{
			while(pTemp->pNext != NULL)
				pTemp = pTemp->pNext; //沿着链表依次查找
			pTemp->pNext = pItem;
		}
		
	}
}

///////////////////////////////////////////////////////////////
//	函 数 名 : Lookup
//	所属类名 : CHash
//	函数功能 : 得到hash结构中nhash位置的指针
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月22日
//	返 回 值 : ITEM*
//	参数说明 : UINT& nHash
///////////////////////////////////////////////////////////////
ITEM* CHash::Lookup(UINT& nHash)
{
	return m_pHashTable[nHash];
}


///////////////////////////////////////////////////////////////
//	函 数 名 : InitHashTable
//	所属类名 : CHash
//	函数功能 : 对hash表进行初始化
//	处理过程 : 
//	备    注 : 
//	作    者 : mjs
//	时    间 : 2005年10月23日
//	返 回 值 : 
//	参数说明 : 用户指定的hash表长度，应该大于等于词表长度
///////////////////////////////////////////////////////////////
void CHash::InitHashTable(int nHashSize)
{
	// ASSERT(nHashSize >= 0);
	
	if(nHashSize > 17)	// 长度小于17，取默认值17
		m_nHashTableSize = NextPrime(nHashSize);

	m_pHashTable = new ITEM*[m_nHashTableSize];
	memset(m_pHashTable, 0, sizeof(ITEM*)*m_nHashTableSize);
}

///////////////////////////////////////////////////////////////
//	函 数 名 : RemoveAll
//	所属类名 : CHash
//	函数功能 : 删除hash表，释放全部内存
//	处理过程 : 
//	备    注 : 
//	作    者 : mjs
//	时    间 : 2005年10月24日
//	返 回 值 : void
//	参数说明 : 
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
//	函 数 名 : GetPosition
//	所属类名 : CHash
//	函数功能 : 查找关键字在hash表中的位置，并通过引用nHash返回
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月24日
//	返 回 值 : int, key在表中，返回关键字的属性1，否则返回-1
//	参数说明 : const char* key,关键字，UINT& nHash，key在表中的位置
///////////////////////////////////////////////////////////////
int CHash::GetPosition(const char* key, UINT& nHash)
{
	// ASSERT(m_nHashTableSize > 0);  // make sure we don't underflow

	nHash = HashKey(key);

	ITEM* pItem = m_pHashTable[nHash];
	if(pItem == NULL)
		return FAIL;
	while(pItem != NULL && strcmp(pItem->key,key) != 0)
		pItem = pItem->pNext; //冲突时，沿着链表依次查找

	if(pItem == NULL)//not in map
		return FAIL;
	else
		return 1; //found
}

inline int CHash::HashKey(const char* key) const
{
	unsigned int nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;//借鉴MFC中的方法
	
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



