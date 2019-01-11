
// ChangeToGrayView.cpp : CChangeToGrayView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_COMMAND(AFX_ID_PREVIEW_CLOSE, &CChangeToGrayView::OnChangetogray)

	ON_MESSAGE(WM_REALIZEPAL, OnRealizePal)
	ON_COMMAND(IDM_CHANGETOGRAY, &CChangeToGrayView::OnChangetogray)
END_MESSAGE_MAP()

// CChangeToGrayView ����/����

CChangeToGrayView::CChangeToGrayView()
{
	// TODO: �ڴ˴���ӹ������

}

CChangeToGrayView::~CChangeToGrayView()
{
}

BOOL CChangeToGrayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CChangeToGrayView ����

void CChangeToGrayView::OnDraw(CDC* pDC)
{
	CChangeToGrayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	/*if (!pDoc)
		return;*/

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//m_bitmap.LoadBitmap(IDC_BITTMAP_IMAGE2);
	if (!pDoc->m_pDib->IsEmpty()) {
		pDoc->m_pDib->Display(pDC, 0, 0);
	}
}


// CChangeToGrayView ��ӡ

BOOL CChangeToGrayView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CChangeToGrayView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CChangeToGrayView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CChangeToGrayView ���

#ifdef _DEBUG
void CChangeToGrayView::AssertValid() const
{
	CView::AssertValid();
}

void CChangeToGrayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChangeToGrayDoc* CChangeToGrayView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChangeToGrayDoc)));
	return (CChangeToGrayDoc*)m_pDocument;
}
#endif //_DEBUG


// CChangeToGrayView ��Ϣ�������


//void CChangeToGrayView::OnChangetogray()
//{
//	// TODO: �ڴ���������������
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

	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ���������������
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
