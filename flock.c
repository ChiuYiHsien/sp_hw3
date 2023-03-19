#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#include <time.h>

#define BUFFER 4096

int main(int argc, char* argv[]) {
	int fd, off_set = 0;
    int flock_return_value = 0;
	char buffer[BUFFER];

	fd = open ("flock.db", O_RDWR, S_IRUSR | S_IWUSR);
	printf("已開啟檔案，描述符為：%d\n", fd);

	for(int i = 0; i < 1000; i++){
		flock_return_value = flock(fd, LOCK_EX);

		lseek(fd, -4, SEEK_END);//取最後面四個單位
		read(fd, buffer, 4);
		sscanf(buffer, "%d", &off_set);

		lseek(fd, off_set, SEEK_END);
		sprintf(buffer, "%d", off_set + 1);
		write(fd, buffer, 4); //寫進去改過的值

		flock_return_value = flock(fd, LOCK_UN);

		usleep(100000);

	}
    if (flock_return_value != 0) // 若鎖定失敗
        perror("flock");

	return 0;
}
