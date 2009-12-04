#include "MzCommon.h"
#include <fstream>
using namespace std;

void MzCommonDateTime::TimetToSystemTime( time_t t, LPSYSTEMTIME pst )
{
	FILETIME ft;
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	ft.dwLowDateTime = (DWORD) ll;
	ft.dwHighDateTime = (DWORD)(ll >> 32);

	FileTimeToSystemTime( &ft, pst );
}

void MzCommonDateTime::TimetToLocalTime( time_t t, LPSYSTEMTIME pst )
{
	t = t + 28800;
	TimetToSystemTime(t,pst);
}

void MzCommonDateTime::SystemTimeToTimet( SYSTEMTIME st, time_t *pt )
{
	FILETIME ft;
	SystemTimeToFileTime( &st, &ft );

	LONGLONG ll;

	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;

	ll = ((LONGLONG)ft.dwHighDateTime << 32) + ft.dwLowDateTime;

	*pt = (DWORD)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
}

int MzCommonDateTime::getWeekDay(int year,int month, int day){
	int D,M,Y,A; 
	D = day; M = month; Y = year;
	if((M==1)||(M==2)) //1,2�µ���ǰһ���13,14�� 
	{ 
		M+=12; 
		Y--; 
	} 
	if((Y<1752)||((Y==1752)&&(M<9))||((Y==1752)&&(M==9)&&(D<3))){ //�ж��Ƿ���1752��9��3��֮ǰ 
		A=(D+2*M+3*(M+1)/5+Y+Y/4+5)%7; //1752��9��3��֮ǰ�Ĺ�ʽ 
	}else{ 
		A=(D+2*M+3*(M+1)/5+Y+Y/4-Y/100+Y/400)%7; //1752��9��3��֮��Ĺ�ʽ 
	}
	return A;
}

