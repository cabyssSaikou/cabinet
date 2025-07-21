#ifndef __drv_uart_H
#define __drv_uart_H

extern int HC05_cnt,HC05_packet_length,arm_1_cnt,arm_1_packet_length,arm_2_cnt,arm_2_packet_length,arm_3_cnt,arm_3_packet_length;
extern bool uart_hc05_done,uart_arm_1_done,uart_arm_2_done,uart_arm_3_done;

void UART_Write(int CMD_UartNum,char *pBuf,int Len);
void UART_Write_num(int CMD_UartNum,int num_c,int len);
void Uart_NVIC_init(void);

#endif

