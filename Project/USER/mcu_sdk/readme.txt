
此MCU_SDK是根据涂鸦开发平台上定义的产品功能，自动生成的MCU代码。在此基础上进行修改、补充，可快速完成MCU程序。

MCU_SDK使用指导文档链接：
https://docs.tuya.com/zh/iot/device-development/access-mode-mcu/wifi-general-solution/software-reference-wifi/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9


开发步骤：

1：需要根据产品实际情况（homekit功能需求、重置wifi按钮和wifi状态指示灯处理方式、是否支持MCU升级等）进行配置，请在protocol.h内修改此配置；

2：移植此MCU_SDK，请查看protocol.c文件内的移植步骤,并正确完成移植。移植后，请完成数据下发处理、数据上报部分的代码，即可完成全部wifi功能。

3：tuya的dp数据和homekit的特性数据的处理，需要分开处理，互不影响。

4：涂鸦模组调试助手支持
Service.json文件包含有homekit服务相关信息，使用此文件，把 涂鸦模组调试助手安装路径/Config/Service.json 文件替换掉，最后重新打开涂鸦模组调试助手即可。

5：文件概览：
此MCU_SDK包括10个文件：

（1）system.c和system.h 是wifi通用协议解析实现代码，无特殊情况，用户不需要修改。

（2）mcu_api.c和mcu_api.h ，用户需要主动调用的函数都在该文件内。

（3）protocol.h和protocol.c ，接收到模块数据后对数据的处理函数，可在此文件内找到，需要用户修改完善相关功能。protocol.h 和protocol.c文件内有详细修改说明，请仔细阅读。

（4）homekit.h和homekit.c ，homekit相关功能实现函数，可在此文件内找到，部分内容需要用户修改完善，用户可根据需要自行修改。homekit.h 和homekit.c文件内有详细修改说明，请仔细阅读。

（5）wifi.h文件包含了以上所有的.h文件，并定义了以上所有文件中的函数里用到的宏定义，使用此SDK相关函数，请#include "wifi.h"。

（6）tuya_type.h文件包含了数据类型的定义，数据类型定义默认单片机为32位，若用户使用的单片机是其他类型，可在此头文件中自行调整数据类型。

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

5：File overview:
This MCU_SDK includes 10 files:

(1) system.c and system.h are wifi general protocol analysis implementation codes, no special circumstances, users do not need to modify.

(2) mcu_api.c and mcu_api.h, the functions that users need to call actively are in this file.

(3) Protocol.h and protocol.c, the data processing functions after receiving the module data, can be found in this file, and users need to modify and improve related functions. There are detailed modification instructions in the protocol.h and protocol.c files, please read them carefully.

(4) homekit.h and homekit.c, homekit-related functions can be found in this file, some of the content needs to be modified by the user, and the user can modify it as needed. There are detailed modification instructions in the homekit.h and homekit.c files, please read them carefully.

(5) The wifi.h file contains all the above .h files and defines the macro definitions used in the functions in all the above files. To use this SDK related function, please #include "wifi.h".

(6) The tuya_type.h file contains the definition of the data type. The data type definition defaults to 32-bit single-chip microcomputer. If the user uses another type of single-chip microcomputer, the data type can be adjusted in this header file.


