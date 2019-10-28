#ifndef KEY_H
#define KEY_H

#define GATE_LEN 5
#define KEY_BAK 15
#include "stm32f10x.h"                  // Device header

void keyboard_init(void);
char get_keyboard(void);
void set_alarm(int *gate);
#endif
