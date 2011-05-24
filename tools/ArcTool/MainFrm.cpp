  // MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "wdCheck.h"
#include "wdCheckView.h"
#include "MainFrm.h"
#include "IsSaveDlg.h"
#include "ArcView.h"
#include "SentenceView.h"
#include "QuestionDlg.h"

#include <fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	ON_WM_CLOSE()
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_UPDATE_COMMAND_UI(ID_DELETE, OnUpdateDelete)
	ON_COMMAND(ID_BUTTONCHANGE, OnButtonchange)
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_SAVE, OnSave)
	ON_COMMAND(ID_FIRST, OnFirst)
	ON_COMMAND(ID_LAST, OnLast)
	ON_COMMAND(ID_PRE, OnPre)
	ON_COMMAND(ID_NEXT, OnNext)
	ON_COMMAND(ID_GO, OnGo)
	ON_COMMAND(ID_QUESTION, OnQuestion)
	ON_UPDATE_COMMAND_UI(ID_FIRST, OnUpdateFirst)
	ON_UPDATE_COMMAND_UI(ID_LAST, OnUpdateLast)
	ON_UPDATE_COMMAND_UI(ID_PRE, OnUpdatePre)
	ON_UPDATE_COMMAND_UI(ID_NEXT, OnUpdateNext)
	ON_UPDATE_COMMAND_UI(ID_GO, OnUpdateGo)
	ON_UPDATE_COMMAND_UI(ID_OPEN, OnUpdateOpen)
	ON_UPDATE_COMMAND_UI(ID_SAVE, OnUpdateSave)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_CLASSIFY, OnClassify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bBegin=FALSE;
	resultfile=NULL;
	checkfile=NULL;
	m_nCurrentRow = 0;

/*
	AfxMessageBox("ok11");
	ifstream fin("863POSList.txt");
	ofstream fout("relation.txt");
	int size = 29;
	string vecline[30];
	int i = 0,j = 0;
	while(getline(fin,vecline[i++]))
	{}
	for(i = 0;i < size-1;i++)
	{
		for(j = i+1;j < size;j++)
		{
			fout<<vecline[i]<<' '<<vecline[j]<<' '<<'0'<<"\t"<<endl;
			fout<<vecline[j]<<' '<<vecline[i]<<' '<<'1'<<"\t"<<endl;
		}
	}
	AfxMessageBox("ok");
*/
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

     cs.style &= ~FWS_ADDTOTITLE;    // no title
	 cs.lpszName="DTSee-��������ҵ��ѧ��Ϣ�����о�����";
     return CFrameWnd::PreCreateWindow(cs);
//	return TRUE;
}

void CMainFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	nCmdShow = SW_SHOWMAXIMIZED;
	CFrameWnd::ActivateFrame(nCmdShow);
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
	
}

void CMainFrame::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
	
}

void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
	
}

void CMainFrame::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
	
}

void CMainFrame::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
	
}

//�رճ���ʱ���ļ��Զ�����
void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
//	CWdCheckView *pWnd2=(CWdCheckView*)m_wndSplitter.GetPane(1,0);
	if(m_bBegin)
	{
		SaveCurrent();
		CWdCheckView *pWnd2=(CWdCheckView*)m_wndSplitter.GetPane(1,0);
		resultfile=new ofstream((LPCTSTR)prefilepath);
		if(!resultfile->is_open())
		{
			AfxMessageBox("Can't open the output file!");
			return;
		}
		for(int i=0;i<m_nLastRow;i++)
		{		
//			string s1,s2,s3;
//			s3=vec_file[i*2];
//			s1=(LPCTSTR)m_DoingBlock[i].m_strSentence;
//			s2=(LPCTSTR)m_DoingBlock[i].m_strPairs; 

//			(*(resultfile))<<vec_file[i*2]<<'\n';//�����еĵ�һ�䣬�޸Ĵ��Ա�Ǻ󣬲��ܸı䣬�ʲ����
			(*(resultfile))<<(LPCTSTR)m_DoingBlock[i].m_strOrigSent<<'\n';
			(*(resultfile))<<(LPCTSTR)m_DoingBlock[i].m_strSentence<<'\n';
			(*(resultfile))<<(LPCTSTR)m_DoingBlock[i].m_strPairs<<'\n';

		}
		resultfile->close();
		delete resultfile;
	}

   	CFrameWnd::OnClose();
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
    m_wndSplitter.CreateStatic(this, 3, 1);	
	m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CSentenceView), CSize(100,190), pContext);
