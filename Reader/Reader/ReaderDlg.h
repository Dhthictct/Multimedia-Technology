
// ReaderDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <iostream>
#include <string>

#include <sapi.h>
#include <sphelper.h>//语音头文件
using namespace std;

// CReaderDlg 对话框
class CReaderDlg : public CDialogEx
{
// 构造
public:
	CReaderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFile();
	// 文件路径
	CString strFilePath;
	// 文本内容
	CString Content;
	CEdit m_con;
	ISpVoice* pSpVoice;
	afx_msg void OnBnClickedButtonSlow();
	afx_msg void OnBnClickedButtonFast();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// 设置后的效果
	void Result(long val1 = 0, USHORT val2 = 0, int flag = 0);
	CString con;
};
