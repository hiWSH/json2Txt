#include "stdafx.h"
#include "opfileUtil.h"

#include "stdafx.h"
#include "strsafe.h"
// Ψһ��Ӧ�ó������
#include <wininet.h>
#pragma comment(lib,"wininet.lib")

#include<vector>
using namespace std;

static  wchar_t wsPathSplit[] = L"\\|/"; //�ļ�·���ָ�������
static  char    csPathSplit[] = "\\|/"; //�ļ�·���ָ�������

template<class T>
void freeVector(std::vector<T> v)
{
	for (vector<T>::iterator it = v.begin(); it != v.end(); it++) 
		if (NULL != *it) 
		{
			delete *it; 
			*it = NULL;
		}
		v.clear();
}
/*

aim:�����Ժ���Ը��ݷָ����չѹ���ļ�����
author:wsh
time:20180403
input:
	string strTime:��Ҫ�ָ���ַ���
output:
	vector<WCHAR*>:�ָ�󱣴��vector����
*/
std::vector<WCHAR*> split(const WCHAR* strTime)  
{  
	std::vector<WCHAR*> result;   
	unsigned int pos = 0;//�ַ���������ǣ����㽫���һ��������vector  
	size_t i;
	for( i = 0; i < wcslen(strTime); i++)  
	{  
		if(strTime[i] == '|' || strTime[i] == '=')  
		{  
			WCHAR* temp = new WCHAR[i-pos+1];
			memset(temp,0x00,sizeof(WCHAR));
			wcsncpy(temp,strTime+pos,i-pos);
			temp[i-pos] = 0x00;
			result.push_back(temp); 
			pos=i+1;
		}  
	}  
	//�ж����һ��
	if (pos < i)
	{
		WCHAR* temp = new WCHAR[i-pos+1];
		memset(temp,0x00,sizeof(WCHAR));
		wcsncpy(temp,strTime+pos,i-pos);
		temp[i-pos] = 0x00;
		result.push_back(temp);
	}
	return result;  
} 

const wchar_t* wcstrrchr(const wchar_t* str, const wchar_t wc)  
{  
	const wchar_t* pwc = NULL;  
	for (int i=wcslen(str)-1;i>=0;i--)  
	{  
		if (str[i] == wc)  
		{  
			pwc = str + i;  
			break;  
		}  
	}  
	return pwc;  
}  

const wchar_t* wcstrrchr(const wchar_t* str, const wchar_t* wc) //wc��ʽ"\\|/"����'\\"��'/'2�ַָ�
{
	std::vector<WCHAR*>  vec = split(wc);
	
	const wchar_t* pwc = NULL; 
	for (int i=wcslen(str)-1;i>=0;i--)  
	{  
		for (std::vector<WCHAR*>::const_iterator itr = vec.cbegin();itr!=vec.cend();itr++)
		{	
			if (wcsncmp(&str[i],*itr,1) == 0)  
			{  
				pwc = str + i;  
				freeVector<wchar_t*>(vec);
				return pwc;  
			}  
		}
		
	}  
	freeVector<wchar_t*>(vec);
	return pwc;  
}

void getPath_Name(const wchar_t* str, const wchar_t* wc,wchar_t* wsPath, wchar_t* wsName)
{
	const wchar_t* pwc = wcstrrchr(str,wc);
	wsPath[0]=0;  
	wsName[0]=0;
	if (pwc)
	{
		for (int i=0; i<pwc-str; i++)  
			wsPath[i] = *(str+i); 
		StringCchCopy(wsName,MAX_PATH,pwc+1);
	}
}

std::vector<char*> split(const char* strTime)  
{  
	std::vector<char*> result;   
	unsigned int pos = 0;//�ַ���������ǣ����㽫���һ��������vector  
	size_t i;
	for( i = 0; i < strlen(strTime); i++)  
	{  
		if(strTime[i] == '|' || strTime[i] == '=')  
		{  
			char* temp = new char[i-pos+1];
			memset(temp,0x00,sizeof(temp));
			strncpy(temp,strTime+pos,i-pos);
			temp[i-pos] = 0x00;
			result.push_back(temp); 
			pos=i+1;
		}  
	}  
	//�ж����һ��
	if (pos < i)
	{
		char* temp = new char[i-pos+1];
		memset(temp,0x00,sizeof(temp));
		strncpy(temp,strTime+pos,i-pos);
		temp[i-pos] = 0x00;
		result.push_back(temp);
	}
	return result;  
} 

