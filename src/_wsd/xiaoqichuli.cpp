   ///////////////////////////////////////////////////////////////
//	文 件 名 :xiaoqichuli.cpp
//	文件功能 :
//	作    者 : lemon
//	创建时间 : 2004年12月15日
//	项目名称 ：
//	操作系统 : 
//	备    注 :
//	历史记录:
///////////////////////////////////////////////////////////////
#include "xiaoqichuli.h"
//#include <WINDOWS.H>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include "math.h"
//#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;
//#define LAM 0.00000001

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

xiaoqichuli::xiaoqichuli()
{
//	LoadDictionary(); //加载用于进行消歧的资源
//	CreateTitleWordList();//加载第三层标题词
//	CreateWordCode();//加载词汇的索引文件
}

xiaoqichuli::~xiaoqichuli()
{
//	AfxMessageBox(" testing is over!");
}
///////////////////////////////////////////////////////////////
//	函 数 名 : CreateWordCode
//	所属类名 : xiaoqichuli
//	函数功能 : 加载词汇及编码文件
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2005年12月30日
//	返 回 值 : void
//	参数说明 : 
///////////////////////////////////////////////////////////////
void xiaoqichuli::CreateWordCode()
{
	ifstream inf( (m_strDataPath + "word_code.dat").c_str() );
	if (!inf)
	{
		printf("can't open file:word_code\n");
		exit(-1);
	}
    string line;
	int pos;
	string strIDs, strwordcode;
	while (getline(inf,line))
	{
		pos = line.find_first_of(' ',0);
		strIDs = line.substr(0,pos);
		mapwordcode[strIDs] = line.substr(pos+1);
	}
	inf.close();

}
////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
//	函 数 名 : CreateTitleWordList
//	所属类名 : xiaoqichuli
//	函数功能 : 构造词义编码（thes三层）和其对应汉语解释的映射表
//	处理过程 : 
//	备    注 : 映射表存储在map<string, string> mapIDs_Explain中，
//				mapIDs_Explain;为类xiaoqichuli的一个私有成员。
//	作    者 : yxc
//	时    间 : 2004年12月15日
//	返 回 值 : void
//	参数说明 : void
///////////////////////////////////////////////////////////////
void xiaoqichuli::CreateTitleWordList()
{
	ifstream inf( (m_strDataPath + "Title_third.txt").c_str() );
	if (!inf)
	{
		printf("can't open file:Title\n");
		exit(-1);
	}

	string strIDs, strExplain;
	while (inf >> strIDs >> strExplain)
	{
		mapIDs_Explain[strIDs] = strExplain;
	}
	inf.close();
}

