/*
 * Copyright (c) 2022 Winsider Seminars & Solutions, Inc.  All rights reserved.
 *
 * This file is part of System Informer.
 *
 * Authors:
 *
 *     wj32    2009-2016
 *     dmex    2017-2023
 *
 */

#ifndef _PH_PHGUI_H
#define _PH_PHGUI_H

#include <commctrl.h>

EXTERN_C_START

// guisup

#define RFF_NOBROWSE 0x0001
#define RFF_NODEFAULT 0x0002
#define RFF_CALCDIRECTORY 0x0004
#define RFF_NOLABEL 0x0008
#define RFF_NOSEPARATEMEM 0x0020
#define RFF_OPTRUNAS 0x0040

#define RFN_VALIDATE (-510)
#define RFN_LIMITEDRUNAS (-511)

typedef struct _NMRUNFILEDLGW
{
    NMHDR hdr;
    PWSTR lpszFile;
    PWSTR lpszDirectory;
    UINT ShowCmd;
} NMRUNFILEDLGW, *LPNMRUNFILEDLGW, *PNMRUNFILEDLGW;

typedef NMRUNFILEDLGW NMRUNFILEDLG;
typedef PNMRUNFILEDLGW PNMRUNFILEDLG;
typedef LPNMRUNFILEDLGW LPNMRUNFILEDLG;

#define RF_OK 0x0000
#define RF_CANCEL 0x0001
#define RF_RETRY 0x0002

typedef HANDLE HTHEME;

// GetDCEx doesn't work without these undocumented flags. 

#define DCX_USESTYLE 0x00010000
#define DCX_NODELETERGN 0x00040000

#define HRGN_FULL ((HRGN)1) // passed by WM_NCPAINT even though it's completely undocumented (wj32)

extern LONG PhSystemDpi;
extern PH_INTEGER_PAIR PhSmallIconSize;
extern PH_INTEGER_PAIR PhLargeIconSize;

PHLIBAPI
VOID
NTAPI
PhGuiSupportInitialization(
    VOID
    );

PHLIBAPI
VOID
NTAPI
PhGuiSupportUpdateSystemMetrics(
    _In_opt_ HWND WindowHandle
    );

PHLIBAPI
VOID
NTAPI
PhInitializeFont(
    _In_ HWND WindowHandle
    );

PHLIBAPI
VOID
NTAPI
PhInitializeMonospaceFont(
    _In_ HWND WindowHandle
    );

PHLIBAPI
HTHEME
NTAPI
PhOpenThemeData(
    _In_opt_ HWND WindowHandle,
    _In_ PCWSTR ClassList,
    _In_ LONG WindowDpi
    );

PHLIBAPI
VOID
NTAPI
PhCloseThemeData(
    _In_ HTHEME ThemeHandle
    );

PHLIBAPI
VOID
NTAPI
PhSetControlTheme(
    _In_ HWND Handle,
    _In_opt_ PCWSTR Theme
    );

PHLIBAPI
BOOLEAN
NTAPI
PhIsThemeActive(
    VOID
    );

