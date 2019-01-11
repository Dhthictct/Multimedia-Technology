// GrayDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChangeToGray.h"
#include "GrayDlg.h"
#include "afxdialogex.h"

#include "Dib.h"
// CGrayDlg 对话框

IMPLEMENT_DYNAMIC(CGrayDlg, CDialogEx)

CGrayDlg::CGrayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GRAY_DIALOG, pParent)
{
	m_strWeightR = _T("0.30");
	m_strWeightG = _T("0.59");
	m_strWeightB = _T("0.11");
	m_nMethod = MEAN_GRAY;
	m_fWeightR = atof((LPCSTR)m_strWeightR);
	m_fWeightG = atof((LPCSTR)m_strWeightG);
	m_fWeightB = atof((LPCSTR)m_strWeightB);
}

CGrayDlg::~CGrayDlg()
{
}

void CGrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strWeightR);
	DDX_Text(pDX, IDC_EDIT2, m_strWeightG);
	DDX_Text(pDX, IDC_EDIT3, m_strWeightB);
}


BEGIN_MESSAGE_MAP(CGrayDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGrayDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &CGrayDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGrayDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CGrayDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CGrayDlg 消息处理程序



void CGrayDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMethod = MEAN_GRAY;
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
}


void CGrayDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMethod = MAXIMUM_GRAY;
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
}


void CGrayDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nMethod = WEIGHT_GRAY;
	GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
}


BOOL CGrayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGrayDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_fWeightR = atof((LPCSTR)m_strWeightR);
	m_fWeightG = atof((LPCSTR)m_strWeightG);
	m_fWeightB = atof((LPCSTR)m_strWeightB);

	CDialogEx::OnOK();
}