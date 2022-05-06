/*************************************************************************
	> File Name: qihao.cpp
	> Author: 
	> Mail: 
	> Created Time: 2021年08月30日 星期一 19时29分08秒
 ************************************************************************/

#include "qihao.h"

#include<iostream>
using namespace std;

const int N = 10000;

int main(int argc, const char *argv[])
{
	int i,a[N],b[N],c[N];
	uint32_t total = 0;
	int lcore_id;

	srand(0);
	for (i=0; i < N; ++i) {
		a[i] = rand();
		b[i] = rand();
		c[i] = rand();
	}

    QIHAO* qihao = new QIHAO();
    qihao->init();
    qihao->start();
	for(i=0;i<100000;i++)
		c[i%N] = 4 * a[i%N] + b[i%N];
	for(i=0;i<N;i++)
		total += c[i];
    qihao->stop();

    qihao->print();

    return 0;

}
