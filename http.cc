//==============================================================================
// Program used to request webpages from domain every nth seconds
// that tracks the (not really sure that it tracks) and displays
// the results into a text file on one line
//
//==============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include </usr/include/curl/curl.h>
#include <stdio.h>

//==========Headers for different OS's for sleep syscall===========
#ifdef __APPLE__
	 #include <unistd.h>
#endif

#ifdef LINUX
	#include <unistd.h>
#endif

#ifdef _WIN64
	#include <windows.h>
#endif

#ifdef _WIN32
	#include <windows.h>
#endif
//=================================================================

void mySleep(int sleepMs){

	#ifdef LINUX
		if(usleep(sleepMs * 1000) > 0)  { 	// usleep takes sleep time in us (1 millionth of a second)
			cout << "Error with unix sleep system call\n";
		}	
	#endif
	#ifdef __APPLE__			
		if (sleep(sleepMs) > 0){ 		// if apple computer then use sleep normally	
			std::cout << "Error with Apple sleep system call\n";
		}
	#endif
	#ifdef _WIN64
        	Sleep(sleepMs); 			// if windows 32 bit sleep, also has no return value        
	 #endif
	#ifdef _WIN32
        	Sleep(sleepMs);         		// if windows 64 bit sleep, also has no return value
	 #endif
}

// total number of requests
#define REQUESTS 100

/*function used to change data types from char * to string (makes everthing easier)*/
std::string translate(char * data){
    return std::string(data);
}

size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata){
	
	return size * nmemb;
}

int main(int argc, char * argv[]){
	
	unsigned counter = 0;
	// name, domain, interval
	if (argc < 4 || argc > 4){ // makes sure that the right parameters were used
		std::cout << "You did not input the right parameters, try again\n";
		return -1;
	}
	std::string name = translate(argv[1]);   // makes the `name` parameter a string
	std::string domain = translate(argv[2]); // makes the `domain` parameter a string
	unsigned interval = atoi(argv[3]); // converts char * to int to be used as a counter

	std::string outfile = name + "REQUESTS.txt"; // appends `REQUESTS,txt` to string
	std::ofstream outputfileStream; // declares an output stream buffer
	outputfileStream.open(outfile.c_str()); // creates an outfile with `REQUESTS.txt` extension in current directory
	
	// TODO: output on one line the data below separated by commas
	// local IP address, time stamp, name of computer
	
	
	for (unsigned i = 0; i < 1; i++){
		
		// output more stuff here
		// output outcome here
		
		CURL * curl = curl_easy_init(); // initializes curl
		CURLcode res = CURLE_OK; // says something is okay, not sure what though
		char IP[100] = {0};	
		
		// error checks curl initialization
		if (!curl){ 
			fprintf(stderr, "curl initialization failure\n");
			return -1;
		}
		
		// sets the write_data as the 
		if((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data)) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
			return -1;
		}
			
		//  
		if((res = curl_easy_getinfo(curl, CURLINFO_LOCAL_IP, IP)) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
			return -1;
		}		
		std::cout << "The IP address is: " << IP << std::endl;
		
		// sets url we will post to
		if ((res = curl_easy_setopt(curl, CURLOPT_URL, domain.c_str())) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
			return -1;
		}
		
		// sets the post fields for the http post
		if ((res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=juan&project=curl")) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
			return -1;
		}
		
		// does all the magic
		if ((res = curl_easy_perform(curl)) != CURLE_OK){
			
			outputfileStream << curl_easy_strerror(res);
			// this is where the error output goes
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
			return -1;
		}
		
		std::cout <<"\n" << "REQUEST[" << counter << "]: ";
		mySleep(interval);
	}
	
	outputfileStream.close();	// closes the outfile stream
	return 0;
}
