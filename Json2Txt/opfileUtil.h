#ifndef __OPFILEUTIL__H__
#define  __OPFILEUTIL__H__

#include "stdafx.h"
#include "strsafe.h"
// Ψһ��Ӧ�ó������
#include <wininet.h>
#pragma comment(lib,"wininet.lib")


#include<vector>
using namespace std;

template<class T>
void freeVector(std::vector<T> v);
/*
aim:�����Ժ���Ը��ݷָ����չѹ���ļ�����
author:wsh
time:20180403
input:
	string strTime:��Ҫ�ָ���ַ���
output:
	vector<WCHAR*>:�ָ�󱣴��vector����
*/
std::vector<WCHAR*> split(const WCHAR* strTime);

const wchar_t* wcstrrchr(const wchar_t* str, const wchar_t wc);

const wchar_t* wcstrrchr(const wchar_t* str, const wchar_t* wc); //wc��ʽ"\\|/"����'\\"��'/'2�ַָ�

void getPath_Name(const wchar_t* str, const wchar_t* wc,wchar_t* wsPath, wchar_t* wsName);

std::vector<char*> split(const char* strTime);

const char* wcstrrchr(const char* str, const char* wc); //wc��ʽ"\\|/"����'\\"��'/'2�ַָ�

void getPath_Name(const char* str, const char* wc,char* wsPath, char* wsName);

bool createMultiDir(const wchar_t* path);

bool createMultiDir(const char* path);

char* readfile(WCHAR* filename);

std::string WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP);

int findStrInVec(std::vector<std::string>& vec, char* str);

bool writefile(WCHAR* filename, std::string content);

bool changeSuffix(WCHAR* filename, WCHAR* oldSuffix, WCHAR* newSuffix,WCHAR* newFilename);

bool readIniSection(TCHAR* ini, TCHAR* section, std::map<TCHAR*,TCHAR*>& map);

void StringToWstring(std::wstring& szDst, std::string str);

void Wchar_tToString(std::string& szDst, wchar_t *wchar);

errno_t getFullName(WCHAR* path,WCHAR* fullName);

int getLastFolderName(WCHAR* path,WCHAR* folderName);

void TraverseDirectory(wchar_t Dir[MAX_PATH],std::map<wchar_t*,int> &m);

void getVecByJson(WCHAR* path,std::vector<std::string>& vecCatagory,std::vector<std::string>& vecWeather,std::vector<std::string>& vecScene,std::vector<std::string>& vecTimeOfDay);
#endif