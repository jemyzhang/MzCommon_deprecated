#pragma once
/*
 * @filename UiSingleOption.h
 * @note 单选列表
 * @author JEMYZHANG
 * @date 2009.10.16
 * @ver. 1.0
 * @changelog
 *  ver.1.0 初始化程序
*/
// include the MZFC library header file
#include <mzfc_inc.h>
#include <list>

#define MZ_MW_TEXT_EDITED MZFC_WM_MESSAGE+0x80

class UiSelectionList : public UiList
{
public:
	void DrawItem(HDC hdcDst, int nIndex, RECT* prcItem, RECT *prcWin, RECT *prcUpdate);
private:
	CMzString preStr;
};

class UiBG : public UiWin
{
protected:
	virtual void PaintWin(HDC hdcDst, RECT* prcWin, RECT* prcUpdate){
		UiWin::PaintWin(hdcDst, prcWin, prcUpdate);
		MzDrawGridDlgBG(hdcDst,prcWin);
	}
};

class Ui_SingleOptionWnd : public CMzWndEx 
{
	MZ_DECLARE_DYNAMIC(Ui_SingleOptionWnd);
public:
	Ui_SingleOptionWnd(void);
	~Ui_SingleOptionWnd(void);
public:
	UiBG m_bg;
	UiSelectionList m_OptionList;
	UiButton m_BtnOK;
	UiButton m_BtnCancel;
    UiStatic m_Title;
public:
    void AppendOptionItem(LPTSTR item){
        if(item == NULL) return;
        ListItem li;
        li.Text = item;
        m_OptionList.AddItem(li);
    }
    void SetSelectedIndex(int nIndex){
        if(nIndex >= m_OptionList.GetItemCount()) nIndex = 0;
        m_OptionList.SetSelectedIndex(nIndex);
    }
    int GetSelectedIndex(){
        return m_OptionList.GetSelectedIndex();
    }
    LPTSTR GetSelectedText(){
        int nIndex = m_OptionList.GetSelectedIndex();
        if(nIndex == -1) return NULL;
        return m_OptionList.GetItem(nIndex)->Text.C_Str();
    }
    void SetTitleText(LPTSTR title);
protected:
    // Initialization of the window (dialog)
    virtual BOOL OnInitDialog();

    // override the MZFC window messages handler
    virtual LRESULT MzDefWndProc(UINT message, WPARAM wParam, LPARAM lParam);
    // override the MZFC command handler
    virtual void OnMzCommand(WPARAM wParam, LPARAM lParam);
private:
    LPTSTR m_title;
};
