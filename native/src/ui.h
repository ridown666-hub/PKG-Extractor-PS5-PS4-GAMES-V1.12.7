#pragma once
#include <stdint.h>
#define WIDTH 1920
#define HEIGHT 1080
#define BTN_UP 0x10u
#define BTN_RIGHT 0x20u
#define BTN_DOWN 0x40u
#define BTN_LEFT 0x80u
#define BTN_R1 0x800u
#define BTN_L1 0x400u
#define BTN_CROSS 0x4000u
#define BTN_CIRCLE 0x2000u
#define BTN_OPTIONS 8u
int ui_init(void);
void ui_render(uint32_t*);
int ui_input(uint32_t);
int ui_quit(void);
void ui_set_controller(int);
void ui_destroy(void);
