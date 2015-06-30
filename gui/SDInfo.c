/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.20                          *
*        Compiled Mar 19 2013, 15:01:00                              *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "includes.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0  (GUI_ID_USER + 0x00)
#define ID_TEXT_0    (GUI_ID_USER + 0x01)
#define ID_TEXT_1    (GUI_ID_USER + 0x02)
#define ID_TEXT_2    (GUI_ID_USER + 0x03)
//#define ID_TEXT_3    (GUI_ID_USER + 0x04)
//#define ID_TEXT_4    (GUI_ID_USER + 0x05)
//#define ID_TEXT_5    (GUI_ID_USER + 0x06)
//#define ID_TEXT_6    (GUI_ID_USER + 0x07)


#define ID_EDIT_0    (GUI_ID_USER + 0x08)
#define ID_EDIT_1    (GUI_ID_USER + 0x09)
//#define ID_EDIT_2    (GUI_ID_USER + 0x0A)
//#define ID_EDIT_3    (GUI_ID_USER + 0x0B)

//#define ID_BUTTON_0  (GUI_ID_USER + 0x0C)
#define ID_BUTTON_1  (GUI_ID_USER + 0x0D)
#define ID_BUTTON_2  (GUI_ID_USER + 0x0E)
#define ID_BUTTON_3  (GUI_ID_USER + 0x0F)


#define ID_PROGBAR_0 (GUI_ID_USER + 0x10)
#define ID_PROGBAR_1 (GUI_ID_USER + 0x11)



// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect,   "MemManage",  ID_WINDOW_0,  0,   0,   240, 295,0, 0x0,  0 },
  { TEXT_CreateIndirect,     MemSize,      ID_TEXT_0,    12,  16,  59,  20, 0, 0x0,  0 },
  { TEXT_CreateIndirect,     MemUsage,     ID_TEXT_1,    12,  79,  80,  20, 0, 0x0,  0 },
  { TEXT_CreateIndirect,     FileNum,      ID_TEXT_2,    12,  47,  80,  20, 0, 0x0,  0 },
  //{ TEXT_CreateIndirect,     FactorySet,   ID_TEXT_3,    12,  148, 108, 20, 0, 0x0,  0 },
  //{ TEXT_CreateIndirect,     VersionNum,   ID_TEXT_4,    12,  187, 200, 20, 0, 0x0,  0 },
  //{ TEXT_CreateIndirect,     MM_batteryVtg,    ID_TEXT_5,    12,  113, 180, 20, 0, 0x0,  0 },
  //{ TEXT_CreateIndirect,     "new",        ID_TEXT_5,    12,  187, 200, 20, 0, 0x0,  0 },
    
  { EDIT_CreateIndirect,     "Edit",       ID_EDIT_0,    120, 12,  115, 20, EDIT_CF_HCENTER, 0x64, 0 },
  { EDIT_CreateIndirect,     "Edit",       ID_EDIT_1,    120, 43,  115, 20, EDIT_CF_HCENTER, 0x64, 0 },
  //{ EDIT_CreateIndirect,     "Edit",       ID_EDIT_2,    120, 111, 115, 20, 0, 0x64, 0},
    
  { PROGBAR_CreateIndirect,  "Progbar",    ID_PROGBAR_0, 120, 77, 115, 20, 0, 0x0,  0 },
  //{ BUTTON_CreateIndirect,   "F1",         ID_BUTTON_0,  120, 143, 115, 25, 0, 0x0,  0 },
  { BUTTON_CreateIndirect,   MemFormat,    ID_BUTTON_1,  10,  260, 65,  25, 0, 0x0,  0 },
  { BUTTON_CreateIndirect,   Quit,         ID_BUTTON_2,  165, 260, 65,  25, 0, 0x0,  0 },
  { PROGBAR_CreateIndirect,  "Progbar",    ID_PROGBAR_1, 9,   228, 222, 20, 0, 0x0,  0 },
    
  // USER START (Optionally insert additional widgets)
  // USER END
};


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
WM_HWIN GUI_Get_FD_Usage_PROGBAR()
{    
     return WM_GetDialogItem(g_hWin_SDInfo, ID_PROGBAR_0);            
}

