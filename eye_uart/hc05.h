#ifndef __hc05_H
#define __hc05_H


extern char HC05_gRxPacket[40];//存从上位机发来的数据
extern char HC05_gRxPacket_copy[40];
extern char HC05_gTxPacket[40];//存将发出的数据

extern int HC05_gRxPacket_pointer;//指向已收到了x个数据(第x个数据地址)
extern int HC05_packet_start,HC05_packet_end;

void hc05_dma_init(void);
int HC05_packet_detect(char *hc05_dat,int len);

#endif

