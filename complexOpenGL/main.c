#include <windows.h>
#include <gl/gl.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265358979

#define ZOOM 0.01

HWND button;

double zoom = 1;

double dfeqence = 1;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

double _Complex G(double feqence,double time){
    return cexp(-2*PI*time*feqence*dfeqence*I)+cexp(-2*PI*time*feqence/8*dfeqence*I);
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    srand(time(0));
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          600,
                          600,
                          NULL,
                          NULL,
                          hInstance,
                          NULL); //FindWindow(NULL,"OpenGL Sample");
    //printf("%p\n",hwnd);

    button = CreateWindowEx(WS_EX_TOPMOST,TEXT("BUTTON"),
                            TEXT("rand"), WS_CHILD | WS_VISIBLE,
                            0, 0, 40, 40, hwnd, NULL, GetModuleHandle(NULL),
                            NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            double _Complex vec;
            double real = creal(vec),imag = cimag(vec);
            /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
            glRotatef(theta, 0.0f, 0.0f, 1.0f);

            glBegin(GL_LINES);
                glVertex2f(0.0f,0.0f);
                glVertex2f(1.0f,1.0f);
                glVertex2f(0.0f,0.0f);
                glVertex2f(-1.0f,-1.0f);
                glVertex2f(0.0f,0.0f);
                glVertex2f(0.0f,0.0f);
                glVertex2f(0.0f,0.0f);
                glVertex2f(-1.0f,1.0f);
                glVertex2f(0.0f,0.0f);
                glVertex2f(1.0f,-1.0f);
            glEnd();

            //»­Ò»¸öÈË
            glBegin(GL_LINE_STRIP);
                for(int i = 0;i < 1e4;i++){
                    vec = G(0.01,i);
                    real = creal(vec)*zoom;
                    imag = cimag(vec)*zoom;
                    glVertex2f((float)real,(float)imag);
                }
            glEnd();

            glPopMatrix();


            //TextOut(hDC,100,100,(LPCSTR)"Éµ±Æ¹þ¹þ",strlen("Éµ±Æ¹þ¹þ"));

            SwapBuffers(hDC);



            theta += 0.05f;
            Sleep (1);
            //glVertex2f((GLfloat)(real*10+300),(GLfloat)(300-imag*10));
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_COMMAND:{
            if ((lParam) == (LPARAM)button)
            {
                printf("click");
                dfeqence = rand()%1000+1;
                return 0;
            }
            printf("click2");
        }
        break;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    break;
                case VK_ADD:
                    zoom += ZOOM;
                    break;
                case VK_SUBTRACT:
                    zoom -= ZOOM;
                    break;
            }
        }
        break;
        case WM_CHAR:{
             if(((char )wParam) == '+' || ((char )wParam) == '='){
                zoom += ZOOM;
                break;
            }else if(((char )wParam) == '-' || ((char )wParam) == '_'){
                zoom -= ZOOM;
                break;
            }
        }
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

