#ifndef __APP_STORAGE_H__
#define __APP_STORAGE_H__


#define BOOT_REQUEST_ACT   0xffffbbcc
#define BOOT_FINISH_ACT    0xffff0000

/*
Sector 0 0x0800 0000 - 0x0800 3FFF 16 Kbyte
Sector 1 0x0800 4000 - 0x0800 7FFF 16 Kbyte
Sector 2 0x0800 8000 - 0x0800 BFFF 16 Kbyte
Sector 3 0x0800 C000 - 0x0800 FFFF 16 Kbyte
Sector 4 0x0801 0000 - 0x0801 FFFF 64 Kbyte
Sector 5 0x0802 0000 - 0x0803 FFFF 128 Kbyte
Sector 6 0x0804 0000 - 0x0805 FFFF 128 Kbyte
Sector 7 0x0806 0000 - 0x0807 FFFF 128 Kbyte
*/

#define ROM_ADDR_SYS_PARA    (0x8004000uL)
#define ROM_ADDR_PARA_SIZE    (sizeof(ROM_PARA))

#define RAM_COPY_MAX_SIZE_K    64
#define SRM_PARA_NUMBER      512
#define TAG_WORD_TABLE_MAP     0XDA3C7B92


#define ROM_PARA_TOTAL_SIZE       (16*1024)      //k Bytes;
#define ROM_PARA_ERASE_SECTOR      FLASH_SECTOR_1
#define ROM_PARA_WRITE_TIMES      (ROM_PARA_TOTAL_SIZE/ROM_ADDR_PARA_SIZE)    //(16/2)

#define DEV_TRUE            1
#define DEV_FALSE           0


#define DEV_ERROR            1
#define DEV_OK               0


#define SYS_TASK_FORMAT_DISK     0X00000001


typedef struct  __sys_storage_struct__
{
unsigned int magic_word;
unsigned int bootFlag;      //������־�����ܸĶ�
unsigned int crc;
unsigned int versionDate;


unsigned int meterPassword;//����
unsigned int recvDelayTime;//����������ʱ
unsigned int execInterval;//ִ��ʱ��
unsigned int plcProtocol; //��Լ
unsigned int channel; //ͨ��
unsigned int baudrate; //������
//before ************10******************

unsigned int preamble; //ǰ����
unsigned int stopbit;
unsigned int number;

//unsigned int pwrValue;//��ص���

unsigned int para_data[SRM_PARA_NUMBER-13];
}ROM_PARA, *P_ROM_PARA;

typedef struct __sys_control__
{
    unsigned int paraAddr;
    u32   guiState;
    u32   testProgBarVal;
    u32   procTask;    //��ǰϵͳ��Ҫ����������
    u32   pwrValue;//��ص���
    u32   sleepTimeout;
    u8    recentMeterAddr[6];   //���ʹ�õı���ַ
    u8    defaultDataFlag[4];   //���ʹ�õı���ַ
    OS_EVENT *downMb; //���䷢�͵���Ϣ
    OS_EVENT *upMb; //���䷢�͵���Ϣ
    u32 sd_total_capacity; //SD��������
    u32 sd_free_capacity; //SD��ʣ������
}SYS_CONTROL, *P_SYS_CONTROL;

#define SYS_ADD_TASK(tn)        g_sys_control.procTask|=tn
#define SYS_DEL_TASK(tn)        g_sys_control.procTask&=(~tn)
#define SYS_IS_TASK(tn)         g_sys_control.procTask&tn
 
extern ROM_PARA     g_sys_register_para;
extern SYS_CONTROL  g_sys_control;

void DEV_Init(void);

unsigned int DEV_Parameters_Write(void);
void DEV_Parameters_Read(void);
void DEV_Power_Off();
void DEV_SoftReset(void);
#endif