int Days[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int MzCommonDateTime::getDays(int year, int month){
	int day = 0;
	if(year < 1970 || (year > 2199)) return day;

	if((month < 1) || (month > 12))   return day;   
    
	isLeapyear(year);

	return Days[month-1];
}

bool MzCommonDateTime::isLeapyear(int year){
	bool b_IsLeapYear = false;
	if((year%4 == 0 && year%100 != 0) || (year%400 == 0))     
	{   
		b_IsLeapYear=true;    
	}   
    
	if(b_IsLeapYear){
		Days[1] = 29;
	}else{
		Days[1] = 28;
	}
	return b_IsLeapYear;
}

void MzCommonDateTime::OneDayDate(SYSTEMTIME &date,bool isYesterday){
	isLeapyear(date.wYear);
	if(isYesterday){
		date.wDay --;
		if(date.wDay <= 0){
			date.wMonth --;
			if(date.wMonth <= 0){
				date.wYear --;
				isLeapyear(date.wYear);
				date.wMonth = 12;
			}
			date.wDay = Days[date.wMonth - 1];
		}
	}else{
		date.wDay++;
		if(date.wDay > Days[date.wMonth - 1]){
			date.wDay = 1;
			date.wMonth ++;
			if(date.wMonth > 12){
				date.wMonth = 1;
				date.wYear++;
			}
		}
	}
}

//error: 1: year, 2: month, 4: day, 0: no error
int MzCommonDateTime::checkDate(int year,int month, int day)   
{
	int rc = 0;
	if(year < 1970 || (year > 2199)) rc |= 1;

	if((month < 1) || (month > 12))   rc |= 2;   
    
	isLeapyear(year);

	if((day < 0) || (day > Days[month-1])){
		rc |= 4;
	}
    
	return rc;   
} 

void MzCommonC::newlinecpy(wchar_t** pdst, const wchar_t* src, size_t nsize){
	if(*pdst) delete *pdst;
	wchar_t* newdst;
	size_t _strlength = lstrlen(src);
	if(nsize == 0 || nsize > _strlength){
		nsize = _strlength;
	}

	newdst = new wchar_t[nsize + 1];
	int i = 0;
	for(i = 0; i < nsize; i++){
		if(src[i] == '\n' || src[i] == '\r'){
			if(i < nsize - 3){	//���"xxxx..."ʡ��ģʽ
				newdst[i++] = '.';
				newdst[i++] = '.';
				newdst[i++] = '.';
			}
			break;
		}
		newdst[i] = src[i];
	}
	newdst[i] = '\0';

	*pdst = newdst;
}

void MzCommonC::newstrcpy(wchar_t** pdst,const wchar_t* src, size_t nsize){
	if(*pdst) delete *pdst;
	wchar_t* newdst;
	if(nsize == 0){
		newdst = new wchar_t[lstrlen(src) + 1];
		lstrcpy(newdst,src);
	}else{
		if(nsize > lstrlen(src)){
			nsize = lstrlen(src);
		}
		newdst = new wchar_t[nsize + 1];
		int i = 0;
		for(i = 0; i < nsize; i++){
			newdst[i] = src[i];
		}
		newdst[i] = '\0';
	}
	*pdst = newdst;
}

wchar_t* MzCommonC::removeSpecStr(wchar_t* str, wchar_t* spec){
	if(str == NULL || spec == NULL) return str;

	int len_str = lstrlen(str);
	int len_spec = lstrlen(spec);
	if(len_str == 0 || len_spec == 0 || len_spec > len_str) return str;
	//wchar_t* resStr = new wchar_t[len_str+1];
	wchar_t* resStr = str;	//ֱ���滻
	int resStrLenCnt = 0;
	int curCnt = 0;	//��λ
	int specCnt = 0;	//�ض��ַ���λ��
	int SamePos = 0;	//��⵽��ͬ�ַ�������ʼλ��
	while(curCnt < len_str){
		if(str[curCnt] == spec[specCnt]){
			if(specCnt == 0) SamePos = curCnt;	//��¼��ʼλ��
			specCnt++;
			if(specCnt == len_spec) specCnt = 0;
			curCnt++;
		}else{
			if(specCnt != 0){	//�Աȵ�һ����ֲ���ͬ
				for(int i = 0; i < specCnt; i++){
					resStr[resStrLenCnt++] = str[SamePos++];
				}
				specCnt = 0;
			}else{
				resStr[resStrLenCnt++] = str[curCnt++];
			}
		}
	}
	resStr[resStrLenCnt] = '\0';
	return resStr;
}

wchar_t* MzCommonC::removeWrap(wchar_t* dst, wchar_t* src){
	*dst = '\0';
	if(src == NULL) return dst;
	if(lstrlen(src) == 0) return dst;
	wchar_t c;
	wchar_t *p = src;
	wchar_t *d = dst;
	do{
		c = *p++;
		if(c == '\n'){
			*d++ = '\\';
			*d++ = 'n';
		}else if(c == '\r'){
			*d++ = '\\';
			*d++ = 'r';
		}else{
			*d++ = c;
		}
	}while(c);
	*d = '\0';
	return dst;
}

wchar_t* MzCommonC::restoreWrap(wchar_t* dst, wchar_t* src){
	*dst = '\0';
	if(src == NULL) return dst;
	if(lstrlen(src) == 0) return dst;
	wchar_t c;
	wchar_t *p = src;
	wchar_t *d = dst;
	bool isplash = false;
	do{
		c = *p++;
		if(isplash){
			isplash = false;
			if(c == 'r'){
				*d++ = '\r';
			}else if(c == 'n'){
				*d++ = '\n';
			}else{
				*d++ = '\\';	//������λ�ķ���
				*d++ = c;
			}
		}else{
			if(c == '\\'){
				isplash = true;
			}else{
				*d++ = c;
			}
		}
	}while(c);
	*d = '\0';
	return dst;
}

TEXTENCODE_t MzCommonFile::getTextCode(TCHAR* filename)
{
	TEXTENCODE_t ret;
    if (FileExists(filename))
    {
		fstream openfile;
        openfile.open(filename, ios::in | ios::binary);
        openfile.seekg(0, ios::beg);
        char *code = new char[2];
        openfile.read(code, 2);
        openfile.close();
        
        unsigned char cc = (unsigned char)code[0];
        unsigned char cc1 = (unsigned char)code[1];
        if ((cc == 0xFF) && (cc1 == 0xFE))
        {
            ret = ttcUnicode;
        }
        else if ((cc == 0xFE) && (cc1 == 0xFF))
        {
            ret = ttcUnicodeBigEndian;
        }
        else if ((cc == 0xEF) && (cc1 == 0xBB))
        {
            ret = ttcUtf8;
        }
        else
        {
            ret = ttcAnsi;
        }
    }
	return ret;
}

wchar_t* MzCommonFile::chr2wch(const char* buffer, wchar_t** wbuf)
{
      size_t len = strlen(buffer); 
      size_t wlen = MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), NULL, 0); 
      wchar_t *wBuf = new wchar_t[wlen + 1]; 
      MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), wBuf, int(wlen));
	  wBuf[wlen] = '\0';
	  *wbuf = wBuf;
	  return wBuf;
} 

