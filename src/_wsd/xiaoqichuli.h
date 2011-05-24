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
	char word[27];//����
	int    IDw;//������Ӧ��ID��
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
	string word;            //ÿ�������Ĵʻ�
//	int    IDs;             //������Ĵʻ�����
	string IDs;
};

typedef vector<wordPsk>::iterator PP;         

///////////////////////////////////////////////////////////////
//	��    �� : xiaoqichuli
//	��    �� : 
//	��    �� : 
//	��    �� : �������д�������
//	��ʷ��¼ : 
//	ʹ��˵�� : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��24��
//	��    ע : 
///////////////////////////////////////////////////////////////
class xiaoqichuli  
{
public:
	void ReadCorpus(const string strSentenceTagger,
		string &strOutNum,
		string &strOutExplain,
		string &strcode);//����һ�仰
	xiaoqichuli();
	virtual ~xiaoqichuli();
	void SetDataPath(const char *cszDataPath = "./wsd_data/")
	{
		m_strDataPath = cszDataPath;
	}
	void LoadDictionary();//������Դ
	void Release();
	void CreateTitleWordList();
	void CreateWordCode();
	
private:
	void CountSore(string &strOutNum, string &strOutExplain);
	
	void _ReadPvs(vector<wordPsk> ::iterator pIt,vector<wordPvs>& temp);
	void CountPvs(int i, vector<wordPvs> vectWordPvsTmp, vector<wordPsk> ::iterator pIt);
	void SearchIDw();
	
private:
	vector<int>      vectIDTmp;       //ÿ����ʱ�Ĵʻ�ID
	vector<word_Tmp> vectWordTmp;     //ÿ�������Ĵʻ� 
	double SoreTmp;
	vector<pair<double, string> > vectSore;    //ֻ���Ƿ������
	vector<pair<double, string> > vectSore_T;  //�������ʺͷ�����ʵĳ˻�
	
	map<string, string> mapIDs_Explain;
	map<string , string > mapwordcode;
    CHash hashtable;
	string m_strDataPath;
};

#endif // !defined(AFX_XIAOQICHULI_H__18F5F1DB_0CE4_4BBF_A72B_9225AE4E5308__INCLUDED_)
