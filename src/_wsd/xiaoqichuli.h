// xiaoqichuli.h: interface for the xiaoqichuli class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_XIAOQICHULI_H__18F5F1DB_0CE4_4BBF_A72B_9225AE4E5308__INCLUDED_)
#define AFX_XIAOQICHULI_H__18F5F1DB_0CE4_4BBF_A72B_9225AE4E5308__INCLUDED_

// #define STL_USING_ALL
// #include "stl.h"
#include <map>
#include <string>
#include "hash.h"

using namespace std;

struct wordID
{
public:
	char word[27];//词条
	int    IDw;//词条对应的ID号
	friend bool operator <(const wordID & left,const wordID & right)
	{
		return left.word < right.word;
	}
};

struct wordPvs
{
public:
	int     IDw;
	float   Pvs;
	friend bool operator <(const wordPvs & left,const wordPvs & right)
	{
		return left.IDw < right.IDw;
	}
};

struct word_Tmp
{
public:
	string word;            //每句待处理的词汇
//	int    IDs;             //待输出的词汇向量
	string IDs;
};

typedef vector<wordPsk>::iterator PP;         

///////////////////////////////////////////////////////////////
//	类    名 : xiaoqichuli
//	基    类 : 
//	描    述 : 
//	功    能 : 用来进行词义消歧
//	历史记录 : 
//	使用说明 : 
//	作    者 : lemon
//	时    间 : 2006年4月24日
//	备    注 : 
///////////////////////////////////////////////////////////////
class xiaoqichuli  
{
public:
	void ReadCorpus(const string strSentenceTagger,
		string &strOutNum,
		string &strOutExplain,
		string &strcode);//处理一句话
	xiaoqichuli();
	virtual ~xiaoqichuli();
	void SetDataPath(const char *cszDataPath = "./wsd_data/")
	{
		m_strDataPath = cszDataPath;
	}
	void LoadDictionary();//加载资源
	void Release();
	void CreateTitleWordList();
	void CreateWordCode();
	
private:
	void CountSore(string &strOutNum, string &strOutExplain);
	
	void _ReadPvs(vector<wordPsk> ::iterator pIt,vector<wordPvs>& temp);
	void CountPvs(int i, vector<wordPvs> vectWordPvsTmp, vector<wordPsk> ::iterator pIt);
	void SearchIDw();
	
private:
	vector<int>      vectIDTmp;       //每句临时的词汇ID
	vector<word_Tmp> vectWordTmp;     //每句待处理的词汇 
	double SoreTmp;
	vector<pair<double, string> > vectSore;    //只考虑发射概率
	vector<pair<double, string> > vectSore_T;  //条件概率和发射概率的乘积
	
	map<string, string> mapIDs_Explain;
	map<string , string > mapwordcode;
    CHash hashtable;
	string m_strDataPath;
};

#endif // !defined(AFX_XIAOQICHULI_H__18F5F1DB_0CE4_4BBF_A72B_9225AE4E5308__INCLUDED_)
