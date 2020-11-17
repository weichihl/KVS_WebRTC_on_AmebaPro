#ifndef BDDORBELL_DEMO_H
#define BDDORBELL_DEMO_H

#define ISP_FLIP_ENABLE	0
#define FILP_NUM        0x03

#define SERVER_PORT 5000

#define FIREBASE_FLASH_ADDR  0x240000 - 0x1000

#define SUSPEND_TIME 60000 //ms  
void doorbell_init_function(void *parm);

#endif