/*
* @filename appconfigini.h
* @note 应用程序配置文件读写类
* @author JEMYZHANG
* @date 2009.6.20
* @ver. 1.2
* @changelog
*  ver.1.0 初始化程序
*  ver.1.1 创建MzConfig类，简化键值读写
*  ver.1.2 初始化读取初始值时，当发现没有值时则创建，防止出现空白配置文件
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

	//读取初始值
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