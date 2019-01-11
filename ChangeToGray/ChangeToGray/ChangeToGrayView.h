
// ChangeToGrayView.h : CChangeToGrayView 类的接口
//

#pragma once


class CChangeToGrayView : public CView
{
protected: // 仅从序列化创建
	CChangeToGrayView();
	DECLARE_DYNCREATE(CChangeToGrayView)

// 特性
public:
	CChangeToGrayDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CChangeToGrayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnChangetogray();
	afx_msg LRESULT OnRealizePal(WPARAM wParam, LPARAM lParam);
	virtual void OnInitialUpdate();
	afx_msg void OnChangetogray();
};

#ifndef _DEBUG  // ChangeToGrayView.cpp 中的调试版本
inline CChangeToGrayDoc* CChangeToGrayView::GetDocument() const
   { return reinterpret_cast<CChangeToGrayDoc*>(m_pDocument); }
#endif

