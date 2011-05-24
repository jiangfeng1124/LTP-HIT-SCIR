  // wdCheckView.cpp : implementation of the CWdCheckView class
//
#include "stdafx.h"
#include "wdCheck.h"
#include "goDialog.h"
#include "wdCheckDoc.h"
#include "IsSaveDlg.h"
#include "MainFrm.h"
#include "Block.h"
#include "SentenceView.h"
#include "wdCheckView.h"
#include "ArcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWdCheckView

IMPLEMENT_DYNCREATE(CWdCheckView, CScrollView)

BEGIN_MESSAGE_MAP(CWdCheckView, CScrollView)
	//{{AFX_MSG_MAP(CWdCheckView)
//	ON_COMMAND(ID_SAVE, OnSave)
//	ON_COMMAND(ID_FIRST, OnFirst)
//	ON_COMMAND(ID_LAST, OnLast)
//	ON_COMMAND(ID_PRE, OnPre)
//	ON_COMMAND(ID_NEXT, OnNext)
//	ON_COMMAND(ID_GO, OnGo)
//	ON_COMMAND(ID_LOAD, OnLoad)
//	ON_COMMAND(ID_OPEN, OnOpen)
//	ON_UPDATE_COMMAND_UI(ID_FIRST, OnUpdateFirst)
//	ON_UPDATE_COMMAND_UI(ID_LAST, OnUpdateLast)
//	ON_UPDATE_COMMAND_UI(ID_PRE, OnUpdatePre)
//	ON_UPDATE_COMMAND_UI(ID_NEXT, OnUpdateNext)
//	ON_UPDATE_COMMAND_UI(ID_GO, OnUpdateGo)
//	ON_UPDATE_COMMAND_UI(ID_OPEN, OnUpdateOpen)
//	ON_UPDATE_COMMAND_UI(ID_SAVE, OnUpdateSave)
//	ON_UPDATE_COMMAND_UI(ID_LOAD, OnUpdateLoad)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWdCheckView construction/destruction

CWdCheckView::CWdCheckView()
{
	// TODO: add construction code here
//	b_load=FALSE;
//	resultfile=NULL;
//	checkfile=NULL;
//	b_modified=FALSE;
	mb_result=0;
//	menuID=0;
//	menupos=0;
}

CWdCheckView::~CWdCheckView()
{
}

BOOL CWdCheckView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx =5000; sizeTotal.cy = 500;
	SetScrollSizes(MM_TEXT, sizeTotal);

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWdCheckView drawing

void CWdCheckView::OnDraw(CDC* pDC)
{
	CWdCheckDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->SetMapMode(MM_TEXT);


	CFont font;
	font.CreateFont(
		18,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"����");
	CFont *pOldFont=pDC->SelectObject(&font);  //test

	CMainFrame *pMainFrame=(CMainFrame*)this->GetParent()->GetParent();
//	if(!pMainFrame->vec_file.empty())
	if(pMainFrame->m_nLastRow > 0)
	{	
	    CRect rc;
	    CString str;
	    GetClientRect(&rc);
		int height;      //��¼������ʾ��y����
    	height=(rc.bottom-rc.top)/5;
	    str.Format("��ǰ��ʾ���ǵ� %ld ��",pMainFrame->m_nCurrentRow+1);
		string strTemp = pMainFrame->m_DoingBlock[pMainFrame->m_nCurrentRow].m_strOrigSent;
	    pDC->TextOut(5,height*1,strTemp.c_str());//,size_cut);
//	    str.Format("��ǰ��ʾ���ǵ� %ld ��",(pMainFrame->numofsentence+1)/2);
//	    pDC->TextOut(330,height,str);
//	    pDC->TextOut(30,height*2,sour_sen,size_sour);
//	    pDC->TextOut(30,height*3,cut_sen,size_cut);

//ȥ��ÿ����ǰ�ı��
//		string strTemp = cut_sen;
//		string strTemp = pMainFrame->m_DoingBlock[pMainFrame->m_nCurrentRow].m_strSentence;
//		int pos1 = strTemp.find('[');
//		while(pos1 != -1)
//		{
//			int pos2 = strTemp.find(']',pos1);
//			strTemp.erase(pos1,pos2-pos1+1);
//			pos1 = strTemp.find('[');
//		}
//	    pDC->TextOut(0,height*1,strTemp.c_str());//,size_cut);
	}
		
	pDC->SelectObject(pOldFont);

}  

/////////////////////////////////////////////////////////////////////////////
// CWdCheckView diagnostics

#ifdef _DEBUG
void CWdCheckView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CWdCheckView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWdCheckDoc* CWdCheckView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWdCheckDoc)));
	return (CWdCheckDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWdCheckView message handlers
void CWdCheckView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class


	m_font.CreateFont(
		18,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"����");
	

}


void CWdCheckView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//    int menupos; //��ǰ��ʾ���ǵ�menupos���ʵĲ˵���
//    LDecideMenuPt(point);
//	if(menuID>0)
//	{
//		DealWithLMenu();
//		menuID=0;
//	}
	CScrollView::OnLButtonDown(nFlags, point);

}

