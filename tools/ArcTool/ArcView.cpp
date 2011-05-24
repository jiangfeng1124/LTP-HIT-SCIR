                                                        // ArcView.cpp : implementation of the CArcView class
//

#include "stdafx.h"

#include "wdCheck.h"
#include "WdCheckDoc.h"
#include "ArcView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArcView

IMPLEMENT_DYNCREATE(CArcView, CScrollView)

BEGIN_MESSAGE_MAP(CArcView, CScrollView)
	//{{AFX_MSG_MAP(CArcView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArcView construction/destruction

CArcView::CArcView():m_pointTopLeft(0, 0)
{
	// TODO: add construction code here
	m_ScrollHigh = SCROLLHIGH;
	m_ScrollWidth = 780 * 10;
	m_nCountClick = 0;
	m_nRightClick = 0;
	m_nLeftBound = 0;
	m_nRightBound = 0;
	menuID=0;
	bDowned = 0;
	bUped = 0;
	PhraseArray[0] = "BNP";
	PhraseArray[1] = "BAP";
	PhraseArray[2] = "BVP";
	PhraseArray[3] = "UNP";
	PhraseArray[4] = "UAP";
	PhraseArray[5] = "UVP";
	PhraseArray[6] = "NH";
	PhraseArray[7] = "NZ";
}

CArcView::~CArcView()
{
}

BOOL CArcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CArcView drawing

void CArcView::OnDraw(CDC* pDC)
{
	CWdCheckDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawText(pDC);	
	DrawArc(pDC);
}

void CArcView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = m_ScrollWidth;
	sizeTotal.cy = m_ScrollHigh;
	SetScrollSizes(MM_TEXT, sizeTotal);
	POINT pt;
	pt.x = 0;
	pt.y = m_ScrollHigh;
	ScrollToPosition( pt );//下拉条置底
}

/////////////////////////////////////////////////////////////////////////////
// CArcView diagnostics

