// heckAre.cpp: implementation of the CheckAre class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CheckAre.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/*CString sideerror="";
CString forkerror="";
CString arrowconflict="";
CString circleerror="";
CString twowordscircle="";*/

CStringArray wordlist;
CStringArray POSlist;

#define MaxWordNumInSent 200

CString words[MaxWordNumInSent];
CString poss[MaxWordNumInSent];
int posilist[MaxWordNumInSent];
int POSposilist[MaxWordNumInSent];

bool linktag[MaxWordNumInSent];

#define GRAPHLEN MaxWordNumInSent

struct graphnode
{
	int iword;
	struct graphnode *link;
};
struct graphnode* wordsgraph[GRAPHLEN];
struct graphnode* wordsgraphbak[GRAPHLEN];


struct headmodinode
{
	int headnum;
	int modinum;
};
struct headmodinode headmodilist[MaxWordNumInSent];

int TreePairIdList[MaxWordNumInSent];

#define MaxWordPairNumInSent 1000

struct mipairnode
{
	int iword1;
	int iword2;

	int headprob;
	bool bfirWord;

	bool visited;
	bool connected;
};
struct mipairnode mipairnodelist[MaxWordPairNumInSent];

#define VALUE 100

int PairLen;
int nSideNum=0;

bool wordgraphtag[GRAPHLEN];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CheckAre::CheckAre()
{

}

CheckAre::~CheckAre()
{

}

void CheckAre::PreProcess(CString &pairlist)
{
	int loc;
	CString result="";
	pairlist.TrimRight('\t');
	pairlist+="\t\t";

	while((loc=pairlist.Find("\t\t")) !=-1)
	{
		CString str;
		str=pairlist.Left(loc);
		pairlist=pairlist.Mid(loc+2);

		loc=str.ReverseFind('_');
		str=str.Left(loc);
		result+=str+"\t\t";
	}

	pairlist=result;
}

void CheckAre::CreateSentList(CString sentence)
{
	biaodiannum=0;
	wordlist.RemoveAll();
	POSlist.RemoveAll();
	sentence.TrimRight(' ');
	sentence+=" ";
	int loc;
	int i=0;
	while((loc=sentence.Find(" ")) !=-1)
	{
		CString str=sentence.Left(loc);
		sentence=sentence.Mid(loc+1);
		
		loc=str.Find("]");
		str=str.Mid(loc+1);

		loc=str.ReverseFind('/');
		wordlist.Add(str.Left(loc));
		POSlist.Add(str.Mid(loc+1));

//		if(POSlist[POSlist.GetSize()-1].GetLength() > 0 && POSlist[POSlist.GetSize()-1].GetAt(0) == 'w')
		if(POSlist[POSlist.GetSize()-1].GetLength() > 0 && POSlist[POSlist.GetSize()-1] == "wp")
			biaodiannum++;

		linktag[i]=false;
		wordsgraph[i]=NULL;
		headmodilist[i].headnum =0;
		headmodilist[i].modinum =0;
		TreePairIdList[i] =-1;

		i++;
	}
}


void CheckAre::AddWordPairSToGraph(CString pairsstr)
{
	int loc;
	int pairID=0;

	while((loc=pairsstr.Find("\t\t")) !=-1)
	{
		CString str;
		str=pairsstr.Left(loc);
		pairsstr=pairsstr.Mid(loc+2);

		CString word1,word2;
		int iword1, iword2;
		
		loc=str.Find("_");
		word1=str.Left(loc);
		word2=str.Mid(loc+1);

		loc=word1.Find("]");
		word1=word1.Left(loc);
		word1=word1.Mid(1);
		iword1=atoi(word1);

		loc=word2.Find("]");
		word2=word2.Left(loc);
		word2=word2.Mid(1);
		iword2=atoi(word2);

		mipairnodelist[pairID].iword1=iword1-1;
		mipairnodelist[pairID].iword2=iword2-1;
		mipairnodelist[pairID].bfirWord=1;
		mipairnodelist[pairID].connected=false;
		mipairnodelist[pairID].headprob=VALUE;
		mipairnodelist[pairID].visited=false;

		pairID++;
	}

	PairLen=pairID;

/*	if(pairID != wordlist.GetSize()-2 && POSlist[POSlist.GetSize()-1].Find("w") ==0)
	{
		sideerror="the number of sides in this sentence is wrong!\r\n";
	}
	else if(pairID != wordlist.GetSize()-1 && POSlist[POSlist.GetSize()-1].Find("w") !=0)
	{
		sideerror="the number of sides in this sentence is wrong!\r\n";
	}*/

	if(pairID != wordlist.GetSize() - biaodiannum -1)
	{
		//sideerror="the number of sides in this sentence is wrong!\r\n";
		sideerror="句子中边的数目不正确!\r\n";
	}
	/*if(pairID != wordlist.GetSize() -1)
	{
		//sideerror="the number of sides in this sentence is wrong!\r\n";
		sideerror="句子中边的数目不正确!\r\n";
	}*/

}

