#ifndef WSDMODEL_H
#define WSDMODEL_H

#include <vector>
#include <string>
using namespace std;

#define WSD_DLL_API

#ifdef _WIN32
	#undef WSD_DLL_API
	#ifdef WSD_DLL_API_EXPORT
		#define WSD_DLL_API extern "C" _declspec(dllexport)
	#else
		#define WSD_DLL_API extern "C" _declspec(dllimport)
		#pragma comment(lib, "_wsd.lib")
	#endif
#endif


WSD_DLL_API void WSD_LoadResource(const char *cszDataPath);
WSD_DLL_API void WSD_GetResults(const string & strInput, char* chOutput, char* strexplain, char* strcode);
WSD_DLL_API void WSD_ReleaseResource();

bool WSD(vector< string >& input , vector< string > &output , vector<string> &strexplain, vector< vector<string> > & strcode);

#endif