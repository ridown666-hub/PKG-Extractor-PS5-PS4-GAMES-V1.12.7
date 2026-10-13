#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
int main(void){uint32_t*p=malloc(WIDTH*HEIGHT*4);if(!p||ui_init())return 1;ui_set_controller(1);ui_render(p);FILE*f=fopen("native-preview.ppm","wb");if(!f)return 2;fprintf(f,"P6\n%d %d\n255\n",WIDTH,HEIGHT);for(int i=0;i<WIDTH*HEIGHT;i++){unsigned char c[]={p[i]&255,(p[i]>>8)&255,(p[i]>>16)&255};fwrite(c,1,3,f);}fclose(f);free(p);ui_destroy();return 0;}
