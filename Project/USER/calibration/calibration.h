#ifndef _CALIBRATION_H_
#define _CALIBRATION_H_

#include "Function_Init.H"

typedef struct
{
    device_shape_enum shape;
    color_TypeDef color;
} calibration_TypeDef;



extern uint8_t calibration_enable;



/*
 * @Description: 颜色校准
 * @param:
 * @return:
*/
void calibration_color(calibration_TypeDef *data_t);

/*
 * @Description: 大三角形的校准
 * @param:
 * @return:
*/
void calibration_triangl_L(calibration_TypeDef *data_t);

/*
 * @Description: 中三角形的校准
 * @param:
 * @return:
*/
void calibration_triangl_M(calibration_TypeDef *data_t);

/*
 * @Description: 小三角形的校准
 * @param:
 * @return:
*/
void calibration_triangl_S(calibration_TypeDef *data_t);

/*
 * @Description: 正方形的校准
 * @param:
 * @return:
*/
void calibration_square(calibration_TypeDef *data_t);
#endif
