// DlgCheck.cpp : 实现文件
//

#include "stdafx.h"
#include "Json2Txt.h"
#include "DlgCheck.h"
#include "afxdialogex.h"
#include "Json2TxtDlg.h"

std::vector<std::string> vecCheckCatagory;
std::vector<std::string> vecCheckWeather;
std::vector<std::string> vecCheckScene;
std::vector<std::string> vecCheckTimeOfDay;
// CDlgCheck 对话框

IMPLEMENT_DYNAMIC(CDlgCheck, CDialogEx)

BOOL CDlgCheck::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	
	// TODO: 在此添加额外的初始化代码
	  

	// 为列表视图控件添加全行选中和栅格风格   
	m_listCatarage.SetExtendedStyle(LVS_EX_CHECKBOXES);

	m_listWeather.SetExtendedStyle(LVS_EX_CHECKBOXES);

	m_listScene.SetExtendedStyle(LVS_EX_CHECKBOXES);

	m_listTimeOfDay.SetExtendedStyle(LVS_EX_CHECKBOXES);

	CRect  rect;
	m_listCatarage.GetClientRect(&rect); 
	m_listCatarage.InsertColumn(0,_T("特征"),LVCFMT_CENTER,rect.Width()); 

	m_listWeather.GetClientRect(&rect); 
	m_listWeather.InsertColumn(0,_T("天气"),LVCFMT_CENTER,rect.Width()); 

	m_listScene.GetClientRect(&rect); 
	m_listScene.InsertColumn(0,_T("场景"),LVCFMT_CENTER,rect.Width()); 

	m_listTimeOfDay.GetClientRect(&rect); 
	m_listTimeOfDay.InsertColumn(0,_T("时间"),LVCFMT_CENTER,rect.Width()); 


	//readini
	std::map<TCHAR*,TCHAR*> mapCatagory;
	std::map<TCHAR*,TCHAR*> mapWeather;
	std::map<TCHAR*,TCHAR*> mapScene;
	std::map<TCHAR*,TCHAR*> mapDay;

	std::vector<std::string> vecCatagory;
	std::vector<std::string> vecWeather;
	std::vector<std::string> vecScene;
	std::vector<std::string> vecDay;

	bool bRdIni = readIni(m_txtCfg.GetBuffer(0),mapCatagory,mapWeather,mapScene,mapDay);

	int iCatagory = 0;
	int iScene = 0;
	int iWeather = 0;
	int iTimeOfDay = 0;

	m_listCatarage.SetExtendedStyle(LVS_EX_CHECKBOXES);

	m_listWeather.SetExtendedStyle(LVS_EX_CHECKBOXES);

	m_listScene.SetExtendedStyle(LVS_EX_CHECKBOXES);

	m_listTimeOfDay.SetExtendedStyle(LVS_EX_CHECKBOXES);

	

	if (bRdIni) //读取配置文件成功，刷新页面
	{ 
		for(std::map<TCHAR*,TCHAR*>::iterator iter = mapCatagory.begin(); iter != mapCatagory.end(); iter++)  
		{
			m_listCatarage.InsertItem(iCatagory,iter->second);//temp为字符串型，即你要添加的复选框的文本
			m_listCatarage.SetCheck(iCatagory,true);
			iCatagory++;
		}
		for(std::map<TCHAR*,TCHAR*>::iterator iter = mapWeather.begin(); iter != mapWeather.end(); iter++)  
		{
			m_listWeather.InsertItem(iWeather,iter->second);//temp为字符串型，即你要添加的复选框的文本
			m_listWeather.SetCheck(iWeather,true);
			iWeather++;
		}
		for(std::map<TCHAR*,TCHAR*>::iterator iter = mapScene.begin(); iter != mapScene.end(); iter++)  
		{
			m_listScene.InsertItem(iScene,iter->second);//temp为字符串型，即你要添加的复选框的文本
			m_listScene.SetCheck(iScene,true);
			iScene++;
		}
		for(std::map<TCHAR*,TCHAR*>::iterator iter = mapDay.begin(); iter != mapDay.end(); iter++)  
		{
			m_listTimeOfDay.InsertItem(iTimeOfDay,iter->second);//temp为字符串型，即你要添加的复选框的文本
			m_listTimeOfDay.SetCheck(iTimeOfDay,true);
			iTimeOfDay++;
		}
	}
	else //读取配置文件不成功 需读取原文件获取数据 写入配置文件
	{
		getVecByJson(m_dirpath.GetBuffer(0),vecCatagory,vecWeather,vecScene,vecDay);
		std::wstring wsTemp;
		WCHAR wcKey[36] = {};
		for(std::vector<std::string>::iterator iter = vecCatagory.begin(); iter != vecCatagory.end(); iter++)  
		{
			StringToWstring(wsTemp,iter->c_str());
			m_listCatarage.InsertItem(iCatagory,wsTemp.c_str());//temp为字符串型，即你要添加的复选框的文本
			m_listCatarage.SetCheck(iCatagory,true);
			wsprintf(wcKey,L"%d",iCatagory);
			WritePrivateProfileString(L"category",wcKey,wsTemp.c_str(),m_txtCfg.GetBuffer(0));
			iCatagory++;
		}
		for(std::vector<std::string>::iterator iter = vecWeather.begin(); iter != vecWeather.end(); iter++)  
		{
			StringToWstring(wsTemp,iter->c_str());
			m_listWeather.InsertItem(iWeather,wsTemp.c_str());//temp为字符串型，即你要添加的复选框的文本
			m_listWeather.SetCheck(iWeather,true);
			wsprintf(wcKey,L"%d",iWeather);
			WritePrivateProfileString(L"weather",wcKey,wsTemp.c_str(),m_txtCfg.GetBuffer(0));
			iWeather++;
		}
		for(std::vector<std::string>::iterator iter = vecScene.begin(); iter != vecScene.end(); iter++)  
		{
			StringToWstring(wsTemp,iter->c_str());
			m_listScene.InsertItem(iScene,wsTemp.c_str());//temp为字符串型，即你要添加的复选框的文本
			m_listScene.SetCheck(iScene,true);
			wsprintf(wcKey,L"%d",iScene);
			WritePrivateProfileString(L"scene",wcKey,wsTemp.c_str(),m_txtCfg.GetBuffer(0));
			iScene++;
		}
		for(std::vector<std::string>::iterator iter = vecDay.begin(); iter != vecDay.end(); iter++)  
		{
			StringToWstring(wsTemp,iter->c_str());
			m_listTimeOfDay.InsertItem(iTimeOfDay,wsTemp.c_str());//temp为字符串型，即你要添加的复选框的文本
			m_listTimeOfDay.SetCheck(iTimeOfDay,true);
			wsprintf(wcKey,L"%d",iTimeOfDay);
			WritePrivateProfileString(L"timeofday",wcKey,wsTemp.c_str(),m_txtCfg.GetBuffer(0));
			iTimeOfDay++;
		}
	}

	// 为列表视图控件添加三列   
