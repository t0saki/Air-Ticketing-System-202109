#pragma once



// CListDlg 窗体视图

class CListDlg : public CFormView
{
	DECLARE_DYNCREATE(CListDlg)

protected:
	CListDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CListDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_LIST };
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
	void changeList();
	virtual void OnInitialUpdate();
	CListCtrl m_List;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);

};


