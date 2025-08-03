#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "file.h"
#include "common.h"


int create_db_file(char *filename) {
	int fd = open(filename, O_RDWR);
	if (fd != -1) {
		printf("File already exists\n");
		close(fd);
		return STATUS_ERROR;
	}
	fd = open(filename, O_RDWR | O_CREAT, 00644);
	if (fd == -1) {
		perror("open");
		return STATUS_ERROR;
	}
	return fd;
}

int open_db_file(char *filename) {
	int fd = open(filename, O_RDWR, 00644);
	if (fd == -1) {
		perror("open");
		return STATUS_ERROR;
	}
	return fd;
}


