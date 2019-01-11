#pragma once
#include "afxwin.h"


// CGrayDlg �Ի���

class CGrayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGrayDlg)

public:
	CGrayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGrayDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strWeightR;
	CString m_strWeightG;
	CString m_strWeightB;

	int m_nMethod;
	double m_fWeightR;
	double m_fWeightG;
	double m_fWeightB;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	virtual BOOL OnInitDialog();
};
