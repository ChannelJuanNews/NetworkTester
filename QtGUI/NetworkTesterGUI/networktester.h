#ifndef NETWORKTESTER_H
#define NETWORKTESTER_H

/* c++ STL includes*/
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
#include <string>
using std::string;
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
using std::setw;
using std::left;
#include <vector>
#include <thread>

/*c++ cURL library includes*/
#include <curl/curl.h>
#include <curl/curl.h>

/*Qt library includes*/
#include <QSql>
#include <QtSql>
#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QtGui>
#include <QInputDialog>


/*c++ mySQL connection libraries*/
//#include <mysql/mysql.h>
//#include <mysql/my_global.h>
//#include <mysql_connection.h>
//#include <mysql_driver.h>
//#include <mysql_error.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>
//include <cppconn/exception.h>

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

/* custom sleep function used for different operation systems*/
void mySleep(int sleepMs){

    #ifdef LINUX
        if(usleep(sleepMs * 1000) > 0){ // usleep takes sleep time in us (1 millionth of a second)
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
            Sleep(sleepMs);             // if windows 64 bit sleep, also has no return value
     #endif
}

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

    CURL * curl;
    CURLcode res;
    std::string ServerCommand;

    curl = curl_easy_init();
    if(curl) {

        //std::cout << "We are checkin the remote server" << std::endl;
        if ((res = curl_easy_setopt(curl, CURLOPT_URL, "https://sev-front.firebaseio.com/flag.json")) != CURLE_OK){
            perror("Error: Setting cURLOPT get request url failed: check_remote_server()");
            return true;
        }
        if ((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, server_data_handler)) != CURLE_OK){
            perror("Error: Setting cURLOPT write function failed: check_remote_server()");
            return true;
        }
        if ((res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ServerCommand)) != CURLE_OK){
            perror("Error: Setting cRULOPT write data failed: check_remote_server()");
        }
        if ((res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout)) != CURLE_OK) {
            perror("Error: Setting cURLOPT timeout failed: check_remote_server()");
            return true;
        }
        if ((res = curl_easy_perform(curl)) != CURLE_OK){
            perror("Error: Failed to retrieve instructions from website: check_remote_server()");
            return true;
        }
        curl_easy_cleanup(curl);
    }
    else {
        perror("Error: Curl failed to initialize: check_remote_server()");
        return true;
    }
    if (ServerCommand == "1"){
        return true;
    }
    else if (ServerCommand == "0"){
        // sleeps for 6 hours
        mySleep(21600);
        check_remote_server(timeout);
        return true;
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

    CURL * curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl){

        if((res = curl_easy_setopt(curl, CURLOPT_URL, IP.c_str())) != CURLE_OK){
            std::cout << "Error: Setting cUROPT url with known IP failed: checkKnownDomainIP()" << std::endl;
        }
        if((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &printHandle)) != CURLE_OK){
            std::cout << "Error: Setting cURLOPT write function failed: checkKnownDomainIP()" << std::endl;
        }
        if ((res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout)) != CURLE_OK) {
            std::cout << "Error: Setting cRULOPT timeout value failed: checkKownDomainIP()" << std::endl;
        }
        if((res = curl_easy_perform(curl)) != CURLE_OK){
            std::cout << "Error: Known IP adress request failed: checkKnownDomainIP()" << std::endl;
            return 1; // if the IP get request fails there is no internet
        }
        curl_easy_cleanup(curl);
        return 2; // otherwise if IP get request works the DNS doesn't work
    }
    return 3; // otherwise CURL was not initialized correctly
}
void parse_log_file(	const std::string & fileName,
            std::vector<std::string> & RequestNum, std::vector<std::string> & GetRequestStatus,
            std::vector<std::string> & SuccessCode, std::vector<std::string> & AttemptedDomain,
            std::vector<std::string> & ErrorStatus, std::vector<std::string> & LocalIP,
            std::vector<std::string> & PrimaryIP, std::vector<std::string> & RequestTime ){

    const int MAX_CHARS_PER_LINE = 512;
    const int MAX_TOKENS_PER_LINE = 22;
    const char * const DELIMITER = ",\"";

    ifstream fin;
    fin.open(fileName.c_str()); // open a file
    if (!fin.good()){
        perror("Error: File does not exist: parse_log_file()");
        return;
    }
    while (!fin.eof()){
        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);
        int n = 0;
        /* array to store memory addresses of the tokens in buf */
        const char * token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
        // parse the line
        token[0] = strtok(buf, DELIMITER); // first token
        if (token[0]) { // zero if line is blank
            for (n = 1; n < MAX_TOKENS_PER_LINE; n++){
                token[n] = strtok(0, DELIMITER); // subsequent tokens
                if (!token[n]) break; // no more tokens
            }
        }
        /* process the tokens into respective vectors */
        for (int i = 0; i < n; i++){ /* n = # of tokens */
            if(i == 0){ RequestNum.push_back(token[i]);}
            if(i == 3){ GetRequestStatus.push_back(token[i]);}
            if(i == 6){ SuccessCode.push_back(token[i]); }
            if(i == 9){ AttemptedDomain.push_back(token[i]);}
            if(i == 12){ ErrorStatus.push_back(token[i]);}
            if(i == 15){ LocalIP.push_back(token[i]);}
            if(i == 18){ PrimaryIP.push_back(token[i]);}
            if(i == 21){ RequestTime.push_back(token[i]);}
        }
    }
}

