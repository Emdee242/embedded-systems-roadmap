#ifndef PROCESSTASK_H
#define PROCESSTASK_H
struct ProcessTaskParam{
    QueueHandle_t *processHandle ;
    Logger *logger;
}
void processTaskEntry(void *parameters);
#endif
