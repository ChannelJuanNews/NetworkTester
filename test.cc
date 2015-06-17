#include <string>
#include <iostream>
#include <sstream>
#include <curl/curl.h>

static size_t http_write(void* buf, size_t size, size_t nmemb, void* userp)
{
	if(userp)
	{
		std::ostringstream* oss = static_cast<std::ostringstream*>(userp);
		std::streamsize len = size * nmemb;
		oss->write(static_cast<char*>(buf), len);
		return nmemb;
	}

	return 0;
}

std::string get_html_page(const std::string& url, long timeout = 0)
{
	CURL* curl = curl_easy_init();

	std::ostringstream oss;

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &http_write);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_FILE, &oss);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	return oss.str();
}

int main()
{
	std::string html = get_html_page("http://www.google.com");

	std::cout << html << std::endl;

	return 0;
}