//	m_wndSplitter.CreateView(0, 0,
//		RUNTIME_CLASS(CSentenceView), CSize(100,50), pContext);
	m_wndSplitter.CreateView(1,0,
		RUNTIME_CLASS(CWdCheckView),CSize(100,40),pContext);//200
	m_wndSplitter.CreateView(2, 0,
		RUNTIME_CLASS(CArcView), CSize(3000,140), pContext);//40
//	m_wndSplitter.CreateView(0, 0,
//		RUNTIME_CLASS(CSentenceView), CSize(100,165), pContext);
//	m_wndSplitter.CreateView(1,0,
//		RUNTIME_CLASS(CWdCheckView),CSize(100,50),pContext);//200
//	m_wndSplitter.CreateView(2, 0,
//		RUNTIME_CLASS(CArcView), CSize(3000,140), pContext);//40


    return TRUE;
	
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::SaveCurrent()
{
	CString strTemp;
	CString strSent = "";
	m_DoingBlock[m_nCurrentRow].m_strSentence = "";
	m_DoingBlock[m_nCurrentRow].m_strPairs = "";

	int pos1 = 0;
	int pos2 = 0;
	
	for(int i = 0; i < m_WordArray.GetSize(); i++)
	{
		m_DoingBlock[m_nCurrentRow].m_strSentence += "[";
		strTemp.Format("%d", m_WordArray.GetWord(i).m_nPos);
		m_DoingBlock[m_nCurrentRow].m_strSentence += strTemp + "]" +
			m_WordArray.GetWord(i).GetWord() + "/" + m_WordArray.GetWord(i).m_strAttr + " ";
		
//�ֶ��޸Ĵ��Ժ󣬵�һ�о��ӵĴ���Ҳ��֮�ı䣬���ǲ����޸ķִ�
//		CString strTag =  m_WordArray.GetWord(i).m_strAttr;
//		if(strTag != "<EOS>" )
//		{
//			pos1 = strSent.Find('/',pos2);
//			pos2 = strSent.Find(' ',pos1);
//			int pos = strSent.Find(']',pos1);//����ʵ���ǵ��ұ߽�
//			if(pos != -1 && pos < pos2)
//				pos2 = pos;
//			strSent = strSent.Left(pos1+1) + strTag + strSent.Right(strSent.GetLength()-pos2);
//			pos2 = pos1 + 1;
//		}

//�ֶ��޸ķִʼ����Ժ󣬵�һ�о��ӵ�Ҳ��֮�ı䣬���ǲ��ܸı�ʵ��߽緽�����ڵĴʼ�����
		CString strTag =  m_WordArray.GetWord(i).m_strAttr;
		if(strTag != "<EOS>")
			strSent += m_WordArray.GetWord(i).GetWord() + "/" + strTag + " ";//�ı�ִʼ����Ա�ע��ľ���
	}
	KeepBracket(m_DoingBlock[m_nCurrentRow].m_strOrigSent,strSent);//����ʵ��߽緽����
	if(m_DoingBlock[m_nCurrentRow].m_strOrigSent[0] == '*')
		strSent = '*' + strSent;//�������淶���
	m_DoingBlock[m_nCurrentRow].m_strOrigSent = strSent;

	//���������ϵ��ע���
	for(int i = 0; i < m_PairArray.GetSize(); i++)
	{
		if(m_PairArray.GetPair(i).m_nNumLeft > 0)
		{
			m_DoingBlock[m_nCurrentRow].m_strPairs += "[";
			strTemp.Format("%d", m_PairArray.GetPair(i).m_nNumLeft);
			m_DoingBlock[m_nCurrentRow].m_strPairs += strTemp + "]" +
				m_PairArray.GetPair(i).m_strWordLeft + "_" + "[";
			strTemp.Format("%d", m_PairArray.GetPair(i).m_nNumRight);
			m_DoingBlock[m_nCurrentRow].m_strPairs += strTemp + "]" +
				m_PairArray.GetPair(i).m_strWordRight + 
				"(" + m_PairArray.GetPair(i).m_strRelation + ")" + "\t\t";
		}
	}
	CArcView *pWnd3 = (CArcView*)m_wndSplitter.GetPane(2,0);
	pWnd3->m_nCountClick = 0;//ǰһ�����ӵĵ����Ӱ����һ������
	pWnd3->m_nRightClick = 0;

//---------------begin-----------------//
//���ڼ�¼�˹���ע�����еĴ��Զ������ɵ�
//�����ϵ��ÿ��עһ�����ӣ��ͽ��µĴ���
//�Ի��µĹ�ϵ������ӵ��ļ��У���������
//��ϵ�ļ��ʹʻ��ϵ�ļ�
//�ù������ڿ�ʼʱȷ�������ϵ�Ĺ��򣬹�
//��ȷ���󣬸öδ��벻��
//	ReadRelation();
//	for(i = 0;i < m_PairArray.GetSize();i++)//�����¼�Ĵ��������ϵ����
//	{
//		AppendRelation(m_PairArray.GetPair(i),vecTagPair,1);//���Թ�ϵ
//
//		if(m_PairArray.GetPair(i).m_strTagLeft == "u")
//			AppendRelation(m_PairArray.GetPair(i),vecWordPair,0);//�ʻ��ϵ
//	}
//	WriteRelation();
//-----------------end-----------------//
}

