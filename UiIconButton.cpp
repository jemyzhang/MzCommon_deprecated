#include "MzCommon.h"
using namespace MzCommon;

#include "UiIconButton.h"

UiIconButton::UiIconButton(){
	m_button.SetPos(0,0,90,90);
	m_button.SetButtonType(MZC_BUTTON_WHITE_ROUND_BOTH);
	m_button.EnableNotifyMessage(true);

	m_text.SetPos(0,90,90,25);
	m_text.SetDrawTextFormat(DT_CENTER | DT_VCENTER);
	m_text.SetTextSize(24);

	AddChild(&m_button);
	AddChild(&m_text);
}

void UiIconButton::SetImage(ImagingHelper *img){
	m_button.SetImage_Normal(img);
	m_button.SetImage_Pressed(img);
}

void UiIconButton::SetText(LPCTSTR text){
	m_text.SetText(text);
}

void UiIconButton::SetID(int nID){
	m_button.SetID(nID);
}