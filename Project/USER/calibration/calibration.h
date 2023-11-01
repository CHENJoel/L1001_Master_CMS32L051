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
 * @Description: ��ɫУ׼
 * @param:
 * @return:
*/
void calibration_color(calibration_TypeDef *data_t);

/*
 * @Description: �������ε�У׼
 * @param:
 * @return:
*/
void calibration_triangl_L(calibration_TypeDef *data_t);

/*
 * @Description: �������ε�У׼
 * @param:
 * @return:
*/
void calibration_triangl_M(calibration_TypeDef *data_t);

/*
 * @Description: С�����ε�У׼
 * @param:
 * @return:
*/
void calibration_triangl_S(calibration_TypeDef *data_t);

/*
 * @Description: �����ε�У׼
 * @param:
 * @return:
*/
void calibration_square(calibration_TypeDef *data_t);
#endif
