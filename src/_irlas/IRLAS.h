/////////////////////////////////////////////////////////////////////////////////////
// File Name   : IRLAS.H
// Project Name: IRLAS
// Author      : Huipeng Zhang (zhp@ir.hit.edu.cn)
// Environment : Microsoft Visual C++ 6.0
// Description : 
// Time        : 2005.7
// History     : 
// CopyRight   : HIT-IRLab (c) 2001-2005, all rights reserved.
/////////////////////////////////////////////////////////////////////////////////////
#ifndef _IRLAS_H_
#define _IRLAS_H_
#include "Segment.h"
#include "NumTime.h"
#include "Person.h"
#include "Location.h"
#include "POSTag.h"

/////////////////////////////////////////////////////////////////////////////////////
/// this class is a wrapper of the classes that don't hold data resources.
/////////////////////////////////////////////////////////////////////////////////////
class CIRLAS
{
public:
    CIRLAS(Bigram* pBigram, Dictionary* pDict)	
		: graph(pBigram),segger(pDict)
	{
		isPerson		=	0;
		isLocation		=	0;
		isPOSTag		=	0;
	}

    void SetOptionNum(int isPER, int isLOC, int isPOS)
	{
		isPerson = isPER;
		isLocation = isLOC;
		isPOSTag = isPOS;
	}

public:
	Graph graph;
	Segment segger;
	NumTime numtime;
	Person person;
	Location location;
	POSTag postag;

public:
	int isPerson;
	int isLocation;
	int isPOSTag;
};

//加载人名资源
int LoadPersonSegRes(const char* resPathName = "data/");
//加载地名资源
int LoadLocationSegRes(const char* resPathName = "data/");
//加载词性标注资源
int LoadPOSTagSegRes(const char* resPathName = "data/");


#endif


