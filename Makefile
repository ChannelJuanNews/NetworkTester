src = src # folder where all our source code is located
CXX = g++ # c++ compiler we are using

NTsrc = NetworkTester.cc # this is the main program 
cURLsrc = basicURL.cc # this is a basic example of the c++ cURL	
SQLsrc = mysqlcpp.cc # this is a basic example of the mysql c++ lib
GUIsrc = gtkmm.cc # this is a basic example of the gtkmm GUI c++ lib

mySQLconfigFlags = `mysql_config --cflags` # mysql compiler flags needed for library linking
mySQLlibFlags = `mysql_config --libs` # mysql compiler flags needed for dynamic library linking
mySQLheaderLocation = -I/usr/local/include # this flag tell the compiler where to find the mysql headers
mySQLcppconnLocation = -I/usr/local/include/cppconn # this flag tells the compiler where to find the c++ mysql connector headers
cppconnflags = -lmysqlcppconn # this flag tells the compiler we are also using the c++ mysql connector library
cURLflags = -lcurl # this flag tells the compiler we are also using the cURL c++ library
GUIflags = `pkg-config gtkmm-3.0 --cflags --libs`

BashNetworkTesterEx = NetworkTester # this is the name of our main program's executable which is terminal based
MysqlNetworkTesterEx = NetworkTester.dSYM # this is the second part of our executable. It is auto generated by the mysql c++ lib and needed for database communication

mySQLex = mySQL	# this is the name of our mySQL executable which is a basic example of how to insert into a mysql database
MysqlmySQLex = mySQL.dSYM # this is the second part of our executable. It is auto generated by the c++ mysql lib and NEEDED for database communication

cURLex = cURL	# this is the name of our cURL executable which is a basic example of how to get data from a website

GUIex = simpleGUI # this si the name of our GUI executable which is a basic example a gtkmm GUI

RMBIN = rm -rfv bin 
MKBIN = mkdir bin

NTGUIflags = g++ NTGUI.cc -o RunNetworkTesterGUI `pkg-config gtkmm-3.0 --cflags --libs`

all: NT CT MYSQLT GT NTGUI
	
NT:
	
	$(RMBIN)
	$(MKBIN)

	cd $(src) && $(CXX) $(mySQLconfigFlags) $(mySQLlibFlags) $(mySQLheaderLocation) $(mySQLcppconnLocation) $(cppconnflags) $(cURLflags) $(NTsrc) -o $(BashNetworkTesterEx) 
	cd $(src) && mv $(BashNetworkTesterEx) ../bin
	cd $(src) && mv $(MysqlNetworkTesterEx) ../bin		
CT:
	cd $(src) && $(CXX) $(cURLflags) $(cURLsrc) -o $(cURLex)
	cd $(src) && mv $(cURLex) ../bin
	
MYSQLT:
	cd $(src) && $(CXX) $(mySQLconfigFlags) $(mySQLlibFlags) $(mySQLheaderLocation) $(mySQLcppconnLocation) $(cppconnflags) $(SQLsrc) -o $(mySQLex) 
	cd $(src) && mv $(mySQLex) ../bin
	cd $(src) && mv $(MysqlmySQLex) ../bin
GT:
	cd $(src) && $(CXX) $(GUIflags) $(GUIsrc) -o $(GUIex)
	cd $(src) && mv $(GUIex) ../bin
NTGUI:
	cd $(src) && $(NTGUIflags)
	cd $(src) && mv RunNetworkTesterGUI ../bin

clean: 
	$(RMDIR)
