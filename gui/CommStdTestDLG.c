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
#define ID_WINDOW_0 (GUI_ID_USER + 0x07)
#define ID_BUTTON_0 (GUI_ID_USER + 0x08)
#define ID_BUTTON_1 (GUI_ID_USER + 0x09)
#define ID_BUTTON_2 (GUI_ID_USER + 0x0A)
#define ID_BUTTON_3 (GUI_ID_USER + 0x0B)
#define ID_BUTTON_4 (GUI_ID_USER + 0x0C)
#define ID_BUTTON_5 (GUI_ID_USER + 0x0D)


#define ID_TEXT_0 (GUI_ID_USER + 0x0E)
#define ID_TEXT_1 (GUI_ID_USER + 0x0F)
#define ID_TEXT_2 (GUI_ID_USER + 0x10)
#define ID_TEXT_3 (GUI_ID_USER + 0x11)
#define ID_TEXT_4 (GUI_ID_USER + 0x12)
#define ID_TEXT_5 (GUI_ID_USER + 0x13)

#define ID_EDIT_0 (GUI_ID_USER + 0x14)
#define ID_EDIT_1 (GUI_ID_USER + 0x15)
#define ID_EDIT_2 (GUI_ID_USER + 0x16)
#define ID_EDIT_3 (GUI_ID_USER + 0x17)
#define ID_EDIT_4 (GUI_ID_USER + 0x18)
#define ID_EDIT_5 (GUI_ID_USER + 0x19)

#define ID_PROGBAR_0 (GUI_ID_USER + 0x1A)



/*********************************************************************
*
*       _aDialogCreate
*/


