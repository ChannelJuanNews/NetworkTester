//============================================================================================================================================
// Termimal Program used to send http get request from inputted domain every nth seconds
// to be used as a network tester to see if there is an internet or DNS failure and stores the logs to a text file
// The parameters are {computer name(used for log file), attempted domain, sleep interval(between requests), timeout value(if request fails)} 
// The results are placed into a file called <name>REQUESTS.txt which display:
// REQUEST[nth value], get request success, error code(1 or 0), attempted domain, error result, local IP, primary IP, timestamp   
//============================================================================================================================================

/* c++ STL includes*/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <iomanip>

/*cURL library includes within this project*/
#include "curl/include/curl/curl.h"
#include "curl/include/curl/easy.h"

/*mysql c++ connector includes within this project*/
#include "mysql-connector/include/mysql_connection.h"
#include "mysql-connector/include/mysql_driver.h"

/*
#include "mysql-connector/include/cppconn/driver.h"
#include "mysql-connector/include/cppconn/exception.h"
#include "mysql-connector/include/cppconn/resultset.h"
#include "mysql-connector/include/cppconn/statement.h"
*/

/*mysql library dependency*/
#include "/usr/local/mysql/include/mysql.h"

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
//#define REQUESTS 100
#define SLEEP 3600

/*function used to change data types from char * to string (makes everthing easier)*/
std::string translate(char * data){
    return std::string(data);
}

static size_t printHandle(char * html, size_t size ,size_t nmembm, void * userdata){		
	// this does nothing
	return size * nmembm;
}

static size_t server_data_handler(void *contents, size_t size, size_t nmemb, void *userp){
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool check_remote_server(int timeout){

	CURL *curl;
	CURLcode res;
	std::string ServerCommand;
		
	curl = curl_easy_init();
	if(curl) {
		//std::cout << "WE ARE IN" << std::endl;
		if ((res = curl_easy_setopt(curl, CURLOPT_URL, "https://sev-front.firebaseio.com/flag.json")) != CURLE_OK){
			std::cout << "THERE WAS AN ERROR WITH SETTING THE URL FOR THE EQ GET REQUEST" << std::endl;
		}
		if ((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, server_data_handler)) != CURLE_OK){
			std::cout << "THERE WAS AN ERROR WITH SETTING THE WRITEFUNCTION FOR THE EQ GET REQUEST" << std::endl;
		}
		if ((res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ServerCommand)) != CURLE_OK){
			std::cout << "THERE WAS AN ERROR SETTING THE WRITE DATA FUNCTION FOR THE EQ GET REQUEST" << std::endl;
		}
		if ((res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout)) != CURLE_OK) {
			std::cout << "ERROR SETTING TIMEOUT VALUE FOR EQ GET REQUEST" << std::endl;
		}
		if ((res = curl_easy_perform(curl)) != CURLE_OK){
			std::cout << "THERE WAS AN ERROR PERFORMING A GET REQUEST ON THE EQ SERVER FOR THE 1 OR 0" << std::endl;
			return true;
		}
		curl_easy_cleanup(curl);
    		//std::cout << "\n\n THE CONTENTS OF THE WEBPAGE ARE: \n\n" << ServerCommand << "\n\n"  << std::endl;
	}
	
	if (ServerCommand == "1"){
		return true;
	}
	else if (ServerCommand == "0"){
		mySleep(21600); // sleeps for 6 hours
		check_remote_server(timeout); // then tries to call again
		return true; // if base case is true then returns true
	}
	return true;
}

