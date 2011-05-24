///////////////////////////////////////////////////////////////
//	文 件 名 : VerbTag.h
//	文件功能 : 动词细分类系统的类的声明
//	作    者 : zhp
//	创建时间 : 2005年3月9日
//	备    注 : 对分词词性标注的结果中的动词进行细分类，共定义了
//             8类动词，采用HMM模型，模型中的状态是8类动词，同
//             时考虑了动词与其两侧的其他词性之间的转移概率
//	历史记录 : 2005年3月23日完成beta测试版
///////////////////////////////////////////////////////////////
#ifndef _VERB_TAG_
#define _VERB_TAG_
//#include <cstdio>
#define STL_USING_ALL
#include <stl.h>
#include <deque>
using namespace std;

extern string g_strDataPath;

struct Prob 
{
	int posIdx;    //词性的索引
	float emitProb;//词性对应的发射概率（已取了负对数）
};

struct Emit //发射概率的数据结构
{
	int num;  //词性个数
	Prob* prob; //发射概率
};

struct VerbWithAdjacentInfo
{
	int verbIndex; //动词的索引
	int posNum; //该动词具有词性的个数
	int positionInSentence; //在句子中的位置，即该动词是句子中的第几个词
	int prePosIndex; //动词前面词性的索引，-1表示前面没有其他词性
	int nextPosIndex; //动词后面词性的索引，-1表示后面没有其他词性
};
typedef vector<VerbWithAdjacentInfo> VerbArray;

struct PathNode
{
	float accumProb; //到此状态结点的累计概率，初始为发射概率和
	//该词性与两侧其他词性之间转移概率的乘积
	int preNodeSubscript; //路径中前一个状态结点在其数组中的下标，初始为-1
	int curNodePosIndex; //当前状态结点词性的索引
};

class CVerbTag
{
public:
	CVerbTag();
	~CVerbTag();
	float VerbTagging(string& inSentence, string& outSentence);
	void Initialize(); //程序初始化，加载各种参数
	void Release();

private:
	vector< pair<string, string> > vecWordPos;//存放输入句子的每一个词/词性对
	VerbArray vecVerb;
	PathNode** nodeArray; 

	void Sentence2VerbArray(string& inSentence);
	void InitHMMStructure(string& inSentence);
	void ViterbiSearch();
	float GenerateBestPath(string& outSentence);
	void FreeMemary();

//---------------各种参数的数据结构及其加载操作--------------------

	bool LoadStart();
	bool LoadTrans();
	bool LoadEmit();
	bool LoadForwardTrans();
	bool LoadBackwardTrans();
	bool LoadPos();
	bool LoadOtherposMap();
	bool LoadVerbMap();

	enum
	{
		POS_NUM = 8, //动词词性的个数 8, 12
		OTHERPOS_NUM = 27, //其他词性 27, 34, 42
		VERB_NUM = 12205 //动词个数
	};

	Emit *emit;
	float *start;
	float **trans, **forwardTrans, **backwardTrans;
	string *idxPos;
	map<string, int> mapOtherposIdx; //其他词性到其索引的映射
	map<string, int> mapVerbIdx; //动词到其索引的映射
//	string idxPos[POS_NUM];
//	map<string, int> mapOtherposIdx; //其他词性到其索引的映射
//	map<string, int> mapVerbIdx; //动词到其索引的映射
//	float start[POS_NUM]; //初始概率数组
//	float trans[POS_NUM][POS_NUM]; //转移概率矩阵
//	float forwardTrans[POS_NUM][OTHERPOS_NUM];
//	float backwardTrans[POS_NUM][OTHERPOS_NUM];
//	Emit emit[VERB_NUM+1]; //下标就是词的索引
//	bool initialized; //标识是否已经加载参数文件，
							 //true表示已加载，false表示未加载
};
#endif