BOOL CMainFrame::CheckArc()
{
	CheckAre check;
	check.CreateSentList(m_DoingBlock[m_nCurrentRow].m_strSentence);
	check.RunChecking(m_DoingBlock[m_nCurrentRow].m_strPairs);
	CString strInfor = check.sideerror + check.forkerror + check.arrowconflict + 
		check.circleerror + check.twowordscircle;
//////////////////////////////////////////////////////////////////////////
//����Ƿ����������͵ı�ע����
	CString strPair = m_DoingBlock[m_nCurrentRow].m_strPairs;
	CString strMyInfo = "";
	if(strPair.Find("(NO)") != -1)
		strMyInfo += "���󣺹�ϵ����û�б�ע�꣡\n";
	int pos = strPair.Find("(HED)");
	if(pos == -1 || strPair.Find("(HED)",pos+1) != -1)
		strMyInfo += "���ӵĺ��Ĵʱ�ע����\n";
//	strMyInfo += MyCheck(strPair,"(DBL)");
//	strMyInfo += MyCheck(strPair,"(DOB)");
//	strMyInfo += MyCheck(strPair,"(DE)");
//	strMyInfo += MyCheck(strPair,"(DI)");
//	strMyInfo += MyCheck(strPair,"(DEI)");
//	strMyInfo += MyCheck(strPair,"(BA)");
//	strMyInfo += MyCheck(strPair,"(BEI)");
	strInfor = strInfor + strMyInfo;
//////////////////////////////////////////////////////////////////////////
	if(strInfor == "")
		return TRUE;
	else
	{
		//��¼��ע�Ĵ����Կ����Ƿ�����
//		CString path=filepath;
//		int pos = path.Find(".txt");
//		path = path.Left(pos) + "_log.txt";
//		resultfile=new ofstream((LPCTSTR)path,ios::app);
//		resultfile->seekp(0,ios::end);
//		(*resultfile)<<"==================No."<<m_nCurrentRow+1<<"================"<<'\n';
//		(*resultfile)<<(LPCTSTR)strInfor<<'\n';
//		resultfile->close();
//		delete resultfile;

		AfxMessageBox(strInfor);
//		return FALSE;
		return TRUE;//������ֱ�ע����Ҳ���ߵ���һ��
	}

}

//����Ƿ����������͵ı�ע����
CString CMainFrame::MyCheck(CString strPair,CString strRel)
{
	CString strMyInfo = "";
	int pos;
	pos = strPair.Find(strRel);
	if(pos == -1)
		return "";
	pos = strPair.Find(strRel,pos+1);
	if(pos == -1)
		strMyInfo = "\n���棺��ϵ���Ϳ��ܲ���ԣ�\n";
//		strMyInfo = "\n���󣺼���DBL��˫����DOB������������\n";
	return strMyInfo;
}

BOOL CMainFrame::CheckArc(CString strSentence, CString strPairs)
{
	CheckAre check;
	check.CreateSentList(strSentence);
	check.RunChecking(strPairs);
	CString strInfor = check.sideerror + check.forkerror + check.arrowconflict + 
		check.circleerror + check.twowordscircle;
	if(strInfor == "")
		return TRUE;
	else
		return FALSE;

}

