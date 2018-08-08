#pragma once

#include "gamectrl.h"
#include"QiPan.h"
#include"Node.h"
class CGoBang :
	public CGameCtrl
{
public:
	CQiPan qipan;
	POINT pointDown;
	int TQiPan[15][15];
	int ComX;
	int ComY;
	//list<Node*> Allqizi;
	vector<vector<Node*>> QiPan;
	Node TempMan;
	Node TempCom;
public:
	CGoBang(void);
	~CGoBang(void);
public:
	DECLARE();
public:
	virtual void OnCreateGame();
	virtual void OnGameDraw();
	virtual void OnGameRun();
	virtual void OnLButtonDown(POINT point);
	virtual void OnLButtonUp(POINT point);
	void ShowListQiZi(HDC hMemDC);
	void MakePiece(Node* TempQiPan, int iGameFlag );
	int CGoBang::DirectionValue( int * piX, int * piY, int iDirection );
	int SubVictory( Node* TempQiPan, int iDirection );
	int Victory( Node* TempQiPan );
	void AI(int *ComX,int *ComY);
	int value(int p,int q);
	int qixing(int n,int p,int q); 
	void bianli(int n,int *i,int *j); 
	
};


class GoBang :
	public CGameCtrl
{
public:
	GoBang(void);
	~GoBang(void);
};

