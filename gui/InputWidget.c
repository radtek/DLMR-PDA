#include "DIALOG.h"
#include "includes.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0  (GUI_ID_USER + 0x00)
#define ID_LISTBOX_0   (GUI_ID_USER + 0x02)
#define ID_BUTTON_0    (GUI_ID_USER + 0x03)
#define ID_BUTTON_1    (GUI_ID_USER + 0x04)
#define ID_TEXT_0      (GUI_ID_USER + 0x05)
#define ID_EDIT_0      (GUI_ID_USER + 0x06)



static const GUI_WIDGET_CREATE_INFO _aListBoxCreate[] = {
  { FRAMEWIN_CreateIndirect,  "ListBox",  ID_FRAMEWIN_0,  20,  40,  200, 200,  0, 0x0, 0 },
  { LISTBOX_CreateIndirect,   "Listbox",  ID_LISTBOX_0,   5,   7,   182, 120,  0, 0x0, 0 },
  { BUTTON_CreateIndirect,    Confirm,    ID_BUTTON_0,    5,   140, 55,  25,   0, 0x0, 0 },
  { BUTTON_CreateIndirect,    Cancel,       ID_BUTTON_1,    138, 140, 55,  25,   0, 0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aEditCreate[] = {
  { FRAMEWIN_CreateIndirect, "Edit",  ID_FRAMEWIN_0, 20,  60, 200, 160, 0, 0x0,  0 },
  { BUTTON_CreateIndirect,   Confirm, ID_BUTTON_0,   5,   82, 55,  25,  0, 0x0,  0 },
  { BUTTON_CreateIndirect,   Cancel,    ID_BUTTON_1,   138, 82, 55,  25,  0, 0x0,  0 },
  { EDIT_CreateIndirect,     "Edit",  ID_EDIT_0,     14,  38, 165, 25,  0, 0x64, 0 },
  //{ TEXT_CreateIndirect,   "Text",    ID_TEXT_0,   14,  16, 165, 20,  0, 0x0,  0 },

};

#if 0
const u8 c_645ctrlDef[2][PLC_CTRL_MAX_NUM] = 
{ 
    //97规约
    {0x05, 0x01, 0x04,  4,5,6,7,8,9,10,11,12,13,14,15,16},
    //07规约
    {0x13, 0X11, 0X14,  0x19,5,6,7,8,9,10,11,12,13,14,15,16}
};


const u32 c_645DidoDef[2][PLC_CTRL_MAX_NUM] = 
{ 
    //97规约
    {0x901f,    0x902f,     0x9410,     0x9420,5,6,7,8,9,10,11,12,13,14,15,16},
    //07规约
    {0x0001ff00,0X0002ff00, 0X0001ff01, 0X0002ff01,4,5,6,7,8,9,10,11,12,13,14,15,}
};
#endif
const u32 c_ValBaudRate[5] = {BAUD_RATE_1200, BAUD_RATE_1500, BAUD_RATE_2400, BAUD_RATE_4800, BAUD_RATE_9600};

const u8 c_TextBaudRate[5][6] = {"1200","1500","2400","4800","9600"};

void Select_Focus(void)
{
    
    if(g_hWin_para>0)
    {
        WM_SetFocus(g_hWin_para);
        CPS_SetFocus();
    }
    
    if((g_hWin_std > 0)&&(g_hWin_relay <= 0)) 
    {
        WM_SetFocus(g_hWin_std);
        CPT_SetFocus();
    }
    
    if(g_hWin_ReadMeter>0)
    {
        WM_SetFocus(g_hWin_ReadMeter);
        RMD_SetFocus();
    }

    if(g_hWin_TimeSet>0)
    {
        WM_SetFocus(g_hWin_TimeSet);
        TMS_SetFocus();
    }
    if(g_hWin_about>0)
    {
        WM_SetFocus(g_hWin_about);
    }
    if(g_hWin_AdvanSet > 0)
    {
        WM_SetFocus(g_hWin_AdvanSet);
        ADS_SetFocus();
    }
    
    if(g_hWin_relay > 0)
    {
        WM_SetFocus(g_hWin_relay);
    }

    if(g_hWin_SDInfo > 0)
    {
        WM_SetFocus(g_hWin_SDInfo);
    }

    if(g_hWin_about>0)
    {
        WM_SetFocus(g_hWin_about);
    }

    if(g_hWin_monitor > 0)
    {
        WM_SetFocus(g_hWin_monitor);
    }
}

//在按下绿色保存按钮的时候，调用此函数
static void Select_Input_Edit(int  EditNum)
{
    WM_HWIN hItem;
    u8 tmpTextBuf[32];
    u8 tmpListBuf[32];//中继地址序号
    int RowCount;
    int RowSel;
    
    hItem=WM_GetDialogItem(g_hWin_Input,ID_EDIT_0);
    switch(EditNum)
    {
        case EDIT_SCR_OUTTIME:
            EDIT_GetText(hItem,tmpTextBuf,4);
            g_rom_para.scrTimeout = atoi(tmpTextBuf);
            if(g_rom_para.scrTimeout < 30)
            {
                g_rom_para.scrTimeout = 30;

                sprintf(tmpTextBuf, "%d", g_rom_para.scrTimeout);
            }
            hItem=CPS_Set_ScrOutTime();
            break;
            
        case EDIT_PASSWORD:
            EDIT_GetText(hItem,tmpTextBuf,7);
            //g_rom_para.meterPassword = atoi(tmpTextBuf);
            hItem=CPS_Set_Pwd();
            break;
            
        case EDIT_RECV_DELAY:
            EDIT_GetText(hItem,tmpTextBuf,5);
            g_rom_para.recvDelayTime = atoi(tmpTextBuf);
            hItem=CPS_Set_RevDelay();
            break;

        case EDIT_BETWEEN_ACT:
            EDIT_GetText(hItem,tmpTextBuf,5);
            g_rom_para.execInterval = atoi(tmpTextBuf);
            hItem=CPS_Set_BetweenAct();
            break;

        case EDIT_ADDR:
            EDIT_GetText(hItem,tmpTextBuf,13);
            GUI_Fill_Zero(tmpTextBuf);
            GUI_GetMeterAddr(tmpTextBuf, g_sys_ctrl.recentMeterAddr);
            hItem=CPT_Set_Addr();
            break;

        case EDIT_DATA_FLAG:
            EDIT_GetText(hItem,tmpTextBuf,9);
            hItem=CPT_Set_DataFlag();
            GUI_GetStrDataFlag(tmpTextBuf, g_rom_para.plcProtocol);
            break;

        case EDIT_LENGTH:
            EDIT_GetText(hItem,tmpTextBuf,2);
            hItem=CPT_Set_Length();
            break;

        case EDIT_DATA:
            EDIT_GetText(hItem,tmpTextBuf,13);
            hItem=CPT_Set_Data();
            break;

        case EDIT_METER_NUM:
            EDIT_GetText(hItem,tmpTextBuf,13);
            GUI_Fill_Zero(tmpTextBuf);
            GUI_GetMeterAddr(tmpTextBuf, g_sys_ctrl.recentMeterAddr);
            hItem=RMD_Get_MeterNum();
            break;
            
        case EDIT_YEAR:
            EDIT_GetText(hItem,tmpTextBuf,3);
            hItem=TMS_Get_Year();
            break;
        case EDIT_MONTH:
            EDIT_GetText(hItem,tmpTextBuf,3);
            hItem=TMS_Get_Month();
            break;
        case EDIT_DAY:
            EDIT_GetText(hItem,tmpTextBuf,3);
            hItem=TMS_Get_Day();
            break;
        case EDIT_HOUR:
            EDIT_GetText(hItem,tmpTextBuf,3);
            hItem=TMS_Get_Hour();
            break;
        case EDIT_MIN:
            EDIT_GetText(hItem,tmpTextBuf,3);
            hItem=TMS_Get_Min();
            break;
        case EDIT_SEC:
            EDIT_GetText(hItem,tmpTextBuf,3);
            hItem=TMS_Get_Sec();
            break;
        //case EDIT_PWD_CFM:
            //EDIT_GetText(hItem,tmpTextBuf,7);
            //hItem = 
          //  break;
        case EDIT_OPCODE:
            EDIT_GetText(hItem,tmpTextBuf,9);
            hItem = ADS_Get_OpCode();
            break;

        case MODIFY_RELAY_ADDR: //修改中继地址
            EDIT_GetText(hItem,tmpTextBuf,13);
            GUI_Fill_Zero(tmpTextBuf);
            
            hItem = RLY_GetListAddr();
            RowSel = LISTVIEW_GetSel(hItem);
            LISTVIEW_SetItemText(hItem ,1, RowSel, tmpTextBuf);
            //LISTVIEW_Handle hObj,unsigned Column,unsigned Row,const char * s)
            hItem = RLY_GetAddr();
            break;

        case ADD_RELAY_ADDR:  //按#增加,这里耦合性应该挺厉害的
            EDIT_GetText(hItem,tmpTextBuf,13);
            GUI_Fill_Zero(tmpTextBuf); 
            hItem = RLY_GetListAddr();
            
            LISTVIEW_AddRow(hItem, NULL);
            RowCount=LISTVIEW_GetNumRows(hItem);
            LISTVIEW_SetItemText(hItem, 1, (RowCount-1), tmpTextBuf);//第1列也就是，中继地址列
            int_to_char((RowCount-1), tmpListBuf, 10);
            LISTVIEW_SetItemText(hItem, 0, (RowCount-1), tmpListBuf);
            hItem = WM_GetDialogItem(g_hWin_Input,ID_EDIT_0);
            break;
            
        default:
            break;
    }
    EDIT_SetText(hItem,tmpTextBuf);
}


static void _init_edit(WM_MESSAGE *pMsg,int EditNum)
{

    WM_HWIN hItem;
    u8 tmpTextBuf[32];
    u8 addr_len;
    u8 tmpZero[13];
    int RowSel;
    int i;
    switch(EditNum)
    {
        case EDIT_SCR_OUTTIME:
            hItem=CPS_Set_ScrOutTime();
            EDIT_GetText(hItem,tmpTextBuf,5);
            //hItem=CPS_Set_ScrOutTime();
            break;
            
        case EDIT_PASSWORD:
            hItem=CPS_Set_Pwd();
            EDIT_GetText(hItem,tmpTextBuf,7);
            break;
            
        case EDIT_RECV_DELAY:
            hItem=CPS_Set_RevDelay();
            EDIT_GetText(hItem,tmpTextBuf,5);
            break;

        case EDIT_BETWEEN_ACT:
            hItem=CPS_Set_BetweenAct();
            EDIT_GetText(hItem,tmpTextBuf,5);
            break;

        case EDIT_ADDR:
            hItem=CPT_Set_Addr();
            EDIT_GetText(hItem,tmpTextBuf,13);            
            break;

        case EDIT_DATA_FLAG:
            hItem=CPT_Set_DataFlag();
            EDIT_GetText(hItem,tmpTextBuf,9);
            break;

        case EDIT_LENGTH:
            hItem=CPT_Set_Length();
            EDIT_GetText(hItem,tmpTextBuf,2);
            break;

        case EDIT_DATA:
            hItem=CPT_Set_Data();
            EDIT_GetText(hItem,tmpTextBuf,13);
            
            break;

        case EDIT_METER_NUM:
            hItem=RMD_Get_MeterNum();
            EDIT_GetText(hItem,tmpTextBuf,13);
            break;

        case EDIT_YEAR:
            hItem=TMS_Get_Year();
            EDIT_GetText(hItem,tmpTextBuf,3);
            break;
            
        case EDIT_MONTH:
            hItem=TMS_Get_Month();
            EDIT_GetText(hItem,tmpTextBuf,3);
            break;
            
        case EDIT_DAY:
            hItem=TMS_Get_Day();
            EDIT_GetText(hItem,tmpTextBuf,3);
            break;
            
        case EDIT_HOUR:
            hItem=TMS_Get_Hour();
            EDIT_GetText(hItem,tmpTextBuf,3);
            break;
            
        case EDIT_MIN:
            hItem=TMS_Get_Min();
            EDIT_GetText(hItem,tmpTextBuf,3);
            break;
            
        case EDIT_SEC:
            hItem=TMS_Get_Sec();
            EDIT_GetText(hItem,tmpTextBuf,3);
            break;
        case EDIT_OPCODE: //长度需要注意,操作码
            hItem = ADS_Get_OpCode();
            EDIT_GetText(hItem,tmpTextBuf,5);
            break;

        case MODIFY_RELAY_ADDR:
            hItem = RLY_GetListAddr();
            RowSel = LISTVIEW_GetSel(hItem);
            LISTVIEW_GetItemText(hItem,1, RowSel, tmpTextBuf, 13);
            break;

        case ADD_RELAY_ADDR:
            memcpy(tmpTextBuf,"\0",1);
            break;
            
        default:
            break;
     }
     FRAMEWIN_SetText(pMsg->hWin,Edit_FrameTitle[EditNum]);
     hItem=WM_GetDialogItem(pMsg->hWin,ID_EDIT_0);
     EDIT_SetText(hItem,tmpTextBuf);
}



/*********************************************************************
*
*       Static code
*
**********************************************************************
*/


void Button_Color_Set(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    hItem = WM_GetDialogItem(pMsg->hWin,ID_BUTTON_0);
    BUTTON_SetBkColor(hItem,0,GUI_GREEN);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
    
    hItem = WM_GetDialogItem(pMsg->hWin,ID_BUTTON_1);
    BUTTON_SetBkColor(hItem,0,GUI_YELLOW);
    WIDGET_AndState(hItem,WIDGET_STATE_FOCUSSABLE);
}



static void _cbEditDlg(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
    int     NCode;
    int     Id;
  
    switch (pMsg->MsgId) 
    {
      case WM_INIT_DIALOG:
        FRAMEWIN_SetTitleHeight(pMsg->hWin,25);
        Button_Color_Set(pMsg);
        _init_edit(pMsg,g_sys_ctrl.selectWidget);
        break;
        
      case WM_KEY:
        if((((WM_KEY_INFO *)(pMsg->Data.p))->PressedCnt)==0)
        {
            switch(((WM_KEY_INFO *)(pMsg->Data.p))->Key)
            {
              case GUI_KEY_YELLOW:
                  WM_DeleteWindow(g_hWin_Input);
                  g_hWin_Input = HBWIN_NULL;
                  Select_Focus();
                  break;
              case GUI_KEY_GREEN:
                  Select_Input_Edit(g_sys_ctrl.selectWidget);
                  WM_DeleteWindow(g_hWin_Input);
                  Select_Focus();
                  g_hWin_Input = HBWIN_NULL;
                  break;
            }
        }
        break;
      
      default:
        WM_DefaultProc(pMsg);
        break;
      }
}


static void _Init_ListBox(WM_MESSAGE *pMsg, int ListBoxNum)
{
    
    //u8 tmpTextBuf[32];
    u32 Sel_Num;
    WM_HWIN hItem;
    int i;
    
    hItem=WM_GetDialogItem(pMsg->hWin,ID_LISTBOX_0);
    
    switch(ListBoxNum)
    {
        case LISTBOX_PROTOCOL:
            LISTBOX_AddString(hItem, "DLT-07");
            LISTBOX_AddString(hItem, "DLT-97");
            switch(g_rom_para.plcProtocol)
            {
                case DL_T_07:
                    LISTBOX_SetSel(hItem,0);
                    break;
                case DL_T_97:
                    LISTBOX_SetSel(hItem,1);
                    break;
            }
            break;
            
        case LISTBOX_CHANNEL:
            //LISTBOX_AddString(hItem, "485");
            LISTBOX_AddString(hItem, WaveCarrier);
            LISTBOX_AddString(hItem, ChannelWireless);
            break;


        case LISTBOX_BAUDRATE:
            LISTBOX_AddString(hItem, "1200");
            LISTBOX_AddString(hItem, "1500");
            LISTBOX_AddString(hItem, "2400");
            LISTBOX_AddString(hItem, "4800");
            LISTBOX_AddString(hItem, "9600");
            switch(g_rom_para.baudrate)
            {
                case 1200:
                    LISTBOX_SetSel(hItem,0);
                    break;
                case 1500:
                    LISTBOX_SetSel(hItem,1);
                    break;
                case 2400:
                    LISTBOX_SetSel(hItem,2);
                    break;
                case 4800:
                    LISTBOX_SetSel(hItem,3);
                    break;
                case 9600:
                    LISTBOX_SetSel(hItem,4);
                    break;
            }
            break;

        case LISTBOX_PREAM:
            break;

        case LISTBOX_STOPBIT:
            LISTBOX_AddString(hItem, "1");
            LISTBOX_AddString(hItem, "2");
            switch(g_rom_para.stopbit)
            {
                case ONE_STOPBIT:
                    LISTBOX_SetSel(hItem, 0);
                    break;
                case TWO_STOPBIT:
                    LISTBOX_SetSel(hItem, 1);
                    break;     
            }
            break;

        
        case LISTBOX_CTLCODE:  /*控制字*/
            LISTBOX_AddString(hItem, GetAddr);
            LISTBOX_AddString(hItem, Readdata);
            //LISTBOX_AddString(hItem, WriteData);
            //LISTBOX_AddString(hItem, ClrDemond);
            break;

        case LISTBOX_READ_SEL:
           LISTBOX_AddString(hItem, Positive);
           LISTBOX_AddString(hItem, Negative);
           LISTBOX_AddString(hItem, DayPositive);
           LISTBOX_AddString(hItem, DayNegative);
           break;

        case LISTBOX_SPEED:
            for(i = 0;i < 8;i++)
            {
                LISTBOX_AddString(hItem,pTextSpeed[i]);
            }
            break;
            
        default:
           break;
    }
    FRAMEWIN_SetText(pMsg->hWin,Listbox_FrameTitle[ListBoxNum]);

}



static void Select_ListBox_Row(int  WidgetNum)
{

    WM_HWIN hItem;
    WM_HWIN hWin;
    int  SelNum;
    hItem=WM_GetDialogItem(g_hWin_Input,ID_LISTBOX_0);
    SelNum=LISTBOX_GetSel(hItem);
    switch(WidgetNum) /*WidgetNum是为了把不同的页面的不同Edit工具句柄传回来*/
    {
        case LISTBOX_PROTOCOL:
            switch(SelNum) 
            {
                case 0:
                    g_rom_para.plcProtocol = DL_T_07;
                    TSK_SetProtocol_07();
                    hWin=CPS_Set_Proto();
                    EDIT_SetText(hWin,"DLT-07");
                    break;
                case 1:
                    g_rom_para.plcProtocol = DL_T_97;
                    TSK_SetProtocol_97();
                    hWin=CPS_Set_Proto();
                    EDIT_SetText(hWin,"DLT-97");
                    break;
            }
            break;

        case LISTBOX_CHANNEL:
            switch(SelNum)
            {
                case 2:
                   // g_rom_para.channel=CHANNEL_485;
                    //hWin=CPS_Set_Channel();
                    //EDIT_SetText(hWin,"485");
                    break;
                    
                case 0:
                    g_rom_para.channel=CHANNEL_PLC;
                    hWin=CPS_Set_Channel();
                    EDIT_SetText(hWin,WaveCarrier);
                    break;
                case 1:
                    g_rom_para.channel=CHANNEL_WIRELESS;
                    hWin=CPS_Set_Channel();
                    EDIT_SetText(hWin,ChannelWireless);
                    break;
            }
            break;
            
        case LISTBOX_BAUDRATE:
            g_rom_para.baudrate = c_ValBaudRate[SelNum];
            hWin = CPS_Set_BaudRate();
            EDIT_SetText(hWin,c_TextBaudRate[SelNum]);
            break;
            
         case LISTBOX_STOPBIT:
            switch(SelNum)
            {
                case 0:
                    g_rom_para.stopbit=ONE_STOPBIT;
                    hWin=CPS_Set_StopBit();
                    EDIT_SetText(hWin,"1");
                    break;
                case 1:
                    g_rom_para.stopbit=TWO_STOPBIT;
                    hWin=CPS_Set_StopBit();
                    EDIT_SetText(hWin,"2");
                    break;
            }
            break;


         case LISTBOX_CTLCODE:
            if(g_rom_para.plcProtocol == DL_T_97)
            {
                g_gui_para.ctlCode = c_645ctrlDef[g_rom_para.plcProtocol][SelNum]; 
            }
            else if(g_rom_para.plcProtocol == DL_T_07)
            {
                g_gui_para.ctlCode = c_645ctrlDef[g_rom_para.plcProtocol][SelNum]; 
            }
            hWin=CPT_Set_CtlCode();
            EDIT_SetText(hWin,pCtlCode[SelNum]);

            break;
            
        case LISTBOX_READ_SEL:
            //pReadSel
            if(g_rom_para.plcProtocol==DL_T_07)
            {        
                memcpy(g_gui_para.dataFlag,
                    &c_645DidoDef[g_rom_para.plcProtocol][SelNum],
                    4);
                
                g_gui_para.ctlCode=0x11;
            }
            else if(g_rom_para.plcProtocol==DL_T_97)
            {
                memcpy(g_gui_para.dataFlag,
                    &c_645DidoDef[g_rom_para.plcProtocol][SelNum],
                    2);
                g_gui_para.ctlCode=0x01; 
        
            }
            hWin=RMD_Get_ReadSel();
            EDIT_SetText(hWin,pReadSel[SelNum]);
            break;

        default:
            break;

      }
}



static void _cbListBoxDlg(WM_MESSAGE *pMsg)
{
    WM_HWIN hItem;
   // int     Id;
    //int     SelNum;

    switch(pMsg->MsgId)
    {
        case WM_INIT_DIALOG:
          GUI_UC_SetEncodeUTF8();
          FRAMEWIN_SetTitleHeight(pMsg->hWin,25);
          //WINDOW_SetBkColor(pMsg->hWin,GUI_WHITE);
          //hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTBOX_0);
          _Init_ListBox(pMsg,g_sys_ctrl.selectWidget);
          Button_Color_Set(pMsg);
          
          break;
          
        case WM_KEY:
          if((((WM_KEY_INFO *)(pMsg->Data.p))->PressedCnt)==0)
          {
              switch(((WM_KEY_INFO *)(pMsg->Data.p))->Key)
              {
                case GUI_KEY_YELLOW:
                    WM_DeleteWindow(g_hWin_Input);
                    //WM_SetFocus(g_hWin_para);
                    Select_Focus();
                    break;
                case GUI_KEY_GREEN:
                    Select_ListBox_Row(g_sys_ctrl.selectWidget);
                    WM_DeleteWindow(g_hWin_Input);
                    Select_Focus();
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
*
**********************************************************************/


//listbox对话框

WM_HWIN Create_ListBox_Set(WM_HWIN parentWin);

WM_HWIN Create_ListBox_Set(WM_HWIN parentWin)
{
    WM_HWIN hWin;
    hWin=GUI_CreateDialogBox(_aListBoxCreate , GUI_COUNTOF(_aListBoxCreate),_cbListBoxDlg,parentWin,0,0);
    return hWin;
}



//edit对话框
WM_HWIN Create_Edit_Set(WM_HWIN parentWin);

WM_HWIN Create_Edit_Set(WM_HWIN parentWin)
{
    WM_HWIN hWin;
    hWin=GUI_CreateDialogBox(_aEditCreate , GUI_COUNTOF(_aEditCreate), _cbEditDlg ,parentWin,0,0);
    return hWin;
}




