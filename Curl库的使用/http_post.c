#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

#define CUR printf("%d\n", __LINE__);

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	CUR;
	printf("%s\n", (char *)contents);
	return 0;
}

int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
	// 头部的每一个json数据串都会调用该函数
	//CUR;
	//if (type != CURLINFO_HEADER_IN)
		//return -1;
	printf("%d\n", type);
	printf("%s\n", (char *)data);
	return 0;
}


int main(int argc, char *argv[])
{
	CURL *curl;
	
	struct curl_slist *headers=NULL;
	char *str;
	CUR;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (!curl)
		return -1;
	curl_slist_append(headers, "Content-Length:171");
	curl_slist_append(headers, "Content-Type: application/json");

	cJSON *obj = cJSON_CreateObject();
	cJSON_AddStringToObject(obj, "frequency", "38095");
	cJSON_AddStringToObject(obj, "preamble", "320,160");
	cJSON_AddStringToObject(obj, "irCode", "20,60,20,60,20,20,20,20,20,20,20,20,20,20,20,20,20,60,20,60,20,60,20,20,20,60,20,20,20,20,20,20,20,873");
	cJSON_AddStringToObject(obj, "repeat", "1");
	str = cJSON_Print(obj);
	printf("%s\n", str);


	curl_easy_setopt(curl, CURLOPT_URL, "http://172.16.24.251/api/v1/irports/2/sendir");
	// 获取body
    //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    //curl_easy_setopt(curl, CURLOPT_READFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
	
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_perform(curl);
	//free(str);
	//cJSON_Delete(obj);
	sleep(20);
	curl_slist_free_all(headers);

	CUR;
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	pause();
	return 0;
}
