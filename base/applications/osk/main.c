/*
 * PROJECT:         ReactOS On-Screen Keyboard
 * LICENSE:         GPL - See COPYING in the top level directory
 * PURPOSE:         On-screen keyboard.
 * COPYRIGHT:       Denis ROBERT
 *                  Copyright 2019 Bișoc George (fraizeraust99 at gmail dot com)
 */

/* INCLUDES *******************************************************************/

#include "osk.h"
#include "settings.h"

/* GLOBALS ********************************************************************/

OSK_GLOBALS Globals;

/* Functions */
int OSK_SetImage(int IdDlgItem, int IdResource);
int OSK_DlgInitDialog(HWND hDlg);
int OSK_DlgClose(void);
int OSK_DlgTimer(void);
BOOL OSK_DlgCommand(WPARAM wCommand, HWND hWndControl);
BOOL OSK_ReleaseKey(WORD ScanCode);

INT_PTR APIENTRY OSK_DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int);

/* FUNCTIONS ******************************************************************/

/***********************************************************************
 *
 *           OSK_SetImage
 *
 *  Set an image on a button
 */
int OSK_SetImage(int IdDlgItem, int IdResource)
{
    HICON hIcon;
    HWND hWndItem;

    hIcon = (HICON)LoadImageW(Globals.hInstance, MAKEINTRESOURCEW(IdResource),
                              IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    if (hIcon == NULL)
        return FALSE;

    hWndItem = GetDlgItem(Globals.hMainWnd, IdDlgItem);
    if (hWndItem == NULL)
    {
        DestroyIcon(hIcon);
        return FALSE;
    }

    SendMessageW(hWndItem, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);

    /* The system automatically deletes these resources when the process that created them terminates (MSDN) */

    return TRUE;
}

/***********************************************************************
 *
 *          OSK_WarningProc
 *
 *  Function handler for the warning dialog box on startup
 */
INT_PTR CALLBACK OSK_WarningProc(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (Msg)
    {
        case WM_INITDIALOG:
        {
            return TRUE;
        }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_SHOWWARNINGCHECK:
                {
                    Globals.bShowWarning = !IsDlgButtonChecked(hDlg, IDC_SHOWWARNINGCHECK);
                    return TRUE;
                }

                case IDOK:
                case IDCANCEL:
                {
                    EndDialog(hDlg, LOWORD(wParam));
                    return TRUE;
                }
            }
            break;
        }
    }

    return FALSE;
}

/***********************************************************************
 *
 *          OSK_About
 *
 *  Initializes the "About" dialog box
 */
VOID OSK_About(VOID)
{
    WCHAR szTitle[MAX_BUFF];
    WCHAR szAuthors[MAX_BUFF];
    HICON OSKIcon;

    /* Load the icon */
    OSKIcon = LoadImageW(Globals.hInstance, MAKEINTRESOURCEW(IDI_OSK), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);

    /* Load the strings into the "About" dialog */
    LoadStringW(Globals.hInstance, STRING_OSK, szTitle, countof(szTitle));
    LoadStringW(Globals.hInstance, STRING_AUTHORS, szAuthors, countof(szAuthors));

    /* Finally, execute the "About" dialog by using the Shell routine */
    ShellAboutW(Globals.hMainWnd, szTitle, szAuthors, OSKIcon);

    /* Once done, destroy the icon */
    DestroyIcon(OSKIcon);
}


/***********************************************************************
 *
 *           OSK_DlgInitDialog
 *
 *  Handling of WM_INITDIALOG
 */
