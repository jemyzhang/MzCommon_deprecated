/*
* @filename appconfigini.h
* @note 应用程序配置文件读写类
* @author JEMYZHANG
* @date 2009.6.20
* @ver. 1.1
* @changelog
*  ver.1.0 初始化程序
*  ver.1.1 创建MzConfig类，简化键值读写
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
		IniReadInt(_mainKey,_subKey,&_value,gs_inifile);
	}
}
