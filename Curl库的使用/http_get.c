#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define CUR printf("%d\n", __LINE__);

int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
	// 头部的每一个json数据串都会调用该函数
	//CUR;
	if (type != CURLINFO_HEADER_IN)
		return -1;
	printf("%d\n", type);
	printf("%s\n", (char *)data);
	return 0;
}


int main(int argc, char *argv[])
{
	CURL *curl;
	
	struct curl_slist *headers=NULL;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (!curl)
		return -1;

	curl_slist_append(headers, "Accept: application/json");
	
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	
	
	curl_easy_setopt(curl, CURLOPT_URL, "http://172.16.24.223/api");
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	pause();
	return 0;
}


