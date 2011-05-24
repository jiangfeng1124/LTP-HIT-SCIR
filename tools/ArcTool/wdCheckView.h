// wdCheckView.h : interface of the CWdCheckView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WDCHECKVIEW_H__90425A67_204F_4550_8D66_2610B4E0A901__INCLUDED_)
#define AFX_WDCHECKVIEW_H__90425A67_204F_4550_8D66_2610B4E0A901__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <fstream>
#include <string>
#include <vector>

using namespace std;


class CWdCheckDoc;

class CWdCheckView : public CScrollView
{
protected: // create from serialization only

	DECLARE_DYNCREATE(CWdCheckView)

// Attributes
public:
	CWdCheckDoc* GetDocument();
	CWdCheckView();   //原是protected，为了在CMainFrame中定义View类的对象，故改
// Operations
public:
//	inline BOOL GetModify() { return b_modified; }
//	inline CString& GetofPath() { return outfilepath; }
//	inline ofstream* GetResultFile() { return resultfile; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWdCheckView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetWord(char *line);  //Get the word in the dictionary,not include the expression
//	void PrepareSentence(long numofsen);
	virtual ~CWdCheckView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	unsigned size_sour,size_cut;
    unsigned  numofsentence;
	BOOL b_load;  //

//	CString filepath; //use by other file
//  ifstream *checkfile;
//	ifstream *dicfile;
//  char line[2000];
//	string sentence; 
//	char sour_sen[2000];
//	char cut_sen[2000];
//
//	vector<int>vec_number;  //菜单上的数字
//	vector<int>vec_space;  //空格的位置
//	vector<string>vec_dic;  //词典 Init in OnLoad();
//  vector<string>vec_dicpos;  //词性词典 Init in OnLoad();
//	vector<string>vec_wordandpos;  //当前句子的每一个词及词性  //Init in SeperateSentence();
//	vector<string>vec_find_word;  //在InitWordAndPos中初始化,字典中以该字开头的所有词
//	vector<string>vec_find_pos;   //在InitWordAndPos中初始化，字典中以该字开头的所有词的词性,含有两词性之间的'/'
//	vector<string>vec_menuword;   //vec_find_word中在句子中的词
//	vector<string>vec_menupos;    //show when Right Button Down ;not include '/'; Init in GetFindPos()
//    CPoint menupoint;
//	int height;      //记录句子显示的y坐标
//	int menuID;      //the menu return ID;
//   //the return result of MessageBox 
//	int menupos;     //the number of the words clicked by Mouse,Init when mouse was clicked;

public:
	void InitPairAndWord();
	CFont m_font;
	int mb_result;
//	vector<string>vec_word;  //当前句子的每一个词  Init in SeperateSentence()
//	vector<string>vec_pos;   //当前句子的每一个词的词性,含'/', Init in SeperateSentence()
//	BOOL IsChinaPos(string& str);
//	BOOL IsWestChar(string &str);
//	string GetPos(string& pos);
//	void ReNewCurrent();
//	BOOL DealWithSentence(int number);
//	void CheckSentence();
//	void DealWithRMenu();
//	void DealWithLMenu();
//	void InitFindWordAndPos(int menupos);   //每次点击鼠标时，获得与该词匹配的所有词及词性
//	void GetFindPos(int nummenu);
//	void RDisplayMenu(int menupos,long x,long y);
//	void RDecideMenuPt(CPoint point);
//	void LDecideMenuPt(CPoint point);
//	void LDisplayMenu(int menupos,long x,long y);
//	void SeperateSentence();
//	BOOL b_modified;
//	CString prefilepath;
//	CString outfilepath;
//	ofstream *resultfile;
//	vector<string>vec_file;  //当前文件
//	vector<string>vec_sourcefile;  //保存初始文件，去掉每句话的第一句。
// Generated message map  functions
protected:

	//{{AFX_MSG(CWdCheckView)
//	afx_msg void OnOpen();
//	afx_msg void OnSave();
//	afx_msg void OnFirst();
//	afx_msg void OnLast();
//	afx_msg void OnPre();
//	afx_msg void OnNext();
//	afx_msg void OnGo();
//	afx_msg void OnLoad();
//	afx_msg void OnUpdateFirst(CCmdUI* pCmdUI);
//	afx_msg void OnUpdateLast(CCmdUI* pCmdUI);
//	afx_msg void OnUpdatePre(CCmdUI* pCmdUI);
//	afx_msg void OnUpdateNext(CCmdUI* pCmdUI);
//	afx_msg void OnUpdateGo(CCmdUI* pCmdUI);
//	afx_msg void OnUpdateOpen(CCmdUI* pCmdUI);
//	afx_msg void OnUpdateSave(CCmdUI* pCmdUI);
//	afx_msg void OnUpdateLoad(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in wdCheckView.cpp
inline CWdCheckDoc* CWdCheckView::GetDocument()
   { return (CWdCheckDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WDCHECKVIEW_H__90425A67_204F_4550_8D66_2610B4E0A901__INCLUDED_)
            
