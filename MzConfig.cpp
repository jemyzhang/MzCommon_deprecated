/*
* @filename appconfigini.h
* @note Ӧ�ó��������ļ���д��
* @author JEMYZHANG
* @date 2009.6.20
* @ver. 1.1
* @changelog
*  ver.1.0 ��ʼ������
*  ver.1.1 ����MzConfig�࣬�򻯼�ֵ��д
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
		IniReadInt(_mainKey,_subKey,&_value,gs_inifile);
	}
}