//	m_listData.InsertColumn(0, _T("序号"), LVCFMT_CENTER, rect.Width() * 0.05, 0);   
//	m_listData.InsertColumn(1, _T("原json路径"), LVCFMT_CENTER, rect.Width() * 0.475, 1);   
//	m_listData.InsertColumn(2, _T("目标txt路径"), LVCFMT_CENTER, rect.Width() * 0.475, 2);   

//	CRect rectCat;  
//	m_catarage.GetClientRect(&rectCat);   

	mapCatagory.erase(mapCatagory.begin(),mapCatagory.end());
	mapWeather.erase(mapWeather.begin(),mapWeather.end());
	mapScene.erase(mapScene.begin(),mapScene.end());
	mapDay.erase(mapDay.begin(),mapDay.end());

	vecCatagory.erase(vecCatagory.begin(),vecCatagory.end());
	vecWeather.erase(vecWeather.begin(),vecWeather.end());
	vecScene.erase(vecScene.begin(),vecScene.end());
	vecDay.erase(vecDay.begin(),vecDay.end());
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


BOOL CDlgCheck::readIni(WCHAR* ini, std::map<TCHAR*,TCHAR*>& mapCatagory,std::map<TCHAR*,TCHAR*>& mapWeather,std::map<TCHAR*,TCHAR*>&mapScene, std::map<TCHAR*,TCHAR*>& mapDay)
{
	DWORD dwAttr;
	try{
		dwAttr = GetFileAttributes(ini);  
	}catch(char* e){
		return false;
	}

	if (dwAttr == INVALID_FILE_ATTRIBUTES) 
	{
		return false;
	}
	else if (dwAttr & FILE_ATTRIBUTE_DIRECTORY) 
	{
		return false;
	}

	readIniSection(ini,CATAGORY,mapCatagory);
	readIniSection(ini,WEATHER,mapWeather);
	readIniSection(ini,SCENE,mapScene);
	readIniSection(ini,TIMEOFDAY,mapDay);
	return true;
}

