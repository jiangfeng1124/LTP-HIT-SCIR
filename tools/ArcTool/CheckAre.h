#if !defined(AFX_HECKARE_H__83E631C3_FA96_458A_AD62_C04E859C9EA6__INCLUDED_)
#define AFX_HECKARE_H__83E631C3_FA96_458A_AD62_C04E859C9EA6__INCLUDED_
// heckAre.h: interface for the CheckAre class.
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CheckAre  
{
public:
	CheckAre();
	virtual ~CheckAre();

	CString sideerror;
	CString forkerror;
	CString arrowconflict;
	CString circleerror;
	CString twowordscircle;
	CString transheaderror;

	int biaodiannum;

	void RunChecking(CString pairsstr);
	void AddWordPairSToGraph(CString pairsstr);
	bool ArrowConflictCheck(int iword1, int iword2, int PairID);
	bool CheckIsFork(int MipairLen, int iword1, int iword2);
	void CheckToAddSide(int MipairLen, int PairID, int iword1, int iword2);
	//bool CheckTwoWordsISCircle(int iword1, int iword2, int PairID);
	bool CheckTwoWordsISCircle(int iword1, int iword2);
	void CopyGraphBak();
	void CreateSentList(CString sentence);
	void Depthsearch(int &iword1, int iword2, bool &bcircle);
	bool FindIsCircle(int iword1, int iword2);
	void ForBothVisitedWords(int iword1, int iword2, int PairID);
	void ForHasUnVisitWords(int iword1, int iword2, int PairID);
	void GreedyAlgorithm(int PairLen);
	void InsertNodeinGraph(int pairID);
	bool NoTransHead(int PairID);
	void PreProcess(CString &pairlist);
	void ReleaseBAKGraphSpace();
	void ReleaseGraphSpace();
	void CreateGraphBak();


};

#endif // !defined(AFX_HECKARE_H__83E631C3_FA96_458A_AD62_C04E859C9EA6__INCLUDED_)
