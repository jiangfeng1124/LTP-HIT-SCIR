 // SentenceView.cpp : implementation file
//

#include "stdafx.h"
#include "wdCheck.h"
#include "SentenceView.h"
#include "ArcView.h"
#include "MainFrm.h"
#include "wdCheckView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSentenceView

IMPLEMENT_DYNCREATE(CSentenceView, CFormView)

static CString arrayDistance[] = {"any","1","2","3","4~6","7~"};
static CString arrayDirection[] = {"Left","Right"};
static int arrayDistance1[] = {-1,1,2,3,4,7};
static int arrayDistance2[] = {-1,1,2,3,6,-1};

CSentenceView::CSentenceView()
	: CFormView(CSentenceView::IDD)
{
	//{{AFX_DATA_INIT(CSentenceView)
	m_strPOS1 = _T("");
	m_strPOS2 = _T("");
	m_strWord1 = _T("");
	m_strWord2 = _T("");
	m_nCount = 0;
	m_strRelation = _T("");
	//}}AFX_DATA_INIT

	Initiatate();
}

CSentenceView::~CSentenceView()
{
}

void CSentenceView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSentenceView)
	DDX_Control(pDX, IDC_MATCHEDPAIR, m_lbMatchedPair);
	DDX_Control(pDX, IDC_DISTANCE, m_lbDistance);
	DDX_Control(pDX, IDC_DIRECTION, m_lbDirection);
	DDX_Control(pDX, IDC_RESULT, m_lbResult);
	DDX_Control(pDX, IDC_SENTENCE, m_editSentence);
	DDX_Text(pDX, IDC_POS1, m_strPOS1);
	DDX_Text(pDX, IDC_POS2, m_strPOS2);
	DDX_Text(pDX, IDC_WORD1, m_strWord1);
	DDX_Text(pDX, IDC_WORD2, m_strWord2);
	DDX_Text(pDX, IDC_COUNT, m_nCount);
	DDV_MinMaxInt(pDX, m_nCount, 0, 10000);
	DDX_Text(pDX, IDC_RELATION, m_strRelation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSentenceView, CFormView)
	//{{AFX_MSG_MAP(CSentenceView)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_LBN_DBLCLK(IDC_RESULT, OnDblclkResult)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSentenceView diagnostics

#ifdef _DEBUG
void CSentenceView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSentenceView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSentenceView message handlers


void CSentenceView::OnSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	ConvertData();
	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	CWordsArray wordsarray;
	CPairArray pairarray;
	m_lbResult.ResetContent();
	m_lbMatchedPair.ResetContent();

	m_nCount = 0;
	for(int i = 0; i < pFrame->m_nLastRow; i++)
	{
		wordsarray.SetWordArray(pFrame->m_DoingBlock[i].m_strSentence);
		pairarray.SetPairArray(pFrame->m_DoingBlock[i].m_strPairs);
		m_strMatchedPair = Match(m_strWord1,m_strPOS1,m_strDirection,m_strWord2,m_strPOS2,m_strRelation,m_nDistance1,m_nDistance2,pairarray,wordsarray);
		if(m_strMatchedPair != "")
		{
			CString strTemp;
			strTemp.Format("%d", i + 1);
//			m_lbResult.AddString(strTemp);
//			m_lbMatchedPair.AddString(m_strMatchedPair);
			m_lbResult.InsertString(-1,strTemp);
			m_lbMatchedPair.InsertString(-1,m_strMatchedPair);
			m_nCount++;
		}
	}
	UpdateData(false);
	if(m_nCount == 0)
		AfxMessageBox("未找到符合要求的句子！");
}

