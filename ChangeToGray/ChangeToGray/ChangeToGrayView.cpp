
// ChangeToGrayView.cpp : CChangeToGrayView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ChangeToGray.h"
#endif

#include "ChangeToGrayDoc.h"
#include "ChangeToGrayView.h"

#include "MainFrm.h"
#include "GrayDlg.h"
#include "dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_REALIZEPAL	(WM_USER + 0x100)

// CChangeToGrayView

IMPLEMENT_DYNCREATE(CChangeToGrayView, CView)

BEGIN_MESSAGE_MAP(CChangeToGrayView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(AFX_ID_PREVIEW_CLOSE, &CChangeToGrayView::OnChangetogray)

	ON_MESSAGE(WM_REALIZEPAL, OnRealizePal)
	ON_COMMAND(IDM_CHANGETOGRAY, &CChangeToGrayView::OnChangetogray)
END_MESSAGE_MAP()

// CChangeToGrayView 构造/析构

CChangeToGrayView::CChangeToGrayView()
{
	// TODO: 在此处添加构造代码

}

CChangeToGrayView::~CChangeToGrayView()
{
}

BOOL CChangeToGrayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CChangeToGrayView 绘制

void CChangeToGrayView::OnDraw(CDC* pDC)
{
	CChangeToGrayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	/*if (!pDoc)
		return;*/

	// TODO: 在此处为本机数据添加绘制代码
	//m_bitmap.LoadBitmap(IDC_BITTMAP_IMAGE2);
	if (!pDoc->m_pDib->IsEmpty()) {
		pDoc->m_pDib->Display(pDC, 0, 0);
	}
}


// CChangeToGrayView 打印

BOOL CChangeToGrayView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CChangeToGrayView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CChangeToGrayView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CChangeToGrayView 诊断

#ifdef _DEBUG
void CChangeToGrayView::AssertValid() const
{
	CView::AssertValid();
}

void CChangeToGrayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChangeToGrayDoc* CChangeToGrayView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChangeToGrayDoc)));
	return (CChangeToGrayDoc*)m_pDocument;
}
#endif //_DEBUG


// CChangeToGrayView 消息处理程序


//void CChangeToGrayView::OnChangetogray()
//{
//	// TODO: 在此添加命令处理程序代码
//	CChangeToGrayDoc* pDoc = GetDocument();
//	CGrayDlg grayDlg(this);
//	if (grayDlg.DoModal() == IDOK)
//	{
//		pDoc->m_pDib->ChangeToGrayscale(grayDlg.m_nMethod,
//			grayDlg.m_fWeightR,
//			grayDlg.m_fWeightG,
//			grayDlg.m_fWeightB);
//		pDoc->SetModifiedFlag(TRUE);
//		OnRealizePal((WPARAM)m_hWnd, 0);  // realize the new palette
//		pDoc->UpdateAllViews(NULL);
//	}
//
//}


void CChangeToGrayView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CChangeToGrayDoc * pDoc = GetDocument();

	CSize sizeTotal(pDoc->m_pDib->GetWidth(), pDoc->m_pDib->GetHeight());
	//SetScrollSizes(MM_TEXT, sizeTotal);

	CMainFrame * pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	ASSERT_KINDOF(CMainFrame, pAppFrame);
	CRect rc;
	pAppFrame->GetClientRect(&rc);
}

LRESULT CChangeToGrayView::OnRealizePal(WPARAM wParam, LPARAM lParam)
{
	ASSERT(wParam != NULL);
	CChangeToGrayDoc * pDoc = GetDocument();

	if (pDoc->m_pDib->IsEmpty()) {
		return 0L;
	}

	CPalette * pPal = pDoc->m_pDib->GetPalette();
	if (pPal != NULL) 
	{
		CWnd * pAppFrame = AfxGetApp()->m_pMainWnd;

		CClientDC appDC(pAppFrame);

		CPalette * oldPalette = appDC.SelectPalette(pPal, ((HWND)wParam) != m_hWnd);

		if (oldPalette != NULL) {
			UINT nColorsChanged = appDC.RealizePalette();
			if (nColorsChanged > 0) {
				GetDocument()->UpdateAllViews(NULL);
			}
			appDC.SelectPalette(oldPalette, TRUE);
		}
		else {
			TRACE0("\tSelectPalette failed!\n");
		}
	}
	return 0L;
}



void CChangeToGrayView::OnChangetogray()
{
	// TODO: 在此添加命令处理程序代码
	CChangeToGrayDoc* pDoc = GetDocument();
	CGrayDlg grayDlg(this);
	if (grayDlg.DoModal() == IDOK)
	{
		pDoc->m_pDib->ChangeToGrayscale(grayDlg.m_nMethod,
			grayDlg.m_fWeightR,
			grayDlg.m_fWeightG,
			grayDlg.m_fWeightB);
		pDoc->SetModifiedFlag(TRUE);
		OnRealizePal((WPARAM)m_hWnd, 0);  // realize the new palette
		pDoc->UpdateAllViews(NULL);
	}
}
