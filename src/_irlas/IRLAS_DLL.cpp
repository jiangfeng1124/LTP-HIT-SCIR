#define IRLAS_DLL_API_EXPORT
#include "IRLAS_DLL.h"
#include "IRLAS.h"

static bool g_isLoadSegRes = false;
Bigram* pBigram		=	NULL;
Dictionary* pDict	=	NULL;
HMM* pHmm[3]		=	{ NULL, NULL, NULL };

// some flags, for configuration
int isNumTime		=	1;
int isPerson		=	1;
int isLocation		=	1;
int isPOSTag		=	0;
int isExtendedDict	=	1;
int isBigram		=	0;
int  bestPathNum	=	1;

/////////////////////////////////////////////////////////////////////////////////////
/// read the configuration file and set the flags.
/////////////////////////////////////////////////////////////////////////////////////
int ReadConfigFile(const char *configFileName)
{
	ifstream in(configFileName);
	if (!in)
	{
		cerr << "can't open the file " << configFileName << endl;
		return 0;
	}
	
	string line;
	while (getline(in, line))
	{
		string item = line.substr(0, line.find("="));
		if (item == "NumTime")
		{
			if (line.find("1") != string::npos) isNumTime = 1;
		}
		else if (item == "Person")
		{
			if (line.find("1") != string::npos) isPerson = 1;
		}
		else if (item == "Location")
		{
			if (line.find("1") != string::npos) isLocation = 1;
		}
		else if (item == "POSTag")
		{
			if (line.find("1") != string::npos) isPOSTag = 1;
		}
		else if (item == "ExtendedDict")
		{
			if (line.find("1") != string::npos) isExtendedDict = 1;
		}
		else if (item == "Bigram")
		{
			if (line.find("1") != string::npos) isBigram = 1;
		}
		else if (item == "BestPathNum")
		{
			string::size_type pos = line.find_first_not_of(' ', line.find("=")+1);
			bestPathNum = atoi(&line[pos]);
		}
	}

	in.close();

	return 1;
}


///////////////////////////////////////////////////////////////
//	函 数 名 : SetOption
//	函数功能 : 为每个词法分析器对象设定识别选项
//	处理过程 : 
//	备    注 : 
//	作    者 : taozi
//	时    间 : 2006年3月31日
//	返 回 值 : void
//	参数说明 : void* pSegger,
//				 int isPER,
//				 int isLOC,
//				 int isPOS
///////////////////////////////////////////////////////////////
void IRLAS_SetOption(void* pSegger, int isPER, int isLOC, int isPOS)
{
	CIRLAS* irlas = (CIRLAS*)pSegger;
	isPerson = isPER;
	isLocation = isLOC;
	isPOSTag = isPOS;
	irlas->SetOptionNum(isPER, isLOC, isPOS);
}
/////////////////////////////////////////////////////////////////////////////////////
/// dll interface function, initialize the resource classes according to the flags.
/////////////////////////////////////////////////////////////////////////////////////
int IRLAS_LoadResource(const char *configFileName, const char *resPathName)
{
//	printf("LoadSegRes... Enter Key...\n");
//	_getch();
	if (g_isLoadSegRes) return 1;
	if (!ReadConfigFile((string(resPathName) +"/" + configFileName).c_str() ) )
	{
		return 0;
	}
	
	int flagDic = 1;
	int flagBig = 1;
	pDict = new Dictionary(isExtendedDict, resPathName, flagDic);
	pBigram = new Bigram(isBigram, resPathName, flagBig);

	if (flagDic==0 || flagBig==0)
	{
		return 0;
	}

	if (isPerson)
	{
		if (!LoadPersonSegRes(resPathName))
			return 0;
	}

	if (isLocation)
	{
		if (!LoadLocationSegRes(resPathName))
			return 0;
	}

	if (isPOSTag)
	{
		if (!LoadPOSTagSegRes(resPathName))
			return 0;
	}
	
	g_isLoadSegRes = true;
	return 1;
}


/////////////////////////////////////////////////////////////////////////////////////
/// dll interface function, release the resources.
/////////////////////////////////////////////////////////////////////////////////////
void IRLAS_ReleaseResource()
{
	//cout << "ReleaseSegRes" << endl;
	if (pDict) {
		pDict->releaseMemory();
		delete pDict;
	//	cout << "pDict" << endl;
		pDict = 0;
	}
	if (pBigram) {
		delete pBigram;
		pDict = 0;
	//	cout << "pBigram" << endl;
	}

	for (int i = 0; i < 3; i++)
	{
		if (pHmm[i])
		{
			delete pHmm[i];
			pHmm[i] = 0;
	//		cout << i << " : pHmm" << endl;
		}
	}

	g_isLoadSegRes = false;
}

/////////////////////////////////////////////////////////////////////////////////////
/// dll interface function, create a segger. 
/// create a object of the class IRLAS, then return the pointer to this segger.
/////////////////////////////////////////////////////////////////////////////////////
void* IRLAS_CreateSegger()
{
	return new CIRLAS(pBigram, pDict);
}

/////////////////////////////////////////////////////////////////////////////////////
/// dll interface function, delete the segger.
/////////////////////////////////////////////////////////////////////////////////////
void IRLAS_ReleaseSegger(void* pSegger)
{
	if (pSegger) {
		delete (CIRLAS*)pSegger;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// word segmentation, the core function of IRLAS.
/// why not use this function as the dll interface?
/// because the parameters are in C++ style and don't work in dll.
/////////////////////////////////////////////////////////////////////////////////////
void WordSegment(void* pSegger, string& line, vector<string>& vecWords)
{
	if (line.empty()) return;
	CIRLAS* irlas = (CIRLAS*)pSegger;
	vector<string> wordSequence;
	vector<string> tagSequence;
	irlas->segger.BasicSegment(line, irlas->graph);
	
	if (isNumTime) 
	{
		irlas->numtime.NumTimeRecg(irlas->segger.vecAtoms, irlas->graph);
	}
	
	if ((isPerson && irlas->isPerson) || (isLocation && irlas->isLocation))
	{
		irlas->graph.GenerateNBestPath(bestPathNum); 
		irlas->segger.AddAtomPath(irlas->graph);
	}
	
	if (isPerson && irlas->isPerson)
	{
		irlas->person.PersonRecg(irlas->graph, irlas->segger.vecAtoms);
	}
	
	if (isLocation && irlas->isLocation)
	{
		irlas->location.LocationRecg(irlas->graph, irlas->segger.vecAtoms);
	}
	irlas->graph.GenerateNBestPath(1);	//best path
	irlas->segger.GenerateBestWordSequence(irlas->graph, wordSequence);
	
	if (isPOSTag && irlas->isPOSTag)
	{
		irlas->postag.POSTagging(irlas->graph, tagSequence); 
		for (unsigned int i = 0; i < wordSequence.size(); i++)
		{
			if (wordSequence[i].find_first_not_of(" \t\n") != string::npos)//ignore white
				vecWords.push_back(wordSequence[i]+"/"+tagSequence[i]);
		}
	}
	else
	{
		vecWords = wordSequence;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/// dll interface function, it calls the function WordSegment.
/////////////////////////////////////////////////////////////////////////////////////
void IRLAS_WordSegment_dll(void* pSegger, char* str, char** pWord, int& wordNum)
{
	string line = str;
	vector<string> vecWords;
	WordSegment(pSegger, line, vecWords);
	wordNum = vecWords.size();
	for (int i = 0; i < wordNum; i++)
	{
		strcpy(pWord[i], vecWords[i].c_str());
		pWord[i][vecWords[i].size()] = '\0';
	}
}



