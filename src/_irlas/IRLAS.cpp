/////////////////////////////////////////////////////////////////////////////////////
// File Name   : IRLAS.CPP
// Project Name: IRSEG
// Author      : Paul Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : the interface functions of the project IRLAS
// Time        : 2005.7
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#include "IRLAS.h"
//#include <conio.h>


extern HMM* pHmm[3];

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadPersonSegRes
//	函数功能 : 加载人名所用的资源
//	处理过程 : 如果人名资源已经加载，则不用加载，否则加载人名资源
//	备    注 : 
//	作    者 : Administrator
//	时    间 : 2006年3月29日
//	返 回 值 : int
//	参数说明 : const char* resPathName: 资源路径名
///////////////////////////////////////////////////////////////
int LoadPersonSegRes(const char* resPathName)
{
	string pathName(resPathName);

	if (pHmm[0] == NULL)
	{
		pHmm[0] = new HMM();
		int flag = pHmm[0]->loadHMMSeg(
			(pathName+"/person_emit.dat").c_str(), 
			(pathName+"/person_trans.dat").c_str(), 
			(pathName+"/person_roles.dat").c_str(), 17);
		
		return flag;
	}
	else
	{
		return 1;
	}
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadLocationSegRes
//	函数功能 : 加载地名识别相应的资源，如果已经加载过，则不再加载
//	处理过程 : 
//	备    注 : 
//	作    者 : Administrator
//	时    间 : 2006年3月29日
//	返 回 值 : int
//	参数说明 : const char* resPathName
///////////////////////////////////////////////////////////////
int LoadLocationSegRes(const char* resPathName)
{
	string pathName(resPathName);
	
	if (pHmm[1] == NULL)
	{
		pHmm[1] = new HMM();
		int flag = pHmm[1]->loadHMMSeg(
			(pathName+"/location_emit.dat").c_str(), 
			(pathName+"/location_trans.dat").c_str(), 
			(pathName+"/location_roles.dat").c_str(), 10);

		return flag; //加载资源成功,则flag = 1, else flag = 0	 	
	}
	else
	{
		return 1;
	}
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadPOSTagSegRes
//	函数功能 : 加载词性标注资源
//	处理过程 : 
//	备    注 : 
//	作    者 : Administrator
//	时    间 : 2006年3月29日
//	返 回 值 : int
//	参数说明 : const char* resPathName
///////////////////////////////////////////////////////////////
int LoadPOSTagSegRes(const char* resPathName)
{
	string pathName(resPathName);

	if (pHmm[2] == NULL)
	{
		pHmm[2] = new HMM();
		int flag = pHmm[2]->loadHMMSeg(
			(pathName+"/postag_emit.dat").c_str(), 
			(pathName+"/postag_trans.dat").c_str(), 
			(pathName+"/postag_tags.dat").c_str(), 28);
		
		return flag;
	}
	else
	{
		return 1;
	}
}

