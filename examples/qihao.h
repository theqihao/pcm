/*************************************************************************
	> File Name: qihao.h
	> Author: 
	> Mail: 
	> Created Time: 2021年08月30日 星期一 17时41分50秒
 ************************************************************************/

#ifndef _QIHAO_H
#define _QIHAO_H

#include "cpucounters.h"
#include "utils.h"

#include <stdio.h>
#include <dlfcn.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>

/*
#define PCM_DELAY_DEFAULT 1.0 // in seconds
#define PCM_DELAY_MIN 0.015 // 15 milliseconds is practical on most modern CPUs
#define MAX_CORES 4096

using namespace std;
using namespace pcm;

void build_event(const char * argv, EventSelectRegister *reg, int idx);

struct CoreEvent
{
	char name[256];
	uint64 value;
	uint64 msr_value;
	char * description;
} events[PERF_MAX_CUSTOM_COUNTERS];

extern "C" {
	SystemCounterState SysBeforeState, SysAfterState;
	std::vector<CoreCounterState> BeforeState, AfterState;
	std::vector<SocketCounterState> DummySocketStates;
	EventSelectRegister regs[PERF_MAX_COUNTERS];
	PCM::ExtendedCustomCoreEventDescription conf;

	int pcm_c_build_core_event(uint8_t idx, const char * argv)
	{
		if(idx > 3)
			return -1;

		cout << "building core event " << argv << " " << idx << "\n";
		build_event(argv, &regs[idx], idx);
		return 0;
	}

	int pcm_c_init()
	{
		PCM * m = PCM::getInstance();
		conf.fixedCfg = NULL; // default
		conf.nGPCounters = m->getMaxCustomCoreEvents();
		conf.gpCounterCfg = regs;
		conf.OffcoreResponseMsrValue[0] = events[0].msr_value;
		conf.OffcoreResponseMsrValue[1] = events[1].msr_value;

		m->resetPMU();
		PCM::ErrorCode status = m->program(PCM::DEFAULT_EVENTS, &conf);
		if(status == PCM::Success)
			return 0;
		else
			return -1;
	}

	void pcm_c_start()
	{
		PCM * m = PCM::getInstance();
		m->getAllCounterStates(SysBeforeState, DummySocketStates, BeforeState);
	}

	void pcm_c_stop()
	{
		PCM * m = PCM::getInstance();
		m->getAllCounterStates(SysAfterState, DummySocketStates, AfterState);
	}

	uint64_t pcm_c_get_cycles(uint32_t core_id)
	{
		return getCycles(BeforeState[core_id], AfterState[core_id]);
	}

	uint64_t pcm_c_get_instr(uint32_t core_id)
	{
		return getInstructionsRetired(BeforeState[core_id], AfterState[core_id]);
	}

	double pcm_c_get_l2_hit(uint32_t core_id)
	{
		return getL2CacheHitRatio(BeforeState[core_id], AfterState[core_id]);
	}

	double pcm_c_get_l3_hit(uint32_t core_id)
	{
		return getL3CacheHitRatio(BeforeState[core_id], AfterState[core_id]);
	}

	double pcm_c_get_exec_usage(uint32_t core_id)
	{
		return getExecUsage(BeforeState[core_id], AfterState[core_id]);
	}

	double pcm_c_get_local_membw(uint32_t core_id)
	{
		return getLocalMemoryBW(BeforeState[core_id], AfterState[core_id]);
	}

	double pcm_c_get_remote_membw(uint32_t core_id)
	{
		return getRemoteMemoryBW(BeforeState[core_id], AfterState[core_id]);
	}

	uint64_t pcm_c_get_core_event(uint32_t core_id, uint32_t event_id)
	{
		return getNumberOfCustomEvents(event_id, BeforeState[core_id], AfterState[core_id]);
	}
}
*/
/*
int get_core_num() {
    const std::string path = "/sys/devices/system/cpu/present";
    std::string content = readSysFS(path);
    const char * buffer = content.c_str();
    int result = -1;
    pcm_sscanf(buffer) >> s_expect("0-") >> result;
    if(result == -1)
    {
       pcm_sscanf(buffer) >> result;
    }
    return result;
}
*/