int OSK_DlgInitDialog(HWND hDlg)
{
    HICON hIcon, hIconSm;
    HMONITOR monitor;
    MONITORINFO info;
    POINT Pt;
    RECT rcWindow, rcDlgIntersect;

    /* Save handle */
    Globals.hMainWnd = hDlg;

    /* Check the checked menu item before displaying the modal box */
    if (Globals.bIsEnhancedKeyboard)
    {
        /* Enhanced keyboard dialog chosen, set the respective menu item as checked */
        CheckMenuItem(GetMenu(hDlg), IDM_ENHANCED_KB, MF_BYCOMMAND | MF_CHECKED);
        CheckMenuItem(GetMenu(hDlg), IDM_STANDARD_KB, MF_BYCOMMAND | MF_UNCHECKED);
    }
    else
    {
        /* Standard keyboard dialog chosen, set the respective menu item as checked */
        CheckMenuItem(GetMenu(hDlg), IDM_STANDARD_KB, MF_BYCOMMAND | MF_CHECKED);
        CheckMenuItem(GetMenu(hDlg), IDM_ENHANCED_KB, MF_BYCOMMAND | MF_UNCHECKED);
    }

    /* Check if the "Click Sound" option was chosen before (and if so, then tick the menu item) */
    if (Globals.bSoundClick)
    {
        CheckMenuItem(GetMenu(hDlg), IDM_CLICK_SOUND, MF_BYCOMMAND | MF_CHECKED);
    }

    /* Set the application's icon */
    hIcon = LoadImageW(Globals.hInstance, MAKEINTRESOURCEW(IDI_OSK), IMAGE_ICON, 0, 0, LR_SHARED | LR_DEFAULTSIZE);
    hIconSm = CopyImage(hIcon, IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_COPYFROMRESOURCE);
    if (hIcon || hIconSm)
    {
        /* Set the window icons (they are deleted when the process terminates) */
        SendMessageW(Globals.hMainWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessageW(Globals.hMainWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
    }

    /* Get screen info */
    memset(&Pt, 0, sizeof(Pt));
    monitor = MonitorFromPoint(Pt, MONITOR_DEFAULTTOPRIMARY);
    info.cbSize = sizeof(info);
    GetMonitorInfoW(monitor, &info);
    GetWindowRect(hDlg, &rcWindow);

    /*
        If the coordination values are default then re-initialize using the specific formulas
        to move the dialog at the bottom of the screen.
    */
    if (Globals.PosX == CW_USEDEFAULT && Globals.PosY == CW_USEDEFAULT)
    {
        Globals.PosX = (info.rcMonitor.left + info.rcMonitor.right - (rcWindow.right - rcWindow.left)) / 2;
        Globals.PosY = info.rcMonitor.bottom - (rcWindow.bottom - rcWindow.top);
    }

    /*
        Calculate the intersection of two rectangle sources (dialog and work desktop area).
        If such sources do not intersect, then the dialog is deemed as "off screen".
    */
    if (IntersectRect(&rcDlgIntersect, &rcWindow, &info.rcWork) == 0)
    {
        Globals.PosX = (info.rcMonitor.left + info.rcMonitor.right - (rcWindow.right - rcWindow.left)) / 2;
        Globals.PosY = info.rcMonitor.bottom - (rcWindow.bottom - rcWindow.top);
    }
    else
    {
        /*
            There's still some intersection but we're not for sure if it is sufficient (the dialog could also be partially hidden).
            Therefore, check the remaining intersection if it's enough.
        */
        if (rcWindow.top < info.rcWork.top || rcWindow.left < info.rcWork.left || rcWindow.right > info.rcWork.right || rcWindow.bottom > info.rcWork.bottom)
        {
            Globals.PosX = (info.rcMonitor.left + info.rcMonitor.right - (rcWindow.right - rcWindow.left)) / 2;
            Globals.PosY = info.rcMonitor.bottom - (rcWindow.bottom - rcWindow.top);
        }
    }

    /* Move the dialog according to the placement coordination */
    SetWindowPos(hDlg, HWND_TOP, Globals.PosX, Globals.PosY, 0, 0, SWP_NOSIZE);

    /* Set icon on visual buttons */
    OSK_SetImage(SCAN_CODE_15, IDI_BACK);
    OSK_SetImage(SCAN_CODE_16, IDI_TAB);
    OSK_SetImage(SCAN_CODE_30, IDI_CAPS_LOCK);
    OSK_SetImage(SCAN_CODE_43, IDI_RETURN);
    OSK_SetImage(SCAN_CODE_44, IDI_SHIFT);
    OSK_SetImage(SCAN_CODE_57, IDI_SHIFT);
    OSK_SetImage(SCAN_CODE_127, IDI_REACTOS);
    OSK_SetImage(SCAN_CODE_128, IDI_REACTOS);
    OSK_SetImage(SCAN_CODE_129, IDI_MENU);
    OSK_SetImage(SCAN_CODE_80, IDI_HOME);
    OSK_SetImage(SCAN_CODE_85, IDI_PG_UP);
    OSK_SetImage(SCAN_CODE_86, IDI_PG_DOWN);
    OSK_SetImage(SCAN_CODE_79, IDI_LEFT);
    OSK_SetImage(SCAN_CODE_83, IDI_TOP);
    OSK_SetImage(SCAN_CODE_84, IDI_BOTTOM);
    OSK_SetImage(SCAN_CODE_89, IDI_RIGHT);

    /* Create a green brush for leds */
    Globals.hBrushGreenLed = CreateSolidBrush(RGB(0, 255, 0));

    /* Set a timer for periodics tasks */
    Globals.iTimer = SetTimer(hDlg, 0, 200, NULL);

    return TRUE;
}

/***********************************************************************
 *
 *           OSK_DlgClose
 *
 *  Handling of WM_CLOSE
 */
int OSK_DlgClose(void)
{
    KillTimer(Globals.hMainWnd, Globals.iTimer);

    /* Release Ctrl, Shift, Alt keys */
    OSK_ReleaseKey(SCAN_CODE_44); // Left shift
    OSK_ReleaseKey(SCAN_CODE_57); // Right shift
    OSK_ReleaseKey(SCAN_CODE_58); // Left ctrl
    OSK_ReleaseKey(SCAN_CODE_60); // Left alt
    OSK_ReleaseKey(SCAN_CODE_62); // Right alt
    OSK_ReleaseKey(SCAN_CODE_64); // Right ctrl

    /* delete GDI objects */
    if (Globals.hBrushGreenLed) DeleteObject(Globals.hBrushGreenLed);

    /* Save the settings to the registry hive */
    SaveDataToRegistry();

    return TRUE;
}

/***********************************************************************
 *
 *           OSK_DlgTimer
 *
 *  Handling of WM_TIMER
 */
int OSK_DlgTimer(void)
{
    /* Always redraw leds because it can be changed by the real keyboard) */
    InvalidateRect(GetDlgItem(Globals.hMainWnd, IDC_LED_NUM), NULL, TRUE);
    InvalidateRect(GetDlgItem(Globals.hMainWnd, IDC_LED_CAPS), NULL, TRUE);
    InvalidateRect(GetDlgItem(Globals.hMainWnd, IDC_LED_SCROLL), NULL, TRUE);

    return TRUE;
}

/***********************************************************************
 *
 *           OSK_DlgCommand
 *
 *  All handling of dialog command
 */
BOOL OSK_DlgCommand(WPARAM wCommand, HWND hWndControl)
{
    WORD ScanCode;
    INPUT Input;
    BOOL bExtendedKey;
    BOOL bKeyDown;
    BOOL bKeyUp;
    LONG WindowStyle;

    /* KeyDown and/or KeyUp ? */
    WindowStyle = GetWindowLongW(hWndControl, GWL_STYLE);
    if ((WindowStyle & BS_AUTOCHECKBOX) == BS_AUTOCHECKBOX)
    {
        /* 2-states key like Shift, Alt, Ctrl, ... */
        if (SendMessageW(hWndControl, BM_GETCHECK, 0, 0) == BST_CHECKED)
        {
            bKeyDown = TRUE;
            bKeyUp = FALSE;
        }
        else
        {
            bKeyDown = FALSE;
            bKeyUp = TRUE;
        }
    }
    else
    {
        /* Other key */
        bKeyDown = TRUE;
        bKeyUp = TRUE;
    }

    /* Extended key ? */
    ScanCode = wCommand;
    if (ScanCode & 0x0200)
        bExtendedKey = TRUE;
    else
        bExtendedKey = FALSE;
    ScanCode &= 0xFF;

    /* Press and release the key */
    if (bKeyDown)
    {
        Input.type = INPUT_KEYBOARD;
        Input.ki.wVk = 0;
        Input.ki.wScan = ScanCode;
        Input.ki.time = GetTickCount();
        Input.ki.dwExtraInfo = GetMessageExtraInfo();
        Input.ki.dwFlags = KEYEVENTF_SCANCODE;
        if (bExtendedKey) Input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
        SendInput(1, &Input, sizeof(Input));
    }

    if (bKeyUp)
    {
        Input.type = INPUT_KEYBOARD;
        Input.ki.wVk = 0;
        Input.ki.wScan = ScanCode;
        Input.ki.time = GetTickCount();
        Input.ki.dwExtraInfo = GetMessageExtraInfo();
        Input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        if (bExtendedKey) Input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
        SendInput(1, &Input, sizeof(Input));
    }

    /* Play the sound during clicking event (only if "Use Click Sound" menu option is ticked) */
    if (Globals.bSoundClick)
    {
        PlaySoundW(MAKEINTRESOURCEW(IDI_SOUNDCLICK), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
    }

    return TRUE;
}

/***********************************************************************
 *
 *           OSK_ReleaseKey
 *
 *  Release the key of ID wCommand
 */
BOOL OSK_ReleaseKey(WORD ScanCode)
{
    INPUT Input;
    BOOL bExtendedKey;
    LONG WindowStyle;
    HWND hWndControl;

    /* Is it a 2-states key ? */
    hWndControl = GetDlgItem(Globals.hMainWnd, ScanCode);
    WindowStyle = GetWindowLongW(hWndControl, GWL_STYLE);
    if ((WindowStyle & BS_AUTOCHECKBOX) != BS_AUTOCHECKBOX) return FALSE;

    /* Is the key down ? */
    if (SendMessageW(hWndControl, BM_GETCHECK, 0, 0) != BST_CHECKED) return TRUE;

    /* Extended key ? */
    if (ScanCode & 0x0200)
        bExtendedKey = TRUE;
    else
        bExtendedKey = FALSE;
    ScanCode &= 0xFF;

    /* Release the key */
    Input.type = INPUT_KEYBOARD;
    Input.ki.wVk = 0;
    Input.ki.wScan = ScanCode;
    Input.ki.time = GetTickCount();
    Input.ki.dwExtraInfo = GetMessageExtraInfo();
    Input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
    if (bExtendedKey) Input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    SendInput(1, &Input, sizeof(Input));

    return TRUE;
}

/***********************************************************************
 *
 *       OSK_DlgProc
 */
INT_PTR APIENTRY OSK_DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_INITDIALOG:
            OSK_DlgInitDialog(hDlg);
            return TRUE;

        case WM_TIMER:
            OSK_DlgTimer();
            return TRUE;

        case WM_CTLCOLORSTATIC:
            if ((HWND)lParam == GetDlgItem(hDlg, IDC_LED_NUM))
            {
                if (GetKeyState(VK_NUMLOCK) & 0x0001)
                    return (INT_PTR)Globals.hBrushGreenLed;
                else
                    return (INT_PTR)GetStockObject(BLACK_BRUSH);
            }
            if ((HWND)lParam == GetDlgItem(hDlg, IDC_LED_CAPS))
            {
                if (GetKeyState(VK_CAPITAL) & 0x0001)
                    return (INT_PTR)Globals.hBrushGreenLed;
                else
                    return (INT_PTR)GetStockObject(BLACK_BRUSH);
            }
            if ((HWND)lParam == GetDlgItem(hDlg, IDC_LED_SCROLL))
            {
                if (GetKeyState(VK_SCROLL) & 0x0001)
                    return (INT_PTR)Globals.hBrushGreenLed;
                else
                    return (INT_PTR)GetStockObject(BLACK_BRUSH);
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDCANCEL:
                {
                    EndDialog(hDlg, FALSE);
                    break;
                }

                case IDM_EXIT:
                {
                    EndDialog(hDlg, FALSE);
                    break;
                }

                case IDM_ENHANCED_KB:
                {
                    if (!Globals.bIsEnhancedKeyboard)
                    {
                        /*
                            The user attempted to switch to enhanced keyboard dialog type.
                            Set the member value as TRUE, destroy the dialog and save the data configuration into the registry.
                        */
                        Globals.bIsEnhancedKeyboard = TRUE;
                        EndDialog(hDlg, FALSE);
                        SaveDataToRegistry();

                        /* Change the condition of enhanced keyboard item menu to checked */
                        CheckMenuItem(GetMenu(hDlg), IDM_ENHANCED_KB, MF_BYCOMMAND | MF_CHECKED);
                        CheckMenuItem(GetMenu(hDlg), IDM_STANDARD_KB, MF_BYCOMMAND | MF_UNCHECKED);

                        /* Finally, display the dialog modal box with the enhanced keyboard dialog */
                        DialogBoxW(Globals.hInstance,
                                   MAKEINTRESOURCEW(MAIN_DIALOG_ENHANCED_KB),
                                   GetDesktopWindow(),
                                   OSK_DlgProc);
                    }

                    break;
                }

                case IDM_STANDARD_KB:
                {
                    if (Globals.bIsEnhancedKeyboard)
                    {
                        /*
                            The user attempted to switch to standard keyboard dialog type.
                            Set the member value as FALSE, destroy the dialog and save the data configuration into the registry.
                        */
                        Globals.bIsEnhancedKeyboard = FALSE;
                        EndDialog(hDlg, FALSE);
                        SaveDataToRegistry();

                        /* Change the condition of standard keyboard item menu to checked */
                        CheckMenuItem(GetMenu(hDlg), IDM_ENHANCED_KB, MF_BYCOMMAND | MF_UNCHECKED);
                        CheckMenuItem(GetMenu(hDlg), IDM_STANDARD_KB, MF_BYCOMMAND | MF_CHECKED);

                        /* Finally, display the dialog modal box with the standard keyboard dialog */
                        DialogBoxW(Globals.hInstance,
                                   MAKEINTRESOURCEW(MAIN_DIALOG_STANDARD_KB),
                                   GetDesktopWindow(),
                                   OSK_DlgProc);
                    }

                    break;
                }

                case IDM_CLICK_SOUND:
                {
                    /*
                        This case is triggered when the user attempts to click on the menu item. Before doing anything,
                        we must check the condition state of such menu item so that we can tick/untick the menu item accordingly.
                    */
                    if (!Globals.bSoundClick)
                    {
                        Globals.bSoundClick = TRUE;
                        CheckMenuItem(GetMenu(hDlg), IDM_CLICK_SOUND, MF_BYCOMMAND | MF_CHECKED);
                    }
                    else
                    {
                        Globals.bSoundClick = FALSE;
                        CheckMenuItem(GetMenu(hDlg), IDM_CLICK_SOUND, MF_BYCOMMAND | MF_UNCHECKED);
                    }

                    break;
                }

                case IDM_ABOUT:
                {
                    OSK_About();
                    break;
                }

                default:
                    OSK_DlgCommand(wParam, (HWND)lParam);
                    break;
            }
            break;

        case WM_CLOSE:
            OSK_DlgClose();
            break;
    }

    return 0;
}

/***********************************************************************
 *
 *       WinMain
 */
int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE prev,
                    LPWSTR cmdline,
                    int show)
{
    HANDLE hMutex;
    DWORD dwError;
    INT LayoutResource;
    INITCOMMONCONTROLSEX iccex;

    UNREFERENCED_PARAMETER(prev);
    UNREFERENCED_PARAMETER(cmdline);
    UNREFERENCED_PARAMETER(show);

    /*
        Obtain a mutex for the program. This will ensure that
        the program is launched only once.
    */
    hMutex = CreateMutexW(NULL, FALSE, L"OSKRunning");

    if (hMutex)
    {
        /* Check if there's already a mutex for the program */
        dwError = GetLastError();

        if (dwError == ERROR_ALREADY_EXISTS)
        {
            /*
                A mutex with the object name has been created previously.
                Therefore, another instance is already running.
            */
            DPRINT("wWinMain(): Failed to create a mutex! The program instance is already running.\n");
            CloseHandle(hMutex);
            return 0;
        }
    }

    /* Load the common controls */
    iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    iccex.dwICC = ICC_STANDARD_CLASSES | ICC_WIN95_CLASSES;
    InitCommonControlsEx(&iccex);

    ZeroMemory(&Globals, sizeof(Globals));
    Globals.hInstance = hInstance;

    /* Load the settings from the registry hive */
    LoadDataFromRegistry();

    /* If the member of the struct (bShowWarning) is set then display the dialog box */
    if (Globals.bShowWarning)
    {
        DialogBoxW(Globals.hInstance, MAKEINTRESOURCEW(IDD_WARNINGDIALOG_OSK), Globals.hMainWnd, OSK_WarningProc);
    }

    /* Before initializing the dialog execution, check if the chosen keyboard type is standard or enhanced */
    if (Globals.bIsEnhancedKeyboard)
    {
        LayoutResource = MAIN_DIALOG_ENHANCED_KB;
    }
    else
    {
        LayoutResource = MAIN_DIALOG_STANDARD_KB;
    }

    /* Create the modal box based on the configuration registry */
    DialogBoxW(hInstance,
               MAKEINTRESOURCEW(LayoutResource),
               GetDesktopWindow(),
               OSK_DlgProc);

    /* Delete the mutex */
    if (hMutex)
    {
        CloseHandle(hMutex);
    }

    return 0;
}

/* EOF */
