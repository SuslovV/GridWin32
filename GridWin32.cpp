#include <windows.h>

#include "TestControl.h"
#include <map>
using namespace std;

struct StructColPar{int Widht; LPCWSTR Title;};
map<int, StructColPar> ColumnsParametrs;

struct StructColumn{LPCWSTR Column1; LPCWSTR Column2; LPCWSTR Column3;};
map<int, StructColumn> Grig;


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     LPCTSTR szAppName = L"TestControl" ;
     HWND        hwnd ;
     MSG         msg ;
     WNDCLASSEX  wndclass ;

     wndclass.cbSize        = sizeof (wndclass) ;
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;
     wndclass.hIconSm       = LoadIcon (NULL, IDI_APPLICATION) ;

     RegisterClassEx (&wndclass) ;

     hwnd = CreateWindow (szAppName,         // window class name
		            L"TestControl",     // window caption
                    WS_OVERLAPPEDWINDOW,     // window style
                    CW_USEDEFAULT,           // initial x position
                    CW_USEDEFAULT,           // initial y position
                    CW_USEDEFAULT,           // initial x size
                    CW_USEDEFAULT,           // initial y size
                    NULL,                    // parent window handle
                    NULL,                    // window menu handle
                    hInstance,               // program instance handle
		      NULL) ;		           // creation parameters

     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

	 StructColPar СтруктураПарКол;
	 СтруктураПарКол.Title = L"Тема";
	 СтруктураПарКол.Widht = 100;

	 ColumnsParametrs.insert(pair<int, StructColPar>(1, СтруктураПарКол));

	 СтруктураПарКол.Title = L"Содержание";
	 СтруктураПарКол.Widht = 200;

	 ColumnsParametrs.insert(pair<int, StructColPar>(2, СтруктураПарКол));

	 СтруктураПарКол.Title = L"Отправитель";
	 СтруктураПарКол.Widht = 100;

	 ColumnsParametrs.insert(pair<int, StructColPar>(3, СтруктураПарКол));

	 //------
	 StructColumn СтруктураКолонок;
	 СтруктураКолонок.Column1 = L"1";
	 СтруктураКолонок.Column2 = L"12";
	 СтруктураКолонок.Column3 = L"13";

	 Grig.insert(pair<int, StructColumn>(1, СтруктураКолонок));
	 
	 СтруктураКолонок.Column1 = L"21";
	 СтруктураКолонок.Column2 = L"22";
	 СтруктураКолонок.Column3 = L"23";

	 Grig.insert(pair<int, StructColumn>(2, СтруктураКолонок));

     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;

     switch (iMsg)
     {

          case WM_PAINT :
			  {
	        hdc = BeginPaint (hwnd, &ps) ;

               GetClientRect (hwnd, &rect) ;

				POINT pt;
				int WidhtGrid = 0;

				map<int, StructColPar>::iterator itColumnsParametrs;
				for (itColumnsParametrs = ColumnsParametrs.begin(); itColumnsParametrs != ColumnsParametrs.end(); itColumnsParametrs++)
				{		
					RECT rect3={WidhtGrid, 0, WidhtGrid + itColumnsParametrs->second.Widht, 22};
					WidhtGrid += itColumnsParametrs->second.Widht;
					
					DrawText (hdc, itColumnsParametrs->second.Title, -1, &rect3,
			             DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
					
					MoveToEx(hdc, WidhtGrid, 0, &pt);
					LineTo(hdc, WidhtGrid, 22);

				}

				//StructColumn СтруктураКолонок;

				map<int, StructColumn>::iterator itGrig;
				for (itGrig = Grig.begin(); itGrig != Grig.end(); itGrig++)
				{		
					WidhtGrid = 0;
					for (itColumnsParametrs = ColumnsParametrs.begin(); itColumnsParametrs != ColumnsParametrs.end(); itColumnsParametrs++)
					{		
						RECT rect3={WidhtGrid, itGrig->first*22, WidhtGrid + itColumnsParametrs->second.Widht, itGrig->first*22+22};
						WidhtGrid += itColumnsParametrs->second.Widht;
						
						DrawText (hdc, itGrig->second.Column1, -1, &rect3, DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
						
					}
					
					MoveToEx(hdc, 0, itGrig->first*22, &pt);
					LineTo(hdc, WidhtGrid, itGrig->first*22);
				}

			  }


	        EndPaint (hwnd, &ps) ;
               return 0 ;

          case WM_DESTROY :
               PostQuitMessage (0) ;
               return 0 ;
     }

     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
}