int checkKnownDomainIP(std::string domain, int timeout){
	
	std::string IP = "";
	if(domain == "google.com"){ IP = "74.125.239.137";}	
	else if(domain == "yahoo.com"){ IP = "206.190.36.45";}
	else if(domain == "facebook.com"){ IP = "173.252.120.6";}
	else if(domain == "reddit.com"){ IP = "198.41.209.143";}
	else if(domain == "twitter.com"){ IP = "199.59.150.39";}
	else if(domain == "github.com"){ IP = "192.30.252.131";}
	else if(domain == "amazon.com"){ IP = "205.251.242.103";}
	else if(domain == "tubmlr.com"){ IP = "66.6.41.30";}
	else if(domain == "apple.com"){ IP = "17.142.160.59";}
	else if(domain == "youtube.com"){ IP = "74.125.239.34";}
	else {
		std::cout << "IP not available for this domain" << std::endl;
		return 3;
	}
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl){
		
		if((res = curl_easy_setopt(curl, CURLOPT_URL, IP.c_str())) != CURLE_OK){
			std::cout << "SETTING cURL FAILED" << std::endl;
		} 
		if((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &printHandle)) != CURLE_OK){
			std::cout << "ERROR setting WRITEFUNCTION in checkKnownDomainIP()" << std::endl;
		}
		if ((res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout)) != CURLE_OK) {
			std::cout << "ERROR SETTING TIMEOUT VALUE" << std::endl;
		}
		if((res = curl_easy_perform(curl)) != CURLE_OK){
			std::cout << "FOR SURE there is no internet then" << std::endl;
			return 1; // if the IP get request fails there is no internet
		}
		curl_easy_cleanup(curl);
		return 2; // otherwise if IP get request works the DNS doesn't work
	}
	return 3; // otherwise CURL was not initialized correctly
	
}

int send_to_mysql_database(std::string fileName){
	
	return 0;
}


