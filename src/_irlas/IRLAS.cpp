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
//	�� �� �� : LoadPersonSegRes
//	�������� : �����������õ���Դ
//	������� : ���������Դ�Ѿ����أ����ü��أ��������������Դ
//	��    ע : 
//	��    �� : Administrator
//	ʱ    �� : 2006��3��29��
//	�� �� ֵ : int
//	����˵�� : const char* resPathName: ��Դ·����
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
//	�� �� �� : LoadLocationSegRes
//	�������� : ���ص���ʶ����Ӧ����Դ������Ѿ����ع������ټ���
//	������� : 
//	��    ע : 
//	��    �� : Administrator
//	ʱ    �� : 2006��3��29��
//	�� �� ֵ : int
//	����˵�� : const char* resPathName
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

		return flag; //������Դ�ɹ�,��flag = 1, else flag = 0	 	
	}
	else
	{
		return 1;
	}
}

///////////////////////////////////////////////////////////////
//	�� �� �� : LoadPOSTagSegRes
//	�������� : ���ش��Ա�ע��Դ
//	������� : 
//	��    ע : 
//	��    �� : Administrator
//	ʱ    �� : 2006��3��29��
//	�� �� ֵ : int
//	����˵�� : const char* resPathName
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

