#ifndef _LTP_OPTION_
#define _LTP_OPTION_
#include <string>
#include <iostream>
using namespace std;
/*
isPER���������Ƿ�ʹ������ʶ��������Ϊ1������Ϊ0�� 
isLOC���������Ƿ�ʹ�õ���ʶ��
isPOS���������Ƿ���д��Ա�ע��
��Ҫʹ����Щ�����������ļ���ѡ���������ص���Դ���С�
*/

struct tagIRLASOption{
	int isPER;
	int isLOC;
	int isPOS;
	string confFile;
	string dataFolder;

	tagIRLASOption(int aIsPER=1, int aIsLOC=1, int aIsPOS=1) : isPER(aIsPER), isLOC(aIsLOC), isPOS(aIsPOS) {}
	struct tagIRLASOption &operator=(const struct tagIRLASOption &irlasOpt)
	{
		isPER = irlasOpt.isPER;
		isLOC = irlasOpt.isLOC;
		isPOS = irlasOpt.isPOS;
		return *this;
	}
	void output()
	{
		cout << "IRLAS options: " << endl
			<< "isPER: " << isPER << endl
			<< "isLOC: " << isLOC << endl
			<< "isPOS: " << isPOS << endl
			<< "confFile: \"" << confFile << "\"" << endl;
	}
};
typedef struct tagIRLASOption IRLASOption;

struct tagNEOption{
	int isEntity;
	int isTime;
	int isNum;

	tagNEOption(int aIsEntity=1, int aIsTime=1, int aIsNum=1) : isEntity(aIsEntity), isTime(aIsTime), isNum(aIsNum) {}
	struct tagNEOption& operator=(const struct tagNEOption &neOpt)
	{
		isEntity = neOpt.isEntity;
		isTime = neOpt.isTime;
		isNum = neOpt.isNum;
		return *this;
	}

	void output()
	{
		cout << "NE options: " << endl 
			<< "isEntity: " << isEntity << endl
			<< "isTime: " << isTime << endl
			<< "isNum: " << isNum << endl;
	}
};
typedef struct tagNEOption NEOption;

struct tagLTPOption
{
	string strLTPDataPath;
	IRLASOption irlasOpt;
	NEOption neOpt;
	void output()
	{
		cout << "ltp options: " << endl
			<< "ltp data path: " << strLTPDataPath << endl;
		irlasOpt.output();
		neOpt.output();
	}
};
typedef tagLTPOption LTPOption;

#endif
