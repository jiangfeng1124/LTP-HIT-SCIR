///////////////////////////////////////////////////////////////
//	�� �� �� : VerbTag.cpp
//	�ļ����� : ����ϸ����ϵͳ�����ʵ���ļ�
//	��    �� : zhp
//	����ʱ�� : 2005��3��9��
//	��    ע : �Էִʴ��Ա�ע�Ľ���еĶ��ʽ���ϸ���࣬��������
//             8�ද�ʣ�����HMMģ�ͣ�ģ���е�״̬��8�ද�ʣ�ͬ
//             ʱ�����˶��������������������֮���ת�Ƹ���
//	��ʷ��¼ : 2005��3��23�����beta���԰�
///////////////////////////////////////////////////////////////
#include "VerbTag.h"
#include "MyLib.h"


//���о�̬�����Ķ��壨�����Ż����ռ䣩
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
//	�� �� �� : Initialize
//	�������� : CVerbTag
//	�������� : ���ظ��ֲ����ļ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 
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
//	�� �� �� : VerbTagging
//	�������� : CVerbTag
//	�������� : ����ϸ����ϵͳ�Ľӿں���
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��21��
//	�޸���ʷ : 
///////////////////////////////////////////////////////////////
float CVerbTag::VerbTagging(string& inSentence, string& outSentence)
{
	InitHMMStructure(inSentence);
	ViterbiSearch();
	return GenerateBestPath(outSentence);
}


