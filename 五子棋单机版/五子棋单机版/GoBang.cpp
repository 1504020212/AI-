#include "GoBang.h"
CGoBang::CGoBang(void)
{
	TempMan.hbitQiZiBlack=NULL;
	TempMan.hbitQiZiWhite=NULL;
	TempMan.iFlag=MAN;
	TempMan.iX=10;
	TempMan.iY=10;
	TempCom.hbitQiZiBlack=NULL;
	TempCom.hbitQiZiWhite=NULL;
	TempCom.iFlag=COM;
	TempCom.iX=10;
	TempCom.iY=10;
	ComX=0;
	ComY=0;
	for(int i=0; i <ORDEX*ORDEX; ++i )
		*( (int*)TQiPan + i ) = SPA;
}

CGoBang::~CGoBang(void)
{
}
IMPLEMENT(CGoBang)


void CGoBang::OnCreateGame()
{
	qipan.InitQiPan(m_hInstance);
	for(int i=0;i<ORDEX;i++)
	{
		vector<Node*> Tempqipan;
		for(int j=0;j<ORDEX;j++)
		{
			Node * p = new Node;
			p->hbitQiZiBlack=::LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP3));
			p->hbitQiZiWhite=::LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
			p->iX=0;
			p->iY=0;
			p->iFlag = SPA;
			Tempqipan.push_back(p);
		}
		QiPan.push_back(Tempqipan);
	}
}

