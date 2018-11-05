#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "simclist.h"

int main()
{
	list_t list;
	int num, ret = 0, *result;
	char *str = NULL, *endptr;
	size_t len = 0;

	if(list_init(&list) != 0) { // initial
		fprintf(stderr, "Init failed\n");
		ret = -1;
		goto exit;
	}
	fprintf(stdout, "Insert your number: ");
	if(getline(&str, &len, stdin) <= 0) {
		fprintf(stderr, "The input isn't a number.\n");
		ret = -1;
		goto exit;
	}
	num = strtol(str, &endptr, 10); //String to int
	errno = 0 ; /* To distinguish success/failure after call */

	/* Check for various possible errors */

	if((errno == ERANGE && (num == LONG_MAX || num == LONG_MIN))
	   || (errno != 0 && num == 0)) {
		perror("strtol");
		ret = -1;
		goto exit;
	}

	if(endptr == str) {
		fprintf(stderr, "No digits were found\n");
		ret = -1;
		goto exit;
	}

	if(list_append(&list, &num) < 0) { // Add an element to the list
		fprintf(stderr, "Add data failed.\n");
		ret = -1;
		goto exit;
	}
	result = (int*)list_get_at(&list, 0); // Get the first element.
	if(result == NULL) {
		fprintf(stderr, "Print the result failed.\n");
		ret = -1;
		goto exit;
	}

	fprintf(stdout, "Your number was: %d\n", *result);

exit:
	list_destroy(&list);
	free(str);
	return ret;
}
