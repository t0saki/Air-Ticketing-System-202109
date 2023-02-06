// CSellDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CSellDlg.h"
#include "m_Data.h"

#include "execsqlite3.h"
#include "orderSort.h"
// CSellDlg


order orderInfo;
//flightInfo flight[100];

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(DIALOG_SELL)
	, m_price(0)
	, m_left(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, c_combo);
	DDX_Text(pDX, IDC_EDIT5, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_left);
	DDX_Text(pDX, IDC_EDIT4, m_num);
	DDX_Control(pDX, IDC_COMBO2, m_vip);
	DDX_Text(pDX, IDC_EDIT7, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_EN_CHANGE(IDC_EDIT10, &CSellDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT2, &CSellDlg::OnEnChangeEdit2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSellDlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSellDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON5, &CSellDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CSellDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSellDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化航班订单

	//初始化下拉框
	//待添加


	memset(flight, 0, sizeof(flight));
	getFlightInfo(db, flight, star);

	CString tmp;
	int i = 0;
	while (flight[i].FUID) {
		c_combo.AddString(CString(flight[i].flightNumber));
		i++;
	}
	//默认值
	c_combo.SetCurSel(0);

	m_vip.SetCurSel(0);
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//切换商品

	//获取下拉框

	int index_1 = c_combo.GetCurSel();
	int index_2 = m_vip.GetCurSel();
	/*CString name_1;
	CString name_2;
	c_combo.GetLBText(index_1, name_1);
	m_vip.GetLBText(index_2, name_2);*/
	int left = getTicketNum(db, orderInfo.fdate, flight[index_1].flightNumber);
	if (index_2) {
		m_price = index_2 == 1 ? flight[index_1].price1 : flight[index_1].price2;
		m_left = index_2 == 1 ? flight[index_1].remain1 - (left >> 16) : flight[index_1].remain2 - ((left << 16) >> 16);
		UpdateData(FALSE);
	}
	//根据下拉框索引名称
	//未添加

}


void CSellDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_num < 0)
	{
		MessageBox(TEXT("购买数量应大于0"));
		return;
	}
	if (m_num > m_left)
	{
		MessageBox(TEXT("购买数量应小于库存"));
		return;
	}


	//购买
	int index_1 = c_combo.GetCurSel();
	int index_2 = m_vip.GetCurSel();
	CString name_1;
	CString name_2;
	c_combo.GetLBText(index_1, name_1);
	m_vip.GetLBText(index_2, name_2);


	order orders[100];
	memset(orders, 0, sizeof(orders));
	getOrder(db, orders, thisUUID);
	int n = 0;
	while (orders[n].OUID) n++;
	//库存改变
	//待添加
	//告诉用户购买信息
	if (!index_2)
	{
		MessageBox(TEXT("请选择舱位"));
		return;
	}
	else{
		UpdateData(TRUE);
		CString str;
		str.Format(_T("商品:%s %s \r\n单价:%d \r\n数量:%d \r\n总价:%d"), name_1, name_2, m_price, m_num, m_price * m_num);
		m_sellInfo = str;
		UpdateData(FALSE);

		//最新数据写回数据库
		orderInfo.UUID = thisUUID;
		strcpy(orderInfo.flightNumber, flight[index_1].flightNumber);
		orderInfo.number = m_num;
		orderInfo.tier = index_2;
		orderInfo.isPaid = 0;
		strcpy(orderInfo.airline, flight[index_1].airline);
		orderInfo.takeOffTime = flight[index_1].takeOffTime;
		orderInfo.estTime = flight[index_1].estTime;
		orderInfo.price = m_price;
		orderInfo.date = thisDate;
		if (!checkOrder(orders, orderInfo, n, thisDate)) {
			MessageBox(TEXT("无法购买"));
			return;
		}
		addOrder(db, orderInfo);
		//boughtFlight(db, flight[index_1].FUID,
		//	(index_2 == 1 ? flight[index_1].remain1 : flight[index_1].remain2)- m_num, index_2 - 1);
		MessageBox(TEXT("购买成功"));
		m_vip.SetCurSel(0);

		//清空数据
		m_num = 0;

		UpdateData(FALSE);
	}
}


void CSellDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//delete
	m_num = 0;
	UpdateData(FALSE);
}


void CSellDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	int index_1 = c_combo.GetCurSel();
	int index_2 = m_vip.GetCurSel();
	/*CString name_1;
	CString name_2;
	c_combo.GetLBText(index_1, name_1);
	m_vip.GetLBText(index_2, name_2);*/
	int left = getTicketNum(db, orderInfo.fdate, flight[index_1].flightNumber);
	if (index_2) {
		m_price = index_2 == 1 ? flight[index_1].price1 : flight[index_1].price2;
		m_left = index_2 == 1 ? flight[index_1].remain1-(left >> 16) : flight[index_1].remain2 - ((left << 16) >> 16);
		UpdateData(FALSE);
	}
}


void CSellDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Data m_data;
	m_data.DoModal();
	orderInfo.fdate = callbackCount;
}


void CSellDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	order orders[100];
	memset(orders, 0, sizeof(orders));
	getOrder(db, orders, thisUUID);
	CString tmp;
	int n = 0;
	while (orders[n].OUID) n++;
	tmp.Format(_T("%d"), checkOrder(orders, orderInfo, n, thisDate));
	MessageBox(tmp);
}
