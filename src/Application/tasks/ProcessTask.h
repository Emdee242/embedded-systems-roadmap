#ifndef PROCESSTASK_H
#define PROCESSTASK_H
struct QueueHandles{
    QueueHandle_t messageHandle;
    QueueHandle_t sensorHandle;
}
static void processTaskEntry(void *parameters);
#endif