void CGoBang::OnGameDraw()
{  
	HDC dc=GetDC(m_hWnd);
	HDC hMemDC=::CreateCompatibleDC(dc);
	HBITMAP hbitmap=CreateCompatibleBitmap(dc,1002,706);
	SelectObject(hMemDC,hbitmap);

	
	qipan.ShowQiOan(hMemDC);
	this->ShowListQiZi(hMemDC);


	BitBlt(dc,0,0,1002,706,hMemDC,0,0,SRCCOPY);
	DeleteDC(hMemDC);
	DeleteObject(hbitmap);
	ReleaseDC(m_hWnd,dc);
}
void CGoBang::OnGameRun()
{
	//while( qipan.g_iPieceLen )
	//{
	//	MakePiece( &Temp, 1 );
	//	if( Victory( &Temp ) )
	//	{
	//		MessageBox(NULL,"恭喜你，战胜电脑！","提示",MB_OK);
	//		return;
	//	}    /* 玩家赢 */
	//	else
	//	{
	//		AI( &QiPan[pointDown.x][pointDown.y]->iY, &QiPan[pointDown.x][pointDown.y]->iX );

	//		MakePiece( &Temp, 0 );
	//		if( Victory( &Temp ) )
	//		{               /* 电脑赢 */
	//			MessageBox(NULL,"真遗憾，你输了！","提示",MB_OK);
	//		}
	//	}
	//}
	//MessageBox(NULL,"和局！","提示",MB_OK);
}
void CGoBang::OnLButtonDown(POINT point)
{  
	pointDown.x=(point.x-49-36+18)/36;
	pointDown.y=(point.y-73-36+18)/36;
	QiPan[pointDown.x][pointDown.y]->iX=pointDown.x;
	QiPan[pointDown.x][pointDown.y]->iY=pointDown.y;
	//QiPan[Tx][Ty]->iFlag=MAN;
	TempMan.iX=pointDown.x;
	TempMan.iY=pointDown.y;
	MakePiece( &TempMan, 1 );
		if( Victory( &TempMan ) )
		{
			MessageBox(NULL,"恭喜你，战胜电脑！","提示",MB_OK);
			return;
		}    /* 玩家赢 */
	
	this->OnGameDraw();
}
void CGoBang::OnLButtonUp(POINT point)
{  
	AI(&ComY,&ComX);
	TempCom.iX=ComX;
	TempCom.iY=ComY;
	QiPan[ComX][ComY]->iX=ComX;
	QiPan[ComX][ComY]->iY=ComY;
	QiPan[ComX][ComY]->iFlag=COM;
	TQiPan[ComX][ComY]=COM;
	MakePiece( &TempCom, 0 );
	if( Victory( &TempCom ) )
	{               /* 电脑赢 */
		MessageBox(NULL,"真遗憾，你输了！","提示",MB_OK);
		return;
	}
	this->OnGameDraw();
}
void CGoBang::ShowListQiZi(HDC hMemDC)
{
	for(int i=0;i<ORDEX;i++)
	{
		for(int j=0;j<ORDEX;j++)
		{
			if(TQiPan[i][j]==MAN)
			{
				 HDC hTempDC = ::CreateCompatibleDC(hMemDC);
				::SelectObject(hTempDC,QiPan[i][j]->hbitQiZiBlack);
				::BitBlt(hMemDC,(QiPan[i][j]->iX)*35+36+49-18+i/3,(QiPan[i][j]->iY)*35+36+73-18+j/3,36,36,hTempDC,0,0,SRCCOPY);
				::DeleteObject(hTempDC);
				//QiPan[i][j]->hbitQiZi=::LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
			}
			else if(TQiPan[i][j]==COM)
			{
				 HDC hTempDC = ::CreateCompatibleDC(hMemDC);
				::SelectObject(hTempDC,QiPan[i][j]->hbitQiZiWhite);
				::BitBlt(hMemDC,(QiPan[i][j]->iX)*35+36+49-18+i/3,(QiPan[i][j]->iY)*35+36+73-18+j/3,36,36,hTempDC,0,0,SRCCOPY);
				::DeleteObject(hTempDC);
				//QiPan[i][j]->hbitQiZi=::LoadBitmap(m_hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
			}
			//else if(QiPan[i][j]->iFlag=SPA)
			//{
			//	 HDC hTempDC = ::CreateCompatibleDC(hMemDC);
			//	::SelectObject(hTempDC,QiPan[i][j]->hbitQiZiWhite);
			//	::BitBlt(hMemDC,-100,-100,36,36,hTempDC,0,0,SRCCOPY);
			//	::DeleteObject(hTempDC);
			//	//QiPan[i][j]->hbitQiZi=NULL;
			//}
			
		}
	}
}
void CGoBang::MakePiece(Node* TempQiPan, int iGameFlag )
{
	/*while(1)
		{
			if( ( TempQiPan->iX < 0 || TempQiPan->iX >=ORDEX ) || ( TempQiPan->iY < 0 || TempQiPan->iY >= ORDEX ) )
				::MessageBox(NULL,"位置无效","提示",MB_OK);
			else if( QiPan[pointDown.x][pointDown.y] )
				::MessageBox(NULL,"此位置有子，请选择其他位置下子","提示",MB_OK);
			else break;
		}*/
	if( iGameFlag == 0 )
	{
		TQiPan[TempQiPan->iX][TempQiPan->iY] = COM;
		QiPan[TempQiPan->iX][TempQiPan->iY]->iFlag= COM;
	}
		
		//TQiPan[ComX][ComY] = COM;
	//--qipan.g_iPieceLen;
	if( iGameFlag == 1 )
	{
		TQiPan[TempQiPan->iX][TempQiPan->iY] = MAN;
		QiPan[TempQiPan->iX][TempQiPan->iY]->iFlag= MAN;
	}
		
		//TQiPan[pointDown.x][pointDown.y] = MAN;
	this->OnGameDraw();
	//if( iGameFlag == 0 )
		//printf("电脑下在%d %d\n", pScmPiece->iX, pScmPiece->iY );
}

int CGoBang::DirectionValue(int*piX ,int*piY ,int iDirection)
{
	switch( iDirection )
	{
	case 0:
		--*piX;
		break;
	case 4:
		++*piX;
		break;
	case 1:
		--*piY;
		break;
	case 5:
		++*piY;
		break;
	case 2:
		--*piX; --*piY;
		break;
	case 6:
		++*piX; ++*piY;
		break;
	case 3:
		--*piX; ++*piY;
		break;
	case 7:
		++*piX; --*piY;
		break;
	}
	if((*piX>=0 && *piX<=ORDEX-1) && (*piY >= 0 && *piY <=ORDEX-1) )
		return 1;
	else return 0;
}


int CGoBang::SubVictory( Node* TempQiPan, int iDirection )
{
	int iX = TempQiPan->iX; 
	int iY = TempQiPan->iY; 
	int iPieceCount = 1;
	while( DirectionValue( &iY, &iX, iDirection ) && TQiPan[iX][iY]==  TempQiPan->iFlag )
	{
		++iPieceCount;
	}
	
	iX = TempQiPan->iX;
	iY =TempQiPan->iY;
	while( DirectionValue( &iY, &iX, iDirection+4 ) && TQiPan[iX][iY] ==  TempQiPan->iFlag )
	{
		++iPieceCount;
	}
		
	return iPieceCount;
}


