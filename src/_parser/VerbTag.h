///////////////////////////////////////////////////////////////
//	�� �� �� : VerbTag.h
//	�ļ����� : ����ϸ����ϵͳ���������
//	��    �� : zhp
//	����ʱ�� : 2005��3��9��
//	��    ע : �Էִʴ��Ա�ע�Ľ���еĶ��ʽ���ϸ���࣬��������
//             8�ද�ʣ�����HMMģ�ͣ�ģ���е�״̬��8�ද�ʣ�ͬ
//             ʱ�����˶��������������������֮���ת�Ƹ���
//	��ʷ��¼ : 2005��3��23�����beta���԰�
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
	int posIdx;    //���Ե�����
	float emitProb;//���Զ�Ӧ�ķ�����ʣ���ȡ�˸�������
};

struct Emit //������ʵ����ݽṹ
{
	int num;  //���Ը���
	Prob* prob; //�������
};

struct VerbWithAdjacentInfo
{
	int verbIndex; //���ʵ�����
	int posNum; //�ö��ʾ��д��Եĸ���
	int positionInSentence; //�ھ����е�λ�ã����ö����Ǿ����еĵڼ�����
	int prePosIndex; //����ǰ����Ե�������-1��ʾǰ��û����������
	int nextPosIndex; //���ʺ�����Ե�������-1��ʾ����û����������
};
typedef vector<VerbWithAdjacentInfo> VerbArray;

struct PathNode
{
	float accumProb; //����״̬�����ۼƸ��ʣ���ʼΪ������ʺ�
	//�ô�����������������֮��ת�Ƹ��ʵĳ˻�
	int preNodeSubscript; //·����ǰһ��״̬������������е��±꣬��ʼΪ-1
	int curNodePosIndex; //��ǰ״̬�����Ե�����
};

class CVerbTag
{
public:
	CVerbTag();
	~CVerbTag();
	float VerbTagging(string& inSentence, string& outSentence);
	void Initialize(); //�����ʼ�������ظ��ֲ���
	void Release();

private:
	vector< pair<string, string> > vecWordPos;//���������ӵ�ÿһ����/���Զ�
	VerbArray vecVerb;
	PathNode** nodeArray; 

	void Sentence2VerbArray(string& inSentence);
	void InitHMMStructure(string& inSentence);
	void ViterbiSearch();
	float GenerateBestPath(string& outSentence);
	void FreeMemary();

//---------------���ֲ��������ݽṹ������ز���--------------------

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
		POS_NUM = 8, //���ʴ��Եĸ��� 8, 12
		OTHERPOS_NUM = 27, //�������� 27, 34, 42
		VERB_NUM = 12205 //���ʸ���
	};

	Emit *emit;
	float *start;
	float **trans, **forwardTrans, **backwardTrans;
	string *idxPos;
	map<string, int> mapOtherposIdx; //�������Ե���������ӳ��
	map<string, int> mapVerbIdx; //���ʵ���������ӳ��
//	string idxPos[POS_NUM];
//	map<string, int> mapOtherposIdx; //�������Ե���������ӳ��
//	map<string, int> mapVerbIdx; //���ʵ���������ӳ��
//	float start[POS_NUM]; //��ʼ��������
//	float trans[POS_NUM][POS_NUM]; //ת�Ƹ��ʾ���
//	float forwardTrans[POS_NUM][OTHERPOS_NUM];
//	float backwardTrans[POS_NUM][OTHERPOS_NUM];
//	Emit emit[VERB_NUM+1]; //�±���Ǵʵ�����
//	bool initialized; //��ʶ�Ƿ��Ѿ����ز����ļ���
							 //true��ʾ�Ѽ��أ�false��ʾδ����
};
#endif
