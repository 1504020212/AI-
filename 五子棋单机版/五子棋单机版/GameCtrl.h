#pragma once

//   动态创建对象的原型

//   1、   定义  CGameCtrl   放的是 每个消息对应的虚函数
//   2.    在不知道具体游戏的情况下 ，在壳里面创建一个  游戏的 子类的对象（通过函数指针）
//   3.    定义一个函数   （在 CGameCtrl 类里  定义一个static的创建对象的函数指针）
//   4.    在 具体的那个游戏的类里  给函数指针赋值  让它指向 子类的 那个创建自己类对象的函数 CreateObject   这个函数也应该是static
//   5.    因为在  主函数外面  不能执行赋值的操作   所有  通过一个全局对象的构造函数  给这个函数指针重新赋值
//   6.    封宏




#ifndef _GAMECTRL_H_
#define _GAMECTRL_H_

#include <windows.h>

#define DECLARE() static CGameCtrl* CreateObject();

#define IMPLEMENT(ThisClass) \
	CGameCtrl* ThisClass::CreateObject()\
	{\
		return new ThisClass;\
	}\
	Init init##ThisClass(&ThisClass::CreateObject);



class CGameCtrl;   //  前向声明
typedef CGameCtrl* (*PFUN_CREATE_OBJECT)();   //  创建对象的函数指针的类型


class CGameCtrl
{
public:
	static PFUN_CREATE_OBJECT pfnCreateObject;     //  创建对象的函数指针
protected:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
public:
	CGameCtrl()
	{
		m_hWnd = NULL;
		m_hInstance = NULL;
	}
	virtual ~CGameCtrl()
	{
	
	}
public:
	void SetHandle(HWND hwnd,HINSTANCE hIns)
	{
		this->m_hWnd = hwnd;
		this->m_hInstance = hIns;
	}
public:
	virtual void OnCreateGame(){}                //  WM_CREATE
	virtual void OnGameDraw(){}                   //  WM_PAINT
	virtual void OnGameRun(WPARAM nTimerID){}      //  WM_TIMER
	virtual void OnKeyDown(WPARAM nKeyChar){}      //  WM_KEYDOWN
	virtual void OnKeyUp(WPARAM nKeyChar){}        //  WM_KEYUP
	virtual void OnLButtonDown(POINT point){}   //  WM_LBUTTONDOWN
	virtual void OnLButtonUp(POINT point){}    //  WM_LBUTTONUP
	virtual void OnMouseMove(POINT point){}     //  WM_MOUSEMOVE
};



class Init        //  给函数指针  重新赋值
{
public:
	Init(PFUN_CREATE_OBJECT pfn)
	{
		CGameCtrl::pfnCreateObject = pfn;
	}
};



#endif // _GAMECTRL_H_