static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "cps",      ID_WINDOW_0,  0,   0,   240, 295, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, RoutTab,    ID_BUTTON_0,  6,   8,  80,  20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, DataSignBtn,ID_BUTTON_1,  151, 8,  80,  20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, Send,       ID_BUTTON_2,  6,   267, 55,  25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, Msg,        ID_BUTTON_3,  80,  267, 80,  25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, Quit,       ID_BUTTON_4,  178, 266, 55,  25, 0, 0x0, 0 },

  { TEXT_CreateIndirect, Speed ,       ID_TEXT_0,    8,   47,  80,  20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, TarAddr,      ID_TEXT_1,    8,   79,  110, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, CtlCode,      ID_TEXT_2,    8,   108, 110, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, DataSign,     ID_TEXT_3,    8,   139, 110, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, Length,       ID_TEXT_4,    8,   171, 110, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, DataField,    ID_TEXT_5,    8,   195, 110, 20, 0, 0x0, 0 },

  { EDIT_CreateIndirect, "Edit",       ID_EDIT_0,    100, 45,  133, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit",       ID_EDIT_1,    100, 76,  133, 20, 0, 0x64, 0 }, 
  { EDIT_CreateIndirect, "Edit",       ID_EDIT_2,    100, 106, 133, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit",       ID_EDIT_3,    100, 136, 133, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit",       ID_EDIT_4,    100, 167, 133, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit",       ID_EDIT_5,    100, 195, 133, 20, 0, 0x64, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 12, 231, 216, 20, 0, 0x0, 0 },

};  


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
//static char std_Edit1_Text[8]; //edit文本字符串
//static int  std_Edit1_Value;

//static char std_Edit3_Text[32]; //edit文本字符串
//static int  std_Edit3_Value;


static int cpt_key_press_cnt=0;

u8 GUI_char2hex(u8 ch);

u8 GUI_char2hex(u8 ch)
{
    if((ch >= '0') && (ch <= '9'))
    {
        return (ch-'0');
    }
    if((ch >= 'a') && (ch <= 'f'))
    {
        return ((ch-'a')+10);
    }
    if((ch >= 'A') && (ch <= 'F'))
    {
        return ((ch-'A')+10);
    }
    return 0xff;
}


WM_HWIN STM_Get_PROGBAR()
{    
     return WM_GetDialogItem(g_hWin_std, ID_PROGBAR_0);            
}

void STM_Print_resp_data(u8 * src, u8 * send_ptr, u8 len)
{
    u8 i;
    for(i = 0; i < len; i++)
    {
        *send_ptr++ = GUI_Hex2Char( src[i]>>4);
        *send_ptr++ = GUI_Hex2Char( src[i]&0x0f);
        //*send_ptr++ = ' ';
    }
    *send_ptr++ = 0;
}



void STM_proc_resp_data(void)
{
    WM_HWIN hItem;
    u8 * pbuf, temb[32];
    u32 len;

    pbuf = g_proto_para.data_buf;
    len = g_proto_para.data_len;

    if(g_hWin_std != WM_HWIN_NULL)
    {   
        if(6==len)
        {
            hItem = WM_GetDialogItem(g_hWin_std, ID_EDIT_1);
            //sprintf(temb, "%d", pbuf);
            //STM_Print_resp_data(pbuf,temb, len);

            EDIT_SetText(hItem, 
                (const char*)GUI_hex2MeterAddrStr(pbuf, len));
        }
        //EDIT_SetText(hItem, temb);
        
        //SWITCH(DATA FLAG)
        if(len)
        {
            if(len > 8)
            {
                len = 8;
            }
            hItem = WM_GetDialogItem(g_hWin_std, ID_EDIT_5);
            EDIT_SetText(hItem, 
            (const char*)GUI_hex2MeterAddrStr(pbuf, len));
            //STM_Print_resp_data(pbuf,temb, len);      
            //EDIT_SetText(hItem, temb);           
        }                            
    }
}

static u32 Get_Para_From_Widget(WM_MESSAGE * pMsg)
{
    u8  i, tb[GUI_645_ADDR_LENGTH+2], len;
    WM_HWIN hItem;
    WM_HWIN hWin;
    //u8 addr[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
 
    int dropdown_num;
    
    hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_1);
    EDIT_GetText(hItem, tb, GUI_645_ADDR_LENGTH+1);
    
    //GUI_GetStrDataFlag(tb , GUI_645_ADDR_LENGTH);

    if(strlen(tb) != GUI_645_ADDR_LENGTH)
    {
        ERR_NOTE(g_hWin_std,GUI_MSBOX_ADDR_ERROR);
        return DEV_ERROR;
    }
    
    //if(0x13 == g_gui_para.ctlCode)
    //{
      //  memcpy(g_gui_para.dstAddr, addr, sizeof(addr));
    //}
    if(DEV_OK != GUI_GetMeterAddr(tb, g_gui_para.dstAddr))
    {
        ERR_NOTE(g_hWin_std,GUI_MSBOX_ADDR_ERROR);
        return DEV_ERROR;
    }    
    //g_rom_para.plcProtocol = DL_T_07;


    hItem = WM_GetDialogItem(pMsg->hWin,ID_EDIT_3);
    //g_gui_para.g_datasign = EDIT_GetValue(pMsg->hWin);
    EDIT_GetText(hItem, tb, 8 + 1);

    if(g_rom_para.plcProtocol == DL_T_07)
        len = DL645_07_DATA_ITEM_LEN;
    else
        len = DL645_97_DATA_ITEM_LEN;
    
    if(strlen(tb) != (len<<1))
    {       
        ERR_NOTE(g_hWin_std,GUI_MSBOX_DIDO_ERROR);
        
        //g_hWin_Err=CreateErrNote(g_hWin_std);
        return DEV_ERROR;
    }

    if(DEV_OK != GUI_GetStrDataFlag(tb, g_rom_para.plcProtocol ))
    {
        ERR_NOTE(g_hWin_std,GUI_MSBOX_DIDO_ERROR);
        
        //g_hWin_Err=CreateErrNote(g_hWin_std);
        return DEV_ERROR;
    }
    

    hItem = WM_GetDialogItem(pMsg->hWin,ID_EDIT_4);/*长度*/
    EDIT_GetText(hItem,tb,4);

    //if(0x13 == g_gui_para.ctlCode)
    //{
        //g_gui_para.dataLen = 0;
    //}
    //else
    //{
    g_gui_para.dataLen = atoi(tb);
    //}
  
    hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_5);/*数据*/
    EDIT_GetText(hItem, tb, 20);

    if(PLC_ROUTE_ON == g_sys_ctrl.sysUseRoute)
    {
        g_gui_para.cmdType = PLC_CMD_TYPE_ROUTE;
    }
    else 
    {
        if(0x13 == g_gui_para.ctlCode)
        {
            g_gui_para.cmdType = PLC_CMD_BROAD_READ;
        }
        else
            g_gui_para.cmdType = PLC_CMD_TYPE_COMMON;
    }
    

    return DEV_OK;
}



    
//向上选择
void CPT_SelEdt_Up(WM_MESSAGE * pMsg)
{
    WM_HWIN hItem;
    if(cpt_key_press_cnt == 0)
    {
        
        //WM_SetFocus(hItem);
        
        hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_5);
        WM_SetFocus(hItem);
        
        cpt_key_press_cnt=5;
    }
    else
    {
        cpt_key_press_cnt--;
        hItem=WM_GetDialogItem(pMsg->hWin,(ID_EDIT_0+cpt_key_press_cnt));
        WM_SetFocus(hItem);
    }
}
//向下选择
void CPT_SelEdt_Down(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    if(cpt_key_press_cnt==5)
    {
        hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_0);
        WM_SetFocus(hItem);

        cpt_key_press_cnt = 0;
    }
    else
    {
        cpt_key_press_cnt++;
        hItem=WM_GetDialogItem(pMsg->hWin,(ID_EDIT_0 + cpt_key_press_cnt));
        WM_SetFocus(hItem);
    }
}


