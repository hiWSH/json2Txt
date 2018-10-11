// Json2TxtDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Json2Txt.h"
#include "Json2TxtDlg.h"
#include "afxdialogex.h"
#include "DlgCheck.h"


using namespace std;
vector<string> vecCategory;
vector<int> vecCategorySum;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int iFileSign;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

extern std::vector<std::string> vecCheckCatagory;
extern std::vector<std::string> vecCheckWeather;
extern std::vector<std::string> vecCheckScene;
extern std::vector<std::string> vecCheckTimeOfDay;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJson2TxtDlg �Ի���




CJson2TxtDlg::CJson2TxtDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJson2TxtDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_inDir = _T("c:\\json|c:\\json2");

	m_outDir = _T("c:\\txt\\");
}

void CJson2TxtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_inDir);
	DDV_MaxChars(pDX, m_inDir, 260);
	//  DDX_Control(pDX, IDC_EDIT2, m_outDir);
	DDX_Control(pDX, IDC_LIST1, m_listData);
	DDX_Text(pDX, IDC_EDIT2, m_outDir);
	DDV_MaxChars(pDX, m_outDir, 260);
	DDX_Control(pDX, IDC_LIST3, m_catarage);
}

BEGIN_MESSAGE_MAP(CJson2TxtDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CJson2TxtDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_CHECK, &CJson2TxtDlg::OnBnClickedBtnCheck)
END_MESSAGE_MAP()


// CJson2TxtDlg ��Ϣ�������

