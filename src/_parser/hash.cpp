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
	ASSERT(nHashSize >= 0);

	if(nHashSize > 17)	// 长度小于17，取默认值17
		m_nHashTableSize = NextPrime(nHashSize);

	m_pHashTable = new ITEM*[m_nHashTableSize];
	memset(m_pHashTable, 0, sizeof(ITEM*)*m_nHashTableSize);
}

///////////////////////////////////////////////////////////////
//	函 数 名 : SetAt
//	所属类名 : CHash
//	函数功能 : 将关键字插入Hash表，允许关键字重复
//	处理过程 : 
//	备    注 : 
//	作    者 : mjs
//	时    间 : 2005年6月23日
//	返 回 值 : void
//	参数说明 : const char* key, 插入表中的关键字
//			   int property, 关键字的属性
///////////////////////////////////////////////////////////////
void CHash::SetAt(const char* key, const char* relation, float prob)
{
	//创建新节点
	ITEM* pItem = new ITEM;
	int nLen = strlen(key);
	pItem->key = new char[nLen+1];	// 动态申请内存
	pItem->key[nLen] = '\0';
	strcpy(pItem->key,key);

	nLen = strlen(relation);
	pItem->relation = new char[nLen+1];
	pItem->relation[nLen] = '\0';
	strcpy(pItem->relation,relation);

	pItem->prob = prob;
	pItem->pNext = NULL;

	//将该单词加入hash表中
	UINT nHash = HashKey(key);
	ITEM* pTemp = m_pHashTable[nHash];
	if(pTemp == NULL)				// the first position is vacant
		m_pHashTable[nHash] = pItem;// put into hash table
	else
	{
		while(pTemp->pNext != NULL)
			pTemp = pTemp->pNext;	// 沿着链表依次查找
		pTemp->pNext = pItem;
	}
}

ITEM* CHash::Lookup(const char* key)
{
	ITEM* pItem = GetPosition(key);
	return pItem;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : GetPosition
//	所属类名 : CHash
//	函数功能 : 查找关键字在hash表中的位置
//	处理过程 : 
//	备    注 : 
//	作    者 : mjs
//	时    间 : 2006年6月23日
//	返 回 值 : key在表中，返回关键字的指针，否则NULL
//	参数说明 : const char* key,关键字
///////////////////////////////////////////////////////////////
ITEM* CHash::GetPosition(const char* key)
{
	ASSERT(m_nHashTableSize > 0);  // make sure we don't underflow

	UINT nHash = HashKey(key);

	ITEM* pItem = m_pHashTable[nHash];
	while(pItem != NULL && strcmp(pItem->key,key) != 0)
		pItem = pItem->pNext; //冲突时，沿着链表依次查找

	return pItem;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : Remove
//	所属类名 : CHash
//	函数功能 : 删除表中的关键字
//	处理过程 : 
//	备    注 : 
//	作    者 : mjs
//	时    间 : 2005年10月31日
//	返 回 值 : BOOL，表中存在该关键字，返回1，如不存在，返回0
//	参数说明 : const char* key
///////////////////////////////////////////////////////////////
BOOL CHash::Remove(const char* key)
{
	//从hash链中删除
	UINT nHash = HashKey(key);

	ITEM* pItem = m_pHashTable[nHash];
	if(pItem == NULL)
		return false;
	ITEM* pFirstItem = pItem;	//记录第一个节点指针
	ITEM* pPreItem = pItem;		//记录前一节点指针
	while(pItem != NULL && strcmp(pItem->key,key) != 0)
	{
		pPreItem = pItem;
		pItem = pItem->pNext; //冲突时，沿着链表依次查找
	}

	if(pItem == NULL)				//此关键字不在表中
		return false;
	else if(pItem == pFirstItem)	//要删除的节点在链表的第一个位置
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



