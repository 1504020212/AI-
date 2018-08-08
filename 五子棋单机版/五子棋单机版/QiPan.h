#pragma once
#include"Sys.h"
#include"Node.h"
class CQiPan
{
public:
	
	/*int pan[ORDEX][ORDEX];*/
	int g_iPieceLen;
	HBITMAP hbitQiPan;
	int x;
	int y;
public:
	CQiPan(void);
	~CQiPan(void);
public:
	void InitQiPan(HINSTANCE hIns);
	void ShowQiOan(HDC hMemDC);
};

