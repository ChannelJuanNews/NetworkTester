#ifndef _CALL_NETWORK_TESTER_
#define _CALL_NETWORK_TESTER_


#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <unistd.h> 
#include <string>
#include <cstring>
#include <string.h>

int callNetworkTester(){
	
	char * my_args[4];
	pid_t pid;
	
	my_args[0] = "juan";
	my_args[1] = "google.com";
	my_args[2] = "2";
	my_args[3] = "5";

	switch ((pid = fork())){
		case -1:
			/* Fork() has failed */
			perror ("fork");
			return -1;
			break;
		case 0:
			/* This is processed by the child */
			execv ("NetworkTester", my_args);
			return -1;
			break;
		default:
			/* This is processed by the parent */
			break;
	}
	return 0;
}
#endif
