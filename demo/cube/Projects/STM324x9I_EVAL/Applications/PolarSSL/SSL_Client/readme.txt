/**
  @page SSL_Client SSL Client application
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    PolarSSL/SSL_Client/readme.txt 
  * @author  MCD Application Team
  * @version V1.4.5
  * @date    03-June-2016
  * @brief   Description of SSL Client application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright � 2016 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par Application Description 

This application guides STM32Cube HAL API users to run an SSL client application 
based on PolarSSL crypto library and LwIP TCP/IP stack

To off-load the CPU from encryption/decryption, hash and RNG, all these 
algorithms are implemented using the hardware acceleration AES 128/192/256, 
Triple DES, MD5, SHA-1 and analog RNG through the STM32Cube HAL APIs 

In this application the client (STM32439I-EVAL) sends a crypted message to the 
server (test PC), which will decrypt the message then reply to the client.

The HyperTerminal can be used to debug messages exchanged between client and 
server.

Note: In this application the Ethernet Link ISR need the System tick interrupt 
to configure the Ethernet MAC, so the Ethernet Link interrupt priority must be 
set lower (numerically greater) than the Systick interrupt priority to ensure 
that the System tick increments while executing the Ethernet Link ISR.

Note: By default, the Ethernet Half duplex mode is not supported in the 
STM324x9I-EVAL board, for more information refer to the HAL_ETH_MspInit() 
function in the ethernetif.c file

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in HAL time base ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the HAL time base interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the HAL time base interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the HAL time base is always set to 1 millisecond to have correct 
      HAL operation.

For more details about this application, refer to UM1723 "STM32Cube PolarSSL application".


@par Directory contents  

    - PolarSSL/SSL_Client/Inc/app_ethernet.h           header of app_ethernet.c file
    - PolarSSL/SSL_Client/Inc/ethernetif.h             header for ethernetif.c file
    - PolarSSL/SSL_Client/Inc/main.h                   Main program header file 
    - PolarSSL/SSL_Client/Inc/config.h                 PolarSSL library configuration options
    - PolarSSL/SSL_Client/Inc/FreeRTOSConfig.h         FreeRTOS configuration options
    - PolarSSL/SSL_Client/Inc/lwipopts.h               LwIP stack configuration options
    - PolarSSL/SSL_Client/Inc/stm32f4xx_it.h           Interrupt handlers header file 
    - PolarSSL/SSL_Client/Inc/stm32f4xx_hal_conf.h     Library Configuration file
    - PolarSSL/SSL_Client/Inc/ssl_client.h             header for ssl_client.c
    - PolarSSL/SSL_Client/Src/app_ethernet.c           Ethernet specific module
    - PolarSSL/SSL_Client/Src/main.c                   Main program
    - PolarSSL/SSL_Client/Src/ssl_client.c             SSL client main thread
    - PolarSSL/SSL_Client/Src/ethernetif.c             Interfacing the LwIP stack to ETH driver
    - PolarSSL/SSL_Client/Src/stm32f4xx_hal_msp.c      HAL MSP module
    - PolarSSL/SSL_Client/Src/stm32f4xx_it.c           Interrupt handlers 
    - PolarSSL/SSL_Client/Src/system_stm32f4xx.c       STM32 system clock configuration file


@par Hardware and Software environment  

  - This application runs on STM32F439xx Devices.
  
  - This application has been tested with the following environments: 
     - STM32439I-EVAL board RevB
     - ssl_server.exe: PC utility is used as SSL server application
        This utility is provided within STM32CubeF4 package under "/Utilities/PC_Software/ssl_server"             
     - DHCP server: PC utility TFTPD32 (http://tftpd32.jounin.net/) is used as a DHCP server 
     - HyperTerminal: used to display debug messages
  
  - STM32439I-EVAL Set-up 
    - Connect STM32439I-EVAL board to remote PC (through a crossover ethernet cable)
      or to your local network (through a straight ethernet cable)
    - RS232 link (used with HyperTerminal like application to display debug messages):
      connect a null-modem female/female RS232 cable between the DB9 connector 
      CN8 (USART1) and PC serial port.

  - Remote PC Set-up
    - Configure a static IP address for your remote PC 
      this address must be as defined in ssl_client.c: 192.168.0.1 by default 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the application

 @Note: 1 Please ensure that the remote PC IP address is the same IP address 
          as the one defined in ssl_client.c file
          (#define SSL_SERVER_NAME "192.168.0.1").
      
        2 If you using a firewall, you must be sure that ssl_server application
          accepts connection requests. Otherwise, the firewall refuses the 
          client requests.
 
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
