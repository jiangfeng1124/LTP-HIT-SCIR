   ///////////////////////////////////////////////////////////////
//	�� �� �� :xiaoqichuli.cpp
//	�ļ����� :
//	��    �� : lemon
//	����ʱ�� : 2004��12��15��
//	��Ŀ���� ��
//	����ϵͳ : 
//	��    ע :
//	��ʷ��¼:
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
//	LoadDictionary(); //�������ڽ����������Դ
//	CreateTitleWordList();//���ص���������
//	CreateWordCode();//���شʻ�������ļ�
}

xiaoqichuli::~xiaoqichuli()
{
//	AfxMessageBox(" testing is over!");
}
///////////////////////////////////////////////////////////////
//	�� �� �� : CreateWordCode
//	�������� : xiaoqichuli
//	�������� : ���شʻ㼰�����ļ�
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2005��12��30��
//	�� �� ֵ : void
//	����˵�� : 
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
//	�� �� �� : CreateTitleWordList
//	�������� : xiaoqichuli
//	�������� : ���������루thes���㣩�����Ӧ������͵�ӳ���
//	������� : 
//	��    ע : ӳ���洢��map<string, string> mapIDs_Explain�У�
//				mapIDs_Explain;Ϊ��xiaoqichuli��һ��˽�г�Ա��
//	��    �� : yxc
//	ʱ    �� : 2004��12��15��
//	�� �� ֵ : void
//	����˵�� : void
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
//	�� �� �� : LoadDictionary
//	�������� : xiaoqichuli
//	�������� : ���شʵ����Դ
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��21��
//	�� �� ֵ : void
//	����˵�� : 
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
        hashtable.SetAt(wordid.word,wordid.IDw,vecpsk);//һ�����hash����
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
//	�� �� �� : Release
//	�������� : xiaoqichuli
//	�������� : 
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��6��21��
//	�� �� ֵ : void
//	����˵�� : 
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
//	�� �� �� : ReadCorpus
//	�������� : xiaoqichuli
//	�������� : xiaoqichuli��Ķ���ӿ�,���뾭�ִʺʹ��Ա�ע�ľ���
//				���3��������ֱ�洢��strOutNum��strOutExplain��strcode�С�
//				strOutNum:Ϊ��������ʹ�õ��Ǵ������
//				strOutExplain:Ϊ�����ֱ�۽���
//                              strcode���ʻ�����б����о�
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��22��
//	�� �� ֵ : void
//	����˵�� : string strSentenceTagger,
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

	if (strSentenceTagger.empty())//����ľ���Ϊ�յ�ʱ��
		
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
	

    	//�������ע�ľ���
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
				if(m_pointer >= m_WordBegin + 1)//����ǿմ�
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
					if(m_pointer == m_WordBegin)//����մ�
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
//	�� �� �� : SearchIDw
//	�������� : xiaoqichuli
//	�������� : Ϊÿһ��������Ĵʻ㣬�ҵ���Ӧ��id��
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��24��
//	�� �� ֵ : void
//	����˵�� : 
///////////////////////////////////////////////////////////////
void xiaoqichuli::SearchIDw()
{
	string word;
	int IDTmp;   //��ʱIDw
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
				pItem = pItem->pNext; //��ͻʱ�������������β���
			if(pItem != NULL)
			{
				IDTmp = pItem->property;
			}
			else
			{
                IDTmp     = -1; 
			}
			
		}
		
		vectIDTmp.push_back(IDTmp);         //ÿ��Ĵʻ�IDwѹ����ʱ��
	}
}
///////////////////////////////////////////////////////////////
//	�� �� �� : _ReadPvs
//	�������� : xiaoqichuli
//	�������� : ��ù��ִʻ����Ϣ
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��24��
//	�� �� ֵ : void
//	����˵�� : vector<wordPsk> ::iterator pIt,
//				vector<wordPvs>& temp��������Ϣ
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
//	�� �� �� : CountPvs
//	�������� : xiaoqichuli
//	�������� : ���������ʻ�ÿһ������ķ�ֵ
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��24��
//	�� �� ֵ : void
//	����˵�� : int i, ��λ������ʻ�ľ���λ��
//				 vector<wordPvs> vectPvsTmp,
//				 vector<wordPsk> ::iterator pIt
///////////////////////////////////////////////////////////////
void xiaoqichuli::CountPvs(int i, vector<wordPvs> vectPvsTmp, vector<wordPsk> ::iterator pIt)
{
	vector<int>    vectConID;
	pair<double,string>   SoreTmp;
	SoreTmp.first = 0;
	SoreTmp.second = pIt->IDs;
	vectConID = vectIDTmp;    //�����Ĺ��ִʻ㣻
	
	vectConID.erase(vectConID.begin() + i);       //ȷ�������ĵ�IDw,���г���������ʵ�id��������������
	int n = 0, m = vectConID.size();
	int count = 1;

	if(count ==0)
	{
		SoreTmp.first = log(pIt->Psk);
		vectSore.push_back(SoreTmp);                         //��Soreֵ�������
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
		
		SoreTmp.first += log(pIt->Psk);                            //����Psk��ȡ����
		vectSore_T.push_back(SoreTmp);                             //��Scoreֵ�������
		SoreTmp.first = log(pIt->Psk);          
		vectSore.push_back(SoreTmp);                               //ֻ���Ƿ�����ʵ�Score              
		
	} 
		

}