///////////////////////////////////////////////////////////////
//	函 数 名 : LoadDictionary
//	所属类名 : xiaoqichuli
//	函数功能 : 加载词典的资源
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月21日
//	返 回 值 : void
//	参数说明 : 
///////////////////////////////////////////////////////////////
void xiaoqichuli::LoadDictionary()
{
	string line;
	string word;
	string change;
	wordPsk subtemp;
	vector<wordPsk> vecpsk;
	int pos;
	hashtable.InitHashTable(88638);

	FILE *finPsk;
	finPsk = fopen( (m_strDataPath+"worddictionary.txt").c_str(), "rb");
	if (finPsk == NULL)
	{
		printf("Error opening file:worddictionary.txt.----yyn\n");
		exit(-1);
	}

	wordID wordid;
	while (!feof(finPsk))
	{
		fread((void *)&wordid, sizeof(wordID), 1, finPsk);
		fread((void *)&pos, sizeof(int), 1, finPsk);
		
		
		for(int i= 0; i < pos; i++)
		{
           fread((void *)&subtemp, sizeof(wordPsk), 1, finPsk);
		   vecpsk.push_back(subtemp);
		}
        hashtable.SetAt(wordid.word,wordid.IDw,vecpsk);//一项放于hash表中
		vecpsk.clear();	
	}

	/*
	while(getline(infile,line))
	{
		pos = 0;
		pos1 = line.find_first_of(' ',0);
		word = line.substr(0,pos1);
		IDw = atoi(line.substr(pos1+1,line.size() - pos1 - 1).c_str());
		getline(infile,line);

		while(line != "\r")
        {
			pos = line.find_first_of(' ',0);
			subtemp.IDs = line.substr(0,pos);
			
			pos = pos + 1;
			pos1 = line.find_first_of(' ', pos);
			subtemp.Psk = atof(line.substr(pos, pos1 - pos).c_str());
			
			pos = pos1 + 1;
			pos1 = line.find_first_of(' ', pos);
			subtemp.P_LAM = atof(line.substr(pos, pos1 - pos).c_str());
			
			pos = pos1 + 1;
			pos1 = line.find_first_of(' ', pos);
			subtemp.begin = atol(line.substr(pos, pos1 - pos).c_str());
			
			pos = pos1 + 1;
			subtemp.end = atol(line.substr(pos).c_str());
			vecpsk.push_back(subtemp);

			getline(infile,line);
        }
		
	
		hashtable.SetAt(word.c_str(),IDw,vecpsk);
		vecpsk.clear();
		
	}
	*/
}
///////////////////////////////////////////////////////////////
//	函 数 名 : Release
//	所属类名 : xiaoqichuli
//	函数功能 : 
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年6月21日
//	返 回 值 : void
//	参数说明 : 
///////////////////////////////////////////////////////////////
void xiaoqichuli::Release()
{
	hashtable.RemoveAll();
	vectIDTmp.clear();       
	vectWordTmp.clear();     
	vectSore.clear();
	vectSore_T.clear();	
	mapIDs_Explain.clear();
	mapwordcode.clear();	
}

///////////////////////////////////////////////////////////////
//	函 数 名 : ReadCorpus
//	所属类名 : xiaoqichuli
//	函数功能 : xiaoqichuli类的对外接口,输入经分词和词性标注的句子
//				输出3个结果，分别存储在strOutNum、strOutExplain和strcode中。
//				strOutNum:为消歧结果，使用的是词义编码
//				strOutExplain:为编码的直观解释
//                              strcode：词汇的所有编码列举
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月22日
//	返 回 值 : void
//	参数说明 : string strSentenceTagger,
//				          string &strOutNum,
//				          string &strOutExplain
//                        string &strcode
///////////////////////////////////////////////////////////////
void xiaoqichuli::ReadCorpus(const string strSentenceTagger,
							 string &strOutNum,
							 string &strOutExplain,
							 string &strCode)
{
	strOutNum = "";
	strOutExplain = "";
	strCode = "";

	if (strSentenceTagger.empty())//输入的句子为空的时候
		
	{
		strOutNum = "";
		strOutExplain = "";
		strCode = "";
		return;
	}
	

	word_Tmp wordTmp;
    string yyn;
	int m_count = 0;
	int  m_pointer   = 0;
	int  m_WordBegin = 0;
	int  m_PartEnd   = 0;
	map<string , string >::iterator iter;
	

    	//处理待标注的句子
	while((m_pointer = strSentenceTagger.find(" ", m_WordBegin)) != -1)
	{   
		yyn = strSentenceTagger.substr(m_WordBegin, m_pointer - m_WordBegin);

		m_PartEnd = yyn.rfind("/", yyn.size());
		if(m_PartEnd >= 0)
		{						
			wordTmp.word = yyn.substr(0, m_PartEnd);
			iter = mapwordcode.find(wordTmp.word);
			if(iter!=mapwordcode.end())
			{
				strCode = strCode + (*iter).second + "#";
			}
			else
			{
				strCode = strCode + "-1#";
			}
			vectWordTmp.push_back(wordTmp); 
		}					
		
		m_WordBegin = m_pointer + 1;	
	}
	if((unsigned)m_WordBegin < strSentenceTagger.size())
	{
		m_PartEnd = strSentenceTagger.rfind("/", strSentenceTagger.size());
		if(m_PartEnd != -1)
		{
			wordTmp.word = strSentenceTagger.substr(m_WordBegin, m_PartEnd - m_WordBegin);
			iter = mapwordcode.find(wordTmp.word);
			if(iter!=mapwordcode.end())
			{
				strCode = strCode + (*iter).second + "#";
			}
			else
			{
				strCode = strCode + "-1#";
			}
			vectWordTmp.push_back(wordTmp); 		 
		}
		
	}


    /*
 	while((m_pointer = strSentenceTagger.find("/", m_WordBegin)) != -1)
	{ 
		if(strSentenceTagger.size() > m_pointer + 1)
		{
			if(strSentenceTagger[m_pointer + 1] == '/')
			{
				wordTmp.word = strSentenceTagger.substr(m_WordBegin, m_pointer + 1 - m_WordBegin);
				
				iter = mapwordcode.find(wordTmp.word);
				if(iter!=mapwordcode.end())
				{
					strCode = strCode + (*iter).second + "#";
				}
				else
				{
					strCode = strCode + "-1#";
				}
				
				vectWordTmp.push_back(wordTmp);
				
			}
			else
			{
				if(m_pointer >= m_WordBegin + 1)//处理非空串
				{						
					wordTmp.word = strSentenceTagger.substr(m_WordBegin, m_pointer - m_WordBegin);
					
					iter = mapwordcode.find(wordTmp.word);
					if(iter!=mapwordcode.end())
					{
						strCode = strCode + (*iter).second + "#";
					}
					else
					{
						strCode = strCode + "-1#";
					}
					
					vectWordTmp.push_back(wordTmp); 
				}
				else
				{
					if(m_pointer == m_WordBegin)//处理空串
					{
						strCode = strCode + "-1#";
						wordTmp.word = "";
						
						vectWordTmp.push_back(wordTmp);
						
					}
					
				}
				
			}
		}
		else
		{	
			wordTmp.word = strSentenceTagger.substr(m_WordBegin, m_pointer  - m_WordBegin);
			
			vectWordTmp.push_back(wordTmp);
			strCode = strCode + "-1#";
		}
		
		
		if((m_PartEnd = strSentenceTagger.find(" ", m_pointer)) != string::npos)
		{
             m_WordBegin = m_PartEnd + 1;
		}
		else
		{
			break;
		}
	}
	*/

	SearchIDw();
	CountSore(strOutNum, strOutExplain);				
}

