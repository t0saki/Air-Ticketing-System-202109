#pragma once


// m_Time 对话框

class m_Time : public CDialogEx
{
	DECLARE_DYNAMIC(m_Time)

public:
	m_Time(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~m_Time();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CComboBox comboHour;
	CComboBox comboMinute;
};