const char* wcstrrchr(const char* str, const char* wc) //wc��ʽ"\\|/"����'\\"��'/'2�ַָ�
{
	std::vector<char*>  vec = split(wc);

	const char* pwc = NULL; 
	for (int i=strlen(str)-1;i>=0;i--)  
	{  
		for (std::vector<char*>::const_iterator itr = vec.cbegin();itr!=vec.cend();itr++)
		{	
			if (strncmp(&str[i],*itr,1) == 0)  
			{  
				pwc = str + i;  
				freeVector<char*>(vec);
				return pwc;  
			}  
		}

	}  
	freeVector<char*>(vec);
	return pwc;  
}

void getPath_Name(const char* str, const char* wc,char* wsPath, char* wsName)
{
	const char* pwc = wcstrrchr(str,wc);
	wsPath[0] = 0;
	wsName[0] = 0;
	if (pwc)
	{
		for (int i=0; i<pwc-str; i++)  
			wsPath[i] = *(str+i); 
		sprintf_s(wsName,MAX_PATH,"%s",pwc+1);
	}
}



bool createMultiDir(const wchar_t* path)  
{  
	if (path == NULL) return false;  
	if (PathIsDirectory(path)) return true;  

	wchar_t wsSubPath[MAX_PATH] = {}; 
	wchar_t wsSubName[MAX_PATH] = {};
	getPath_Name(path, wsPathSplit,wsSubPath,wsSubName); 
	if (wcslen(wsSubPath) > 0 )
	{
		createMultiDir(wsSubPath);
	}
	if(CreateDirectory(path,NULL)) return true;  
	return false;  
} 

bool createMultiDir(const char* path)  
{  
	if (path == NULL) return false;  
	if (PathIsDirectoryA(path)) return true;  

	char csSubPath[MAX_PATH] = {}; 
	char csSubName[MAX_PATH] = {};
	getPath_Name(path, csPathSplit,csSubPath,csSubName); 
	if (strlen(csSubPath) )
		createMultiDir(csSubPath);
	if(CreateDirectoryA(path,NULL)) return true;  
	return false;  
} 

char* readfile(WCHAR* filename)
{
	
	HANDLE hFile = CreateFile(filename,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	
	DWORD dwHigh = 0;  
	DWORD dwSize = ::GetFileSize(hFile, &dwHigh);  
	__int64 nSize2 = ((__int64)dwHigh << 32) + dwSize;//���ڴ��ļ���Ҫ����32λ�͵�32λƴ�ӳ�64λ����  
	
	char* pcsData = new char[nSize2 + (__int64)1];
	memset(pcsData,0,sizeof(pcsData));
	DWORD dwReadSize;
	if(!ReadFile(hFile,pcsData,nSize2+(__int64)1,&dwReadSize,NULL)){
		delete[] pcsData;
		CloseHandle(hFile);
		return nullptr;
	}
	CloseHandle(hFile);
	return pcsData;
}


std::string WcharToChar(const wchar_t* wp, size_t m_encode)
{
	std::string str;
	int len = WideCharToMultiByte(m_encode, 0, wp, -1, NULL, 0, NULL, NULL);
	char	*m_char = new char[len + 1];
	memset(m_char, 0, sizeof(char)*(len+1));
	WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	str = m_char;
	delete m_char;
	return str;
}

int findStrInVec(std::vector<std::string>& vec, char* str)
{
	int iRet = -1;
	for (int i=0; i<vec.size(); i++)
	{
		if (0 == strcmp(str,vec[i].c_str()))
		{
			iRet = i;
			break;
		}
	}
	return iRet;
}

bool writefile(WCHAR* filename, std::string content)
{
	

	HANDLE hFile = CreateFile(filename,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	
	DWORD dwWriteSize;
	if(!WriteFile(hFile,content.c_str(),content.length(),&dwWriteSize,NULL)){
		CloseHandle(hFile);
		return false;
	}
	CloseHandle(hFile);
    return true;
}

bool changeSuffix(WCHAR* filename, WCHAR* oldSuffix, WCHAR* newSuffix,WCHAR* newFilename)
{
	int iLen = wcslen(filename);
	StringCchCopy(newFilename,MAX_PATH,filename);
	for (int i = iLen-1; i>=0; i--)
	{
		if (L'.' == filename[i])
		{
			WCHAR wcTemp[MAX_PATH] = {};
			wsprintf(wcTemp,L"%s",filename+i+1);
			if (0 == wcscmp(wcTemp,oldSuffix))
			{
				StringCchCopy(newFilename+i+1,MAX_PATH,newSuffix);
				return true;
			}
			return false;
		}
	}
	return false;
}

void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,wText,-1,NULL,0,NULL,FALSE);// WideCharToMultiByte������
	char *psText; // psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
	psText = new char[dwNum];
	WideCharToMultiByte (CP_OEMCP,NULL,wText,-1,psText,dwNum,NULL,FALSE);// WideCharToMultiByte���ٴ�����
	szDst = psText;// std::string��ֵ
	delete []psText;// psText�����
}

