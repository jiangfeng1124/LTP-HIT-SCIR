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
	tb.LoadDictionary(); //加载用于进行消歧的资源
	cout << "LoadDictionary over" << endl;
	tb.CreateTitleWordList();//加载第三层标题词
	cout << "CreateTitleWord over" << endl;
	tb.CreateWordCode();//加载词汇的索引文件
	cout << "CreateWordCode over" << endl;
}

void WSD_GetResults(const string & strInput, char* chOutput, char* strexplain, char* strcode)
{
	string temp;
	string output;
	string wordcode;//wordcode采用同一个词汇的编码采用空格隔开，不同词汇的用分号隔开；
    
	tb.ReadCorpus(strInput,output,temp,wordcode);//消歧处理过程

	strcpy(chOutput,output.c_str());
	strcpy(strexplain,temp.c_str());
	strcpy(strcode,wordcode.c_str());

}

void WSD_ReleaseResource()
{
	tb.Release();
}
