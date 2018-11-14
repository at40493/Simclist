#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "simclist.h"

int main()
{
	list_t list;
	int ret = -1; // Default return failed.

	if(list_init(&list) != 0) { // initial
		fprintf(stderr, "Init failed\n");
		return ret;
	}

	/* request to store copies, and provide the metric function */
	list_attributes_copy(&list, list_meter_int32_t, 1);

	fprintf(stdout, "End with a negative number\n");
	fprintf(stdout, "Insert your number: \n");

	int num = 0; // input number
	char *str = NULL, *endptr = NULL;
	size_t len = 0;
	while(getline(&str, &len, stdin) != -1) {

		errno = 0 ; /* To distinguish success/failure after call */
		num = strtol(str, &endptr, 10); //String to int
		
		/* Check for various possible errors */
		if(errno == ERANGE) {
			perror("strtol");
			continue;
		}

		if(endptr == str) {
			fprintf(stderr, "No digits were found\n");
			continue;
		}

		if(num < 0) { // Exit the while loop.
			ret = 0; // success
			break;
		}

		if(list_append(&list, &num) < 0) { // Add an element to the list
			fprintf(stderr, "Add num failed: %d.\n", num);
			break; // Add failed.
		}

		
	}


	fprintf(stdout, "The output: \n");

	int *data = NULL; // The data pointer.
	int pos;// The position of list entry.
	for(pos = 0 ; pos < list_size(&list) ; pos++) {
		data = (int*)list_get_at(&list, pos); // Get the element.
		if(data == NULL) {
			fprintf(stderr, "Print the data failed.\n");
			ret = -1;//print the data failed.
			continue;
		}

		fprintf(stdout, "%d\n", *data);
	}
	
	list_destroy(&list);
	if(str != NULL) { // str isn't NULL.
		free(str);
	}
	/* ret==0 is success, the other is failed. */
	return ret;
}
