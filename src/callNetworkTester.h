#ifndef _CALL_NETWORK_TESTER_
#define _CALL_NETWORK_TESTER_

#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <string>
#include <cstring>
#include <string.h>
#include <iostream>

int callNetworkTester(){
	
	char * my_args[6];
	//pid_t pid;
	char * path = "/Users/JuanRuelas/Desktop/NetworkTester/bin";
	my_args[1] = "juan";
	my_args[2] = "google.com";
	my_args[3] = "2";
	my_args[4] = "5"; 
	my_args[5] = NULL;
		
	std::cout << "WE ARE ABOUT TO EXECUTE" << std::endl << std::flush;
	if(execvP("NetworkTester",path, my_args) == -1){
		std::cout << "THERE WAS AN ERROR EXECTUING OUR PROGRAM" << std::endl;
	}
	
	return 0;
}
#endif
