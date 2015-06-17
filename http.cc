//==============================================================================
// Program used to request webpages from domain every nth seconds
// that tracks the (not really sure that it tracks) and displays
// the results into a text file on one line
//
//==============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <curl/curl.h>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <algorithm>

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

// custom sleep function used for different operation systems
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

static size_t printHandle(char * html, size_t size ,size_t nmembm, void * userdata){		
	
	return size * nmembm;
}

void http_get_request(const std::string & name, const std::string & domain, unsigned & interval, unsigned & timeout){
	
	CURL * curl = curl_easy_init(); // intialize curl
	CURLcode res = CURLE_OK; // bool value used in error checking	
	std::ofstream outputfileStream; // declares an output stream
	std::string outfile = name + "REQUESTS.txt"; // appends `REQUESTS,txt` to file name
	outputfileStream.open(outfile.c_str()); // creates an outfile with `REQUESTS.txt` extension in current directory
	unsigned counter = 1; // counter that will keep track of number of http requests sent
	
	
	// ill put condition here to check for web flags later
	while(1){
		
		char * localIP; // = '\0'; // char * that stores the local IP address
		char * primaryIP; // = '\0'; // char * that sores the primary IP address
		std::cout << "[" << counter << "] request" << std::endl; // for the user to see that work is actually being done on the screen
		
		// error checks curl initialization
		if (!curl){
			// need to put some sort of flags if curl initialization fails
			// to tell web server that it needs to be fixed on that computer
			
			fprintf(stderr, "curl initialization failure\n"); // if error occurs, prints to stderr
			outputfileStream << "\n\"curl initialization failure\"\n"; // if error occurs, prints to txt file
			return;
		}
		//=====================================
		// configure curl member functions here
		//=====================================
		
		// prints out the request number
		outputfileStream <<"\n\"REQUEST[" << counter << "]\","; // if intialization is okay print request #
		
		// sets the 'printHandle` function as the pring handler function
		if((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, printHandle)) != CURLE_OK){
			fprintf(stderr,"%s\n", curl_easy_strerror(res)); // if error occurs initalizing write handle function, output error
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // output same error, but to txt file
			counter++;
			continue;
		}
		else { outputfileStream << "\"CURLOPT_WRITEFUNCTION is OK\","; }  // if setting print functions is good then print success code and proceed

		// sets the URL to be used
		if ((res = curl_easy_setopt(curl, CURLOPT_URL, domain.c_str())) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if error occurs, prints to stderr
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // if error occurs prints to txt file
			counter++;
			continue;
		}
		else {outputfileStream << "\"CURLOPT_URL is OK\",";} // if setting url is good print success code
		
		// sets up an HTTPGET request
		if ((res = curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L)) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if error occurs, print to stderr
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // if error occurs print to txt file
			counter++;
			continue;
		}
		else { outputfileStream << "\"HTTP get request OK\",";} // if get request succeeds then proceed	
		
		// sets the timeout variable from paramter
		if ((res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout)) != CURLE_OK) {
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if error occurs, prints to stderr
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // if error occurs, print to txt file
			counter++;
			continue;
		}
		else { outputfileStream << "\"Timeout value OK\",";} // if timeout settings succeed then proceed
		
		//=====================================
		// execute the configurations
		//=====================================
		// performs the request
		if ((res = curl_easy_perform(curl)) != CURLE_OK){	
			
			/*switch (res){
        			case CURLE_COULDNT_CONNECT:
					outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
        				break;
				case CURLE_COULDNT_RESOLVE_HOST:	
					outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
        				break;
				case CURLE_COULDNT_RESOLVE_PROXY:
					outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
					std::cout << "Internet dose not exist\n";
					break;
				default: 
					break;
    			}*/	
			// this is where the error output goes
			
			outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if cannot reslove domain name, print to stdout
			counter++;
			mySleep(interval);
			continue;
		}
		else {outputfileStream << "\"Domain name resolved\",";} // if domain name resolved, proceed
		
		//==================================
		// Gets Local and Primary IP address
		//==================================
		//  gets the local IP addres
		bool local = true;
		bool primary = true;;
		if((res = curl_easy_getinfo(curl, CURLINFO_LOCAL_IP, &localIP)) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if local IP not found, print to stderr
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // if local IP not found, print to txt
			local = false; // set print bool to false to not print the local IP
			counter++; // increment counter for request number at the top
			continue; // continue to next iteration of while loop
		}
		if ((res = curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &primaryIP)) != CURLE_OK) {
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if primary IP not found, print to stderr
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // if primary IP not found, print to txt
			primary = false; // set print bool to false to not print the primary IP
			counter++; // increment counter for request number at the toop
			continue; // contine to next iteration of while loop
		}
		if (local){ // if attaining local IP address succeeded, print it
			outputfileStream << "\"Local IP found: " << localIP << "\",";
		}
		if (primary){ // 	
			outputfileStream << "\"Primary IP found: " << primaryIP << "\",";
		}
		outputfileStream.flush();
			
		time_t ltime; /* calendar time */
		ltime=time(NULL); /* get current cal time */
		std::string test = asctime( localtime(&ltime) ); // moves time stamp to a string
		test.erase(std::remove(test.begin(), test.end(), '\n'), test.end()); // erases the \n at the end of the string
		outputfileStream <<"\"" <<  test << "\""; // prints it out to txt file
		/*
		FILE * printFile = fopen(outfile.c_str(), "a+");
		fprintf(printFile, "Local IP found: %s <---> Primary IP found: %s \n",localIP?localIP:"na", primaryIP?primaryIP:"na");	
		*/
		
		//==========================================
		// Sleep for alloted time given in parameter
		//==========================================
		mySleep(interval);
		counter++;
	}
	//=====================================
	// cleanup the curl stuff
	//=====================================
	outputfileStream.close(); // closes the outfile stream
	curl_easy_cleanup(curl); // cleans up curl
}

int main(int argc, char * argv[]){
	
	// name, domain, interval
	if (argc < 5 || argc > 5){ // makes sure that the right parameters were used
		std::cout << "You did not input the right parameters, try again\n";
		return -1;
	}
	std::string name = translate(argv[1]);  // makes the `name` parameter a string
	std::string domain = translate(argv[2]); // makes the `domain` parameter a string
	unsigned interval = atoi(argv[3]); // converts char * to int to be used as a sleep timer
	unsigned timeout = atoi(argv[4]); // converst char * to int to be used as timeout variable for requests
	std::string outfile = name + "REQUESTS.txt"; // appends `REQUESTS,txt` to string	
	http_get_request(name, domain, interval, timeout);
	
	return 0;
}
