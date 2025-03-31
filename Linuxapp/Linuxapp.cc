//Copyright Björn



﻿// Linux app.cpp : Defines the entry point for the application.
//

#include "Linuxapp.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <thread>
#include <sys/sysinfo.h>
#include <cstring>
#include <vector>
#include <sys/utsname.h>
#include <stdint.h>
#include <math.h> 
#include <string.h>
using namespace std;

float is;
float ant;

void Info() {
	int num_processors = sysconf(_SC_NPROCESSORS_ONLN);

	// Get hostname
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) == -1) {
		perror("gethostname");
		exit(1);
	}

	// Get hardware platform (machine)
	struct utsname uname_info;
	if (uname(&uname_info) == -1) {
		perror("uname");
		exit(1);
	}

	// Get total memory
	struct sysinfo sys_info;
	if (sysinfo(&sys_info) == -1) {
		perror("sysinfo");
		exit(1);
	}
	long total_memory = sys_info.totalram * sys_info.mem_unit / 1024 / 1024/1024; // in MB

	// Output system information
	cout << "Number of processors: " << num_processors << endl;
	cout << "Hostname: " << hostname << endl;
	cout << "Hardware platform: " << uname_info.machine << endl;
	cout << "Total memory: " << total_memory << " GB" << endl;
}

void CalculateSum() {
	pid_t pid = fork();
	if(pid != 0){
		uint64_t sum = 0;
	
		for (int i = 1; i < 50000; i++)
		{
			for (int j = 1; j < i; j++)
			{
					sum += sqrt(i * j);
			}
		}
		std::cout << " PID: " << pid;
		
		std::cout << " Sum: " << sum << std::endl;
	}
	


}

void CalculateSumThreaded(int threads) {
	
	pid_t pid = getpid();
	uint64_t sum = 0;
	for (int i = 1; i < 50000; i++)
	{
		for (int j = 1; j < i; j++)
		{
				sum += sqrt(i * j);
		}
	}
    std::cout << " PID: " << pid;
	std::cout << " Sum: " << sum << std::endl;
	

	
}

int main(int argc, char* argv[])
{
	if (strcmp(argv[1], "-i") == 0)
		Info();
	if (strcmp(argv[1], "-f") == 0) {
		string a = argv[2];
		int x = atoi(a.c_str());
		std::cout << " x: " << x << std::endl;
		for(int i = 0; i<x;i++){
			
			CalculateSum();
		}
		
		
	}

	if (strcmp(argv[1], "-t") == 0) {
		string a = argv[2];
		
		int x = atoi(a.c_str());

		std::vector<std::thread> threaders;
		for(int i = 0; i < x;i++){
			threaders.push_back(std::thread(CalculateSumThreaded,i));
		}

		for(auto& th : threaders){
			th.join();
		}
	
	}
}
