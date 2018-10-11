#pragma once


// CDlgCheck 对话框

class CDlgCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCheck)

public:
	CDlgCheck(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCheck();

	BOOL readIni(WCHAR* ini, std::map<TCHAR*,TCHAR*>& mapCatagory,std::map<TCHAR*,TCHAR*>& mapWeather,std::map<TCHAR*,TCHAR*>&mapScene, std::map<TCHAR*,TCHAR*>& mapDay);
// 对话框数据
	enum { IDD = IDD_DLG_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnOk;
	CString m_txtCfg;
	CListCtrl m_listScene;
	CListCtrl m_listTimeOfDay;
	CListCtrl m_listWeather;
	CListCtrl m_listCatarage;
	afx_msg void OnBnClickedButton1();
	CString m_dirpath;
	afx_msg void OnBnClickedBtnCfg();
	afx_msg void OnBnClickedBtnOk();
};