void http_get_request(const std::string & name, const std::string & domain, unsigned & interval, unsigned & timeout){
	
	CURL * curl = curl_easy_init(); // intialize curl
	CURLcode res = CURLE_OK; // bool value used in error checking	
	std::ofstream outputfileStream; // declares an output stream
	std::string outfile = name + "REQUESTS.csv"; // appends `REQUESTS,txt` to file name
	outputfileStream.open(outfile.c_str()); // creates an outfile with `REQUESTS.txt` extension in current directory
	unsigned counter = 1; // counter that will keep track of number of http requests sent	
	time_t ltime; /* calendar time */
	ltime=time(NULL); /* get current cal time */
	std::string test = asctime( localtime(&ltime) ); // moves time stamp to a string
	test.erase(std::remove(test.begin(), test.end(), '\n'), test.end()); // erases the \n at the end of the string
	
	// ill put condition here to check for web flags later
	while(check_remote_server(timeout)){
		
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
		}/*
		else { outputfileStream << "\"curl initialization OK\",";}
		*/

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
		}/*
		else { outputfileStream << "\"CURLOPT_WRITEFUNCTION is OK\","; } 
		// if setting print functions is good then print success code and proceed
		*/
		
		// sets the URL to be used
		if ((res = curl_easy_setopt(curl, CURLOPT_URL, domain.c_str())) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if error occurs, prints to stderr
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // if error occurs prints to txt file
			counter++;
			continue;
		}/*
		else {outputfileStream << "\"CURLOPT_URL is OK\",";} // if setting url is good print success code
		*/
		
		// sets up an HTTPGET request
		if ((res = curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L)) != CURLE_OK){
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if error occurs, print to stderr
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // if error occurs print to txt file
			counter++;
			continue;
		}/*
		else { outputfileStream << "\"HTTP get request OK\",";} // if get request succeeds then proceed	
		*/

		// sets the timeout variable from paramter
		if ((res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout)) != CURLE_OK) {
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if error occurs, prints to stderr
			outputfileStream << "\"" << curl_easy_strerror(res) << "\""; // if error occurs, print to txt file
			counter++;
			continue;
		}/*
		else { outputfileStream << "\"Timeout value OK\",";} // if timeout settings succeed then proceed
		*/
	
		//=====================================
		// execute the configurations
		//=====================================
		// performs the request
		if ((res = curl_easy_perform(curl)) != CURLE_OK){	
			
			outputfileStream << "\"get request failed\",";
			// IF THERE IS AN ERROR WITH GET REQUEST THE PRINT A 0
			outputfileStream << "\"0\",";
			outputfileStream << "\"" << domain << "\",";
			
			// output error to txt file
			
			// compare error codes to find the root of the problem
			if (res == CURLE_COULDNT_CONNECT){
				// Failed to connect() to host or proxy, most likely this error is caused b/c of no internet
				
				outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
				//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
				outputfileStream.flush();
			}
			else if (res == CURLE_COULDNT_RESOLVE_HOST){
				// Couldn't resolve host. The given remote host was not resolved.	
				int domainStatus = checkKnownDomainIP(domain,timeout);
				
				if(domainStatus == 1){	
					outputfileStream << "\"" <<  "Check internet connection"/*curl_easy_strerror(res)*/ << "\","; // does the same but prints to txt file
					//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
					std::cout << "THERE IS NO INTERNET" << std::endl;
					outputfileStream.flush();
				}
				else if (domainStatus == 2){
					outputfileStream << "\"" << "DNS failure" /*curl_easy_strerror(res)*/ << "\","; // does the same but prints to txt file
					//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
					outputfileStream.flush();
					std::cout << "DNS FAILURE" << std::endl;
				}
				else if(domainStatus == 3){
					// else it is another error for sure
					outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
					//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
					outputfileStream.flush();
					std::cout << "SECOND TEST FAILED" << std::endl;
				}/*
				outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
				outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
				outputfileStream.flush();
				*/
			}
			else if (res == CURLE_OPERATION_TIMEDOUT){
				// Operation timeout. The specified time-out period was reached according to the conditions.
				// ERROR CODES ARE AS FOLLOWS:
				// 1 = "NO INTERNET CONNECTION"
				// 2 = "DNS DID NOT RESOLVE IP"
				// 3 = "CURL WAS NOT INTIALIZED PROPERLY"	
				int domainStatus = checkKnownDomainIP(domain,timeout);
				
				if(domainStatus == 1){
					
					outputfileStream << "\"" <<  "Check internet connection"/*curl_easy_strerror(res)*/ << "\","; // does the same but prints to txt file
					//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
					std::cout << "THERE IS NO INTERNET" << std::endl;
					outputfileStream.flush();
				}
				else if (domainStatus == 2){
					outputfileStream << "\"" << "DNS failure" /*curl_easy_strerror(res)*/ << "\","; // does the same but prints to txt file
					//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
					outputfileStream.flush();
					std::cout << "DNS FAILURE" << std::endl;
				}
				else if(domainStatus == 3){
					// else it is another error for sure
					outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
					//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
					outputfileStream.flush();
					std::cout << "SECOND TEST FAILED" << std::endl;
				}
			}
			else if (res == CURLE_HTTP_POST_ERROR){
				//This is an odd error that mainly occurs due to internal confusion.
				//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
				outputfileStream.flush();
			}
			else {
				// some other error
				std::cout << "THIS IS SOME OTHER ERROR" << std::endl;
				//outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
				outputfileStream.flush();
			}	
			
			//outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
			fprintf(stderr, "%s\n", curl_easy_strerror(res)); // prints the error to stdout
			counter++; // increments the counter for request number output
			mySleep(interval); // sleeps for given interval
			//continue;
		}
		else {
			outputfileStream << "\"get request OK\",";
			// SINCE NO ERROR, PRINT A ONE
			outputfileStream << "\"1\",";
			outputfileStream << "\"" << domain << "\",";
			outputfileStream << "\"" << curl_easy_strerror(res) << "\","; // does the same but prints to txt file
			outputfileStream.flush();	
		}
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
			outputfileStream << "\"" << localIP << "\",";
		}
		if (primary){ // 	
			outputfileStream << "\"" << primaryIP << "\",";
		}
		outputfileStream.flush(); // print everything to log file
		// prints out time stamp
		outputfileStream <<"\"" <<  test << "\""; // prints it out to txt file
		
		//==========================================
		// Sleep for alloted time given in parameter
		//==========================================
		mySleep(interval);
		counter++; // increment counter for request number

		int PacificStandardTime = 7; // we are -7 standard time in california
		int hour = ((time (0)/60/60)-PacificStandardTime) % 24; // mod by 24 to get military time
		

		//* for now */
		send_to_mysql_database(name);
		
		/* every 6 hours send data to mysql database*/			
		if((hour%6) == 0){
			
			//ERROR CODES BELOW:
			// 0) error sending file. don't delete file, but keep logging
			// 1) file sent, delete file and create new one
			// 2) some other error need to see whats up
			
			/*if returns 0 there was an error*/
			if(send_to_mysql_database(name) == 0){
			
				
			}
			else if(send_to_mysql_database(name) == 1){
				// success, delete the CSV file
				// create new empty CSV file
				
			}
			else if(send_to_mysql_database(name) == 2){
				// some other error
				
			}
			else {
				// other error don't know whats up
			
			}
		}	
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
	std::string outfile = name + "REQUESTS.csv"; // appends `REQUESTS,txt` to string	
	http_get_request(name, domain, interval, timeout);
	// at time t ftp the file to a server. Then delete file and make file again
	
	return 0;
}
