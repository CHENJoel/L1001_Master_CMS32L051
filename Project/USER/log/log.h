#ifndef _LOG_H_
#define _LOG_H_

typedef enum
{
    SYS_CODE_BASE = 0x000, /* ϵͳ���� */
    ACT_CODE_BASE = 0x100, /* �������� */
    ACT_CLOCK,             // ���Ӷ���
    ACT_KEY,               // ��������
    ACT_LISTPLAY,          // �б���
    ERR_CODE_BASE = 0x200, /* ������� */
} LOG_CODE;

#endif
