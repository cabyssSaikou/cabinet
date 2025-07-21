#include "ti_msp_dl_config.h"
#include <string.h>
#include "drv_uart/drv_uart.h"
#include "arm_controller/arm_controller.h"

long int timing[10]={-1};
//任务触发时间，类似于freertos的,并且时间也影响pid控制，特别是增量型pid
//-1表示未启用

bool flag;//指示数据有没有出错 出错为false

int get_int_u(char *hc05_dat,int begin,int max);
int get_int(char *hc05_dat,int begin,int len);


int get_int(char *hc05_dat,int begin,int len)
{
    int t_int,i;
    t_int=0;
    for (i=begin;i<=begin+len-1;i++)
        {
            if (hc05_dat[i]<='9' && hc05_dat[i]>='0' )
                t_int=(hc05_dat[i]-'0')+t_int*10;
            else
            {
                UART_Write(0, "data error\n", 11);
                flag=false;
                return t_int;
            }
        }
    return t_int;
}
int get_int_u(char *hc05_dat,int begin,int max)
{
    int t_int,i;
    t_int=0;
    i=0;
    while(hc05_dat[i]<='9' && hc05_dat[i]>='0'&& i<begin+max)
    {
        
        if (hc05_dat[i]>'9' && hc05_dat[i]<'0')
        {
            UART_Write(0, "data error\n", 11);
            flag=false;
            return t_int;
        }
        else
        {
            t_int=(hc05_dat[i]-'0')+t_int*10;
            i++;
        }
    }
    return t_int;
}

void HC05_server(char *hc05_dat,int p_begin,int p_end)
{
    int i,t_int_1,t_int_2;
    bool sign;
//    double t_double,t_double_2;
    flag=true;
    UART_Write(0,hc05_dat, p_end);
    if(hc05_dat[0]==0x01)//直接给步进电机指令
    {
        UART_Write(1, hc05_dat, p_end);
        __BKPT();
    }
    if(hc05_dat[0]=='/')
    switch(hc05_dat[1])
    {
        case 'p':
            i=3;
            t_int_1=0;
            t_int_2=0;
            if (hc05_dat[i]=='-')
            {
                sign=true;
                i++;
            }
            else
                sign=false;
            while (hc05_dat[i]<='9' && hc05_dat[i]>='0')
            {
               t_int_1=(hc05_dat[i]-'0')+t_int_1*10;
                i++;
            }
            if (sign)
                t_int_1=t_int_1*-1;
            i++;
        
            if (hc05_dat[i]=='-')
            {
                sign=true;
                i++;
            }
            else
                sign=false;
            while (hc05_dat[i]<='9' && hc05_dat[i]>='0')
            {
                t_int_2=(hc05_dat[i]-'0')+t_int_2*10;
                i++;
            }
            if (sign)
                t_int_2=t_int_2*-1;
        
        
            arm_server((double) t_int_1, (double) t_int_2);
            UART_Write(0, "x=", 3);
            UART_Write_num(0, t_int_1, 4);
            UART_Write(0, "y=", 3);
            UART_Write_num(0, t_int_2, 4);
            UART_Write(0, "set success.\n", 13);
            break;
        case 'u':
            i=3;
            t_int_1=0;
            if (hc05_dat[i]=='-')
            {
                sign=true;
                i++;
            }
            else
                sign=false;
            while (hc05_dat[i]<='9' && hc05_dat[i]>='0')
            {
               t_int_1=(hc05_dat[i]-'0')+t_int_1*10;
                i++;
            }
            if (sign)
                t_int_1=t_int_1*-1;
            i++;
            if (t_int_1==0)
                t_int_1=15;
//            height_server((double)t_int_1);
            UART_Write_num(0, t_int_1, 4);
            UART_Write(0, " pull up success.\n", 18);
        break;
        case 'd':
            i=3;
            t_int_1=0;
            if (hc05_dat[i]=='-')
            {
                sign=true;
                i++;
            }
            else
                sign=false;
            while (hc05_dat[i]<='9' && hc05_dat[i]>='0')
            {
               t_int_1=(hc05_dat[i]-'0')+t_int_1*10;
                i++;
            }
            if (sign)
                t_int_1=t_int_1*-1;
            i++;
            height_server((double)t_int_1);
            UART_Write_num(0, t_int_1, 4);
            UART_Write(0, " drop success.\n", 15);
        break;
        default:
//        __BKPT();
        break;
    }
}






