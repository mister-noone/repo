#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "parse.h"

void list_employees(struct dbheader_t *dbhdr, struct employee_t *employees) {

}

int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addstring) {

}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut) {

}

int output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees) {

}	

int write_header_to_file(int fd, struct dbheader_t **headerOut) {
	if (write(fd, *headerOut, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)) {
		perror("write");
		return STATUS_ERROR;
	}
	return STATUS_SUCCESS;
}

int validate_db_header(int fd, struct dbheader_t **headerOut) {
	struct dbheader_t *dbhdr = calloc(1, sizeof(struct dbheader_t));
	struct stat dbstat;
	if (dbhdr == NULL) {
		perror("calloc");
		return STATUS_ERROR;
	}
	if (read(fd, dbhdr, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)) {
		perror("read");
		return STATUS_ERROR;
	}
	dbhdr->magic = ntohl(dbhdr->magic);
	dbhdr->version = ntohs(dbhdr->version);
	dbhdr->count = ntohs(dbhdr->count);
	dbhdr->filesize = ntohl(dbhdr->filesize);
	fstat(fd, &dbstat);
	if (dbhdr->magic != HEADER_MAGIC || dbhdr->filesize != dbstat.st_size) {
		printf("DB file is corrupted\n");
		return STATUS_ERROR;
	}
	*headerOut = dbhdr;
	return STATUS_SUCCESS;

}

int create_db_header(int fd, struct dbheader_t **headerOut) {
	struct dbheader_t *dbhdr = calloc(1, sizeof(struct dbheader_t));
	if (dbhdr == NULL) {
		perror("calloc");
		return STATUS_ERROR;
	}
	dbhdr->magic = htonl(HEADER_MAGIC);
	dbhdr->version = htons(1);
	dbhdr->count = htons(0);
	dbhdr->filesize = htonl(sizeof(struct dbheader_t));
	*headerOut = dbhdr;
	return STATUS_SUCCESS;

}


