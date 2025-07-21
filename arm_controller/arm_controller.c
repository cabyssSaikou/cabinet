#include "ti_msp_dl_config.h"
#include "drv_uart/drv_uart.h"
#include <math.h>

double offset_x_act=0.0,offset_y_act=0.0,m_x,m_y;//基座中点相对于坐标系原点的偏移值 取向右为x正 向前为y正
int offset_x_ang=0,offset_y_ang=0;
const double min_limit=2500.0,max_limit=360000.0;//mm^2
const double x_min_limit=-600.0,x_max_limit=600.0;//mm
const double y_min_limit=40.0,y_max_limit=600.0;//mm
const double arm_1_len=300.0,arm_2_len=300.0;//大臂 小臂的长度
int packet_uart_1_exp=-1,packet_uart_2_exp=-1,packet_uart_3_exp=-1;//每次使用时都需要手动置位
int v;
long t_int_1,t_int_2;

double angle_1,angle_2;

char arm_1_gRxPacket[40];
char arm_1_gRxPacket_copy[40];
char arm_2_gRxPacket[40];
char arm_2_gRxPacket_copy[40];
char arm_3_gRxPacket[40];
char arm_3_gRxPacket_copy[40];
char data_arm_1[13]={0x01 ,0xFD ,0X01 ,0X00,0X00 ,0X00, 0X00,0X00,0X00,0X00, 0X01,0X00,0X6B};
char data_arm_2[13]={0x01 ,0xFD ,0X01 ,0X00,0X00 ,0X00, 0X00,0X00,0X00,0X00, 0X01,0X00,0X6B};
bool uart_hc05_tx_pro,uart_arm_1_tx_pro,uart_arm_2_tx_pro,uart_arm_3_tx_pro;

bool position_flag=false,height_flag=false;
long position_count,height_count;
int position_set_x,position_set_y,position_set_z;//设定的机械臂x位置 y z
long count;
//还是0x68校验好了
void cmd_arm_1_position_set(int position,int speed)
{
    data_arm_1[4]=speed%256;
    data_arm_1[3]=speed/256%256;

    data_arm_1[9]=position%256;
    data_arm_1[8]=position/256%256;
    data_arm_1[7]=position/65536%256;
    data_arm_1[6]=position/16777216%256;

    packet_uart_1_exp=4;
    
    while(uart_hc05_tx_pro || uart_arm_1_tx_pro || uart_arm_2_tx_pro || uart_arm_3_tx_pro);
    UART_Write(1, data_arm_1, 13);
//    __BKPT();
}

void cmd_arm_2_position_set(int position,int speed)
{
    data_arm_2[4]=speed%256;
    data_arm_2[3]=speed/256%256;

    data_arm_2[9]=position%256;
    data_arm_2[8]=position/256%256;
    data_arm_2[7]=position/65536%256;
    data_arm_2[6]=position/16777216%256;

    packet_uart_2_exp=4;
    
    while(uart_hc05_tx_pro || uart_arm_1_tx_pro || uart_arm_2_tx_pro || uart_arm_3_tx_pro);
    UART_Write(2, data_arm_2, 13);
//    __BKPT();
}

int cmd_arm_xy_position_detect(int tick)
{
    //数据包格式
    char tx_data_1[3]={0x01,0x37,0x6B};
    char tx_data_2[3]={0x01,0x37,0x6B};

    t_int_1=10086;
    t_int_2=10086;
    //给大臂电机发数据包
    uart_arm_1_done=true;
    uart_arm_2_done=false;
    while(uart_hc05_tx_pro || uart_arm_1_tx_pro || uart_arm_2_tx_pro || uart_arm_3_tx_pro);
    packet_uart_2_exp=8;
//    __BKPT();
    UART_Write(2, tx_data_2, 3);

    uart_arm_1_done=false;
    uart_arm_2_done=true;
    while(uart_hc05_tx_pro || uart_arm_1_tx_pro || uart_arm_2_tx_pro || uart_arm_3_tx_pro);

    packet_uart_1_exp=8;
    UART_Write(1, tx_data_1, 3);
    while (!uart_arm_1_done && !uart_arm_2_done);

//    __BKPT();
//    uart_arm_2_done=true;//手动设置
    while (!uart_arm_1_done && !uart_arm_2_done);
    //处理数据
    if (arm_1_gRxPacket_copy[7]==107)
    {
        t_int_1=arm_1_gRxPacket_copy[6]+arm_1_gRxPacket_copy[5]*256+arm_1_gRxPacket_copy[4]*65536+arm_1_gRxPacket_copy[3]*16777216;
    }
    
    if (arm_2_gRxPacket_copy[7]==107)
        t_int_2=arm_2_gRxPacket_copy[6]+arm_2_gRxPacket_copy[5]*256+arm_2_gRxPacket_copy[4]*65536+arm_2_gRxPacket_copy[3]*16777216;
    v=t_int_2;
    //位置数据为position_set_x position_set_y
    if (t_int_1<10 && t_int_2<10)
        return 1;
    if (tick>30)//超时
    {
        UART_Write(0, "Time Limit Exceeded.\n", 21);
        return -1;
    }
    else
    {
//        __BKPT();
        return 0;
    }
}