CDlgCheck::CDlgCheck(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCheck::IDD, pParent)
{

	m_txtCfg = _T("c:\\cfg\\json.ini");
	m_dirpath = _T("c:\\json|c:\\json2");
}

CDlgCheck::~CDlgCheck()
{
}

void CDlgCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btnOk);
	DDX_Text(pDX, IDC_EDIT_CFG, m_txtCfg);
	DDX_Control(pDX, IDC_LIST_SCENE, m_listScene);
	DDX_Control(pDX, IDC_LIST_TIMEOFDAY, m_listTimeOfDay);
	DDX_Control(pDX, IDC_LIST_WEATHER, m_listWeather);
	DDX_Control(pDX, IDC_LIST4, m_listCatarage);
	DDX_Text(pDX, IDC_TXT_DATA, m_dirpath);
}


BEGIN_MESSAGE_MAP(CDlgCheck, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CFG, &CDlgCheck::OnBnClickedBtnCfg)
	ON_BN_CLICKED(IDC_BTN_OK, &CDlgCheck::OnBnClickedBtnOk)
END_MESSAGE_MAP()


// CDlgCheck 消息处理程序

/*

void CDlgCheck::OnBnClickedButton1()
{
	CJson2TxtDlg dlg;
	dlg.DoModal();

}
*/