CString CSentenceView::Match(CString m_strWord1, CString m_strPOS1, CString m_strDirection, CString m_strWord2, CString m_strPOS2, CString m_strRelation, int m_nDistance1,int m_nDistance2,CPairArray& pairarray, CWordsArray& wordsarray)
{
	CString strMatchedPair = "";
	for(int i = 0; i < pairarray.GetSize(); i++)
	{
		int nLeftNum = pairarray.GetPair(i).GetLeftNum();
		int nRightNum = pairarray.GetPair(i).GetRightNum();
		CString strDirection;
		if(nLeftNum > nRightNum)//弧的方向向左
		{
			strDirection = "Left";
		}
		else//弧的方向向右
		{
			strDirection = "Right";
		}
		if(m_strDirection == strDirection && m_strDirection == "Left")
		{
			if((m_strWord1 == "" || pairarray.GetPair(i).m_strWordLeft == m_strWord1)//match left word
				&& (m_strWord2 == "" || pairarray.GetPair(i).m_strWordRight == m_strWord2)//match right word
				
				&& (m_strPOS1 == "" || wordsarray.GetAttr(nLeftNum -1 ) == m_strPOS1)//match left tag
				&& (m_strPOS2 == "" || wordsarray.GetAttr(nRightNum -1 ) == m_strPOS2)//match right tag

				&& (m_strRelation == "" || pairarray.GetPair(i).m_strRelation == m_strRelation)//match dependency relation

				&& (MatchDistance(nLeftNum,nRightNum,m_nDistance1,m_nDistance2) ) )//match distance
			{
				CString strTemp;
				strMatchedPair += "[";
				strTemp.Format("%d", nLeftNum);
				strMatchedPair += strTemp + "]" +
					pairarray.GetPair(i).m_strWordLeft + "_" + "[";
				strTemp.Format("%d", nRightNum);
				strMatchedPair += strTemp + "]" +
					pairarray.GetPair(i).m_strWordRight ;
				return strMatchedPair;//返回匹配上的依存对
			}
		}
		if(m_strDirection == strDirection && m_strDirection == "Right")
		{
			if((m_strWord1 == "" || pairarray.GetPair(i).m_strWordRight == m_strWord1)//match left word
				&& (m_strWord2 == "" || pairarray.GetPair(i).m_strWordLeft == m_strWord2)//match right word
				
				&& (m_strPOS1 == "" || wordsarray.GetAttr(nRightNum -1 ) == m_strPOS1)//match left tag
				&& (m_strPOS2 == "" || wordsarray.GetAttr(nLeftNum -1 ) == m_strPOS2)//match right tag

				&& (m_strRelation == "" || pairarray.GetPair(i).m_strRelation == m_strRelation)//match dependency relation

				&& (MatchDistance(nLeftNum,nRightNum,m_nDistance1,m_nDistance2) ) )//match distance
			{
				CString strTemp;
				strMatchedPair += "[";
				strTemp.Format("%d", nLeftNum);
				strMatchedPair += strTemp + "]" +
					pairarray.GetPair(i).m_strWordLeft + "_" + "[";
				strTemp.Format("%d", nRightNum);
				strMatchedPair += strTemp + "]" +
					pairarray.GetPair(i).m_strWordRight ;
				return strMatchedPair;//返回匹配上的依存对
			}
		}
	}
	return "";
}

bool CSentenceView::MatchDistance(int nLeftNum, int nRightNum, int m_nDistance1,int m_nDistance2)
{
	if(m_nDistance1 == -1 && m_nDistance2 == -1)
		return 1;
	int distance = nLeftNum - nRightNum;
	if(distance < 0)
		distance = 0 - distance;
	if(m_nDistance2 == -1)
	{
		if(distance >= m_nDistance1)
			return 1;
		else
			return 0;
	}
	else if(m_nDistance1 <= distance && distance <= m_nDistance2)
		return 1;
	else
		return 0;
}


void CSentenceView::OnDblclkResult() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	pFrame->SaveCurrent();
	if(!pFrame->CheckArc())
		return;
	CWdCheckView *pWnd2=(CWdCheckView*)pFrame->m_wndSplitter.GetPane(1,0);