list<CMzString> MzCommonFile::loadText(TCHAR* filename, TEXTENCODE_t enc){
	list<CMzString> lines;
	if(!FileExists(filename)){
		return lines;
	}

	CMzString m_Text;
	if(enc == ttcAnsi){
        ifstream file;
        file.open(filename,  ios::in | ios::binary);
        if (file.is_open())
        {
                file.seekg(0, ios::end);
                int nLen = file.tellg();
                char *ss = new char[nLen+1];
                file.seekg(0, ios::beg);
                file.read(ss, nLen);
                ss[nLen] = '\0';
				wchar_t *wss;
				chr2wch(ss,&wss);
                m_Text = wss;
				delete[] ss;
				delete[] wss;
        }
        file.close();
	}else if(enc == ttcUnicode ||
		enc == ttcUnicodeBigEndian){
		wifstream ofile;
        ofile.open(filename, ios::in | ios ::binary);
        if (ofile.is_open())
        {
			ofile.seekg(0, ios::end);
            int nLen = ofile.tellg();
            ofile.seekg(2, ios::beg);
            wchar_t *tmpstr = new wchar_t[nLen + 1];
            ofile.read(tmpstr, nLen);                        
            tmpstr[nLen] = '\0';
            m_Text = tmpstr;
			delete[] tmpstr;
		}
        ofile.close();
	}

	//����ɶ���
	wchar_t *pstr = m_Text.C_Str();
	wchar_t wch = 0;
	int scnt = 0;
	int npos = 0;
	int ncnt = 0;
	do{
		wch = pstr[scnt++];
		if(wch == '\n' || wch == '\r'){
			if(ncnt != 0){
				lines.push_back(m_Text.SubStr(npos,ncnt));
				npos += (ncnt+1);
				ncnt = 0;
			}else{
				npos++;	//���Ի��з�
			}
			continue;
		}
		ncnt++;
	}while(wch != '\0');
	return lines;
}

wchar_t* MzCommonSystem::sVersion = 0;
wchar_t* MzCommonSystem::getVersion(){
	PLATFORMVERSION pv[4];
	SystemParametersInfo(SPI_GETPLATFORMVERSION, sizeof(pv), pv, SPIF_UPDATEINIFILE);
	if(sVersion == 0) sVersion = new wchar_t[50];
	wsprintf(sVersion, L"%d.%d.%d.%d", pv[1].dwMajor, pv[1].dwMinor, pv[2].dwMajor, pv[2].dwMinor); 
	return sVersion;
}

BOOL MzCommonSystem::getVersion(DWORD &Major,DWORD &Minor,DWORD &Major1,DWORD &Minor1){
	BOOL bRet = FALSE;
	PLATFORMVERSION pv[4];
	bRet = SystemParametersInfo(SPI_GETPLATFORMVERSION, sizeof(pv), pv, SPIF_UPDATEINIFILE);
	if(bRet){
		Major = pv[1].dwMajor; Minor = pv[1].dwMinor;
		Major1 = pv[2].dwMajor; Minor1 = pv[2].dwMinor;
	}
	return bRet;
}

BOOL MzCommonSystem::requireVersion(DWORD Major,DWORD Minor,DWORD Major1,DWORD Minor1){
	BOOL bRet = FALSE;
	PLATFORMVERSION pv[4];
	bRet = SystemParametersInfo(SPI_GETPLATFORMVERSION, sizeof(pv), pv, SPIF_UPDATEINIFILE);
	int nCompare = 0;
	if(bRet){
		if(pv[1].dwMajor != Major) 
			nCompare += (pv[1].dwMajor > Major ? 8 : -8);

		if(pv[1].dwMinor != Minor)
			nCompare += (pv[1].dwMinor > Minor ? 4 : -4);

		if(pv[2].dwMajor != Major1)
			nCompare += (pv[2].dwMajor > Major1 ? 2 : -2);

		if(pv[2].dwMinor != Minor1)
			nCompare += (pv[2].dwMinor > Minor1 ? 1 : -1);
	}
	return (nCompare >= 0);
}