bool CheckAre::ArrowConflictCheck(int iword1, int iword2, int PairID)
{
	//->
	if(mipairnodelist[PairID].bfirWord==1 && headmodilist[iword2].modinum ==1)
		return true;
	//<-
	if(mipairnodelist[PairID].bfirWord==0 && headmodilist[iword1].modinum ==1)
		return true;

	return false;
}

bool CheckAre::CheckIsFork(int MipairLen, int iword1, int iword2)
{
	
	if((iword2-iword1) == 1)
		return false;

	for(int i=0; i<MipairLen; i++)
	{
		//check if there is a fork
		if(mipairnodelist[i].connected && mipairnodelist[i].iword1 < iword1 && iword1 < mipairnodelist[i].iword2 && iword2 > mipairnodelist[i].iword2)
			return true;
		if(mipairnodelist[i].connected && mipairnodelist[i].iword1 < iword2 && iword2 < mipairnodelist[i].iword2 && iword1 > mipairnodelist[i].iword2)
			return true;
		if(mipairnodelist[i].connected && mipairnodelist[i].iword2 < iword1 && iword1 < mipairnodelist[i].iword1 && iword2 > mipairnodelist[i].iword1)
			return true;
		if(mipairnodelist[i].connected && mipairnodelist[i].iword2 < iword2 && iword2 < mipairnodelist[i].iword1 && iword1 > mipairnodelist[i].iword1)
			return true;

		//check if there is a fork
		if(mipairnodelist[i].connected && mipairnodelist[i].iword1 < iword2 && iword2 < mipairnodelist[i].iword2 && iword1 < mipairnodelist[i].iword1)
			return true;
		if(mipairnodelist[i].connected && mipairnodelist[i].iword1 < iword1 && iword1 < mipairnodelist[i].iword2 && iword2 < mipairnodelist[i].iword1)
			return true;
		if(mipairnodelist[i].connected && mipairnodelist[i].iword2 < iword2 && iword2 < mipairnodelist[i].iword1 && iword1 < mipairnodelist[i].iword2)
			return true;
		if(mipairnodelist[i].connected && mipairnodelist[i].iword2 < iword1 && iword1 < mipairnodelist[i].iword1 && iword2 < mipairnodelist[i].iword2)
			return true;

	}
	return false;

}

//bool CheckAre::CheckTwoWordsISCircle(int iword1, int iword2, int PairID)
bool CheckAre::CheckTwoWordsISCircle(int iword1, int iword2)
{

	for(int l=0; l<nSideNum; l++)
	{
		//if(mipairnodelist[TreePairIdList[l]].iword1 == iword1 && mipairnodelist[TreePairIdList[l]].iword2 == iword2 && PairID !=TreePairIdList[l])
		if(mipairnodelist[l].iword1 == iword2 && mipairnodelist[l].iword2 == iword1 )
			return true;
	}

	return false;

}