//	pWnd2->CheckSentence();
//	if(pWnd2->mb_result==6)
	{
		CString strTemp;
		m_lbResult.GetText(m_lbResult.GetCurSel(), strTemp);
		m_lbMatchedPair.SetCurSel(m_lbResult.GetCurSel());
		char* pTemp;
		pTemp = strTemp.GetBuffer(strTemp.GetLength());
		pFrame->m_nCurrentRow = ::atoi(pTemp);
		pFrame->m_nCurrentRow--;
   		if(pFrame->m_nCurrentRow < pFrame->m_nLastRow)
		{
			pFrame->m_PairArray.SetPairArray(pFrame->m_DoingBlock[pFrame->m_nCurrentRow].m_strPairs);
			CArcView *pWnd3 = (CArcView *) pFrame->m_wndSplitter.GetPane(2, 0);
			pWnd3->Invalidate();
//			pWnd2->PrepareSentence(pFrame->m_nCurrentRow*2+1);
			pWnd2->Invalidate();
			pFrame->m_WordArray.SetWordArray(pFrame->m_DoingBlock[pFrame->m_nCurrentRow].m_strSentence);
			CSentenceView *pWnd1= (CSentenceView *) pFrame->m_wndSplitter.GetPane(0,0);
			pWnd1->m_editSentence.SetWindowText(pFrame->m_DoingBlock[pFrame->m_nCurrentRow].m_strSentence);
		}
		else
		{
			AfxMessageBox("Too large number!!");
		}
		pWnd2->mb_result=0;
	}
}

void CSentenceView::Initiatate()
{
//	CString str1 = arrayDirection[0];
//	m_lbDirection.AddString(arrayDirection[0]);
//	m_lbDirection.AddString(arrayDirection[1]);
//	m_lbDirection.SetCurSel(0);
//
//	for(int i = 0; i < 6; i++)
//	{
//		CString str2 = arrayDistance[i];
//		m_lbDistance.AddString(arrayDistance[i]);
//	}
//	m_lbDistance.SetCurSel(5);

//	UpdateData(TRUE);
}
void CSentenceView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_lbDirection.InsertString(-1,arrayDirection[0]);
	m_lbDirection.InsertString(-1,arrayDirection[1]);
	m_lbDirection.SetCurSel(0);

	for(int i = 0; i < 6; i++)
	{
		CString str2 = arrayDistance[i];
		m_lbDistance.InsertString(-1,arrayDistance[i]);
	}
	m_lbDistance.SetCurSel(0);

}

void CSentenceView::ConvertData()
{

	int num = m_lbDistance.GetCurSel();
	m_nDistance1 = arrayDistance1[num];
	m_nDistance2 = arrayDistance2[num];
	
	num = m_lbDirection.GetCurSel();//弧的方向
	m_strDirection = arrayDirection[num];
}

void CSentenceView::OnReset() 
{
	// TODO: Add your control notification handler code here
	m_strPOS1 = "";
	m_strPOS2 = "";
	m_strWord1 = "";
	m_strWord2 = "";
	m_strRelation = "";
	m_lbDirection.SetCurSel(0);
	m_lbDistance.SetCurSel(0);
	UpdateData(FALSE);
	
}

