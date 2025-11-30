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
	int maxthreads = 20;
	int benchmark = 0;
	//set max children to input
	int opt;
	while ((opt = getopt(argc, argv, "p:t:b:")) != -1) {
    	switch (opt) {
        case 'p':
            maxchildren = atoi(optarg);
            break;
		case 't':
			maxthreads = atoi(optarg);
			break;
		case 'b':
			benchmark = atoi(optarg);
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
			char threads[64] = {};
			sprintf(threads, "%d",maxthreads);
			execl("./mandel","./mandel","-o",outfile,"-m","4000","-s",scale,"-x","-0.743643887","-y","0.131825904","-t",threads,NULL);
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
	if(benchmark){
	FILE *csv = fopen("mandel_runtimes.csv", "a");
	if(csv == NULL){
		perror("failed to open file");
		return 1;
	}
	fprintf(csv, "%d,%d,%.6f\n",maxthreads, maxchildren, elapsed);
    fclose(csv);
    }
	printf("Total runtime: %.6f seconds\n", elapsed);
	return 0;
}

