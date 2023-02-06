#pragma once



// CAlllist 窗体视图

class CAlllist : public CFormView
{
	DECLARE_DYNCREATE(CAlllist)

protected:
	CAlllist();           // 动态创建所使用的受保护的构造函数
	virtual ~CAlllist();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DAILOG_ALLLIST };
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
	CListCtrl m_alllist;
	void changeList();
	virtual void OnInitialUpdate();
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
};


