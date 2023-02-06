// CInfoDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CInfoDlg.h"

#include "execsqlite3.h"
#include "flightSort.h"
#include "m_Data.h"

// CInfoDlg

flightInfo origInfo[100];

int selDate=0;

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(DIALOG_INFO)
	, editDepS(_T(""))
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT1, editDep);
	DDX_Text(pDX, IDC_EDIT1, editDepS);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CInfoDlg::OnColumnclickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInfoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序



void CInfoDlg::changeWindow() {
	CString tmp;
	ttime tmptime;
	int i = 0;
	int left;
	m_list.DeleteAllItems();
	while (flight[i].FUID) {
		left = getTicketNum(db, selDate, flight[i].flightNumber);
		m_list.InsertItem(i, CString(flight[i].flightNumber));
		m_list.SetItemText(i, 1, CString(flight[i].departure));
		m_list.SetItemText(i, 2, CString(flight[i].land));
		int2time(flight[i].takeOffTime, &tmptime);
		tmp.Format(_T("%d:%d"), tmptime.h, tmptime.m);
		m_list.SetItemText(i, 3, tmp);
		int2time(flight[i].estTime, &tmptime);
		tmp.Format(_T("%d:%d"), tmptime.h, tmptime.m);
		m_list.SetItemText(i, 4, tmp);
		tmp.Format(_T("%d"), flight[i].price1);
		m_list.SetItemText(i, 5, tmp);
		tmp.Format(_T("%d"), flight[i].price2);
		m_list.SetItemText(i, 6, tmp);
		tmp.Format(_T("%d"), flight[i].remain1- (left >> 16));
		m_list.SetItemText(i, 7, tmp);
		tmp.Format(_T("%d"), flight[i].remain2- ((left << 16) >> 16));
		m_list.SetItemText(i, 8, tmp);
		int allLeft = ((left >> 16) + ((left << 16) >> 16));
		tmp.Format(_T("%.1f"), ((double)allLeft/ (double)(flight[i].remain1 + flight[i].remain2))*100);
		m_list.SetItemText(i, 9, tmp);
		i++;
	}
	//tmp.Format(_T("Recommend:%s"), flight[0].flightNumber);
	SetDlgItemText(IDC_EDIT2, CString(flight[0].flightNumber));
}

void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	editDepS = _T("*");
	UpdateData(0);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString field[] = { _T("航班号"), _T("出发地"), _T("目的地"), _T("起飞时间"),_T("持续时间"), _T("经济舱票价"), _T("头等舱票价"),_T("经济舱余票数"), _T("头等舱余票数"), _T("上座率") };

	for (int i = 0; i < 10; i++)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_LEFT, 125);
	}

	
	//memset(flight, 0, sizeof(flight));
	memset(origInfo, 0, sizeof(origInfo));
	if (i==1)
		getFlightInfo(db, origInfo, star);
	else
		getFlightInfo(db, origInfo, airline);
	memcpy(flight, origInfo, sizeof(origInfo));
	changeWindow();
}

/*
static int CALLBACK CompareFunc(LPARAM   lParam1, LPARAM   lParam2, LPARAM   lParamSort)
{
	CListCtrl* pListCtrl = (CListCtrl*)lParamSort;//{这里面都是固定语法,适当了解
	LVFINDINFO findInfo;
	findInfo.flags = LVFI_PARAM;
	findInfo.lParam = lParam1;
	int iItem1 = pListCtrl->FindItem(&findInfo, -1);
	findInfo.lParam = lParam2;
	int iItem2 = pListCtrl->FindItem(&findInfo, -1);//这里面都是固定语法,适当了解}

	CString strItem1 = pListCtrl->GetItemText(iItem1, dwSelColID);   //需要研究
	CString strItem2 = pListCtrl->GetItemText(iItem2, dwSelColID);   //需要研究
	char* str1 = (char*)strItem1.GetBuffer(strItem1.GetLength());  //需要研究
	char* str2 = (char*)strItem2.GetBuffer(strItem1.GetLength());  //需要研究


	if (bASC)
		return strcmp(str1, str2);
	else
		return strcmp(str2, str1);
}*/

void CInfoDlg::OnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CString tmp;
	int sn = pNMLV->iSubItem;
	tmp.Format(_T("%d"), sn);
	MessageBox(tmp);
	int n = 0;
	while (flight[n].FUID) n++;
	switch (sn) {
	case 3:
		flightSortByTime(flight, n);
		break;
	case 5:
		flightSortByPrice(flight, n);
		break;
	}
	changeWindow();
}

void CInfoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Data m_data;
	m_data.DoModal();
	selDate = callbackCount;
	changeWindow();
}


void CInfoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(1);
	memset(origInfo, 0, sizeof(origInfo));
	char tmp[100]; Cstring2Char(editDepS, tmp);
	getFlightInfoByCol(db, origInfo, "departure", tmp);
	memcpy(flight, origInfo, sizeof(origInfo));
	changeWindow();
}
