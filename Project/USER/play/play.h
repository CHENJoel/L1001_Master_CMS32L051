#ifndef _PLAY_H
#define _PLAY_H
#include "Function_Init.H"

#include "L0_slave.h"
#define DMA_BUFFER_SIZE (SLAVEDEVICE_NUM * sizeof(playdata_Typedef) + sizeof(packhead_Typedef))
#define NULL_EFFECTNUM 0xFF // 无效灯效编号

// // // extern uint8_t dma_buffer[DMA_BUFFER_SIZE];
extern const uint8_t bright_table[5];




typedef enum
{
    PLAYING_MODE,   // 正常播放模式
    PAIRING_MODE,   // 灯板配对模式
    PREVIEW_MODE,   // 灯效预览模式
} control_mode_enum; /*控制模式*/


typedef enum
{
    SOURCE_LIST,   // 列表播放
    SOURCE_FREE,   // 自由播放
} playsource_enum; /*播放源*/

typedef enum
{
    PLAY_IN_SEQUENCE, // 顺序播放
    PLAY_IN_RANDOM,   // 随机播放
} PlayMode_enum;      /*播放模式*/

typedef enum
{
    CYCLE_IN_ONCE, // 单次列表
    CYCLE_IN_LOOP, // 循环播放
} CycleMode_enum;  /*循环模式*/

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
    uint8_t listindex;               // 当前播放列表索引号
    uint8_t efindex;                 // 当前播放灯效索引
    time_MS_TypeDef duration;        // 持续时循环的模式间
    uint8_t listefsum;               /* 灯效列表中有效数据的数量 */
    uint8_t idex_inlist;             // 当前灯效在列表中的序号（指针）
    uint8_t list[PlayList_efMaxNum]; /* 灯效列表 */
    uint8_t history[32];             // 保存最近播放的灯效记录 可删掉

} play_minidetail_TypeDef; /*播放列表详情*/

typedef enum
{
    SW_OFF, // 关灯
    SW_ON,  // 开灯
} sw_status_enum;

typedef struct
{
    uint8_t now;   // 当前值
    uint8_t tar;   // 目标值
    uint8_t set;   // 存储值
    uint8_t dir;   // 方向
} NTSD_VAL_TypeDef;

typedef enum
{
    RHYTHM_OFF,
    RHYTHM_ON,
} rhythm_enum;

typedef struct
{
    sw_status_enum sw_status;              // 全局开关
    NTSD_VAL_TypeDef brightness;           // 全局亮度
    global_setting_TypeDef global_setting; // 全局设置 断电存储
    uint32_t playtime_cnt;                 // 当前已播放时间
    rhythm_enum rhythm_sta;                // 律动开关
} playwork_TypeDef;                        //

typedef struct
{
    uint8_t playindex; // 当前播放在表中的序号
    uint8_t listsize;
    uint8_t list[PlayList_efMaxNum];
}playorder_TypeDef;


typedef enum
{
    NO_CLOCK,   // 当前无执行闹钟
    CLOCK_ON,   // 当前有执行闹钟
}clock_status_enum;

typedef struct
{
    clock_status_enum status;   // 闹钟状态
    uint8_t ef_index;           // 灯效索引
    uint8_t bright;             // 当前亮度
    action_enum action;         // 动作类型
    uint8_t ultimatebright;     // 最终亮度
    time_HM_TypeDef actiontime; // 动作时间
    time_HM_TypeDef duration;   // 持续时间
    repeat_TypeDef repeat;      // 星期计划
    uint8_t action_day;         // 执行日期
} clock_task_TypeDef;

typedef struct
{
    control_mode_enum control_mode; // 控制模式
    playsource_enum source;         // 播放源
    playwork_TypeDef work;
    PlayMode_enum playmode;         // 播放模式
    CycleMode_enum cyclemode;       // 循环模式
    playstatus_enum status;         // 播放状态
    play_minidetail_TypeDef detail; // 播放详情信息
    Efdetail_TypeDef efdetail;      // 当前灯效信息
    clock_task_TypeDef clock;
} play_TypeDef;

extern play_TypeDef play;


/*-----------------------------------------------------------*/
// typedef struct
// {
//     uint8_t brightness;    // 默认亮度
//     uint8_t color_sum;     // 色表中颜色数量 值0代表该灯效未启用
//     Motion_TypeDef motion; // 动效编号,静态/呼吸/流动/来回/跳动/闪电/点燃/随机 0~7
//     Move_TypeDef move;     // 运动方向编号,向上/向下/向左/向右/四周发散/中心汇聚 0~5
//     MODE_TypeDef Mode;     // 普通/律动
//     uint8_t speed;         // 运动速度
//     uint8_t RESERVED[2];   // 空间保留
// } parabuf_TypeDeff;    // 8byte
// typedef struct
// {
//     EF_para_data_TypeDef User_EF_Param[64]; // 灯效的参数,前30为内置灯效的参数，后30为自定义灯效的参数,其余为备用
// } UserEFparadata_TypeDef;

