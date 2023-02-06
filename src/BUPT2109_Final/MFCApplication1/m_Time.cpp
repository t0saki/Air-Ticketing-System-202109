// m_Time.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "m_Time.h"
#include "afxdialogex.h"
#include "execsqlite3.h"

// m_Time 对话框

IMPLEMENT_DYNAMIC(m_Time, CDialogEx)

m_Time::m_Time(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_TIME, pParent)
{

}

m_Time::~m_Time()
{
}

void m_Time::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, comboHour);
	DDX_Control(pDX, IDC_COMBO3, comboMinute);
}


BEGIN_MESSAGE_MAP(m_Time, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &m_Time::OnBnClickedButton1)
END_MESSAGE_MAP()


// m_Time 消息处理程序


void m_Time::OnBnClickedButton1()
{
	callbackCount = comboHour.GetCurSel() * 3600 + comboMinute.GetCurSel() * 60;
	OnOK();
	// TODO: 在此添加控件通知处理程序代码
}


BOOL m_Time::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString tmp;
	// TODO:  在此添加额外的初始化
	for (int i = 0; i < 24; i++) {
		tmp.Format(_T("%d"), i);
		comboHour.AddString(tmp);
	}

	for (int i = 0; i < 60; i++) {
		tmp.Format(_T("%d"), i);
		comboMinute.AddString(tmp);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
