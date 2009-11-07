#pragma once
/*
 * @filename UiSwitchOption.h
 * @note ����ѡ��, ID: ���� ID+0x100: ����
 * @author JEMYZHANG
 * @date 2009.10.16
 * @ver. 1.0
 * @changelog
 *  ver.1.0 ��ʼ������
*/
// include the MZFC library header file
#include <mzfc_inc.h>
#include <list>

class UiSwitchOption : public UiButtonEx 
{
	MZ_DECLARE_DYNAMIC(UiSwitchOption);
public:
	UiSwitchOption(void);
	~UiSwitchOption(void);
public:
	UiButtonEx m_Switch;
	void SetPos(int x, int y, int w, int h, UINT flags=0){
		m_Switch.SetPos(w-120,0,120,h,flags);
		UiButtonEx::SetPos(x,y,w,h,flags);
	}
	void SetID(int nID){
		m_Switch.SetID(nID + 0x100);
		UiButtonEx::SetID(nID);
	}

public:
	BOOL GetSwitchStatus(){	//true: switch on
		return (m_Switch.GetState() == MZCS_BUTTON_PRESSED);
	}
	void SetSwitchStatus(BOOL s){
		m_Switch.SetState(s ? MZCS_BUTTON_PRESSED : MZCS_BUTTON_NORMAL);
	}
protected:

};
