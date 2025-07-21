/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (4687U)
#define TIMER_0_REPEAT_COUNT_2                                               (1)



/* Defines for UART_eye */
#define UART_eye_INST                                                      UART0
#define UART_eye_INST_IRQHandler                                UART0_IRQHandler
#define UART_eye_INST_INT_IRQN                                    UART0_INT_IRQn
#define GPIO_UART_eye_RX_PORT                                              GPIOB
#define GPIO_UART_eye_TX_PORT                                              GPIOB
#define GPIO_UART_eye_RX_PIN                                       DL_GPIO_PIN_1
#define GPIO_UART_eye_TX_PIN                                       DL_GPIO_PIN_0
#define GPIO_UART_eye_IOMUX_RX                                   (IOMUX_PINCM13)
#define GPIO_UART_eye_IOMUX_TX                                   (IOMUX_PINCM12)
#define GPIO_UART_eye_IOMUX_RX_FUNC                    IOMUX_PINCM13_PF_UART0_RX
#define GPIO_UART_eye_IOMUX_TX_FUNC                    IOMUX_PINCM12_PF_UART0_TX
#define UART_eye_BAUD_RATE                                              (115200)
#define UART_eye_IBRD_32_MHZ_115200_BAUD                                    (17)
#define UART_eye_FBRD_32_MHZ_115200_BAUD                                    (23)
/* Defines for UART_arm_1 */
#define UART_arm_1_INST                                                    UART1
#define UART_arm_1_INST_IRQHandler                              UART1_IRQHandler
#define UART_arm_1_INST_INT_IRQN                                  UART1_INT_IRQn
#define GPIO_UART_arm_1_RX_PORT                                            GPIOA
#define GPIO_UART_arm_1_TX_PORT                                            GPIOA
#define GPIO_UART_arm_1_RX_PIN                                    DL_GPIO_PIN_18
#define GPIO_UART_arm_1_TX_PIN                                    DL_GPIO_PIN_17
#define GPIO_UART_arm_1_IOMUX_RX                                 (IOMUX_PINCM40)
#define GPIO_UART_arm_1_IOMUX_TX                                 (IOMUX_PINCM39)
#define GPIO_UART_arm_1_IOMUX_RX_FUNC                  IOMUX_PINCM40_PF_UART1_RX
#define GPIO_UART_arm_1_IOMUX_TX_FUNC                  IOMUX_PINCM39_PF_UART1_TX
#define UART_arm_1_BAUD_RATE                                            (115200)
#define UART_arm_1_IBRD_32_MHZ_115200_BAUD                                  (17)
#define UART_arm_1_FBRD_32_MHZ_115200_BAUD                                  (23)
/* Defines for UART_arm_2 */
#define UART_arm_2_INST                                                    UART2
#define UART_arm_2_INST_IRQHandler                              UART2_IRQHandler
#define UART_arm_2_INST_INT_IRQN                                  UART2_INT_IRQn
#define GPIO_UART_arm_2_RX_PORT                                            GPIOA
#define GPIO_UART_arm_2_TX_PORT                                            GPIOB
#define GPIO_UART_arm_2_RX_PIN                                    DL_GPIO_PIN_24
#define GPIO_UART_arm_2_TX_PIN                                    DL_GPIO_PIN_17
#define GPIO_UART_arm_2_IOMUX_RX                                 (IOMUX_PINCM54)
#define GPIO_UART_arm_2_IOMUX_TX                                 (IOMUX_PINCM43)
#define GPIO_UART_arm_2_IOMUX_RX_FUNC                  IOMUX_PINCM54_PF_UART2_RX
#define GPIO_UART_arm_2_IOMUX_TX_FUNC                  IOMUX_PINCM43_PF_UART2_TX
#define UART_arm_2_BAUD_RATE                                            (115200)
#define UART_arm_2_IBRD_32_MHZ_115200_BAUD                                  (17)
#define UART_arm_2_FBRD_32_MHZ_115200_BAUD                                  (23)
/* Defines for UART_arm_3 */
#define UART_arm_3_INST                                                    UART3
#define UART_arm_3_INST_IRQHandler                              UART3_IRQHandler
#define UART_arm_3_INST_INT_IRQN                                  UART3_INT_IRQn
#define GPIO_UART_arm_3_RX_PORT                                            GPIOA
#define GPIO_UART_arm_3_TX_PORT                                            GPIOA
#define GPIO_UART_arm_3_RX_PIN                                    DL_GPIO_PIN_13
#define GPIO_UART_arm_3_TX_PIN                                    DL_GPIO_PIN_14
#define GPIO_UART_arm_3_IOMUX_RX                                 (IOMUX_PINCM35)
#define GPIO_UART_arm_3_IOMUX_TX                                 (IOMUX_PINCM36)
#define GPIO_UART_arm_3_IOMUX_RX_FUNC                  IOMUX_PINCM35_PF_UART3_RX
#define GPIO_UART_arm_3_IOMUX_TX_FUNC                  IOMUX_PINCM36_PF_UART3_TX
#define UART_arm_3_BAUD_RATE                                            (115200)
#define UART_arm_3_IBRD_32_MHZ_115200_BAUD                                  (17)
#define UART_arm_3_FBRD_32_MHZ_115200_BAUD                                  (23)




/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_UART_eye_init(void);
void SYSCFG_DL_UART_arm_1_init(void);
void SYSCFG_DL_UART_arm_2_init(void);
void SYSCFG_DL_UART_arm_3_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
