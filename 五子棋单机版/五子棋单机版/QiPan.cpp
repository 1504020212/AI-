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
	//����һ��װͼƬ�� ������DC
	HDC hTempQiPan=::CreateCompatibleDC(hMemDC);
	//��ͼƬ����hTempDC ������DC
	SelectObject(hTempQiPan,hbitQiPan);
	//��hTempDC ������DC �����ͼƬ ���䵽hMemDC
	::BitBlt(hMemDC,x,y,1002,706,hTempQiPan,0,0,SRCCOPY);
	//ɾ��hTempDC
	::DeleteDC(hTempQiPan);
	hTempQiPan=NULL;
}
