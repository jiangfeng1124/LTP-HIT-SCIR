// AugPronTag.h: interface for the AugPronTag class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _AUG_PRON_TAG_
#define _AUG_PRON_TAG_

#define STL_USING_ALL
#include "stl.h"
using namespace std;

extern string g_strDataPath;

class AugPronTag  
{
public:
	AugPronTag();
	virtual ~AugPronTag();

	void Initialize();
	void Release();
	void TagAug(string& strSent);
	void TagPron(string& strSent);

private:

	map < string, string > mapAug;
	map < string, string > mapPron;
};

#endif