///////////////////////////////////////////////////////////////
//	函 数 名 : SearchIDw
//	所属类名 : xiaoqichuli
//	函数功能 : 为每一个待处理的词汇，找到对应的id号
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月24日
//	返 回 值 : void
//	参数说明 : 
///////////////////////////////////////////////////////////////
void xiaoqichuli::SearchIDw()
{
	string word;
	int IDTmp;   //临时IDw
	int i = 0;
	UINT nHash;
	
	for(i; i <= vectWordTmp.size() - 1; i++)
	{
		word = vectWordTmp[i].word;
		if(word == "")
		{
           IDTmp     = -1; 
		   vectIDTmp.push_back(IDTmp);
		   continue;
		}
		
		int nResult = hashtable.GetPosition(word.c_str(), nHash);
		if(nResult == FAIL)
		{
			IDTmp     = -1; 
		}
		else
		{
			ITEM* pItem = hashtable.Lookup(nHash);
			
			while(pItem != NULL && strcmp(pItem->key,word.c_str()) != 0)
				pItem = pItem->pNext; //冲突时，沿着链表依次查找
			if(pItem != NULL)
			{
				IDTmp = pItem->property;
			}
			else
			{
                IDTmp     = -1; 
			}
			
		}
		
		vectIDTmp.push_back(IDTmp);         //每句的词汇IDw压入临时表
	}
}
///////////////////////////////////////////////////////////////
//	函 数 名 : _ReadPvs
//	所属类名 : xiaoqichuli
//	函数功能 : 获得共现词汇的信息
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月24日
//	返 回 值 : void
//	参数说明 : vector<wordPsk> ::iterator pIt,
//				vector<wordPvs>& temp，返回信息
///////////////////////////////////////////////////////////////
void xiaoqichuli::_ReadPvs(vector<wordPsk> ::iterator pIt,vector<wordPvs>& temp)
{
	temp.clear();
	wordPvs Els;
	wordPvs PvsTmp;
	int i = 0;
	int j = (pIt->end - pIt->begin)/sizeof(wordPvs);
	fstream finPvs( (m_strDataPath+"Pvs-hebing").c_str(), ios::in|ios::binary);
	if(!finPvs)
	{
		cout << "pvs-hebing is not existing;"<<endl;
		return;
	}
	finPvs.seekg(pIt->begin);
	for(i; i < j; i++)
	{		
		finPvs.read((char *) & Els,sizeof(wordPvs));
		PvsTmp.IDw = Els.IDw;
		PvsTmp.Pvs = Els.Pvs;
		temp.push_back(PvsTmp);
	}
}