int CGoBang::Victory( Node* TempQiPan )
{
	int iDirection = 0; 
	while( iDirection < 4 )
		if(SubVictory(TempQiPan,iDirection++) >=5)
			return 1;
	return 0;

}

void CGoBang::AI(int *p,int *q)           //电脑下子 *p *q返回下子坐标 
{
	//int i,j,k,max=0,I,J;  // I J为下点坐标
	int i=0;
	int j=0;
	int k=0;
	int max=0;
	int I=0;
	int J=0;

	for(j=0;j<15;j++)
	{
		for(i=0;i<15;i++)
			if(TQiPan[j][i]==SPA)
			{									//历遍棋盘，遇到空点则计算价值，取最大价值点下子。 
				k=value(i,j);
				if(k>=max) 
				{ 
					I=i; 
					J=j; 
					max=k; 
				}
			}
	*p=I;
	*q=J;
	}
}
int CGoBang::value(int p,int q) /* 计算空点p q的价值 以k返回 */ 
{
	int n=1,k=0,k1,k2,K1,K2,X1,Y1,Z1,X2,Y2,Z2,temp;  
	int a[2][4][4]={40,400,3000,10000,6,10,600,10000,20,120,200,0,6,10,500,0,30,300,2500,5000,2,8,300,8000,26,160,0,0,4,20,300,0};
	       /* 数组a中储存己方和对方共32种棋型的值  己方0对方1    活0冲1空活2空冲3    子数0-3（0表示1个子，3表示4个子） */
	while(n!=5)
	{
		k1=qixing(n,p,q); 
		n+=4;			/* k1,k2为2个反方向的棋型编号 */
		k2=qixing(n,p,q); 
		n-=3;
		if(k1>k2) 
		{
			temp=k1;
			k1=k2;
			k2=temp;
		}  /* 使编号小的为k1,大的为k2 */
		K1=k1;
		K2=k2;       /* K1 K2储存k1 k2的编号 */
		Z1=k1%10;
		Z2=k2%10;
		k1/=10;
		k2/=10;
		Y1=k1%10;
		Y2=k2%10;
		k1/=10;
		k2/=10;
		X1=k1%10;
		X2=k2%10;
		    /* X Y Z分别表示 己方0对方1    活0冲1空活2空冲3    子数0-3（0表示1个子，3表示4个子） */
		if(K1==-1)
		{ 
			if(K2<0) 
			{ 
				k+=0;
				continue;
			}
			else 
				k+=a[X2][Y2][Z2]+5; 
			continue;
		};    /* 空棋型and其他 */
		if(K1==-2) 
		{ 
			if(K2<0) 
			{ 
				k+=0; 
				continue; 
			} 
			else 
				k+=a[X2][Y2][Z2]/2;
			continue; 
		};       /* 边界冲棋型and其他 */ 
		if(K1==-3) 
		{ 
			if(K2<0) 
			{ 
				k+=0; 
				continue; 
			} 
			else
				k+=a[X2][Y2][Z2]/3;
			continue;
		};    /* 边界空冲棋型and其他 */ 
		if(((K1>-1&&K1<4)&&((K2>-1&&K2<4)||(K2>9&&K2<14)))||((K1>99&&K1<104)&&((K2>99&&K2<104)||(K2>109&&K2<114))))
		{
			/* 己活己活 己活己冲 对活对活 对活对冲 的棋型赋值*/
			if(Z1+Z2>=2) 
			{ 
				k+=a[X2][Y2][3];
				continue; 
			}
			else 
			{ 
				k+=a[X2][Y2][Z1+Z2+1];
				continue;
			}
		}
		if(((K1>9&&K1<14)&&(K2>9&&K2<14))||((K1>109&&K1<114)&&(K2>109&&K2<114)))
		{
			/* 己冲己冲 对冲对冲 的棋型赋值*/
			if(Z1+Z2>=2) 
			{ 
				k+=10000;
				continue;
			}
			else 
			{ 
				k+=0; 
				continue; 
			}
		}
		if(((K1>-1&&K1<4)&&((K2>99&&K2<104)||(K2>109&&K2<114)))||((K1>9&&K1<14)&&((K2>99&&K2<104)||(K2>109&&K2<114))))
		{
			/* 己活对活 己活对冲 己冲对活 己冲对冲 的棋型赋值*/
			if(Z1==3||Z2==3) 
			{
				k+=10000; 
				continue;
			}
			else 
			{ 
				k+=a[X2][Y2][Z2]+a[X1][Y1][Z1]/4; 
				continue;
			} 
		}
		else  
		{ 
			k+=a[X1][Y1][Z1]+a[X2][Y2][Z2]; 
			continue;
		}    /* 其他棋型的赋值 */
	}
	return k;
}

