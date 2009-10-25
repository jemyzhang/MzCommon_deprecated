#pragma once
// include the MZFC library header file
#include <mzfc_inc.h>
#include <list>
using std::list;

typedef enum TextEncode{
	ttcAnsi, 
	ttcUnicode, 
	ttcUnicodeBigEndian, 
	ttcUtf8
}TEXTENCODE_t;

#define LOADIMAGE(nID)	ImagingHelper::GetImageObject(ImgresHandle,nID)
#define LOADSTRING(uID)	MzLoadString(uID,LangresHandle)
#define MZFC_WM_MESSAGE_QUIT	MZFC_WM_MESSAGE+0x100

class MzCommonC
{
public:
	static void newstrcpy(wchar_t** pdst,const wchar_t* src, size_t nsize = 0);
    //ȥ���ַ������ض����ַ�
	static wchar_t* removeSpecStr(wchar_t* sStr, wchar_t* dStr);
	//remove LF to "\n"
	static wchar_t* removeWrap(wchar_t* dst, wchar_t* src);
	//restore "\n" "\r" to LF
	static wchar_t* restoreWrap(wchar_t* dst, wchar_t* src);
	static wchar_t* _wcstok(wchar_t* _Str, const wchar_t *_Delim){
		static wchar_t* header;
		wchar_t* retval;
		if(_Str != NULL){
			header = _Str;
		}
		if(header == NULL || _Delim == NULL){
			return header;
		}
		int delimLen = lstrlen(_Delim);
		if(delimLen == 0){
			return header;
		}
		CMzString tmp = header;
		int cnt = 0;
		while(tmp.SubStr(cnt++,delimLen).Compare(_Delim) != 0){
			if(cnt >= tmp.Length()){
				retval = header;
				header = NULL;
				return retval;
			}
		}
		retval = header;
		header[cnt-1] = '\0';
		header += (cnt-1 + delimLen);
		return retval;
	}
};

