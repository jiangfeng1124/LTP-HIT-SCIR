//Copyright (c) 2005,HIT-IRLab. All Rights Reserved.

#define STL_USING_ALL
#include "stl.h"

#ifndef _HASH_FIND_
#define  _HASH_FIND_
#define FAIL -1

///////////////////////////////////////////////////////////////
//	类    名 : CHash
//	基    类 : 无
//	描    述 : 根据为英文拼写检查写的词表查找函数（Version6.02）修改，
//				改为查找关键词属性（概率）的Hash函数
//	功    能 : 将条目放入Hash表中，然后可以查找关键字是否存在，
//				然后返回对应的数据，用链表法解决冲突
//	使用说明 : 先初始化，然后将条目依次放入表中，然后可以查询
//	作    者 : 马金山
//	时    间 : 2006年6月17日修改
//	备    注 :（1）删除查找等长词的功能
//			  （2）改为允许存关键字相同的词条
///////////////////////////////////////////////////////////////
typedef int BOOL;
typedef unsigned int UINT;

struct ITEM			// hash表的条目
{
	char* key;		// 关键字
	char* relation;	// 关系类型
	float prob;		// 关键字的属性
    ITEM* pNext;
};

class CHash  
{
public:
	CHash();
	virtual ~CHash();
	void InitHashTable(int nTableSize);			//初始化hash表，输入为数字大于或等于插入的关键字个数
	void SetAt(const char* key, const char* relation, float prob);	//将关键字插入hash表中
	ITEM* Lookup(const char* key);//查找关键字是否存在，存在返回ture，否则返回false
	BOOL Remove(const char* key);				//删除表中的关键字，表中如存在，删除，返回1，如不存在，返回0
	void RemoveAll();							//释放内存


private:
	inline int HashKey(const char* key) const;		//计算关键字的键值
	ITEM* GetPosition(const char* key);				//获取关键字在hash表中的位置
	int NextPrime(int N);							//获取大于N的第一个质数
	int IsPrime(int N);								//判断一个数是否为质数

	UINT m_nHashTableSize;
	ITEM** m_pHashTable;
};

#endif