// string to wstring
void StringToWstring(std::wstring& szDst, std::string str)
{
	std::string temp = str;
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL,0); 
	wchar_t * wszUtf8 = new wchar_t[len+1]; 
	memset(wszUtf8, 0, len * 2 + 2); 
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);
	szDst = wszUtf8;
	std::wstring r = wszUtf8;
	delete[] wszUtf8;
}
bool readIniSection(TCHAR* ini, TCHAR* section, std::map<TCHAR*,TCHAR*>& map)
{
	TCHAR szBuf[1024];
	memset(szBuf,0,1024);
	TCHAR szWork[_MAX_PATH];
	memset(szWork,0,_MAX_PATH);
	INT nNum = 0;
	INT nCount = 0;
	INT nLen = 0;
	
	nNum = ::GetPrivateProfileSection(section,szBuf,1024,ini);
	nLen = _tcslen(szBuf);
	TCHAR* p = szBuf;
	std::string strKey;
	std::string strValue;
	while(nLen < nNum)
	{
		_tcscpy(szWork,p);//�˴���szWorkΪ��������
		
		for (int i=0; i<wcslen(szWork); i++)
		{
			if (i == wcslen(szWork)-1)
			{
				TCHAR* szWorkKey = new TCHAR[MAX_PATH];
				TCHAR* szWorkValue = new TCHAR[MAX_PATH];
				memset(szWorkKey,0x00,sizeof(szWorkKey));
				memset(szWorkValue,0x00,sizeof(szWorkValue));
				_tcscpy(szWorkKey,szWork);
				map.insert(make_pair<TCHAR*,TCHAR*>(szWorkKey,L""));
				break;
			}
			if (szWork[i] == L'=')
			{
				TCHAR* szWorkKey = new TCHAR[MAX_PATH];
				TCHAR* szWorkValue = new TCHAR[MAX_PATH];
				memset(szWorkKey,0x00,sizeof(szWorkKey));
				memset(szWorkValue,0x00,sizeof(szWorkValue));
				_tcsncpy(szWorkKey,szWork,i);
				_tcsncpy(szWorkValue,szWork+i+1,wcslen(szWork)-i-1);
				szWorkValue[wcslen(szWork)-i-1] = 0x00;
				map.insert(make_pair<TCHAR*,TCHAR*>(szWorkKey,szWorkValue));
				break;
			}
		}
		nLen = nLen + 1;
		p = &szBuf[nLen];
		nLen += _tcslen(p);


	}
	return true;
}



