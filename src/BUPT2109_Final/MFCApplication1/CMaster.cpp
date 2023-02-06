// CMaster.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CMaster.h"

#include "execsqlite3.h"
#include "check.h"

// CMaster

IMPLEMENT_DYNCREATE(CMaster, CFormView)

CMaster::CMaster()
	: CFormView(DIALOG_MASTER)
	, m_NewP(_T(""))
	, m_SureP(_T(""))
	, m_NewE(_T(""))
	, m_Name(_T(""))
	, m_airline(_T(""))
	, m_email(_T(""))
{

}

CMaster::~CMaster()
{
}

void CMaster::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT4, m_NewPassword);
	DDX_Text(pDX, IDC_EDIT7, m_NewP);
	DDX_Text(pDX, IDC_EDIT5, m_SureP);
	DDX_Text(pDX, IDC_EDIT6, m_NewE);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
	DDX_Text(pDX, IDC_EDIT10, m_airline);
	DDX_Text(pDX, IDC_EDIT11, m_email);
}

BEGIN_MESSAGE_MAP(CMaster, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CMaster::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMaster::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CMaster::OnBnClickedButton7)
END_MESSAGE_MAP()


// CMaster 诊断

#ifdef _DEBUG
void CMaster::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMaster::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMaster 消息处理程序

void CMaster::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_NewP.IsEmpty() || m_SureP.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空"));
		return;
	}

	if (m_NewP != m_SureP)
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
	file.writepwd(tmp.GetBuffer(), tmp2.GetBuffer());*/	char tmp[20];
	Cstring2Char(m_NewP, tmp);
	if (!checkpassword(tmp)) {
		MessageBox(TEXT("失败"));
		return;
	}
	if (!changeAdminInfo(1, tmp))
		MessageBox(TEXT("修改成功"));
	else MessageBox(TEXT("失败"));

	OnInitialUpdate();
	//清空输入框

	m_NewP.Empty();
	m_SureP.Empty();
	UpdateData(FALSE);
}


void CMaster::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_NewE.IsEmpty())
	{
		MessageBox(TEXT("输入不能为空"));
		return;
	}

	char tmp[20];
	Cstring2Char(m_NewE, tmp);
	if (!checkemail(tmp)) {
		MessageBox(TEXT("失败"));
		return;
	}
	if (!changeAdminInfo(3, tmp))
		MessageBox(TEXT("修改成功"));
	else MessageBox(TEXT("失败"));

	OnInitialUpdate();

	m_NewE.Empty();

	UpdateData(FALSE);
}





void CMaster::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_NewE.Empty();
	
	m_NewP.Empty();
	m_SureP.Empty();

	UpdateData(FALSE);
}


void CMaster::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	
	// TODO: 在此添加专用代码和/或调用基类
		//身份,id,tele,email初始化位置
	if (i == 2) {
		//m_user = TEXT("管理员");
		adminInfo info;
		getAdminInfo(db, &info, unc);

		m_Name = info.ID;
		m_airline = info.airline;
		m_email = info.email;

		Cstring2Char(m_airline,airline);
	}
	else {
		;
	}
	CFormView::OnInitialUpdate();
}
