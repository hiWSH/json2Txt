
// Json2TxtDlg.h : 头文件
//

#pragma once


// CJson2TxtDlg 对话框
class CJson2TxtDlg : public CDialogEx
{
// 构造
public:
	CJson2TxtDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JSON2TXT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_inDir;
//	CEdit m_outDir;
	CListCtrl m_listData;
	afx_msg void OnBnClickedOk();
	CString m_outDir;
	CListCtrl m_catarage;
	afx_msg void OnBnClickedBtnCheck();
};
