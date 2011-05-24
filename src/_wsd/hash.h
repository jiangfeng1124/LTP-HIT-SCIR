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

struct wordPsk//用于消歧的信息
{
public:
	char IDs[5];
	float  Psk;
	float  P_LAM;
	int   begin;
	int   end;
};

struct ITEM			// hash表的条目
{
	char* key;		// 关键字
	int property;	// 关键字的ID
	vector<wordPsk> psk;
	ITEM* pNext;
};


///////////////////////////////////////////////////////////////
//	类    名 : CHash
//	基    类 : 
//	描    述 : 
//	功    能 : 
//	历史记录 : 
//	使用说明 : 
//	作    者 : lemon
//	时    间 : 2006年4月24日
//	备    注 : 为了提高消歧速度，采用了hash表的结构
///////////////////////////////////////////////////////////////
class CHash  
{

public:
	CHash();
	virtual ~CHash();
	void InitHashTable(int nTableSize);			//初始化hash表，输入为数字大于或等于插入的关键字个数
	void SetAt(const char* key, int property,vector<wordPsk> psk);	//将关键字插入hash表中
	int GetPosition(const char* key, UINT& nHash);	//获取关键字在hash表中的位置
	ITEM* Lookup(UINT& nHash);//返回hash表中nHash所在位置的指针
	void RemoveAll();							//释放内存
	


private:
	inline int HashKey(const char* key) const;		//计算关键字的键值
	
	int NextPrime(int N);							//获取大于N的第一个质数
	int IsPrime(int N);								//判断一个数是否为质数

	UINT m_nHashTableSize;
	ITEM** m_pHashTable;
};

#endif

