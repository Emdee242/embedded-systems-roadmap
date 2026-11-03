#ifndef PROCESSTASK_H
#define PROCESSTASK_H
#include "../../core/Logger.h"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
struct ProcessTaskParam{
    QueueHandle_t *processHandle ;
    Logger *logger;
};
void processTaskEntry(void *parameters);
#endif