class MzCommonDateTime
{
public:
	static void waitms(unsigned int ms){
		DWORD s = GetTickCount();
		DWORD e;
		do{	//wait
			//Do Events
			MSG msg;  
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )  
			{  
				TranslateMessage(   &msg   );  
				DispatchMessage(   &msg   );  
			}
			e = GetTickCount();
		}while(e < s + ms);
	}

	//��ȡ��ǰ����
    //����ֵ:��ǰϵͳ���ڣ���ʽ��2009-12-11

	static SYSTEMTIME StrToDate(wchar_t* datestr,wchar_t* format = L"%04d-%02d-%02d") {
		SYSTEMTIME sysDate;
		sysDate.wYear = 0;
		sysDate.wMonth = 0;
		sysDate.wDay = 0;
		if(datestr){
			swscanf(datestr,format,&sysDate.wYear,&sysDate.wMonth,&sysDate.wDay);
		}
		return sysDate;
	}
    static CMzString Date() {
        SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);
        CMzString sDate(16);
        wsprintf(sDate.C_Str(), L"%04d-%02d-%02d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);

        return sDate;
    }

    static void getDate(int *py = 0, int *pm = 0, int *pd = 0) {
        SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);
		if(py) *py = sysTime.wYear;
		if(pm) *pm = sysTime.wMonth;
		if(pd) *pd = sysTime.wDay;
        return;
    }
	static void getPreDate(int &y, int &m) { 
		m--; 
		if(m <= 0){
			m = 12;
			y--;
		}
	}
	static void getNextDate(int &y, int &m) {
		m++; 
		if(m > 12){
			m = 1;
			y++;
		}
	}
	static int getWeekDay(int year,int month, int day);
	static bool isLeapyear(int year);
	static void OneDayDate(SYSTEMTIME &date,bool isYesterday = false);
    //��ȡ��ǰʱ��
    //����ֵ:��ǰϵͳʱ�䣬��ʽ��12:12:15

    static CMzString Time() {
        SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);
        CMzString sTime(16);
        wsprintf(sTime.C_Str(), L"%02d:%02d:%02d", sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
        return sTime;
    }


    //��ȡ��ǰʱ��
	static wchar_t* NowtoStr(){
		static wchar_t nowstr[128];
        SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);
        wsprintf(nowstr, L"%04d%02d%02d%02d%02d%02d", 
			sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
        return nowstr;
	}

    static CMzString Now() {
        CMzString sDateTime(32), sDate(16), sTime(16);

        sDate = Date();
        sTime = Time();

        sDateTime = sDate + L" " + sTime;
        return sDateTime;
    }
	//��ȡһ���µ�����
	static int getDays(int year, int month);
	static int checkDate(int year,int month, int day);
    static int compareDateTime(SYSTEMTIME tm1, SYSTEMTIME tm2){
        int nRet = 0;
        if(tm1.wYear > tm2.wYear){
            nRet += 32;
        }else if(tm1.wYear < tm2.wYear){
            nRet -= 32;
        }
        if(tm1.wMonth > tm2.wMonth){
            nRet += 16;
        }else if(tm1.wMonth < tm2.wMonth){
            nRet -= 16;
        }
        if(tm1.wDay > tm2.wDay){
            nRet += 8;
        }else if(tm1.wDay < tm2.wDay){
            nRet -= 8;
        }
        if(tm1.wHour > tm2.wHour){
            nRet += 4;
        }else if(tm1.wHour < tm2.wHour){
            nRet -= 4;
        }
        if(tm1.wMinute > tm2.wMinute){
            nRet += 2;
        }else if(tm1.wMinute < tm2.wMinute){
            nRet -= 2;
        }
        if(tm1.wSecond > tm2.wSecond){
            nRet += 1;
        }else if(tm1.wYear < tm2.wYear){
            nRet -= 1;
        }
        return nRet;
    }
    //0: equal 1: large -1: small
	static int compareDate(SYSTEMTIME tm1, SYSTEMTIME tm2){
		if(tm1.wYear > tm2.wYear) return 1;
		if((tm1.wYear == tm2.wYear) &&
			(tm1.wMonth > tm2.wMonth)){
				return 1;
		}
		if((tm1.wYear == tm2.wYear) &&
			(tm1.wMonth == tm2.wMonth) &&
			(tm1.wDay > tm2.wDay)){
				return 1;
		}
		if((tm1.wYear == tm2.wYear) &&
			(tm1.wMonth == tm2.wMonth) &&
			(tm1.wDay == tm2.wDay) &&
			(tm1.wHour > tm2.wHour) ){
				return 1;
		}
		if((tm1.wYear == tm2.wYear) &&
			(tm1.wMonth == tm2.wMonth) &&
			(tm1.wDay == tm2.wDay) &&
			(tm1.wHour == tm2.wHour) &&
			(tm1.wMinute > tm2.wMinute)){
				return 1;
		}
		if((tm1.wYear == tm2.wYear) &&
			(tm1.wMonth == tm2.wMonth) &&
			(tm1.wDay == tm2.wDay) &&
			(tm1.wHour == tm2.wHour) &&
			(tm1.wMinute == tm2.wMinute) &&
			(tm1.wSecond > tm2.wSecond) ){
				return 1;
		}
		if((tm1.wYear == tm2.wYear) &&
			(tm1.wMonth == tm2.wMonth) &&
			(tm1.wDay == tm2.wDay) &&
			(tm1.wHour == tm2.wHour) &&
			(tm1.wMinute == tm2.wMinute) &&
			(tm1.wSecond == tm2.wSecond) ){
				return 0;
		}
		return -1;
	}
};

//�ļ��������ú���
class MzCommonFile{
public:
	//����ļ����Ƿ���ڣ����������½�
	static BOOL DirectoryExists_New(TCHAR* foldername){
		if(FileExists(foldername)){
			return true;
		}
		return CreateDirectory(foldername,NULL);
	}
	//�Ե�ǰʱ��Ϊ���ƴ����ļ���
	static CMzString CreateDirectoryByDate(TCHAR* parentdir,BOOL &result){
		CMzString str = parentdir;
		str = str + L"\\";
		str = str + MzCommonDateTime::NowtoStr();
		result = DirectoryExists_New(str.C_Str());
		return str;
	}
	//�б������ļ���
	//���ļ����򷵻�0
	static int ListDirectory(TCHAR* parentdir, list<CMzString> &s){
	  WIN32_FIND_DATA FindFileData;
	  HANDLE hFind;
	  BOOL bFinished = true;
	  int ret = 0;
	  CMzString str = parentdir;
	  str = str + L"\\*.*";

	  s.clear();	//����������
	  hFind = FindFirstFile(str.C_Str(), &FindFileData);
	  if(hFind != INVALID_HANDLE_VALUE){
		  while(bFinished){
			  if((FindFileData.dwFileAttributes & (~FILE_ATTRIBUTE_DIRECTORY)) == 0){	//is Directory
				  s.push_back(FindFileData.cFileName);
				  ret++;
			  }
			  bFinished = FindNextFile(hFind,&FindFileData);
		  }
		  FindClose(hFind);
	  }
	  return ret;
	}

