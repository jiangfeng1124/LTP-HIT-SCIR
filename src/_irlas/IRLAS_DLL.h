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

//���������ļ�������Դ
IRLAS_DLL_API int IRLAS_LoadResource(const char *configFileName = "IRLAS_config.ini", const char *resPathName = "data/");
//��̬���÷ִ�����ѡ��
IRLAS_DLL_API void IRLAS_SetOption(void* pSegger, int isPER, int isLOC, int isPOS);
//�ͷŷִ�������Դ
IRLAS_DLL_API void IRLAS_ReleaseResource();
//����һ���ʷ�������ָ��
IRLAS_DLL_API void* IRLAS_CreateSegger();
//�ͷ�ָ��ʷ���������ָ��
IRLAS_DLL_API void IRLAS_ReleaseSegger(void* pSegger);
//�ִʵ�dll�ӿ�
IRLAS_DLL_API void IRLAS_WordSegment_dll(void* pSegger, char* str, char** pWord, int& wordNum);

#endif