// typedef struct
// {
//     RGBWInf_TypeDef data[EfColor_SizeNum]; // 每个灯效最多包含16个颜色
// } colorbuf_TypeDef;

// typedef struct
// {
//     colorbuf_TypeDef color;
//     parabuf_TypeDeff para;
// } playbuf_TypeDef;


extern Efdetail_TypeDef playbuf;











/*------------------------------------------------------------*/
/*切换灯效*/
uint8_t switch_effect(uint8_t efnum);
/*切换上下灯效*/
uint8_t switch_lastnext_effect(switchplay_enum num);

/*在列表中播放下一灯效*/
void switch_next_ef_in_list(void);
/*在列表中播放上一灯效*/
void switch_last_ef_in_list(void);
/* 切换播放列表 */
uint8_t switch_playlist(uint8_t listnum);
//
void switch_playmode(PlayMode_enum mod);   // 切换播放模式
void switch_cyclemode(CycleMode_enum mod); // 切换循环模式
//

/*播放初始化*/
void play_init(void);
/*新增历史播放灯效*/
void push_playnum_in_history(uint8_t efnum);

/*
 * @Description: 取出历史播放灯效
 * @param:
 * @return:
*/
uint8_t pop_playnum_in_history(void);

//
void enter_device_pairing_mode(void);                       // 进入灯板配对模式
void enter_playing_effect_mode(void);                       // 进入正常播放灯效模式
void enter_preview_effect_mode(Efdetail_TypeDef *efdetail); // 进入预览灯效模式
void exit_preview_effect_mode(void);                        // 退出预览灯效模式
//

/*在表中获取下一个元素*/
uint8_t get_list_next_num(uint8_t *list, uint8_t size, uint8_t num);


/*
 * @Description: 暂停播放灯效
 * @param:
 * @return:
*/
void effect_play_pause(void);
/*
 * @Description: 继续播放灯效
 * @param:
 * @return:
 */
void resume_play_effect(void);
/***************************/
//
void load_local_effect_data(void);                         // 加载本地灯效信息
void load_preview_effect_data(Efdetail_TypeDef *efdetail); // 加载预览灯效信息
//
/*复位播放帧进度*/
void play_frame_reset(void);
/*系统播放灯效初始化*/
void play_sys_effect_init(void);
/*生成该灯效的动画缓存*/
void generate_play_video_buffer(void);
/*根据方向计算出从机的运行编号*/
void figure_slave_run_number_in_direction(Direction_Enum dir);
/*发送从机播放数据*/
// // void transmit_slave_play_data(void);
/*所有灯点亮同个颜色*/
void play_color_in_all_salve_light(uint8_t bri, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
/*关闭所有灯板*/
void turn_off_all_salve_light(void);

/*播放灯效*/
void play_effect_video(void);
//
void play_current_effect(void);                       // 从头开始播放当前灯效
void play_free_effect(uint8_t efnum);                 // 播放自由灯效
void play_new_effect(uint8_t efnum);                  // 播放新灯效
void play_preview_effect(Efdetail_TypeDef *efdetail); // 播放预览灯效
//
void preprocess_play_effect(void); // 预处理播放数据
/***********************************************************************/

void transmit_playdata_RGBbr(void);                    // 发送“RGBbr”格式的播放数据
void transmit_playdata_COLOR(void); // 发送“COLOR”格式的播放数据
void transmit_playsame_RGBbr(L0_playRGBbr_Typedef *x); // 广播发送“RGBbr”格式的播放数据

void transmit_play_fft(void); //测试显示fft
//void light_device_pairing_play(app_device_control_Typedef *x); //灯板显示配对状态

//
void permute_list_in_random(uint8_t *list, uint8_t size);                          // 重新随机排列列表内的数据
uint8_t move_data_to_first_in_list(uint8_t data, uint8_t *list, uint8_t listsize); // 将某数从列表中挪至第一项
void adjust_play_list(void);                                                       // 调整播放顺序
void invert_list(uint8_t *list, uint8_t size);                                     // 将原数组倒序排列
void start_play_list(uint8_t listindex);                                           // 开始播放一个列表
void end_play_list(void);                                                          // 结束列表播放
void reload_current_play_list(void);                                               // 重新加载当前播放列表
//
#endif