void GUI_Set_FD_Format_PROGBAR(u32 val)
{
    WM_HWIN hItem;

    
    hItem = WM_GetDialogItem(g_hWin_SDInfo, ID_PROGBAR_1);  
    
    if(WM_HWIN_NULL != hItem)
    {
        PROGBAR_SetValue(hItem, val);              
    }
}

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) 
{
      WM_HWIN hItem;
      int     NCode;
      int     Id;
      u8    sbuf[64];

      switch (pMsg->MsgId) 
      {
          case WM_INIT_DIALOG:
            get_sd_info();
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
            sprintf(sbuf, "%dMB", (g_sys_ctrl.sd_total_capacity/1024));
            EDIT_SetText(hItem, sbuf);
            
            //WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
            WM_DisableWindow(hItem);
            
            hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
            g_sys_ctrl.sysFileNum = get_file_num();
            sprintf(sbuf, "%d", g_sys_ctrl.sysFileNum);
            EDIT_SetText(hItem, sbuf);
            //EDIT_SetText(hItem,"1");
            //scan_files("/");
            //EDIT_SetDecMode(hItem,g_sys_ctrl.FileNumber,0,9999,0,0);
            //EDIT_SetValue(hItem,g_sys_ctrl.FileNumber);
            //WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
            WM_DisableWindow(hItem);

#if 0
            hItem = WM_GetDialogItem(pMsg->hWin,ID_EDIT_2);
            WM_DisableWindow(hItem);
            EDIT_SetFloatMode(hItem,((g_sys_ctrl.pwrValue*3.3)/4096),0,99999,2,
                                     GUI_EDIT_SUPPRESS_LEADING_ZEROES);
            EDIT_SetFloatValue(hItem,(g_sys_ctrl.pwrValue*3.3)/4096);
            //WM_CF_SHOW
#endif
            hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
            PROGBAR_SetBarColor(hItem, 0, GUI_GREEN);
            NCode = (100*g_sys_ctrl.sd_free_capacity)/g_sys_ctrl.sd_total_capacity;
            NCode %= 100;
            NCode = 100-NCode;
            PROGBAR_SetValue(hItem, NCode);
            //sprintf(sbuf, "%dMbytes", (g_sys_ctrl.sd_total_capacity/1024));
            
            hItem=WM_GetDialogItem(pMsg->hWin,ID_BUTTON_1);
            BUTTON_SetBkColor(hItem,0,GUI_GREEN);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
            
            hItem=WM_GetDialogItem(pMsg->hWin,ID_BUTTON_2);
            BUTTON_SetBkColor(hItem,0,GUI_YELLOW);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
#if 0
            hItem=WM_GetDialogItem(pMsg->hWin,ID_BUTTON_0);
            BUTTON_SetBkColor(hItem,0,GUI_CYAN);
            WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
#endif
            //hItem = WM_GetDialogItem(pMsg->hWin,ID_PROGBAR_0);

            hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_1); 
            PROGBAR_SetBarColor(hItem, 0, GUI_GREEN);
            //PROGBAR_SetValue(hItem, 100);
            break;
          case WM_KEY:
            
            if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==1)
            {
                switch(((WM_KEY_INFO *)(pMsg->Data.p))->Key)
                {
                    case GUI_KEY_GREEN:
                        //SYS_ADD_TASK(SYS_TASK_FORMAT_DISK);
                        ERR_NOTE(g_hWin_SDInfo, GUI_MSBOX_FORMAT_ERROR);//确认格式化�
                        break;
                    case GUI_KEY_YELLOW:
                        WM_DeleteWindow(g_hWin_SDInfo);
                        g_hWin_SDInfo = HBWIN_NULL;
                        WM_SetFocus(g_hWin_SysInfo);
                        break;
                    case GUI_KEY_F1:
                        break;
                }
            }   
                
            break;
          default:
            WM_DefaultProc(pMsg);
            break;
      }
}

/*********************************************************************
*
*       Public code
*SDInfo
**********************************************************************
*/
/*********************************************************************
*
*       CreateMemManage
*/
WM_HWIN CreateSDInfo(void);
WM_HWIN CreateSDInfo(void) {
  WM_HWIN hWin;
  //WM_HWIN hTimer;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, g_hWin_SysInfo, 0, 0);
  //hTimer = WM_CreateTimer(g_hWin_mem, 0, 2000, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
