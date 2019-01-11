
// ReaderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Reader.h"
#include "ReaderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReaderDlg �Ի���



CReaderDlg::CReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READER_DIALOG, pParent)
	, strFilePath(_T(""))
	, Content(_T(""))
	, pSpVoice(NULL)
	, con(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_con);
	DDX_Text(pDX, IDC_EDIT_CONTENT, con);
}

BEGIN_MESSAGE_MAP(CReaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CReaderDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_SLOW, &CReaderDlg::OnBnClickedButtonSlow)
	ON_BN_CLICKED(IDC_BUTTON_FAST, &CReaderDlg::OnBnClickedButtonFast)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CReaderDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CReaderDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDOK, &CReaderDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CReaderDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CReaderDlg ��Ϣ�������

BOOL CReaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReaderDlg::OnBnClickedButtonFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();
		CFile pFile;
		int hResult = pFile.Open(strFilePath, CFile::modeRead);
		if (hResult != 0) {
			int len = pFile.GetLength();
			char szBuff[1000000] = "";
			//pFile.Read(temp.GetBuffer(pFile.GetLength()), pFile.GetLength());
			pFile.Read(szBuff, pFile.GetLength());
			pFile.Close();
			Content = szBuff;
			GetDlgItem(IDC_EDIT_CONTENT)->SetWindowText(Content);
			::CoInitialize(NULL);//��ʼ����������
			if (FAILED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void **)&pSpVoice)))
				//���������������������൱�ڴ�������������FAILED�Ǹ��궨�壬�������ж�CoCreateInstance���������û�гɹ��������������������ǲ��ɹ�����ʾ��Ϣ��
			{
				MessageBox("Failed to create instance of ISpVoice!");
			}
		}
	}
}


void CReaderDlg::OnBnClickedButtonSlow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	long val;
	pSpVoice->GetRate(&val);
	if (val < -9) {
		val = -10;
	}
	else {
		val--;
	}
	pSpVoice->SetRate(val);
	Result(val, 0, 0);
}


void CReaderDlg::OnBnClickedButtonFast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	long val;
	pSpVoice->GetRate(&val);
	if (val > 9) {
		val = 10;
	}
	else {
		val++;
	}
	pSpVoice->SetRate(val);
	Result(val, 0, 0);
}


void CReaderDlg::OnBnClickedButtonDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USHORT val;
	pSpVoice->GetVolume(&val);
	if (val < 10) {
		val = 0;
	}
	else {
		val -= 10;
	}
	pSpVoice->SetVolume(val);
	Result(0, val, 1);
}


void CReaderDlg::OnBnClickedButtonUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USHORT val;
	pSpVoice->GetVolume(&val);
	if (val > 90) {
		val = 100;
	}
	else {
		val += 10;
	}
	pSpVoice->SetVolume(val);
	Result(0, val, 1);
}


void CReaderDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	USES_CONVERSION;
	pSpVoice->Speak(A2CW((LPCSTR)Content), SPF_DEFAULT, NULL);//ִ������������Speek����������������������֡�
	
}


void CReaderDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pSpVoice->Release(); //�ͷ���������
	::CoUninitialize();//�ͷ���������
	CDialogEx::OnCancel();
}


// ���ú��Ч��
void CReaderDlg::Result(long val1, USHORT val2, int flag)
{
	pSpVoice->Speak(L"Hello World!", SPF_DEFAULT, NULL);
}