void CMainFrame::OnChange()
{
    CString strSentence;
	CSentenceView *pWnd1= (CSentenceView *) m_wndSplitter.GetPane(0,0);
	pWnd1->m_editSentence.GetWindowText(strSentence);

	strSentence += " ";
	int nOrigWordsNum = m_WordArray.GetSize();
	m_WordArray.ReSetWordArray(strSentence);
	if(m_WordArray.GetSize() != nOrigWordsNum){
		m_PairArray.ReSetPairArray(m_WordArray);
	}
    SaveCurrent();
	CArcView *pWnd3=(CArcView*) m_wndSplitter.GetPane(2,0);
	pWnd3->Invalidate();
}

void CMainFrame::OnDelete() 
{
	// TODO: Add your command handler code here
	m_PairArray.SetPairArray("");
	SaveCurrent();
	CArcView *pWnd3= (CArcView *) m_wndSplitter.GetPane(2, 0);
	pWnd3->Invalidate();
	
}

void CMainFrame::OnUpdateDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bBegin);
	
}


void CMainFrame::OnButtonchange() 
{
	// TODO: Add your command handler code here
    CString strSentence;
	CSentenceView *pWnd1= (CSentenceView *) m_wndSplitter.GetPane(0,0);
	pWnd1->m_editSentence.GetWindowText(strSentence);

	//�޸ĵ�һ�о��ӵĴ���ʱ�����ܸı�ո������
//	CString strBeforeSent = m_DoingBlock[m_nCurrentRow].m_strSentence;
//	int nCount1 = Count(strBeforeSent,' ');
//	int nCount2 = Count(strSentence,' ');
//	if(nCount1 != nCount2)
//	{
//		AfxMessageBox("����ɾ�������ӿո�");
//		return;
//	}

	strSentence += " ";
	int nOrigWordsNum = m_WordArray.GetSize();
	m_WordArray.ReSetWordArray(strSentence);
	if(m_WordArray.GetSize() != nOrigWordsNum){
		m_PairArray.ReSetPairArray(m_WordArray);
	}
    SaveCurrent();
	
	pWnd1->m_editSentence.SetWindowText(m_DoingBlock[m_nCurrentRow].m_strSentence);
	CWdCheckView *pWnd2 = (CWdCheckView*)m_wndSplitter.GetPane(1,0);
	pWnd2->Invalidate();
	CArcView *pWnd3=(CArcView*) m_wndSplitter.GetPane(2,0);
	pWnd3->Invalidate();
}

void CMainFrame::ReadRelation()
{
	ifstream fin1("TagRelation.txt");
	ifstream fin2("WordRelation.txt");
	
	ReadFile(fin1,vecTagPair);//������Թ�ϵ����
	ReadFile(fin2,vecWordPair);//����ʻ��ϵ����

	fin1.close();
	fin2.close();
}

//����ϵ������ļ��ж�������
void CMainFrame::ReadFile(ifstream &fin, vector < CPair > &vecPair)
{
	string strTemp;
	CString strline,strUnit,strRel;
	int pos;

	for(int i = 0;i < (int)vecPair.size();i++)
		vecPair[i].other.clear();
	vecPair.clear();
	
	while(getline(fin,strTemp))
	{
		if(strTemp == "")
			continue;
		strline = strTemp.c_str();
		
		CPair myPair;
		pos = strline.ReverseFind(' ');
		strUnit = strline.Mid(0,pos);
		myPair.m_strTagRule = strUnit;
		myPair.m_strWordRule = strUnit;
		strline = strline.Right(strline.GetLength()-pos-1);
		pos = strline.Find('\t');
		myPair.m_strRelation = strline.Mid(0,pos);

		strline = strline.Right(strline.GetLength()-pos-1);
		pos = strline.Find('\t');
		while(pos != -1)
		{
			strRel = strline.Mid(0,pos);
			strline = strline.Right(strline.GetLength()-pos-1);
			myPair.other.push_back(strRel);
			pos = strline.Find('\t');
		}
		vecPair.push_back(myPair);
	}
}

void CMainFrame::WriteRelation()
{
	ofstream fout1("TagRelation.txt");
	ofstream fout2("WordRelation.txt");

	WriteFile(fout1,vecTagPair,1);//д����Թ�ϵ����
	WriteFile(fout2,vecWordPair,0);//д��ʻ��ϵ����

	fout1.close();
	fout2.close();
}

