#pragma once
/*
 * @filename appconfigini.h
 * @note Ӧ�ó��������ļ���д��
 * @author JEMYZHANG
 * @date 2009.6.20
 * @ver. 1.1
 * @changelog
 *  ver.1.0 ��ʼ������
 *  ver.1.1 ����MzConfig�࣬�򻯼�ֵ��д
 *  ver.1.2 MzConfig�ڽ⹹ʱ��д�����ã��������õ��ļ���д
*/

// include the MZFC library header file
#include <mzfc_inc.h>

//�����ļ�·��
//��AppConfigIni��ʼ��
static TCHAR * gs_inifile = NULL;

//�����ļ�������д��
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
	//��������ļ�·���Լ���ֵ
	bool checkKey(){
		bool nRet = true;
		if(_mainKey == NULL || _subKey == NULL ||
			gs_inifile == NULL){
			nRet = false;
		}
		return nRet;
	}
private:
	TCHAR * _mainKey;	//����
	TCHAR * _subKey;	//�Ӽ�
	DWORD _defaultValue;	//����ֵ������ʱ��Ĭ��ֵ
	DWORD _value;	//ֵ
	bool _bupdate;	//����ֵ�����Ҫ����
};

/////////////////////////////////
//Ӧ�ó�������
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
	//config�汾��Ϣ
	MzConfig IniConfigVersion;
private:
	wchar_t ini_path[MAX_PATH];
};