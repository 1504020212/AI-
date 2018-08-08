#pragma once

//   ��̬���������ԭ��

//   1��   ����  CGameCtrl   �ŵ��� ÿ����Ϣ��Ӧ���麯��
//   2.    �ڲ�֪��������Ϸ������� ���ڿ����洴��һ��  ��Ϸ�� ����Ķ���ͨ������ָ�룩
//   3.    ����һ������   ���� CGameCtrl ����  ����һ��static�Ĵ�������ĺ���ָ�룩
//   4.    �� ������Ǹ���Ϸ������  ������ָ�븳ֵ  ����ָ�� ����� �Ǹ������Լ������ĺ��� CreateObject   �������ҲӦ����static
//   5.    ��Ϊ��  ����������  ����ִ�и�ֵ�Ĳ���   ����  ͨ��һ��ȫ�ֶ���Ĺ��캯��  ���������ָ�����¸�ֵ
//   6.    ���




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



class CGameCtrl;   //  ǰ������
typedef CGameCtrl* (*PFUN_CREATE_OBJECT)();   //  ��������ĺ���ָ�������


class CGameCtrl
{
public:
	static PFUN_CREATE_OBJECT pfnCreateObject;     //  ��������ĺ���ָ��
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



class Init        //  ������ָ��  ���¸�ֵ
{
public:
	Init(PFUN_CREATE_OBJECT pfn)
	{
		CGameCtrl::pfnCreateObject = pfn;
	}
};



#endif // _GAMECTRL_H_