std::string convertIntToString(int Number, std::string & Result){
    std::ostringstream convert;   // stream used for the conversion
    convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
    return (Result += convert.str()); // set 'Result' to the contents of the stream
}

std::string getCurrentTime(std::string & currTime){

    time_t currentTime;
    struct tm *localTime;
    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time

    int Day    = localTime->tm_mday;
    int Month  = localTime->tm_mon + 1;
    int Year   = localTime->tm_year + 1900;
    int Hour   = localTime->tm_hour;
    int Min    = localTime->tm_min;
    int Sec    = localTime->tm_sec;

    convertIntToString(Year, currTime);
    currTime += "-";
    convertIntToString(Month, currTime);
    currTime += "-";
    convertIntToString(Day, currTime);
    currTime += "-";
    convertIntToString(Hour, currTime);
    currTime += "-";
    convertIntToString(Min, currTime);
    currTime += "-";
    convertIntToString(Sec, currTime);
    return currTime;
}

MainWindow * uI; /*Pointer to NetworkTester UI*/
std::thread * SmartThread; // I called this a smart thread because it's a genuis thanks to me of course
bool StopThread; /*sentinel control boolean variable*/

QString GLOBAL_MESSAGE;

static QString get_qstring(){
    return GLOBAL_MESSAGE;
}

static void set_qstring(QString value){
    GLOBAL_MESSAGE = value;
}



