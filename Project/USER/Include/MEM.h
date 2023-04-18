#ifndef MEM_H
#define MEM_H

#define thread_create(func, name, stack_size, argc, priority, tcb) \
    xTaskCreate((TaskFunction_t)func,                              \
                (const char *)name,                                \
                (uint16_t)stack_size / 4,                          \
                (void *)argc,                                      \
                (UBaseType_t)priority,                             \
                (TaskHandle_t *)tcb);





void Print_HEX16(uint8_t *sur, uint16_t size);
void SPI_FlashDebug(void);
void ROM_BufferRead(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);

#endif // MEM_H
