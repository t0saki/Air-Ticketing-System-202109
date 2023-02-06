#pragma once


// m_Data 对话框

class m_Data : public CDialogEx
{
	DECLARE_DYNAMIC(m_Data)

public:
	m_Data(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~m_Data();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_DATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox comboYear;
	CComboBox comboMonth;
	CComboBox comboDate;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnEditchangeCombo3();
	afx_msg void OnCbnSelchangeCombo3();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnBnClickedButton8();
};