//����ϵ���������д���ļ���
void CMainFrame::WriteFile(ofstream &fout, vector < CPair > &vecPair,bool bTag)
{
	string strTemp;
	CPair myPair;
	CString strline,strUnit,strRule;

	int size = vecPair.size();
	for(int i = 0;i < size;i++)
	{
		if(bTag)
			strRule = vecPair[i].m_strTagRule;
		else
			strRule = vecPair[i].m_strWordRule;
		if("NO" != vecPair[i].m_strRelation)
			fout<<(LPCTSTR)strRule<<' '<<(LPCTSTR)vecPair[i].m_strRelation<<'\t';

		int len = vecPair[i].other.size();
		for(int j = 0;j < len;j++)
		{
			CString str = vecPair[i].other[j];
			if("NO" != str)
				fout<<(LPCTSTR)vecPair[i].other[j]<<'\t';
		}
		fout<<endl;
	}
}

void CMainFrame::AppendRelation(CPair &mypair,vector < CPair > &vecPair,bool bTag)
{
	CString strRule,vecRule,strDirect;
	if(mypair.m_nNumLeft < mypair.m_nNumRight)
		strDirect = "0";
	else
		strDirect = "1";
	mypair.m_strTagRule = mypair.m_strTagLeft + ' ' + mypair.m_strTagRight + ' ' + strDirect;
	mypair.m_strWordRule = mypair.m_strWordLeft + '/' + mypair.m_strTagLeft + ' ' + mypair.m_strTagRight + ' ' + strDirect;
	mypair.other.clear();
	for(int i = 0;i < (int)vecPair.size();i++)
	{
		if(bTag)
		{
			strRule = mypair.m_strTagRule;
			vecRule = vecPair[i].m_strTagRule;
		}
		else
		{
			strRule = mypair.m_strWordRule;
			vecRule = vecPair[i].m_strWordRule;
		}
		
		if(strRule != vecRule)
			continue;
		CString str1 = vecPair[i].m_strRelation;
		if(mypair.m_strRelation == vecPair[i].m_strRelation)
			return;
		int size = vecPair[i].other.size();
		int j;
		for(j = 0;j < size;j++)
		{
			CString str2 = vecPair[i].other[j];
			if(mypair.m_strRelation == vecPair[i].other[j])
				return;
		}
		if(j == size)
		{
			vecPair[i].other.push_back(mypair.m_strRelation);
			return;
		}
	}
	vecPair.push_back(mypair);
}

