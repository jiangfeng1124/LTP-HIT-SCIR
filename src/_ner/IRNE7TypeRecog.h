#ifndef __IRNE7TYPERECOG_H__
#define __IRNE7TYPERECOG_H__

#include "Model.h"
#include "MyNLPlib.h"
#include "InitDic.h"
#include "RuleNErecog.h"

//using namespace maxent;

/*
 *	ʵ��NEʶ����������̣�����������ȡ�����Ԥ�⣬��������
 */

class IRNErecog
{
public:
	IRNErecog();
	~IRNErecog();
	void setObject(InitDic *pdic, CModel* model);
	void IRNE7TypeRecog(const string& strSen, string& StrOut, int tagForm, bool* isNEtypeFlag);

private:
	struct SearchNode
	{
		int preNode;  //ǰһ���ʶ�Ӧ��nodeNum
		string NEtype;  //NE���
		double prob;  //�ۻ�����
	};
	typedef struct SearchNode SEARCHNODE; //���Ԥ�����������Ž��

	typedef vector<SEARCHNODE> SEARCHVECTOR;

	typedef pair<char, int> FEATURE;

	enum
	{
		SEARCHNODE_NUM = 5,
		TEMPLATE_NUM = 23,
		FormBracket = 1,
		FormBIESO = 2,
		FormMerge = 3
	};


private:
	void NEtaggingNormal(string& NEResult);
	void getNEResult(string& result, int tagform);
	void NEtaggingBasedOnBIOForm1(string& NEResult);
	void NEtaggingBasedOnBIOForm2(string& NEResult);
	void NEtaggingBasedOnBIOForm3(string& NEResult);
	void NEtaggingBasedOnBIESO(string& NEResult);
	//read Template file to vecTemplate
	void readTemplateFile();
	//put words into maps
	void initRuleMaps();    
	void NErecogAtCurrentPostion(int position);
	
	//get proper Word, POS or NEtag
	bool getFeature(const int vecIndex, const int listIndex, 
		const char FeatureChar, string& FeatureOut);

	//combine word, POS, NEtay, and so on, to form a feature 
	void combineOneFeature(int NENODEpos, int preNode, int FeatureNum, string& FeatureOut);
	void seachBestPath(int posVec, int preNode, const vector< pair<string, double> >& vecProb);
	void getBestNEResult();
	void dealFirstPathNode(int posVec, const vector< pair<string, double> >& vecProb);
	void dealOtherPathNode(int posVec, int preNode,
		const vector< pair<string, double> >& vecProb);
	bool isSearchNodeEmpty(int posVec, int Listsize);
	int getListNodeIndexWithSameType(const string& NEtype, int posVec);
	int getNodeIndexWithSmallProb(int posVec);
	int getNodeIndexWithHighProb(int posVec);
	void outvecList(vector<SEARCHVECTOR>& vecOut, ofstream& outfile);
	string getNEtagforHC(const string& Word);
	void cutSingleNE(vector<string>& vecNE);

	void getNEstring(int& senBegpos, int& NEBegpos, string& strOut);
	string getNEPOS(string& NEtype);

private:
	vector<SEARCHVECTOR> vecList;  //�ʵ�����
	//vector<FEATURE> vecTemplate[TEMPLATE_NUM];  //����ģ��
	CModel* Cmodel;

	InitDic* pdic;
	Ruletest ruletest;


	//MaxentModel MEmodel;
	vector<string> vecContext;  //�������
	vector< pair<string, double> > vecOutcome;  //���NEԤ�������͸�����Ϣ
	vector< pair<string, string> > vec2paSen;  //��ž��ӵ�Ԥ������
	vector<string> vecNEResult;


	map<string, int> map_Niend;
	map<string, int> map_Nsend;
	map<string, int> map_Nzend;
	map<string, int> map_sufNh;
	map<string, int> map_preNh;

	bool* bIsNEtypeFlag;


	/*
	 *	����for debug
	 */
	//ofstream temp; //for debug
	//ofstream tempProb;
	//ofstream srcProb;
};


#endif
