int CGoBang::qixing(int n,int p,int q)            /* 返回空点p q在n方向上的棋型号 n为1-8方向 从右顺时针开始数 */ 
{
	int k=0;
	int	m=0;  /* 棋型号注解:  己活000-003 己冲010-013 对活100-103 对冲110-113 己空活020-023 己空冲030-033 对空活120-123 对空冲130-133 空-1 边界冲-2 边界空冲-3*/
	bianli(n,&p,&q);
	if(p<0||p>14||q<0||q>14)
	{
		k=-2;
	}/* 边界冲棋型 */
	switch(TQiPan[q][p])
	{
		case COM:
			{
				m++; 
				bianli(n,&p,&q);
				if(p<0||p>14||q<0||q>14) 
				{ 
					k=m+9;
					return k; 
				}
				while(TQiPan[q][p]==COM) 
				{ 
					m++; 
					bianli(n,&p,&q); 
					if(p<0||p>14||q<0||q>14) 
					{ 
						k=m+9; 
						return k; 
					} 
				}
				if(TQiPan[q][p]==SPA) 
					k=m-1;                         /* 己方活棋型 */
 				else 
					k=m+9;                                         /* 己方冲棋型 */
			}
			break;
		case MAN:
			{
				m++; 
				bianli(n,&p,&q);
				if(p<0||p>14||q<0||q>14) 
				{ 
					k=m+109; 
					return k; 
				}
				while(TQiPan[q][p]==MAN) 
				{ 
					m++; 
					bianli(n,&p,&q); 
					if(p<0||p>14||q<0||q>14) 
					{ 
						k=m+109; 
						return k; 
					} 
				}
				if(TQiPan[q][p]==SPA) 
					k=m+99;                         /* 对方活棋型 */
				else 
					k=m+109;                                        /* 对方冲棋型 */
			}
			break;
		case SPA:
			{
				bianli(n,&p,&q);
				if(p<0||p>14||q<0||q>14) 
				{ 
					k=-3; 
					return k; 
				}         /* 边界空冲棋型 */
				switch(TQiPan[q][p])
				{
				case COM:
				{
					m++; 
					bianli(n,&p,&q);
					if(p<0||p>14||q<0||q>14) 
					{ 
						k=m+29; 
						return k; 
					}
					while(TQiPan[q][p]==COM) 
					{ 
						m++; 
						bianli(n,&p,&q); 
						if(p<0||p>14||q<0||q>14) 
						{ 
							k=m+29; 
							return k; 
						} 
					}
					if(TQiPan[q][p]==SPA) 
						k=m+19;                      /* 己方空活棋型 */
					else k=m+29;                                      /* 己方空冲棋型 */
				}
					break;
				case MAN:
					{
						m++; 
						bianli(n,&p,&q);
						if(p<0||p>14||q<0||q>14)
						{ 
							k=m+129; 
							return k; 
						}
						while(TQiPan[q][p]==MAN) 
						{ 
							m++; 
							bianli(n,&p,&q); 
							if(p<0||p>14||q<0||q>14) 
							{ 
								k=m+129; 
								return k; 
							} 
						}		   
						if(TQiPan[q][p]==SPA)
							k=m+119;                     /* 对方空活棋型 */
						else 
							k=m+129;                                     /* 对方空冲棋型 */ 
					}
						break;
				case SPA: 
					k=-1; 
					break;                                         /* 空棋型 */
				}
			}break;
	}
	return k;
}
void CGoBang::bianli(int n,int *i,int *j)        /* 在n方向上对坐标 i j 移位 n为1-8方向 从右顺时针开始数 */
{
	switch(n)
	{
	case 1:
		*i+=1;
		break;
	case 2:
		*i+=1;
		*j+=1;
		break;
	case 3:
		*j+=1;
		break;
	case 4:
		*i-=1;
		*j+=1;
		break;
	case 5:
		*i-=1;
		break;
	case 6:
		*i-=1;
		*j-=1;
		break;
	case 7:
		*j-=1;
		break;
	case 8:
		*i+=1;
		*j-=1;
		break;
	}
}

