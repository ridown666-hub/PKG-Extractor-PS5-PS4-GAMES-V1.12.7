/* Own native application shell. SDK interfaces follow public PS5 homebrew references. */
#include "platform.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdarg.h>
static FILE *logfile;
static void log_result(const char*name,int code){fprintf(stderr,"[Arctic native] %s: 0x%08x\n",name,(unsigned)code);if(logfile){fprintf(logfile,"%s: 0x%08x\n",name,(unsigned)code);fflush(logfile);}}
/* Adapted pixel addressing from SDL PS5, Copyright 2026 John Tornblom.
 * zlib license retained in THIRD_PARTY_NOTICES.md. This is an altered scalar adaptation. */
static unsigned tile_offset(unsigned x,unsigned y){return (x&1)|((x&2))|((y&1)<<2)|((y&2)<<2)|((y&4)<<2)|((x&4)<<3)|(((x>>3^y>>3)&1)<<6)|(((x>>4^y>>4)&1)<<7)|(((x>>6^y>>5)&1)<<8)|(((x>>5^y>>6)&1)<<9)|((y&8)<<7)|((x&16)<<7)|((y&64)<<6)|((x&64)<<7)|((x&128)<<7)|((x&256)<<7);}
int main(void){int video=-1,pad=-1,allocated=0,mapped=0,result=-1;intptr_t physical=0;void*direct=NULL;struct kevent*queue=NULL;uint32_t*linear=NULL;VideoBuffer bufs[2]={{0}};VideoAttribute attr={{0}};unsigned user_params[16]={0};uint32_t last=0;uint64_t frame=0;unsigned version=1,rendered[2]={0};int user=-1;
mkdir("/data/arctic_native",0755);logfile=fopen("/data/arctic_native/startup.log","w");
if(ui_init()){log_result("UI assets",-1);goto done;}linear=malloc(WIDTH*HEIGHT*4);if(!linear)goto done;
int rc=sceSystemServiceHideSplashScreen();log_result("HideSplashScreen",rc);
video=sceVideoOutOpen(0xff,0,0,NULL);log_result("VideoOutOpen",video);if(video<0)goto done;
size_t memsize=0x4000000;rc=sceKernelAllocateMainDirectMemory(memsize,0x20000,3,&physical);log_result("AllocateDirectMemory",rc);if(rc)goto done;allocated=1;
rc=sceKernelMapDirectMemory(&direct,memsize,0x33,0,physical,0x20000);log_result("MapDirectMemory",rc);if(rc)goto done;mapped=1;memset(direct,0,memsize);bufs[0].data=direct;bufs[1].data=(unsigned char*)direct+memsize/2;
rc=sceKernelCreateEqueue(&queue,"arctic native flip");log_result("CreateEqueue",rc);if(rc)goto done;
rc=sceVideoOutAddFlipEvent(queue,video,NULL);log_result("AddFlipEvent",rc);if(rc)goto done;
sceVideoOutSetBufferAttribute2(&attr,0x8000000022000000ULL,0,WIDTH,HEIGHT,0,0,0);
rc=sceVideoOutRegisterBuffers2(video,0,0,bufs,2,&attr,0,NULL);log_result("RegisterBuffers2",rc);if(rc)goto done;
sceVideoOutSetFlipRate(video,0);sceUserServiceInitialize(user_params);scePadInit();
rc=sceUserServiceGetInitialUser(&user);log_result("GetInitialUser",rc);if(!rc){pad=scePadOpen(user,0,0,NULL);log_result("PadOpen",pad);}ui_set_controller(pad>=0);ui_render(linear);
unsigned col[WIDTH],yoff[128];for(unsigned x=0;x<WIDTH;x++)col[x]=(x/512)*65536+tile_offset(x%512,0);for(unsigned y=0;y<128;y++)yoff[y]=tile_offset(0,y);
while(!ui_quit()){
_Alignas(16) unsigned char data[512]={0};uint32_t buttons=0;int connected=0;
if(pad>=0&&!scePadReadState(pad,data)){memcpy(&buttons,data,4);connected=data[0x4c]!=0;}uint32_t pressed=buttons&~last;last=buttons;
if(pressed&&ui_input(pressed)){version++;ui_render(linear);}if(ui_quit())break;
unsigned idx=(unsigned)(frame%2);if(rendered[idx]!=version){uint32_t*dst=bufs[idx].data;for(unsigned y=0;y<HEIGHT;y++){unsigned base=(y/128)*(128*WIDTH),yo=yoff[y%128];for(unsigned x=0;x<WIDTH;x++)dst[base+(col[x]^yo)]=linear[y*WIDTH+x];}__sync_synchronize();rendered[idx]=version;}
rc=sceVideoOutSubmitFlip(video,(int)idx,1,(int64_t)frame);if(rc){log_result("SubmitFlip",rc);goto done;}struct kevent event;int count=0;unsigned timeout=1000000;rc=sceKernelWaitEqueue(queue,&event,1,&count,&timeout);if(rc){log_result("WaitFlip",rc);goto done;}frame++;
if(!connected&&pad<0&&frame%120==0){if(!sceUserServiceGetInitialUser(&user)){pad=scePadOpen(user,0,0,NULL);if(pad>=0){ui_set_controller(1);version++;ui_render(linear);}}}
}result=0;
done:if(pad>=0)scePadClose(pad);if(queue&&video>=0)sceVideoOutDeleteFlipEvent(queue,video);if(video>=0)sceVideoOutClose(video);if(queue)sceKernelDeleteEqueue(queue);if(mapped)munmap(direct,0x4000000);if(allocated)sceKernelReleaseDirectMemory(physical,0x4000000);free(linear);ui_destroy();if(logfile)fclose(logfile);return result;}