PHLIBAPI
BOOLEAN
NTAPI
PhIsThemePartDefined(
    _In_ HTHEME ThemeHandle,
    _In_ INT PartId,
    _In_ INT StateId
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetThemeClass(
    _In_ HTHEME ThemeHandle,
    _Out_writes_z_(ClassLength) PWSTR Class,
    _In_ ULONG ClassLength
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetThemeColor(
    _In_ HTHEME ThemeHandle,
    _In_ INT PartId,
    _In_ INT StateId,
    _In_ INT PropId,
    _Out_ COLORREF* Color
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetThemeInt(
    _In_ HTHEME ThemeHandle,
    _In_ INT PartId,
    _In_ INT StateId,
    _In_ INT PropId,
    _Out_ PINT Value
    );

typedef enum _THEMEPARTSIZE
{
    THEMEPARTSIZE_MIN, // minimum size
    THEMEPARTSIZE_TRUE, // size without stretching
    THEMEPARTSIZE_DRAW // size that theme mgr will use to draw part
} THEMEPARTSIZE;

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetThemePartSize(
    _In_ HTHEME ThemeHandle,
    _In_opt_ HDC hdc,
    _In_ INT PartId,
    _In_ INT StateId,
    _In_opt_ LPCRECT Rect,
    _In_ THEMEPARTSIZE Flags,
    _Out_ PSIZE Size
    );

PHLIBAPI
BOOLEAN
NTAPI
PhDrawThemeBackground(
    _In_ HTHEME ThemeHandle,
    _In_ HDC hdc,
    _In_ INT PartId,
    _In_ INT StateId,
    _In_ LPCRECT Rect,
    _In_opt_ LPCRECT ClipRect
    );

PHLIBAPI
LONG
NTAPI
PhGetDpi(
    _In_ LONG Number,
    _In_ LONG DpiValue
    );

PHLIBAPI
LONG
NTAPI
PhGetMonitorDpi(
    _In_ LPCRECT rect
    );

PHLIBAPI
LONG
NTAPI
PhGetSystemDpi(
    VOID
    );

PHLIBAPI
LONG
NTAPI
PhGetTaskbarDpi(
    VOID
    );

PHLIBAPI
LONG
NTAPI
PhGetWindowDpi(
    _In_ HWND WindowHandle
    );

PHLIBAPI
LONG
NTAPI
PhGetDpiValue(
    _In_opt_ HWND WindowHandle,
    _In_opt_ LPCRECT Rect
    );

PHLIBAPI
LONG
NTAPI
PhGetSystemMetrics(
    _In_ INT Index,
    _In_opt_ LONG DpiValue
    );

PHLIBAPI
BOOLEAN
NTAPI
PhGetSystemSafeBootMode(
    VOID
    );

PHLIBAPI
BOOL
NTAPI
PhGetSystemParametersInfo(
    _In_ INT Action,
    _In_ UINT Param1,
    _Pre_maybenull_ _Post_valid_ PVOID Param2,
    _In_opt_ LONG DpiValue
    );

PHLIBAPI
VOID
NTAPI
PhGetSizeDpiValue(
    _Inout_ PRECT rect,
    _In_ LONG DpiValue,
    _In_ BOOLEAN isUnpack
    );

FORCEINLINE LONG_PTR PhGetClassStyle(
    _In_ HWND WindowHandle
    )
{
    return GetClassLongPtr(WindowHandle, GCL_STYLE);
}

FORCEINLINE VOID PhSetClassStyle(
    _In_ HWND Handle,
    _In_ LONG_PTR Mask,
    _In_ LONG_PTR Value
    )
{
    LONG_PTR style;

    style = GetClassLongPtr(Handle, GCL_STYLE);
    style = (style & ~Mask) | (Value & Mask);
    SetClassLongPtr(Handle, GCL_STYLE, style);
}

FORCEINLINE LONG_PTR PhGetWindowStyle(
    _In_ HWND WindowHandle
    )
{
    return GetWindowLongPtr(WindowHandle, GWL_STYLE);
}

FORCEINLINE LONG_PTR PhGetWindowStyleEx(
    _In_ HWND WindowHandle
    )
{
    return GetWindowLongPtr(WindowHandle, GWL_EXSTYLE);
}

FORCEINLINE VOID PhSetWindowStyle(
    _In_ HWND Handle,
    _In_ LONG_PTR Mask,
    _In_ LONG_PTR Value
    )
{
    LONG_PTR style;

    style = GetWindowLongPtr(Handle, GWL_STYLE);
    style = (style & ~Mask) | (Value & Mask);
    SetWindowLongPtr(Handle, GWL_STYLE, style);
}

FORCEINLINE VOID PhSetWindowExStyle(
    _In_ HWND Handle,
    _In_ LONG_PTR Mask,
    _In_ LONG_PTR Value
    )
{
    LONG_PTR style;

    style = GetWindowLongPtr(Handle, GWL_EXSTYLE);
    style = (style & ~Mask) | (Value & Mask);
    SetWindowLongPtr(Handle, GWL_EXSTYLE, style);
}

FORCEINLINE WNDPROC PhGetWindowProcedure(
    _In_ HWND WindowHandle
    )
{
    return (WNDPROC)GetWindowLongPtr(WindowHandle, GWLP_WNDPROC);
}

FORCEINLINE WNDPROC PhSetWindowProcedure(
    _In_ HWND WindowHandle,
    _In_ PVOID SubclassProcedure
    )
{
    return (WNDPROC)SetWindowLongPtr(WindowHandle, GWLP_WNDPROC, (LONG_PTR)SubclassProcedure);
}

#define PH_WINDOW_TIMER_DEFAULT 0xF

FORCEINLINE UINT_PTR PhSetTimer(
    _In_ HWND WindowHandle,
    _In_ UINT_PTR TimerID,
    _In_ UINT Elapse,
    _In_opt_ TIMERPROC TimerProcedure
    )
{
    assert(WindowHandle);
    return SetTimer(WindowHandle, TimerID, Elapse, TimerProcedure);
}

FORCEINLINE BOOL PhKillTimer(
    _In_ HWND WindowHandle,
    _In_ UINT_PTR TimerID
    )
{
    assert(WindowHandle);
    return KillTimer(WindowHandle, TimerID);
}

#define IDC_DIVIDER MAKEINTRESOURCE(106) // comctl32.dll

FORCEINLINE
HCURSOR
NTAPI
PhLoadCursor(
    _In_opt_ PVOID BaseAddress,
    _In_ PCWSTR CursorName
    )
{
    return (HCURSOR)LoadImage((HINSTANCE)BaseAddress, CursorName, IMAGE_CURSOR, 0, 0, LR_SHARED);
    //return LoadCursor((HINSTANCE)BaseAddress, CursorName);
}

FORCEINLINE
HCURSOR
NTAPI
PhGetCursor(
    VOID
    )
{
    return GetCursor();
}

FORCEINLINE
HCURSOR
NTAPI
PhSetCursor(
    _In_opt_ HCURSOR CursorHandle
    )
{
    return SetCursor(CursorHandle);
}

FORCEINLINE
BOOLEAN
NTAPI
PhGetKeyState(
    _In_ INT VirtualKey
    )
{
    return GetKeyState(VirtualKey) < 0;
}

#ifndef WM_REFLECT
#define WM_REFLECT 0x2000
#endif

FORCEINLINE LRESULT PhReflectMessage(
    _In_ HWND Handle,
    _In_ UINT Message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    if (Message == WM_NOTIFY)
    {
        LPNMHDR header = (LPNMHDR)lParam;

        if (header->hwndFrom == Handle)
            return SendMessage(Handle, WM_REFLECT + Message, wParam, lParam);
    }

    return 0;
}

#define REFLECT_MESSAGE(hwnd, msg, wParam, lParam) \
    { \
        LRESULT result_ = PhReflectMessage(hwnd, msg, wParam, lParam); \
        \
        if (result_) \
            return result_; \
    }

#define REFLECT_MESSAGE_DLG(hwndDlg, hwnd, msg, wParam, lParam) \
    { \
        LRESULT result_ = PhReflectMessage(hwnd, msg, wParam, lParam); \
        \
        if (result_) \
        { \
            SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, result_); \
            return TRUE; \
        } \
    }

FORCEINLINE VOID PhSetListViewStyle(
    _In_ HWND Handle,
    _In_ BOOLEAN AllowDragDrop,
    _In_ BOOLEAN ShowLabelTips
    )
{
    ULONG style;

    style = LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_INFOTIP;

    if (AllowDragDrop)
        style |= LVS_EX_HEADERDRAGDROP;
    if (ShowLabelTips)
        style |= LVS_EX_LABELTIP;

    ListView_SetExtendedListViewStyleEx(
        Handle,
        style,
        INT_ERROR
        );
}

PHLIBAPI
INT
NTAPI
PhAddListViewColumn(
    _In_ HWND ListViewHandle,
    _In_ INT Index,
    _In_ INT DisplayIndex,
    _In_ INT SubItemIndex,
    _In_ INT Format,
    _In_ INT Width,
    _In_ PWSTR Text
    );

PHLIBAPI
INT
NTAPI
PhAddListViewItem(
    _In_ HWND ListViewHandle,
    _In_ INT Index,
    _In_ PWSTR Text,
    _In_opt_ PVOID Param
    );

PHLIBAPI
INT
NTAPI
PhFindListViewItemByFlags(
    _In_ HWND ListViewHandle,
    _In_ INT StartIndex,
    _In_ ULONG Flags
    );

PHLIBAPI
INT
NTAPI
PhFindListViewItemByParam(
    _In_ HWND ListViewHandle,
    _In_ INT StartIndex,
    _In_opt_ PVOID Param
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetListViewItemImageIndex(
    _In_ HWND ListViewHandle,
    _In_ INT Index,
    _Out_ PINT ImageIndex
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetListViewItemParam(
    _In_ HWND ListViewHandle,
    _In_ INT Index,
    _Outptr_ PVOID *Param
    );

PHLIBAPI
BOOLEAN
NTAPI
PhSetListViewItemParam(
    _In_ HWND ListViewHandle,
    _In_ INT Index,
    _In_ PVOID Param
    );

PHLIBAPI
VOID
NTAPI
PhRemoveListViewItem(
    _In_ HWND ListViewHandle,
    _In_ INT Index
    );

PHLIBAPI
VOID
NTAPI
PhSetListViewItemImageIndex(
    _In_ HWND ListViewHandle,
    _In_ INT Index,
    _In_ INT ImageIndex
    );

PHLIBAPI
VOID
NTAPI
PhSetListViewSubItem(
    _In_ HWND ListViewHandle,
    _In_ INT Index,
    _In_ INT SubItemIndex,
    _In_ PWSTR Text
    );

PHLIBAPI
VOID
NTAPI
PhRedrawListViewItems(
    _In_ HWND ListViewHandle
    );

PHLIBAPI
INT
NTAPI
PhAddListViewGroup(
    _In_ HWND ListViewHandle,
    _In_ INT GroupId,
    _In_ PWSTR Text
    );

PHLIBAPI
INT
NTAPI
PhAddListViewGroupItem(
    _In_ HWND ListViewHandle,
    _In_ INT GroupId,
    _In_ INT Index,
    _In_ PWSTR Text,
    _In_opt_ PVOID Param
    );

PHLIBAPI
INT
NTAPI
PhAddTabControlTab(
    _In_ HWND TabControlHandle,
    _In_ INT Index,
    _In_ PWSTR Text
    );

#define PhaGetDlgItemText(hwndDlg, id) \
    PH_AUTO_T(PH_STRING, PhGetWindowText(GetDlgItem(hwndDlg, id)))

PHLIBAPI
PPH_STRING
NTAPI
PhGetWindowText(
    _In_ HWND WindowHandle
    );

#define PH_GET_WINDOW_TEXT_INTERNAL 0x1
#define PH_GET_WINDOW_TEXT_LENGTH_ONLY 0x2

PHLIBAPI
ULONG
NTAPI
PhGetWindowTextEx(
    _In_ HWND WindowHandle,
    _In_ ULONG Flags,
    _Out_opt_ PPH_STRING *Text
    );

PHLIBAPI
NTSTATUS
NTAPI
PhGetWindowTextToBuffer(
    _In_ HWND WindowHandle,
    _In_ ULONG Flags,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer,
    _In_opt_ ULONG BufferLength,
    _Out_opt_ PULONG ReturnLength
    );

FORCEINLINE
VOID
NTAPI
PhAddComboBoxStrings(
    _In_ HWND WindowHandle,
    _In_ PWSTR* Strings,
    _In_ ULONG NumberOfStrings
    )
{
    for (ULONG i = 0; i < NumberOfStrings; i++)
        ComboBox_AddString(WindowHandle, Strings[i]);
}

FORCEINLINE
VOID
NTAPI
PhAddComboBoxStringRefs(
    _In_ HWND WindowHandle,
    _In_ CONST PPH_STRINGREF* Strings,
    _In_ ULONG NumberOfStrings
    )
{
    for (ULONG i = 0; i < NumberOfStrings; i++)
        ComboBox_AddString(WindowHandle, Strings[i]->Buffer);
}

PHLIBAPI
PPH_STRING
NTAPI
PhGetComboBoxString(
    _In_ HWND WindowHandle,
    _In_ INT Index
    );

PHLIBAPI
INT
NTAPI
PhSelectComboBoxString(
    _In_ HWND WindowHandle,
    _In_ PWSTR String,
    _In_ BOOLEAN Partial
    );

PHLIBAPI
PPH_STRING
NTAPI
PhGetListBoxString(
    _In_ HWND WindowHandle,
    _In_ INT Index
    );

PHLIBAPI
VOID
NTAPI
PhSetStateAllListViewItems(
    _In_ HWND WindowHandle,
    _In_ ULONG State,
    _In_ ULONG Mask
    );

PHLIBAPI
PVOID
NTAPI
PhGetSelectedListViewItemParam(
    _In_ HWND WindowHandle
    );

PHLIBAPI
VOID
NTAPI
PhGetSelectedListViewItemParams(
    _In_ HWND WindowHandle,
    _Out_ PVOID **Items,
    _Out_ PULONG NumberOfItems
    );

PHLIBAPI
VOID
NTAPI
PhSetImageListBitmap(
    _In_ HIMAGELIST ImageList,
    _In_ INT Index,
    _In_ HINSTANCE InstanceHandle,
    _In_ LPCWSTR BitmapName
    );

#define PH_LOAD_ICON_SHARED 0x1
#define PH_LOAD_ICON_SIZE_SMALL 0x2
#define PH_LOAD_ICON_SIZE_LARGE 0x4
#define PH_LOAD_ICON_STRICT 0x8

PHLIBAPI
HICON
NTAPI
PhLoadIcon(
    _In_opt_ PVOID ImageBaseAddress,
    _In_ PWSTR Name,
    _In_ ULONG Flags,
    _In_opt_ ULONG Width,
    _In_opt_ ULONG Height,
    _In_opt_ LONG SystemDpi
    );

PHLIBAPI
VOID
NTAPI
PhGetStockApplicationIcon(
    _Out_opt_ HICON *SmallIcon,
    _Out_opt_ HICON *LargeIcon
    );

//PHLIBAPI
//HICON PhGetFileShellIcon(
//    _In_opt_ PWSTR FileName,
//    _In_opt_ PWSTR DefaultExtension,
//    _In_ BOOLEAN LargeIcon
//    );

PHLIBAPI
VOID
NTAPI
PhSetClipboardString(
    _In_ HWND WindowHandle,
    _In_ PPH_STRINGREF String
    );

PHLIBAPI
PPH_STRING
NTAPI
PhGetClipboardString(
    _In_ HWND WindowHandle
    );

#include <pshpack1.h>
typedef struct _DLGTEMPLATEEX
{
    USHORT dlgVer;
    USHORT signature;
    ULONG helpID;
    ULONG exStyle;
    ULONG style;
    USHORT cDlgItems;
    SHORT x;
    SHORT y;
    SHORT cx;
    SHORT cy;
    //sz_Or_Ord menu;
    //sz_Or_Ord windowClass;
    //WCHAR title[titleLen];
    //USHORT pointsize;
    //USHORT weight;
    //BYTE italic;
    //BYTE charset;
    //WCHAR typeface[stringLen];
} DLGTEMPLATEEX, *PDLGTEMPLATEEX;
#include <poppack.h>

PHLIBAPI
HWND
NTAPI
PhCreateDialogFromTemplate(
    _In_ HWND Parent,
    _In_ ULONG Style,
    _In_ PVOID Instance,
    _In_ PWSTR Template,
    _In_ DLGPROC DialogProc,
    _In_ PVOID Parameter
    );

PHLIBAPI
HWND
NTAPI
PhCreateDialog(
    _In_ PVOID Instance,
    _In_ PWSTR Template,
    _In_opt_ HWND ParentWindow,
    _In_ DLGPROC DialogProc,
    _In_opt_ PVOID Parameter
    );

PHLIBAPI
HWND
NTAPI
PhCreateWindow(
    _In_opt_ PCWSTR ClassName,
    _In_ ULONG Style,
    _In_ LONG X,
    _In_ LONG Y,
    _In_ LONG Width,
    _In_ LONG Height,
    _In_opt_ HWND ParentWindow,
    _In_opt_ HMENU MenuHandle,
    _In_opt_ PVOID InstanceHandle,
    _In_opt_ PVOID Parameter
    );

PHLIBAPI
HWND
NTAPI
PhCreateWindowEx(
    _In_opt_ PCWSTR ClassName,
    _In_ ULONG Style,
    _In_ ULONG ExStyle,
    _In_ LONG X,
    _In_ LONG Y,
    _In_ LONG Width,
    _In_ LONG Height,
    _In_opt_ HWND ParentWindow,
    _In_opt_ HMENU MenuHandle,
    _In_opt_ PVOID InstanceHandle,
    _In_opt_ PVOID Parameter
    );

PHLIBAPI
INT_PTR
NTAPI
PhDialogBox(
    _In_ PVOID Instance,
    _In_ PWSTR Template,
    _In_opt_ HWND ParentWindow,
    _In_ DLGPROC DialogProc,
    _In_opt_ PVOID Parameter
    );

PHLIBAPI
HMENU
NTAPI
PhLoadMenu(
    _In_ PVOID DllBase,
    _In_ PCWSTR MenuName
    );

PHLIBAPI
BOOLEAN PhModalPropertySheet(
    _Inout_ PROPSHEETHEADER *Header
    );

#define PH_ANCHOR_LEFT 0x1
#define PH_ANCHOR_TOP 0x2
#define PH_ANCHOR_RIGHT 0x4
#define PH_ANCHOR_BOTTOM 0x8
#define PH_ANCHOR_ALL 0xf

// This interface is horrible and should be rewritten, but it works for now.

#define PH_LAYOUT_FORCE_INVALIDATE 0x1000 // invalidate the control when it is resized
#define PH_LAYOUT_TAB_CONTROL 0x2000 // this is a dummy item, a hack for the tab control
#define PH_LAYOUT_IMMEDIATE_RESIZE 0x4000 // needed for the tab control hack

#define PH_LAYOUT_DUMMY_MASK (PH_LAYOUT_TAB_CONTROL) // items that don't have a window handle, or don't actually get their window resized

typedef struct _PH_LAYOUT_ITEM
{
    HWND Handle;
    struct _PH_LAYOUT_ITEM *ParentItem; // for rectangle calculation
    struct _PH_LAYOUT_ITEM *LayoutParentItem; // for actual resizing
    ULONG LayoutNumber;
    ULONG NumberOfChildren;
    HDWP DeferHandle;

    RECT Rect;
    RECT Margin;
    ULONG Anchor;
} PH_LAYOUT_ITEM, *PPH_LAYOUT_ITEM;

typedef struct _PH_LAYOUT_MANAGER
{
    PPH_LIST List;
    PH_LAYOUT_ITEM RootItem;

    ULONG LayoutNumber;

    LONG dpiValue;
} PH_LAYOUT_MANAGER, *PPH_LAYOUT_MANAGER;

PHLIBAPI
VOID
NTAPI
PhInitializeLayoutManager(
    _Out_ PPH_LAYOUT_MANAGER Manager,
    _In_ HWND RootWindowHandle
    );

PHLIBAPI
VOID
NTAPI
PhDeleteLayoutManager(
    _Inout_ PPH_LAYOUT_MANAGER Manager
    );

PHLIBAPI
PPH_LAYOUT_ITEM
NTAPI
PhAddLayoutItem(
    _Inout_ PPH_LAYOUT_MANAGER Manager,
    _In_ HWND Handle,
    _In_opt_ PPH_LAYOUT_ITEM ParentItem,
    _In_ ULONG Anchor
    );

PHLIBAPI
PPH_LAYOUT_ITEM
NTAPI
PhAddLayoutItemEx(
    _Inout_ PPH_LAYOUT_MANAGER Manager,
    _In_ HWND Handle,
    _In_opt_ PPH_LAYOUT_ITEM ParentItem,
    _In_ ULONG Anchor,
    _In_ RECT Margin
    );

PHLIBAPI
VOID
NTAPI
PhLayoutManagerLayout(
    _Inout_ PPH_LAYOUT_MANAGER Manager
    );

#define PH_WINDOW_CONTEXT_DEFAULT 0xFFFF

PHLIBAPI
PVOID
NTAPI
PhGetWindowContext(
    _In_ HWND WindowHandle,
    _In_ ULONG PropertyHash
    );

PHLIBAPI
VOID
NTAPI
PhSetWindowContext(
    _In_ HWND WindowHandle,
    _In_ ULONG PropertyHash,
    _In_ PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhRemoveWindowContext(
    _In_ HWND WindowHandle,
    _In_ ULONG PropertyHash
    );

FORCEINLINE
PVOID
NTAPI
PhGetWindowContextEx(
    _In_ HWND WindowHandle
    )
{
#if (PHNT_WINDOW_CLASS_CONTEXT)
    return PhGetWindowContext(WindowHandle, MAXCHAR);
#else
    //assert(GetClassLongPtr(WindowHandle, GCL_CBWNDEXTRA) == sizeof(PVOID));
    return (PVOID)GetWindowLongPtr(WindowHandle, 0);
#endif
}

FORCEINLINE
VOID
NTAPI
PhSetWindowContextEx(
    _In_ HWND WindowHandle,
    _In_ PVOID Context
    )
{
#if (PHNT_WINDOW_CLASS_CONTEXT)
    PhSetWindowContext(WindowHandle, MAXCHAR, Context);
#else
    //assert(GetClassLongPtr(WindowHandle, GCL_CBWNDEXTRA) == sizeof(PVOID));
    SetWindowLongPtr(WindowHandle, 0, (LONG_PTR)Context);
#endif
}

FORCEINLINE
VOID
NTAPI
PhRemoveWindowContextEx(
    _In_ HWND WindowHandle
    )
{
#if (PHNT_WINDOW_CLASS_CONTEXT)
    PhRemoveWindowContext(WindowHandle, MAXCHAR);
#else
    //assert(GetClassLongPtr(WindowHandle, GCL_CBWNDEXTRA) == sizeof(PVOID));
    SetWindowLongPtr(WindowHandle, 0, (LONG_PTR)NULL);
#endif
}

typedef BOOL (CALLBACK* PH_ENUM_CALLBACK)(
    _In_ HWND WindowHandle,
    _In_opt_ PVOID Context
    );

VOID PhEnumWindows(
    _In_ PH_ENUM_CALLBACK Callback,
    _In_opt_ PVOID Context
    );

typedef BOOLEAN (CALLBACK *PH_CHILD_ENUM_CALLBACK)(
    _In_ HWND WindowHandle,
    _In_opt_ PVOID Context
    );

VOID PhEnumChildWindows(
    _In_opt_ HWND WindowHandle,
    _In_ ULONG Limit,
    _In_ PH_CHILD_ENUM_CALLBACK Callback,
    _In_opt_ PVOID Context
    );

HWND PhGetProcessMainWindow(
    _In_opt_ HANDLE ProcessId,
    _In_opt_ HANDLE ProcessHandle
    );

HWND PhGetProcessMainWindowEx(
    _In_opt_ HANDLE ProcessId,
    _In_opt_ HANDLE ProcessHandle,
    _In_ BOOLEAN SkipInvisible
    );

PHLIBAPI
ULONG
NTAPI
PhGetDialogItemValue(
    _In_ HWND WindowHandle,
    _In_ INT ControlID
    );

PHLIBAPI
VOID
NTAPI
PhSetDialogItemValue(
    _In_ HWND WindowHandle,
    _In_ INT ControlID,
    _In_ ULONG Value,
    _In_ BOOLEAN Signed
    );

PHLIBAPI
VOID
NTAPI
PhSetDialogItemText(
    _In_ HWND WindowHandle,
    _In_ INT ControlID,
    _In_ PCWSTR WindowText
    );

PHLIBAPI
VOID
NTAPI
PhSetWindowText(
    _In_ HWND WindowHandle,
    _In_ PCWSTR WindowText
    );

PHLIBAPI
VOID
NTAPI
PhSetGroupBoxText(
    _In_ HWND WindowHandle,
    _In_ PCWSTR WindowText
    );

PHLIBAPI
VOID
NTAPI
PhSetWindowAlwaysOnTop(
    _In_ HWND WindowHandle,
    _In_ BOOLEAN AlwaysOnTop
    );

FORCEINLINE ULONG PhGetWindowTextLength(
    _In_ HWND WindowHandle
    )
{
    return (ULONG)SendMessage(WindowHandle, WM_GETTEXTLENGTH, 0, 0); // DefWindowProc
}

FORCEINLINE VOID PhSetDialogFocus(
    _In_ HWND WindowHandle,
    _In_ HWND FocusHandle
    )
{
    // Do not use the SendMessage function to send a WM_NEXTDLGCTL message if your application will
    // concurrently process other messages that set the focus. Use the PostMessage function instead.
    SendMessage(WindowHandle, WM_NEXTDLGCTL, (WPARAM)FocusHandle, MAKELPARAM(TRUE, 0));
}

FORCEINLINE VOID PhResizingMinimumSize(
    _Inout_ PRECT Rect,
    _In_ WPARAM Edge,
    _In_ LONG MinimumWidth,
    _In_ LONG MinimumHeight
    )
{
    if (Edge == WMSZ_BOTTOMRIGHT || Edge == WMSZ_RIGHT || Edge == WMSZ_TOPRIGHT)
    {
        if (Rect->right - Rect->left < MinimumWidth)
            Rect->right = Rect->left + MinimumWidth;
    }
    else if (Edge == WMSZ_BOTTOMLEFT || Edge == WMSZ_LEFT || Edge == WMSZ_TOPLEFT)
    {
        if (Rect->right - Rect->left < MinimumWidth)
            Rect->left = Rect->right - MinimumWidth;
    }

    if (Edge == WMSZ_BOTTOMRIGHT || Edge == WMSZ_BOTTOM || Edge == WMSZ_BOTTOMLEFT)
    {
        if (Rect->bottom - Rect->top < MinimumHeight)
            Rect->bottom = Rect->top + MinimumHeight;
    }
    else if (Edge == WMSZ_TOPRIGHT || Edge == WMSZ_TOP || Edge == WMSZ_TOPLEFT)
    {
        if (Rect->bottom - Rect->top < MinimumHeight)
            Rect->top = Rect->bottom - MinimumHeight;
    }
}

FORCEINLINE VOID PhCopyControlRectangle(
    _In_ HWND ParentWindowHandle,
    _In_ HWND FromControlHandle,
    _In_ HWND ToControlHandle
    )
{
    RECT windowRect;

    GetWindowRect(FromControlHandle, &windowRect);
    MapWindowPoints(NULL, ParentWindowHandle, (POINT *)&windowRect, 2);
    MoveWindow(ToControlHandle, windowRect.left, windowRect.top,
        windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, FALSE);
}

// icotobmp

PHLIBAPI
HBITMAP
NTAPI
PhIconToBitmap(
    _In_ HICON Icon,
    _In_ LONG Width,
    _In_ LONG Height
    );

PHLIBAPI
VOID
NTAPI
PhBitmapSetAlpha(
    _In_ PVOID Bits,
    _In_ LONG Width,
    _In_ LONG Height
    );

// extlv

#define PH_ALIGN_CENTER 0x0
#define PH_ALIGN_LEFT 0x1
#define PH_ALIGN_RIGHT 0x2
#define PH_ALIGN_TOP 0x4
#define PH_ALIGN_BOTTOM 0x8

#define PH_ALIGN_MONOSPACE_FONT 0x80000000

typedef enum _PH_ITEM_STATE
{
    // The item is normal. Use the ItemColorFunction to determine the color of the item.
    NormalItemState = 0,
    // The item is new. On the next tick, change the state to NormalItemState. When an item is in
    // this state, highlight it in NewColor.
    NewItemState,
    // The item is being removed. On the next tick, delete the item. When an item is in this state,
    // highlight it in RemovingColor.
    RemovingItemState
} PH_ITEM_STATE;

typedef COLORREF (NTAPI *PPH_EXTLV_GET_ITEM_COLOR)(
    _In_ INT Index,
    _In_ PVOID Param,
    _In_opt_ PVOID Context
    );

typedef HFONT (NTAPI *PPH_EXTLV_GET_ITEM_FONT)(
    _In_ INT Index,
    _In_ PVOID Param,
    _In_opt_ PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhSetExtendedListView(
    _In_ HWND WindowHandle
    );

PHLIBAPI
VOID
NTAPI
PhSetExtendedListViewEx(
    _In_ HWND WindowHandle,
    _In_ ULONG SortColumn,
    _In_ ULONG SortOrder
    );

PHLIBAPI
VOID
NTAPI
PhSetHeaderSortIcon(
    _In_ HWND hwnd,
    _In_ INT Index,
    _In_ PH_SORT_ORDER Order
    );

// next 1122

#define ELVM_ADDFALLBACKCOLUMN (WM_APP + 1106)
#define ELVM_ADDFALLBACKCOLUMNS (WM_APP + 1109)
#define ELVM_RESERVED5 (WM_APP + 1120)
#define ELVM_INIT (WM_APP + 1102)
#define ELVM_SETCOLUMNWIDTH (WM_APP + 1121)
#define ELVM_SETCOMPAREFUNCTION (WM_APP + 1104)
#define ELVM_SETCONTEXT (WM_APP + 1103)
#define ELVM_SETCURSOR (WM_APP + 1114)
#define ELVM_RESERVED4 (WM_APP + 1118)
#define ELVM_SETITEMCOLORFUNCTION (WM_APP + 1111)
#define ELVM_SETITEMFONTFUNCTION (WM_APP + 1117)
#define ELVM_RESERVED1 (WM_APP + 1112)
#define ELVM_SETREDRAW (WM_APP + 1116)
#define ELVM_GETSORT (WM_APP + 1113)
#define ELVM_SETSORT (WM_APP + 1108)
#define ELVM_SETSORTFAST (WM_APP + 1119)
#define ELVM_RESERVED0 (WM_APP + 1110)
#define ELVM_SETTRISTATE (WM_APP + 1107)
#define ELVM_SETTRISTATECOMPAREFUNCTION (WM_APP + 1105)
#define ELVM_SORTITEMS (WM_APP + 1101)
#define ELVM_RESERVED3 (WM_APP + 1115)

#define ExtendedListView_AddFallbackColumn(hWnd, Column) \
    SendMessage((hWnd), ELVM_ADDFALLBACKCOLUMN, (WPARAM)(Column), 0)
#define ExtendedListView_AddFallbackColumns(hWnd, NumberOfColumns, Columns) \
    SendMessage((hWnd), ELVM_ADDFALLBACKCOLUMNS, (WPARAM)(NumberOfColumns), (LPARAM)(Columns))
#define ExtendedListView_Init(hWnd) \
    SendMessage((hWnd), ELVM_INIT, 0, 0)
#define ExtendedListView_SetColumnWidth(hWnd, Column, Width) \
    SendMessage((hWnd), ELVM_SETCOLUMNWIDTH, (WPARAM)(Column), (LPARAM)(Width))
#define ExtendedListView_SetCompareFunction(hWnd, Column, CompareFunction) \
    SendMessage((hWnd), ELVM_SETCOMPAREFUNCTION, (WPARAM)(Column), (LPARAM)(CompareFunction))
#define ExtendedListView_SetContext(hWnd, Context) \
    SendMessage((hWnd), ELVM_SETCONTEXT, 0, (LPARAM)(Context))
#define ExtendedListView_SetCursor(hWnd, Cursor) \
    SendMessage((hWnd), ELVM_SETCURSOR, 0, (LPARAM)(Cursor))
#define ExtendedListView_SetItemColorFunction(hWnd, ItemColorFunction) \
    SendMessage((hWnd), ELVM_SETITEMCOLORFUNCTION, 0, (LPARAM)(ItemColorFunction))
#define ExtendedListView_SetItemFontFunction(hWnd, ItemFontFunction) \
    SendMessage((hWnd), ELVM_SETITEMFONTFUNCTION, 0, (LPARAM)(ItemFontFunction))
#define ExtendedListView_SetRedraw(hWnd, Redraw) \
    SendMessage((hWnd), ELVM_SETREDRAW, (WPARAM)(Redraw), 0)
#define ExtendedListView_GetSort(hWnd, Column, Order) \
    SendMessage((hWnd), ELVM_GETSORT, (WPARAM)(Column), (LPARAM)(Order))
#define ExtendedListView_SetSort(hWnd, Column, Order) \
    SendMessage((hWnd), ELVM_SETSORT, (WPARAM)(Column), (LPARAM)(Order))
#define ExtendedListView_SetSortFast(hWnd, Fast) \
    SendMessage((hWnd), ELVM_SETSORTFAST, (WPARAM)(Fast), 0)
#define ExtendedListView_SetTriState(hWnd, TriState) \
    SendMessage((hWnd), ELVM_SETTRISTATE, (WPARAM)(TriState), 0)
#define ExtendedListView_SetTriStateCompareFunction(hWnd, CompareFunction) \
    SendMessage((hWnd), ELVM_SETTRISTATECOMPAREFUNCTION, 0, (LPARAM)(CompareFunction))
#define ExtendedListView_SortItems(hWnd) \
    SendMessage((hWnd), ELVM_SORTITEMS, 0, 0)

#define ELVSCW_AUTOSIZE (-1)
#define ELVSCW_AUTOSIZE_USEHEADER (-2)
#define ELVSCW_AUTOSIZE_REMAININGSPACE (-3)

/**
 * Gets the brightness of a color.
 *
 * \param Color The color.
 *
 * \return A value ranging from 0 to 255, indicating the brightness of the color.
 */
FORCEINLINE
ULONG
PhGetColorBrightness(
    _In_ COLORREF Color
    )
{
    ULONG r = Color & 0xff;
    ULONG g = (Color >> 8) & 0xff;
    ULONG b = (Color >> 16) & 0xff;
    ULONG min;
    ULONG max;

    min = r;
    if (g < min) min = g;
    if (b < min) min = b;

    max = r;
    if (g > max) max = g;
    if (b > max) max = b;

    return (min + max) / 2;
}

FORCEINLINE
COLORREF
PhHalveColorBrightness(
    _In_ COLORREF Color
    )
{
    /*return RGB(
        (UCHAR)Color / 2,
        (UCHAR)(Color >> 8) / 2,
        (UCHAR)(Color >> 16) / 2
        );*/
    // Since all targets are little-endian, we can use the following method.
    *((PUCHAR)&Color) /= 2;
    *((PUCHAR)&Color + 1) /= 2;
    *((PUCHAR)&Color + 2) /= 2;

    return Color;
}

FORCEINLINE
COLORREF
PhMakeColorBrighter(
    _In_ COLORREF Color,
    _In_ UCHAR Increment
    )
{
    UCHAR r;
    UCHAR g;
    UCHAR b;

    r = (UCHAR)Color;
    g = (UCHAR)(Color >> 8);
    b = (UCHAR)(Color >> 16);

    if (r <= 255 - Increment)
        r += Increment;
    else
        r = 255;

    if (g <= 255 - Increment)
        g += Increment;
    else
        g = 255;

    if (b <= 255 - Increment)
        b += Increment;
    else
        b = 255;

    return RGB(r, g, b);
}

// Window support

typedef enum _PH_PLUGIN_WINDOW_EVENT_TYPE
{
    PH_PLUGIN_WINDOW_EVENT_TYPE_NONE,
    PH_PLUGIN_WINDOW_EVENT_TYPE_TOPMOST,
    PH_PLUGIN_WINDOW_EVENT_TYPE_MAX
} PH_PLUGIN_WINDOW_EVENT_TYPE;

typedef struct _PH_PLUGIN_WINDOW_CALLBACK_REGISTRATION
{
    HWND WindowHandle;
    PH_PLUGIN_WINDOW_EVENT_TYPE Type;
} PH_PLUGIN_WINDOW_CALLBACK_REGISTRATION, *PPH_PLUGIN_WINDOW_CALLBACK_REGISTRATION;

typedef struct _PH_PLUGIN_WINDOW_NOTIFY_EVENT
{
    PH_PLUGIN_WINDOW_EVENT_TYPE Type;
    union
    {
        BOOLEAN TopMost;
        //HFONT FontHandle;
    };
} PH_PLUGIN_WINDOW_NOTIFY_EVENT, *PPH_PLUGIN_WINDOW_NOTIFY_EVENT;

typedef struct _PH_PLUGIN_MAINWINDOW_NOTIFY_EVENT
{
    PPH_PLUGIN_WINDOW_NOTIFY_EVENT Event;
    PPH_PLUGIN_WINDOW_CALLBACK_REGISTRATION Callback;
} PH_PLUGIN_MAINWINDOW_NOTIFY_EVENT, *PPH_PLUGIN_MAINWINDOW_NOTIFY_EVENT;

PHLIBAPI
VOID
NTAPI
PhRegisterWindowCallback(
    _In_ HWND WindowHandle,
    _In_ PH_PLUGIN_WINDOW_EVENT_TYPE Type,
    _In_opt_ PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhUnregisterWindowCallback(
    _In_ HWND WindowHandle
    );

PHLIBAPI
VOID
NTAPI
PhWindowNotifyTopMostEvent(
    _In_ BOOLEAN TopMost
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhRegenerateUserEnvironment(
    _Out_opt_ PVOID* NewEnvironment,
    _In_ BOOLEAN UpdateCurrentEnvironment
    );

PHLIBAPI
BOOLEAN
NTAPI
PhIsImmersiveProcess(
    _In_ HANDLE ProcessHandle
    );

typedef enum _PROCESS_UICONTEXT
{
    PROCESS_UICONTEXT_DESKTOP,
    PROCESS_UICONTEXT_IMMERSIVE,
    PROCESS_UICONTEXT_IMMERSIVE_BROKER,
    PROCESS_UICONTEXT_IMMERSIVE_BROWSER
} PROCESS_UICONTEXT;

typedef enum _PROCESS_UI_FLAGS
{
    PROCESS_UIF_NONE,
    PROCESS_UIF_AUTHORING_MODE,
    PROCESS_UIF_RESTRICTIONS_DISABLED
} PROCESS_UI_FLAGS;

typedef struct _PROCESS_UICONTEXT_INFORMATION
{
    PROCESS_UICONTEXT ProcessUIContext;
    PROCESS_UI_FLAGS Flags;
} PROCESS_UICONTEXT_INFORMATION, *PPROCESS_UICONTEXT_INFORMATION;

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetProcessUIContextInformation(
    _In_ HANDLE ProcessHandle,
    _Out_ PPROCESS_UICONTEXT_INFORMATION UIContext
    );

typedef enum _PH_PROCESS_DPI_AWARENESS
{
    PH_PROCESS_DPI_AWARENESS_UNAWARE = 0,
    PH_PROCESS_DPI_AWARENESS_SYSTEM_DPI_AWARE = 1,
    PH_PROCESS_DPI_AWARENESS_PER_MONITOR_DPI_AWARE = 2,
    PH_PROCESS_DPI_AWARENESS_PER_MONITOR_AWARE_V2 = 3,
    PH_PROCESS_DPI_AWARENESS_UNAWARE_GDISCALED = 4,
} PH_PROCESS_DPI_AWARENESS, *PPH_PROCESS_DPI_AWARENESS;

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetProcessDpiAwareness(
    _In_ HANDLE ProcessHandle,
    _Out_ PPH_PROCESS_DPI_AWARENESS ProcessDpiAwareness
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetPhysicallyInstalledSystemMemory(
    _Out_ PULONGLONG TotalMemory,
    _Out_ PULONGLONG ReservedMemory
    );

PHLIBAPI
NTSTATUS
NTAPI
PhGetSessionGuiResources(
    _In_ ULONG Flags,
    _Out_ PULONG Total
    );

PHLIBAPI
NTSTATUS
NTAPI
PhGetProcessGuiResources(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags,
    _Out_ PULONG Total
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetThreadWin32Thread(
    _In_ HANDLE ThreadId,
    _Out_opt_ PGUITHREADINFO ThreadInfo
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhGetSendMessageReceiver(
    _In_ HANDLE ThreadId,
    _Out_ HWND *WindowHandle
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhExtractIcon(
    _In_ PWSTR FileName,
    _Out_opt_ HICON *IconLarge,
    _Out_opt_ HICON *IconSmall
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhExtractIconEx(
    _In_ PPH_STRINGREF FileName,
    _In_ BOOLEAN NativeFileName,
    _In_ INT32 IconIndex,
    _Out_opt_ HICON *IconLarge,
    _Out_opt_ HICON *IconSmall,
    _In_ LONG WindowDpi
    );

// Imagelist support

PHLIBAPI
HIMAGELIST
NTAPI
PhImageListCreate(
    _In_ INT32 Width,
    _In_ INT32 Height,
    _In_ UINT32 Flags,
    _In_ INT32 InitialCount,
    _In_ INT32 GrowCount
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListDestroy(
    _In_opt_ HIMAGELIST ImageListHandle
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListSetImageCount(
    _In_ HIMAGELIST ImageListHandle,
    _In_ UINT32 Count
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListGetImageCount(
    _In_ HIMAGELIST ImageListHandle,
    _Out_ PINT32 Count
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListSetBkColor(
    _In_ HIMAGELIST ImageListHandle,
    _In_ COLORREF BackgroundColor
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListRemoveIcon(
    _In_ HIMAGELIST ImageListHandle,
    _In_ INT32 Index
    );

#define PhImageListRemoveAll(ImageListHandle) \
    PhImageListRemoveIcon((ImageListHandle), INT_ERROR)

PHLIBAPI
INT32
NTAPI
PhImageListAddIcon(
    _In_ HIMAGELIST ImageListHandle,
    _In_ HICON IconHandle
    );

PHLIBAPI
INT32
NTAPI
PhImageListAddBitmap(
    _In_ HIMAGELIST ImageListHandle,
    _In_ HBITMAP BitmapImage,
    _In_opt_ HBITMAP BitmapMask
    );

PHLIBAPI
HICON
NTAPI
PhImageListGetIcon(
    _In_ HIMAGELIST ImageListHandle,
    _In_ INT32 Index,
    _In_ UINT32 Flags
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListGetIconSize(
    _In_ HIMAGELIST ImageListHandle,
    _Out_ PINT32 cx,
    _Out_ PINT32 cy
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListReplace(
    _In_ HIMAGELIST ImageListHandle,
    _In_ INT32 Index,
    _In_ HBITMAP BitmapImage,
    _In_opt_ HBITMAP BitmapMask
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListDrawIcon(
    _In_ HIMAGELIST ImageListHandle,
    _In_ INT32 Index,
    _In_ HDC Hdc,
    _In_ INT32 x,
    _In_ INT32 y,
    _In_ UINT32 Style,
    _In_ BOOLEAN Disabled
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListDrawEx(
    _In_ HIMAGELIST ImageListHandle,
    _In_ INT32 Index,
    _In_ HDC Hdc,
    _In_ INT32 x,
    _In_ INT32 y,
    _In_ INT32 dx,
    _In_ INT32 dy,
    _In_ COLORREF BackColor,
    _In_ COLORREF ForeColor,
    _In_ UINT Style,
    _In_ ULONG State
    );

PHLIBAPI
BOOLEAN
NTAPI
PhImageListSetIconSize(
    _In_ HIMAGELIST ImageListHandle,
    _In_ INT32 cx,
    _In_ INT32 cy
    );

#define PH_SHUTDOWN_RESTART 0x1
#define PH_SHUTDOWN_POWEROFF 0x2
#define PH_SHUTDOWN_INSTALL_UPDATES 0x4
#define PH_SHUTDOWN_HYBRID 0x8
#define PH_SHUTDOWN_RESTART_BOOTOPTIONS 0x10

PHLIBAPI
ULONG
NTAPI
PhInitiateShutdown(
    _In_ ULONG Flags
    );

PHLIBAPI
BOOLEAN
NTAPI
PhSetProcessShutdownParameters(
    _In_ ULONG Level,
    _In_ ULONG Flags
    );

PHLIBAPI
VOID
NTAPI
PhCustomDrawTreeCpuHeatMap(
    _In_ HWND WindowHandle,
    _In_ HDC Hdc,
    _In_ RECT CellRect,
    _In_ RECT TextRect,
    _In_ ULONG ShowCpuBelow001,
    _In_ FLOAT Value
    );

PHLIBAPI
VOID
NTAPI
PhCustomDrawTreePrivateBytesHeatMap(
    _In_ HWND WindowHandle,
    _In_ HDC Hdc,
    _In_ RECT CellRect,
    _In_ RECT TextRect,
    _In_ SIZE_T Value,
    _In_ SIZE_T Total
    );

#define PH_DRAW_TIMELINE_OVERFLOW 0x1
#define PH_DRAW_TIMELINE_DARKTHEME 0x2

PHLIBAPI
VOID
NTAPI
PhCustomDrawTreeTimeLine(
    _In_ HDC Hdc,
    _In_ RECT CellRect,
    _In_ ULONG Flags,
    _In_opt_ PLARGE_INTEGER StartTime,
    _In_ PLARGE_INTEGER CreateTime
    );

// Windows Imaging Component (WIC) bitmap support

typedef enum _PH_IMAGE_FORMAT_TYPE
{
    PH_IMAGE_FORMAT_TYPE_NONE,
    PH_IMAGE_FORMAT_TYPE_ICO,
    PH_IMAGE_FORMAT_TYPE_BMP,
    PH_IMAGE_FORMAT_TYPE_JPG,
    PH_IMAGE_FORMAT_TYPE_PNG,
} PH_IMAGE_FORMAT_TYPE, *PPH_IMAGE_FORMAT_TYPE;

PHLIBAPI
HBITMAP
NTAPI
PhLoadImageFormatFromResource(
    _In_ PVOID DllBase,
    _In_ PCWSTR Name,
    _In_ PCWSTR Type,
    _In_ PH_IMAGE_FORMAT_TYPE Format,
    _In_ UINT Width,
    _In_ UINT Height
    );

PHLIBAPI
HBITMAP
NTAPI
PhLoadImageFromResource(
    _In_ PVOID DllBase,
    _In_ PCWSTR Name,
    _In_ PCWSTR Type,
    _In_ UINT Width,
    _In_ UINT Height
    );

PHLIBAPI
HBITMAP
NTAPI
PhLoadImageFromFile(
    _In_ PWSTR FileName,
    _In_ UINT Width,
    _In_ UINT Height
    );

// Acrylic support

typedef enum _WINDOWCOMPOSITIONATTRIB
{
    WCA_UNDEFINED = 0,
    WCA_NCRENDERING_ENABLED = 1,
    WCA_NCRENDERING_POLICY = 2,
    WCA_TRANSITIONS_FORCEDISABLED = 3,
    WCA_ALLOW_NCPAINT = 4,
    WCA_CAPTION_BUTTON_BOUNDS = 5,
    WCA_NONCLIENT_RTL_LAYOUT = 6,
    WCA_FORCE_ICONIC_REPRESENTATION = 7,
    WCA_EXTENDED_FRAME_BOUNDS = 8,
    WCA_HAS_ICONIC_BITMAP = 9,
    WCA_THEME_ATTRIBUTES = 10,
    WCA_NCRENDERING_EXILED = 11,
    WCA_NCADORNMENTINFO = 12,
    WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
    WCA_VIDEO_OVERLAY_ACTIVE = 14,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
    WCA_DISALLOW_PEEK = 16,
    WCA_CLOAK = 17,
    WCA_CLOAKED = 18,
    WCA_ACCENT_POLICY = 19,
    WCA_FREEZE_REPRESENTATION = 20,
    WCA_EVER_UNCLOAKED = 21,
    WCA_VISUAL_OWNER = 22,
    WCA_HOLOGRAPHIC = 23,
    WCA_EXCLUDED_FROM_DDA = 24,
    WCA_PASSIVEUPDATEMODE = 25,
    WCA_USEDARKMODECOLORS = 26,
    WCA_CORNER_STYLE = 27,
    WCA_PART_COLOR = 28,
    WCA_DISABLE_MOVESIZE_FEEDBACK = 29,
    WCA_SYSTEMBACKDROP_TYPE = 30,
    WCA_SET_TAGGED_WINDOW_RECT = 31,
    WCA_CLEAR_TAGGED_WINDOW_RECT = 32,
    WCA_LAST
} WINDOWCOMPOSITIONATTRIB;

typedef struct _WINDOWCOMPOSITIONATTRIBUTEDATA
{
    WINDOWCOMPOSITIONATTRIB Attribute;
    PVOID Data;
    SIZE_T Length;
} WINDOWCOMPOSITIONATTRIBUTEDATA, *PWINDOWCOMPOSITIONATTRIBUTEDATA;

PHLIBAPI
BOOLEAN
NTAPI
PhSetWindowCompositionAttribute(
    _In_ HWND WindowHandle,
    _In_ PWINDOWCOMPOSITIONATTRIBUTEDATA AttributeData
    );

// TODO: https://stackoverflow.com/questions/12304848/fast-algorithm-to-invert-an-argb-color-value-to-abgr/42133405#42133405
FORCEINLINE ULONG MakeARGB(
    _In_ BYTE a,
    _In_ BYTE r,
    _In_ BYTE g,
    _In_ BYTE b)
{
    return (((ULONG)(b) << 0) | ((ULONG)(g) << 8) | ((ULONG)(r) << 16) | ((ULONG)(a) << 24));
}

FORCEINLINE ULONG MakeABGR(
    _In_ BYTE a,
    _In_ BYTE b,
    _In_ BYTE g,
    _In_ BYTE r)
{
    return (((ULONG)(a) << 24) | ((ULONG)(b) << 16) | ((ULONG)(g) << 8) | ((ULONG)(r) << 0));
}

FORCEINLINE ULONG MakeARGBFromCOLORREF(_In_ BYTE Alpha, _In_ COLORREF rgb)
{
    return MakeARGB(Alpha, GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
}

FORCEINLINE ULONG MakeABGRFromCOLORREF(_In_ BYTE Alpha, _In_ COLORREF rgb)
{
    return MakeABGR(Alpha, GetBValue(rgb), GetGValue(rgb), GetRValue(rgb));
}

typedef enum _ACCENT_STATE
{
    ACCENT_DISABLED,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,
    ACCENT_ENABLE_HOSTBACKDROP = 5,
    ACCENT_INVALID_STATE
} ACCENT_STATE;

typedef enum _ACCENT_FLAG
{
    ACCENT_NONE,
    ACCENT_WINDOWS11_LUMINOSITY = 0x2,
    ACCENT_BORDER_LEFT = 0x20,
    ACCENT_BORDER_TOP = 0x40,
    ACCENT_BORDER_RIGHT = 0x80,
    ACCENT_BORDER_BOTTOM = 0x100,
    ACCENT_BORDER_ALL = (ACCENT_BORDER_LEFT | ACCENT_BORDER_TOP | ACCENT_BORDER_RIGHT | ACCENT_BORDER_BOTTOM)
} ACCENT_FLAG;

typedef struct _ACCENT_POLICY
{
    ACCENT_STATE AccentState;
    ULONG AccentFlags;
    ULONG GradientColor;
    ULONG AnimationId;
} ACCENT_POLICY;

PHLIBAPI
BOOLEAN
NTAPI
PhSetWindowAcrylicCompositionColor(
    _In_ HWND WindowHandle,
    _In_ ULONG GradientColor
    );

PHLIBAPI
HCURSOR
NTAPI
PhLoadArrowCursor(
    VOID
    );

PHLIBAPI
HCURSOR
NTAPI
PhLoadDividerCursor(
    VOID
    );

PHLIBAPI
BOOLEAN
NTAPI
PhIsInteractiveUserSession(
    VOID
    );

PHLIBAPI
PPH_STRING
NTAPI
PhGetCurrentWindowStationName(
    VOID
    );

PHLIBAPI
PPH_STRING
NTAPI
PhGetCurrentThreadDesktopName(
    VOID
    );

_Success_(return)
PHLIBAPI
BOOLEAN
NTAPI
PhRecentListCreate(
    _Out_ PHANDLE RecentHandle
    );

PHLIBAPI
VOID
NTAPI
PhRecentListDestroy(
    _In_ HANDLE RecentHandle
    );

PHLIBAPI
BOOLEAN
NTAPI
PhRecentListAddCommand(
    _In_ PPH_STRINGREF Command
    );

typedef BOOLEAN (NTAPI* PPH_ENUM_MRULIST_CALLBACK)(
    _In_ PPH_STRINGREF Command,
    _In_opt_ PVOID Context
    );

PHLIBAPI
VOID
NTAPI
PhEnumerateRecentList(
    _In_ PPH_ENUM_MRULIST_CALLBACK Callback,
    _In_opt_ PVOID Context
    );

#ifndef DBT_DEVICEARRIVAL
#define DBT_DEVICEARRIVAL        0x8000  // system detected a new device
#define DBT_DEVICEREMOVECOMPLETE 0x8004  // device is gone

#define DBT_DEVTYP_VOLUME        0x00000002  // logical volume

typedef struct _DEV_BROADCAST_HDR
{
    ULONG dbch_size;
    ULONG dbch_devicetype;
    ULONG dbch_reserved;
} DEV_BROADCAST_HDR, *PDEV_BROADCAST_HDR;
#endif

// theme support (theme.c)

extern HFONT PhApplicationFont;
extern HFONT PhTreeWindowFont;
extern HFONT PhMonospaceFont;
extern HBRUSH PhThemeWindowBackgroundBrush;
extern BOOLEAN PhEnableThemeSupport;
extern BOOLEAN PhEnableThemeAcrylicSupport;
extern BOOLEAN PhEnableThemeListviewBorder;
extern COLORREF PhThemeWindowForegroundColor;
extern COLORREF PhThemeWindowBackgroundColor;
extern COLORREF PhThemeWindowBackground2Color;
extern COLORREF PhThemeWindowHighlightColor;
extern COLORREF PhThemeWindowTextColor;

PHLIBAPI
VOID
NTAPI
PhInitializeWindowTheme(
    _In_ HWND WindowHandle,
    _In_ BOOLEAN EnableThemeSupport
    );

PHLIBAPI
VOID
NTAPI
PhInitializeWindowThemeEx(
    _In_ HWND WindowHandle
    );

PHLIBAPI
VOID
NTAPI
PhReInitializeWindowTheme(
    _In_ HWND WindowHandle
    );

PHLIBAPI
VOID
NTAPI
PhInitializeThemeWindowFrame(
    _In_ HWND WindowHandle
    );

PHLIBAPI
HBRUSH
NTAPI
PhWindowThemeControlColor(
    _In_ HWND WindowHandle,
    _In_ HDC Hdc,
    _In_ HWND ChildWindowHandle,
    _In_ INT Type
    );

PHLIBAPI
BOOLEAN
NTAPI
PhThemeWindowDrawItem(
    _In_ HWND WindowHandle,
    _In_ PDRAWITEMSTRUCT DrawInfo
    );

PHLIBAPI
BOOLEAN
NTAPI
PhThemeWindowMeasureItem(
    _In_ HWND WindowHandle,
    _In_ PMEASUREITEMSTRUCT DrawInfo
    );

PHLIBAPI
VOID
NTAPI
PhInitializeWindowThemeMainMenu(
    _In_ HMENU MenuHandle
    );

PHLIBAPI
LRESULT
CALLBACK
PhThemeWindowDrawRebar(
    _In_ LPNMCUSTOMDRAW DrawInfo
    );

PHLIBAPI
LRESULT
CALLBACK
PhThemeWindowDrawToolbar(
    _In_ LPNMTBCUSTOMDRAW DrawInfo
    );

// Font support

FORCEINLINE
HFONT
NTAPI
PhCreateFont(
    _In_opt_ PWSTR Name,
    _In_ ULONG Size,
    _In_ ULONG Weight,
    _In_ ULONG PitchAndFamily,
    _In_ LONG dpiValue
    )
{
    return CreateFont(
        -(LONG)PhMultiplyDivide(Size, dpiValue, 72),
        0,
        0,
        0,
        Weight,
        FALSE,
        FALSE,
        FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        PitchAndFamily,
        Name
        );
}

FORCEINLINE
HFONT
NTAPI
PhCreateCommonFont(
    _In_ LONG Size,
    _In_ INT Weight,
    _In_opt_ HWND hwnd,
    _In_ LONG dpiValue
    )
{
    HFONT fontHandle;
    LOGFONT logFont;

    if (!PhGetSystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &logFont, dpiValue))
        return NULL;

    fontHandle = CreateFont(
        -PhMultiplyDivideSigned(Size, dpiValue, 72),
        0,
        0,
        0,
        Weight,
        FALSE,
        FALSE,
        FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY,
        DEFAULT_PITCH,
        logFont.lfFaceName
        );

    if (!fontHandle)
        return NULL;

    if (hwnd)
        SetWindowFont(hwnd, fontHandle, TRUE);

    return fontHandle;
}

FORCEINLINE
HFONT
NTAPI
PhCreateIconTitleFont(
    _In_opt_ LONG WindowDpi
    )
{
    LOGFONT logFont;

    if (PhGetSystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &logFont, WindowDpi))
        return CreateFontIndirect(&logFont);

    return NULL;
}

FORCEINLINE
HFONT
NTAPI
PhCreateMessageFont(
    _In_opt_ LONG WindowDpi
    )
{
    NONCLIENTMETRICS metrics = { sizeof(metrics) };

    if (PhGetSystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, WindowDpi))
        return CreateFontIndirect(&metrics.lfMessageFont);

    return NULL;
}

FORCEINLINE
HFONT
NTAPI
PhDuplicateFont(
    _In_ HFONT Font
    )
{
    LOGFONT logFont;

    if (GetObject(Font, sizeof(LOGFONT), &logFont))
        return CreateFontIndirect(&logFont);

    return NULL;
}

FORCEINLINE
HFONT
NTAPI
PhDuplicateFontWithNewWeight(
    _In_ HFONT Font,
    _In_ LONG NewWeight
    )
{
    LOGFONT logFont;

    if (GetObject(Font, sizeof(LOGFONT), &logFont))
    {
        logFont.lfWeight = NewWeight;
        return CreateFontIndirect(&logFont);
    }

    return NULL;
}

FORCEINLINE
HFONT
NTAPI
PhDuplicateFontWithNewHeight(
    _In_ HFONT Font,
    _In_ LONG NewHeight,
    _In_ LONG dpiValue
    )
{
    LOGFONT logFont;

    if (GetObject(Font, sizeof(LOGFONT), &logFont))
    {
        logFont.lfHeight = PhGetDpi(NewHeight, dpiValue);
        return CreateFontIndirect(&logFont);
    }

    return NULL;
}

FORCEINLINE
BOOLEAN
NTAPI
PhRectEmpty(
    _In_ CONST PRECT Rect
    )
{
#if (PHNT_NATIVE_RECT)
    return !!IsRectEmpty(Rect);
#else
    if (!Rect)
        return TRUE;

    if (Rect->left >= Rect->right || Rect->top >= Rect->bottom)
        return TRUE;

    return FALSE;
#endif
}

FORCEINLINE
VOID
NTAPI
PhInflateRect(
    _In_ CONST PRECT Rect,
    _In_ INT dx,
    _In_ INT dy
    )
{
#if (PHNT_NATIVE_RECT)
    InflateRect(Rect, dx, dy);
#else
    Rect->left -= dx;
    Rect->top -= dy;
    Rect->right += dx;
    Rect->bottom += dy;
#endif
}

FORCEINLINE
VOID
NTAPI
PhOffsetRect(
    _In_ CONST PRECT Rect,
    _In_ INT dx,
    _In_ INT dy
    )
{
#if (PHNT_NATIVE_RECT)
    OffsetRect(Rect, dx, dy);
#else
    Rect->left += dx;
    Rect->top += dy;
    Rect->right += dx;
    Rect->bottom += dy;
#endif
}

FORCEINLINE
BOOLEAN
NTAPI
PhPtInRect(
    _In_ CONST PRECT Rect,
    _In_ CONST POINT Point
    )
{
#if (PHNT_NATIVE_RECT)
    return !!PtInRect(Rect, Point);
#else
    return Point.x >= Rect->left && Point.x < Rect->right &&
        Point.y >= Rect->top && Point.y < Rect->bottom;
#endif
}

FORCEINLINE
BOOLEAN
NTAPI
PhEqualRect(
    _In_ CONST PRECT Rect1,
    _In_ CONST PRECT Rect2
    )
{
#if (PHNT_NATIVE_RECT)
    return !!EqualRect(Rect1, Rect2);
#else
    return RtlEqualMemory(Rect1, Rect2, sizeof(RECT));
#endif
}

VOID PhWindowThemeMainMenuBorder(
    _In_ HWND WindowHandle
    );

// directdraw.cpp

HICON PhGdiplusConvertBitmapToIcon(
    _In_ HBITMAP Bitmap,
    _In_ LONG Width,
    _In_ LONG Height,
    _In_ COLORREF Background
    );

HWND PhCreateBackgroundWindow(
    _In_ HWND ParentWindowHandle
    );

// Listview2 (Undocumented)

#ifndef LVM_QUERYINTERFACE
#define LVM_QUERYINTERFACE (LVM_FIRST + 189) // IListView, IListView2, IOleWindow, IVisualProperties, IPropertyControlSite, IListViewFooter
#endif

DEFINE_GUID(IID_IListView, 0xE5B16AF2, 0x3990, 0x4681, 0xA6, 0x09, 0x1F, 0x06, 0x0C, 0xD1, 0x42, 0x69);
DEFINE_GUID(IID_IDrawPropertyControl, 0xE6DFF6FD, 0xBCD5, 0x4162, 0x9C, 0x65, 0xA3, 0xB1, 0x8C, 0x61, 0x6F, 0xDB);
DEFINE_GUID(IID_IDrawPropertyControlWin10, 0x1572DD51, 0x443C, 0x44B0, 0xAC, 0xE4, 0x38, 0xA0, 0x05, 0xFC, 0x69, 0x7E);
// {F0034DA8-8A22-4151-8F16-2EBA76565BCC}
DEFINE_GUID(IID_IListViewFooter, 0xF0034DA8, 0x8A22, 0x4151, 0x8F, 0x16, 0x2E, 0xBA, 0x76, 0x56, 0x5B, 0xCC);
// {88EB9442-913B-4AB4-A741-DD99DCB7558B}
DEFINE_GUID(IID_IListViewFooterCallback, 0x88EB9442, 0x913B, 0x4AB4, 0xA7, 0x41, 0xDD, 0x99, 0xDC, 0xB7, 0x55, 0x8B);
// {44C09D56-8D3B-419D-A462-7B956B105B47}
DEFINE_GUID(IID_IOwnerDataCallback, 0x44C09D56, 0x8D3B, 0x419D, 0xA4, 0x62, 0x7B, 0x95, 0x6B, 0x10, 0x5B, 0x47);
// {5E82A4DD-9561-476A-8634-1BEBACBA4A38}
DEFINE_GUID(IID_IPropertyControl, 0x5E82A4DD, 0x9561, 0x476A, 0x86, 0x34, 0x1B, 0xEB, 0xAC, 0xBA, 0x4A, 0x38);
// {6E71A510-732A-4557-9596-A827E36DAF8F}
DEFINE_GUID(IID_IPropertyControlBase, 0x6E71A510, 0x732A, 0x4557, 0x95, 0x96, 0xA8, 0x27, 0xE3, 0x6D, 0xAF, 0x8F);
// {7AF7F355-1066-4E17-B1F2-19FE2F099CD2}
DEFINE_GUID(IID_IPropertyValue, 0x7AF7F355, 0x1066, 0x4E17, 0xB1, 0xF2, 0x19, 0xFE, 0x2F, 0x09, 0x9C, 0xD2);
// {11A66240-5489-42C2-AEBF-286FC831524C}
DEFINE_GUID(IID_ISubItemCallback, 0x11A66240, 0x5489, 0x42C2, 0xAE, 0xBF, 0x28, 0x6F, 0xC8, 0x31, 0x52, 0x4C);

DEFINE_GUID(CLSID_CAsyncSubItemControlsView, 0xa1dccc29, 0x7c70, 0x4821, 0x97, 0xae, 0x67, 0xf0, 0x41, 0x5, 0xec, 0x91);
DEFINE_GUID(CLSID_CFooterAreaView, 0xebe684bf, 0x3301, 0x4a6d, 0x83, 0xce, 0xe4, 0xd6, 0x85, 0x1b, 0xe8, 0x81);
DEFINE_GUID(CLSID_CGroupedVirtualModeView, 0xa08a0f2d, 0x647, 0x4443, 0x94, 0x50, 0xc4, 0x60, 0xf4, 0x79, 0x10, 0x46);
DEFINE_GUID(CLSID_CGroupSubsetView, 0x64a11699, 0x104a, 0x482a, 0x9d, 0x85, 0xcc, 0xfe, 0xa2, 0xee, 0x3c, 0x94);
DEFINE_GUID(CLSID_CSubItemControlsView, 0x13e88673, 0xd30c, 0x46ba, 0x8f, 0x2e, 0x97, 0xc5, 0xcd, 0x2, 0x4e, 0x73);

// {1E8F0D70-7399-41BF-8598-7949A2DEC898}
DEFINE_GUID(CLSID_CBooleanControl, 0x1E8F0D70, 0x7399, 0x41BF, 0x85, 0x98, 0x79, 0x49, 0xA2, 0xDE, 0xC8, 0x98);
// {e2183960-9d58-4e9c-878a-4acc06ca564a}
DEFINE_GUID(CLSID_CCustomDrawMultiValuePropertyControl, 0xE2183960, 0x9D58, 0x4E9C, 0x87, 0x8A, 0x4A, 0xCC, 0x06, 0xCA, 0x56, 0x4A);
// {AB517586-73CF-489c-8D8C-5AE0EAD0613A}
DEFINE_GUID(CLSID_CCustomDrawPercentFullControl, 0xAB517586, 0x73CF, 0x489c, 0x8D, 0x8C, 0x5A, 0xE0, 0xEA, 0xD0, 0x61, 0x3A);
// {0d81ea0d-13bf-44b2-af1c-fcdf6be7927c}
DEFINE_GUID(CLSID_CCustomDrawProgressControl, 0x0d81ea0d, 0x13bf, 0x44B2, 0xAF, 0x1C, 0xFC, 0xDF, 0x6B, 0xE7, 0x92, 0x7C);
// {15756be1-a4ad-449c-b576-df3df0e068d3}
DEFINE_GUID(CLSID_CHyperlinkControl, 0x15756BE1, 0xA4AD, 0x449C, 0xB5, 0x76, 0xDF, 0x3D, 0xF0, 0xE0, 0x68, 0xD3);
// {53a01e9d-61cc-4cb0-83b1-31bc8df63156}
DEFINE_GUID(CLSID_CIconListControl, 0x53A01E9D, 0x61CC, 0x4CB0, 0x83, 0xB1, 0x31, 0xBC, 0x8D, 0xF6, 0x31, 0x56);
// {6A205B57-2567-4a2c-B881-F787FAB579A3}
DEFINE_GUID(CLSID_CInPlaceCalendarControl, 0x6A205B57, 0x2567, 0x4A2C, 0xB8, 0x81, 0xF7, 0x87, 0xFA, 0xB5, 0x79, 0xA3);
// {0EEA25CC-4362-4a12-850B-86EE61B0D3EB}
DEFINE_GUID(CLSID_CInPlaceDropListComboControl, 0x0EEA25CC, 0x4362, 0x4A12, 0x85, 0x0B, 0x86, 0xEE, 0x61, 0xB0, 0xD3, 0xEB);
// {A9CF0EAE-901A-4739-A481-E35B73E47F6D}
DEFINE_GUID(CLSID_CInPlaceEditBoxControl, 0xA9CF0EAE, 0x901A, 0x4739, 0xA4, 0x81, 0xE3, 0x5B, 0x73, 0xE4, 0x7F, 0x6D);
// {8EE97210-FD1F-4b19-91DA-67914005F020}
DEFINE_GUID(CLSID_CInPlaceMLEditBoxControl, 0x8EE97210, 0xFD1F, 0x4B19, 0x91, 0xDA, 0x67, 0x91, 0x40, 0x05, 0xF0, 0x20);
// {8e85d0ce-deaf-4ea1-9410-fd1a2105ceb5}
DEFINE_GUID(CLSID_CInPlaceMultiValuePropertyControl, 0x8E85D0CE, 0xDEAF, 0x4EA1, 0x94, 0x10, 0xFD, 0x1A, 0x21, 0x05, 0xCE, 0xB5);
// {85e94d25-0712-47ed-8cde-b0971177c6a1}
DEFINE_GUID(CLSID_CRatingControl, 0x85e94d25, 0x0712, 0x47ed, 0x8C, 0xDE, 0xB0, 0x97, 0x11, 0x77, 0xC6, 0xA1);
// {527c9a9b-b9a2-44b0-84f9-f0dc11c2bcfb}
DEFINE_GUID(CLSID_CStaticPropertyControl, 0x527C9A9B, 0xB9A2, 0x44B0, 0x84, 0xF9, 0xF0, 0xDC, 0x11, 0xC2, 0xBC, 0xFB);

#undef INTERFACE
#define INTERFACE IOwnerDataCallback
DECLARE_INTERFACE_(IOwnerDataCallback, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    // IOwnerDataCallback
    STDMETHOD(OnDataAvailable)(THIS_ LPARAM lParam, ULONG dwItemCount) PURE;
    STDMETHOD(OnDataUnavailable)(THIS_ LPARAM lParam) PURE;
    STDMETHOD(OnDataChanged)(THIS_ LPARAM lParam, ULONG dwItemCount) PURE;
    STDMETHOD(OnDataReset)(THIS_ LPARAM lParam) PURE;
};

#undef INTERFACE
#define INTERFACE ISubItemCallback
DECLARE_INTERFACE_(ISubItemCallback, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    // ISubItemCallback
    STDMETHOD(GetSubItemTitle)(THIS_ INT subItemIndex, PWSTR pBuffer, INT bufferSize) PURE;
    STDMETHOD(GetSubItemControl)(THIS_ INT itemIndex, INT subItemIndex, REFIID requiredInterface, PPVOID ppObject) PURE;
    STDMETHOD(BeginSubItemEdit)(THIS_ INT itemIndex, INT subItemIndex, INT mode, REFIID requiredInterface, PPVOID ppObject) PURE;
    STDMETHOD(EndSubItemEdit)(THIS_ INT itemIndex, INT subItemIndex, int mode, struct IPropertyControl* pPropertyControl) PURE;
    STDMETHOD(BeginGroupEdit)(THIS_ INT groupIndex, REFIID INT, PPVOID ppObject) PURE;
    STDMETHOD(EndGroupEdit)(THIS_ INT groupIndex, INT mode, struct IPropertyControl* pPropertyControl) PURE;
    STDMETHOD(OnInvokeVerb)(THIS_ INT itemIndex, LPCWSTR pVerb) PURE;
};

#undef INTERFACE
#define INTERFACE IDrawPropertyControl
DECLARE_INTERFACE_(IDrawPropertyControl, IUnknown)
{
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // IPropertyControlBase
    STDMETHOD(Initialize)(IUnknown*, ULONG) PURE; // 2/calendar, 3/textbox
    STDMETHOD(GetSize)(enum PROPCTL_RECT_TYPE, HDC, SIZE const*, SIZE*) PURE;
    STDMETHOD(SetWindowTheme)(PCWSTR, PCWSTR) PURE;
    STDMETHOD(SetFont)(HFONT) PURE;
    STDMETHOD(SetTextColor)(ULONG) PURE;
    STDMETHOD(GetFlags)(INT*) PURE;
    STDMETHOD(SetFlags)(INT, INT) PURE;
    STDMETHOD(AdjustWindowRectPCB)(HWND, RECT*, RECT const*, INT) PURE;
    STDMETHOD(SetValue)(IUnknown*) PURE;
    STDMETHOD(InvokeDefaultAction)(VOID) PURE;
    STDMETHOD(Destroy)(VOID) PURE;
    STDMETHOD(SetFormatFlags)(INT) PURE;
    STDMETHOD(GetFormatFlags)(INT*) PURE;

    // IDrawPropertyControl
    STDMETHOD(GetDrawFlags)(PINT Flags) PURE;
    STDMETHOD(WindowlessDraw)(HDC hDC, RECT pDrawingRectangle, int a) PURE;
    STDMETHOD(HasVisibleContent)(VOID) PURE;
    STDMETHOD(GetDisplayText)(LPWSTR * Text) PURE;
    STDMETHOD(GetTooltipInfo)(HDC, SIZE const*, PINT) PURE;
};

#undef INTERFACE
#define INTERFACE IListView
DECLARE_INTERFACE_(IListView, IUnknown) // real name is IListView2
{
    BEGIN_INTERFACE

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    // IOleWindow
    STDMETHOD(GetWindow)(THIS_ __RPC__in IOleWindow* window, __RPC__deref_out_opt HWND* WindowHandle) PURE;
    STDMETHOD(ContextSensitiveHelp)(THIS_ __RPC__in IOleWindow* window, _In_ BOOL fEnterMode) PURE;
    // IListView
    STDMETHOD(GetImageList)(THIS_ int imageList, HIMAGELIST* pHImageList) PURE;
    STDMETHOD(SetImageList)(THIS_ int imageList, HIMAGELIST hNewImageList, HIMAGELIST* pHOldImageList) PURE;
    STDMETHOD(GetBackgroundColor)(THIS_ COLORREF* pColor) PURE;
    STDMETHOD(SetBackgroundColor)(THIS_ COLORREF color) PURE;
    STDMETHOD(GetTextColor)(THIS_ COLORREF* pColor) PURE;
    STDMETHOD(SetTextColor)(THIS_ COLORREF color) PURE;
    STDMETHOD(GetTextBackgroundColor)(THIS_ COLORREF* pColor) PURE;
    STDMETHOD(SetTextBackgroundColor)(THIS_ COLORREF color) PURE;
    STDMETHOD(GetHotLightColor)(THIS_ COLORREF* pColor) PURE;
    STDMETHOD(SetHotLightColor)(THIS_ COLORREF color) PURE;
    STDMETHOD(GetItemCount)(THIS_ PINT pItemCount) PURE;
    STDMETHOD(SetItemCount)(THIS_ int itemCount, ULONG flags) PURE;
    STDMETHOD(GetItem)(THIS_ LVITEMW* pItem) PURE;
    STDMETHOD(SetItem)(THIS_ LVITEMW* const pItem) PURE;
    STDMETHOD(GetItemState)(THIS_ int itemIndex, int subItemIndex, ULONG mask, ULONG* pState) PURE;
    STDMETHOD(SetItemState)(THIS_ int itemIndex, int subItemIndex, ULONG mask, ULONG state) PURE;
    STDMETHOD(GetItemText)(THIS_ int itemIndex, int subItemIndex, LPWSTR pBuffer, int bufferSize) PURE;
    STDMETHOD(SetItemText)(THIS_ int itemIndex, int subItemIndex, LPCWSTR pText) PURE;
    STDMETHOD(GetBackgroundImage)(THIS_ LVBKIMAGEW* pBkImage) PURE;
    STDMETHOD(SetBackgroundImage)(THIS_ LVBKIMAGEW* const pBkImage) PURE;
    STDMETHOD(GetFocusedColumn)(THIS_ PINT pColumnIndex) PURE;
    STDMETHOD(SetSelectionFlags)(THIS_ ULONG mask, ULONG flags) PURE; // HRESULT SetSelectionFlags (SELECTION_FLAGS, SELECTION_FLAGS);
    STDMETHOD(GetSelectedColumn)(THIS_ PULONG pColumnIndex) PURE;
    STDMETHOD(SetSelectedColumn)(THIS_ ULONG columnIndex) PURE;
    STDMETHOD(GetView)(THIS_ ULONG* pView) PURE;
    STDMETHOD(SetView)(THIS_ ULONG view) PURE;
    STDMETHOD(InsertItem)(THIS_ LVITEMW* const pItem, PULONG pItemIndex) PURE;
    STDMETHOD(DeleteItem)(THIS_ ULONG itemIndex) PURE;
    STDMETHOD(DeleteAllItems)(THIS) PURE;
    STDMETHOD(UpdateItem)(THIS_ ULONG itemIndex) PURE;
    STDMETHOD(GetItemRect)(THIS_ LVITEMINDEX itemIndex, int rectangleType, LPRECT pRectangle) PURE;
    STDMETHOD(GetSubItemRect)(THIS_ LVITEMINDEX itemIndex, int subItemIndex, int rectangleType, LPRECT pRectangle) PURE;
    STDMETHOD(HitTestSubItem)(THIS_ LVHITTESTINFO* pHitTestData) PURE;
    STDMETHOD(GetIncrSearchString)(THIS_ PWSTR pBuffer, int bufferSize, PINT pCopiedChars) PURE;
    STDMETHOD(GetItemSpacing)(THIS_ BOOL smallIconView, PINT pHorizontalSpacing, PINT pVerticalSpacing) PURE;
    STDMETHOD(SetIconSpacing)(THIS_ int horizontalSpacing, int verticalSpacing, PINT pHorizontalSpacing, PINT pVerticalSpacing) PURE;
    STDMETHOD(GetNextItem)(THIS_ LVITEMINDEX itemIndex, ULONG flags, LVITEMINDEX* pNextItemIndex) PURE;
    STDMETHOD(FindItem)(THIS_ LVITEMINDEX startItemIndex, LVFINDINFOW const* pFindInfo, LVITEMINDEX* pFoundItemIndex) PURE;
    STDMETHOD(GetSelectionMark)(THIS_ LVITEMINDEX* pSelectionMark) PURE;
    STDMETHOD(SetSelectionMark)(THIS_ LVITEMINDEX newSelectionMark, LVITEMINDEX* pOldSelectionMark) PURE;
    STDMETHOD(GetItemPosition)(THIS_ LVITEMINDEX itemIndex, POINT* pPosition) PURE;
    STDMETHOD(SetItemPosition)(THIS_ ULONG itemIndex, POINT const* pPosition) PURE;
    STDMETHOD(ScrollView)(THIS_ ULONG horizontalScrollDistance, ULONG verticalScrollDistance) PURE;
    STDMETHOD(EnsureItemVisible)(THIS_ LVITEMINDEX itemIndex, BOOL partialOk) PURE;
    STDMETHOD(EnsureSubItemVisible)(THIS_ LVITEMINDEX itemIndex, ULONG subItemIndex) PURE;
    STDMETHOD(EditSubItem)(THIS_ LVITEMINDEX itemIndex, ULONG subItemIndex) PURE;
    STDMETHOD(RedrawItems)(THIS_ ULONG firstItemIndex, ULONG lastItemIndex) PURE;
    STDMETHOD(ArrangeItems)(THIS_ ULONG mode) PURE;
    STDMETHOD(RecomputeItems)(THIS_ int unknown) PURE;
    STDMETHOD(GetEditControl)(THIS_ HWND* EditWindowHandle) PURE;
    STDMETHOD(EditLabel)(THIS_ LVITEMINDEX itemIndex, LPCWSTR initialEditText, HWND* EditWindowHandle) PURE;
    STDMETHOD(EditGroupLabel)(THIS_ ULONG groupIndex) PURE;
    STDMETHOD(CancelEditLabel)(THIS) PURE;
    STDMETHOD(GetEditItem)(THIS_ LVITEMINDEX* itemIndex, PINT subItemIndex) PURE;
    STDMETHOD(HitTest)(THIS_ LVHITTESTINFO* pHitTestData) PURE;
    STDMETHOD(GetStringWidth)(THIS_ PCWSTR pString, PINT pWidth) PURE;
    STDMETHOD(GetColumn)(THIS_ ULONG columnIndex, LVCOLUMNW* pColumn) PURE;
    STDMETHOD(SetColumn)(THIS_ ULONG columnIndex, LVCOLUMNW* const pColumn) PURE;
    STDMETHOD(GetColumnOrderArray)(THIS_ ULONG numberOfColumns, PINT pColumns) PURE;
    STDMETHOD(SetColumnOrderArray)(THIS_ ULONG numberOfColumns, int const* pColumns) PURE;
    STDMETHOD(GetHeaderControl)(THIS_ HWND* HeaderWindowHandle) PURE;
    STDMETHOD(InsertColumn)(THIS_ ULONG insertAt, LVCOLUMNW* const pColumn, PINT pColumnIndex) PURE;
    STDMETHOD(DeleteColumn)(THIS_ ULONG columnIndex) PURE;
    STDMETHOD(CreateDragImage)(THIS_ ULONG itemIndex, POINT const* pUpperLeft, HIMAGELIST* pHImageList) PURE;
    STDMETHOD(GetViewRect)(THIS_ RECT* pRectangle) PURE;
    STDMETHOD(GetClientRect)(THIS_ BOOL unknown, RECT* pClientRectangle) PURE;
    STDMETHOD(GetColumnWidth)(THIS_ ULONG columnIndex, PINT pWidth) PURE;
    STDMETHOD(SetColumnWidth)(THIS_ ULONG columnIndex, ULONG width) PURE;
    STDMETHOD(GetCallbackMask)(THIS_ ULONG* pMask) PURE;
    STDMETHOD(SetCallbackMask)(THIS_ ULONG mask) PURE;
    STDMETHOD(GetTopIndex)(THIS_ PULONG pTopIndex) PURE;
    STDMETHOD(GetCountPerPage)(THIS_ PULONG pCountPerPage) PURE;
    STDMETHOD(GetOrigin)(THIS_ POINT* pOrigin) PURE;
    STDMETHOD(GetSelectedCount)(THIS_ PULONG pSelectedCount) PURE;
    STDMETHOD(SortItems)(THIS_ BOOL unknown, LPARAM lParam, PFNLVCOMPARE pComparisonFunction) PURE;
    STDMETHOD(GetExtendedStyle)(THIS_ ULONG* pStyle) PURE;
    STDMETHOD(SetExtendedStyle)(THIS_ ULONG mask, ULONG style, ULONG* pOldStyle) PURE;
    STDMETHOD(GetHoverTime)(THIS_ PULONG pTime) PURE;
    STDMETHOD(SetHoverTime)(THIS_ UINT time, PULONG pOldSetting) PURE;
    STDMETHOD(GetToolTip)(THIS_ HWND* ToolTipWindowHandle) PURE;
    STDMETHOD(SetToolTip)(THIS_ HWND ToolTipWindowHandle, HWND* OldToolTipWindowHandle) PURE;
    STDMETHOD(GetHotItem)(THIS_ LVITEMINDEX* pHotItem) PURE;
    STDMETHOD(SetHotItem)(THIS_ LVITEMINDEX newHotItem, LVITEMINDEX* pOldHotItem) PURE;
    STDMETHOD(GetHotCursor)(THIS_ HCURSOR* pHCursor) PURE;
    STDMETHOD(SetHotCursor)(THIS_ HCURSOR hCursor, HCURSOR* pHOldCursor) PURE;
    STDMETHOD(ApproximateViewRect)(THIS_ int itemCount, PINT pWidth, PINT pHeight) PURE;
    STDMETHOD(SetRangeObject)(THIS_ int unknown, LPVOID pObject) PURE;
    STDMETHOD(GetWorkAreas)(THIS_ int numberOfWorkAreas, RECT* pWorkAreas) PURE;
    STDMETHOD(SetWorkAreas)(THIS_ int numberOfWorkAreas, RECT const* pWorkAreas) PURE;
    STDMETHOD(GetWorkAreaCount)(THIS_ PINT pNumberOfWorkAreas) PURE;
    STDMETHOD(ResetEmptyText)(THIS) PURE;
    STDMETHOD(EnableGroupView)(THIS_ BOOL Eable) PURE;
    STDMETHOD(IsGroupViewEnabled)(THIS_ PBOOL IsEnabled) PURE;
    STDMETHOD(SortGroups)(THIS_ PFNLVGROUPCOMPARE pComparisonFunction, PVOID lParam) PURE;
    STDMETHOD(GetGroupInfo)(THIS_ ULONG unknown1, ULONG groupID, LVGROUP* pGroup) PURE;
    STDMETHOD(SetGroupInfo)(THIS_ ULONG unknown, ULONG groupID, LVGROUP* const pGroup) PURE;
    STDMETHOD(GetGroupRect)(THIS_ BOOL unknown, ULONG groupID, ULONG rectangleType, RECT* pRectangle) PURE;
    STDMETHOD(GetGroupState)(THIS_ ULONG groupID, ULONG mask, ULONG* pState) PURE;
    STDMETHOD(HasGroup)(THIS_ INT groupID, BOOL* pHasGroup) PURE;
    STDMETHOD(InsertGroup)(THIS_ INT insertAt, LVGROUP* const pGroup, PINT pGroupID) PURE;
    STDMETHOD(RemoveGroup)(THIS_ INT groupID) PURE;
    STDMETHOD(InsertGroupSorted)(THIS_ LVINSERTGROUPSORTED const* pGroup, PINT pGroupID) PURE;
    STDMETHOD(GetGroupMetrics)(THIS_ LVGROUPMETRICS* pMetrics) PURE;
    STDMETHOD(SetGroupMetrics)(THIS_ LVGROUPMETRICS* const pMetrics) PURE;
    STDMETHOD(RemoveAllGroups)(THIS) PURE;
    STDMETHOD(GetFocusedGroup)(THIS_ PINT pGroupID) PURE;
    STDMETHOD(GetGroupCount)(THIS_ PINT pCount) PURE;
    STDMETHOD(SetOwnerDataCallback)(THIS_ IOwnerDataCallback* pCallback) PURE;
    STDMETHOD(GetTileViewInfo)(THIS_ LVTILEVIEWINFO* pInfo) PURE;
    STDMETHOD(SetTileViewInfo)(THIS_ LVTILEVIEWINFO* const pInfo) PURE;
    STDMETHOD(GetTileInfo)(THIS_ LVTILEINFO* pTileInfo) PURE;
    STDMETHOD(SetTileInfo)(THIS_ LVTILEINFO* const pTileInfo) PURE;
    STDMETHOD(GetInsertMark)(THIS_ LVINSERTMARK* pInsertMarkDetails) PURE;
    STDMETHOD(SetInsertMark)(THIS_ LVINSERTMARK const* pInsertMarkDetails) PURE;
    STDMETHOD(GetInsertMarkRect)(THIS_ LPRECT pInsertMarkRectangle) PURE;
    STDMETHOD(GetInsertMarkColor)(THIS_ COLORREF* pColor) PURE;
    STDMETHOD(SetInsertMarkColor)(THIS_ COLORREF color, COLORREF* pOldColor) PURE;
    STDMETHOD(HitTestInsertMark)(THIS_ POINT const* pPoint, LVINSERTMARK* pInsertMarkDetails) PURE;
    STDMETHOD(SetInfoTip)(THIS_ LVSETINFOTIP* const pInfoTip) PURE;
    STDMETHOD(GetOutlineColor)(THIS_ COLORREF* pColor) PURE;
    STDMETHOD(SetOutlineColor)(THIS_ COLORREF color, COLORREF* pOldColor) PURE;
    STDMETHOD(GetFrozenItem)(THIS_ PINT pItemIndex) PURE;
    STDMETHOD(SetFrozenItem)(THIS_ int unknown1, int unknown2) PURE;
    STDMETHOD(GetFrozenSlot)(THIS_ RECT* pUnknown) PURE;
    STDMETHOD(SetFrozenSlot)(THIS_ int unknown1, POINT const* pUnknown2) PURE;
    STDMETHOD(GetViewMargin)(THIS_ RECT* pMargin) PURE;
    STDMETHOD(SetViewMargin)(THIS_ RECT const* pMargin) PURE;
    STDMETHOD(SetKeyboardSelected)(THIS_ LVITEMINDEX itemIndex) PURE;
    STDMETHOD(MapIndexToId)(THIS_ int itemIndex, PINT pItemID) PURE;
    STDMETHOD(MapIdToIndex)(THIS_ int itemID, PINT pItemIndex) PURE;
    STDMETHOD(IsItemVisible)(THIS_ LVITEMINDEX itemIndex, BOOL* pVisible) PURE;
    STDMETHOD(EnableAlphaShadow)(THIS_ BOOL enable) PURE;
    STDMETHOD(GetGroupSubsetCount)(THIS_ PINT pNumberOfRowsDisplayed) PURE;
    STDMETHOD(SetGroupSubsetCount)(THIS_ int numberOfRowsToDisplay) PURE;
    STDMETHOD(GetVisibleSlotCount)(THIS_ PINT pCount) PURE;
    STDMETHOD(GetColumnMargin)(THIS_ RECT* pMargin) PURE;
    STDMETHOD(SetSubItemCallback)(THIS_ LPVOID pCallback) PURE;
    STDMETHOD(GetVisibleItemRange)(THIS_ LVITEMINDEX* pFirstItem, LVITEMINDEX* pLastItem) PURE;
    STDMETHOD(SetTypeAheadFlags)(THIS_ UINT mask, UINT flags) PURE; // HRESULT SetTypeAheadFlags (TYPEAHEAD_FLAGS, TYPEAHEAD_FLAGS);

    // Windows 10
    STDMETHOD(SetWorkAreasWithDpi)(THIS_ int, struct tagLVWORKAREAWITHDPI const*) PURE;
    STDMETHOD(GetWorkAreasWithDpi)(THIS_ int, struct tagLVWORKAREAWITHDPI*) PURE;
    STDMETHOD(SetWorkAreaImageList)(THIS_ int, int, HIMAGELIST, HIMAGELIST*) PURE;
    STDMETHOD(GetWorkAreaImageList)(THIS_ int, int, HIMAGELIST*) PURE;
    STDMETHOD(EnableIconBullying)(THIS_ INT Mode) PURE;
    STDMETHOD(EnableQuirks)(THIS_ ULONG Flags) PURE;

    END_INTERFACE
};

#define IListViewQueryInterface(This,riid,ppvObject) \
    ((This)->lpVtbl->QueryInterface(This,riid,ppvObject))
#define IListView_AddRef(This) \
    ((This)->lpVtbl->AddRef(This))
#define IListView_Release(This) \
    ((This)->lpVtbl->Release(This))
#define IListView_GetWindow(This, WindowHandle) \
    ((This)->lpVtbl->AddRef(This))
#define IListView_ContextSensitiveHelp(This, fEnterMode) \
    ((This)->lpVtbl->ContextSensitiveHelp(This, fEnterMode))
#define IListView_GetImageList(This, imageList, pHImageList) \
    ((This)->lpVtbl->GetImageList(This, imageList, pHImageList))
#define IListView_SetImageList(This, imageList, hNewImageList, pHOldImageList) \
    ((This)->lpVtbl->SetImageList(This, imageList, hNewImageList, pHOldImageList))
#define IListView_GetBackgroundColor(This, pColor) \
    ((This)->lpVtbl->GetBackgroundColor(This, pColor))
#define IListView_SetBackgroundColor(This, color) \
    ((This)->lpVtbl->SetBackgroundColor(This, color))
#define IListView_GetTextColor(This, pColor) \
    ((This)->lpVtbl->GetTextColor(This, pColor))
#define IListView_SetTextColor(This, color) \
    ((This)->lpVtbl->SetTextColor(This, color))
#define IListView_GetTextBackgroundColor(This, pColor) \
    ((This)->lpVtbl->GetTextBackgroundColor(This, pColor))
#define IListView_SetTextBackgroundColor(This, color) \
    ((This)->lpVtbl->SetTextBackgroundColor(This, color))
#define IListView_GetHotLightColor(This, pColor) \
    ((This)->lpVtbl->GetHotLightColor(This, pColor))
#define IListView_SetHotLightColor(This, color) \
    ((This)->lpVtbl->SetHotLightColor(This, color))
#define IListView_GetItemCount(This, pItemCount) \
    ((This)->lpVtbl->GetItemCount(This, pItemCount))
#define IListView_SetItemCount(This, itemCount, flags) \
    ((This)->lpVtbl->SetItemCount(This, itemCount, flags))
#define IListView_GetItem(This, pItem) \
    ((This)->lpVtbl->GetItem(This, pItem))
#define IListView_SetItem(This, pItem) \
    ((This)->lpVtbl->SetItem(This, pItem))
#define IListView_GetItemState(This, itemIndex, subItemIndex, mask, pState) \
    ((This)->lpVtbl->GetItemState(This, itemIndex, subItemIndex, mask, pState))
#define IListView_SetItemState(This, itemIndex, subItemIndex, mask, state) \
    ((This)->lpVtbl->SetItemState(This, itemIndex, subItemIndex, mask, state))
#define IListView_GetItemText(This, itemIndex, subItemIndex, pBuffer, bufferSize) \
    ((This)->lpVtbl->GetItemText(This, itemIndex, subItemIndex, pBuffer, bufferSize))
#define IListView_SetItemText(This, itemIndex, subItemIndex, pText) \
    ((This)->lpVtbl->SetItemText(This, itemIndex, subItemIndex, pText))
#define IListView_GetBackgroundImage(This, pBkImage) \
    ((This)->lpVtbl->GetBackgroundImage(This, pBkImage))
#define IListView_SetBackgroundImage(This, pBkImage) \
    ((This)->lpVtbl->SetBackgroundImage(This, pBkImage))
#define IListView_GetFocusedColumn(This, pColumnIndex) \
    ((This)->lpVtbl->GetFocusedColumn(This, pColumnIndex))
#define IListView_SetSelectionFlags(This, mask, flags) \
    ((This)->lpVtbl->SetSelectionFlags(This, mask, flags))
#define IListView_GetSelectedColumn(This, pColumnIndex) \
    ((This)->lpVtbl->GetSelectedColumn(This, pColumnIndex))
#define IListView_SetSelectedColumn(This, columnIndex) \
    ((This)->lpVtbl->SetSelectedColumn(This, columnIndex))
#define IListView_GetView(This, pView) \
    ((This)->lpVtbl->GetView(This, pView))
#define IListView_SetView(This, view) \
    ((This)->lpVtbl->SetView(This, view))
#define IListView_InsertItem(This, pItem, pItemIndex) \
    ((This)->lpVtbl->InsertItem(This, pItem, pItemIndex))
#define IListView_DeleteItem(This, itemIndex) \
    ((This)->lpVtbl->DeleteItem(This, itemIndex))
#define IListView_DeleteAllItems(This) \
    ((This)->lpVtbl->DeleteAllItems(This))
#define IListView_UpdateItem(This, itemIndex) \
    ((This)->lpVtbl->UpdateItem(This, itemIndex))
#define IListView_GetItemRect(This, itemIndex, rectangleType, pRectangle) \
    ((This)->lpVtbl->GetItemRect(This, itemIndex, rectangleType, pRectangle))
#define IListView_GetSubItemRect(This, itemIndex, subItemIndex, rectangleType, pRectangle) \
    ((This)->lpVtbl->GetSubItemRect(This, itemIndex, subItemIndex, rectangleType, pRectangle))
#define IListView_HitTestSubItem(This, pHitTestData) \
    ((This)->lpVtbl->HitTestSubItem(This, pHitTestData))
#define IListView_GetIncrSearchString(This, pBuffer, bufferSize, pCopiedChars) \
    ((This)->lpVtbl->GetIncrSearchString(This, pBuffer, bufferSize, pCopiedChars))
#define IListView_GetItemSpacing(This, smallIconView, pHorizontalSpacing, pVerticalSpacing) \
    ((This)->lpVtbl->GetItemSpacing(This, smallIconView, pHorizontalSpacing, pVerticalSpacing))
#define IListView_SetIconSpacing(This, horizontalSpacing, verticalSpacing, pHorizontalSpacing, pVerticalSpacing) \
    ((This)->lpVtbl->SetIconSpacing(This, horizontalSpacing, verticalSpacing, pHorizontalSpacing, pVerticalSpacing))
#define IListView_GetNextItem(This, itemIndex, flags, pNextItemIndex) \
    ((This)->lpVtbl->GetNextItem(This, itemIndex, flags, pNextItemIndex))
#define IListView_FindItem(This, startItemIndex, pFindInfo, pFoundItemIndex) \
    ((This)->lpVtbl->FindItem(This, startItemIndex, pFindInfo, pFoundItemIndex))
#define IListView_GetSelectionMark(This, pSelectionMark) \
    ((This)->lpVtbl->GetSelectionMark(This, pSelectionMark))
#define IListView_SetSelectionMark(This, newSelectionMark, pOldSelectionMark) \
    ((This)->lpVtbl->SetSelectionMark(This, newSelectionMark, pOldSelectionMark))
#define IListView_GetItemPosition(This, itemIndex, pPosition) \
    ((This)->lpVtbl->GetItemPosition(This, itemIndex, pPosition))
#define IListView_SetItemPosition(This, itemIndex, pPosition) \
    ((This)->lpVtbl->SetItemPosition(This, itemIndex, pPosition))
#define IListView_ScrollView(This, horizontalScrollDistance, verticalScrollDistance) \
    ((This)->lpVtbl->ScrollView(This, horizontalScrollDistance, verticalScrollDistance))
#define IListView_EnsureItemVisible(This, itemIndex, partialOk) \
    ((This)->lpVtbl->EnsureItemVisible(This, itemIndex, partialOk))
#define IListView_EnsureSubItemVisible(This, itemIndex, subItemIndex) \
    ((This)->lpVtbl->EnsureSubItemVisible(This, itemIndex, subItemIndex))
#define IListView_EditSubItem(This, itemIndex, subItemIndex) \
    ((This)->lpVtbl->EditSubItem(This, itemIndex, subItemIndex))
#define IListView_RedrawItems(This, firstItemIndex, lastItemIndex) \
    ((This)->lpVtbl->RedrawItems(This, firstItemIndex, lastItemIndex))
#define IListView_ArrangeItems(This, mode) \
    ((This)->lpVtbl->ArrangeItems(This, mode))
#define IListView_RecomputeItems(This, unknown) \
    ((This)->lpVtbl->RecomputeItems(This, unknown))
#define IListView_GetEditControl(This, EditWindowHandle) \
    ((This)->lpVtbl->GetEditControl(This, EditWindowHandle))
#define IListView_EditLabel(This, itemIndex, initialEditText, EditWindowHandle) \
    ((This)->lpVtbl->EditLabel(This, itemIndex, initialEditText, EditWindowHandle))
#define IListView_EditGroupLabel(This, groupIndex) \
    ((This)->lpVtbl->EditGroupLabel(This, groupIndex))
#define IListView_CancelEditLabel(This) \
    ((This)->lpVtbl->CancelEditLabel(This))
#define IListView_GetEditItem(This, itemIndex, subItemIndex) \
    ((This)->lpVtbl->GetEditItem(This, itemIndex, subItemIndex))
#define IListView_HitTest(This, pHitTestData) \
    ((This)->lpVtbl->HitTest(This, pHitTestData))
#define IListView_GetStringWidth(This, pString, pWidth) \
    ((This)->lpVtbl->GetStringWidth(This, pString, pWidth))
#define IListView_GetColumn(This, columnIndex, pColumn) \
    ((This)->lpVtbl->GetColumn(This, columnIndex, pColumn))
#define IListView_SetColumn(This, columnIndex, pColumn) \
    ((This)->lpVtbl->SetColumn(This, columnIndex, pColumn))
#define IListView_GetColumnOrderArray(This, numberOfColumns, pColumns) \
    ((This)->lpVtbl->GetColumnOrderArray(This, numberOfColumns, pColumns))
#define IListView_SetColumnOrderArray(This, numberOfColumns, pColumns) \
    ((This)->lpVtbl->SetColumnOrderArray(This, numberOfColumns, pColumns))
#define IListView_GetHeaderControl(This, HeaderWindowHandle) \
    ((This)->lpVtbl->GetHeaderControl(This, HeaderWindowHandle))
#define IListView_InsertColumn(This, insertAt, pColumn, pColumnIndex) \
    ((This)->lpVtbl->InsertColumn(This, insertAt, pColumn, pColumnIndex))
#define IListView_DeleteColumn(This, columnIndex) \
    ((This)->lpVtbl->DeleteColumn(This, columnIndex))
#define IListView_CreateDragImage(This, itemIndex, pUpperLeft, pHImageList) \
    ((This)->lpVtbl->CreateDragImage(This, itemIndex, pUpperLeft, pHImageList))
#define IListView_GetViewRect(This, pRectangle) \
    ((This)->lpVtbl->GetViewRect(This, pRectangle))
#define IListView_GetClientRect(This, unknown, pClientRectangle) \
    ((This)->lpVtbl->GetClientRect(This, unknown, pClientRectangle))
#define IListView_GetColumnWidth(This, columnIndex, pWidth) \
    ((This)->lpVtbl->GetColumnWidth(This, columnIndex, pWidth))
#define IListView_SetColumnWidth(This, columnIndex, width) \
    ((This)->lpVtbl->SetColumnWidth(This, columnIndex, width))
#define IListView_GetCallbackMask(This, pMask) \
    ((This)->lpVtbl->GetCallbackMask(This, pMask))
#define IListView_SetCallbackMask(This, mask) \
    ((This)->lpVtbl->SetCallbackMask(This, mask))
#define IListView_GetTopIndex(This, pTopIndex) \
    ((This)->lpVtbl->GetTopIndex(This, pTopIndex))
#define IListView_GetCountPerPage(This, pCountPerPage) \
    ((This)->lpVtbl->GetCountPerPage(This, pCountPerPage))
#define IListView_GetOrigin(This, pOrigin) \
    ((This)->lpVtbl->GetOrigin(This, pOrigin))
#define IListView_GetSelectedCount(This, pSelectedCount) \
    ((This)->lpVtbl->GetSelectedCount(This, pSelectedCount))
#define IListView_SortItems(This, unknown, lParam, pComparisonFunction) \
    ((This)->lpVtbl->SortItems(This, unknown, lParam, pComparisonFunction))
#define IListView_GetExtendedStyle(This, pStyle) \
    ((This)->lpVtbl->GetExtendedStyle(This, pStyle))
#define IListView_SetExtendedStyle(This, mask, style, pOldStyle) \
    ((This)->lpVtbl->SetExtendedStyle(This, mask, style, pOldStyle))
#define IListView_GetHoverTime(This, pTime) \
    ((This)->lpVtbl->GetHoverTime(This, pTime))
#define IListView_SetHoverTime(This, time, pOldSetting) \
    ((This)->lpVtbl->SetHoverTime(This, time, pOldSetting))
#define IListView_GetToolTip(This, ToolTipWindowHandle) \
    ((This)->lpVtbl->GetToolTip(This, ToolTipWindowHandle))
#define IListView_SetToolTip(This, ToolTipWindowHandle, OldToolTipWindowHandle) \
    ((This)->lpVtbl->SetToolTip(This, ToolTipWindowHandle, OldToolTipWindowHandle))
#define IListView_GetHotItem(This, pHotItem) \
    ((This)->lpVtbl->GetHotItem(This, pHotItem))
#define IListView_SetHotItem(This, newHotItem, pOldHotItem) \
    ((This)->lpVtbl->SetHotItem(This, newHotItem, pOldHotItem))
#define IListView_GetHotCursor(This, pHCursor) \
    ((This)->lpVtbl->GetHotCursor(This, pHCursor))
#define IListView_SetHotCursor(This, hCursor, pHOldCursor) \
    ((This)->lpVtbl->SetHotCursor(This, hCursor, pHOldCursor))
#define IListView_ApproximateViewRect(This, itemCount, pWidth, pHeight) \
    ((This)->lpVtbl->ApproximateViewRect(This, itemCount, pWidth, pHeight))
#define IListView_SetRangeObject(This, unknown, pObject) \
    ((This)->lpVtbl->SetRangeObject(This, unknown, pObject))
#define IListView_GetWorkAreas(This, numberOfWorkAreas, pWorkAreas) \
    ((This)->lpVtbl->GetWorkAreas(This, numberOfWorkAreas, pWorkAreas))
#define IListView_SetWorkAreas(This, numberOfWorkAreas, pWorkAreas) \
    ((This)->lpVtbl->SetWorkAreas(This, numberOfWorkAreas, pWorkAreas))
#define IListView_GetWorkAreaCount(This, pNumberOfWorkAreas) \
    ((This)->lpVtbl->GetWorkAreaCount(This, pNumberOfWorkAreas))
#define IListView_ResetEmptyText(This) \
    ((This)->lpVtbl->ResetEmptyText(This))
#define IListView_EnableGroupView(This, enable) \
    ((This)->lpVtbl->EnableGroupView(This, enable))
#define IListView_IsGroupViewEnabled(This, pIsEnabled) \
    ((This)->lpVtbl->IsGroupViewEnabled(This, pIsEnabled))
#define IListView_SortGroups(This, pComparisonFunction, lParam) \
    ((This)->lpVtbl->SortGroups(This, pComparisonFunction, lParam))
#define IListView_GetGroupInfo(This, unknown1, unknown2, pGroup) \
    ((This)->lpVtbl->GetGroupInfo(This, unknown1, unknown2, pGroup))
#define IListView_SetGroupInfo(This, unknown, groupID, pGroup) \
    ((This)->lpVtbl->SetGroupInfo(This, unknown, groupID, pGroup))
#define IListView_GetGroupRect(This, unknown, groupID, rectangleType, pRectangle) \
    ((This)->lpVtbl->GetGroupRect(This, unknown, groupID, rectangleType, pRectangle))
#define IListView_GetGroupState(This, groupID, mask, pState) \
    ((This)->lpVtbl->GetGroupState(This, groupID, mask, pState))
#define IListView_HasGroup(This, groupID, pHasGroup) \
    ((This)->lpVtbl->HasGroup(This, groupID, pHasGroup))
#define IListView_InsertGroup(This, insertAt, pGroup, pGroupID) \
    ((This)->lpVtbl->InsertGroup(This, insertAt, pGroup, pGroupID))
#define IListView_RemoveGroup(This, groupID) \
    ((This)->lpVtbl->RemoveGroup(This, groupID))
#define IListView_InsertGroupSorted(This, pGroup, pGroupID) \
    ((This)->lpVtbl->InsertGroupSorted(This, pGroup, pGroupID))
#define IListView_GetGroupMetrics(This, pMetrics) \
    ((This)->lpVtbl->GetGroupMetrics(This, pMetrics))
#define IListView_SetGroupMetrics(This, pMetrics) \
    ((This)->lpVtbl->SetGroupMetrics(This, pMetrics))
#define IListView_RemoveAllGroups(This) \
    ((This)->lpVtbl->RemoveAllGroups(This))
#define IListView_GetFocusedGroup(This, pGroupID) \
    ((This)->lpVtbl->GetFocusedGroup(This, pGroupID))
#define IListView_GetGroupCount(This, pCount) \
    ((This)->lpVtbl->GetGroupCount(This, pCount))
#define IListView_SetOwnerDataCallback(This, pCallback) \
    ((This)->lpVtbl->SetOwnerDataCallback(This, pCallback))
#define IListView_GetTileViewInfo(This, pInfo) \
    ((This)->lpVtbl->GetTileViewInfo(This, pInfo))
#define IListView_SetTileViewInfo(This, pInfo) \
    ((This)->lpVtbl->SetTileViewInfo(This, pInfo))
#define IListView_GetTileInfo(This, pTileInfo) \
    ((This)->lpVtbl->GetTileInfo(This, pTileInfo))
#define IListView_SetTileInfo(This, pTileInfo) \
    ((This)->lpVtbl->SetTileInfo(This, pTileInfo))
#define IListView_GetInsertMark(This, pInsertMarkDetails) \
    ((This)->lpVtbl->GetInsertMark(This, pInsertMarkDetails))
#define IListView_SetInsertMark(This, pInsertMarkDetails) \
    ((This)->lpVtbl->SetInsertMark(This, pInsertMarkDetails))
#define IListView_GetInsertMarkRect(This, pInsertMarkRectangle) \
    ((This)->lpVtbl->GetInsertMarkRect(This, pInsertMarkRectangle))
#define IListView_GetInsertMarkColor(This, pColor) \
    ((This)->lpVtbl->GetInsertMarkColor(This, pColor))
#define IListView_SetInsertMarkColor(This, color, pOldColor) \
    ((This)->lpVtbl->SetInsertMarkColor(This, color, pOldColor))
#define IListView_HitTestInsertMark(This, pPoint, pInsertMarkDetails) \
    ((This)->lpVtbl->HitTestInsertMark(This, pPoint, pInsertMarkDetails))
#define IListView_SetInfoTip(This, pInfoTip) \
    ((This)->lpVtbl->SetInfoTip(This, pInfoTip))
#define IListView_GetOutlineColor(This, pColor) \
    ((This)->lpVtbl->GetOutlineColor(This, pColor))
#define IListView_SetOutlineColor(This, color, pOldColor) \
    ((This)->lpVtbl->SetOutlineColor(This, color, pOldColor))
#define IListView_GetFrozenItem(This, pItemIndex) \
    ((This)->lpVtbl->GetFrozenItem(This, pItemIndex))
#define IListView_SetFrozenItem(This, unknown1, unknown2) \
    ((This)->lpVtbl->SetFrozenItem(This, unknown1, unknown2))
#define IListView_GetFrozenSlot(This, pUnknown) \
    ((This)->lpVtbl->GetFrozenSlot(This, pUnknown))
#define IListView_SetFrozenSlot(This, unknown1, pUnknown2) \
    ((This)->lpVtbl->SetFrozenSlot(This, unknown1, pUnknown2))
#define IListView_GetViewMargin(This, pMargin) \
    ((This)->lpVtbl->GetViewMargin(This, pMargin))
#define IListView_SetViewMargin(This, pMargin) \
    ((This)->lpVtbl->SetViewMargin(This, pMargin))
#define IListView_SetKeyboardSelected(This, itemIndex) \
    ((This)->lpVtbl->SetKeyboardSelected(This, itemIndex))
#define IListView_MapIndexToId(This, itemIndex, pItemID) \
    ((This)->lpVtbl->MapIndexToId(This, itemIndex, pItemID))
#define IListView_MapIdToIndex(This, itemID, pItemIndex) \
    ((This)->lpVtbl->MapIdToIndex(This, itemID, pItemIndex))
#define IListView_IsItemVisible(This, itemIndex, pVisible) \
    ((This)->lpVtbl->IsItemVisible(This, itemIndex, pVisible))
#define IListView_EnableAlphaShadow(This, enable) \
    ((This)->lpVtbl->EnableAlphaShadow(This, enable))
#define IListView_GetGroupSubsetCount(This, pNumberOfRowsDisplayed) \
    ((This)->lpVtbl->GetGroupSubsetCount(This, pNumberOfRowsDisplayed))
#define IListView_SetGroupSubsetCount(This, numberOfRowsToDisplay) \
    ((This)->lpVtbl->SetGroupSubsetCount(This, numberOfRowsToDisplay))
#define IListView_GetVisibleSlotCount(This, pCount) \
    ((This)->lpVtbl->GetVisibleSlotCount(This, pCount))
#define IListView_GetColumnMargin(This, pMargin) \
    ((This)->lpVtbl->GetColumnMargin(This, pMargin))
#define IListView_SetSubItemCallback(This, pCallback) \
    ((This)->lpVtbl->SetSubItemCallback(This, pCallback))
#define IListView_GetVisibleItemRange(This, pFirstItem, pLastItem) \
    ((This)->lpVtbl->GetVisibleItemRange(This, pFirstItem, pLastItem))
#define IListView_SetTypeAheadFlags(This, mask, flags) \
    ((This)->lpVtbl->SetTypeAheadFlags(This, mask, flags))

EXTERN_C_END

#endif
