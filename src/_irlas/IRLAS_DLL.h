#ifndef __IRLAS_DLL_H__
#define __IRLAS_DLL_H__

//#define STL_USING_ALL
//#include <STL.h>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

#define IRLAS_DLL_API

#ifdef _WIN32
	#undef IRLAS_DLL_API
	#ifdef IRLAS_DLL_API_EXPORT
		#define IRLAS_DLL_API extern "C" _declspec(dllexport)
	#else
		#define IRLAS_DLL_API extern "C" _declspec(dllimport)
		#pragma comment(lib, "_irlas.lib")
	#endif
#endif

void IRLAS(void* pSegger, string& line, vector<string>& vecWords);

//根据配置文件加载资源
IRLAS_DLL_API int IRLAS_LoadResource(const char *configFileName = "IRLAS_config.ini", const char *resPathName = "data/");
//动态设置分词器的选项
IRLAS_DLL_API void IRLAS_SetOption(void* pSegger, int isPER, int isLOC, int isPOS);
//释放分词器的资源
IRLAS_DLL_API void IRLAS_ReleaseResource();
//创建一个词法分析器指针
IRLAS_DLL_API void* IRLAS_CreateSegger();
//释放指向词法分析器的指针
IRLAS_DLL_API void IRLAS_ReleaseSegger(void* pSegger);
//分词的dll接口
IRLAS_DLL_API void IRLAS_WordSegment_dll(void* pSegger, char* str, char** pWord, int& wordNum);

#endif


