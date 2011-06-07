#ifndef _L4_KIP_H
#define _L4_KIP_H

#include <l4/types.h>

typedef struct {
	char version;
	char subversion;
	L4_Word16_t padding;
} L4_ApiVersion_t;

typedef struct {
	Word flags;
} L4_ApiFlags_t;

typedef struct {
	char id;
	char subid;
	L4_Word16_t padding;
} L4_KernelId_t;

typedef struct {
	L4_Word16_t MemDescPtr;
	L4_Word16_t n;
} L4_MemoryInfo_t;

typedef struct {
	Word info;
} L4_UtcbInfo_t;

typedef struct {
	Word info;
} L4_KipAreaInfo_t;

typedef struct {
	L4_Word16_t SchedulePrecision;
	L4_Word16_t ReadPrecision;
} L4_ClockInfo_t;

typedef struct {
	L4_Word_t info;
} L4_ThreadInfo_t;

typedef struct {
	L4_Word_t info;
} L4_PageInfo_t;

typedef struct {
	L4_Word16_t s;
	L4_Word16_t processors;
} L4_ProcessorInfo_t;

typedef struct {
	L4_Word_t magic;
	L4_ApiVersion_t ApiVersion;
	L4_ApiFlags_t ApiFlags;
	L4_Wprd_t KernelDescPtr;
	L4_Word_t padding1[4];
	L4_Word_t padding2[4];
	L4_Word_t padding3[4];
	L4_Word_t padding4[4];
	L4_Word_t padding5[1];
	L4_MemoryInfo_t MemoryInfo;
	L4_Word_t padding6[2];
	L4_Word_t padding7[4];
	L4_Word_t padding8[4];
	L4_Word_t padding9[4];
	L4_Word_t padding10[4];
	L4_Word_t padding11[2];
	L4_UtcbInfo_t UtcbInfo;
	L4_KipAreaInfo_t KipAreaInfo;
	L4_Word_t padding12[2];
	L4_Word_t BootInfo;
	L4_Word_t ProcDescPtr;
	L4_ClockInfo_t ClockInfo;
	L4_ThreadInfo_t ThreadInfo;
	L4_PageInfo_t PageInfo;
	L4_ProcessorInfo_t ProcessorInfo;
	L4_Word_t SPACECONTROLpSC;
	L4_Word_t THREADCONTROLpSC;
	L4_Word_t PROCESSORCONTROLpSC;
	L4_Word_t MEMORYCONTROLpSC;
	L4_Word_t IPCSC;
	L4_Word_t LIPCSC;
	L4_Word_t UNMAPSC;
	L4_Word_t EXCHANGEREGISTERSSC;
	L4_Word_t SYSTEMCLOCKSC;
	L4_Word_t THREADSWITCHSC;
	L4_Word_t SCHEDULESC;
	L4_Word_t padding13;
} L4_KernelInterfacePage_t;

#endif

