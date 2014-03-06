#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void atomic_append(const char *file_name, const char **messages, int message_count)
{
	int fd;
	struct flock lock_region;
	struct stat stat_buffer;
	fd = open(file_name, O_RDWR | O_CREAT, 0644);
	if(fd == 0) {
		fprintf(stderr, "Could not open '%s'\n", file_name);
		return;
	}
	fstat(fd, &stat_buffer);
	lock_region.l_type = F_WRLCK;
	lock_region.l_whence = SEEK_SET;
	lock_region.l_start = 0;
	lock_region.l_len = stat_buffer.st_size;
	// fprintf(stderr, "fsize = %lu\n", stat_buffer.st_size);
	if(lock_region.l_len <= 0)
		lock_region.l_len = 1;
	{
		int max_trial_count = 300;
		while(max_trial_count-- > 0) {
			int fcntl_result;
			fcntl_result = fcntl(fd, F_SETLK, &lock_region);
			// fprintf(stderr, "result = %d\n", fcntl_result);
			if(fcntl_result == 0) break;
			sleep(2);
		}

	}
	fstat(fd, &stat_buffer);
	lseek(fd, stat_buffer.st_size, SEEK_SET);
	{
		int i;
		char *p;
		char *buffer = (char*)malloc(16777216);
		if(buffer == NULL) {
			fprintf(stderr, "ERROR: out of memory\n");
			return;
		}
		p = buffer;
		for(i = 0; i < message_count; i++) {
			const char *s;
			if(i) *p++ = ' ';
			s = messages[i];
			while(*s) *p++ = *s++;
		}
		*p++ = '\n';
		write(fd, buffer, p - buffer);
		free(buffer);
	}
	close(fd);
}

int main(int argc, const char **argv)
{
	if(argc < 3) {
		fprintf(stderr, "usage: atomicappend <file> <message>\n");
		return 1;
	}
	atomic_append(argv[1], argv + 2, argc - 2);
	return 0;
}