#ifdef _DEBUG
void CArcView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CArcView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CWdCheckDoc* CArcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWdCheckDoc)));
	return (CWdCheckDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArcView message handlers

void CArcView::DrawArc(CDC* pDC)
{
	int y = POSITION_Y;
	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	for(int i = 0; i < pFrame->m_PairArray.GetSize(); i++){
		CPen pen;
		CBrush brush;
		int nBegin = pFrame->m_PairArray.GetPair(i).m_nNumLeft * g_nWeigth + g_nWeigth / 6;
		int nEnd = pFrame->m_PairArray.GetPair(i).m_nNumRight * g_nWeigth + g_nWeigth / 6;
		int nWidth = nEnd - nBegin;
		int nOffset = 1.5;//字体长度的一半
		int nHigh;
		
		if(pFrame->m_PairArray.GetPair(i).bRelation)//鼠标点击该弧上的关系，弧的颜色变红
		{
			pen.CreatePen(PS_SOLID,1,RGB(255,0,0,));
			brush.CreateSolidBrush(RGB(255,0,0));
			pFrame->m_PairArray.ChangeMark(i,0);
		}
		else
		{
			pen.CreatePen(PS_SOLID,1,RGB(0,0,255));
			brush.CreateSolidBrush(RGB(0,0,255));
		}
		if(nWidth > 0)
		{//弧的方向向左，画左面的箭头
			pDC->SelectObject(&pen);
			pDC->SelectObject(&brush);
			pDC->SetArcDirection(AD_CLOCKWISE);
			
			nBegin += 4;
			nBegin++;
			POINT p[3];
			/*p[0].x = nBegin;
			p[0].y = y;
			p[1].x = nBegin + 5;
			p[1].y = y - 5;
			p[2].x = nBegin - 0;
			p[2].y = y - 8;*/
			p[0].x = nEnd;
			p[0].y = y;
			p[1].x = nEnd - 5;
			p[1].y = y - 5;
			p[2].x = nEnd - 0;
			p[2].y = y - 8;
			LPPOINT lp=p;
			pDC->Polygon(lp,3);
			nBegin--;

			nHigh = nWidth / 5 + 10;
			pDC->Arc(nBegin+2, POSITION_Y - nHigh,
				nEnd + nOffset, POSITION_Y + nHigh,
				nBegin, POSITION_Y,
				nEnd + nOffset, POSITION_Y);
		}
		else
		{//弧的方向向右，画右面的箭头
			pDC->SelectObject(&pen);
			pDC->SelectObject(&brush);
			pDC->SetArcDirection(AD_COUNTERCLOCKWISE); 
			
			nBegin -= 4;
			nWidth = (-1) * nWidth;
			nHigh = nWidth / 5 + 10;
			POINT p[3];
			/*p[0].x = nBegin;
			p[0].y = y;
			p[1].x = nBegin - 5;
			p[1].y = y - 5;
			p[2].x = nBegin - 0;
			p[2].y = y - 8;*/
			p[0].x = nEnd;
			p[0].y = y;
			p[1].x = nEnd + 5;
			p[1].y = y - 5;
			p[2].x = nEnd - 0;
			p[2].y = y - 8;
			LPPOINT lp = p;
			pDC->Polygon(lp,3);

			pDC->Arc(nBegin , POSITION_Y - nHigh,
				nEnd + nOffset, POSITION_Y + nHigh,
				nBegin, POSITION_Y,
				nEnd + nOffset, POSITION_Y);
		}

		CString strRelation;
			strRelation = pFrame->m_PairArray.GetPair(i).m_strRelation;
		CFont font;
		font.CreateFont(
			12,                        // nHeight
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
			"宋体");
	
		CRect rect;
		
		rect.left = (nBegin+nEnd)/2-7;
		rect.top = POSITION_Y-nHigh-5;
		rect.right = (nBegin+nEnd)/2+7;
		rect.bottom = POSITION_Y-nHigh+5;
//		pFrame->m_PairArray.GetPair(i).left = 3;
		m_pair.rect = rect;
		pFrame->m_PairArray.ChangeRect(i,m_pair);

		int left,top;
		left = pFrame->m_PairArray.GetPair(i).rect.left;
		top = pFrame->m_PairArray.GetPair(i).rect.top;
		pDC->SetMapMode(MM_TEXT);
		CFont *pOldFont=pDC->SelectObject(&font);  //test
		pDC->SetTextColor(RGB(255,0,0));
//		pDC->DrawText(strRelation,&rect,DT_CENTER);
		pDC->TextOut(left,top,strRelation);
		
	}
}


void CArcView::DrawText(CDC* pDC)
{
	CFont font;
	font.CreateFont(
		15,                        // nHeight
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
		"宋体");
	
	CFont *pOldFont=pDC->SelectObject(&font);  //test
	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	for(int i = 1; i < pFrame->m_WordArray.GetSize() + 1; i++)
	{
		CPen pen;
		CBrush brush;
		pDC->SelectObject(&pen);
		pDC->SelectObject(&brush);
		if(m_pair.GetLeftNum() == i && m_nCountClick == 1)
			pDC->SetTextColor(RGB(255,0,0));//改变颜色，响应鼠标左键
		else if((m_nLeftBound == i) && m_nRightClick == 1)
			pDC->SetTextColor(RGB(0,255,0));//改变颜色，响应鼠标右键
		else
			pDC->SetTextColor(RGB(0,0,255));
		
		int nOffset = 0;
		CString strShow = pFrame->m_WordArray.GetWord(i - 1).m_strWord;
		CString strTag = pFrame->m_WordArray.GetWord(i - 1).m_strAttr;
		do
		{
			CString strLine = strShow.Left(2);//由4改为2
			strShow = strShow.Right(strShow.GetLength() - 2);//由4改为2
			pDC->TextOut(i * g_nWeigth, POSITION_Y + nOffset, strLine);
			nOffset += 15;
		}
		while(strShow != "");
		pDC->TextOut(i * g_nWeigth, POSITION_Y + 60, strTag);//增加词性显示
	}
	
	char pTemp[10];
	itoa(pFrame->m_nCurrentRow + 1, pTemp, 10);
 	CString strTemp = pTemp;
	if(pFrame->m_bBegin)
		pDC->TextOut(50, POSITION_Y + 120, "当前显示的是第 " + strTemp + " 句");
}

void CArcView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	bDowned = TRUE;
	bUped = 0;
	ptLast = point;

	//坐标转换
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.LPtoDP(&m_pointTopLeft);
	point = point - m_pointTopLeft;
	m_pointTopLeft = CPoint(0, 0);

	if(point.y < POSITION_Y)//鼠标点击关系，对关系类型进行修改
	{
		ChangeRelation(point);
		return;
	}
	if(point.y > POSITION_Y + 70)//鼠标点击词性以下的位置，无反应
		return;
	//鼠标点击汉字，对弧进行修改
	int nNum = point.x / g_nWeigth;
	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	if(pFrame->m_nLastRow != 0 && nNum > 0)
	{
		if(nNum > 0 && nNum <= pFrame->m_WordArray.GetSize())
		{
			CString strWord = pFrame->m_WordArray.GetWord(nNum - 1).GetWord();
			CString strTag = pFrame->m_WordArray.GetWord(nNum - 1).m_strAttr;
			m_nCountClick++;
			if(m_nCountClick % 2 != 0)
			{
				m_pair.SetLeft(nNum, strWord,strTag);
			}
			else
			{
				m_nCountClick = 0;
				m_pair.SetRight(nNum, strWord,strTag);
				if(m_pair.m_nNumLeft != m_pair.m_nNumRight){
					pFrame->m_PairArray.DoPair(m_pair);
				}
			}
		}
	}	
	Invalidate();
	CScrollView::OnLButtonDown(nFlags, point);
}

