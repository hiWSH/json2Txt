
// Json2TxtDlg.h : ͷ�ļ�
//

#pragma once


// CJson2TxtDlg �Ի���
class CJson2TxtDlg : public CDialogEx
{
// ����
public:
	CJson2TxtDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JSON2TXT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