void CWdCheckView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	menuID=0;
//	RDecideMenuPt(point);
//	if(menuID>0)
//	{
//		DealWithRMenu();
//		menuID=0;
//	}
	CScrollView::OnRButtonDown(nFlags, point);
}


void CWdCheckView::InitPairAndWord()
{

	CMainFrame *pMainFrame=(CMainFrame*)this->GetParent()->GetParent();
	CArcView *pWnd3=(CArcView *)pMainFrame->m_wndSplitter.GetPane(2, 0);
	pMainFrame->m_PairArray.SetPairArray(pMainFrame->m_DoingBlock[pMainFrame->m_nCurrentRow].m_strPairs);
	pWnd3->Invalidate();

	pMainFrame->m_WordArray.SetWordArray(pMainFrame->m_DoingBlock[pMainFrame->m_nCurrentRow].m_strSentence);  //�ʣ�ÿ�仰�ĵڶ���
	CSentenceView *pWnd1 = (CSentenceView *)pMainFrame->m_wndSplitter.GetPane(0,0);
	pWnd1->m_editSentence.SetWindowText(pMainFrame->m_DoingBlock[pMainFrame->m_nCurrentRow].m_strSentence);

}


/*
void CWdCheckView::PrepareSentence(long numofsen)
{
	unsigned i;
	numofsentence=numofsen;
	for(i=0;i<1000;i++)
	{
	    sour_sen[i]=0;
	    cut_sen[i]=0;
	}
	sentence.erase();
    sentence=vec_file[numofsen-1];
    for(i=0;i<sentence.size();i++)
	{
		sour_sen[i]=sentence[i];
		size_sour=i+1;
	}
	sentence.erase();
	sentence=vec_file[numofsen];
    for(i=0;i<sentence.size();i++)
	{
		cut_sen[i]=sentence[i];
		size_cut=i+1;
	}
}


void CWdCheckView::GetWord(char *line)
{
	int i;
	for(i=0;i<2000;i++)
	{
		if(line[i]=='#')
			size_cut=i+1;
		if(line[i]=='*')
		{
			size_sour=i-1;
			break;
		}
	}
	
}

void CWdCheckView::ReNewCurrent()
{
	CString strSentence;
	CString strTemp;
	int i;
	for(i = 0; i <(int) vec_wordandpos.size(); i++){
	    strSentence += "[";
		strTemp.Format("%d", i+1);
		strSentence +=strTemp+ "]"+
			vec_wordandpos[i].c_str()+" ";
	}
	strTemp.Format("%d",i+1);
	strSentence+="["+strTemp+"]"+"<EOS>/<EOS>";
	CMainFrame *pMainFrame=(CMainFrame*)this->GetParent()->GetParent();
	CSentenceView *pWnd1=(CSentenceView*)pMainFrame->m_wndSplitter.GetPane(0,0);
	pWnd1->m_editSentence.SetWindowText(strSentence);
	pMainFrame->OnChange();
}

*/
/*
void CWdCheckView::SeperateSentence()
{
//	vector<string> wordandpos;
    vec_word.clear();
	vec_pos.clear();
	vec_wordandpos.clear();
	vec_space.clear();
//	TRACE("%d,%d\n",vec_menuword.size(),vec_menupos.size());
  
	string word;
	int i,j=0;
	int k;
	sentence.erase();
    sentence=vec_file[numofsentence];
	for(i=0;i<(int)sentence.size();i++)    //�����еĴʷֿ�(�ӿո�ֿ�)
	{
		if(sentence.at(i)==' ')
		{
			vec_space.push_back(i);
			word.erase();
			if(j==0)
			{
			    for(k=j;k<i;k++)
				{
				    word+=sentence.at(k);
				}
			}
			else
			    for(k=j+1;k<i;k++)
				{
					word+=sentence.at(k);
				}
			string str=word; //test
			vec_wordandpos.push_back(word);
			j=i;
  
		}
	
	}

		
////
	int size=(int)vec_wordandpos.size(); //test
	for(i=0;i<(int)vec_wordandpos.size();i++) //��ÿ����������Էֿ�
	{

//		char c1,c2=0;
		string str;
		word.erase();
		str.erase();
		word=vec_wordandpos[i];

		string::size_type npos=-1;
		k=word.find_last_of('/');
		if(k==(int)npos)
			k=(int)word.size();
		for(j=0;j<k;j++)
		{
			str+=word.at(j);  //����
		}
//		int size=str.size();
//////////////
		if(str.at(0)=='\\')
		{
			string::size_type pos,pre_pos;
			pre_pos=pos=0;
			string str_copy=str;
			str.erase();
			while((pos=str_copy.find_first_of('\\',pos))!=-1)
			{
				string::size_type lpos=str_copy.find_last_of('\\');
	            str+=str_copy.substr(pre_pos,pos-pre_pos);
				
				if(pos==lpos)
				{
					str+=str_copy.substr(pos+1,str_copy.size());
					break;
				}
                pre_pos=++pos;
			
			}
		}
/////////////
		vec_word.push_back(str);
		str.erase();
		str=word.substr(k,word.size());  //����
		vec_pos.push_back(str);
		
		
	}
}

void CWdCheckView::LDecideMenuPt(CPoint point)
{
	if(!vec_file.empty())
	{
			
	     	long x,y;
            int h,w;
			long menu_x, menu_y;
			x=point.x;
			y=point.y;
			menu_x=x;
			menu_y=y;

			CPoint pt=GetScrollPosition( );
			menupoint=pt;
			x+=pt.x; y+=pt.y;
    		CDC *pDC=GetDC();
			CFont *pOldFont=pDC->SelectObject(&m_font);
			CSize size;
		
			char a[]=" ";
			size=pDC->GetTextExtent(a,1);
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			h=size.cy;
			w=size.cx;
			CRect rc;
			GetClientRect(&rc);
			height=(rc.bottom-rc.top)/5;
   		if(height*3<y &&y<height*3+h)
		{
            SeperateSentence();
			for(int i=0;i<(int)vec_space.size()-1;i++) //�����ʵĲ˵���
				                                       //���ε����ı�����
			{
				if(i==0)
				{
					
				    if(30<x&&x<vec_space[0]*w+30)
					{
						menupos=i;
						LDisplayMenu(0,menu_x,height*3+h-pt.y);
					}
				}
				if(i==(int)vec_space.size()-1)
				{
					if(30+vec_space[i-1]*w+w<x&&x<(int)vec_file[numofsentence].
						size()*w+30)
					{
                        menupos=i;
						LDisplayMenu(vec_space.size(), menu_x,height*3+h-pt.y);
					}
				}
				if(i>0&&30+vec_space[i-1]*w+w<x&&x<
					vec_space[i]*w+30)
				{
					menupos=i;
					LDisplayMenu(i, menu_x,height*3+h-pt.y);
				}
			}

//	    DealWithLMenu();
		}

	}

}

void CWdCheckView::LDisplayMenu(int menupos,long x,long y)
{
	
	if(IsWestChar(vec_word[menupos])||IsChinaPos(vec_word[menupos]))
		return;
	int num=menupos;
	int nID=100;
    InitFindWordAndPos(menupos);

//////////vec_find_word
	string::size_type npos=-1;


///////////////////��ʾ�˵�///////////////////////////////////
     CMenu menu;
	 menu.CreatePopupMenu();
	 CPoint point(x,y);
	 ClientToScreen(&point);
     for(int i=0;i<(int)vec_menuword.size();i++)
	 {
	     menu.AppendMenu(MF_STRING|MF_ENABLED,nID++,
		 vec_menuword[i].c_str());
	 }
	 int size=(int)vec_wordandpos.size(); //test;
	 vec_number.clear();
     int k=menupos+1;
	 for(i=1;i<(int)vec_wordandpos.size()-1-menupos;i++)
	 {  
        if(IsWestChar(vec_word[k])||IsChinaPos(vec_word[k])) 
			break;
		char a[1];
		vec_number.push_back(i+1);
		itoa(i+1,a,10);
		menu.AppendMenu(MF_STRING|MF_ENABLED,nID++,a);
		k++;
	 }
	 menuID=menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL|
		 TPM_RETURNCMD,point.x,point.y,this);
     menu.DestroyMenu();

}

void CWdCheckView::RDecideMenuPt(CPoint point)
{
    if(!vec_file.empty())
	{
		
        long x,y;
		long menu_x, menu_y;
		x=point.x;
		y=point.y;
		menu_x=x;
		menu_y=y;

		CPoint pt=GetScrollPosition( );
//		menupoint=pt;
		x+=pt.x; y+=pt.y;
    	CDC *pDC=GetDC();
		CFont *pOldFont=pDC->SelectObject(&m_font);
		CSize size;
		int h,w;
		char a[]=" ";
		size=pDC->GetTextExtent(a,1);
		pDC->SelectObject(pOldFont);
		ReleaseDC(pDC);
		h=size.cy;
		w=size.cx;

   		if(height*3<y&&y<height*3+h)
		{
            SeperateSentence();
			for(int i=0;i<(int)vec_space.size();i++) //�����ʵĲ˵���
				                                     //���ε����ı�����
			{                                        //�˴�������
				if(i==0)
				{
				    if(30<x&&x<vec_space[0]*w+30)
					{	
						menupos=i;
						RDisplayMenu(i,menu_x,height*3+h-pt.y);
					}
				}
//				if(i==(int)vec_space.size()-1)
//				{
//					if(30+w+w*vec_space[vec_space.size()-2]<
//						x&&x<(int)vec_file[numofsentence].
//						size()*w+30)
//					{   
//						menupos=i;
//						RDisplayMenu(vec_space.size()-1,menu_x,height*3+h-pt.y);
//					}
//				}
				if(i>0&&30+vec_space[i-1]*w+w<x&&x<
					vec_space[i]*w+30)
				{
					menupos=i;
					RDisplayMenu(i,menu_x,height*3+h-pt.y);
				}
			}
//        	DealWithRMenu();
		}

	   
	}
	
}

void CWdCheckView::RDisplayMenu(int menupos, long x, long y)
{
	BOOL b_ready=FALSE;
	if(IsChinaPos(vec_word[menupos]))
	{
		vec_menupos.clear();
		for(int i=10;i<20;i++)
			vec_menupos.push_back(vec_dicpos[i]);
		b_ready=TRUE;
		
	}
	if(IsWestChar(vec_word[menupos]))
	{
		if(!IsWestChar(vec_word[menupos+1]))
		{
			vec_menupos.clear();
			for(int i=0;i<10;i++)
				vec_menupos.push_back(vec_dicpos[i]);
			b_ready=TRUE;
		}
		else
			return;
	}

    if(!b_ready)
		GetFindPos(menupos);
	CMenu menu;
    int nID=100;
	menu.CreatePopupMenu();
	CPoint point(x,y);
	ClientToScreen(&point);
    for(int i=0;i<(int)vec_menupos.size();i++)
	{
		string str=vec_menupos[i]; //test
	    menu.AppendMenu(MF_STRING|MF_ENABLED,nID++,
				vec_menupos[i].c_str());
//       string str=vec_find_pos[i];
	}
	menuID=menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL|
	    TPM_NONOTIFY|TPM_RETURNCMD,point.x,point.y,this);
    menu.DestroyMenu();

}

void CWdCheckView::GetFindPos(int nummenu)
{
	int posindic=-1;
	string word;
    menupos=nummenu;
	InitFindWordAndPos(menupos);
	vec_menupos.clear();
	word=vec_word[menupos];
//    int size7=(int)word.size(); //test
	if(menupos!=(int)vec_word.size()-1)  //����Ĳ��Ǳ�����
	{
			for(int i=0;i<(int)vec_find_word.size();i++)
			{
				if(word==vec_find_word[i])
				{
					posindic=i;
					break;
				}
			}
//		if(pos==npos)
//	        posindic=vec_dic.size()+1;
			if(posindic==-1)
			{
				for(int i=0;i<10;i++)
					vec_menupos.push_back(vec_dicpos[i]); //����ֵ���û��
			}
			else
			{
				int k=0;
				string::size_type pos,npos=-1;
				word.erase();
				word=vec_find_pos[posindic];
				for(int i=0;i<(int)word.size();i++)
				{
					if(word.at(i)=='/')
						k++;
				}
				if(k==0)
				{
//				first=word.find_first_of('\\');
//				string str=word.substr(first+1,word.size());
					vec_menupos.push_back(word);
				}
				if(k==1)
				{

					pos=word.find_first_of('/');
//					string str1,str2; //test
//					str1=word.substr(0,pos); //test
//					str2=word.substr(pos+1,word.size());  //test
					vec_menupos.push_back(word.substr(0,pos));
					vec_menupos.push_back(word.substr(pos+1,word.size()));
				}
				if(k>1)
				{
					string::size_type pre_pos=word.find_first_of('/');

	           
					pre_pos=pos=word.find_last_of('/');
					vec_menupos.push_back(word.substr(pos+1,word.size()));
//					string str=word.substr(pos+1,word.size());  //test
					pre_pos=pos=0;
					while((pos=word.find_first_of('/',pos))!=npos)
					{
				 
//						string str=word.substr(pre_pos,pos-pre_pos);  //test
					    vec_menupos.push_back(word.substr(pre_pos,pos-pre_pos));
					    pre_pos=++pos;
				
					}
				}
			}

		
	}
	if(menupos==(int)vec_word.size()-1)
	{
		for(int i=10;i<20;i++)
			vec_menupos.push_back(vec_dicpos[i]);
	}
}

 void CWdCheckView::InitFindWordAndPos(int menupos)
{	
	long first,next;
	int i;
	first=next=-1;
	string str;
    string strdic;
    BOOL b_isword=FALSE;
	str.erase();
//	string s6=vec_word[menupos];  //test
    str+=vec_word[menupos].at(0);
    if((int)vec_word[menupos].size()>=2)
	{
		str+=vec_word[menupos].at(1);
		b_isword=TRUE;
	}
	vec_find_pos.clear();
	vec_find_word.clear();
	vec_menuword.clear();

///////////�ҳ��ʵ����Ը��ֿ�ͷ�Ĵ�//////////////////////

    unsigned char c1,c2;
	c1=str.at(0);
	if(c1>=176&&b_isword)
	{
	    
//    	c1=str.at(0);
        c2=str.at(1);
	    long begin,mid,last;
		begin=0;last=vec_dic.size()-1;
		BOOL b_found=FALSE;
		while(!b_found)
		{
			strdic.erase();
			mid=(begin+last)/2;
			strdic+=vec_dic[mid].at(0);
			strdic+=vec_dic[mid].at(1);
			if(str<strdic)
				last=mid;
			if(str>strdic)
				begin=mid;
			if(str==strdic)
			{
				first=next=mid;
				b_found=TRUE;
			}
		}
		while(first>-1)
		{
			strdic.erase();
			strdic+=vec_dic[first].at(0);
			strdic+=vec_dic[first].at(1);
			if(str>strdic)
				break;
			else
			{
				vec_menuword.push_back(vec_dic[first]);
				first--;
			}
		}
		while(next>-1&&next<(long)vec_dic.size())
		{
			strdic.erase();
			strdic+=vec_dic[next].at(0);
			strdic+=vec_dic[next].at(1);
			if(str<strdic)
				break;
			else
			{
				next++;
				vec_menuword.push_back(vec_dic[next]);
			}
		}
	}
			

/////////////���ҵ��Ĵ��еĺ�������Էֿ�//////
	for(i=0;i<(int)vec_menuword.size();i++) //��ÿ����������Էֿ�
	{
        int k,j;       
//		char c1,c2=0;
		string word;
		str.erase();
//		word.erase();
		str=vec_menuword[i];

		k=(int)str.find_last_of('\\');
		for(j=0;j<k;j++)
		{
			word+=str.at(j);  //����
		}

		vec_find_word.push_back(word);
		word=str.substr(k+1,str.size());  //����
		vec_find_pos.push_back(word);
	}
//////////vec_find_word
	string::size_type npos=-1;
	vec_menuword.clear();
	string str1;
	string::size_type pos;
	for(int k=menupos;k<(int)vec_word.size();k++)
		str1+=vec_word[k];
	for(i=0;i<(int)vec_find_word.size();i++)
	{
		if((pos=str1.find(vec_find_word[i]))!=npos)
		{
			if(pos==0)
				vec_menuword.push_back(vec_find_word[i]);
		}
	}


}

void CWdCheckView::DealWithLMenu()
{   

		for(int i=0;i<(int)vec_wordandpos.size()-menupos-1+(int)vec_menuword.size();i++)
		{
/////����ʵ����/////////////////////////////////////////
			int size=vec_menuword.size(); //test
			if((menuID==100+i)&&menuID<(100+(int)vec_menuword.size()))  //�����ʽ�˵��ϵĴ�
			{
				if(vec_menuword[i]==vec_word[menupos])  //ѡ�Ĵ����������ͬ��do nothing 
					return;
////�ִ�////////////
				if(vec_menuword[i].length()<vec_word[menupos].length()) //ѡ�Ĵ��Ǿ����еĴʵ�һ����,����һ���ʷֳ�����
				{
					vector<string> vec_wordandpos_copy=vec_wordandpos;
					vector<string> vec_word_copy=vec_word;
					vec_wordandpos.clear();
					string str1,str2;
					str1=vec_menuword[i];
					str2=vec_word_copy[menupos].substr(str1.length(),vec_word_copy[menupos].size());
					for(int j=0;j<menupos;j++)
						vec_wordandpos.push_back(vec_wordandpos_copy[j]);
					string str1pos,str2pos;
					str1pos=GetPos(str1); 
					str2pos=GetPos(str2);
					vec_wordandpos.push_back(str1+'/'+str1pos);
					vec_wordandpos.push_back(str2+'/'+str2pos);
					for(j=menupos+1;j<(int)vec_wordandpos_copy.size();j++)
      					vec_wordandpos.push_back(vec_wordandpos_copy[j]);
					vec_file[numofsentence].erase();
					for(j=0;j<(int)vec_wordandpos.size();j++)
					{
						vec_file[numofsentence]+=vec_wordandpos[j];
//					    if(j!=(int)vec_wordandpos.size()-1)
							vec_file[numofsentence]+=' ';
					}	
///////����vec_word///   
					vec_word.clear();
					for(j=0;j<menupos;j++)
						vec_word.push_back(vec_word_copy[j]);
					vec_word.push_back(str1);
					vec_word.push_back(str2);
					for(j=menupos+1;j<(int)vec_word_copy.size();j++)
						vec_word.push_back(vec_word_copy[j]);
/////////����vec_word����///////////	
					b_modified=TRUE;
					ReNewCurrent();  //����Eidt�ؼ�
					PrepareSentence(numofsentence);
					Invalidate();
				}
/////�ִʵ��˽���///

////////////�ϴ�//////////////
//				string s1,s2;  //test
//				s1=vec_menuword[i];s2=vec_word[menupos];  //test
				if(vec_menuword[i].length()>vec_word[menupos].length())  //��ѡ�ĴʱȾ����еĴ�Ҫ������������ʺ�����������������һ���ʵ�һ���ֺ�����
				{
					 int size,num=0;
					vector<string>vec_wordandpos_copy=vec_wordandpos;
					vector<string>vec_word_copy=vec_word;
					vec_wordandpos.clear();
					size=vec_word[menupos].length();
					while((int)vec_menuword[i].length()>size)
					{
						++num;
						size+=vec_word[menupos+num].length();
					}
////////�ϳ���������///////
					if((int)vec_menuword[i].length()==size)  //�պ����������ʵĴ�С
					{
						string str;
						for(int j=0;j<menupos;j++)
						    vec_wordandpos.push_back(vec_wordandpos_copy[j]);
					    for(j=menupos;j<=menupos+num;j++)
						    str+=vec_word[j];
						string strpos;
						strpos=GetPos(str);
						vec_wordandpos.push_back(str+'/'+strpos);
					    for(j=menupos+num+1;j<(int)vec_wordandpos_copy.size();j++)
						    vec_wordandpos.push_back(vec_wordandpos_copy[j]);
						vec_word.clear();

					    for(j=0;j<menupos;j++)
						    vec_word.push_back(vec_word_copy[i]);
						vec_word.push_back(str);
					    for(j=menupos+1;j<(int)vec_word_copy.size();j++)
						    vec_word.push_back(vec_word_copy[i]);
						  
					}
/////�ϳ��������ʵ��˽���///

/////����������һ���ʵ�һ���ֺϳ�//
					if((int)vec_menuword[i].length()<size)
					{
						string str1,str2;
						for(int j=0;j<menupos;j++)
						    vec_wordandpos.push_back(vec_wordandpos_copy[j]);
						for(j=menupos;j<=menupos+num;j++)
						    str1+=vec_word[j];
						str2=str1.substr(vec_menuword[i].size(),str1.size());
						string strpos1,strpos2;
						strpos1=GetPos(vec_menuword[i]);
						vec_wordandpos.push_back(vec_menuword[i]+'/'+strpos1);
						strpos2=GetPos(str2);
						vec_wordandpos.push_back(str2+'/'+strpos2);
						for(j=menupos+num+1;j<(int)vec_wordandpos_copy.size();j++)
						    vec_wordandpos.push_back(vec_wordandpos_copy[j]);
						vec_word.clear();
///////����vec_word/////////////
						for(j=0;j<menupos;j++)
						    vec_word.push_back(vec_word_copy[j]);
						vec_word.push_back(vec_menuword[i]);
						vec_word.push_back(str2);
						for(j=menupos+num+1;j<(int)vec_word_copy.size();j++)
						    vec_word.push_back(vec_word[j]);
////////����vec_word����//////
					}
//////////////����������һ���ʵ�һ���ֺϳɽ���//
					vec_file[numofsentence].erase();
					b_modified=TRUE;
					for(int j=0;j<(int)vec_wordandpos.size();j++)
					{
						vec_file[numofsentence]+=vec_wordandpos[j];
//						if(j!=(int)vec_file.size()-1)
							vec_file[numofsentence]+=' ';
					}
                    ReNewCurrent();  
					PrepareSentence(numofsentence);
					Invalidate();
				}

			}
///////����ʽ���////

  			if((menuID==100+i)&&menuID>=100+(int)vec_menuword.size())  //�����ʽ�˵��ϵ�����
			{
				int num=menuID-100-(int)vec_menuword.size();
                for(int m=menupos;m<menupos+vec_number[num];m++)
					if(IsWestChar(vec_word[m])||IsChinaPos(vec_word[m]))
						return;
				vector<string>vec_wordandpos_copy=vec_wordandpos;
				vector<string>vec_word_copy=vec_word;
				vec_wordandpos.clear();
				vec_word.clear();
				for(int j=0;j<menupos;j++)
				{
					vec_wordandpos.push_back(vec_wordandpos_copy[j]);
					vec_word.push_back(vec_word_copy[j]);
				}
				string str;
				for(j=menupos;j<menupos+vec_number[num];j++)
					str+=vec_word_copy[j];
				string strpos=GetPos(str);
				vec_wordandpos.push_back(str+'/'+strpos);
				vec_word.push_back(str);
				for(j=menupos+vec_number[num];j<(int)vec_wordandpos_copy.size();j++)
				{
					vec_word.push_back(vec_word_copy[j]);
					vec_wordandpos.push_back(vec_wordandpos_copy[j]);
				}
				vec_file[numofsentence].erase();
				b_modified=TRUE;
				for(j=0;j<(int)vec_wordandpos.size();j++)
				{
					vec_file[numofsentence]+=vec_wordandpos[j];
//					if(j!=(int)vec_wordandpos.size()-1)
						vec_file[numofsentence]+=' ';
				}
				ReNewCurrent();
				PrepareSentence(numofsentence);
				Invalidate();

			}
		}
	
}

void CWdCheckView::DealWithRMenu()
{

	int num=menuID-100;
	if(num>=0)
	{
		vector<string>vec_pos_copy=vec_pos;
        vec_wordandpos.clear();
		vec_pos.clear();
		for(int i=0;i<menupos;i++)
			vec_pos.push_back(vec_pos_copy[i]);
		string str='/'+vec_menupos[num];
		vec_pos.push_back(str);
		for(i=menupos+1;i<(int)vec_pos_copy.size();i++)
			vec_pos.push_back(vec_pos_copy[i]);
		vec_file[numofsentence].erase();
		for(i=0;i<(int)vec_word.size();i++)
		{
			vec_wordandpos.push_back(vec_word[i]+vec_pos[i]);
			vec_file[numofsentence]+=vec_word[i]+vec_pos[i];
//			if(i!=(int)vec_file.size()-1)
				vec_file[numofsentence]+=' ';
		}
		b_modified=TRUE;
		ReNewCurrent();
		PrepareSentence(numofsentence);
		Invalidate();
	}
}

string CWdCheckView::GetPos(string& word)
{
	vector<string>findword;
	string str=word;
	string strdic;
    long position;
	BOOL b_found=FALSE;
	unsigned char c1,c2;

	c1=str.at(0);
	if(c1<161)
	{
		str=vec_dicpos[0];
	}
	if(161<c1&&c1<176)
	{
		 str=vec_dicpos[11];
	}
	long first,next;
	if(c1>=176)
	{
        c2=str.at(1);
		string ch;
		ch+=str.at(0);
		ch+=str.at(1);
	    long begin,mid,last;
		begin=0;last=vec_dic.size()-1;
		while(!b_found)
		{
			strdic.erase();
			mid=(begin+last)/2;
			strdic+=vec_dic[mid].at(0);
			strdic+=vec_dic[mid].at(1);
			if(ch<strdic)
				last=mid;
			if(ch>strdic)
				begin=mid;
			if(ch==strdic)
			{
				first=next=mid;
				b_found=TRUE;
			}
		}
	    while(first>-1)
		{
			strdic.erase();
			strdic+=vec_dic[first].at(0);
			strdic+=vec_dic[first].at(1);
			if(ch>strdic)
				break;
		 	else
			{
				findword.push_back(vec_dic[first]);
				first--;
			}
		}
		while(next>-1&&next<(long)vec_dic.size())
		{
			strdic.erase();
			strdic+=vec_dic[next].at(0);
			strdic+=vec_dic[next].at(1);
			if(ch<strdic)
				break;
			else
			{
				next++;
				findword.push_back(vec_dic[next]);
			}
		}
	}
	BOOL b_in=FALSE;
	string::size_type pos=-1;
	for(int i=0;i<(int)findword.size();i++)
    {
		string s;
		string::size_type pos;
		pos=findword[i].find_first_of('\\');
		s=findword[i].substr(0,pos);
		if(word==s)
		{
  			position=i;
			b_in=TRUE;
			break;
		}
	}
	if(b_in)
	{
		strdic.erase();
		string::size_type pos1,pos2;
		strdic=findword[position];
		pos1=strdic.find_first_of('\\');
		pos2=strdic.find_first_of('/');
		if(pos2==-1)
			str=strdic.substr(pos1+1,strdic.size());
		else
			str=strdic.substr(pos1+1,pos2-pos1-1);
	}
	if(!b_in)
		str=vec_dicpos[0];


	return str;
}

BOOL CWdCheckView::IsWestChar(string &str)
{
	unsigned char c1;
	unsigned int size = str.size();
	if(str.size()>0)
		c1=str.at(0);
	if(c1<161)
		return TRUE;
	else 
		return FALSE;
}

BOOL CWdCheckView::IsChinaPos(string &str)
{
	unsigned char c1;
	if(str.size()>0)
		c1=str.at(0);
	if(161<=c1&&c1<176)
		return TRUE;
	else 
		return FALSE;
	
}
*/

