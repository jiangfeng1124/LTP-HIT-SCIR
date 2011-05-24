 // supervisedWSD.cpp : Defines the initialization routines for the DLL.
//
#define WSD_DLL_API_EXPORT
#include "WSD_dll.h"
#include "xiaoqichuli.h"
#include <string.h>
#include <iostream>
using namespace std;

xiaoqichuli tb;

void WSD_LoadResource(const char *cszDataPath)
{
	tb.SetDataPath(cszDataPath);
	cout << "SetDataPath over" << endl;
	tb.LoadDictionary(); //�������ڽ����������Դ
	cout << "LoadDictionary over" << endl;
	tb.CreateTitleWordList();//���ص���������
	cout << "CreateTitleWord over" << endl;
	tb.CreateWordCode();//���شʻ�������ļ�
	cout << "CreateWordCode over" << endl;
}

void WSD_GetResults(const string & strInput, char* chOutput, char* strexplain, char* strcode)
{
	string temp;
	string output;
	string wordcode;//wordcode����ͬһ���ʻ�ı�����ÿո��������ͬ�ʻ���÷ֺŸ�����
    
	tb.ReadCorpus(strInput,output,temp,wordcode);//���紦�����

	strcpy(chOutput,output.c_str());
	strcpy(strexplain,temp.c_str());
	strcpy(strcode,wordcode.c_str());

}

void WSD_ReleaseResource()
{
	tb.Release();
}