//////////////////////////////////////////////////////////////////////////
//��CWdCheckView���ƹ�����Ϣ����
void CMainFrame::OnOpen() 
{
	// TODO: Add your command handler code here
//	CMainFrame *pFrame=(CMainFrame*)this->GetParent()->GetParent();
  	CWdCheckView *pWnd2=(CWdCheckView*)m_wndSplitter.GetPane(1,0);
	if(m_bBegin)
	{
		resultfile=new ofstream((LPCTSTR)prefilepath);
		if(!resultfile->is_open())
		{
			MessageBox("Can't open the file!");
			return;
		}
		for(int i=0;i<m_nLastRow;i++)
		{
//			(*resultfile)<<vec_file[i*2]<<'\n';
			(*resultfile)<<(LPCTSTR)m_DoingBlock[i].m_strOrigSent<<'\n';
			(*resultfile)<<(LPCTSTR)m_DoingBlock[i].m_strSentence<<'\n';
			(*resultfile)<<(LPCTSTR)m_DoingBlock[i].m_strPairs<<'\n';
		}
		resultfile->close();
		delete resultfile;
	}
			

    CFileDialog dlg(TRUE,"txt","*.txt");
	if(dlg.DoModal()==IDOK)
	{
        long num=0;
	    CRect rc;
	    CString str;
//		if(!outfilepath.IsEmpty())  //open a new file, delete the output file's directory
//			outfilepath.Empty();

	    filepath=dlg.GetPathName();
		prefilepath=filepath;
        
//�˴�����ifstream����һ������ֻ����һ���ļ�����
		checkfile=new ifstream((LPCTSTR)filepath);
		if(!checkfile->is_open())
		{
			AfxMessageBox("Can't open!");
			return;
		}
//		vec_file.clear();
        CString path=filepath+".bak";
		resultfile=new ofstream((LPCTSTR)path);
		if(!resultfile->is_open())
		{
			AfxMessageBox("Can't open the file for bak!");
			return;
		}
//		CMainFrame *pMainFrame=(CMainFrame*)this->GetParent()->GetParent();
		m_nCurrentRow=0;
		m_nLastRow=0;
//		while(checkfile->getline(line,1000))
		while(getline(*checkfile,sentence))
		{ 
//          sentence.erase();
//		    sentence=line;
			(*resultfile)<<sentence<<'\n';//���Ƚ���ע�ļ�����
			//if(sentence.empty())
			//{
			//	MessageBox("�ļ����п���!");
			//	return;
			//} Changed by Carl at 2002.10.29 16:17
			if(num%3==0)
//                vec_file.push_back(sentence);  //ֻȡÿ���ǰ����
                 m_DoingBlock[m_nCurrentRow].m_strOrigSent=sentence.c_str();
			if(num%3==1)                    //ֻȡÿ��ĺ����� 
			{
//				vec_sourcefile.push_back(sentence);
                 m_DoingBlock[m_nCurrentRow].m_strSentence=sentence.c_str();
//		         if(DealWithSentence(num))
//				     vec_file.push_back(sentence);
//				 else 
//				 {
//					vec_file.clear();
//					return;
//				 }
			
			}
			if(num%3==2)
			{
				m_DoingBlock[m_nCurrentRow].m_strPairs=sentence.c_str();
				m_nCurrentRow++;
				m_nLastRow++;
			}
			num++;
          }
        checkfile->close(); 
		resultfile->close();
		delete checkfile;
		delete resultfile;
		m_bBegin=TRUE;
        m_nCurrentRow=0;
		numofsentence=1;
//      PrepareSentence(1);
		pWnd2->Invalidate();
		pWnd2->InitPairAndWord();
	}
		
}

void CMainFrame::OnSave() 
{
	// TODO: Add your command handler code here
//	outfilepath="E:\\E_Documents\\��׼���Լ�\\tts265_�����ע���.txt";
    CString path=filepath;
	int pos = path.Find(".txt");
	path = path.Left(pos) + "_results.txt";
	resultfile=new ofstream((LPCTSTR)path);
	if(!resultfile->is_open())
	{
		MessageBox("Can't Open the file!");
		return;
	}
	for(int i=0;i<m_nLastRow;i++)
	{
//		(*resultfile)<<vec_file[i*2]<<'\n';//�����еĵ�һ�䣬�޸Ĵ��Ա�Ǻ󣬲��ܸı䣬�ʲ����
		(*resultfile)<<(LPCTSTR)m_DoingBlock[i].m_strOrigSent<<'\n';
		(*resultfile)<<(LPCTSTR)m_DoingBlock[i].m_strSentence<<'\n';
		(*resultfile)<<(LPCTSTR)m_DoingBlock[i].m_strPairs<<'\n';
	}
	resultfile->close();
	delete resultfile;
}

void CMainFrame::OnFirst() 
{
	// TODO: Add your command handler code here
//	CMainFrame *pMainFrame=(CMainFrame*)this->GetParent()->GetParent();
  	CWdCheckView *pWnd2=(CWdCheckView*)m_wndSplitter.GetPane(1,0);
	SaveCurrent();
    CheckArc();
//	CheckSentence();
//	if(mb_result==6)
	{
//		PrepareSentence(1);
		numofsentence = 1;
		Invalidate();
//		mb_result=0;
		m_nCurrentRow=0;
		pWnd2->InitPairAndWord();
	}
}

void CMainFrame::OnLast() 
{
	// TODO: Add your command handler code here
//	CMainFrame *pMainFrame=(CMainFrame*)this->GetParent()->GetParent();
  	CWdCheckView *pWnd2=(CWdCheckView*)m_wndSplitter.GetPane(1,0);
	SaveCurrent();
    CheckArc();
//	CheckSentence();
//	if(mb_result==6)
	{
//		PrepareSentence(vec_file.size()-1);
		numofsentence = m_nLastRow;
		Invalidate();
//		mb_result=0;
		m_nCurrentRow=m_nLastRow-1;
		pWnd2->InitPairAndWord();
	}
	
}

