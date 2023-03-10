//北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
//北   
//北  $Workfile:   WinTools.cpp  $
//北  $Version$
//北  $Revision:   1.00  $
//北    
//北  DESCRIPTION:
//北     Functions to aid in Windows Tools development
//北        
//北  (c) Copyright 1996, Dynamix Inc.   All rights reserved.
//北 
//北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北

#include "wintools.h"

//北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北
//?   
//? NAME
//?   GenericDlg
//?   
//? DESCRIPTION
//?   Handle dialog boxes that simply display a notice
//?   
//北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北北

BOOL CALLBACK GenericDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM)
{
   BOOL  msgProcessed;
   RECT  r;

   msgProcessed = FALSE;
   switch (message) 
   {
      case WM_INITDIALOG:         
         GetWindowRect(hDlg, &r);

         r.left = (GetSystemMetrics(SM_CXSCREEN) - (r.right - r.left)) / 2;
         r.top  = (GetSystemMetrics(SM_CYSCREEN) - (r.bottom - r.top)) / 2;
         SetWindowPos(hDlg, NULL, r.left,r.top,0,0, SWP_NOSIZE | SWP_NOZORDER);
         msgProcessed = TRUE;
         break;

      case WM_COMMAND:            
         switch(LOWORD(wParam))
         {
            case IDYES:
            case IDNO:
            case IDOK:
            case IDCANCEL:
               EndDialog(hDlg, wParam);         
               msgProcessed = TRUE;
               break;  

            default:
               break;
         }
         break;
   }
   return (msgProcessed);               
}