void http_get_request(const std::string & name, const std::string & domain, unsigned & interval, unsigned & timeout,
                      std::string HOST, std::string USER, std::string DATABASE, std::string PASSWORD, std::string EMAIL){

    std::ofstream outputfileStream; // declares an output stream
    std::string outfile = name + "REQUESTS.csv"; // appends `REQUESTS,txt` to file name
    outputfileStream.open(outfile.c_str()); // creates an outfile with `REQUESTS.txt` extension in specified directory
    if(!outputfileStream.is_open()){
        perror("Error: output file failed to open: http_get_request()");
    }
    std::string current_local_time;
    getCurrentTime(current_local_time);
    bool SendToDatabase = true; /*Sentinel control to determine when we are eligible to send file to database*/
    unsigned counter = 1; // counter that will keep track of number of http requests sent


    CURL * curl = curl_easy_init(); // intialize curl
    CURLcode res = CURLE_OK; // bool value used in error checking

    while(check_remote_server(timeout)){


        if(StopThread){
            outputfileStream.flush();
            outputfileStream.close();
            StopThread = false;
            return;
        }

        /* prints out the request number to log file */
       outputfileStream <<"\n\"REQUEST[" << counter << "]\" , ";
       std::cout << "[" << counter << "] request" << std::endl; // prints request number

       string number;
       convertIntToString(counter, number);
       QString number2 = QString::fromStdString(number);
       GLOBAL_MESSAGE = "[" + number2 + "] request";
       uI->sendMessage(GLOBAL_MESSAGE);

       char * localIP;
       char * primaryIP;

        if (!curl){
            perror("Error: curl failed to initialize: http_get_request()");
            return;
        }

        //=====================================
        // configure curl member functions here
        //=====================================

        /* Resets the curl options every time, no return value */
        curl_easy_reset(curl);
        /* sets the DNS cache timeout to 0 to disable DNS cache */
        long curl_cache_timeout = 0;
        if((res = curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, curl_cache_timeout)) != CURLE_OK){
            continue;
        }
        /* sets the 'printHandle` function as the pring handler function */
        if((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, printHandle)) != CURLE_OK){
            perror("Error: print handle was not initialized: http_get_request");
            continue;
        }
        /* sets the URL to be used */
        if ((res = curl_easy_setopt(curl, CURLOPT_URL, domain.c_str())) != CURLE_OK){
            perror("Error: url cRULOPT was not initialized: http_get_request()");
        }
        /* sets up an HTTPGET request url */
        if ((res = curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L)) != CURLE_OK){
            perror("Error: http get cRULOPT was not initialized: http_get_request()");
            continue;
        }
        /* sets the timeout variable from paramter */
        if ((res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout)) != CURLE_OK){
            perror("Error: timeout cURLOPT was not initialized: http_get_request()");
            continue;
        }

        //=====================================
        // execute the configurations
        //=====================================
        if ((res = curl_easy_perform(curl)) != CURLE_OK){

            outputfileStream << "\"get request failed\" , ";
            outputfileStream << "\"0\" , ";
            outputfileStream << "\"" << domain << "\" , ";


            // compare error codes to find the root of the problem
            if (res == CURLE_COULDNT_CONNECT){
                /* Failed to connect() to host or proxy, most likely this error is caused b/c of no internet */
                perror(curl_easy_strerror(res));
                outputfileStream << "\"" << curl_easy_strerror(res) << "\" , ";
                outputfileStream.flush();
            }
            else if (res == CURLE_COULDNT_RESOLVE_HOST){
                /* Couldn't resolve host. The given remote host was not resolved */
                int domainStatus = checkKnownDomainIP(domain,timeout);
                perror(curl_easy_strerror(res));

                if(domainStatus == 1){
                    outputfileStream << "\"" <<  "Check internet connection" << "\" , ";
                    outputfileStream.flush();
                    perror("Failure: 2nd test; check internet connection: http_get_request()");
                }
                else if (domainStatus == 2){
                    outputfileStream << "\"" << "DNS failure" << "\" , "; // does the same but prints to txt file
                    outputfileStream.flush();
                    perror("Failure: 2nd test; DNS failure: http_get_request()");
                }
                else if(domainStatus == 3){
                    outputfileStream << "\"" << curl_easy_strerror(res) << "\" , "; // does the same but prints to txt file
                    outputfileStream.flush();
                    perror("Failure: 2nd test; unknown error, run away: http_get_request()");
                }
            }
            else if (res == CURLE_OPERATION_TIMEDOUT){
                // Operation timeout. The specified time-out period was reached according to the conditions.
                // ERROR CODES ARE AS FOLLOWS:
                // 1 = "NO INTERNET CONNECTION"
                // 2 = "DNS DID NOT RESOLVE IP"
                // 3 = "CURL WAS NOT INTIALIZED PROPERLY"
                int domainStatus = checkKnownDomainIP(domain,timeout);

                if(domainStatus == 1){

                    outputfileStream << "\"" <<  "Check internet connection"/*curl_easy_strerror(res)*/ << "\" , "; // does the same but prints to txt file
                    //outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
                    std::cout << "THERE IS NO INTERNET" << std::endl;
                    outputfileStream.flush();
                }
                else if (domainStatus == 2){
                    outputfileStream << "\"" << "DNS failure" /*curl_easy_strerror(res)*/ << "\" , "; // does the same but prints to txt file
                    //outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
                    outputfileStream.flush();
                    std::cout << "DNS FAILURE" << std::endl;
                }
                else if(domainStatus == 3){
                    // else it is another error for sure
                    outputfileStream << "\"" << curl_easy_strerror(res) << "\" , "; // does the same but prints to txt file
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
            outputfileStream << "\"get request OK\" , ";
            outputfileStream << "\"1\" , ";
            outputfileStream << "\"" << domain << "\" , ";
            outputfileStream << "\"" << curl_easy_strerror(res) << "\" , "; // does the same but prints to txt file
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
            outputfileStream << "\"" << curl_easy_strerror(res) << "\" , "; // if local IP not found, print to txt
            local = false; // set print bool to false to not print the local IP
            counter++; // increment counter for request number at the top
            continue; // continue to next iteration of while loop
        }
        if ((res = curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &primaryIP)) != CURLE_OK) {
            fprintf(stderr, "%s\n", curl_easy_strerror(res)); // if primary IP not found, print to stderr
            outputfileStream << "\"" << curl_easy_strerror(res) << "\" , "; // if primary IP not found, print to txt
            primary = false; // set print bool to false to not print the primary IP
            counter++; // increment counter for request number at the toop
            continue; // contine to next iteration of while loop
        }
        if (local){ // if attaining local IP address succeeded, print it
            outputfileStream << "\"" << localIP << "\" , ";
        }
        if (primary){ //
            outputfileStream << "\"" << primaryIP << "\" , ";
        }
        // prints out time stamp
        outputfileStream <<"\"" <<  current_local_time << "\""; // prints it out to txt file
        outputfileStream.flush(); // print everything to log file

        //==========================================
        // Sleep for alloted time given in parameter
        //==========================================
        mySleep(interval);
        counter++; // increment counter for request number

        int PacificStandardTime = 7; // we are -7 standard time in california
        int hour = ((time(0)/60/60)-PacificStandardTime) % 24; // mod by 24 to get military time

        // one hour after we send to mysql database we
        // now set our second variable to true so we are able to send to database 5 hours after
        // for a total of 6 hours
        if((hour % 7) == 0){
            SendToDatabase = true;
        }

        //* for now PARAMS: filename, url, username, password, database */
        /* every 6 hours send data to mysql database*/
        /*if((hour%6) == 0 && SendToDatabase){
            cout << "NOW IS THE TIME" << endl;
            SendToDatabase = false; // that way it only uploads once!
            //ERROR CODES BELOW:
            // 0) file sent, delete file and create new one
            // 1) error sending file. don't delete file, but keep logging
            // 2) some other error need to see whats up
            // send_to_mysql_database(std::string fileName, std::string url, std::string user, std::string pass, std::string database){
           */ /*if returns 0 there was an error*/

            /*if(send_to_mysql_database(outfile, Host, User, Password, Database) == 0){
                // success, delete the CSV file
                // create new file with the same name
                outputfileStream.close();
                if(remove(outfile.c_str())!= 0){
                    perror("Error deleting file!");
                    outputfileStream.open(outfile.c_str());
                    continue;
                }
                else {
                    cout << "We have successfully removed the file!" << endl;
                }
                outputfileStream.open(outfile.c_str());
            }
            else if(send_to_mysql_database(outfile, "", "", "", "") == 1){
                // there was an error, don't delete file, keep logging
                continue;
            }
            else if(send_to_mysql_database(outfile, "", "", "", "") == 2){
                // some other error
                perror("there was some unforseen error sending data to mysql database");
                continue;
            }
        }*/
    }
    //=====================================
    // cleanup the curl stuff
    //=====================================
    outputfileStream.close(); // closes the outfile stream
    curl_easy_cleanup(curl); // cleans up curl
}

