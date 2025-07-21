#ifndef __arm_controller_H
#define __arm_controller_H


extern bool position_flag,height_flag;
extern long position_count,height_count;
extern bool position_return_flag,height_return_flag;
extern char arm_1_gRxPacket[40];
extern char arm_1_gRxPacket_copy[40];
extern char arm_2_gRxPacket[40];
extern char arm_2_gRxPacket_copy[40];
extern char arm_3_gRxPacket[40];
extern char arm_3_gRxPacket_copy[40];
extern int count;
extern int packet_uart_1_exp,packet_uart_2_exp,packet_uart_3_exp;
extern int v;
extern bool uart_hc05_tx_pro,uart_arm_1_tx_pro,uart_arm_2_tx_pro,uart_arm_3_tx_pro;

void cmd_arm_1_position_set(int position,int speed);
void cmd_arm_2_position_set(int position,int speed);
int cmd_arm_xy_position_detect(int tick);
int cmd_arm_z_position_detect(int tick);
void arm_server(double x_act,double y_act);
void height_server(double h);


#endif
