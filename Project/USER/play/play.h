#ifndef _PLAY_H
#define _PLAY_H
#include "Function_Init.H"

#define NULL_EFFECTNUM 0xFF // 无效灯效编号

typedef enum
{
    RANDOM_MODE, // 随机播放
    LOOP_MODE,   // 循环播放
} playmode_enum; /*播放循环模式*/

typedef enum
{
    PAUSE, // 暂停
    RUN,   // 运行
} playstatus_enum;

typedef enum
{
    LAST_EFFECT, // 上一个灯效
    NEXT_EFFECT, // 下一个灯效
} switchplay_enum;

typedef struct /*  */
{
    uint8_t listnum;                // 当前播放列表索引号
    uint8_t efnum;                  // 当前播放灯效索引
    time_TypeDef duration;          // 持续时间
    uint8_t num;                    /* 灯效列表中有效数据的数量 */
    uint8_t list[PlayList_SizeNum]; /* 灯效列表 */
    uint8_t history[10];         // 保存最近播放的灯效记录
} play_minidetail_TypeDef;          /*播放列表详情*/

typedef struct
{
    playmode_enum mode;             // 播放模式
    playstatus_enum status;         // 播放状态
    play_minidetail_TypeDef detail; // 播放详情信息
} play_TypeDef;

extern play_TypeDef play;

/*切换灯效*/
uint8_t switch_effect(uint8_t efnum);
/*切换上下灯效*/
uint8_t switch_ln_effect(switchplay_enum num);
/* 切换播放列表 */
uint8_t switch_playlist(uint8_t listnum);
/*播放初始化*/
void play_init(void);
/*在表中新增灯效编号*/
void add_num_in_list(uint8_t efnum);
/*在表中获取下一个元素*/
uint8_t get_list_next_num(uint8_t *list, uint8_t size, uint8_t num);
#endif