void CPT_Color_Change(void)
{
    WM_HWIN hItem;
    int i;
    for(i=0;i<6;i++)
    {
        hItem=WM_GetDialogItem(g_hWin_std,ID_EDIT_0+i);
        if(WM_HasFocus(hItem)==1)
        {
            EDIT_SetBkColor(hItem,0,GUI_GREEN);
        }
        else if(WM_HasFocus(hItem)==0)
        {
            EDIT_SetBkColor(hItem,0,0xC0C0C0);
        }
    }
}

void CPT_SetFocus(void)
{
    WM_HWIN hItem;
    hItem = WM_GetDialogItem(g_hWin_std, (ID_EDIT_0 + cpt_key_press_cnt));
    WM_SetFocus(hItem);
}

void CST_Set_DataFlag(u8 * tst)
{
    WM_HWIN hItem;
    hItem=WM_GetDialogItem(g_hWin_std,(ID_EDIT_3));
    EDIT_SetText(hItem, tst); 
}

void CPT_ClearData(void)
{
    WM_HWIN hItem;
    hItem = WM_GetDialogItem(g_hWin_std, ID_EDIT_5);
    EDIT_SetText(hItem, "00000000");
}

WM_HWIN CPT_Get_Speed(void)
{
    return WM_GetDialogItem(g_hWin_std,ID_EDIT_0);
}

WM_HWIN CPT_Set_Addr(void)
{
    return WM_GetDialogItem(g_hWin_std,ID_EDIT_1);
}

WM_HWIN CPT_Set_CtlCode(void)
{
    return WM_GetDialogItem(g_hWin_std,ID_EDIT_2);
}

WM_HWIN CPT_Set_DataFlag(void)
{
    return WM_GetDialogItem(g_hWin_std,ID_EDIT_3);
}

WM_HWIN CPT_Set_Length(void)
{
    return WM_GetDialogItem(g_hWin_std,ID_EDIT_4);
}

WM_HWIN CPT_Set_Data(void)
{
    return WM_GetDialogItem(g_hWin_std,ID_EDIT_5);
}


static void _init_dialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hItem;
    int i;
    u8 tempbuf[10];

   
    hItem=WM_GetDialogItem(pMsg->hWin,ID_BUTTON_0);
    BUTTON_SetBkColor(hItem,0,GUI_CYAN);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

    hItem=WM_GetDialogItem(pMsg->hWin,ID_BUTTON_1);
    BUTTON_SetBkColor(hItem,0,GUI_CYAN);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

    hItem=WM_GetDialogItem(pMsg->hWin,ID_BUTTON_2);
    BUTTON_SetBkColor(hItem,0,GUI_GREEN);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

    hItem=WM_GetDialogItem(pMsg->hWin,ID_BUTTON_3);
    BUTTON_SetBkColor(hItem,0,GUI_CYAN);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

    hItem=WM_GetDialogItem(pMsg->hWin,ID_BUTTON_4);
    BUTTON_SetBkColor(hItem,0,GUI_YELLOW);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);

   

    for(i=0;i<6;i++)
    {
        hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_0+i);
        WM_DisableWindow(hItem);
    }
    
    PUB_InitFreq(pMsg,ID_EDIT_0);//根据保存的参数初始化速率设置项
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);    
    EDIT_SetText(hItem, GUI_hex2MeterAddrStr(g_sys_ctrl.recentMeterAddr, 6));
    //
    // Initialization of 'Dropdown'
    //
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    EDIT_SetText(hItem, Readdata);
     if(g_rom_para.plcProtocol == DL_T_07)
    {
        g_gui_para.ctlCode = c_645ctrlDef[g_rom_para.plcProtocol][1]; 
    }
    else if(g_rom_para.plcProtocol == DL_T_97)
    {
        g_gui_para.ctlCode = c_645ctrlDef[g_rom_para.plcProtocol][1]; 
    }

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
    GUI_GetHexDataFlag(tempbuf, g_sys_ctrl.defaultDataFlag, 4);
    EDIT_SetText(hItem, tempbuf);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_4);
    //GUI_GetHexDataFlag(tempbuf, g_sys_ctrl.defaultDataFlag, 4);
    EDIT_SetText(hItem, "0");
    
    
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_5);
    EDIT_SetText(hItem, "00000000");

    hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
    PROGBAR_SetBarColor(hItem,0,GUI_GREEN);
}