// GOLBAL VARIABLES

string Domain;
string Name;
unsigned Interval;
unsigned Timeout;
string Host;
string User;
string Database;
string Password;
string Email;
QTextEdit * Console;


std::thread * TimeThread;
std::thread * MessageThread;
std::thread * CounterThread;

void beginThread(MainWindow * UI){
    http_get_request(Name, Domain, Interval, Timeout, Host, User, Database, Password, Email);
    Console->setText("We are in");
}
void stopThread(){
   StopThread = true;
   delete SmartThread;
   SmartThread = NULL;
   return;
}

void secondThread(MainWindow * UI){
    //UI->sendMessage("This is the second thread");
    return;
}

std::thread * InitializeNetworkTester(MainWindow * ui, string domain, string name, string interval,
                             string timeout, string host, string user, string database,
                             string password, string email, string Directory, QTextEdit * LogMessage){

    string fileName = Directory + "/" + name;// + "REQUESTS.csv";
    unsigned INTERVAL = atoi(interval.c_str());
    unsigned TIMEOUT = atoi(timeout.c_str());
    std::cout << "The path is: " << fileName << std::endl;

    uI = ui;
    Domain = domain;
    Name = fileName;
    Interval = INTERVAL;
    Timeout = TIMEOUT;
    Host = host;
    User = user;
    Database = database;
    Password = password;
    Email = email;
    Console = LogMessage;
    StopThread = false;

    SmartThread = new std::thread(beginThread, ui);
    SmartThread->detach();

    MessageThread = new std::thread(secondThread,ui);


    return SmartThread;
}

#endif // NETWORKTESTER_H

















