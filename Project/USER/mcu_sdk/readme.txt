
��MCU_SDK�Ǹ���Ϳѻ����ƽ̨�϶���Ĳ�Ʒ���ܣ��Զ����ɵ�MCU���롣�ڴ˻����Ͻ����޸ġ����䣬�ɿ������MCU����

MCU_SDKʹ��ָ���ĵ����ӣ�
https://docs.tuya.com/zh/iot/device-development/access-mode-mcu/wifi-general-solution/software-reference-wifi/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9


�������裺

1����Ҫ���ݲ�Ʒʵ�������homekit������������wifi��ť��wifi״ָ̬ʾ�ƴ���ʽ���Ƿ�֧��MCU�����ȣ��������ã�����protocol.h���޸Ĵ����ã�

2����ֲ��MCU_SDK����鿴protocol.c�ļ��ڵ���ֲ����,����ȷ�����ֲ����ֲ������������·����������ϱ����ֵĴ��룬�������ȫ��wifi���ܡ�

3��tuya��dp���ݺ�homekit���������ݵĴ�����Ҫ�ֿ���������Ӱ�졣

4��Ϳѻģ���������֧��
Service.json�ļ�������homekit���������Ϣ��ʹ�ô��ļ����� Ϳѻģ��������ְ�װ·��/Config/Service.json �ļ��滻����������´�Ϳѻģ��������ּ��ɡ�

5���ļ�������
��MCU_SDK����10���ļ���

��1��system.c��system.h ��wifiͨ��Э�����ʵ�ִ��룬������������û�����Ҫ�޸ġ�

��2��mcu_api.c��mcu_api.h ���û���Ҫ�������õĺ������ڸ��ļ��ڡ�

��3��protocol.h��protocol.c �����յ�ģ�����ݺ�����ݵĴ����������ڴ��ļ����ҵ�����Ҫ�û��޸�������ع��ܡ�protocol.h ��protocol.c�ļ�������ϸ�޸�˵��������ϸ�Ķ���

��4��homekit.h��homekit.c ��homekit��ع���ʵ�ֺ��������ڴ��ļ����ҵ�������������Ҫ�û��޸����ƣ��û��ɸ�����Ҫ�����޸ġ�homekit.h ��homekit.c�ļ�������ϸ�޸�˵��������ϸ�Ķ���

��5��wifi.h�ļ��������������е�.h�ļ��������������������ļ��еĺ������õ��ĺ궨�壬ʹ�ô�SDK��غ�������#include "wifi.h"��

��6��tuya_type.h�ļ��������������͵Ķ��壬�������Ͷ���Ĭ�ϵ�Ƭ��Ϊ32λ�����û�ʹ�õĵ�Ƭ�����������ͣ����ڴ�ͷ�ļ������е����������͡�

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


This MCU_SDK is the MCU code automatically generated according to the product functions defined on the Tuya development platform. Modifications and supplements on this basis can quickly complete the MCU program.

MCU_SDK use guide document link:
https://docs.tuya.com/zh/iot/device-development/access-mode-mcu/wifi-general-solution/software-reference-wifi/overview-of-migrating-tuyas-mcu-sdk?id= K9hhi0xr5vll9


Development steps:

1: It needs to be configured according to the actual situation of the product (homekit function requirements, reset wifi button and wifi status indicator processing method, whether to support MCU upgrade, etc.), please modify this configuration in protocol.h;

2: To migrate this MCU_SDK, please check the migration steps in the protocol.c file and complete the migration correctly. After transplantation, please complete the code for data delivery processing and data reporting to complete all wifi functions.

3: The processing of tuya's dp data and homekit's characteristic data needs to be processed separately and does not affect each other.

4: Tuya module debugging assistant support
The Service.json file contains homekit service related information. Use this file to replace the Tuya module debugging assistant installation path/Config/Service.json file, and finally reopen the Tuya module debugging assistant.

5��File overview:
This MCU_SDK includes 10 files:

(1) system.c and system.h are wifi general protocol analysis implementation codes, no special circumstances, users do not need to modify.

(2) mcu_api.c and mcu_api.h, the functions that users need to call actively are in this file.

(3) Protocol.h and protocol.c, the data processing functions after receiving the module data, can be found in this file, and users need to modify and improve related functions. There are detailed modification instructions in the protocol.h and protocol.c files, please read them carefully.

(4) homekit.h and homekit.c, homekit-related functions can be found in this file, some of the content needs to be modified by the user, and the user can modify it as needed. There are detailed modification instructions in the homekit.h and homekit.c files, please read them carefully.

(5) The wifi.h file contains all the above .h files and defines the macro definitions used in the functions in all the above files. To use this SDK related function, please #include "wifi.h".

(6) The tuya_type.h file contains the definition of the data type. The data type definition defaults to 32-bit single-chip microcomputer. If the user uses another type of single-chip microcomputer, the data type can be adjusted in this header file.