/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  int key_num;
  // USER START (Optionally insert additional variables)
  // USER END
  key_num=((WM_KEY_INFO *)(pMsg->Data.p))->Key;
  
  switch (pMsg->MsgId) 
  {
      case WM_INIT_DIALOG:
        
        _init_dialog(pMsg);
        //CPT_Color_Change(pMsg);
        break;
     case WM_KEY:
        Id  = WM_GetId(pMsg->hWinSrc);
        if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==1)
        {
            switch(Id)
            {
              case ID_EDIT_0:
                if(key_num==GUI_KEY_ENTER)
                {
                  g_hWin_speed = CreateSpeed(g_hWin_std);
                }
                break;
                
              case ID_EDIT_1:
                if(key_num==GUI_KEY_ENTER)
                {
                  g_sys_ctrl.selectWidget=EDIT_ADDR;
                  g_hWin_Input=Create_Edit_Set(g_hWin_std);
                  
                  WM_SetFocus(g_hWin_Input);
                }
                break;
              case ID_EDIT_2:
                if(key_num==GUI_KEY_ENTER)
                {
                  g_sys_ctrl.selectWidget=LISTBOX_CTLCODE;
                  g_hWin_Input=Create_ListBox_Set(g_hWin_std);
                  WM_SetFocus(g_hWin_Input);
                }
                break;
              case ID_EDIT_3:
                if(key_num==GUI_KEY_ENTER)
                {
                  g_sys_ctrl.selectWidget=EDIT_DATA_FLAG;
                  g_hWin_Input=Create_Edit_Set(g_hWin_std);
                  WM_SetFocus(g_hWin_Input);
                }
                break;
              case ID_EDIT_4:
                if(key_num==GUI_KEY_ENTER)
                {
                  g_sys_ctrl.selectWidget=EDIT_LENGTH;
                  g_hWin_Input=Create_Edit_Set(g_hWin_std);
                  WM_SetFocus(g_hWin_Input);
                }
                break;
              case ID_EDIT_5:
                if(key_num==GUI_KEY_ENTER)
                {
                  g_sys_ctrl.selectWidget=EDIT_DATA;
                  g_hWin_Input=Create_Edit_Set(g_hWin_std);
                  WM_SetFocus(g_hWin_Input);
                }
                break;                
            }               

        }
        switch(((WM_KEY_INFO *)(pMsg->Data.p))->Key)
        {
            case GUI_KEY_YELLOW:
                if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==1)
                {
                    WM_DeleteWindow(g_hWin_std);
                    g_hWin_std = HBWIN_NULL;
                    WM_BringToBottom(g_hWin_msg);
                    WM_HideWindow(g_hWin_msg);
                    WM_ShowWindow(g_hWin_TimeBar);
                    WM_ShowWindow(g_hWin_Date);
                    WM_SetFocus(g_hWin_menu); 
                    g_sys_ctrl.guiState = GUI_PLC_MSG_IDLE;
                    cpt_key_press_cnt=0;
                }
                break;
                
            case GUI_KEY_GREEN:
                if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==1)
                {
                    if(DEV_OK == Get_Para_From_Widget(pMsg))//获取参数数据
                    {
                        g_sys_ctrl.guiState = GUI_PLC_MSG_TEST;
                        OSMboxPost(g_sys_ctrl.up_mbox,(void*)&g_gui_para);
                    }  
                }
                break;
                
            case GUI_KEY_UP:
                if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==0)
                {
                    CPT_SelEdt_Up(pMsg);
                    CPT_Color_Change();
                }
                
                break;
                
            case GUI_KEY_DOWN:
                if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==0)
                {
                    CPT_SelEdt_Down(pMsg);
                    CPT_Color_Change();
                }
                
                break;
                
            case GUI_KEY_F1:
                if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==0)
                {
                    g_hWin_relay=CreateRelayAddr();
                    WM_ShowWindow(g_hWin_relay);
                    WM_SetFocus(g_hWin_relay);
                }
                break;

            case GUI_KEY_F2:
                if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==0)
                {
                    g_hWin_DataSign=CreateDataSign();
                    WM_ShowWindow(g_hWin_DataSign);
                    WM_SetFocus(g_hWin_DataSign);
                }
                break;

             case GUI_KEY_TAB:
                if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==0)
                {
                    //CPT_SelEdt_Up(pMsg);
                    CPT_Color_Change();
                }
                
                break;

            case '#':
                if((((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt)==0)
                {
                    WM_BringToTop(g_hWin_msg);
                    WM_ShowWindow(g_hWin_msg);                    
                    WM_SetFocus(g_hWin_msg);
                }
                break;

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
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateCommProtoTest
*/
WM_HWIN CreateCommStdTest(void);
WM_HWIN CreateCommStdTest(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, g_hWin_menu, 0, 0);
  return hWin;

}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
