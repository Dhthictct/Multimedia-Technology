
// ReaderDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <iostream>
#include <string>

#include <sapi.h>
#include <sphelper.h>//����ͷ�ļ�
using namespace std;

// CReaderDlg �Ի���
class CReaderDlg : public CDialogEx
{
// ����
public:
	CReaderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFile();
	// �ļ�·��
	CString strFilePath;
	// �ı�����
	CString Content;
	CEdit m_con;
	ISpVoice* pSpVoice;
	afx_msg void OnBnClickedButtonSlow();
	afx_msg void OnBnClickedButtonFast();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// ���ú��Ч��
	void Result(long val1 = 0, USHORT val2 = 0, int flag = 0);
	CString con;
};
