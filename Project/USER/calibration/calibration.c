#include "calibration.H"

uint8_t calibration_enable;


/*
 * @Description: 颜色校准
 * @param:
 * @return:
*/
void calibration_color(calibration_TypeDef *data_t)
{
   // uint16_t i;
    switch (data_t->shape)
    {
    case TRIANGLE_L: // 大三
        calibration_triangl_L(data_t);
        break;
    case TRIANGLE_M: // 中三
        calibration_triangl_M(data_t);
        break;
    case TRIANGLE_S: // 小三
        calibration_triangl_S(data_t);
        break;
    case SQUARE: // 方形
        calibration_square(data_t);
        break;
    default:
        break;
    }
}

/*
 * @Description: 大三角形的校准
 * @param:
 * @return:
*/
void calibration_triangl_L(calibration_TypeDef *data_t)
{

}

/*
 * @Description: 中三角形的校准
 * @param:
 * @return:
 */
void calibration_triangl_M(calibration_TypeDef *data_t)
{
    uint8_t flag = 0;
    // uint32_t sur;
    // uint32_t tar;
    uint32_t cal;
    if (data_t->color.R)
    {
        flag |= 1 << 0;
    }
    if (data_t->color.G)
    {
        flag |= 1 << 1;
    }
    if (data_t->color.B)
    {
        flag |= 1 << 2;
    }
    switch (flag)
    {
    case 0b000: // 单色校准
        break;
    case 0b111: // 三色校准
        // sur = data_t->color.B;
        // tar = sur * 225;
        // data_t->color.R = tar / 255;

        cal = data_t->color.R * 225 / 255;
        data_t->color.R = cal;
        // // data_t->color.R = data_t->color.B * 225 / 255;
        cal = data_t->color.G * 230 /255;
        data_t->color.G = cal;
        // // data_t->color.G = data_t->color.B * 230 /255;
        break;
    case 0b011: // RG

        cal = data_t->color.G * 230 /255;
        data_t->color.G = cal;
        break;
    case 0b110: // GB

        cal = data_t->color.G * 230 /255;
        data_t->color.G = cal;
        break;
    case 0b101: // RB

        cal = data_t->color.R * 225 / 255;
        data_t->color.R = cal;
        break;
    default:
        break;
    }
}

/*
 * @Description: 小三角形的校准
 * @param:
 * @return:
 */
void calibration_triangl_S(calibration_TypeDef *data_t)
{
    uint8_t flag = 0;
    uint32_t cal;
    if (data_t->color.R)
    {
        flag |= 1 << 0;
    }
    if (data_t->color.G)
    {
        flag |= 1 << 1;
    }
    if (data_t->color.B)
    {
        flag |= 1 << 2;
    }
    switch (flag)
    {
    case 0b000: // 单色校准
        break;
    case 0b111: // 三色校准

        cal = data_t->color.R * 220 / 255;
        data_t->color.R = cal; 

        cal = data_t->color.G * 230 /255;
        data_t->color.G = cal;
        break;
    case 0b011: // RG

        cal = data_t->color.G * 220 / 255;  //210
        data_t->color.G = cal;
        break;
    case 0b110: // GB

        cal = data_t->color.G * 230 /255;
        data_t->color.G = cal;
        break;
    case 0b101: // RB

        cal = data_t->color.R * 220 / 255;  // 210
        data_t->color.R = cal;
        break;
    default:
        break;
    }
}

/*
 * @Description: 正方形的校准
 * @param:
 * @return:
 */
void calibration_square(calibration_TypeDef *data_t)
{
    uint8_t flag = 0;
    uint32_t cal;
    if (data_t->color.R)
    {
        flag |= 1 << 0;
    }
    if (data_t->color.G)
    {
        flag |= 1 << 1;
    }
    if (data_t->color.B)
    {
        flag |= 1 << 2;
    }
    switch (flag)
    {
    case 0b000: // 单色校准
        break;
    case 0b111: // 三色校准

        cal = data_t->color.R * 220 / 255;
        data_t->color.R = cal;

        cal = data_t->color.B * 245 / 255;
        data_t->color.B = cal;
        break;
    case 0b011: // RG

        cal = data_t->color.R * 220 / 255;
        data_t->color.R = cal;
        break;
    case 0b110: // GB

        cal = data_t->color.B * 245 / 255;
        data_t->color.B = cal;
        break;
    case 0b101: // RB

        cal = data_t->color.R * 230 /255;
        data_t->color.R = cal;
        break;
    default:
        break;
    }
}
