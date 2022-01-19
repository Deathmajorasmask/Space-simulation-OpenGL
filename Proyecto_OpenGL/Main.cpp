#include <windows.h>
#include <windowsx.h>
#include <string>
#include <gl\GLU.h>
#include <gl\GL.h>
#include <gl\glut.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
//Creamos una clase que administre por separado al OpenGL
#include"Graphics.h"
#define Timer1 100

#pragma comment(lib, "glu32.lib")

bool reversa = false, reversa1 = false;
char Comando[MAX_PATH] = "";
char path[300] = { "The Blue Danube.mp3" };
struct Input
{
	enum Keys
	{
		Backspace = 0x08, Tab,
		Clear = 0x0C, Enter,
		Shift = 0x10, Control, Alt,
		Escape = 0x1B,
		Space = 0x20, PageUp, PageDown, End, Home, Left, Up, Right, Down,
		Zero = 0x30, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NumPad0 = 0x60, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
		F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
	};
}input;
bool KEYS[256];

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void SetUpPixelFormat(HDC hDC);

//debemos declarar una variable global que maneje el acceso al dispositivo grafico
HDC gHDC;

//Declaramos al puntero del objeto 

Graph *OGLobj;
bool renderiza = false;

void KeysEvents(HWND hDlg);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "Ventana";
	RegisterClassEx(&wc);
	RECT wr = { 0, 0, 800, 600 };
	AdjustWindowRect(&	wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,"Ventana", "Space C++ OpenGL Win32", WS_OVERLAPPEDWINDOW, 100, 100, wr.right - wr.left,
		wr.bottom - wr.top, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//Creamos al objeto y se lo pasamos al puntero
	OGLobj = new Graph(hWnd);

	SetTimer(hWnd, Timer1, 30, NULL);

	MSG msg = { 0 };
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			//en este lazo estara ejecutandose el render
			//"renderiza" controla si se hace el render o no a traves
			//del timer Timer1
			if (renderiza)
			{
				OGLobj->Render(gHDC);
				renderiza = false;
			}
		}
	}

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hRC;
	static HDC hDC;
	int ancho, alto;

	switch (message)
	{

	case MM_MCINOTIFY: {
		if (wParam == MCI_NOTIFY_SUCCESSFUL) {
			strcat(Comando, "open \"");
			strcat(Comando, path);
			strcat(Comando, "\" alias mp3 ");
			strcat(Comando, " notify");
			mciSendString(Comando, NULL, 0, 0);
			mciSendString("play mp3", NULL, 0, 0);
			strcpy(Comando, "");

		}
	}
	break;

	case WM_CREATE:
		hDC = GetDC(hWnd);
		gHDC = hDC;
		SetUpPixelFormat(hDC);
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		break;

	case WM_KEYDOWN:
	{
		KEYS[wParam] = true;
	}
	break;
	case WM_KEYUP:
	{
		KEYS[wParam] = false;
	}
	break;

	case WM_TIMER:
		KeysEvents(hWnd);
		////Objeto se muevan
		if (Rotacion < 360) {
			Rotacion += 45;
		}
		else if (Rotacion == 360) {
			Rotacion = 0;
		}
		if (Rotacion2 < 360) {
			Rotacion2 += 15;
		}
		else if (Rotacion2 == 360) {
			Rotacion2 = 0;
		}
		if (RotacionPlaneta < 360) {
			RotacionPlaneta += 2;
		}
		else if (RotacionPlaneta == 360) {
			RotacionPlaneta = 0;
		}

		if (reversa == false) {
			movX += 1;
			if (movX == 200) {
				reversa = true;
			}
		}
		if (reversa == true) {
			movX -= 1;
			if (movX == -200) {
				reversa = false;
			}
		}

		if (reversa1 == false) {
			movY += 1;
			if (movY == 200) {
				reversa1 = true;
			}
		}
		if (reversa1 == true) {
			movY -= 1;
			if (movY == -200) {
				reversa1 = false;
			}
		}
		
		renderiza = true;
		break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, Timer1);
		//en caso de salir desocupar los recursos del opengl
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_SIZE:
	{
		//esta opcion del switch se ejecuta una sola vez al arrancar y si se
		//afecta el tamaño de la misma se dispara de nuevo
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 1000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void SetUpPixelFormat(HDC hDC)
{
	int PixForm;

	static PIXELFORMATDESCRIPTOR pixfordes = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0,0,0,0,0,0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0,0,0,0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0,0,0 //mascaras de capas ignoradas
	};

	PixForm = ChoosePixelFormat(hDC, &pixfordes);
	SetPixelFormat(hDC, PixForm, &pixfordes);
}

void KeysEvents(HWND hDlg) {
	//MOVER LA CAMARA
	if (KEYS[input.A]) {
		poscx -= 5;
	}
	if (KEYS[input.D]) {
		poscx += 5;
	}
	if (KEYS[input.W]) {
		poscy += 5;
	}
	if (KEYS[input.S]) {
		poscy -= 5;
	}
	if (KEYS[input.Q]) {
		poscz -= 5;
	}
	if (KEYS[input.E]) {
		poscz += 5;
	}
	//MOVER LUZ
	if (KEYS[input.Up]) {
		LuzY += 10;
	}
	if (KEYS[input.Down]) {
		LuzY -= 10;
	}
	if (KEYS[input.Left]) {
		LuzX -= 10;
	}
	if (KEYS[input.Right]) {
		LuzX += 10;
	}
	if (KEYS[input.M]) {
		
		strcat(Comando, "open \"");
		strcat(Comando, path);
		strcat(Comando, "\" alias mp3");
		strcat(Comando, " notify");
		mciSendString(Comando, NULL, 0, 0);
		mciSendString("play mp3", NULL, 0, 0);
		strcpy(Comando, "");
	}
	if (KEYS[input.N]) {
		mciSendString("pause mp3", NULL, 0, 0);
		mciSendString("close mp3", NULL, 0, 0);
	}
	//Para el escalado
	if (KEYS[input.I]) {
		EscaladoX += 1;
	}
	if (KEYS[input.J]) {
		EscaladoX -= 1;
	}
	if (KEYS[input.O]) {
		EscaladoY += 1;
	}
	if (KEYS[input.K]) {
		EscaladoY -= 1;
	}
	if (KEYS[input.P]) {
		EscaladoZ += 1;
	}
	if (KEYS[input.L]) {
		EscaladoZ -= 1;
	}
	if (KEYS[input.U]) {
		EscaladoZ = 1.0;
		EscaladoY = 1.0;
		EscaladoX = 1.0;
	}
}