/*
bool CSentenceView::IsPair(CString strPOS1, CString strPOS2, CString strWord1, CString strWord2, 
						   CPairArray& pairarray, CWordsArray& wordsarray)
{
	bool bPOS = TRUE;
	bool bWord = TRUE;
	
	if(strPOS1 != "" || strPOS2 != "")
		bPOS = FALSE;
	if(strWord1 != "" || strWord2 != "")
		bWord = FALSE;
	
	if(!bPOS){
		for(int i = 0; i < pairarray.GetSize(); i++){
			int nLeftNum = pairarray.GetPair(i).GetLeftNum();
			if(wordsarray.GetAttr(nLeftNum -1 ) == strPOS1){
				int nRightNum = pairarray.GetPair(i).GetRightNum();
				if(wordsarray.GetAttr(nRightNum - 1) == strPOS2){
					bPOS = TRUE;
					break;
				}
			}
		}
	}
	
	if(!bWord){
		for(int i = 0; i < pairarray.GetSize(); i++){
			if(pairarray.GetPair(i).m_strWordLeft == strWord1 && 
				pairarray.GetPair(i).m_strWordRight == strWord2){				
					bWord = TRUE;
					break;
			}
		}
	}

	return (bPOS && bWord);
}

void CSentenceView::OnSearch() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	CWordsArray wordsarray;
	CPairArray pairarray;
	m_lbResult.ResetContent();
	m_nCount = 0;
	for(int i = 0; i < pFrame->m_nLastRow; i++){
		wordsarray.SetWordArray(pFrame->m_DoingBlock[i].m_strSentence);
		pairarray.SetPairArray(pFrame->m_DoingBlock[i].m_strPairs);
		if((m_strPOS1 != "" && m_strPOS2 != "") || (m_strWord1 != "" && m_strWord2 != "")){
			if(IsPair(m_strPOS1, m_strPOS2, m_strWord1, m_strWord2, pairarray, wordsarray)){
				CString strTemp;
				strTemp.Format("%d", i + 1);
				m_lbResult.AddString(strTemp);
				m_nCount++;
			}
		}else if((m_strPOS1 != "" && m_strPOS2 == "") || (m_strWord1 != "" && m_strWord2 == "")){
			if(IsLeft(m_strPOS1, m_strWord1, pairarray, wordsarray)){
				CString strTemp;
				strTemp.Format("%d", i + 1);
				m_lbResult.AddString(strTemp);
				m_nCount++;
			}
		}else if((m_strPOS1 == "" && m_strPOS2 != "") || (m_strWord1 == "" && m_strWord2 != "")){
			if(IsRight(m_strPOS2, m_strWord2, pairarray, wordsarray)){
				CString strTemp;
				strTemp.Format("%d", i + 1);
				m_lbResult.AddString(strTemp);
				m_nCount++;
			}
		}
	}
	m_strPOS1 = "";
	m_strPOS2 = "";
	m_strWord1 = "";
	m_strWord2 = "";
	UpdateData(FALSE);
}

bool CSentenceView::IsLeft(CString strPOS1, CString strWord1, CPairArray& pairarray, CWordsArray& wordsarray)
{
	bool bPOS = TRUE;
	bool bWord = TRUE;
	
	if(strPOS1 != "")
		bPOS = FALSE;
	if(strWord1 != "")
		bWord = FALSE;
	
	if(!bPOS){
		for(int i = 0; i < pairarray.GetSize(); i++){
			int nLeftNum = pairarray.GetPair(i).GetLeftNum();
			if(wordsarray.GetAttr(nLeftNum -1 ) == strPOS1){
				bPOS = TRUE;
				break;
			}
		}
	}
	
	if(!bWord){
		for(int i = 0; i < pairarray.GetSize(); i++){
			if(pairarray.GetPair(i).m_strWordLeft == strWord1){
				bWord = TRUE;
				break;
			}
		}
	}

	return (bPOS && bWord);
}

bool CSentenceView::IsRight(CString strPOS1, CString strWord1, CPairArray& pairarray, CWordsArray& wordsarray)
{
	bool bPOS = TRUE;
	bool bWord = TRUE;
	
	if(strPOS1 != "")
		bPOS = FALSE;
	if(strWord1 != "")
		bWord = FALSE;
	
	if(!bPOS){
		for(int i = 0; i < pairarray.GetSize(); i++){
			int nRightNum = pairarray.GetPair(i).GetRightNum();

			if(wordsarray.GetAttr(nRightNum - 1) == strPOS1){
				bPOS = TRUE;
				break;
			}
		}
	}
	
	if(!bWord){
		for(int i = 0; i < pairarray.GetSize(); i++){
			if(pairarray.GetPair(i).m_strWordRight == strWord1){
				bWord = TRUE;
				break;
			}
		}
	}

	return (bPOS && bWord);
}
*/