///////////////////////////////////////////////////////////////
//	�� �� �� : CountSore
//	�������� : xiaoqichuli
//	�������� : ����
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2005��12��22��
//	�� �� ֵ : void
//	����˵�� : string &strOutNum������������
//                 string &strOutExplain,�����ֱ�۽���
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
	for(i; i < j; i++)                  //����ÿ���ʻ��IDs
	{		
		if(vectIDTmp[i] == -1)          //IDw = -1 �Ĵʻ����ڱ����Ҳ�����
		{
			vectWordTmp[i].IDs = "-1";
		}
		else                            //�Զ���ʽ������
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
					pItem = pItem->pNext; //��ͻʱ�������������β���
				
				if(pItem == NULL)//not in map
				{
					vectWordTmp[i].IDs = "-1";
				}
				else//found
				{  
                     if(pItem->psk.size() == 1)//û������
					 {
						 vectWordTmp[i].IDs = pItem->psk[0].IDs;
					 }
					 else//������
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
							vectWordTmp[i].IDs =vectSore_T[0].second ;                //ȷ�����ŵ�IDs
							for(y; y < vectSore_T.size(); y++)                        //��������Soreֵ����ȷ�����ŵ�IDs
							{
								if(vectSore_T[y].first > STmp)
								{
									STmp = vectSore_T[y].first;
									vectWordTmp[i].IDs =vectSore_T[y].second ;        //ȷ�����ŵ�IDs
								}
							}

						}
						 else
						{
							unsigned int x = 0;
							double STmp =vectSore[0].first;
							vectWordTmp[i].IDs =vectSore[0].second;                    //ȷ�����ŵ�IDs
							for(x; x < vectSore.size(); x++)                           //��������Soreֵ����ȷ�����ŵ�IDs
							{
								if(vectSore[x].first > STmp)
								{							
									STmp = vectSore[x].first;
									vectWordTmp[i].IDs =vectSore[x].second;            //ȷ�����ŵ�IDs
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

	//һ��Ҫ���
	vectIDTmp.clear();
	vectWordTmp.clear();
}

/////////////////////////////////////////////////////////////
//	�� �� �� : main
//	�������� : ������
//	������� : 
//	��    ע : 
//	��    �� : lemon
//	ʱ    �� : 2006��4��22��
//	�� �� ֵ : void
//	����˵�� : 
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