void CArcView::ChangeRelation(CPoint point)
{
    DisplayMenu(point);
	if(menuID>0)
	{
		menuID=0;
	}
	m_vecRect.clear();
}

void CArcView::DisplayMenu(CPoint point)
{
	long x,y;
//	int h,w;
	long menu_x, menu_y;
	x=point.x;
	y=point.y;
	menu_x=x;
	menu_y=y;

	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	int length = pFrame->m_PairArray.GetSize();
	int nPairPosition;
	for(nPairPosition = 0;nPairPosition < length;nPairPosition++)
	{
		CRect rect;
		rect = pFrame->m_PairArray.GetPair(nPairPosition).rect;
		if(rect.left < x && x < rect.right
			&& rect.top < y && y < rect.bottom)//鼠标点在关系的范围之内
		{
//			point.x = rect.left;
//			point.y = rect.top;
			pFrame->m_PairArray.ChangeMark(nPairPosition,1);//表示该关系已被用户选中
			Invalidate();
			break;
		}
	}
	if(nPairPosition == length)//鼠标点在关系范围之外
	{
		Invalidate();
		return;
	}
	
/*
	CPoint pt=GetScrollPosition( );
//	menupoint=pt;
	x+=pt.x; y+=pt.y;
	CDC *pDC=GetDC();
//	CFont *pOldFont=pDC->SelectObject(&m_font);
	CSize size;
	
	char a[]=" ";
	size=pDC->GetTextExtent(a,1);
//	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);
	h=size.cy;
	w=size.cx;
	CRect rc;
	GetClientRect(&rc);
//	height=(rc.bottom-rc.top)/5;
*/

	//坐标转换
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.LPtoDP(&m_pointTopLeft);
	point = point + m_pointTopLeft;
	m_pointTopLeft = CPoint(0, 0);
	
////////////////////////显示菜单//////////////////////////////
	CMenu menu;
	menu.CreatePopupMenu();
	ClientToScreen(&point);
	int nID=100;
	
	for(int j=0;j < (int)pFrame->m_PairArray.GetPair(nPairPosition).candidate.size();j++)
	{
//		CString str = pFrame->m_PairArray.GetPair(nPairPosition).candidate[j];
		menu.AppendMenu(MF_STRING|MF_ENABLED,nID++,pFrame->m_PairArray.GetPair(nPairPosition).candidate[j]);
	}

/////////////// begin///////////////
//候选关系列表中没有正确的依存关系，在子菜单中列出全部关系类型
	CMenu submenu;
	int nSubID = 200;
	submenu.CreatePopupMenu();
	//依存弧的方向向左
	bool bLeft = 0;
	if(pFrame->m_PairArray.GetPair(nPairPosition).m_nNumLeft < pFrame->m_PairArray.GetPair(nPairPosition).m_nNumRight)
	{
		bLeft = 1;
		for(int j=0;j < (int)pFrame->m_PairArray.GetPair(nPairPosition).allLeftRelation.size();j++)
			submenu.AppendMenu(MF_STRING|MF_ENABLED,nSubID++,pFrame->m_PairArray.GetPair(nPairPosition).allLeftRelation[j]);
	}
	//依存弧的方向向右
	else
	{
		for(int j=0;j < (int)pFrame->m_PairArray.GetPair(nPairPosition).allRightRelation.size();j++)
			submenu.AppendMenu(MF_STRING|MF_ENABLED,nSubID++,pFrame->m_PairArray.GetPair(nPairPosition).allRightRelation[j]);
	}
	menu.AppendMenu(MF_POPUP, (UINT)submenu.m_hMenu, "all");
////////////////end////////////////
	menuID=menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL|
		TPM_RETURNCMD,point.x,point.y,this);
	menu.DestroyMenu();

	if(menuID == 0)//未点击菜单
		return;
	CString strRel;
	if(menuID >= 200)//点击子菜单
	{
		if(bLeft == 1)
			strRel = pFrame->m_PairArray.GetPair(nPairPosition).allLeftRelation[menuID-200];
		else
			strRel = pFrame->m_PairArray.GetPair(nPairPosition).allRightRelation[menuID-200];
		strRel = strRel.Mid(0,strRel.Find(' '));
	}
	else//点击主菜单
		strRel = pFrame->m_PairArray.GetPair(nPairPosition).candidate[menuID-100];

	pFrame->m_PairArray.ChangeRelation(nPairPosition,strRel);
	Invalidate();
}
 

