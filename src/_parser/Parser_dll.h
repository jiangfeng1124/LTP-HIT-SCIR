/////////////////////////////////////////////////////////////////////////////////////
// File Name   : Parser.h
// Project Name: 
// Author      : Ma Jinshan
// Environment : Microsoft Visual .Net
// Description : Adapt interface to XML project
// Time        : 2006.6.27
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////


#ifndef __PARSER_DLL_H__
#define __PARSER_DLL_H__

#define PARSER_DLL_API

#ifdef _WIN32 	
	#undef PARSER_DLL_API
	#ifdef PARSER_DLL_API_EXPORT
		#define PARSER_DLL_API extern "C" _declspec(dllexport) 
	#else
		#define PARSER_DLL_API extern "C" _declspec(dllimport)
	#endif
#endif

#pragma warning(disable: 4786)

#include <string>
#include <vector>
using namespace std;

int Parser(vector < string >& vecWord, vector < string >& vecPOS, vector < pair<int,string> >& vecParse);
int Parser_with_postag(vector < string >& vecWord, vector<string> &vecCPOS, vector < string >& vecPOS, vector < pair<int,string> >& vecParse);


///////////////////////////////////////////////////////////////

PARSER_DLL_API int GetParseResults( vector< string >& vecWord, vector < string >& vecPOS,char *strOutput);
PARSER_DLL_API int GetParseResults_with_postag(vector < string >& vecWord, vector<string> &vecCPOS,  vector < string >& vecPOS,char *strOutput);

// Interface
PARSER_DLL_API void Parser_LoadResource(const char *cszDataPath);
PARSER_DLL_API void Parser_ReleaseResource();

#endif