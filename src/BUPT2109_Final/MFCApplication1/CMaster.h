#pragma once



// CMaster 窗体视图

class CMaster : public CFormView
{
	DECLARE_DYNCREATE(CMaster)

protected:
	CMaster();           // 动态创建所使用的受保护的构造函数
	virtual ~CMaster();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_MASTER };
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
	CEdit m_NewPassword;
	CString m_NewP;
	CString m_SureP;
	CString m_NewE;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton7();
	CString m_Name;
	CString m_airline;
	CString m_email;
	virtual void OnInitialUpdate();
};