///////////////////////////////////////////////////////////////
//	函 数 名 : CountPvs
//	所属类名 : xiaoqichuli
//	函数功能 : 计算带消歧词汇每一个词义的分值
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月24日
//	返 回 值 : void
//	参数说明 : int i, 定位到消歧词汇的具体位置
//				 vector<wordPvs> vectPvsTmp,
//				 vector<wordPsk> ::iterator pIt
///////////////////////////////////////////////////////////////
void xiaoqichuli::CountPvs(int i, vector<wordPvs> vectPvsTmp, vector<wordPsk> ::iterator pIt)
{
	vector<int>    vectConID;
	pair<double,string>   SoreTmp;
	SoreTmp.first = 0;
	SoreTmp.second = pIt->IDs;
	vectConID = vectIDTmp;    //上下文共现词汇；
	
	vectConID.erase(vectConID.begin() + i);       //确定上下文的IDw,其中除掉了消歧词的id，并放入向量中
	int n = 0, m = vectConID.size();
	int count = 1;

	if(count ==0)
	{
		SoreTmp.first = log(pIt->Psk);
		vectSore.push_back(SoreTmp);                         //将Sore值计入表中
	}
	else
	{
	    int k;
		for(k = 0; k < m; k++ )
		{
           int id = vectConID[k];
		   vector< wordPvs >::iterator iter = vectPvsTmp.begin(), iter_end = vectPvsTmp.end();
		   while(iter != iter_end)
		   {
			   if(iter->IDw == id)
			   {
				   SoreTmp.first += log(iter->Pvs);
				   break;
			   }
			   iter++;
		   }
		   if(iter == iter_end)
		   {
			   SoreTmp.first += log(pIt->P_LAM);
		   }
		}
		
		SoreTmp.first += log(pIt->Psk);                            //乘上Psk并取对数
		vectSore_T.push_back(SoreTmp);                             //将Score值计入表中
		SoreTmp.first = log(pIt->Psk);          
		vectSore.push_back(SoreTmp);                               //只考虑发射概率的Score              
		
	} 
		

}