int cmd_arm_z_position_detect(int tick)
{
    //数据包格式
    char tx_data[3]={0x01,0x37,0x6B};
    long t_int_3;
    t_int_3=10086;
    //给大臂电机发数据包
    UART_Write(3, tx_data, 3);
    packet_uart_3_exp=8;//数据包总长
    while (!uart_arm_3_done);
    //处理数据
    if (arm_3_gRxPacket_copy[7]==0x6B)
        t_int_3=arm_3_gRxPacket_copy[6]+arm_3_gRxPacket_copy[5]*256+arm_3_gRxPacket_copy[4]*65536+arm_3_gRxPacket_copy[3]*16777216;
    
    //位置数据为position_set_x position_set_y
    if (t_int_3<10 && t_int_3>-10)
    {
        UART_Write(0, "height reached.\n", 14);
        return 1;
    }
    if (tick>150)//超时
    {
        UART_Write(0, "Time Limit Exceeded.\n", 21);
        return -1;
    }
    else 
        return 0;
}

//解算相关的函数
void arm_server(double x_act,double y_act)
{
    double x,y,H_x,H_y,k,d,arm_mul;
    arm_mul=arm_1_len/arm_2_len;
    x=x_act-offset_x_act;
    y=y_act-offset_y_act;
    if (x*x+y*y<min_limit ||x*x+y*y>max_limit)
    {
        UART_Write(0, "limited\n", 10);
        return;
    }
    if (x<x_min_limit ||x>x_max_limit)
    {
        UART_Write(0, "x limited\n", 10);
        return;
    }
    if (y<y_min_limit ||y>y_max_limit)
    {
        UART_Write(0, "y limited\n", 10);
        return;
    }
    H_x=x*arm_mul/(arm_mul+1.0);
    H_y=y*arm_mul/(arm_mul+1.0);
    k=-1.0*x/y;
    d=arm_1_len*arm_1_len-H_x*H_x-H_y*H_y;//垂足到连接点距离的平方
    d=sqrt(d);
    m_x=H_x+d*1.0/sqrt(1.0+k*k);//正负值各有一个 取正值
    m_y=H_y+d*k/sqrt(1.0+k*k);
    
    //10~+170
    angle_1=atan2((double)(m_y-0.0),(double)(m_x-0.0))*57.29578;
    //360
    angle_2=atan2((double)(y-m_y),(double)(x-m_x))*57.29578;

//    __BKPT();
    //先以默认速度跑 后面再考虑做线性
    while(uart_hc05_tx_pro || uart_arm_1_tx_pro || uart_arm_2_tx_pro || uart_arm_3_tx_pro);
    cmd_arm_2_position_set((int)(angle_2*10*6)+offset_y_ang,300);//6是减速比
    while(uart_hc05_tx_pro || uart_arm_1_tx_pro || uart_arm_2_tx_pro || uart_arm_3_tx_pro);
    cmd_arm_1_position_set((int)(angle_1*10*6)+offset_x_ang,300);//6是减速比
    
    
    //开监听判断是否已到达位置
    position_flag=true;
    position_count=count;
    
    
}

void height_server(double h)
{
   //一圈是3200
    const int speed=1500;
    int position;
    position=(int)(h*5.0*3200);
    static char data[13]={0x01 ,0xFD ,0X01 ,0X00,0X00 ,0X00, 0X00,0X00,0X00,0X00, 0X00,0X00,0X6B};

    data[4]=speed%256;
    data[3]=speed/256%256;

    data[10]=0x01;

    data[9]=position%256;
    data[8]=position/256%256;
    data[7]=position/65536%256;
    data[6]=position/16777216%256;

    packet_uart_3_exp=4;
    UART_Write(3, data, 13);
    
    height_flag=true;
    height_count=count;

}
