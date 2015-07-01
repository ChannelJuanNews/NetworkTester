#ifndef NETWORKTESTER_H
#define NETWORKTESTER_H


//============================================================================================================================================
// Termimal Program used to send http get request from inputted domain every nth seconds
// to be used as an internet/DNS tester to see if there is an internet or DNS failure and stores logs with contextual information to a CSV file
// The parameters are {computer name(used for log file), attempted domain, sleep interval(between requests), timeout value(if request fails)}
// The results are placed into a file called <name>REQUESTS.txt which display:
// REQUEST[nth value], get request success/failure, error code(1 or 0), attempted domain, error result, local IP, primary IP, timestamp
//============================================================================================================================================

/* c++ STL includes*/
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
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
using std::setw;
using std::left;
#include <vector>

/*cURL library includes within this project*/
#include <curl/curl.h>
#include <curl/easy.h>

/*mysql library c++ includes*/
#include <mysql/mysql.h>
#include <mysql/my_global.h>
/*mysql c++ connector library includes within this project*/
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
/*mysql database information*/
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "test"

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
// #define REQUESTS 100
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

    CURL * curl;
    CURLcode res;
    std::string ServerCommand;

    curl = curl_easy_init();
    if(curl) {

        //std::cout << "WE ARE IN" << std::endl;
        if ((res = curl_easy_setopt(curl, CURLOPT_URL, "https://sev-front.firebaseio.com/flag.json")) != CURLE_OK){
            perror("THERE WAS AN ERROR WITH SETTING THE URL FOR THE EQ GET REQUEST");
        }
        if ((res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, server_data_handler)) != CURLE_OK){
            perror("THERE WAS AN ERROR WITH SETTING THE WRITEFUNCTION FOR THE EQ GET REQUEST");
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
    else {
        perror("curl failed to initialize");
        return true;
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

void parseLogFile(	const std::string & fileName,
            std::vector<std::string> & RequestNum, std::vector<std::string> & GetRequestStatus,
            std::vector<std::string> & SuccessCode, std::vector<std::string> & AttemptedDomain,
            std::vector<std::string> & ErrorStatus, std::vector<std::string> & LocalIP,
            std::vector<std::string> & PrimaryIP, std::vector<std::string> & RequestTime ){

    const int MAX_CHARS_PER_LINE = 512;
    const int MAX_TOKENS_PER_LINE = 22;
    const char * const DELIMITER = ",\"";

    // create a file-reading object
    ifstream fin;
    fin.open(fileName.c_str()); // open a file
    if (!fin.good()){
        cout << "File does not exist" << endl;
        return; // exit if file not found
    }
    // read each line of the file
    while (!fin.eof()){
        // read an entire line into memory
        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);
        // parse the line into blank-delimited tokens
        int n = 0; // a for-loop index
        // array to store memory addresses of the tokens in buf
        const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
        // parse the line
        token[0] = strtok(buf, DELIMITER); // first token
        if (token[0]) { // zero if line is blank
            for (n = 1; n < MAX_TOKENS_PER_LINE; n++){
                token[n] = strtok(0, DELIMITER); // subsequent tokens
                if (!token[n]) break; // no more tokens
            }
        }
        // process the tokens into respective vectors
        for (int i = 0; i < n; i++){ // n = #of tokens
            //cout << "Token[" << i << "] = " << token[i] << endl;

            if(i == 0){ RequestNum.push_back(token[i]);}
            if(i == 3){ GetRequestStatus.push_back(token[i]);}
            if(i == 6){ SuccessCode.push_back(token[i]); }
            if(i == 9){ AttemptedDomain.push_back(token[i]);}
            if(i == 12){ ErrorStatus.push_back(token[i]);}
            if(i == 15){ LocalIP.push_back(token[i]);}
            if(i == 18){ PrimaryIP.push_back(token[i]);}
            if(i == 21){ RequestTime.push_back(token[i]);}
        }
        //cout << endl;
    }
}

int send_to_mysql_database(std::string fileName, std::string url, std::string user, std::string pass, std::string database){

    if (url == ""){url = HOST;}
    if(user == ""){user = USERNAME;}
    if(pass == ""){pass = PASSWORD;}
    if(database == ""){database = DATABASE;}

    try {
        MYSQL *conn, mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        int query_state; // user for error detection

        /*declare the vectors to hold all log info*/
        std::vector<std::string> RequestNum;
        std::vector<std::string> GetRequestStatus;
        std::vector<std::string> SuccessCode;
        std::vector<std::string> AttemptedDomain;
        std::vector<std::string> ErrorStatus;
        std::vector<std::string> LocalIP;
        std::vector<std::string> PrimaryIP;
        std::vector<std::string> RequestTime;

        std::cout << "WE ARE ABOUT THE PARSE THE LOG FILE" << endl;
        /*parse the log file and send info into respective vectors*/
        parseLogFile(fileName, RequestNum, GetRequestStatus, SuccessCode, AttemptedDomain, ErrorStatus, LocalIP, PrimaryIP, RequestTime);

        mysql_init(&mysql);
        conn = mysql_real_connect(&mysql, HOST, USERNAME, PASSWORD, DATABASE, 0, 0, 0);
        if(conn == NULL) {
            cout << mysql_error(&mysql) << endl << endl;
            return 1;
        }
        query_state = mysql_query(conn, "select * from NetworkTester");
        if(query_state != 0) {
            cout << mysql_error(conn) << endl << endl;
            return 1;
        }
        res = mysql_store_result(conn);
        cout << "MySQL Values in the NetworkTester Table." << endl << endl;
        while((row = mysql_fetch_row(res)) != NULL){
            cout << left;
            cout << setw(18) << row[0] << setw(18) << row[1] << setw(18) << row[2] << setw(18) << row[3]<<endl;
        }
        cout << endl << endl;

        for(unsigned i = 0; i < RequestNum.size(); i++){
            std::string MYSQLinsert = "insert into NetworkTester (RequestNumber, RequestStatus, SuccessCode, AttemptedDomain, ErrorMessage, LocalIP, PrimaryIP, RequestTime) ";
            std::string MYSQLVal = MYSQLinsert + "values ('" + RequestNum[i] + "', '" + GetRequestStatus[i] + "',";
            std::string MYSQLVal1 = MYSQLVal + SuccessCode[i] + ", '" + AttemptedDomain[i] + "', '" + ErrorStatus[i] + "', '" + LocalIP[i] + "', '";
            std::string MYSQLVal2 = MYSQLVal1 +  PrimaryIP[i] +  "', '" + RequestTime[i] + "')";
            query_state = mysql_query(conn, MYSQLVal2.c_str());

            if(query_state == 0){
                cout << "Success sending query!" << endl;
            }
            else if (query_state == 1){
                // there was a faulire sending the query
                cout << "Error sending query" << endl;
                mysql_free_result(res);
                mysql_close(conn);
                return 1;
            }
            else {
                cout << "Something weird happened" << endl;
                mysql_free_result(res);
                mysql_close(conn);
                return 2;
            }
        }

        mysql_free_result(res);
        mysql_close(conn);

    }
    catch (sql::SQLException &e) {
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return 0;
}

void convertIntToString(int Number, std::string & Result){

    std::ostringstream convert;   // stream used for the conversion
    convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
    Result += convert.str(); // set 'Result' to the contents of the stream

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

void http_get_request(const std::string & name, const std::string & domain, unsigned & interval, unsigned & timeout){

    CURL * curl = curl_easy_init(); // intialize curl
    CURLcode res = CURLE_OK; // bool value used in error checking
    std::ofstream outputfileStream; // declares an output stream
    std::string outfile = name + "REQUESTS.csv"; // appends `REQUESTS,txt` to file name
    outputfileStream.open(outfile.c_str()); // creates an outfile with `REQUESTS.txt` extension in current directory
    unsigned counter = 1; // counter that will keep track of number of http requests sent
    //time_t ltime; /* calendar time */
    //ltime=time(NULL); /* get current cal time */
    std::string test;// = asctime( localtime(&ltime) ); // moves time stamp to a string
    //test.erase(std::remove(test.begin(), test.end(), '\n'), test.end()); // erases the \n at the end of the string
    test = getCurrentTime(test);

    bool SendToDatabase = true;

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
        outputfileStream <<"\n\"REQUEST[" << counter << "]\" , "; // if intialization is okay print request #

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

            outputfileStream << "\"get request failed\" , ";
            // IF THERE IS AN ERROR WITH GET REQUEST THE PRINT A 0
            outputfileStream << "\"0\" , ";
            outputfileStream << "\"" << domain << "\" , ";

            // output error to txt file

            // compare error codes to find the root of the problem
            if (res == CURLE_COULDNT_CONNECT){
                // Failed to connect() to host or proxy, most likely this error is caused b/c of no internet

                outputfileStream << "\"" << curl_easy_strerror(res) << "\" , "; // does the same but prints to txt file
                //outputfileStream <<"\"" <<  test << "\""; // prints the time stamp
                outputfileStream.flush();
            }
            else if (res == CURLE_COULDNT_RESOLVE_HOST){
                // Couldn't resolve host. The given remote host was not resolved.
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
            // SINCE NO ERROR, PRINT A ONE
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
        outputfileStream <<"\"" <<  test << "\""; // prints it out to txt file
        outputfileStream.flush(); // print everything to log file

        //==========================================
        // Sleep for alloted time given in parameter
        //==========================================
        mySleep(interval);
        counter++; // increment counter for request number

        int PacificStandardTime = 7; // we are -7 standard time in california
        int hour = ((time (0)/60/60)-PacificStandardTime) % 24; // mod by 24 to get military time

        // one hour after we send to mysql database we
        // now set our second variable to true so we are able to send to database 5 hours after
        // for a total of 6 hours
        if((hour % 7) == 0){
            SendToDatabase = true;
        }

        //* for now PARAMS: filename, url, username, password, database */
        /* every 6 hours send data to mysql database*/
        if((hour%6) == 0 && SendToDatabase){
            cout << "NOW IS THE TIME" << endl;
            SendToDatabase = false; // that way it only uploads once!
            //ERROR CODES BELOW:
            // 0) file sent, delete file and create new one
            // 1) error sending file. don't delete file, but keep logging
            // 2) some other error need to see whats up
            // send_to_mysql_database(std::string fileName, std::string url, std::string user, std::string pass, std::string database){
            /*if returns 0 there was an error*/
            if(send_to_mysql_database(outfile, "", "", "", "") == 0){
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
        }
    }
    //=====================================
    // cleanup the curl stuff
    //=====================================
    outputfileStream.close(); // closes the outfile stream
    curl_easy_cleanup(curl); // cleans up curl
}

int BeginNetworkTesting(int argc, char * argv[]){

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




#endif // NETWORKTESTER_H