///////////////////////////////////////////////////////////////
//	函 数 名 : CountSore
//	所属类名 : xiaoqichuli
//	函数功能 : 消歧
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2005年12月22日
//	返 回 值 : void
//	参数说明 : string &strOutNum，返回消歧结果
//                 string &strOutExplain,词义的直观解释
///////////////////////////////////////////////////////////////
void xiaoqichuli::CountSore(string &strOutNum, string &strOutExplain)
{
	vector<wordPvs> vectWordPvsTmp;
	// wordPsk ToSearch;
	string temp;
	UINT nHash;
	int n_count = 0;
	vector<wordPsk>::iterator pIt;

	int i =0;
	int j =vectWordTmp.size();
	for(i; i < j; i++)                  //计算每个词汇的IDs
	{		
		if(vectIDTmp[i] == -1)          //IDw = -1 的词汇是在表中找不到的
		{
			vectWordTmp[i].IDs = "-1";
		}
		else                            //对多义词进行消岐
		{
			temp = vectWordTmp[i].word;
			if (hashtable.GetPosition(temp.c_str(), nHash) == 1)
			{
				ITEM* pItem = hashtable.Lookup(nHash);
				if(pItem == NULL)
				{
					vectWordTmp[i].IDs = "-1";
				}
				while(pItem != NULL && strcmp(pItem->key,temp.c_str()) != 0)
					pItem = pItem->pNext; //冲突时，沿着链表依次查找
				
				if(pItem == NULL)//not in map
				{
					vectWordTmp[i].IDs = "-1";
				}
				else//found
				{  
                     if(pItem->psk.size() == 1)//没有歧义
					 {
						 vectWordTmp[i].IDs = pItem->psk[0].IDs;
					 }
					 else//有歧义
					 {
						 for(pIt = pItem->psk.begin() ; pIt != pItem->psk.end(); pIt++)
					    {
							_ReadPvs(pIt,vectWordPvsTmp);
							CountPvs(i, vectWordPvsTmp, pIt);
							vectWordPvsTmp.clear();
						 }
                         if(vectSore_T.size() >0)
						{
							unsigned int y = 1;
							double STmp =vectSore_T[0].first;
							vectWordTmp[i].IDs =vectSore_T[0].second ;                //确定最优的IDs
							for(y; y < vectSore_T.size(); y++)                        //计算最大的Sore值，并确定最优的IDs
							{
								if(vectSore_T[y].first > STmp)
								{
									STmp = vectSore_T[y].first;
									vectWordTmp[i].IDs =vectSore_T[y].second ;        //确定最优的IDs
								}
							}

						}
						 else
						{
							unsigned int x = 0;
							double STmp =vectSore[0].first;
							vectWordTmp[i].IDs =vectSore[0].second;                    //确定最优的IDs
							for(x; x < vectSore.size(); x++)                           //计算最大的Sore值，并确定最优的IDs
							{
								if(vectSore[x].first > STmp)
								{							
									STmp = vectSore[x].first;
									vectWordTmp[i].IDs =vectSore[x].second;            //确定最优的IDs
								}
							}

						}
						 vectSore.clear();
						 vectSore_T.clear();
						 
					 }
				}
			}
			else
			{
				vectWordTmp[i].IDs = "-1";
			}

		}
	}
	
	
	unsigned int y;
	for(y=0; y < vectWordTmp.size(); y++)
	{
		 //strOutNum =strOutNum + vectWordTmp[y].word + "#" + vectWordTmp[y].IDs + " ";
		strOutNum =strOutNum + vectWordTmp[y].IDs + " ";
		if ( vectWordTmp[y].IDs != "-1")
		{
			strOutExplain = strOutExplain +  mapIDs_Explain[vectWordTmp[y].IDs] + " ";
		}
		else
		{
             strOutExplain = strOutExplain + "-1 ";
		}
	}

	//一定要清空
	vectIDTmp.clear();
	vectWordTmp.clear();
}

/////////////////////////////////////////////////////////////
//	函 数 名 : main
//	函数功能 : 测试用
//	处理过程 : 
//	备    注 : 
//	作    者 : lemon
//	时    间 : 2006年4月22日
//	返 回 值 : void
//	参数说明 : 
/////////////////////////////////////////////////////////////
/*
void main()
{
	clock_t tBegin, tEnd;
	double t;
	tBegin = clock();
	xiaoqichuli CWsd;
	tEnd = clock();
	t = (double)(tEnd-tBegin)/CLK_TCK;
	cout << t << endl;
	
	string str, str2, str3;
	
	ifstream inf("testspeed1.txt");
	if (!inf)
	{
		cerr << " can not open the file!" << endl;
		exit(-1);
	}
	
	
	vector<string> vecText;
	while (getline(inf, str))
	{
		vecText.push_back(str);
	}
	tEnd = clock();
	t = (double)(tEnd-tBegin)/CLK_TCK;
	cout << t << endl;
	
	vector<string>::iterator iterBegin, iterEnd;
	iterBegin = vecText.begin();
	iterEnd = vecText.end();
	for (; iterBegin != iterEnd; iterBegin++)
	{
		str = *iterBegin;
		CWsd.ReadCorpus(str, str2, str3);
	}
	
	tEnd = clock();
	t = (double)(tEnd-tBegin)/CLK_TCK;
	cout << t << endl;
	
	inf.close();
}
*/
