/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "arm_controller/arm_controller.h"
#include "eye_uart/hc05.h"
#include "eye_uart/hc05_reqserver.h"
#include "drv_uart/drv_uart.h"

int flash_flag;
long count_2;

int main(void)
{
    int t;
    t=0;
    SYSCFG_DL_init();

    //开uart串口中断
    Uart_NVIC_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
//    DL_SYSCTL_enableSleepOnExit();

    count=0;
    count_2=0;
    DL_TimerA_startCounter(TIMER_0_INST);
    UART_Write(0, "ready.\n", 7);
    uart_hc05_done=false;
    arm_1_cnt=0;
    arm_2_cnt=0;
    arm_3_cnt=0;

    while (1) 
    {
      if (flash_flag!=0)
      {
//        __BKPT();
        if (uart_hc05_done)
        {
            HC05_server(HC05_gRxPacket_copy,0,HC05_packet_length);
            uart_hc05_done=false;
        }
        flash_flag=0;
        if (position_flag)//监听机械臂位置
        {
            t=cmd_arm_xy_position_detect(count-position_count);
            if (t!=0)
            {
                position_flag=false;
                UART_Write(0,"xy reached.\n",12);
//                __BKPT();
            }
        }
        if (height_flag)//监听高度位置
        {
            t=cmd_arm_z_position_detect(count-height_count);
            if (t!=0)
            {
                height_flag=false;
                UART_Write(0,"z reached.\n",11);
//                __BKPT();
            }
        }
        
        
      }
        //delay 100ms
//        for (o=1;o<=720;o++);
//          count_2++;
    }
}

void TIMER_0_INST_IRQHandler(void)
{
    switch (DL_TimerA_getPendingInterrupt(TIMER_0_INST)) 
    {
        case DL_TIMERA_IIDX_REPEAT_COUNT:
        {
            count++;
            count=count%2147483647;
            flash_flag=1;
//            uart_hc05_done=false;
//            uart_arm_1_done=false;//防止卡死
//            uart_arm_2_done=false;
//            uart_arm_3_done=false;
            break;
        }
        default:
            break;
    }
}