void CMainFrame::OnPre() 
{
	// TODO: Add your command handler code here
//	CMainFrame *pMainFrame=(CMainFrame*)this->GetParent()->GetParent();
  	CWdCheckView *pWnd2=(CWdCheckView*)m_wndSplitter.GetPane(1,0);
	SaveCurrent();
    CheckArc();
//	CheckSentence();
//	if(mb_result==6)
	{
//		PrepareSentence(numofsentence-2);
		numofsentence -- ;
		Invalidate();
//		mb_result=0;
		m_nCurrentRow--;
		pWnd2->InitPairAndWord();
	}
}

void CMainFrame::OnNext() 
{
	// TODO: Add your command handler code here
//	CMainFrame *pMainFrame=(CMainFrame*)this->GetParent()->GetParent();
  	CWdCheckView *pWnd2=(CWdCheckView*)m_wndSplitter.GetPane(1,0);
	SaveCurrent();
    CheckArc();
//	CheckSentence();
//	if(mb_result==6)
	{

//		PrepareSentence(numofsentence+2);
		numofsentence ++;
		Invalidate();
//		mb_result=0;
		m_nCurrentRow++;
		pWnd2->InitPairAndWord();
	}
}

void CMainFrame::OnGo() 
{
	// TODO: Add your command handler code here
   	CWdCheckView *pWnd2=(CWdCheckView*)m_wndSplitter.GetPane(1,0);
 	SaveCurrent();
    CheckArc();
//	CheckSentence();
//	if(mb_result==6)//���ִʺʹ��Ա�ע�Ľ��
	{
	    CgoDialog godlg;
	    if(godlg.DoModal()==IDOK)
		{
		    if((godlg.m_numsen<=0)||((int)godlg.m_numsen>m_nLastRow))
			{
			    MessageBox("��������ֲ�����!");
			    return;
			}
//	        PrepareSentence(godlg.m_numsen*2-1);
		    Invalidate();
//			mb_result=0;
			m_nCurrentRow = godlg.m_numsen-1;
			numofsentence = godlg.m_numsen;
			pWnd2->InitPairAndWord();
		}
	}
	
}

//��¼��ע����������������
void CMainFrame::OnQuestion() 
{
	// TODO: Add your command handler code here
	CQuestionDlg qdlg;
	if(qdlg.DoModal()==IDOK)
	{
		CString strQuestion = qdlg.m_question;
		CString path=filepath;
		int pos = path.Find(".txt");
		path = path.Left(pos) + "_labelingquestions.txt";
		resultfile=new ofstream((LPCTSTR)path,ios::app);
		resultfile->seekp(0,ios::end);
		(*resultfile)<<endl<<"==================No."<<m_nCurrentRow+1<<"================"<<'\n';
		(*resultfile)<<(LPCTSTR)m_DoingBlock[m_nCurrentRow].m_strSentence << '\n';
		(*resultfile)<<(LPCTSTR)strQuestion<<'\n';
		resultfile->close();
		delete resultfile;
	}
}

void CMainFrame::OnUpdateFirst(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(!(vec_file.empty())&&(!(numofsentence==1)));
	pCmdUI->Enable((!(numofsentence==1)));
}

void CMainFrame::OnUpdateLast(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(!(vec_file.empty())&&(!(numofsentence==m_nLastRow-1)));
	pCmdUI->Enable((!((int)numofsentence==m_nLastRow)));
}

void CMainFrame::OnUpdatePre(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(!(vec_file.empty())&&(!(numofsentence==1)));
	pCmdUI->Enable((!(numofsentence==1)));
}

void CMainFrame::OnUpdateNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(!(vec_file.empty())&&(!(numofsentence==m_nLastRow-1)));
	pCmdUI->Enable((!((int)numofsentence == m_nLastRow)));
}

void CMainFrame::OnUpdateGo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	pCmdUI->Enable(!(vec_file.empty())&&(!vec_file.empty()));
	pCmdUI->Enable(m_nLastRow > 0);
}

void CMainFrame::OnUpdateOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnUpdateSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_bBegin);

}

//////////////////////////////////////////////////////////////////////////

