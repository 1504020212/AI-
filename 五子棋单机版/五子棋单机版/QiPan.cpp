#include "QiPan.h"


CQiPan::CQiPan(void)
{
	g_iPieceLen=ORDEX*ORDEX;
	hbitQiPan=NULL;
	x=0;
	y=0;
}

CQiPan::~CQiPan(void)
{
	::DeleteObject(hbitQiPan);
	hbitQiPan=NULL;
}

void CQiPan::InitQiPan(HINSTANCE hIns)
{
	hbitQiPan=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BITMAP1));

}
void CQiPan::ShowQiOan(HDC hMemDC)
{
	//创建一个装图片的 兼容性DC
	HDC hTempQiPan=::CreateCompatibleDC(hMemDC);
	//把图片放在hTempDC 兼容性DC
	SelectObject(hTempQiPan,hbitQiPan);
	//把hTempDC 兼容性DC 里面的图片 传输到hMemDC
	::BitBlt(hMemDC,x,y,1002,706,hTempQiPan,0,0,SRCCOPY);
	//删除hTempDC
	::DeleteDC(hTempQiPan);
	hTempQiPan=NULL;
}