errno_t getFullName(WCHAR* path,WCHAR* fullName)
{
	//�õ��ļ���
	WCHAR path_buffer[_MAX_PATH] = {};
	WCHAR drive[_MAX_DRIVE]= {};
	WCHAR dir[_MAX_DIR]= {};
	WCHAR fname[_MAX_FNAME]= {};
	WCHAR ext[_MAX_EXT]= {};
	memset(fullName,0x00,sizeof(fullName));
	errno_t ret = _wsplitpath_s(path,drive,dir,fname,ext);
	StringCchCopy(fullName,MAX_PATH,fname);
	StringCchCat(fullName,MAX_PATH,ext);
	return ret;
}

int getLastFolderName(WCHAR* path,WCHAR* folderName)
{
	int lenPath = wcslen(path);
	for (;lenPath;lenPath--)
		if (path[lenPath-1] == '\\')
			break;
	StringCchCopy(folderName,MAX_PATH,path+lenPath);
	return 0;
}

//����Ҫ�������ļ���·������������Ӧ�ļ��� �õ��ļ�����Ҷ�ӽڵ� 
void TraverseDirectory(wchar_t Dir[MAX_PATH],std::map<wchar_t*,int> &m)      
{  
	WIN32_FIND_DATA FindFileData;  
	HANDLE hFind=INVALID_HANDLE_VALUE;  
	wchar_t DirSpec[MAX_PATH];                  //����Ҫ�������ļ��е�Ŀ¼  
	DWORD dwError = 0;  
	StringCchCopy(DirSpec,MAX_PATH,Dir);  
	StringCchCat(DirSpec,MAX_PATH,TEXT("\\*"));   //����Ҫ�������ļ��е�����·��\*  
	bool bIsEmptyFolder = true;
	hFind=FindFirstFile(DirSpec,&FindFileData);          //�ҵ��ļ����еĵ�һ���ļ�  

	if(hFind==INVALID_HANDLE_VALUE)                               //���hFind�������ʧ�ܣ����������Ϣ  
	{  
		FindClose(hFind); 
		wchar_t* path = new wchar_t[MAX_PATH];
		memset(path,0x00,sizeof(path));
		StringCchCopy(path,MAX_PATH,Dir);
		m.insert(make_pair(path,true)); //�ļ�������
		return;    
	}  
	else   
	{   
		while(FindNextFile(hFind,&FindFileData)!=0)                            //���ļ������ļ��д���ʱ  
		{  
			if((FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)!=0&&wcscmp(FindFileData.cFileName,L".")==0||wcscmp(FindFileData.cFileName,L"..")==0)        //�ж����ļ���&&��ʾΪ"."||��ʾΪ"."  
			{  
				continue;  
			}  
			wchar_t DirAdd[MAX_PATH];  
			StringCchCopy(DirAdd,MAX_PATH,Dir);  
			StringCchCat(DirAdd,MAX_PATH,TEXT("/"));  
			StringCchCat(DirAdd,MAX_PATH,FindFileData.cFileName); 
			if((FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)!=0)      //�ж�������ļ���  
			{  
				//ƴ�ӵõ����ļ��е�����·��  
				bIsEmptyFolder = false;
				TraverseDirectory(DirAdd,m);                                  //ʵ�ֵݹ����  
			}  
			if((FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==0)    //��������ļ���  
			{  
				//wcout<<Dir<<"\\"<<FindFileData.cFileName<<endl;            //�������·��  
				bIsEmptyFolder = false;
				wchar_t* path = new wchar_t[MAX_PATH];
				memset(path,0x00,sizeof(path));
				StringCchCopy(path,MAX_PATH,DirAdd);
				m.insert(make_pair(path,false)); //�ļ�����
			}  
		}  
		if (bIsEmptyFolder)
		{
			wchar_t* path = new wchar_t[MAX_PATH];
			memset(path,0x00,sizeof(path));
			StringCchCopy(path,MAX_PATH,Dir);
			m.insert(make_pair(path,TRUE)); //�ļ�������
		}
		FindClose(hFind);  
	}  
} 

void getVecByJson(WCHAR* path,std::vector<std::string>& vecCatagory,std::vector<std::string>& vecWeather,std::vector<std::string>& vecScene,std::vector<std::string>& vecTimeOfDay)
{
	std::vector<WCHAR*> vSrcCol = split(path);
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

				cJSON * itemScene = cJSON_GetObjectItem(itemAttributes, "scene");
				if (!itemScene) {cJSON_Delete(root);delete[] pcFileData;continue;}

				cJSON * itemTimeofday = cJSON_GetObjectItem(itemAttributes, "timeofday");
				if (!itemTimeofday) {cJSON_Delete(root);delete[] pcFileData;continue;}

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
				
				cJSON * itemObjectsChildCategory = nullptr;
				CHAR category[MAX_PATH] = {};
			
				int iVecSign = -1;
				iVecSign = findStrInVec(vecWeather,itemWeather->valuestring);
				if (iVecSign < 0 )
				{
					vecWeather.push_back(itemWeather->valuestring);
				}

				iVecSign = findStrInVec(vecScene,itemScene->valuestring);
				if (iVecSign < 0 )
				{
					vecScene.push_back(itemScene->valuestring);
				}

				iVecSign = findStrInVec(vecTimeOfDay,itemTimeofday->valuestring);
				if (iVecSign < 0 )
				{
					vecTimeOfDay.push_back(itemTimeofday->valuestring);
				}

				do 
				{
					iVecSign = -1;
					itemObjectsChildBox2d = cJSON_GetObjectItem(itemObjectsChildNext, "box2d");
					if (itemObjectsChildBox2d)
					{
						itemObjectsChildCategory = cJSON_GetObjectItem(itemObjectsChildNext, "category");
						if (itemObjectsChildCategory)sprintf(category,"%s",itemObjectsChildCategory->valuestring);

						iVecSign = findStrInVec(vecCatagory,category);
						if (iVecSign < 0 )
						{
							vecCatagory.push_back(category);
						}
					}
					itemObjectsChildNext = itemObjectsChildNext->next;
				} while (itemObjectsChildNext);


				cJSON_Delete(root);
				delete[] pcFileData;
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

			cJSON * itemScene = cJSON_GetObjectItem(itemAttributes, "scene");
			if (!itemScene) {cJSON_Delete(root);delete[] pcFileData;continue;}

			cJSON * itemTimeofday = cJSON_GetObjectItem(itemAttributes, "timeofday");
			if (!itemTimeofday) {cJSON_Delete(root);delete[] pcFileData;continue;}

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

			cJSON * itemObjectsChildCategory = nullptr;
			CHAR category[MAX_PATH] = {};
		
			//frames
			//�����ļ�


			int iVecSign = -1;
			iVecSign = findStrInVec(vecWeather,itemWeather->valuestring);
			if (iVecSign < 0 )
			{
				vecWeather.push_back(itemWeather->valuestring);
			}

			iVecSign = findStrInVec(vecScene,itemScene->valuestring);
			if (iVecSign < 0 )
			{
				vecScene.push_back(itemScene->valuestring);
			}

			iVecSign = findStrInVec(vecTimeOfDay,itemTimeofday->valuestring);
			if (iVecSign < 0 )
			{
				vecTimeOfDay.push_back(itemTimeofday->valuestring);
			}
			do 
			{
				iVecSign = -1;
				itemObjectsChildBox2d = cJSON_GetObjectItem(itemObjectsChildNext, "box2d");
				if (itemObjectsChildBox2d)
				{
					itemObjectsChildCategory = cJSON_GetObjectItem(itemObjectsChildNext, "category");
					if (itemObjectsChildCategory)sprintf(category,"%s",itemObjectsChildCategory->valuestring);

					iVecSign = findStrInVec(vecCatagory,category);
					if (iVecSign < 0 )
					{
						vecCatagory.push_back(category);	
					}
				}
				itemObjectsChildNext = itemObjectsChildNext->next;
			} while (itemObjectsChildNext);
			cJSON_Delete(root);
			delete[] pcFileData;
		}
	}
}