void CDlgCheck::OnBnClickedBtnCfg()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_listCatarage.DeleteAllItems();
	m_listScene.DeleteAllItems();
	m_listTimeOfDay.DeleteAllItems();
	m_listWeather.DeleteAllItems();

	std::vector<std::string> vecCatagory;
	std::vector<std::string> vecWeather;
	std::vector<std::string> vecScene;
	std::vector<std::string> vecDay;

	int iCatagory = 0;
	int iScene = 0;
	int iWeather = 0;
	int iTimeOfDay = 0;

	getVecByJson(m_dirpath.GetBuffer(0),vecCatagory,vecWeather,vecScene,vecDay);
	std::wstring wsTemp;
	WCHAR wcKey[36] = {};
	for(std::vector<std::string>::iterator iter = vecCatagory.begin(); iter != vecCatagory.end(); iter++)  
	{
		StringToWstring(wsTemp,iter->c_str());
		m_listCatarage.InsertItem(iCatagory,wsTemp.c_str());//temp为字符串型，即你要添加的复选框的文本
		m_listCatarage.SetCheck(iCatagory,true);
		wsprintf(wcKey,L"%d",iCatagory);
		WritePrivateProfileString(L"category",wcKey,wsTemp.c_str(),m_txtCfg.GetBuffer(0));
		iCatagory++;
	}
	for(std::vector<std::string>::iterator iter = vecWeather.begin(); iter != vecWeather.end(); iter++)  
	{
		StringToWstring(wsTemp,iter->c_str());
		m_listWeather.InsertItem(iWeather,wsTemp.c_str());//temp为字符串型，即你要添加的复选框的文本
		m_listWeather.SetCheck(iWeather,true);
		wsprintf(wcKey,L"%d",iWeather);
		WritePrivateProfileString(L"weather",wcKey,wsTemp.c_str(),m_txtCfg.GetBuffer(0));
		iWeather++;
	}
	for(std::vector<std::string>::iterator iter = vecScene.begin(); iter != vecScene.end(); iter++)  
	{
		StringToWstring(wsTemp,iter->c_str());
		m_listScene.InsertItem(iScene,wsTemp.c_str());//temp为字符串型，即你要添加的复选框的文本
		m_listScene.SetCheck(iScene,true);
		wsprintf(wcKey,L"%d",iScene);
		WritePrivateProfileString(L"scene",wcKey,wsTemp.c_str(),m_txtCfg.GetBuffer(0));
		iScene++;
	}
	for(std::vector<std::string>::iterator iter = vecDay.begin(); iter != vecDay.end(); iter++)  
	{
		StringToWstring(wsTemp,iter->c_str());
		m_listTimeOfDay.InsertItem(iTimeOfDay,wsTemp.c_str());//temp为字符串型，即你要添加的复选框的文本
		m_listTimeOfDay.SetCheck(iTimeOfDay,true);
		wsprintf(wcKey,L"%d",iTimeOfDay);
		WritePrivateProfileString(L"timeofday",wcKey,wsTemp.c_str(),m_txtCfg.GetBuffer(0));
		iTimeOfDay++;
	}

	vecCatagory.erase(vecCatagory.begin(),vecCatagory.end());
	vecWeather.erase(vecWeather.begin(),vecWeather.end());
	vecScene.erase(vecScene.begin(),vecScene.end());
	vecDay.erase(vecDay.begin(),vecDay.end());

	UpdateData(FALSE);
}


void CDlgCheck::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	std::vector<std::string> vecEmpty;
	vecCheckCatagory.swap(vecEmpty);
	vecCheckTimeOfDay.swap(vecEmpty);
	vecCheckWeather.swap(vecEmpty);
	vecCheckScene.swap(vecEmpty);

	std::string strTemp = "";
	for(int nItem=0; nItem<m_listCatarage.GetItemCount(); nItem++)
	{
		if(! m_listCatarage.GetCheck(nItem))
			continue;
		strTemp = "";
		Wchar_tToString(strTemp,m_listCatarage.GetItemText(nItem, 0).GetBuffer(0));
		vecCheckCatagory.push_back(strTemp);
	}

	for(int nItem=0; nItem<m_listTimeOfDay.GetItemCount(); nItem++)
	{
		if(!m_listTimeOfDay.GetCheck(nItem))
			continue;
		strTemp = "";
		Wchar_tToString(strTemp,m_listTimeOfDay.GetItemText(nItem, 0).GetBuffer(0));
		vecCheckTimeOfDay.push_back(strTemp);
	}

	for(int nItem=0; nItem<m_listWeather.GetItemCount(); nItem++)
	{
		if(!m_listWeather.GetCheck(nItem))
			continue;
		strTemp = "";
		Wchar_tToString(strTemp,m_listWeather.GetItemText(nItem, 0).GetBuffer(0));
		vecCheckWeather.push_back(strTemp);
	}

	for(int nItem=0; nItem<m_listScene.GetItemCount(); nItem++)
	{
		if(!m_listScene.GetCheck(nItem))
			continue;
		strTemp = "";
		Wchar_tToString(strTemp,m_listScene.GetItemText(nItem, 0).GetBuffer(0));
		vecCheckScene.push_back(strTemp);
	}
	GetParent()->ShowWindow(SW_SHOW);
	OnCancel(); //or OnOK();
	//UpdateData(FALSE);
}
