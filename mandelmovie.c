/*
* File: mandelmovie.c
* Lab 11 - Multiprocessing
* Author: Spencer Jones
* CPE 2600 121
* Build using make, run using ./mandelmovie -p (number of processes to use)
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/wait.h>

int main( int argc, char *argv[] )
{
	//default max children to 20
	int maxchildren = 20;
	//set max children to input
	int opt;
	while ((opt = getopt(argc, argv, "p:")) != -1) {
    	switch (opt) {
        case 'p':
            maxchildren = atoi(optarg);
            break;

        default:
            exit(1);
    	}
	}
	//file output name
	char outfile [7] = "xx.jpg";
	int currentchildren = 0;
	//get current time
	struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

	for(int frame = 0 ; frame < 90; frame++){

		while(currentchildren >= maxchildren){
			wait(NULL);
			currentchildren--;
		}
		
		pid_t pid = fork();

		if(pid == 0){
			outfile[1] = (frame % 10) + '0';
			outfile[0] = (frame / 10) + '0';
			char scale [32] = {};
			sprintf(scale,"%lf",0.002 * pow(0.95,frame));
			execl("./mandel","./mandel","-o",outfile,"-m","4000","-s",scale,"-x","-0.743643887","-y","0.131825904",NULL);
			_exit(0);
		}

		currentchildren++;

	}
	while (currentchildren > 0) {
    wait(NULL);
    currentchildren--;
	}
	//get current time again to time the algorithm
	clock_gettime(CLOCK_MONOTONIC, &end);
	double elapsed =
    (end.tv_sec - start.tv_sec) +
    (end.tv_nsec - start.tv_nsec) / 1e9;

	printf("Total runtime: %.6f seconds\n", elapsed);
	return 0;
}