bool CheckAre::NoTransHead(int PairID)
{

	if(mipairnodelist[PairID].bfirWord)
	{//iword1->iword2
	//	if(headmodilist[mipairnodelist[PairID].iword2].headnum == 0 && headmodilist[mipairnodelist[PairID].iword1].modinum ==0)
	//		return true;

		for(int i=0; i<nSideNum; i++)
		{
			if(mipairnodelist[PairID].iword1 < mipairnodelist[PairID].iword2)
			{
				if(mipairnodelist[TreePairIdList[i]].iword1 == mipairnodelist[PairID].iword2)// && mipairnodelist[TreePairIdList[i]].bfirWord ==0)
				{//iword2做了其它边的主词
					int iword2=mipairnodelist[TreePairIdList[i]].iword2;
					if(iword2 < mipairnodelist[PairID].iword1 && iword2 < mipairnodelist[TreePairIdList[i]].iword1)
						return false;
				}
				
				if(mipairnodelist[TreePairIdList[i]].iword2 == mipairnodelist[PairID].iword1) //&& mipairnodelist[TreePairIdList[i]].bfirWord ==0)
				{//iword1做了其它边的从词
					int iword1=mipairnodelist[TreePairIdList[i]].iword1;
					if(iword1 < mipairnodelist[PairID].iword2 && iword1 > mipairnodelist[TreePairIdList[i]].iword2)
						return false;
				}
			}
			else if(mipairnodelist[PairID].iword1 > mipairnodelist[PairID].iword2)
			{
				for(int i=0; i<nSideNum; i++)
				{
					if(mipairnodelist[TreePairIdList[i]].iword2 == mipairnodelist[PairID].iword1 )//&& mipairnodelist[TreePairIdList[i]].bfirWord)
					{//iword1做了其它边的从词
						int iword1=mipairnodelist[TreePairIdList[i]].iword1;
						if(iword1 > mipairnodelist[PairID].iword2 && iword1 < mipairnodelist[TreePairIdList[i]].iword2)
							return false;
					}
					
					if(mipairnodelist[TreePairIdList[i]].iword1 == mipairnodelist[PairID].iword2 )// && mipairnodelist[TreePairIdList[i]].bfirWord)
					{//iword2做了其它边的主词
						int iword2=mipairnodelist[TreePairIdList[i]].iword2;
						if(iword2 > mipairnodelist[PairID].iword1 && iword2 < mipairnodelist[TreePairIdList[i]].iword1)
							return false;
					}
				}
			}

/*			if(mipairnodelist[TreePairIdList[i]].iword2 == mipairnodelist[PairID].iword2 && mipairnodelist[TreePairIdList[i]].bfirWord ==0)
			{//iword2做了其它边的主词
				int iword1=mipairnodelist[TreePairIdList[i]].iword1;
				if(iword1 < mipairnodelist[PairID].iword1)
					return false;
			}
			else if(mipairnodelist[TreePairIdList[i]].iword2 == mipairnodelist[PairID].iword2 && mipairnodelist[TreePairIdList[i]].bfirWord ==1)
			{//iword2做了其它边的主词
				int iword1=mipairnodelist[TreePairIdList[i]].iword1;
				if(iword1 < mipairnodelist[PairID].iword1)
					return false;
			}

			if(mipairnodelist[TreePairIdList[i]].iword1 == mipairnodelist[PairID].iword1 && mipairnodelist[TreePairIdList[i]].bfirWord ==0)
			{//iword1做了其它边的从词
				int iword2=mipairnodelist[TreePairIdList[i]].iword2;
				if(iword2 < mipairnodelist[PairID].iword2)
					return false;
			}*/
		}
	}
	else
	{//iword1<-iword2
	//	if(headmodilist[mipairnodelist[PairID].iword1].headnum == 0 && headmodilist[mipairnodelist[PairID].iword1].modinum ==0)
	//		return true;

		for(int i=0; i<nSideNum; i++)
		{
			if(mipairnodelist[TreePairIdList[i]].iword1 == mipairnodelist[PairID].iword1 && mipairnodelist[TreePairIdList[i]].bfirWord)
			{
				int iword2=mipairnodelist[TreePairIdList[i]].iword2;
				if(iword2 > mipairnodelist[PairID].iword2)
					return false;
			}

			if(mipairnodelist[TreePairIdList[i]].iword2 == mipairnodelist[PairID].iword2 && mipairnodelist[TreePairIdList[i]].bfirWord)
			{
				int iword1=mipairnodelist[TreePairIdList[i]].iword1;
				if(iword1 > mipairnodelist[PairID].iword1)
					return false;
			}
		}
	}

	return true;

}

