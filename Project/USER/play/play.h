#ifndef _PLAY_H
#define _PLAY_H
#include "Function_Init.H"
#define DMA_BUFFER_SIZE (SLAVEDEVICE_NUM * sizeof(playdata_Typedef) + sizeof(packhead_Typedef))
#define NULL_EFFECTNUM 0xFF // 无效灯效编号

// // // extern uint8_t dma_buffer[DMA_BUFFER_SIZE];
extern const uint8_t bright_table[5];

typedef enum
{
    MCU_CONTROL,
    APP_CONTROL,
} control_mode_enum; /*控制模式*/


typedef enum
{
    SOURCE_LIST,   // 列表播放
    SOURCE_TEMP,   // 临时播放
} playsource_enum; /*播放源*/

typedef enum
{
    RANDOM_MODE, // 随机播放
    LOOP_MODE,   // 循环播放
} playmode_enum; /*播放循环模式*/

typedef enum
{
    RUN,   // 运行
    PAUSE, // 暂停
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
    uint8_t history[32];            // 保存最近播放的灯效记录
} play_minidetail_TypeDef;          /*播放列表详情*/

typedef enum
{
    SW_OFF,
    SW_ON,
} sw_status_enum;

typedef struct
{
    uint8_t now;    // 当前值
    uint8_t tar;    // 目标值
    uint8_t set;    // 保存值
    uint8_t dir;    // 方向
} NTSD_VAL_TypeDef;

typedef struct
{
    sw_status_enum sw_status;    // 全局开关
    NTSD_VAL_TypeDef brightness; // 全局亮度
} playwork_TypeDef;

typedef struct
{
    control_mode_enum control_mode; // 控制模式
    playsource_enum source;         // 播放源
    playwork_TypeDef work;
    playmode_enum mode;             // 播放模式
    playstatus_enum status;         // 播放状态
    play_minidetail_TypeDef detail; // 播放详情信息
    Efdetail_TypeDef efdetail;      // 当前灯效信息
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
uint8_t switch_ln_effect(switchplay_enum num);

/*在列表中播放下一灯效*/
void switch_next_ef_in_playlist(void);
/*在列表中播放上一灯效*/
void switch_last_ef_in_playlist(void);
/* 切换播放列表 */
uint8_t switch_playlist(uint8_t listnum);


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

/*
 * @Description: 进入app控制模式
 * @param:
 * @return:
*/
void goto_app_control_mode(void);

/*
 * @Description: 进入mcu控制模式
 * @param:
 * @return:
*/
void goto_mcu_control_mode(void);







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
void effect_play_run(void);
/***************************/



/*加载播放灯效信息*/
void load_play_effect_data(void);
/*复位播放帧进度*/
void play_frame_reset(void);
/*播放灯效初始化*/
void play_effect_init(void);
/*生成该灯效的动画缓存*/
void generate_play_video_buffer(void);
/*计算出从机的运行编号*/
void figure_slave_run_number(void);
/*发送从机播放数据*/
void transmit_slave_play_data(void);
/*所有灯点亮同个颜色*/
void play_color_in_all_salve_light(uint8_t bri, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
/*关闭所有灯板*/
void turn_off_all_salve_light(void);





/*播放灯效*/
void play_effect_video(void);
/*播放新灯效*/
void play_new_effect(uint8_t efnum);


#endif
