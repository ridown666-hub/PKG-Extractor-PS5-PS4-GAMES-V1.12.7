#pragma once
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/event.h>
typedef struct {void *data; uint64_t reserved[3];} VideoBuffer;
typedef struct {uint8_t reserved[80];} VideoAttribute;
int sceVideoOutOpen(int,int,int,const void*);
int sceVideoOutClose(int);
int sceVideoOutSetFlipRate(int,int);
int sceVideoOutSubmitFlip(int,int,uint32_t,int64_t);
int sceVideoOutAddFlipEvent(struct kevent*,int,void*);
int sceVideoOutDeleteFlipEvent(struct kevent*,int);
void sceVideoOutSetBufferAttribute2(VideoAttribute*,uint64_t,uint32_t,uint32_t,uint32_t,uint64_t,uint32_t,uint64_t);
int sceVideoOutRegisterBuffers2(int,int,int,VideoBuffer*,int,VideoAttribute*,int,void*);
int sceKernelAllocateMainDirectMemory(size_t,size_t,int,intptr_t*);
int sceKernelMapDirectMemory(void**,size_t,int,int,intptr_t,size_t);
int sceKernelReleaseDirectMemory(intptr_t,size_t);
int sceKernelCreateEqueue(struct kevent**,const char*);
int sceKernelWaitEqueue(struct kevent*,struct kevent*,int,int*,unsigned int*);
int sceKernelDeleteEqueue(struct kevent*);
int sceSystemServiceHideSplashScreen(void);
int sceUserServiceInitialize(const void*);
int sceUserServiceGetInitialUser(int*);
int scePadInit(void);
int scePadOpen(int,int,int,const void*);
int scePadClose(int);
int scePadReadState(int,void*);
