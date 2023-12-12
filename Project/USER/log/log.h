#ifndef _LOG_H_
#define _LOG_H_

typedef enum
{
    SYS_CODE_BASE = 0x000, /* 系统代码 */
    ACT_CODE_BASE = 0x100, /* 动作代码 */
    ACT_CLOCK,             // 闹钟动作
    ACT_KEY,               // 按键动作
    ACT_LISTPLAY,          // 列表播放
    ERR_CODE_BASE = 0x200, /* 错误代码 */
} LOG_CODE;

#endif