struct QIHAO {
	int (*pcm_c_init)();
	void (*pcm_c_start)();
	void (*pcm_c_stop)();
	uint64_t (*pcm_c_get_cycles)(uint32_t core_id);
	uint64_t (*pcm_c_get_instr)(uint32_t core_id);
	double (*pcm_c_get_l2_hit)(uint32_t core_id);
	double (*pcm_c_get_l3_hit)(uint32_t core_id);
	double (*pcm_c_get_exec_usage)(uint32_t core_id);
	double (*pcm_c_get_local_membw)(uint32_t core_id);
	double (*pcm_c_get_remote_membw)(uint32_t core_id);

    void check(void *fun) {
        if (nullptr == fun) {
            printf("dlsym is null\n");
        }
    }

    void init() {
        void * handle = dlopen("./libpcm.so", RTLD_LAZY);
        if(!handle) {
            printf("Abort: could not (dynamically) load shared library \n");
            return;
        }

        check((void *)(pcm_c_init = (int (*)()) dlsym(handle, "pcm_c_init")));
        check((void *)(pcm_c_start = (void (*)()) dlsym(handle, "pcm_c_start")));
        check((void *)(pcm_c_stop = (void (*)()) dlsym(handle, "pcm_c_stop")));
        check((void *)(pcm_c_get_cycles = (uint64_t (*)(uint32_t)) dlsym(handle, "pcm_c_get_cycles")));
        check((void *)(pcm_c_get_instr = (uint64_t (*)(uint32_t)) dlsym(handle, "pcm_c_get_instr")));
        check((void *)(pcm_c_get_l2_hit = (double (*)(uint32_t)) dlsym(handle, "pcm_c_get_l2_hit")));
        check((void *)(pcm_c_get_l3_hit = (double (*)(uint32_t)) dlsym(handle, "pcm_c_get_l3_hit")));
        check((void *)(pcm_c_get_exec_usage = (double (*)(uint32_t)) dlsym(handle, "pcm_c_get_exec_usage")));
        check((void *)(pcm_c_get_local_membw = (double (*)(uint32_t)) dlsym(handle, "pcm_c_get_local_membw")));
        check((void *)(pcm_c_get_remote_membw = (double (*)(uint32_t)) dlsym(handle, "pcm_c_get_remote_membw")));
        /*
	    // pcm_c_build_core_event = pcm_c_build_core_event;
	    pcm_c_init = pcm_c_init;
	    pcm_c_start = pcm_c_start;
	    pcm_c_stop = pcm_c_stop;
	    pcm_c_get_cycles = pcm_c_get_cycles;
	    pcm_c_get_instr = pcm_c_get_instr;
        pcm_c_get_l2_hit = pcm_c_get_l2_hit;
        pcm_c_get_l3_hit = pcm_c_get_l3_hit;
        pcm_c_get_local_membw = pcm_c_get_local_membw;
        pcm_c_get_remote_membw = pcm_c_get_remote_membw;
        */
        pcm_c_init();
    }

    void start() {
        pcm_c_start();
    }

    void stop() {
        pcm_c_stop();
    }

    void print() {
        int core_num = 56; //get_core_num();
        printf("cycles, instr, ipc, l2_hit, l3_hit\n");
        double avg_cycles = 0;
        double avg_instr = 0;
        double avg_ipc = 0;
        double avg_l2_hit = 0;
        double avg_l3_hit = 0;
        for (int i = 0; i < core_num; ++i) {
            uint64_t cycles = pcm_c_get_cycles(i);
            uint64_t instr  = pcm_c_get_instr(i);
            double   ipc    = (double)instr / cycles;
            double   l2_hit = pcm_c_get_l2_hit(i);
            double   l3_hit = pcm_c_get_l3_hit(i);
            double cpu_usage= pcm_c_get_exec_usage(i);
            double local_bw = pcm_c_get_local_membw(i);
            double remote_bw= pcm_c_get_remote_membw(i);
            printf("%lu, %lu, %f, %f, %f, %f, %f, %f\n", cycles, instr, ipc, l2_hit, l3_hit, cpu_usage, local_bw, remote_bw);
            printf("%lu %lu %f %f %f\n", cycles, instr, ipc, l2_hit, l3_hit);
            avg_cycles += cycles;
            avg_instr += instr;
            avg_ipc += ipc;
            avg_l2_hit += l2_hit;
            avg_l3_hit += l3_hit;
        }

        avg_cycles /= core_num;
        avg_instr /= core_num;
        avg_ipc /= core_num;
        avg_l2_hit /= core_num;
        avg_l3_hit /= core_num;
        printf("%f %f %f %f %f\n", avg_cycles, avg_instr, avg_ipc, avg_l2_hit, avg_l3_hit);
    }
};


#endif