//////////////////////////////////////////////////////////////////////////////
//	�� �� �� : Sentence2VerbArray
//	�������� : CVerbTag
//	�������� : ��һ��������ַ���ת��ΪVerbArray�͵�����
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��19��
//  �õ������ݽṹ :
//	struct VerbWithAdjacentInfo
//	{
//		int verbIndex; //���ʵ�����
//		int posNum; //�ö��ʾ��д��Եĸ���
//		int positionInSentence; //�ھ����е�λ�ã����ö����Ǿ����еĵڼ�����
//		int prePosIndex; //����ǰ����Ե�������-1��ʾǰ��û����������
//		int nextPosIndex; //���ʺ�����Ե�������-1��ʾ����û����������
//	};
//	typedef vector<VerbWithAdjacentInfo> VerbArray;
//	�޸���ʷ : 
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
		if (vecWordPos[i].second == "v") //����Ƕ�������붯̬����vecVerb��
		{
			iter = mapVerbIdx.find(vecWordPos[i].first);
			if (iter != mapVerbIdx.end()) 
			{
				verbNode.verbIndex = iter->second;
			}
			else
			{
				//������ʱ����Ҳ����ö��ʣ���Ĭ�ϸö��ʴ���Ϊvt
				//�ļ�emit.dat���һ��Ϊ1 8 20��8��vt������
				verbNode.verbIndex = VERB_NUM; 
			}
			
			if (i > 0 && vecWordPos[i-1].second != "v")
			{
				iter = mapOtherposIdx.find(vecWordPos[i-1].second);
				if (iter != mapOtherposIdx.end()) 
				{
					verbNode.prePosIndex = iter->second;
				}
				else //�˱�ǲ���һ�����Ա��
				{
					verbNode.prePosIndex = -1;
				}
			}
			else //�˱���Ƕ���
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
				else //�˱�ǲ���һ�����Ա��
				{
					verbNode.nextPosIndex = -1;
				}
			}
			else //�˱���Ƕ���
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
//	�� �� �� : InitHMMStructure
//	�������� : CVerbTag
//	�������� : ��ʼ��HMMģ���е����ݽṹ����ά���飩
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��21��
//  �õ������ݽṹ :
//	struct PathNode
//	{
//		float accumProb; //����״̬�����ۼƸ��ʣ���ʼΪ������ʺ�
//                       //�ô�����������������֮��ת�Ƹ��ʵĳ˻�
//		int preNodeSubscript; //·����ǰһ��״̬������������е��±꣬��ʼΪ-1
//		int curNodePosIndex; //��ǰ״̬�����Ե�����
//	};
//	PathNode** nodeArray; 
//	�޸���ʷ : 
///////////////////////////////////////////////////////////////////////////////
void CVerbTag::InitHMMStructure(string& inSentence)
{
	Sentence2VerbArray(inSentence);
	int verbNum = vecVerb.size();
	nodeArray = new PathNode*[verbNum];
	//Ϊÿһ�����ʸ��ݶ��ʴ��Ը�������ռ䲢��ʼ��
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
//	�� �� �� : ViterbiSearch
//	�������� : CVerbTag
//	�������� : Viterbi����
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��21��
//	�޸���ʷ : 
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
	for (int i = 1; i < verbNum; i++) //��ÿ������
	{
		for (int j = 0; j < vecVerb[i].posNum; j++) //�Զ��ʵ�ÿ������
		{	
			curnodeEmit = nodeArray[i][j].accumProb;
			nodeArray[i][j].accumProb = INFINITE;
			for (int k = 0; k < vecVerb[i-1].posNum; k++) //��ǰһ�����ʵ�ÿһ������
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
//	�� �� �� : FreeMemary
//	�������� : CVerbTag
//	�������� : �ͷ�������ڴ�ռ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��23��
//	�޸���ʷ : 
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
//	�� �� �� : GenerateBestPath
//	�������� : CVerbTag
//	�������� : �������ŵĶ��ʱ�ע���
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��21��
//	�޸���ʷ : 2005��4��2�գ��޸�һ��bug������ if (outSentence.size() > 0) 
///////////////////////////////////////////////////////////////////////////////
float CVerbTag::GenerateBestPath(string& outSentence)
{
	const float INFINITE = 10000;
	float tempProb = INFINITE;
	int verbNum = vecVerb.size();
	int lastNodeSubscript;
	if (verbNum > 0) //��������еĶ��ʸ�����Ϊ0
	{
		//�������·�������һ��״̬���������е��±�
		for (int i = 0; i < vecVerb[verbNum-1].posNum; i++) 
		{
			if (nodeArray[verbNum-1][i].accumProb < tempProb) 
			{
				tempProb = nodeArray[verbNum-1][i].accumProb;
				lastNodeSubscript = i;
			}
		}
		deque<string> dequeBestPath;
		//�����ŵ�ÿһ�����ʱ�Ǵ浽һ��deque��
		for (int j = verbNum-1, k = lastNodeSubscript; j >= 0; j--) 
		{
			int posIdx = nodeArray[j][k].curNodePosIndex;
			dequeBestPath.push_front(idxPos[posIdx]);
			if (j-1 >= 0) 
			{
				k = nodeArray[j][k].preNodeSubscript;
			}
		}
		
		for (int l = 0; l < verbNum; l++) //��vecWordPos�е�vת����ϸ���Ķ��ʱ��
		{
			vecWordPos[vecVerb[l].positionInSentence].second = dequeBestPath[l];
		}
	}
	
	outSentence = "";
	int wordNum = vecWordPos.size();
	for (int m = 0; m < wordNum; m++) //�������ľ��ӣ�������outSentence��
	{
		outSentence += vecWordPos[m].first + "/" + vecWordPos[m].second + " ";
	}

	FreeMemary();
	return tempProb/(verbNum*2);
}


//--------------------------���ز���------------------------------

///////////////////////////////////////////////////////////////
//	�� �� �� : LoadStart
//	�������� : CVerbTag
//	�������� : ���س�ʼ�����ļ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 
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
//	�� �� �� : LoadTrans
//	�������� : CVerbTag
//	�������� : ����ת�Ƹ����ļ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 
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
//	�� �� �� : LoadEmit
//	�������� : CVerbTag
//	�������� : ���ط�������ļ�
//	��    ע : emit.dat�ļ��ĸ�ʽ��
//   3 8 20 10 20 5 20  //3�����ԣ������Ǵ��Ե���ź͸���
//   3 8 20 9 20 5 20
//   2 8 20 5 20
//   3 8 7.17104 9 6.17942 5 7.55495
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 2005��3��13�գ���ΪC�������ٶȴ�����
//             2005��3��26�գ�������delete[] buf;һ��
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
	int flag = 0;//��ʾ�����ַ����͵ı�־
	             //0:���Ը���, 1:��������, 2:���Է������
	int line = 0;//�ļ��е��кţ���emit������±�
	int pos = 0;//ָʾ�ǵڼ�������
	string temp;//�����ʱ�ַ���
	
	for(int i = 0; i < fileLength; i++)
	{
		if (flag == 0) 
		{
			if (buf[i] == 32) //����ո���������Ը���
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
			else if (buf[i] == 10) //����س���
			{
				flag = 0;
				emit[line].prob[pos].emitProb = (float)atof(temp.c_str());
				pos = 0;
				temp = "";
				line++;
			}
			else if (buf[i] != 13) //���Զ���Ļ��з�
			{
				temp += buf[i];			
			}
		}
	}
	delete[] buf;

	return true;
}

///////////////////////////////////////////////////////////////
//	�� �� �� : LoadForwardTrans
//	�������� : CVerbTag
//	�������� : ����ǰ��ת�Ƹ����ļ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 
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
//	�� �� �� : LoadBackwardTrans
//	�������� : CVerbTag
//	�������� : ���غ���ת�Ƹ����ļ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 
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
//	�� �� �� : LoadPos
//	�������� : CVerbTag
//	�������� : ���ض��ʱ���ļ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 2005��3��21�գ�����idxPos[i] = pos;һ��
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
//	�� �� �� : LoadOtherposMap
//	�������� : CVerbTag
//	�������� : �����������Ա���ļ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 
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
//	�� �� �� : LoadVerbMap
//	�������� : CVerbTag
//	�������� : ���ض��ʴʱ��ļ�
//	��    ע : 
//	��    �� : zhp
//	ʱ    �� : 2005��3��9��
//	�޸���ʷ : 
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
