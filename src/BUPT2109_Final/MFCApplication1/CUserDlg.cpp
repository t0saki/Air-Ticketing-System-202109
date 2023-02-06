// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CUserDlg.h"

#include "execsqlite3.h"
#include "check.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(DIALOG_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_tele(_T(""))
	, m_email(_T(""))
	, m_pwd(_T(""))
	, m_surepwd(_T(""))
	, m_newTele(_T(""))
	, m_newEmail(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_tele);
	DDX_Text(pDX, IDC_EDIT4, m_email);
	DDX_Text(pDX, IDC_EDIT5, m_pwd);
	DDX_Text(pDX, IDC_EDIT6, m_surepwd);
	DDX_Text(pDX, IDC_EDIT7, m_newTele);
	DDX_Text(pDX, IDC_EDIT9, m_newEmail);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT8, &CUserDlg::OnEnChangeEdit8)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	//身份,id,tele,email初始化位置
	if (i==1) {
		m_user = TEXT("普通用户");
		userInfo info;
		getUserInfo(db, &info, unc);


		m_user = info.ID;
		m_name = info.name;
		CString tmp;
		tmp.Format(_T("%lld"), info.phone);
		m_tele = tmp;
		m_email = info.email;
	}
	else {
		;
	}
	// TODO: 在此添加专用代码和/或调用基类

	CFormView::OnInitialUpdate();
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//修改密码按钮
	UpdateData(TRUE);

	if (m_pwd.IsEmpty() || m_surepwd.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空"));
		return;
	}
	
	if (m_pwd != m_surepwd)
	{
		MessageBox(TEXT("确定密码与新密码不一致"));
		return;
	}
	//新旧密码不一致
	//待添加

	//改密码
	/*CStringA tmp;
	CStringA tmp2;
	tmp = name;
	tmp2 = m_pwd;
	file.writepwd(tmp.GetBuffer(), tmp2.GetBuffer());*/
	char tmp[20];
	Cstring2Char(m_pwd, tmp);	
	if (!checkpassword(tmp)) {
		MessageBox(TEXT("失败"));
		return;
	}
	if (!changeUserInfo(1,tmp))
		MessageBox(TEXT("修改成功"));
	else MessageBox(TEXT("失败"));
	//清空输入框

	m_pwd.Empty();
	m_surepwd.Empty();
	OnInitialUpdate();
	UpdateData(FALSE);
}


void CUserDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CUserDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//修改邮箱
	UpdateData(TRUE);

	if (m_newEmail.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空"));
		return;
	}
	
	char tmp[20];
	Cstring2Char(m_newEmail, tmp);
	if (!checkemail(tmp)){
		MessageBox(TEXT("失败"));
		return;
	}
	if (!changeUserInfo(3, tmp))
		MessageBox(TEXT("修改成功"));
	else MessageBox(TEXT("失败"));

	OnInitialUpdate();
	m_newEmail.Empty();
	
	UpdateData(FALSE);
	
}


void CUserDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//修改电话
	UpdateData(TRUE);

	if (m_newTele.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空"));
		return;
	}

	char tmp[20];
	Cstring2Char(m_newTele, tmp);
	if (!checkphone(tmp)) {
		MessageBox(TEXT("失败"));
		return;
	}
	if (!changeUserInfo(2, tmp))
		MessageBox(TEXT("修改成功"));
	else MessageBox(TEXT("失败"));

	OnInitialUpdate();
	m_newTele.Empty();

	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_newEmail.Empty();
	m_newTele.Empty();
	m_pwd.Empty();
	m_surepwd.Empty();

	UpdateData(FALSE);
}
