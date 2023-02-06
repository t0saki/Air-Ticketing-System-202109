// CListDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CListDlg.h"
#include "execsqlite3.h"
#include "orderSort.h"

//order orders[100];
//memset(orders, 0, sizeof(orders));

// CListDlg

IMPLEMENT_DYNCREATE(CListDlg, CFormView)

CListDlg::CListDlg()
	: CFormView(DIALOG_LIST)
{

}

CListDlg::~CListDlg()
{
}

void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}

BEGIN_MESSAGE_MAP(CListDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CListDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CListDlg::OnBnClickedButton2)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CListDlg::OnColumnclickList1)
END_MESSAGE_MAP()


// CListDlg 诊断

#ifdef _DEBUG
void CListDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CListDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CListDlg 消息处理程序

void CListDlg::changeList() {
	m_List.DeleteAllItems();
	CString tmp;
	ttime tmptime;
	int i = 0;
	while (orders[i].OUID) {
		m_List.InsertItem(i, CString(orders[i].flightNumber));
		//m_list.SetItemText(i, 1, CString(orders[i].takeOffTime));
		//tmp.Format(_T("%.2lf"), orders[i].takeOffTime);
		//m_List.SetItemText(i, 1, tmp);
		int2time(orders[i].takeOffTime, &tmptime);
		tmp.Format(_T("%d:%d"), tmptime.h, tmptime.m);
		m_List.SetItemText(i, 1, tmp);
		int2time(orders[i].estTime, &tmptime);
		tmp.Format(_T("%d:%d"), tmptime.h, tmptime.m);
		m_List.SetItemText(i, 2, tmp);
		m_List.SetItemText(i, 3, orders[i].tier == 1 ? _T("经济舱") : _T("头等舱"));
		tmp.Format(_T("%d"), orders[i].price);
		m_List.SetItemText(i, 4, tmp);
		tmp.Format(_T("%d"), orders[i].number);
		m_List.SetItemText(i, 5, tmp);
		m_List.SetItemText(i, 6, orders[i].isPaid ? _T("已支付") : _T("未支付"));
		tdate tmpdate;
		int2date(orders[i].date, &tmpdate);
		tmp.Format(_T("%d月%d日"), tmpdate.m, tmpdate.d);
		m_List.SetItemText(i, 7, tmp);
		int2date(orders[i].fdate, &tmpdate);
		tmp.Format(_T("%d月%d日"), tmpdate.m, tmpdate.d);
		m_List.SetItemText(i, 8, tmp);
		CString tmp2;
		for (int j = 1; j < orders[i].number; j++) {
			tmp.Format(_T("Y%d%d%c"), (orders[i].OUID * 3539) % 9 + 1, (orders[i].OUID * 2741) % 10, ((orders[i].OUID+j) * 1741) % 5 + 'A');
			tmp2 = tmp2 + tmp+_T(",");
		}
		tmp.Format(_T("Y%d%d%c"), (orders[i].OUID * 3539) % 9 + 1, (orders[i].OUID * 2741) % 10, ((orders[i].OUID + orders[i].number) * 1741) % 5 + 'A');
		tmp2 = tmp2 + tmp;
		m_List.SetItemText(i, 9, tmp2);
		tmp.Format(_T("%d"), orders[i].number* orders[i].price);
		m_List.SetItemText(i, 10, tmp);
		i++;
	}
}


void CListDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类




	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString field[] = { _T("航班号"), _T("起飞时间"), _T("持续时间"), _T("舱位类型"),
		_T("单位票价"), _T("数量"), _T("支付状态"),_T("购买日期"),  _T("出发日期"), _T("座位号"), _T("总价") };

	for (int i = 0; i < 11; i++)
	{
		m_List.InsertColumn(i, field[i], LVCFMT_LEFT, 100);
	}
	UpdateData(FALSE);
	//listv.DeleteAllItems();

	memset(orders, 0, sizeof(orders));
	getOrder(db, orders, thisUUID);
	changeList();
}


void CListDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//支付订单
	int n = m_List.GetSelectionMark();
	if (orders[n].isPaid) {
		MessageBox(TEXT("Already Paid"));
		return;
	}
	if (n<0) {
		MessageBox(TEXT("Not Selected"));
		return;
	}
	if (changePaid(db,orders[n].OUID)) {
		MessageBox(TEXT("Failed"));
	}
	else {
		orders[n].isPaid = 1;
		MessageBox(TEXT("Paid"));
		m_List.SetItemText(n, 6, orders[n].isPaid ? _T("已支付") : _T("未支付"));
		//CListDlg::OnInitialUpdate();
	}

	/*
	CString tmp;
	tmp.Format(_T("%d"), n);
	MessageBox(tmp);*/
}


void CListDlg::OnBnClickedButton2()
{
	//String tmp;
	//tmp.Format(_T("%d"), m_List.GetSelectionMark());
	//MessageBox(tmp);
	int n = m_List.GetSelectionMark();
	if (orders[n].isPaid) {
		MessageBox(TEXT("已支付不得取消"));
		return;
	} else if (deleteOrder(db, orders[n].OUID)) {
		MessageBox(TEXT("失败"));
		return;
	}
	else MessageBox(TEXT("已取消"));

	memset(orders, 0, sizeof(orders));
	getOrder(db, orders, thisUUID);
	changeList();
	// TODO: 在此添加控件通知处理程序代码
}

void CListDlg::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int sn = pNMLV->iSubItem;
	CString tmp;
	tmp.Format(_T("%d"), sn);
	MessageBox(tmp);
	int n = 0;
	while (orders[n].OUID) n++;
	switch (sn) {
	case 1:
		orderSortByTime(orders, n);
		break;
	case 10:
		orderSortByIncome(orders, n);
		break;
	}
	changeList();
}