
// ChangeToGrayView.h : CChangeToGrayView ��Ľӿ�
//

#pragma once


class CChangeToGrayView : public CView
{
protected: // �������л�����
	CChangeToGrayView();
	DECLARE_DYNCREATE(CChangeToGrayView)

// ����
public:
	CChangeToGrayDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CChangeToGrayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnChangetogray();
	afx_msg LRESULT OnRealizePal(WPARAM wParam, LPARAM lParam);
	virtual void OnInitialUpdate();
	afx_msg void OnChangetogray();
};

#ifndef _DEBUG  // ChangeToGrayView.cpp �еĵ��԰汾
inline CChangeToGrayDoc* CChangeToGrayView::GetDocument() const
   { return reinterpret_cast<CChangeToGrayDoc*>(m_pDocument); }
#endif

