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
	wndclass.cbClsExtra = 0;//���ӵ���Ϣ ����Ҫ�����ڴ���
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = 0;//���е����� ����Ҫ��
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW; //����ɫ
	wndclass.hCursor = NULL;  //���
	wndclass.hIcon = NULL;   //ͼ��
	wndclass.hIconSm = NULL; //����   ͼ��
	wndclass.hInstance = hIns;// Ӧ�ó���ʵ�����
	wndclass.lpfnWndProc = MyProc;
	wndclass.lpszClassName = ClassName;//�����������
	wndclass.lpszMenuName = NULL;   //�˵�
	wndclass.style = CS_HREDRAW|CS_VREDRAW; //ˢ��

	
	RegisterClassEx(&wndclass);//ע�ᴰ��
	//��������   �������������⣬��ʽ�����Ͻ�����(X,Y)�����ڵĳ��Ϳ����״��ڣ��˵���Ӧ�ó���ʵ����������ĵ�
	hWnd = CreateWindow(ClassName,
						"������",
						WS_OVERLAPPEDWINDOW,
						10,10,
						1002+16,706+38,
						NULL,
						NULL,
						hIns,
						NULL);
	if (hWnd == NULL)     //    �жϴ����Ƿ񴴽��ɹ�
	{
		MessageBox(NULL,"���ڴ���ʧ�ܣ�","ERROR",MB_OK);
		return 0;
	}
	
	ShowWindow(hWnd,nShowCmd/*SW_SHOW*/);   //   ��ʾ�������

	while(GetMessage(&message,NULL,0,0))   //  ���ϵ�����Ϣ������ȡ����Ϣ
	{
		TranslateMessage(&message);     //������Ϣ
		DispatchMessage(&message);		// ������Ϣ
	}
	
	return 0;
}


CGameCtrl* ctrl = NULL;



LRESULT CALLBACK MyProc(                                //�ص�����
						HWND hwnd,
						UINT uMsg,
						WPARAM wParam,
						LPARAM lParam
							)
{
	switch (uMsg)       //�жϷ��͹�������ʲô��Ϣ
	{
	case WM_CREATE:
		if(CGameCtrl::pfnCreateObject == NULL)
		{
			::MessageBox(NULL,"������Ϸʧ��!","��ʾ",MB_OK);
			//  ���ٴ���
			::DestroyWindow(hwnd);
			//  �˳�����
			::PostQuitMessage(0);
		}
		else
		{
			//   ͨ������ָ��  ����һ�� ����Ķ���
			ctrl = (*CGameCtrl::pfnCreateObject)();
			//   ����  ���
			ctrl->SetHandle(hwnd,hIns);
			//   ��Ϸ�ĳ�ʼ��
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
		PostQuitMessage(0);   //������˳�����Ϣ   ���˳�
		break;
	}
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
