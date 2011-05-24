#ifndef __SVMTAGGER_DLL_H__
#define __SVMTAGGER_DLL_H__


#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#ifdef _WIN32	// use DLL API
	#ifdef SVMTAGGER_DLL_API_EXPORT
		#define SVMTAGGER_DLL_API extern "C" _declspec(dllexport) 
	#else
		#define SVMTAGGER_DLL_API extern "C" _declspec(dllimport)
		#pragma comment(lib, "_svmtagger.lib")
	#endif
#else
	#define SVMTAGGER_DLL_API
#endif

//���������ļ�������Դ
SVMTAGGER_DLL_API int svmtagger_LoadResource(const char *szResPath);
//�ͷŷִ�������Դ
SVMTAGGER_DLL_API int svmtagger_ReleaseResource();
//���Ա�ע��DLL�ӿ�
SVMTAGGER_DLL_API int svmtagger_PosTag(const char **szWordsArr, char**pword,int nWordNum);

int svmtagger_PosTag(const vector<string> &vecWord, vector<string> &vecPOS);

#endif