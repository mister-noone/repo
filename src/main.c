#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[]) {
	printf("Usage: %s -n -f <filename>\n", argv[0]);
	printf("\t -n - create a new file\n");
	printf("\t -f - file path (required)\n");
	printf("\t -h - help\n");
	return;
}

int main(int argc, char *argv[]) { 
	bool newfile = false;
	bool addingEmployee = false;
	char *filename = NULL;
	int opt;
	int fd = -1;
	char *addstring = NULL;
	struct dbheader_t *dbhdr = NULL;
	struct employee_t *employees = NULL;
	while((opt = getopt(argc, argv, ":hf:an")) != -1){
		switch(opt){
			case 'h':
				print_usage(argv);
				return 0;
			case 'n':
				newfile = true;
				break;
			case 'f':
				filename = optarg;
				break;
			case 'a':
				addstring = optarg;
				addingEmployee = true;
				break;
			case '?':
				printf("Uknown option: %c\n", optopt);
				break;

			default:
				return -1;
		}
	}
	
	if(filename == NULL){
		printf("Filename is required\n");
		print_usage(argv);
		return 0;
	}
	if (newfile) {
		fd = create_db_file(filename);
		if (fd == STATUS_ERROR) {
			printf("Could not create file: %s\n", filename);
			return -1;
		}
		if (create_db_header(fd, &dbhdr) == STATUS_ERROR) {
			printf("Could not create DB header\n");
			return -1;
		}
		if (write_header_to_file(fd, &dbhdr) == STATUS_ERROR) {
			printf("Could not write header to DB file\n");
			return -1;
		}
	} else {
		fd = open_db_file(filename);		
		if (fd == STATUS_ERROR) {
			printf("Could not open file: %s\n", filename);
			return -1;
		}
		if (validate_db_header(fd, &dbhdr) == STATUS_ERROR) {
			printf("DB header validation failed\n");
			return -1;
		}
	}

	if (addingEmployee && addstring != NULL) {
		if (read_employees(fd, dbhdr, &employees) == STATUS_ERROR) {
			printf("Could not load employees from the file\n");
			return -1;
		}
		if (add_employee(dbhdr, employees, addstring) == STATUS_ERROR) {
			printf("Could not add an employee\n");
			return -1;
		}	
		printf("Employee added!\n");
	}

	return 0;
	
}
