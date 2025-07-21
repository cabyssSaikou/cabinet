#include "ti_msp_dl_config.h"
#include <string.h>
#include "eye_uart/hc05.h"
#include "eye_uart/hc05_reqserver.h"
#include "arm_controller/arm_controller.h"

//用到uart的文件

volatile int HC05_cnt=0,HC05_packet_length,arm_1_cnt=0,arm_1_packet_length,arm_2_cnt=0,arm_2_packet_length,arm_3_cnt=0,arm_3_packet_length;
volatile bool uart_hc05_done=false,uart_arm_1_done=false,uart_arm_2_done=false,uart_arm_3_done=false;

void UART_Write(int CMD_UartNum,char *pBuf,int Len)
{
//    int i;
    switch (CMD_UartNum)
    {
        case 0://uart0 eye
        //no dma
        uart_hc05_tx_pro=true;
        for (int i = 0; i<Len; i++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
	    {
		    DL_UART_Main_transmitDataBlocking(UART0, pBuf[i]);
	    }
        uart_hc05_tx_pro=false;
        break;
        case 1:
        //uart1 大臂
        uart_arm_1_tx_pro=true;
        for (int i = 0; i<Len; i++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
	    {
		    DL_UART_Main_transmitDataBlocking(UART1, pBuf[i]);
	    }
        uart_arm_1_tx_pro=false;
        break;
        case 2://uart2 小臂
        //no dma
        uart_arm_2_tx_pro=true;
        for (int i = 0; i<Len; i++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
	    {
		    DL_UART_Main_transmitDataBlocking(UART2, pBuf[i]);
	    }
        uart_arm_2_tx_pro=false;
        break;
        case 3:
        //uart3 升降驱动
        //no dma
        uart_arm_3_tx_pro=true;
        for (int i = 0; i<Len; i++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
	    {
		    DL_UART_Main_transmitDataBlocking(UART3, pBuf[i]);
	    }
        uart_arm_3_tx_pro=false;
        break;
        default:
            __BKPT();
        break;
    }
}
void UART_Write_num(int CMD_UartNum,int num_c,int len)
{
    int i,t;
    char d_buf[22];
    int num;
    if (num_c<0)
    {
        num_c=num_c*-1;//负数
        UART_Write(CMD_UartNum, "-", 1);
    }
    //输出整数
    for (i=0;i<len;i++)
        d_buf[i]='0';
    num=num_c;
    i=len;
    while (i>0 && num>0)
    {
        t=num;
        i--;
        d_buf[i]='0'+t%10;
        num=num/10;
    }
    UART_Write(CMD_UartNum, d_buf, len);
}

void UART0_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART0)) 
    {
        case DL_UART_MAIN_IIDX_RX:
        //no dma
//        __BKPT();
            HC05_gRxPacket[HC05_cnt]=DL_UART_Main_receiveData(UART_eye_INST);
            HC05_cnt++;
            if (HC05_gRxPacket[HC05_cnt-1]=='\n'||HC05_gRxPacket[HC05_cnt-1]=='!')
            {
                if (!uart_hc05_done)
                {
                    memset(HC05_gRxPacket_copy, 0, 35);
                    memcpy(HC05_gRxPacket_copy,HC05_gRxPacket,HC05_cnt);
                    HC05_packet_length=HC05_cnt;
                    uart_hc05_done=true;
                }

                HC05_cnt=0;
                
            }
            break;
        default:
            __BKPT();
        break;
    }
}

void UART1_IRQHandler(void)
{
    int i,j;
    switch (DL_UART_Main_getPendingInterrupt(UART1)) {
        case DL_UART_MAIN_IIDX_RX:
        //no dma
            arm_1_gRxPacket[arm_1_cnt]=DL_UART_Main_receiveData(UART_arm_1_INST);
            arm_1_cnt++;
            for (i=arm_1_cnt;i>=0;i--)           
              if (arm_1_gRxPacket[i]==107)//107是停止位
              {
//                if (!uart_arm_1_done)
                if (packet_uart_1_exp!=-1 && i>=packet_uart_1_exp)//若exp为-1则必定满足
                    if (arm_1_gRxPacket[i-packet_uart_1_exp+1]==1)//1是起始位
                    {
                        memset(arm_1_gRxPacket_copy, 0, 35);
                        for (j=0;j<=packet_uart_1_exp-1;j++)
                        {
                            arm_1_gRxPacket_copy[j]=arm_1_gRxPacket[i-packet_uart_1_exp+1+j];
                        }
                        arm_1_cnt=0;
                        arm_1_packet_length=packet_uart_1_exp;
                        uart_arm_1_done=true;
                        memset(arm_1_gRxPacket, 0, 35);
//                  __BKPT();
//                        UART_Write(0, arm_1_gRxPacket_copy, arm_1_packet_length);
                    }
                
                if (packet_uart_1_exp==-1)
                {
                    memcpy(arm_1_gRxPacket_copy,arm_1_gRxPacket,arm_1_cnt);
                    arm_1_packet_length=arm_1_cnt;
                    uart_arm_1_done=true;
//                __BKPT();
//                    UART_Write(0, arm_1_gRxPacket_copy, arm_1_packet_length);
                    arm_1_cnt=0;
                }
                
                break;
              }
            break;
        default:
            __BKPT();
        break;
    }
}
void UART2_IRQHandler(void)
{
    int i,j;
    switch (DL_UART_Main_getPendingInterrupt(UART2)) {
        case DL_UART_MAIN_IIDX_RX:
        //no dma
            arm_2_gRxPacket[arm_2_cnt]=DL_UART_Main_receiveData(UART_arm_2_INST);
            arm_2_cnt++;
            for (i=arm_2_cnt;i>=0;i--)           
              if (arm_2_gRxPacket[i]==107)//107是停止位
              {
                if (packet_uart_2_exp!=-1 && i>=packet_uart_2_exp)//若exp为-1则必定满足
                    if (arm_2_gRxPacket[i-packet_uart_2_exp+1]==1)//1是起始位
                    {
                        memset(arm_2_gRxPacket_copy, 0, 35);
                        for (j=0;j<=packet_uart_2_exp-1;j++)
                        {
                            arm_2_gRxPacket_copy[j]=arm_2_gRxPacket[i-packet_uart_2_exp+1+j];
                        }
//                        __BKPT();
                        arm_2_cnt=0;
                        arm_2_packet_length=packet_uart_2_exp;
                        uart_arm_2_done=true;
                        memset(arm_2_gRxPacket, 0, 35);
//                  __BKPT();
//                        UART_Write(0, arm_1_gRxPacket_copy, arm_1_packet_length);
                    }
                
                if (packet_uart_2_exp==-1)
                {
                    memcpy(arm_2_gRxPacket_copy,arm_2_gRxPacket,arm_2_cnt);
                    arm_2_packet_length=arm_2_cnt;
                    uart_arm_2_done=true;
//                __BKPT();
//                    UART_Write(0, arm_1_gRxPacket_copy, arm_1_packet_length);
                    arm_2_cnt=0;
                }
                
                break;
              }
            break;
        default:
            __BKPT();
        break;
    }
}
void UART3_IRQHandler(void)
{
    int i,j;
    switch (DL_UART_Main_getPendingInterrupt(UART3)) {
        case DL_UART_MAIN_IIDX_RX:
        //no dma
            arm_3_gRxPacket[arm_1_cnt]=DL_UART_Main_receiveData(UART_arm_3_INST);
            arm_3_cnt++;
            for (i=arm_3_cnt;i>=0;i--)           
              if (arm_3_gRxPacket[i]==107)//107是停止位
              {
//                if (!uart_arm_1_done)
                if (packet_uart_3_exp!=-1 && i>=packet_uart_3_exp)//若exp为-1则必定满足
                    if (arm_3_gRxPacket[i-packet_uart_3_exp+1]==1)//1是起始位
                    {
                        for (j=0;j<=packet_uart_3_exp-1;j++)
                        {
                            arm_3_gRxPacket_copy[j]=arm_3_gRxPacket[i-packet_uart_3_exp+1+j];
                        }
                        arm_3_cnt=0;
                        arm_3_packet_length=packet_uart_3_exp;
                        uart_arm_3_done=true;
//                  __BKPT();
//                        UART_Write(0, arm_1_gRxPacket_copy, arm_1_packet_length);
                    }
                
                if (packet_uart_3_exp==-1)
                {
                    memcpy(arm_3_gRxPacket_copy,arm_3_gRxPacket,arm_3_cnt);
                    arm_3_packet_length=arm_3_cnt;
                    uart_arm_3_done=true;
//                __BKPT();
//                    UART_Write(0, arm_1_gRxPacket_copy, arm_1_packet_length);
                    arm_3_cnt=0;
                }
                
                break;
              }
            break;
        default:
            __BKPT();
        break;
    }
}

void Uart_NVIC_init(void)
{
    NVIC_EnableIRQ(UART0_INT_IRQn);
    NVIC_EnableIRQ(UART1_INT_IRQn);
    NVIC_EnableIRQ(UART2_INT_IRQn);
    NVIC_EnableIRQ(UART3_INT_IRQn);
}

