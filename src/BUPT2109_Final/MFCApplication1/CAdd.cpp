// CAdd.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "CAdd.h"

#include "execsqlite3.h"
#include "m_Time.h"
#include "flightSort.h"

double takeOffTime, estTime;
// CAdd

IMPLEMENT_DYNCREATE(CAdd, CFormView)

CAdd::CAdd()
	: CFormView(DIALOG_ADD)
	, m_Flightname(_T(""))
	, m_Airline(_T(""))
	, m_Departure(_T(""))
	, m_Land(_T(""))
	, m_Takeofftime(_T(""))
	, m_Esttime(_T(""))
	, Type(_T(""))
	, m_Ontimeperf(_T(""))
	, m_polite1(_T(""))
	, m_polite2(_T(""))
	, m_price1(_T(""))
	, m_price2(_T(""))
	, m(_T(""))
	, m_remain2(_T(""))
	, m_remain1(_T(""))
{

}

CAdd::~CAdd()
{
}

void CAdd::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Flightname);
	DDX_Text(pDX, IDC_EDIT2, m_Airline);
	DDX_Text(pDX, IDC_EDIT10, m_Departure);
	DDX_Text(pDX, IDC_EDIT11, m_Land);
	DDX_Text(pDX, IDC_EDIT3, m_Takeofftime);
	DDX_Text(pDX, IDC_EDIT4, m_Esttime);
	DDX_Text(pDX, IDC_EDIT5, Type);
	DDX_Text(pDX, IDC_EDIT6, m_Ontimeperf);
	DDX_Text(pDX, IDC_EDIT7, m_polite1);
	DDX_Text(pDX, IDC_EDIT12, m_polite2);
	DDX_Text(pDX, IDC_EDIT13, m_price1);
	DDX_Text(pDX, IDC_EDIT14, m_price2);
	DDX_Text(pDX, IDC_EDIT9, m);
	DDX_Text(pDX, IDC_EDIT15, m_remain2);
	DDX_Text(pDX, IDC_EDIT16, m_remain1);
}

BEGIN_MESSAGE_MAP(CAdd, CFormView)
	ON_BN_CLICKED(IDC_BUTTON5, &CAdd::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON11, &CAdd::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CAdd::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON10, &CAdd::OnBnClickedButton10)
END_MESSAGE_MAP()


// CAdd 诊断

#ifdef _DEBUG
void CAdd::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAdd::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAdd 消息处理程序


void CAdd::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	flightInfo flight;
	UpdateData(TRUE);
	if (m_Flightname.IsEmpty() || m_Airline.IsEmpty() || m_Departure.IsEmpty() || m_Land.IsEmpty() || 
		Type.IsEmpty() || m_Ontimeperf.IsEmpty() || m_polite1.IsEmpty() || m_polite2.IsEmpty() || m_price1.IsEmpty() || m_price2.IsEmpty() ||
		m_remain1.IsEmpty() || m_remain2.IsEmpty())
	{

		MessageBox(TEXT("输入信息有误"));
		return;
	}
	char tmp[100];
	Cstring2Char(m_Flightname,flight.flightNumber);
	Cstring2Char(m_Airline, flight.airline);
	Cstring2Char(m_Departure, flight.departure);
	Cstring2Char(m_Land, flight.land);
	//Cstring2Char(m_Takeofftime, tmp);
	flight.takeOffTime = takeOffTime;
	//Cstring2Char(m_Esttime, tmp);
	flight.estTime = estTime;
	Cstring2Char(Type, flight.type);
	Cstring2Char(m_Ontimeperf, tmp);
	flight.onTimePerf = atof(tmp);
	Cstring2Char(m_polite1, flight.pilot1);
	Cstring2Char(m_polite2, flight.pilot2);
	Cstring2Char(m_price1, tmp);
	flight.price1 = atoi(tmp);
	Cstring2Char(m_price2, tmp);
	flight.price2 = atoi(tmp);
	Cstring2Char(m_remain1, tmp);
	flight.remain1 = atoi(tmp);
	Cstring2Char(m_remain2, tmp);
	flight.remain2 = atoi(tmp);


	flightInfo flights[100];
	memset(flights, 0, sizeof(flight));
	if (i == 1)
		getFlightInfo(db, flights, star);
	else
		getFlightInfo(db, flights, airline);
	int n1 = 0, n2 = 0;
	flightInfo p1[100];
	flightInfo p2[100];
	getFlightInfoByCol(db, p1, "pilot1", flight.pilot1);
	getFlightInfoByCol(db, p2, "pilot2", flight.pilot2);
	while (p1[n1].FUID>=0) n1++;
	while (p2[n2].FUID >= 0) n2++;
	if (checkFlight1(p1, flight, n1) && checkFlight2(p2, flight, n2)) {
		if (addFlight(db, flight))
			MessageBox(TEXT("添加成功"));
		else
			MessageBox(TEXT("失败"));
	} else
		MessageBox(TEXT("conflict"));


}




void CAdd::OnBnClickedButton11()
{
	m_Time m_time;
	m_time.DoModal();
	takeOffTime = callbackCount;
	CString tmp; tmp.Format(_T("%d"), callbackCount);
	GetDlgItem(IDC_BUTTON11)->SetWindowText(tmp);
}


void CAdd::OnBnClickedButton12()
{
	m_Time m_time;
	m_time.DoModal();
	estTime = callbackCount;
	CString tmp; tmp.Format(_T("%d"), callbackCount);
	GetDlgItem(IDC_BUTTON12)->SetWindowText(tmp);
}


void CAdd::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码

}
