///////////////////////////////////////////////////////////////
//	文 件 名 : VerbTag.cpp
//	文件功能 : 动词细分类系统的类的实现文件
//	作    者 : zhp
//	创建时间 : 2005年3月9日
//	备    注 : 对分词词性标注的结果中的动词进行细分类，共定义了
//             8类动词，采用HMM模型，模型中的状态是8类动词，同
//             时考虑了动词与其两侧的其他词性之间的转移概率
//	历史记录 : 2005年3月23日完成beta测试版
///////////////////////////////////////////////////////////////
#include "VerbTag.h"
#include "MyLib.h"


//类中静态变量的定义（定义后才会分配空间）
//string CVerbTag::idxPos[POS_NUM];
//map<string, int> CVerbTag::mapOtherposIdx;
//map<string, int> CVerbTag::mapVerbIdx;
//float CVerbTag::start[POS_NUM];
//float CVerbTag::trans[POS_NUM][POS_NUM];
//float CVerbTag::forwardTrans[POS_NUM][OTHERPOS_NUM];
//float CVerbTag::backwardTrans[POS_NUM][OTHERPOS_NUM];
//Emit CVerbTag::emit[VERB_NUM+1];
//bool CVerbTag::initialized = false; 

CVerbTag::CVerbTag()
{
	//if (initialized == false) 
	//{
	//	Initialize();
	//}
}

CVerbTag::~CVerbTag()
{
}

///////////////////////////////////////////////////////////////
//	函 数 名 : Initialize
//	所属类名 : CVerbTag
//	函数功能 : 加载各种参数文件
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 
///////////////////////////////////////////////////////////////
void CVerbTag::Initialize()
{
	idxPos = new string[POS_NUM];
	start = new float[POS_NUM];
	emit = new Emit[VERB_NUM+1];
	trans = new float*[POS_NUM];
	forwardTrans = new float*[POS_NUM];
	backwardTrans = new float*[POS_NUM];
	int i;
	for(i = 0; i < POS_NUM; i++)
	{
		trans[i] = new float[POS_NUM];
		forwardTrans[i] = new float[OTHERPOS_NUM];
		backwardTrans[i] = new float[OTHERPOS_NUM];
	}
	LoadStart();
 	LoadTrans();
	LoadEmit();
	LoadForwardTrans();
	LoadBackwardTrans();
	LoadPos();
	LoadOtherposMap();
 	LoadVerbMap();
//	initialized = true;
}

void CVerbTag::Release()
{
	delete [] emit;
	delete [] idxPos;
	delete [] start;

	int i;
	for(i = 0; i < POS_NUM; i++)
	{
		delete [] trans[i];
		delete [] forwardTrans[i];
		delete [] backwardTrans[i];
	}
	delete [] trans;
	delete [] forwardTrans;
	delete [] backwardTrans;

	mapOtherposIdx.clear();
	mapVerbIdx.clear();
	vecWordPos.clear(); 
	vecVerb.clear(); 
}

///////////////////////////////////////////////////////////////
//	函 数 名 : VerbTagging
//	所属类名 : CVerbTag
//	函数功能 : 动词细分类系统的接口函数
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月21日
//	修改历史 : 
///////////////////////////////////////////////////////////////
float CVerbTag::VerbTagging(string& inSentence, string& outSentence)
{
	InitHMMStructure(inSentence);
	ViterbiSearch();
	return GenerateBestPath(outSentence);
}


