// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E0335B28_C8C0_4262_8C8C_6EBE8613D769__INCLUDED_)
#define AFX_MAINFRM_H__E0335B28_C8C0_4262_8C8C_6EBE8613D769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// This data is from Car's programme
const int g_nBlock =100000;

#include "Block.h"
#include "PairArray.h"
#include "WordArray.h"
#include "CheckAre.h"
#include "Relation.h"
#include "goDialog.h"



class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	void ActivateFrame(int nCmdShow);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// These data is from Car's program
public:
	int FindPosition(CString strSent,int nPos);
	bool BasicPhrase(int nLeftPos,int nRightPos);
	void BasicPhrase(int nLeftPos,int nRightPos,CString strPhrase);
	void AppendRelation(CPair &mypair,vector < CPair > &vecPair,bool bTag);
	void WriteFile(ofstream &fout, vector < CPair > &vecPair,bool bTag);
	void WriteRelation();
	void ReadFile(ifstream &fin, vector < CPair > &vecPair);
	void ReadRelation();
	void OnChange();

	CString MyCheck(CString strPair,CString strRel);
	BOOL CheckArc(CString strSentence, CString strPairs);
	BOOL CheckArc();
	void SaveCurrent();
	CSplitterWnd m_wndSplitter;
	CBlock m_DoingBlock[g_nBlock];
	CRelation m_relation;
	CString m_strFileName;
	CPairArray m_PairArray;
	CWordsArray m_WordArray;
	vector < CPair > vecTagPair,vecWordPair;
	bool m_bBegin;
	int m_nLastRow;
	int m_nCurrentRow;

//////////////////////////////////////////////////////////////////////////
//从CWdCheckView中移过来
	CString prefilepath;
	CString outfilepath;
	ofstream *resultfile;
//	vector<string>vec_file;  //当前文件
	vector<string>vec_sourcefile;  //保存初始文件，去掉每句话的第一句。
	CString filepath; //use by other file
   	ifstream *checkfile;
    char line[2000];
	string sentence; 
    unsigned  numofsentence;
//////////////////////////////////////////////////////////////////////////

// end
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnDelete();
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
	afx_msg void OnButtonchange();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnFirst();
	afx_msg void OnLast();
	afx_msg void OnPre();
	afx_msg void OnNext();
	afx_msg void OnGo();
	afx_msg void OnQuestion();
	afx_msg void OnClassify();
	afx_msg void OnUpdateFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePre(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void KeepBracket(CString strSentWithBracket, CString& strSent);
	int Count(CString strSent, CString str);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E0335B28_C8C0_4262_8C8C_6EBE8613D769__INCLUDED_)
