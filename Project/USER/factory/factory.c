#include "factory.h"


/*��ʱ�ƻ���ָ���������*/
void schedule_factory_reset(void)
{
    schedule_list_TypeDef schedule;
    memset(&schedule, 0, sizeof(schedule));
    save_all_schedule(&schedule);
}
