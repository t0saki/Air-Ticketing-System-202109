#pragma once



// CAdd 窗体视图

class CAdd : public CFormView
{
	DECLARE_DYNCREATE(CAdd)

protected:
	CAdd();           // 动态创建所使用的受保护的构造函数
	virtual ~CAdd();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADD };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Flightname;
	CString m_Airline;
	CString m_Departure;
	CString m_Land;
	CString m_Takeofftime;
	CString m_Esttime;
	CString Type;
	CString m_Ontimeperf;
	CString m_polite1;
	CString m_polite2;
	CString m_price1;
	CString m_price2;
	CString m;
	CString m_remain2;
	CString m_remain1;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton10();
};


