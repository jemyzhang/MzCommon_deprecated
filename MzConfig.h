#pragma once
/*
 * @filename appconfigini.h
 * @note 应用程序配置文件读写类
 * @author JEMYZHANG
 * @date 2009.6.20
 * @ver. 1.1
 * @changelog
 *  ver.1.0 初始化程序
 *  ver.1.1 创建MzConfig类，简化键值读写
 *  ver.1.2 MzConfig在解构时再写入配置，减少配置的文件读写
*/

// include the MZFC library header file
#include <mzfc_inc.h>

//配置文件路径
//由AppConfigIni初始化
static TCHAR * gs_inifile = NULL;

//配置文件基本读写类
class MzConfig{
public:
	MzConfig(){
		_mainKey = NULL;
		_subKey = NULL;
		_defaultValue = 0;
		_value = 0;
		_bupdate = false;
	}
	~MzConfig();
public:
	void InitKey(TCHAR * mainKey, TCHAR * subKey, DWORD defaultVal = 0);
public:
	DWORD Get() { return _value; }
	void Set(DWORD v) { 
		if(_value == v) return;
		_value = v; 
		_bupdate = true;
	}
private:
	//检查配置文件路径以及键值
	bool checkKey(){
		bool nRet = true;
		if(_mainKey == NULL || _subKey == NULL ||
			gs_inifile == NULL){
			nRet = false;
		}
		return nRet;
	}
private:
	TCHAR * _mainKey;	//主键
	TCHAR * _subKey;	//子键
	DWORD _defaultValue;	//当键值不存在时的默认值
	DWORD _value;	//值
	bool _bupdate;	//设置值后才需要更新
};

/////////////////////////////////
//应用程序配置
class AppConfigIni
{
public:
	AppConfigIni(LPTSTR iniFile = NULL){
		SetupIniPath(iniFile);
		CreateIni();
		InitIniKey();
	}
protected:
	void SetupIniPath(LPTSTR iniFile = NULL);
	void CreateIni();
	virtual void InitIniKey();
public:
	//config版本信息
	MzConfig IniConfigVersion;
private:
	wchar_t ini_path[MAX_PATH];
};