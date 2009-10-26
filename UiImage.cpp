#include "UiImage.h"
#include "MzCommon.h"
using namespace MzCommon;

void UiImage::PaintWin(HDC hdcDst, RECT* prcWin, RECT* prcUpdate){
    UiWin::PaintWin(hdcDst,prcWin,prcUpdate);
    if(pimg){
        pimg->Draw(hdcDst,prcWin,true,true);
    }
    if(pimgPath){
        ImagingHelper::DrawImage(hdcDst,prcWin,pimgPath,true,true);
    }
}

void UiImage::setupImagePath(LPWSTR path){
    if(path){
        C::newstrcpy(&pimgPath,path);
        if(pimg){
            delete pimg;
            pimg = 0;
        }
    }
}