void CheckAre::InsertNodeinGraph(int pairID)
{

	if(pairID<0)
	{
		AfxMessageBox("error in InsertNodeinGraph");
	}

	if(mipairnodelist[pairID].bfirWord)
	{
		struct graphnode *p;
		p=new struct graphnode;
		if(p ==NULL)
		{
			AfxMessageBox("get space fails");
			return ;
		}

		p->iword=mipairnodelist[pairID].iword2;
		p->link=wordsgraph[mipairnodelist[pairID].iword1];
		wordsgraph[mipairnodelist[pairID].iword1]= p;
	}
	else
	{
		struct graphnode *p;
		p=new struct graphnode;
		if(p ==NULL)
		{
			AfxMessageBox("get space fails");
			return ;
		}
		
		p->iword=mipairnodelist[pairID].iword1;
		p->link=wordsgraph[mipairnodelist[pairID].iword2];
		wordsgraph[mipairnodelist[pairID].iword2]= p;
	}

}

void CheckAre::ForHasUnVisitWords(int iword1, int iword2, int PairID)
{

	if(!NoTransHead(PairID))
		transheaderror="Find trans head error!\r\n";
	
	mipairnodelist[PairID].connected=true;
	InsertNodeinGraph(PairID);
	if(mipairnodelist[PairID].bfirWord)
	{
		//headmodilist[mipairnodelist[PairID].iword1].headnum++;
		headmodilist[iword1].headnum++;
		//headmodilist[mipairnodelist[PairID].iword2].modinum++;
		headmodilist[iword2].modinum++;
	}
	else
	{
		headmodilist[mipairnodelist[PairID].iword2].headnum++;
		headmodilist[mipairnodelist[PairID].iword1].modinum++;
	}
	
	TreePairIdList[nSideNum]=PairID;
	
	nSideNum++;
	

}

void CheckAre::ReleaseBAKGraphSpace()
{

	for(int k=0; k<GRAPHLEN; k++)
	{
	
		if(wordsgraphbak[k] !=NULL)
		{
			struct graphnode *p=wordsgraphbak[k];
			
			while(p !=NULL)
			{
				wordsgraphbak[k]=wordsgraphbak[k]->link;
				delete p;
				p=wordsgraphbak[k];
			}
		}
		wordsgraphbak[k] =NULL;
	}

}

void CheckAre::CreateGraphBak()
{

	ReleaseBAKGraphSpace();

	struct graphnode *p ,*q ,*qq;

	for(int i=0; i<GRAPHLEN; i++)
	{
		p=wordsgraph[i];
		q=NULL;
		wordsgraphbak[i]=NULL;
		while(p !=NULL)
		{
			qq=new struct graphnode;
			if(qq ==NULL)
			{
				AfxMessageBox("get space fails");
				return ;
			}

			qq->iword=p->iword;
			qq->link=NULL;
			if(wordsgraphbak[i] == NULL)
			{
				wordsgraphbak[i]=qq;
				q=qq;
			}
			else
			{
				q->link =qq;
				q=qq;
			}
			p=p->link;
		}
	}

}

void CheckAre::Depthsearch(int &iword1, int iword2, bool &bcircle)
{

	wordgraphtag[iword1]=true;

	int w =-100;
	struct graphnode *q;

	if(wordsgraph[iword1] !=NULL)
	{
		w=wordsgraph[iword1]->iword;

		q=wordsgraph[iword1];
		wordsgraph[iword1]=q->link;

		delete q;
		q=NULL;

	}

	while( w!= -100)
	{
		if(w == iword2)
		{
			bcircle=true;
		}

		if(!wordgraphtag[w])
			Depthsearch(w, iword2, bcircle);

		if(wordsgraph[iword1] !=NULL)
		{
			w=wordsgraph[iword1]->iword;
			
			q=wordsgraph[iword1];
			wordsgraph[iword1]=q->link;
			
			delete q;
			q=NULL;
		}
		else
		{
			w=-100;
		}
	}

}

bool CheckAre::FindIsCircle(int iword1, int iword2)
{

	for(int i=0; i<GRAPHLEN; i++)
		wordgraphtag[i]=false;

	bool bcircle=false;

	Depthsearch(iword1, iword2, bcircle);

	if(bcircle)
	{
		circleerror="find circle error!\r\n";
	}

	return bcircle;

}

