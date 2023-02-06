// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"

#include "execsqlite3.h"

#include "m_Data.h"

// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
	, m_username(_T(""))
	, m_password(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoginDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoginDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CLoginDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//click
	char* fname = (char*)"bupt44Database.db";
	//std::global db;
	//extern db;
	db = openDb(fname);

	UpdateData(TRUE);
	if (m_username.IsEmpty() || m_password.IsEmpty())
	{
		MessageBox(TEXT("You should input something!!"));
		return;
	}

	//登录check
	//CString un, pw;
	//un.Format(m_username);
	//pw.Format(m_password);
	//char unc[20];
	char pwc[20];
	Cstring2Char(m_username, unc);
	Cstring2Char(m_password, pwc);
	int check = loginUser(db, unc, pwc);
	if (check) {
		CDialog::OnCancel();
		i = 1;
	}else{
		MessageBox(TEXT("Failed"));
		return;
	}
}





void CLoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CLoginDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_username.IsEmpty() || m_password.IsEmpty())
	{
		MessageBox(TEXT("You should input something!!"));
		return;
	}
	else
	{
		i = 2;
		//CDialog::OnCancel();
	}

	char* fname = (char*)"bupt44Database.db";
	//std::global db;
	//extern db;
	db = openDb(fname);

	UpdateData(TRUE);
	if (m_username.IsEmpty() || m_password.IsEmpty())
	{
		MessageBox(TEXT("You should input something!!"));
		return;
	}

	//登录check
	//CString un, pw;
	//un.Format(m_username);
	//pw.Format(m_password);
	//char unc[20];
	char pwc[20];
	Cstring2Char(m_username, unc);
	Cstring2Char(m_password, pwc);
	int check = loginAdmin(db, unc, pwc);
	if (check) {
		CDialog::OnCancel();
	}
	else {
		MessageBox(TEXT("Failed"));
		return;
	}
}


void CLoginDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Data m_data;
	m_data.DoModal();
	thisDate = callbackCount;
}
