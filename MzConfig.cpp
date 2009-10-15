/*
* @filename appconfigini.h
* @note Ӧ�ó��������ļ���д��
* @author JEMYZHANG
* @date 2009.6.20
* @ver. 1.2
* @changelog
*  ver.1.0 ��ʼ������
*  ver.1.1 ����MzConfig�࣬�򻯼�ֵ��д
*  ver.1.2 ��ʼ����ȡ��ʼֵʱ��������û��ֵʱ�򴴽�����ֹ���ֿհ������ļ�
*/

#include "MzConfig.h"

#include "ReadWriteIni.h"
#include "MzCommon.h"
using namespace MzCommon;

#pragma comment(lib,"PlatformApi.lib")

MzConfig::~MzConfig(){
	if(!_bupdate) return;

	if(!checkKey()) return;
	IniWriteInt(_mainKey,_subKey,_value,gs_inifile);
}

void MzConfig::InitKey(TCHAR * mainKey, TCHAR * subKey, DWORD defaultVal){
	_mainKey = mainKey;
	_subKey = subKey;
	_defaultValue = defaultVal;

	//��ȡ��ʼֵ
	_value = _defaultValue;
	if(checkKey()){
        if(!IniReadInt(_mainKey,_subKey,&_value,gs_inifile)){
            IniWriteInt(_mainKey,_subKey,_value,gs_inifile);
        }
	}
}

///////////////////////////////////////////

void AppConfigIni::SetupIniPath(LPTSTR iniFile){
	//setup path
	wchar_t currpath[128];
	if(File::GetCurrentPath(currpath)){
		if(iniFile){
			wsprintf(ini_path,L"%s\\%s",currpath,iniFile);
		}else{
			wsprintf(ini_path,L"%s\\config.ini",currpath);
		}
	}else{
		wsprintf(ini_path,L"config.ini");
	}
	gs_inifile = ini_path;
}

void AppConfigIni::CreateIni(){
	if(!File::FileExists(ini_path)){
		IniCreateFile(ini_path);
	}
}

void AppConfigIni::InitIniKey(){
	IniConfigVersion.InitKey(L"Config",L"iniVersion",100);
}