// CAlllist.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CAlllist.h"


#include "execsqlite3.h"
#include "orderSort.h"
// CAlllist

//order orders[100];

IMPLEMENT_DYNCREATE(CAlllist, CFormView)



CAlllist::CAlllist()
	: CFormView(DAILOG_ALLLIST)
{

}

CAlllist::~CAlllist()
{
}

void CAlllist::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_alllist);
}

BEGIN_MESSAGE_MAP(CAlllist, CFormView)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CAlllist::OnColumnclickList1)
END_MESSAGE_MAP()


// CAlllist 诊断

#ifdef _DEBUG
void CAlllist::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAlllist::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAlllist 消息处理程序

void CAlllist::changeList() {
	m_alllist.DeleteAllItems();
	CString tmp;
	ttime tmptime;
	int i = 0;
	while (orders[i].OUID) {
		m_alllist.InsertItem(i, getUserName(orders[i].UUID));
		//m_alllist.SetItemText(i, 1, CString(orders[i].takeOffTime));
		//tmp.Format(_T("%.2lf"), orders[i].takeOffTime);
		//m_alllist.SetItemText(i, 1, tmp);
		m_alllist.SetItemText(i, 1, CString(orders[i].flightNumber));
		int2time(orders[i].takeOffTime, &tmptime);
		tmp.Format(_T("%d:%d"), tmptime.h, tmptime.m);
		m_alllist.SetItemText(i, 2, tmp);
		int2time(orders[i].estTime, &tmptime);
		tmp.Format(_T("%d:%d"), tmptime.h, tmptime.m);
		m_alllist.SetItemText(i, 3, tmp);
		m_alllist.SetItemText(i, 4, orders[i].tier == 1 ? _T("经济舱") : _T("头等舱"));
		tmp.Format(_T("%d"), orders[i].price);
		m_alllist.SetItemText(i, 5, tmp);
		tmp.Format(_T("%d"), orders[i].number);
		m_alllist.SetItemText(i, 6, tmp);
		m_alllist.SetItemText(i, 7, orders[i].isPaid ? _T("已支付") : _T("未支付"));
		tdate tmpdate;
		int2date(orders[i].date, &tmpdate);
		tmp.Format(_T("%d月%d日"), tmpdate.m, tmpdate.d);
		m_alllist.SetItemText(i, 8, tmp);
		int2date(orders[i].fdate, &tmpdate);
		tmp.Format(_T("%d月%d日"), tmpdate.m, tmpdate.d);
		m_alllist.SetItemText(i, 9, tmp);
		CString tmp2;
		for (int j = 1; j < orders[i].number; j++) {
			tmp.Format(_T("Y%d%d%c"), (orders[i].OUID * 3539) % 9 + 1, (orders[i].OUID * 2741) % 10, ((orders[i].OUID + j) * 1741) % 5 + 'A');
			tmp2 = tmp2 + tmp + _T(",");
		}
		tmp.Format(_T("Y%d%d%c"), (orders[i].OUID * 3539) % 9 + 1, (orders[i].OUID * 2741) % 10, ((orders[i].OUID + orders[i].number) * 1741) % 5 + 'A');
		tmp2 = tmp2 + tmp;
		m_alllist.SetItemText(i, 10, tmp2);
		tmp.Format(_T("%d"), orders[i].number * orders[i].price);
		m_alllist.SetItemText(i, 11, tmp);
		i++;
	}
}


void CAlllist::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_alllist.SetExtendedStyle(m_alllist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString field[] = { _T("用户名"),_T("航班号"), _T("起飞时间"), _T("持续时间"), _T("舱位类型"),
		_T("单位票价"), _T("数量"), _T("支付状态"),_T("购买日期"),  _T("出发日期"), _T("座位号"), _T("总价") };

	for (int i = 0; i < 12; i++)
	{
		m_alllist.InsertColumn(i, field[i], LVCFMT_LEFT, 100);
	}
	UpdateData(FALSE);
	//order orders[100];
	memset(orders, 0, sizeof(orders));
	getOrderByAl(db, orders, airline);

	changeList();

}


void CAlllist::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
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
	case 2:
		orderSortByTime(orders, n);
		break;
	case 11:
		orderSortByIncome(orders, n);
		break;
	}
	changeList();
}