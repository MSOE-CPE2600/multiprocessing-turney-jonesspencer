# System Programming Lab 11 Multiprocessing

This project implements mandelmovie, a multiprocessing program that launches multiple child processes to generate Mandelbrot-set images. The program accepts a -p option using getopt to choose the number of child processes. Each child independently invokes the mandel program to generate one frame. Frames are zoomed by decreasing scale each iteration. After generation, ffmpeg was used to assemble a movie.

Below is the plot of # of processes vs total runtime:

![Runtime Plot](benchmark.png)

Overall, the exponential decay trend shows that adding more processes increases performance quickly, but the benefit drops off once CPU cores become saturated, resulting in diminishing returns.
