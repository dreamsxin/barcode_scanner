	#include <curl/curl.h>
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <stddef.h>
	#include "pantry_api.h"
	#include "scanner_helper.h"
	#include "api_urls.h"

	//save urls
	

	char complete_url[1000]; // char string for complete url when requesting URL data



//INSERTS


	char * insert_update_freezer_from_upcid(char upcid[100])
	{
		strcpy(complete_url, url_api_barcode); // root url
		strcat(complete_url, apib_insert_update_freezer_from_upcid); // api func call
		strcat(complete_url, upcid); // api parameter
		printf("insert_update_freezer_from_upcid url: %s\n", complete_url);

		//char * piid = getURLData(complete_url);
		//return piid;
		return "piid";
	}

	char * insert_update_fridge_from_upcid(char upcid[100])
	{
		strcpy(complete_url, url_api_barcode); // root url
		strcat(complete_url, apib_insert_update_fridge_from_upcpid); // api func call
		strcat(complete_url, upcid); // api parameter
		printf("insert_update_fridge_from_upcid url: %s\n", complete_url);
		return "fridge";

		char * piid = getURLData(complete_url);
		return piid;
	}

	char * insert_update_pantry_from_upcid(char upcid[100])
	{
		strcpy(complete_url, url_api_barcode); // root url
		strcat(complete_url, apib_insert_update_pantry_from_upcpid); // api func call
		strcat(complete_url, upcid); // api parameter
		printf("insert_update_pantry_from_upcid url: %s\n", complete_url);
		return "pantry";
		char * piid = getURLData(complete_url);
		return piid;
	}

//GETTERS


	char * scan_barcode(char * barcode)
	{
		// make url
		strcpy(complete_url, url_api_barcode); // root url
		strcat(complete_url, apib_scan_barcode); // api func call
		strcat(complete_url, barcode); // api parameter
		printf("check_barcode_exists complete url: %s\n", complete_url);
		char * barcode_info = getURLData(complete_url);
		return barcode_info;
	}


	// will this now come from get_barcode_info?
	char * get_iid_from_upcid(char upcid[100])
	{
		strcpy(complete_url, url_api_barcode); // root url
		strcat(complete_url, apib_get_iid_from_upcid); // api func call
		strcat(complete_url, upcid); // api parameter
		char * iid = getURLData(complete_url);
		return iid;
	}

	//should this be from upcid?
	char * get_piid_from_iid(char iid[100])
	{
		strcpy(complete_url, url_api_barcode); // root url
		strcat(complete_url, apib_get_piid_from_iid); // api func call
		strcat(complete_url, iid); // api parameter
		char * piid = getURLData(complete_url);
		return piid;
	}

	char * get_iid_information(char * iid)
	{
		//TODO
	}

	char * get_upcid_information(char * upcid)
	{
		//TODO
	}

	char * get_qtid_from_iid(char * iid)
	{
		//TODO
	}

	char * get_qtid_from_upcid(char * upcid)
	{
		//TODO
	}

	char * get_qtid_from_qtype(char * qtype)
	{
		//TODO
	}

	char * get_qtypes()
	{
		//TODO
	}

	char * get_default_qtids(char * upcid)
	{
		//TODO
	}




	char * move_upc_location(char upcid[100], char * amount, char * from, char * to)
	{
		//TODO
	}

	char * increase_upc_location(char upcid[100], char * amount, char * location)
	{
		//TODO
	}

	char * decrease_upc_location(char upcid[100], char * amount, char * location)
	{
		//TODO 
	}

	/*
	char * addIngredientFromUpcid(char upcid[100])
	{
		strcpy(complete_url, url_api_barcode); // root url
		strcat(complete_url, api_func_insert_ingredient_from_upcid); // api func call
		strcat(complete_url, upcid); // api parameter

		char * iid = getURLData(complete_url);
		if(strcmp(iid, "0") == 0){
			 // failed
			// iid = ...
			printf("failed to addIngredientFromUpcid()\n");
		} else {
			strcpy(complete_url, url_api_barcode); // root url
			strcat(complete_url, api_func_add_upc_ingredient); // api func call
			strcat(complete_url, iid); // api parameter
			strcat(complete_url, "/"); // api parameter
			strcat(complete_url, upcid); // api parameter
			char * result = getURLData(complete_url);
		}

		return iid;
	}
	*/




	/*
	int populateCompleteBarcode(struct barcode_information *barcode_p){
		 // need to populate title, nutrition, amount, qqtid, qtype
		strncpy(barcode_p->title, getTitleFromUpcid(barcode_p->upcid), sizeof(barcode_p->title) - 1);
		strncpy(barcode_p->description, getDescriptionFromUpcid(barcode_p->upcid), sizeof(barcode_p->description) - 1);
		strncpy(barcode_p->qtid, getQtidFromUpcid(barcode_p->upcid), sizeof(barcode_p->qtid) - 1);
		strncpy(barcode_p->amount, getAmountFromUpcid(barcode_p->upcid), sizeof(barcode_p->amount) - 1);
		strncpy(barcode_p->calories, getCaloriesFromUpcid(barcode_p->upcid), sizeof(barcode_p->calories) - 1);
		strncpy(barcode_p->nutrition, getNutritionFromUpcid(barcode_p->upcid), sizeof(barcode_p->nutrition) - 1);
	}
	*/



	// download html source from supplied url
	char * getURLData(char *url){
		CURL *curl;
		CURLcode res;


	  	struct MemoryStruct chunk;

	  	chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */ 
	  	chunk.size = 0;    /* no data at this point */ 

		curl_global_init(CURL_GLOBAL_ALL);

		/* init the curl session */ 
	 	curl = curl_easy_init();

		curl_easy_setopt(curl, CURLOPT_URL, url);//"http://rontonsoup.com/recipe_management/index.php/api/checkPiidExistsInFridge/3");
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,WriteMemoryCallback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
		    fprintf(stderr, "curl_easy_perform() failed: %s\n",
		            curl_easy_strerror(res));
		  }
		  else {
		    /*
		     * Now, our chunk.memory points to a memory block that is chunk.size
		     * bytes big and contains the remote file.
		     *
		     * Do something nice with it!
		     *
		     * You should be aware of the fact that at this point we might have an
		     * allocated data block, and nothing has yet deallocated that data. So when
		     * you're done with it, you should free() it as a nice application.
		     */ 
		 
		    printf("%lu bytes retrieved\n", (long)chunk.size);
		  }

		/* cleanup curl stuff */ 
			curl_easy_cleanup(curl);

			//printf("%lu bytes retrieved\n", (long)chunk.size);
			//printf("%s string retrieved\n", chunk.memory);


		/* we're done with libcurl, so clean it up */ 
		curl_global_cleanup();

		return chunk.memory;
	}
	
	char * getURLData2(char * url)
	{
		CURL *curl;
		CURLcode res;

		curl = curl_easy_init();
		if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
		/* example.com is redirected, so we tell libcurl to follow redirection */ 
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
		  fprintf(stderr, "curl_easy_perform() failed: %s\n",
		          curl_easy_strerror(res));

		/* always cleanup */ 
		curl_easy_cleanup(curl);
		}
	}

	static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
	{
	  size_t realsize = size * nmemb;
	  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
	 
	  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	  if(mem->memory == NULL) {
	    /* out of memory! */ 
	    printf("not enough memory (realloc returned NULL)\n");
	    return 0;
	  }
	 
	  memcpy(&(mem->memory[mem->size]), contents, realsize);
	  mem->size += realsize;
	  mem->memory[mem->size] = 0;
	 
	  return realsize;
	}