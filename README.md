# NetworkTester

*What is NetworkTester?*

*NetworkTester* is a terminal based program that is meant to run diagnostics on your computer's internet connection. 
If you are having trouble connecting to a website this program will pinpoint what your problem is by running 2 tests.
The first test is a simple one; the program will send an `http get request` to a website of your choice.
If the get request works, then all is well! You have internet that works and a working Domain Name Server (DNS).
If the get request fails then the program will then run its second test to then pinpoint the problem.
The second test will go through a list of known IP addresses to find one that matches the domain you provided.
This is why it is recommend to use the [most frequented websites](https://en.wikipedia.org/wiki/List_of_most_popular_websites) on the web.
If your domain is matched with a known IP address, then the second test can start, otherwise we're stuck and won't be able to pinpoint the problem.
Once the second test starts, the program will send an http get request with the known IP address instead of the domain.
If the get request works, then your internet works and we know the problem is your DNS since the domain name is not being resolved to an IP address.
If the get request fails, then your internet must be disconnected, and the DNS is most likely not the cause of your problem.

##Other utilities

*NetworkTester* offers other utilities other than just sending simple get requests to a domain for testing.
This program will also keep logs of every request attempt and store them in an auto generated `CSV` file.
Not only does it keep track if what it does, it also sends its information to a `MySQL` database after it collects as much data as you want it to!

##Usefullness

With the ability to keep logs of the success or failure of a get request, and the ability to query into a database, *NetworkTester*
can be quite useful for figuring out the internet troubles of a small business or network. It was created to aid the systems administrator in
pinpointing the cause of internet malfunction, despite when everything looks like it is working fine.
In order to use it effectively, you must install *NetworkTester* on mulitple computers on the problematic network and have them all point
to the same `MySQL` server, but also have them send data to different databases. You will then have an archive of all the failures and
successes of each computer's *NetworkTester*. Then using MySQL you can figure out more details about the problem, like if only certain computers
are being affected or if the DNS goes down at a certain time of day and more. All these things can then help you find the heart of the problem.


##Building & Dependencies

To get *NetworkTester* up and running you will need to compile it into an executable, however there are dependencies. 
You will need to install the *cURL* c++ library. You can do that manually [here](http://curl.haxx.se/download.html) or
You can use a package manager like `Homebrew` [here](http://brewformulas.org/Curl). 

Then you will need to install the `MySQL server` [here](https://dev.mysql.com/downloads/mysql/). Which is a build dependency for
the MySQL c++ connector. I used `Homebrew, so you can find the install command [here](http://brewformulas.org/MysqlConnectorCxx).

Once you have all the dependencies installed, just run `make` in the NetworkTester directory and all your executables will be in your `bin` folder.

####Running NetworkTester

To run *NetworkTester* on the command line, you will need to pass parameters with the executable. 

Run: `$ ./NetworkTester [<Name of your computer>] [<Domain you want to connect to >] [<Interval between each connection>] [<Timeout Value>]`

So an example run would look like:

`$ ./NetworkTester juan google.com 5 10`

That will then connect to google.com every 5 seconds with a timeout value of 10 seconds and will spit out logs to a file named juanREQUESTS.csv. 

##Development

*NetworkTester* is under ACTIVE development. Soon it will have a GUI that will allow you to enter data more effectively rather
than on just the command line. It will also soon have cleaner code so if anyone is interested in learning how to use the cURL c++ library or
the MySQL c++ connector libraries then it won't be hard to just read over the code and learn. 

##Contributing

Honestly I don't know if many people can contribute to this project because it is a small project and it doesn't need much attention
from a lot of people, but if you feel like you can contribute or help out, PLEASE feel free to fork this repo, change whatever you feel needs
to be changed, and then issue a pull request. Chances are that I will most likely accept the changes :)

