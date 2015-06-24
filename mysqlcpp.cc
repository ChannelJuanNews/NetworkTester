/*C++ STL includes*/
#include <fstream>
using std::ifstream;
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <cstring>
#include <iomanip>
using std::setw;
using std::left;
/*mysql library c++ includes*/
#include <mysql/mysql.h>
#include <mysql/my_global.h>
//#include <mysql_driver.h>
//#include <mysql_connection.h>
/*c++ mysql connector includes*/
//#include <cppconn/driver.h>
#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>
//#include <cppconn/prepared_statement.h>

/*Defining Constant Variables for connection*/
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "test"

/*error handling function for mysql*/
void finish_with_error(MYSQL *con){
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);        
}	

void printVector(std::vector<std::string> & v){

	for(unsigned i = 0; i < v.size(); i++){
		std::cout << v.at(i) << " ";
	}
	std::cout << std::endl;
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
		
int main(int argc, char * argv[]){

	std::string url(argc >= 2 ? argv[1] : HOST);
	const std::string user(argc >= 3 ? argv[2] : USERNAME);
	const std::string pass(argc >= 4 ? argv[3] : PASSWORD);
	const std::string database(argc >= 5 ? argv[4] : DATABASE);
	const std::string fileName = "juanREQUESTS.csv";	
			
	
	try {	
		MYSQL *conn, mysql;
		MYSQL_RES *res;
		MYSQL_ROW row;
		int query_state;
		
		/*declare the vectors to hold all log info*/
		std::vector<std::string> RequestNum;
		std::vector<std::string> GetRequestStatus;
		std::vector<std::string> SuccessCode;	
		std::vector<std::string> AttemptedDomain;
		std::vector<std::string> ErrorStatus;
		std::vector<std::string> LocalIP;
		std::vector<std::string> PrimaryIP;
		std::vector<std::string> RequestTime;
		
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
	
		for(unsigned i = 0; i < RequestNum.size() - 1; i++){
			std::string MYSQLinsert = "insert into NetworkTester (RequestNumber, RequestStatus, SuccessCode, AttemptedDomain, ErrorMessage, LocalIP, PrimaryIP, RequestTime) "; 
			std::string MYSQLVal = MYSQLinsert + "values ('" + RequestNum[i] + "', '" + GetRequestStatus[i] + "',";
			std::string MYSQLVal1 = MYSQLVal + SuccessCode[i] + ", '" + AttemptedDomain[i] + "', '" + ErrorStatus[i] + "', '" + LocalIP[i] + "', '";
			std::string MYSQLVal2 = MYSQLVal1 +  PrimaryIP[i] +  "', '" + RequestTime[i] + "')";
			query_state = mysql_query(conn, MYSQLVal2.c_str());
			
			
		}
		
		mysql_free_result(res);
		mysql_close(conn);
	
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return EXIT_SUCCESS;
}