//////////////////////////////////////////////////////////////////////////////
//	函 数 名 : Sentence2VerbArray
//	所属类名 : CVerbTag
//	函数功能 : 把一个输入的字符串转换为VerbArray型的数组
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月19日
//  用到的数据结构 :
//	struct VerbWithAdjacentInfo
//	{
//		int verbIndex; //动词的索引
//		int posNum; //该动词具有词性的个数
//		int positionInSentence; //在句子中的位置，即该动词是句子中的第几个词
//		int prePosIndex; //动词前面词性的索引，-1表示前面没有其他词性
//		int nextPosIndex; //动词后面词性的索引，-1表示后面没有其他词性
//	};
//	typedef vector<VerbWithAdjacentInfo> VerbArray;
//	修改历史 : 
///////////////////////////////////////////////////////////////////////////////
void CVerbTag::Sentence2VerbArray(string& inSentence)
{
	vecWordPos.clear(); 
 	vecVerb.clear(); 

	split_to_pair(inSentence, vecWordPos);
	int wordNum = vecWordPos.size();
	map<string, int>::iterator iter;
	
	VerbWithAdjacentInfo verbNode;
	for(int i = 0; i < wordNum; i++)
	{
		if (vecWordPos[i].second == "v") //如果是动词则插入动态数组vecVerb中
		{
			iter = mapVerbIdx.find(vecWordPos[i].first);
			if (iter != mapVerbIdx.end()) 
			{
				verbNode.verbIndex = iter->second;
			}
			else
			{
				//如果动词表中找不到该动词，则默认该动词词性为vt
				//文件emit.dat最后一行为1 8 20，8即vt的索引
				verbNode.verbIndex = VERB_NUM; 
			}
			
			if (i > 0 && vecWordPos[i-1].second != "v")
			{
				iter = mapOtherposIdx.find(vecWordPos[i-1].second);
				if (iter != mapOtherposIdx.end()) 
				{
					verbNode.prePosIndex = iter->second;
				}
				else //此标记不是一个词性标记
				{
					verbNode.prePosIndex = -1;
				}
			}
			else //此标记是动词
			{
				verbNode.prePosIndex = -1;
			}

			if (i < wordNum-1 && vecWordPos[i+1].second != "v")
			{
				iter = mapOtherposIdx.find(vecWordPos[i+1].second);
				if (iter != mapOtherposIdx.end()) 
				{
					verbNode.nextPosIndex = iter->second;
				}
				else //此标记不是一个词性标记
				{
					verbNode.nextPosIndex = -1;
				}
			}
			else //此标记是动词
			{
				verbNode.nextPosIndex = -1;
			}
			
			verbNode.posNum = emit[verbNode.verbIndex].num;
			verbNode.positionInSentence = i;
			vecVerb.push_back(verbNode);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//	函 数 名 : InitHMMStructure
//	所属类名 : CVerbTag
//	函数功能 : 初始化HMM模型中的数据结构（二维数组）
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月21日
//  用到的数据结构 :
//	struct PathNode
//	{
//		float accumProb; //到此状态结点的累计概率，初始为发射概率和
//                       //该词性与两侧其他词性之间转移概率的乘积
//		int preNodeSubscript; //路径中前一个状态结点在其数组中的下标，初始为-1
//		int curNodePosIndex; //当前状态结点词性的索引
//	};
//	PathNode** nodeArray; 
//	修改历史 : 
///////////////////////////////////////////////////////////////////////////////
void CVerbTag::InitHMMStructure(string& inSentence)
{
	Sentence2VerbArray(inSentence);
	int verbNum = vecVerb.size();
	nodeArray = new PathNode*[verbNum];
	//为每一个动词根据动词词性个数分配空间并初始化
	for(int i = 0; i < verbNum; i++) 
	{
		nodeArray[i] = new PathNode[vecVerb[i].posNum];

		for(int j = 0; j < vecVerb[i].posNum; j++)
		{
			nodeArray[i][j].preNodeSubscript = -1;
			nodeArray[i][j].curNodePosIndex = emit[vecVerb[i].verbIndex].prob[j].posIdx;

			int curPosIndex = nodeArray[i][j].curNodePosIndex;
			int prePosIndex = vecVerb[i].prePosIndex;
			int nextPosIndex = vecVerb[i].nextPosIndex;
			float forwardTransProb = 0, backwardTransProb = 0;
			if (prePosIndex != -1) 
			{
				forwardTransProb = forwardTrans[curPosIndex][prePosIndex];
			}
			if (nextPosIndex != -1) 
			{
				backwardTransProb = backwardTrans[curPosIndex][nextPosIndex];
			}
			
			nodeArray[i][j].accumProb = emit[vecVerb[i].verbIndex].prob[j].emitProb
				+ forwardTransProb + backwardTransProb;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//	函 数 名 : ViterbiSearch
//	所属类名 : CVerbTag
//	函数功能 : Viterbi搜索
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月21日
//	修改历史 : 
///////////////////////////////////////////////////////////////////////////////
void CVerbTag::ViterbiSearch()
{
	int verbNum = vecVerb.size();
	for (int t = 0; verbNum > 0 && t < vecVerb[0].posNum; t++) 
	{
		nodeArray[0][t].accumProb += start[nodeArray[0][t].curNodePosIndex];
	}
	
	float tempProb, curnodeEmit;
	const float INFINITE = 10000;
	for (int i = 1; i < verbNum; i++) //对每个动词
	{
		for (int j = 0; j < vecVerb[i].posNum; j++) //对动词的每个词性
		{	
			curnodeEmit = nodeArray[i][j].accumProb;
			nodeArray[i][j].accumProb = INFINITE;
			for (int k = 0; k < vecVerb[i-1].posNum; k++) //对前一个动词的每一个词性
			{
				int preIndex = nodeArray[i-1][k].curNodePosIndex; 
				int	curIndex = nodeArray[i][j].curNodePosIndex;

				tempProb = curnodeEmit + nodeArray[i-1][k].accumProb
					+ trans[preIndex][curIndex];
				if (tempProb < nodeArray[i][j].accumProb) 
				{
					nodeArray[i][j].accumProb = tempProb;
					nodeArray[i][j].preNodeSubscript = k;
				}
			}			
		}
	}	
}

///////////////////////////////////////////////////////////////////////////////
//	函 数 名 : FreeMemary
//	所属类名 : CVerbTag
//	函数功能 : 释放申请的内存空间
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月23日
//	修改历史 : 
///////////////////////////////////////////////////////////////////////////////
void CVerbTag::FreeMemary()
{
	for (unsigned int i = 0; i < vecVerb.size(); i++) 
	{
		delete[] nodeArray[i];
	}
	delete[] nodeArray;
}

///////////////////////////////////////////////////////////////////////////////
//	函 数 名 : GenerateBestPath
//	所属类名 : CVerbTag
//	函数功能 : 生成最优的动词标注结果
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月21日
//	修改历史 : 2005年4月2日，修改一个bug，加入 if (outSentence.size() > 0) 
///////////////////////////////////////////////////////////////////////////////
float CVerbTag::GenerateBestPath(string& outSentence)
{
	const float INFINITE = 10000;
	float tempProb = INFINITE;
	int verbNum = vecVerb.size();
	int lastNodeSubscript;
	if (verbNum > 0) //如果句子中的动词个数不为0
	{
		//获得最优路径的最后一个状态在其数组中的下标
		for (int i = 0; i < vecVerb[verbNum-1].posNum; i++) 
		{
			if (nodeArray[verbNum-1][i].accumProb < tempProb) 
			{
				tempProb = nodeArray[verbNum-1][i].accumProb;
				lastNodeSubscript = i;
			}
		}
		deque<string> dequeBestPath;
		//把最优的每一个动词标记存到一个deque中
		for (int j = verbNum-1, k = lastNodeSubscript; j >= 0; j--) 
		{
			int posIdx = nodeArray[j][k].curNodePosIndex;
			dequeBestPath.push_front(idxPos[posIdx]);
			if (j-1 >= 0) 
			{
				k = nodeArray[j][k].preNodeSubscript;
			}
		}
		
		for (int l = 0; l < verbNum; l++) //把vecWordPos中的v转换成细化的动词标记
		{
			vecWordPos[vecVerb[l].positionInSentence].second = dequeBestPath[l];
		}
	}
	
	outSentence = "";
	int wordNum = vecWordPos.size();
	for (int m = 0; m < wordNum; m++) //生成最后的句子，保存在outSentence中
	{
		outSentence += vecWordPos[m].first + "/" + vecWordPos[m].second + " ";
	}

	FreeMemary();
	return tempProb/(verbNum*2);
}


//--------------------------加载参数------------------------------

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadStart
//	所属类名 : CVerbTag
//	函数功能 : 加载初始概率文件
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 
///////////////////////////////////////////////////////////////
bool CVerbTag::LoadStart()
{
	ifstream in( (g_strDataPath+"start.dat").c_str() );
	if (!in) 
	{
		cerr<<"cannot open the file start.dat!"<<endl;
		exit(1);
	}
	int i;
	for(i = 0; i < POS_NUM; i++)
	{
		in>>start[i];
	}
	if (i != POS_NUM) 
	{
		cout<<"error when load start file!"<<endl;
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadTrans
//	所属类名 : CVerbTag
//	函数功能 : 加载转移概率文件
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 
///////////////////////////////////////////////////////////////
bool CVerbTag::LoadTrans()
{
	ifstream in( (g_strDataPath+"trans.dat").c_str() );
	if (!in) 
	{
		cerr<<"cannot open the file trans.dat!"<<endl;
		exit(1);
	}
	for(int i = 0; i < POS_NUM; i++)
		for(int j = 0; j < POS_NUM; j++)
			in >> trans[i][j] ;
	return true;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadEmit
//	所属类名 : CVerbTag
//	函数功能 : 加载发射概率文件
//	备    注 : emit.dat文件的格式：
//   3 8 20 10 20 5 20  //3个词性，后面是词性的序号和概率
//   3 8 20 9 20 5 20
//   2 8 20 5 20
//   3 8 7.17104 9 6.17942 5 7.55495
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 2005年3月13日，改为C操作，速度大大提高
//             2005年3月26日，加入了delete[] buf;一行
///////////////////////////////////////////////////////////////
bool CVerbTag::LoadEmit()
{
	FILE *fp;
	if ( (fp = fopen( (g_strDataPath+"emit.dat").c_str(), "rb")) == NULL ) 
	{
		cerr<<"cannot open the file emit.dat!"<<endl;
	}
	fseek(fp, 0 , SEEK_END); 
    int fileLength = ftell(fp); 
 	char *buf = new char[fileLength];
	fseek(fp, 0, SEEK_SET);

	fread(buf, fileLength, 1, fp);
	fclose(fp);
	int flag = 0;//表示读入字符类型的标志
	             //0:词性个数, 1:词性索引, 2:词性发射概率
	int line = 0;//文件中的行号，即emit数组的下标
	int pos = 0;//指示是第几个词性
	string temp;//存放临时字符串
	
	for(int i = 0; i < fileLength; i++)
	{
		if (flag == 0) 
		{
			if (buf[i] == 32) //读入空格，则输出词性个数
			{
				flag = 1;
				emit[line].num = atoi(temp.c_str());
				emit[line].prob = new Prob[emit[line].num];
				temp = "";
			}
			else
			{
				temp += buf[i];
			}	
		}
		else if (flag == 1) 
		{
			if (buf[i] == 32) 
			{
				flag = 2;
				emit[line].prob[pos].posIdx = atoi(temp.c_str());
				temp = "";
			}
			else
			{
				temp += buf[i];
			}
		}
		else if (flag == 2) 
		{
			if (buf[i] == 32) 
			{
				flag = 1;
				emit[line].prob[pos].emitProb = (float)atof(temp.c_str());
				pos++;
				temp = "";
			}
			else if (buf[i] == 10) //读入回车符
			{
				flag = 0;
				emit[line].prob[pos].emitProb = (float)atof(temp.c_str());
				pos = 0;
				temp = "";
				line++;
			}
			else if (buf[i] != 13) //忽略读入的换行符
			{
				temp += buf[i];			
			}
		}
	}
	delete[] buf;

	return true;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadForwardTrans
//	所属类名 : CVerbTag
//	函数功能 : 加载前向转移概率文件
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 
///////////////////////////////////////////////////////////////
bool CVerbTag::LoadForwardTrans()
{
	ifstream in( (g_strDataPath+"forwardtrans.dat").c_str() );
	if (!in) 
	{
		cerr<<"cannot open the file forwardtrans.dat!"<<endl;
		exit(1);
	}
	for(int i = 0; i < POS_NUM; i++)
		for(int j = 0; j < OTHERPOS_NUM; j++)
			in >> forwardTrans[i][j] ;
	return true;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadBackwardTrans
//	所属类名 : CVerbTag
//	函数功能 : 加载后向转移概率文件
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 
///////////////////////////////////////////////////////////////
bool CVerbTag::LoadBackwardTrans()
{
	ifstream in( (g_strDataPath+"backwardtrans.dat").c_str() );
	if (!in) 
	{
		cerr<<"cannot open the file backwardtrans.dat!"<<endl;
		exit(1);
	}
	for(int i = 0; i < POS_NUM; i++)
		for(int j = 0; j < OTHERPOS_NUM; j++)
			in >> backwardTrans[i][j] ;
	return true;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadPos
//	所属类名 : CVerbTag
//	函数功能 : 加载动词标记文件
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 2005年3月21日，加上idxPos[i] = pos;一行
///////////////////////////////////////////////////////////////
bool CVerbTag::LoadPos()
{
	ifstream in( (g_strDataPath+"pos.dat").c_str() );
	if (!in) 
	{
		cerr<<"cannot open the file pos.dat!"<<endl;
		exit(1);
	}
	string pos;
	for(int i = 0; i < POS_NUM; i++)
	{
		in>>pos;
		idxPos[i] = pos;
	}
	return true;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadOtherposMap
//	所属类名 : CVerbTag
//	函数功能 : 加载其他词性标记文件
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 
///////////////////////////////////////////////////////////////
bool CVerbTag::LoadOtherposMap()
{
	ifstream in( (g_strDataPath+"otherpos.dat").c_str() );
	if (!in) 
	{
		cerr<<"cannot open the file otherpos.dat!"<<endl;
		exit(1);
	}
	string pos;
	for(int i = 0; i < OTHERPOS_NUM; i++)
	{
		in>>pos;
		mapOtherposIdx[pos] = i;
	}
	return true;
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadVerbMap
//	所属类名 : CVerbTag
//	函数功能 : 加载动词词表文件
//	备    注 : 
//	作    者 : zhp
//	时    间 : 2005年3月9日
//	修改历史 : 
///////////////////////////////////////////////////////////////
bool CVerbTag::LoadVerbMap()
{
	FILE *fp;
	char verb[10];

	if ( (fp = fopen( (g_strDataPath+"verb.dat").c_str(), "r")) == NULL ) 
	{
		cerr<<"cannot open the file verb.dat!"<<endl;
	}
	
 	map<string, int>::iterator pos = mapVerbIdx.begin();

	for(int i = 0; i < VERB_NUM; i++)
	{
		fscanf(fp, "%s", verb);
	  	mapVerbIdx.insert(pos, make_pair(string(verb), i));
	}
 	fclose(fp); 

	return true;
}
