#include <Windows.h>
#include "GameCtrl.h"
#include <time.h>

PFUN_CREATE_OBJECT CGameCtrl::pfnCreateObject = NULL;

HINSTANCE hIns;
char ClassName[10] = "classname";
LRESULT CALLBACK MyProc(          HWND hwnd,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam
							);


int WINAPI WinMain( __in HINSTANCE hInstance,
				   __in_opt HINSTANCE hPrevInstance,
				   __in_opt LPSTR lpCmdLine,
				   __in int nShowCmd )
{

	srand((unsigned int)time(NULL));
	hIns = hInstance;
	HWND hWnd;
	MSG	message;

	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;//附加的信息 不需要开辟内存了
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = 0;//特有的数据 不需要了
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW; //背景色
	wndclass.hCursor = NULL;  //光标
	wndclass.hIcon = NULL;   //图标
	wndclass.hIconSm = NULL; //左上   图标
	wndclass.hInstance = hIns;// 应用程序实例句柄
	wndclass.lpfnWndProc = MyProc;
	wndclass.lpszClassName = ClassName;//窗口类的名字
	wndclass.lpszMenuName = NULL;   //菜单
	wndclass.style = CS_HREDRAW|CS_VREDRAW; //刷新

	
	RegisterClassEx(&wndclass);//注册窗口
	//创建窗口   窗口类名，标题，样式，左上角坐标(X,Y)，窗口的长和宽，父亲窗口，菜单，应用程序实例句柄，多文档
	hWnd = CreateWindow(ClassName,
						"五子棋",
						WS_OVERLAPPEDWINDOW,
						10,10,
						1002+16,706+38,
						NULL,
						NULL,
						hIns,
						NULL);
	if (hWnd == NULL)     //    判断窗口是否创建成功
	{
		MessageBox(NULL,"窗口创建失败！","ERROR",MB_OK);
		return 0;
	}
	
	ShowWindow(hWnd,nShowCmd/*SW_SHOW*/);   //   显示这个窗口

	while(GetMessage(&message,NULL,0,0))   //  不断的在消息队列里取出消息
	{
		TranslateMessage(&message);     //翻译消息
		DispatchMessage(&message);		// 发送消息
	}
	
	return 0;
}


CGameCtrl* ctrl = NULL;



LRESULT CALLBACK MyProc(                                //回调函数
						HWND hwnd,
						UINT uMsg,
						WPARAM wParam,
						LPARAM lParam
							)
{
	switch (uMsg)       //判断发送过来的是什么消息
	{
	case WM_CREATE:
		if(CGameCtrl::pfnCreateObject == NULL)
		{
			::MessageBox(NULL,"创建游戏失败!","提示",MB_OK);
			//  销毁窗口
			::DestroyWindow(hwnd);
			//  退出程序
			::PostQuitMessage(0);
		}
		else
		{
			//   通过函数指针  创建一个 子类的对象
			ctrl = (*CGameCtrl::pfnCreateObject)();
			//   设置  句柄
			ctrl->SetHandle(hwnd,hIns);
			//   游戏的初始化
			ctrl->OnCreateGame();
		}
		break;
	case WM_PAINT:
		ctrl->OnGameDraw();
		break;
	case WM_TIMER:
		ctrl->OnGameRun(wParam);
		break;
	case WM_KEYDOWN:
		ctrl->OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		ctrl->OnKeyUp(wParam);
		break;
	case WM_LBUTTONDOWN:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnLButtonDown(point);
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnLButtonUp(point);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnMouseMove(point);
		}
		break;
	case WM_DESTROY:   
		delete ctrl;
		ctrl = NULL;
		PostQuitMessage(0);   //如果是退出的消息   就退出
		break;
	}
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
