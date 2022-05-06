/*************************************************************************
	> File Name: qihao.cpp
	> Author: 
	> Mail: 
	> Created Time: 2021年08月30日 星期一 19时29分08秒
 ************************************************************************/

#include "qihao.h"
#include "mem.h"

#include<unistd.h>
#include<iostream>
using namespace std;

const int N = 10000000;

int main(int argc, const char *argv[])
{
	int a[N],b[N],c[N];
	uint32_t total = 0;
	int lcore_id;
    uint64_t i;

	srand(0);
	for (i=0; i < N; ++i) {
		a[i] = rand();
		b[i] = rand();
		c[i] = rand();
	}
    bool encpu = true;
    bool enmem = true;
    QIHAO* qihao = NULL;
    MEM* mem = NULL;

    if (encpu) qihao = new QIHAO();
    if (enmem) mem = new MEM();
    if (encpu) qihao->init();
    if (enmem) mem->init();
    if (encpu) qihao->start();
    if (enmem) mem->start();
    sleep(2);
	for(i=0;i<10000000000;i++)
		c[i%N] = 4 * a[i%N] + b[i%N];
	for(i=0;i<N;i++)
		total += c[i];
    if (encpu) qihao->stop();
    if (enmem) mem->stop();

    if (encpu) qihao->print();
    if (enmem) mem->print();

    if (encpu) delete qihao;
    if (enmem) delete mem;
    return 0;

}
