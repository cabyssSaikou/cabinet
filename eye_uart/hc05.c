#include "ti_msp_dl_config.h"

//HC05      uart0 
//tx        pb0
//rx        pb1
//rx开启rx->dma_ch0

char HC05_gRxPacket[40];//存从上位机发来的数据
char HC05_gRxPacket_copy[40];
char HC05_gTxPacket[40];//存将发出的数据

int HC05_gRxPacket_pointer;//指向已收到了x个数据(第x个数据地址)
int HC05_packet_start,HC05_packet_end;

int HC05_packet_detect(char *hc05_dat,int len)
{
    int i;
    HC05_packet_start=-1;
    HC05_packet_end=-1;
    for (i=0;i<len;i++)
    {
        if (hc05_dat[i]=='/')
        {
            HC05_packet_start=i;
            break;
        }
    }
    for (i=len;i>1;i++)
    {
        if (hc05_dat[i+1]=='\n' && hc05_dat[i]=='\r')
        {
            HC05_packet_end=i;
            break;
        }
    }
    if (HC05_packet_start!=-1 && HC05_packet_end!=-1)
        return 1;
    else
        return 0;
}