/*
void CWdCheckView::CheckSentence()
{

	SeperateSentence();

////��ǰ���Ƿ��ڴʵ���
    vector<int>vec_word_notin;
	BOOL b_wordin=FALSE;
//	int size1=vec_word.size(); //test
	for(int i=0;i<(int)vec_word.size()-1;i++)
	{
		if(!(IsWestChar(vec_word[i])||IsChinaPos(vec_word[i])))
		{
			InitFindWordAndPos(i);
//		string str=vec_word[i]; //test
			for(int j=0;j<(int)vec_menuword.size();j++)
				if(vec_word[i]==vec_menuword[j])
				{
					b_wordin=TRUE;  break;
				}
		
			if(!b_wordin)
			{
				vec_word_notin.push_back(i);
				b_wordin=FALSE;
			}
			b_wordin=FALSE;
		}
	}
//    int size=vec_word_notin.size(); //test
	string s;   //=vec_word[vec_word_notin[0]]; //test
////��ǰ�εĴ����Ƿ���ʵ���ƥ��
	BOOL b_posin=FALSE;
	vector<int>vec_pos_notin;
	for( i=0;i<(int)vec_word.size();i++)
	{
		if(IsChinaPos(vec_word[i]))
		{   
			vec_menupos.clear();
			for(int m=10;m<20;m++)
				vec_menupos.push_back(vec_dicpos[m]);
		}
		if(IsWestChar(vec_word[i]))
		{
			vec_menupos.clear();
			if(IsWestChar(vec_word[i+1]))
				vec_menupos.push_back("");
			else
				for(int m=0;m<10;m++)
					vec_menupos.push_back(vec_dicpos[m]);
		}
		if(!(IsChinaPos(vec_word[i])||IsWestChar(vec_word[i])))
		    GetFindPos(i);

		string str=vec_pos[i];
		if((int)str.length()>0)
			str=vec_pos[i].substr(1,vec_pos[i].size());
		else
			str="";
		for(int j=0;j<(int)vec_menupos.size();j++)
		{
            string s8=vec_menupos[j];  //test
			if(str==vec_menupos[j])
			{
				b_posin=TRUE;break;
			}
		}
		if(!b_posin)
		{
			vec_pos_notin.push_back(i);
			b_posin=FALSE;
		}
		b_posin=FALSE;
	}
//    size=vec_pos_notin.size();  //test
////��ǰ���Ƿ������
    BOOL b_notlongest=FALSE;
	vector<int>vec_notlongest;
	for( i=0;i<(int)vec_word.size()-1;i++)
	{
		if(!(IsWestChar(vec_word[i])||IsChinaPos(vec_word[i])))
		{
			InitFindWordAndPos(i);
			for(int j=0;j<(int)vec_menuword.size();j++)
				if(vec_word[i].length()<vec_menuword[j].length())
				{
					b_notlongest=TRUE;
					break;
				}
		
			if(b_notlongest)
			{
				vec_notlongest.push_back(i);
				b_notlongest=FALSE;
			}
		}
	}
//	size=vec_notlongest.size(); //test
	string word,pos,longest;
	for( i=0;i<(int)vec_word_notin.size();i++)
	{
		word+="\"";
		word+=vec_word[vec_word_notin[i]];
		word+="\"";
		word+="  ";
	}
	if(!vec_word_notin.empty())
		word+="���ڴʵ���";
	for( i=0;i<(int)vec_pos_notin.size();i++)
	{
		 pos+="\"";
         pos+=vec_word[vec_pos_notin[i]];
		 pos+="\"";
		 pos+="  ";
	}
	if(!vec_pos_notin.empty())
		pos+="  �Ĵ��Բ��ڴʵ���";
	for( i=0;i<(int)vec_notlongest.size();i++)
	{
		longest+="\"";
		longest+=vec_word[vec_notlongest[i]];
		longest+="\"";
		longest+="  ";
	}
	if(!vec_notlongest.empty())
		longest+="  �����ֵ�����Ĵ�";
	CString str;
	str.Format("��ǰ������\n%s\n%s\n%s\n�Ƿ����?",word.c_str(),pos.c_str(),longest.c_str());

	if(vec_word_notin.size()||vec_pos_notin.size()||vec_notlongest.size())
	{
		mb_result=MessageBox((LPCTSTR)str,"ICM Words Check",MB_ICONEXCLAMATION|MB_ICONWARNING|MB_YESNO);
	}
	else
		mb_result=6;


}

BOOL CWdCheckView::DealWithSentence(int number)
{

	//ȷ������ǿո�
    string word;
	int i,j=0,k;
	word=sentence;
	vec_wordandpos.clear();
	string::size_type pos=word.find_last_of('>');

	if(word.at((int)word.size()-1)!='>')
	{
		sentence.erase();
		sentence=word.substr(0,pos);
	}
	vec_space.clear();
	for(i=0;i<(int)sentence.size();i++)    //�����еĴʷֿ�(�ӿո�ֿ�)
	{
		if(sentence.at(i)==' ')
		{
			vec_space.push_back(i);
			word.erase();
			if(j==0)
			{
			    for(k=j;k<i;k++)
				{
				    word+=sentence.at(k);
				}
			}
			else
			    for(k=j+1;k<i;k++)
				{
					word+=sentence.at(k);
				}

			vec_wordandpos.push_back(word);
			j=i;
  
		}
	
	}
    
	for(i=0;i<(int)vec_space.size()-1;i++)
		if(vec_space[i]+1==vec_space[i+1])
		{   
			CString str;
			str.Format("��%ld���к��������Ŀո��޷��������޸�!",number);
			MessageBox(str);
			return FALSE;
		}
	////ȥ��[]���
    vector<string>vec_wordandpos_copy=vec_wordandpos;
	vec_wordandpos.clear();
	for(i=0;i<(int)vec_wordandpos_copy.size();i++)
	{
		word.erase();
		string word_copy;
		word_copy=vec_wordandpos_copy[i];
	    pos=word_copy.find_last_of(']');
		if(pos==-1)
			word=word_copy;
		else
			word=word_copy.substr(pos+1,word_copy.size());
		vec_wordandpos.push_back(word);
	}

	sentence.erase();
	for(i=0;i<(int)vec_wordandpos.size();i++)
		sentence+=vec_wordandpos[i]+' ';

	return TRUE;
}
*/