//�ڸ���λ�������ӻ�ɾ��������
bool CMainFrame::BasicPhrase(int nLeftPos, int nRightPos)
{
	if(nLeftPos == nRightPos)//���ͬһ����
		return 0;
	else if(nLeftPos > nRightPos)//����λ�ã�С����ǰ
	{
		int nTemp = nLeftPos;
		nLeftPos = nRightPos;
		nRightPos = nTemp;
	}
	CString strSent = m_DoingBlock[m_nCurrentRow].m_strOrigSent;
	int pos1 = FindPosition(strSent,nLeftPos);
	int pos2 = FindPosition(strSent,nRightPos);
	if(pos1 == -1 || pos2 == -1)
		return 0;
	//��λ������ұ߽�
	int pos = strSent.Find(' ',pos2);
	if(strSent.Find(']',pos2) != -1 && strSent.Find(']',pos2) < pos)
		pos2 = strSent.Find(']',pos2);
	else
		pos2 = pos;
	if(strSent[pos2] == ']' && strSent[pos2+1] > 'a')
	{
		AfxMessageBox("����ɾ��ԭ��ı�ǣ�");
		return 0;
	}
	if( strSent[pos1] == '[' && strSent[pos2] == ']')//delete mark
	{
		int pos = strSent.Find(' ',pos2);
		strSent.Delete(pos2,pos-pos2);
		strSent.Delete(pos1,1);
		m_DoingBlock[m_nCurrentRow].m_strOrigSent = strSent;
		Invalidate();
		return 0;
	}
	if( strSent[pos1] != '[' && strSent[pos2] != ']')//add mark
	{
		strSent.Insert(pos2,"]");
		strSent.Insert(pos1,"[");
		m_DoingBlock[m_nCurrentRow].m_strOrigSent = strSent;
		Invalidate();
		return 1;
	}
	else
		return 0;//��ƥ��
}

int CMainFrame::FindPosition(CString strSent, int nPos)
{
	int nNum = 1;
	int	pos = -1;
	while(nNum < nPos)
	{
		pos = strSent.Find(' ',pos+1);
		nNum++;
	}
	return pos+1;
}

//���Ӷ�����
void CMainFrame::BasicPhrase(int nLeftPos,int nRightPos,CString strPhrase)
{
	if(nLeftPos > nRightPos)//����λ�ã�С����ǰ
	{
		int nTemp = nLeftPos;
		nLeftPos = nRightPos;
		nRightPos = nTemp;
	}
	CString strSent = m_DoingBlock[m_nCurrentRow].m_strOrigSent;
	int pos1 = FindPosition(strSent,nRightPos);
	int pos2 = strSent.Find(' ',pos1);
	strSent.Insert(pos2,strPhrase);
	m_DoingBlock[m_nCurrentRow].m_strOrigSent = strSent;
	Invalidate();
}

//�����ַ���strSent�к���ĳһ�ַ�str�ĸ���
int CMainFrame::Count(CString strSent, CString str)
{
	int pos = strSent.Find(str);
	int count = 0;
	while(pos != -1)
	{
		count++;
		pos = strSent.Find(' ',pos+1);
	}
	return count;
}

//����һ�������е�����ʵ�弰��־�滻�ڶ��������е���Ӧ�ɷ�
void CMainFrame::KeepBracket(CString strSentWithBracket, CString& strSent)
{
	CString strPhrase,strPhraseAndMark;
	int pos1,pos2;
	pos1 = strSentWithBracket.Find('[');
	while(pos1 != -1)
	{
		pos2 = strSentWithBracket.Find(']',pos1);
		strPhrase = strSentWithBracket.Mid(pos1+1,pos2-pos1-1);
		pos2 = strSentWithBracket.Find(' ',pos2);
		strPhraseAndMark = strSentWithBracket.Mid(pos1,pos2-pos1);
		strSent.Replace(strPhrase,strPhraseAndMark);
		pos1 = strSentWithBracket.Find('[',pos2);
	}
}

void CMainFrame::OnClassify() 
{
	// TODO: Add your command handler code here
	CString strSent = m_DoingBlock[m_nCurrentRow].m_strOrigSent;
	if(strSent[0] == '*')
	{
		strSent = strSent.Mid(1,strSent.GetLength()-1);
		m_DoingBlock[m_nCurrentRow].m_strOrigSent = strSent;
//		AfxMessageBox("�Ѿ�ɾ�����淶��ǣ�");
	}
	else
	{
		strSent = '*' + strSent;
		m_DoingBlock[m_nCurrentRow].m_strOrigSent = strSent;
	}
	CWdCheckView *pWnd2 = (CWdCheckView*)m_wndSplitter.GetPane(1,0);
	pWnd2->Invalidate();
}