BOOL CJson2TxtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;   

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_listData.GetClientRect(&rect);   

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_listData.SetExtendedStyle(m_listData.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   

	// Ϊ�б���ͼ�ؼ��������   
	m_listData.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width() * 0.05, 0);   
	m_listData.InsertColumn(1, _T("ԭjson·��"), LVCFMT_CENTER, rect.Width() * 0.475, 1);   
	m_listData.InsertColumn(2, _T("Ŀ��txt·��"), LVCFMT_CENTER, rect.Width() * 0.475, 2);   

	CRect rectCat;  
	m_catarage.GetClientRect(&rectCat);   

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_catarage.SetExtendedStyle(m_catarage.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);   
	m_catarage.InsertColumn(0, _T("���"), LVCFMT_CENTER, rectCat.Width() * 0.2, 0);   
	m_catarage.InsertColumn(1, _T("Ŀ����"), LVCFMT_CENTER, rectCat.Width() * 0.6, 1);   
	m_catarage.InsertColumn(2, _T("����"), LVCFMT_CENTER, rectCat.Width() * 0.2, 2);   

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CJson2TxtDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJson2TxtDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CJson2TxtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJson2TxtDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_listData.DeleteAllItems();
	m_catarage.DeleteAllItems();
	iFileSign = 0;

	std::vector<WCHAR*> vSrcCol = split(m_inDir.GetBuffer(0));
	std::string strFile = "";
	wchar_t*  pwcSourcePath = nullptr;
	for (std::vector<WCHAR*>::const_iterator itr=vSrcCol.cbegin();itr!=vSrcCol.cend();itr++)
	{
		DWORD dwFtyp = GetFileAttributes(*itr);
		if (INVALID_FILE_ATTRIBUTES == dwFtyp)
		{
			continue;
		}
		else if(dwFtyp & FILE_ATTRIBUTE_DIRECTORY) //�ļ���
		{
			map<wchar_t* ,int> mPath;
			TraverseDirectory(*itr,mPath);
			for (map<wchar_t*,int>::const_iterator mcitr = mPath.cbegin();mcitr!=mPath.cend();mcitr++)
			{
				strFile = "";
				pwcSourcePath = mcitr->first;
				if (0 == wcscmp(mcitr->first,*itr))continue;
				//�����ļ���
				if (mcitr->second == true)  continue;
				
				char* pcFileData = readfile(mcitr->first);
				if (!pcFileData) continue;
				cJSON * root = cJSON_Parse(pcFileData);
				if (!root) {delete[] pcFileData;continue;}
		
				cJSON * itemAttributes = cJSON_GetObjectItem(root, "attributes");
				if (!itemAttributes) {cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemWeather = cJSON_GetObjectItem(itemAttributes, "weather");
				if (!itemWeather) {cJSON_Delete(root);delete[] pcFileData;continue;}
				if(findStrInVec(vecCheckWeather,itemWeather->valuestring)<0){cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemScene = cJSON_GetObjectItem(itemAttributes, "scene");
				if (!itemScene) {cJSON_Delete(root);delete[] pcFileData;continue;}
				if(findStrInVec(vecCheckScene,itemScene->valuestring)<0){cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemTimeofday = cJSON_GetObjectItem(itemAttributes, "timeofday");
				if (!itemTimeofday) {cJSON_Delete(root);delete[] pcFileData;continue;}
				if(findStrInVec(vecCheckTimeOfDay,itemTimeofday->valuestring)<0){cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemFrames = cJSON_GetObjectItem(root, "frames");
				if (!itemFrames) {cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemFramesChild = itemFrames->child;
				if (!itemFramesChild) {cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemObjects = cJSON_GetObjectItem(itemFramesChild, "objects");
				if (!itemObjects) {cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemObjectsChild = itemObjects->child;
				if (!itemObjectsChild) {cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemObjectsChildNext = itemObjectsChild;

				cJSON * itemObjectsChildBox2d = nullptr;
				cJSON * itemObjectsChildBox2dX1 = nullptr;
				cJSON * itemObjectsChildBox2dX2 = nullptr;
				cJSON * itemObjectsChildBox2dY1 = nullptr;
				cJSON * itemObjectsChildBox2dY2 = nullptr;
				cJSON * itemObjectsChildCategory = nullptr;
				CHAR category[MAX_PATH] = {};
				double X1,X2,Y1,Y2;

				double x,y,w,h;
#define dw 1/1280
#define dh 1/720
				//frames
				//�����ļ�
				
				char cLine[MAX_PATH] = {0};
				int iVecSign = -1;
				do 
				{
					memset(cLine,0x00,sizeof(cLine));
					iVecSign = -1;
					itemObjectsChildBox2d = cJSON_GetObjectItem(itemObjectsChildNext, "box2d");
					if (itemObjectsChildBox2d)
					{
						itemObjectsChildCategory = cJSON_GetObjectItem(itemObjectsChildNext, "category");
						if (itemObjectsChildCategory)sprintf(category,"%s",itemObjectsChildCategory->valuestring);
						if (findStrInVec(vecCheckCatagory,category)>=0)
						{
							itemObjectsChildBox2dX1 = cJSON_GetObjectItem(itemObjectsChildBox2d, "x1");
							if (itemObjectsChildBox2dX1) X1 = itemObjectsChildBox2dX1->valuedouble;

							itemObjectsChildBox2dX2 = cJSON_GetObjectItem(itemObjectsChildBox2d, "x2");
							if (itemObjectsChildBox2dX2) X2 = itemObjectsChildBox2dX2->valuedouble;
					
							itemObjectsChildBox2dY1 = cJSON_GetObjectItem(itemObjectsChildBox2d, "y1");
							if (itemObjectsChildBox2dY1) Y1 = itemObjectsChildBox2dY1->valuedouble;

							itemObjectsChildBox2dY2 = cJSON_GetObjectItem(itemObjectsChildBox2d, "y2");
							if (itemObjectsChildBox2dY2) Y2 = itemObjectsChildBox2dY2->valuedouble;

							iVecSign = findStrInVec(vecCategory,category);
							if (iVecSign < 0 )
							{
								vecCategory.push_back(category);
								vecCategorySum.push_back(1);
								iVecSign = vecCategory.size()-1;
							}
							else
							{
								vecCategorySum[iVecSign] += 1;
							}
							x = (X1+X2)/2 * dw;
							y = (Y1+Y2)/2 * dh;
							w = (X2-X1) * dw;
							h = (Y2-Y1) * dh;
							sprintf(cLine,"%d %.6f %.6f %.6f %.6f\n",iVecSign,x,y,w,h);
							strFile.append(cLine);
						}
					}
					itemObjectsChildNext = itemObjectsChildNext->next;
				} while (itemObjectsChildNext);
				

				cJSON_Delete(root);
				delete[] pcFileData;
				if (strFile.length()>0)
				{
					wchar_t wcAddPath[MAX_PATH] = {};
					memset(wcAddPath,0x00,sizeof(wcAddPath));
					StringCchCopy(wcAddPath,MAX_PATH,m_outDir.GetBuffer(0));
					StringCchCat(wcAddPath,MAX_PATH,mcitr->first+wcslen(*itr)+1);
					WCHAR wcPath[MAX_PATH] = {0};
					WCHAR wcName[MAX_PATH] = {0};
					getPath_Name(wcAddPath,L"\\|/",wcPath,wcName);
					//cout<<*(mcitr->first+wcslen(*itr)+1)<<endl;
					createMultiDir(wcPath);

					wchar_t wcAddPathTxt[MAX_PATH] = {};
					changeSuffix(wcAddPath,L"json",L"txt",wcAddPathTxt);

					WCHAR cFileSign[36] = {0};
					wsprintf(cFileSign,L"%d",iFileSign);
					m_listData.InsertItem(iFileSign, cFileSign);   
					m_listData.SetItemText(iFileSign, 1, mcitr->first);   
					m_listData.SetItemText(iFileSign, 2, wcAddPathTxt); 
					iFileSign++;
					writefile(wcAddPathTxt,strFile);
				}
			}
			mPath.erase(mPath.begin(),mPath.end());
			
		}
		else  //�����ļ�
		{
			strFile = "";
			pwcSourcePath = *itr;
			//�����ļ���

			CHAR* pcFileData = readfile(*itr);
			if (!pcFileData) continue;

			cJSON * root = cJSON_Parse(pcFileData);
			if (!root) {delete[] pcFileData;continue;}

			cJSON * itemAttributes = cJSON_GetObjectItem(root, "attributes");
			if (!itemAttributes) {cJSON_Delete(root);delete[] pcFileData;continue;}

			cJSON * itemWeather = cJSON_GetObjectItem(itemAttributes, "weather");
			if (!itemWeather) {cJSON_Delete(root);delete[] pcFileData;continue;}
			if(findStrInVec(vecCheckWeather,itemWeather->valuestring)<0){cJSON_Delete(root);delete[] pcFileData;continue;}

			cJSON * itemScene = cJSON_GetObjectItem(itemAttributes, "scene");
			if (!itemScene) {cJSON_Delete(root);delete[] pcFileData;continue;}
			if(findStrInVec(vecCheckScene,itemScene->valuestring)<0){cJSON_Delete(root);delete[] pcFileData;continue;}

			cJSON * itemTimeofday = cJSON_GetObjectItem(itemAttributes, "timeofday");
			if (!itemTimeofday) {cJSON_Delete(root);delete[] pcFileData;continue;}
			if(findStrInVec(vecCheckTimeOfDay,itemTimeofday->valuestring)<0){cJSON_Delete(root);delete[] pcFileData;continue;}

			cJSON * itemFrames = cJSON_GetObjectItem(root, "frames");
			if (!itemFrames) {cJSON_Delete(root);delete[] pcFileData;continue;}

			cJSON * itemObjects = cJSON_GetObjectItem(itemFrames, "frames");
			if (!itemObjects) {cJSON_Delete(root);delete[] pcFileData;continue;}

			cJSON * itemObjectsChild = itemObjects->child;
			if (!itemObjectsChild) {cJSON_Delete(root);delete[] pcFileData;continue;}

			cJSON * itemObjectsChildNext = itemObjectsChild;

			cJSON * itemObjectsChildBox2d = nullptr;
			cJSON * itemObjectsChildBox2dX1 = nullptr;
			cJSON * itemObjectsChildBox2dX2 = nullptr;
			cJSON * itemObjectsChildBox2dY1 = nullptr;
			cJSON * itemObjectsChildBox2dY2 = nullptr;
			cJSON * itemObjectsChildCategory = nullptr;
			CHAR category[MAX_PATH] = {};
			double X1,X2,Y1,Y2;

			double x,y,w,h;
#define dw 1/1280
#define dh 1/720
			//frames
			//�����ļ�

			char cLine[MAX_PATH] = {0};
			int iVecSign = -1;
			do 
			{
				memset(cLine,0x00,sizeof(cLine));
				iVecSign = -1;
				itemObjectsChildBox2d = cJSON_GetObjectItem(itemObjectsChildNext, "box2d");
				if (itemObjectsChildBox2d)
				{
					itemObjectsChildCategory = cJSON_GetObjectItem(itemObjectsChildNext, "category");
					if (itemObjectsChildCategory)sprintf(category,"%s",itemObjectsChildCategory->valuestring);
					if (findStrInVec(vecCheckCatagory,category)>=0)
					{
						itemObjectsChildBox2dX1 = cJSON_GetObjectItem(itemObjectsChildBox2d, "x1");
						if (itemObjectsChildBox2dX1) X1 = itemObjectsChildBox2dX1->valuedouble;

						itemObjectsChildBox2dX2 = cJSON_GetObjectItem(itemObjectsChildBox2d, "x2");
						if (itemObjectsChildBox2dX2) X2 = itemObjectsChildBox2dX2->valuedouble;

						itemObjectsChildBox2dY1 = cJSON_GetObjectItem(itemObjectsChildBox2d, "y1");
						if (itemObjectsChildBox2dY1) Y1 = itemObjectsChildBox2dY1->valuedouble;

						itemObjectsChildBox2dY2 = cJSON_GetObjectItem(itemObjectsChildBox2d, "y2");
						if (itemObjectsChildBox2dY2) Y2 = itemObjectsChildBox2dY2->valuedouble;

						iVecSign = findStrInVec(vecCategory,category);
						if (iVecSign < 0 )
						{
							vecCategory.push_back(category);
							vecCategorySum.push_back(1);
							iVecSign = vecCategory.size()-1;
						}
						else
						{
							vecCategorySum[iVecSign] += 1;
						}
						x = (X1+X2)/2 * dw;
						y = (Y1+Y2)/2 * dh;
						w = (X2-X1) * dw;
						h = (Y2-Y1) * dh;
						sprintf(cLine,"%d %.6f %.6f %.6f %.6f\n",iVecSign,x,y,w,h);
						strFile.append(cLine);
					}
				}
				itemObjectsChildNext = itemObjectsChildNext->next;
			} while (itemObjectsChildNext);
			cJSON_Delete(root);
			delete[] pcFileData;

			if (strFile.length()>0)
			{
				wchar_t wcAddPath[MAX_PATH] = {};
				memset(wcAddPath,0x00,sizeof(wcAddPath));
				StringCchCopy(wcAddPath,MAX_PATH,m_outDir.GetBuffer(0));
				WCHAR wcPath[MAX_PATH] = {0};
				WCHAR wcName[MAX_PATH] = {0};
				getPath_Name(*itr,L"\\|/",wcPath,wcName);
				StringCchCat(wcAddPath,MAX_PATH,wcName);
				//cout<<*(mcitr->first+wcslen(*itr)+1)<<endl;
				createMultiDir(wcAddPath);

				wchar_t wcAddPathTxt[MAX_PATH] = {};
				changeSuffix(wcAddPath,L"json",L"txt",wcAddPathTxt);

				WCHAR cFileSign[36] = {0};
				wsprintf(cFileSign,L"%d",iFileSign);
				m_listData.InsertItem(iFileSign, cFileSign);   
				m_listData.SetItemText(iFileSign, 1, *itr);   
				m_listData.SetItemText(iFileSign, 2, wcAddPathTxt); 
				iFileSign++;
				writefile(wcAddPathTxt,strFile);
			}
		}
	}
	//�ļ���
	WCHAR wcSign[36] = {};
	WCHAR wsCategory[MAX_PATH] = {};
	WCHAR wsCategorySum[36] = {};
	for (int i=0; i<vecCategory.size(); i++)
	{
		wsprintf(wcSign,L"%d",i);
		swprintf(wsCategory,L"%hs",vecCategory[i].c_str());
		wsprintf(wsCategorySum,L"%d",vecCategorySum[i]);

		m_catarage.InsertItem(i, wcSign);   
		m_catarage.SetItemText(i, 1, wsCategory);   
		m_catarage.SetItemText(i, 2, wsCategorySum);
	}
	UpdateData(FALSE);
	//CDialogEx::OnOK();
	
}

void CJson2TxtDlg::OnBnClickedBtnCheck()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDlgCheck dlgCheck;
	if (dlgCheck.DoModal() == IDC_BTN_OK)
	{

	}
}
