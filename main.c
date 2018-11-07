#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "simclist.h"

int main()
{
	list_t list;
	int num, ret = -1, *result;
	char *str = NULL, *endptr;
	size_t len = 0;

	if(list_init(&list) != 0) { // initial
		fprintf(stderr, "Init failed\n");
		return ret;
	}
	fprintf(stdout, "Insert your number: ");
	if(getline(&str, &len, stdin) <= 0) {
		fprintf(stderr, "The input isn't a number.\n");
		goto exit;
	}
	errno = 0 ; /* To distinguish success/failure after call */
	num = strtol(str, &endptr, 10); //String to int

	/* Check for various possible errors */

	if(errno == ERANGE) {
		perror("strtol");
		goto exit;
	}

	if(endptr == str) {
		fprintf(stderr, "No digits were found\n");
		goto exit;
	}

	if(list_append(&list, &num) < 0) { // Add an element to the list
		fprintf(stderr, "Add data failed.\n");
		goto exit;
	}
	result = (int*)list_get_at(&list, 0); // Get the first element.
	if(result == NULL) {
		fprintf(stderr, "Print the result failed.\n");
		goto exit;
	}

	fprintf(stdout, "Your number was: %d\n", *result);
	ret = 0;
exit:
	list_destroy(&list);
	if(str != NULL) // str isn't NULL
		free(str);
	return ret;
}