	//���������ļ�
	//��Ŀ���ļ��в������ǣ��Զ��½�
	static bool BackupFiles(TCHAR* srcdir, TCHAR* destdir,list<CMzString> &files){
		if(lstrcmp(srcdir,destdir) == 0){	//Դ�ļ�����Ŀ���ļ�����ͬ
			return false;
		}
		if(!FileExists(srcdir)){	//Դ�ļ��в�����
			return false;
		}
		if(!DirectoryExists_New(destdir)){ //Ŀ���ļ��д�������
			return false;
		}
		list<CMzString>::iterator i = files.begin();
		for(; i != files.end(); i++){
			CMzString srcfile = srcdir;
			srcfile = srcfile + L"\\" + *i;
			CMzString destfile = destdir;
			destfile = destfile + L"\\" + *i;
			CopyFile(srcfile,destfile,false);
		}
		return true;
	}

	static BOOL DelFile(TCHAR* file){
		BOOL ret = false;
		if(FileExists(file)){
			ret = DeleteFile(file);
		}
		return ret;
	}
	//����ɾ���ļ���
	static BOOL DelDirectory(TCHAR* foldername){
	  WIN32_FIND_DATA FindFileData;
	  HANDLE hFind;
	  BOOL ret;
	  BOOL bFinished = true;
	  CMzString str = foldername;
	  str = str + L"\\*.*";

	  CMzString parentfolder = foldername;
	  parentfolder = parentfolder + L"\\";

	  hFind = FindFirstFile(str.C_Str(), &FindFileData);
	  if(hFind != INVALID_HANDLE_VALUE){
		  while(bFinished){
			  if((FindFileData.dwFileAttributes & (~FILE_ATTRIBUTE_DIRECTORY)) == 0){	//is Directory
				  CMzString folder = parentfolder + FindFileData.cFileName;
				  ret = DelDirectory(folder.C_Str());
			  }else{
				  CMzString file = parentfolder + FindFileData.cFileName;
				  ret = DeleteFile(file.C_Str());
			  }
			  bFinished = FindNextFile(hFind,&FindFileData);
		  }
		  FindClose(hFind);
	  }
	  return RemoveDirectory(parentfolder.C_Str());
	}
	//����ļ������
	static bool FileExists(TCHAR* filename)
	{
	  WIN32_FIND_DATA FindFileData;
	  HANDLE hFind;

	  hFind = FindFirstFile(filename, &FindFileData);
	  if (hFind == INVALID_HANDLE_VALUE)
	  {
		return false;
	  }
	  else
	  {
		FindClose(hFind);
		return true;
	  }
	}
	//��ȡӦ�ó���Ŀ¼
	static bool GetCurrentPath(LPTSTR szPath) 
	{ 
			HMODULE handle = GetModuleHandle(NULL);
			DWORD dwRet = GetModuleFileName(handle, szPath, MAX_PATH);
			if (dwRet == 0)
			{
					return false;
			}
			else
			{
					TCHAR* p = szPath;
					while(*p)++p; //let p point to '\0' 
					while('\\' != *p)--p; //let p point to '\\' 
					++p;
					*p = '\0'; //get the path
					return true; 
			}
	}
	static TEXTENCODE_t getTextCode(TCHAR* filename);
	//���������ĵ�
	static list<CMzString> loadText(TCHAR* file, TEXTENCODE_t enc = ttcAnsi);
	static wchar_t* chr2wch(const char* buffer, wchar_t** wBuf);
};

namespace MzCommon {
	class File : public MzCommonFile {};
	class DateTime : public MzCommonDateTime {};
	class C : public MzCommonC { };
};