void CArcView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//坐标转换
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.LPtoDP(&m_pointTopLeft);
	point = point - m_pointTopLeft;
	m_pointTopLeft = CPoint(0, 0);

	if(point.y < POSITION_Y)//鼠标点击关系，删除该弧
	{
		DeleteArc(point);
		return;
	}
	
	//鼠标点击汉字，标记基本短语的边界
	int nNum = point.x / g_nWeigth;
	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	if(pFrame->m_nLastRow != 0 && nNum > 0)
	{
		if(nNum > 0 && nNum <= pFrame->m_WordArray.GetSize())
		{
			m_nRightClick++;
			if(m_nRightClick % 2 != 0)
			{
				m_nLeftBound = nNum;
			}
			else
			{
				m_nRightClick = 0;
				m_nRightBound = nNum;
				if(pFrame->BasicPhrase(m_nLeftBound,m_nRightBound))//是删除短语还是增加短语
				{
					//坐标转换
					dc.LPtoDP(&m_pointTopLeft);
					point = point + m_pointTopLeft;
					m_pointTopLeft = CPoint(0, 0);
					//选择短语类型
					CMenu menu;
					menu.CreatePopupMenu();
					ClientToScreen(&point);
					int nID=100;
					
					for(int j=0;j < ALLPHRASE;j++)
					{
						menu.AppendMenu(MF_STRING|MF_ENABLED,nID++,PhraseArray[j]);
					}
					menuID=menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL|
						TPM_RETURNCMD,point.x,point.y,this);
					menu.DestroyMenu();
					
					CString strRel;
					if(menuID == 0)//未点击菜单
						strRel = "BNP";
					else
						strRel = PhraseArray[menuID-100];
					pFrame->BasicPhrase(m_nLeftBound,m_nRightBound,strRel);
				}
			}
		}
	}
	Invalidate();
	CScrollView::OnRButtonDown(nFlags, point);
}

//删除依存弧
void CArcView::DeleteArc(CPoint point)
{
	long x,y;
	x=point.x;
	y=point.y;

	CMainFrame* pFrame = (CMainFrame *) AfxGetApp() -> m_pMainWnd;
	int length = pFrame->m_PairArray.GetSize();
	int nPairPosition;
	for(nPairPosition = 0;nPairPosition < length;nPairPosition++)
	{
		CRect rect;
		rect = pFrame->m_PairArray.GetPair(nPairPosition).rect;
		if(rect.left < x && x < rect.right
			&& rect.top < y && y < rect.bottom)//鼠标点在关系的范围之内
		{
			int nNum = pFrame->m_PairArray.GetPair(nPairPosition).m_nNumLeft;
			CString strWord = pFrame->m_WordArray.GetWord(nNum - 1).GetWord();
			CString strTag = pFrame->m_WordArray.GetWord(nNum - 1).m_strAttr;
			m_pair.SetLeft(nNum, strWord,strTag);

			nNum = pFrame->m_PairArray.GetPair(nPairPosition).m_nNumRight;
			strWord = pFrame->m_WordArray.GetWord(nNum - 1).GetWord();
			strTag = pFrame->m_WordArray.GetWord(nNum - 1).m_strAttr;
			m_pair.SetRight(nNum, strWord,strTag);

			pFrame->m_PairArray.DeletePair(m_pair);
			Invalidate();
			break;
		}
	}
}

//用移动鼠标控制滚动条,按下左键
void CArcView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
//	if(bDowned && !bUped)
//	{
//		CPoint pt = GetScrollPosition( );
//		pt.x += (point.x - ptLast.x);
//		ScrollToPosition( pt );//左右移动滚动条
//		ptLast = point;
//	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CArcView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	bUped = 1;
	bDowned = 0;
	CScrollView::OnLButtonUp(nFlags, point);
}
