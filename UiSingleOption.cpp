#include "UiSingleOption.h"
#include "MzCommon.h"

using namespace MzCommon;

MZ_IMPLEMENT_DYNAMIC(Ui_SingleOptionWnd)

#define MZ_IDC_OPTION_LIST 101
#define MZ_IDC_BTN_OK   102
#define MZ_IDC_BTN_CANCEL   103
Ui_SingleOptionWnd::Ui_SingleOptionWnd(void)
{
    C::newstrcpy(&m_title,L"设置");
}

Ui_SingleOptionWnd::~Ui_SingleOptionWnd(void)
{
}

BOOL Ui_SingleOptionWnd::OnInitDialog() {
    // Must all the Init of parent class first!
    if (!CMzWndEx::OnInitDialog()) {
        return FALSE;
    }

    // Then init the controls & other things in the window
	m_bg.SetPos(0,0,GetWidth(),GetHeight());
	AddUiWin(&m_bg);

    m_Title.SetPos(20,10,GetWidth() - 40,MZM_HEIGHT_SINGLELINE_EDIT);
    m_Title.SetText(m_title);
    m_Title.SetTextColor(RGB(128,128,128));
    m_Title.SetTextSize(30);
    m_Title.SetTextWeight(FW_BOLD);
    m_Title.SetDrawTextFormat(DT_VCENTER|DT_CENTER);
	m_bg.AddChild(&m_Title);

	m_OptionList.SetPos(20,20 + MZM_HEIGHT_SINGLELINE_EDIT,GetWidth() - 40,GetHeight() - MZM_HEIGHT_BUTTONEX - 40 - 10 - MZM_HEIGHT_SINGLELINE_EDIT);
	m_OptionList.SetID(MZ_IDC_OPTION_LIST);
    m_OptionList.EnableGridlines(false);
	m_OptionList.EnableNotifyMessage(true);
	m_bg.AddChild(&m_OptionList);

	int y = GetHeight() - MZM_HEIGHT_BUTTONEX - 20 - 20;
	m_BtnOK.SetPos(10,y,GetWidth()/2-15,MZM_HEIGHT_BUTTONEX);
	m_BtnOK.SetText(L"确定");
	m_BtnOK.SetID(MZ_IDC_BTN_OK);
	m_bg.AddChild(&m_BtnOK);

	m_BtnCancel.SetPos(GetWidth()/2+5,y,GetWidth()/2-15,MZM_HEIGHT_BUTTONEX);
	m_BtnCancel.SetText(L"取消");
	m_BtnCancel.SetID(MZ_IDC_BTN_CANCEL);
	m_bg.AddChild(&m_BtnCancel);

    return TRUE;
}

void Ui_SingleOptionWnd::SetTitleText(LPTSTR title){
    if(title){
        C::newstrcpy(&m_title,title);
        m_Title.SetText(m_title);
        m_Title.Invalidate();
    }
}

void Ui_SingleOptionWnd::OnMzCommand(WPARAM wParam, LPARAM lParam) {
    UINT_PTR id = LOWORD(wParam);
    switch (id) {
		case MZ_IDC_BTN_OK:
            if(m_OptionList.GetSelectedIndex() == -1) return;
			EndModal(ID_OK);
			break;
		case MZ_IDC_BTN_CANCEL:
			EndModal(ID_CANCEL);
			break;
	}
	return;
}

LRESULT Ui_SingleOptionWnd::MzDefWndProc(UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case MZ_WM_MOUSE_NOTIFY:
        {
            int nID = LOWORD(wParam);
            int nNotify = HIWORD(wParam);
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            if (nID == MZ_IDC_OPTION_LIST && nNotify == MZ_MN_LBUTTONUP) {
                if (!m_OptionList.IsMouseDownAtScrolling() && !m_OptionList.IsMouseMoved()) {
                    int nIndex = m_OptionList.CalcIndexOfPos(x, y);
                    m_OptionList.SetSelectedIndex(nIndex);
                    m_OptionList.Invalidate();
                    m_OptionList.Update();
                }
                return 0;
            }
        }
    }
    return CMzWndEx::MzDefWndProc(message, wParam, lParam);
}


void UiSelectionList::DrawItem(HDC hdcDst, int nIndex, RECT* prcItem, RECT *prcWin, RECT *prcUpdate){
	RECT rcSelection = {prcItem->left + 5,prcItem->top,prcItem->left + 45,prcItem->bottom};
    if (nIndex == GetSelectedIndex()) {
		MzDrawControl(hdcDst, &rcSelection,  MZC_SELECTED, 0);
    }else{
        MzDrawControl(hdcDst, &rcSelection,  MZC_UNSELECTED, 0);
    }
    ListItem *li = GetItem(nIndex);

    HFONT hf = FontHelper::GetFont( 28 );
    SelectObject( hdcDst , hf );
    RECT rcText = {prcItem->left + 50,prcItem->top,prcItem->right,prcItem->bottom};
    COLORREF cr = RGB(255,255,255);
    ::SetTextColor( hdcDst , cr );
    MzDrawText( hdcDst , li->Text.C_Str(), &rcText , DT_VCENTER|DT_LEFT|DT_SINGLELINE|DT_WORD_ELLIPSIS );
	DeleteObject(hf);
}