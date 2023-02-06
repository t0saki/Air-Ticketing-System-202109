// m_Data.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "m_Data.h"
#include "afxdialogex.h"
#include "execsqlite3.h"

// m_Data 对话框

IMPLEMENT_DYNAMIC(m_Data, CDialogEx)

m_Data::m_Data(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_DATA, pParent)
{

}

m_Data::~m_Data()
{
}

void m_Data::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, comboYear);
	DDX_Control(pDX, IDC_COMBO3, comboMonth);
	DDX_Control(pDX, IDC_COMBO4, comboDate);
}


BEGIN_MESSAGE_MAP(m_Data, CDialogEx)
	ON_CBN_EDITCHANGE(IDC_COMBO3, &m_Data::OnCbnEditchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO3, &m_Data::OnCbnSelchangeCombo3)
//	ON_BN_CLICKED(IDC_BUTTON1, &m_Data::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO4, &m_Data::OnCbnSelchangeCombo4)
	ON_BN_CLICKED(IDC_BUTTON8, &m_Data::OnBnClickedButton8)
END_MESSAGE_MAP()


// m_Data 消息处理程序


BOOL m_Data::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString tmp;
	// TODO:  在此添加额外的初始化
	for (int i = 0; i < 3; i++) {
		tmp.Format(_T("%d"), i+2021);
		comboYear.AddString(tmp);
	}

	for (int i = 1; i <= 12; i++) {
		tmp.Format(_T("%d"), i);
		comboMonth.AddString(tmp);
	}

	for (int i = 1; i <= md[0]; i++) {
		tmp.Format(_T("%d"), i);
		comboDate.AddString(tmp);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void m_Data::OnCbnEditchangeCombo3()
{
	UpdateData(1);
	comboDate.Clear();
	CString tmp;
	for (int i = 1; i <= md[comboMonth.GetCurSel()]; i++) {
		tmp.Format(_T("%d"), i);
		comboDate.AddString(tmp);
	}
	UpdateData(0);
}


void m_Data::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	comboDate.Clear();
	comboDate.ResetContent();
	CString tmp;
	for (int i = 1; i <= md[comboMonth.GetCurSel()]; i++) {
		tmp.Format(_T("%d"), i);
		comboDate.AddString(tmp);
	}
	UpdateData(0);
}


void m_Data::OnCbnSelchangeCombo4()
{
	// TODO: 在此添加控件通知处理程序代码
}


void m_Data::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	tdate thisDate;
	thisDate.y = comboYear.GetCurSel();
	thisDate.m = comboMonth.GetCurSel()+1;
	thisDate.d = comboDate.GetCurSel()+1;
	callbackCount = date2int(&thisDate);
	OnOK();
}