void CheckAre::ReleaseGraphSpace()
{

	for(int k=0; k<GRAPHLEN; k++)
	{
		if(wordsgraph[k] !=NULL)
		{
			struct graphnode *p=wordsgraph[k];
			
			while(p !=NULL)
			{
				wordsgraph[k]=wordsgraph[k]->link;
				delete p;
				p=wordsgraph[k];
			}
		}
		wordsgraph[k] =NULL;
		
	}

}

void CheckAre::CopyGraphBak()
{

	ReleaseGraphSpace();

	struct graphnode *p ,*q ,*qq;
	for(int i=0; i<GRAPHLEN; i++)
	{
		p=wordsgraphbak[i];
		q=NULL;
		wordsgraph[i]=NULL;
		while(p !=NULL)
		{
			qq=new struct graphnode;
			if(qq == NULL)
			{
				AfxMessageBox("get space fails");
				return ;
			}
			qq->iword=p->iword;
			qq->link=NULL;
			if(wordsgraph[i] ==NULL)
			{
				wordsgraph[i]=qq;
				q=qq;
			}
			else
			{
				q->link =qq;
				q=qq;
			}
			p=p->link;
		}
	}
}

void CheckAre::ForBothVisitedWords(int iword1, int iword2, int PairID)
{

	if(!NoTransHead(PairID))
		transheaderror="Find trans head error!\r\n";
	
	CreateGraphBak();
	
//	if(FindIsCircle(iword1, iword2))
//		circleerror="Find cirlce error!\r\n";
	
//	CopyGraphBak();
		
	if(FindIsCircle(iword2, iword1))
		circleerror="Find cirlce error!\r\n";

	CopyGraphBak();
	
	mipairnodelist[PairID].connected=true;
	InsertNodeinGraph(PairID);
	if(mipairnodelist[PairID].bfirWord)
	{
		headmodilist[mipairnodelist[PairID].iword1].headnum++;
		headmodilist[mipairnodelist[PairID].iword2].modinum++;
	}
	else
	{
		headmodilist[mipairnodelist[PairID].iword2].headnum++;
		headmodilist[mipairnodelist[PairID].iword1].modinum++;
	}
	
	TreePairIdList[nSideNum]=PairID;
	
	nSideNum++;
	
	ReleaseBAKGraphSpace();
}

void CheckAre::CheckToAddSide(int MipairLen, int PairID, int iword1, int iword2)
{

	if(ArrowConflictCheck(iword1, iword2, PairID))
		//arrowconflict="find arrow conflict error!\r\n";
		arrowconflict="箭头存在冲突!\r\n";
	
	if(CheckIsFork(MipairLen, iword1, iword2))
		//forkerror="find fork error!\r\n";
		forkerror="存在交叉错误!\r\n";


	//if(CheckTwoWordsISCircle(iword1, iword2, PairID))
	if(CheckTwoWordsISCircle(iword1, iword2))
		//twowordscircle="two words makes a circle!\r\n";
		twowordscircle="两个词构成了圈!\r\n";

	if(!(linktag[iword1] && linktag[iword2]))
	{
		ForHasUnVisitWords(iword1, iword2, PairID);
	}
	else if(linktag[iword1] && linktag[iword2])
	{
		ForBothVisitedWords(iword1,iword2, PairID);
	}
	
	if(!linktag[iword1])
		linktag[iword1] = true;
	if(!linktag[iword2])
		linktag[iword2] = true;

}


void CheckAre::GreedyAlgorithm(int PairLen)
{

	int PairID=-1;
	int iword1,iword2;
	nSideNum=0;

	for(int j=0; j<PairLen; j++)
	{
		PairID=j;
		
		if(PairID < 0)
			break;
		
		iword1=mipairnodelist[PairID].iword1;
		iword2=mipairnodelist[PairID].iword2;
		
		CheckToAddSide(nSideNum, PairID, iword1, iword2);

	}

	ReleaseGraphSpace();

}

void CheckAre::RunChecking(CString pairsstr)
{

	AddWordPairSToGraph(pairsstr);

	GreedyAlgorithm(PairLen);

}
