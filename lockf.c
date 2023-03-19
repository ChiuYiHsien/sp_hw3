#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#include <assert.h>
#include <time.h>

#define BUFFER 4096

int main(int argc, char* argv[]) {
	int fd, off_set = 0;
    int f_size = 0;
	char buffer[BUFFER];

	fd = open ("lockf.db", O_RDWR, S_IRUSR | S_IWUSR);
	printf("已開啟檔案，描述符為：%d\n", fd);

	for(int i = 0; i < 1000; i++){

        f_size = lseek(fd, 0, SEEK_END); //返回文件大小


		if (lockf(fd, F_LOCK, f_size) < 0) {
            perror("lockf() 呼叫失敗");
            exit(EXIT_FAILURE);
        }

		lseek(fd, -4, SEEK_END);//取最後面四個單位
		read(fd, buffer, 4);
		sscanf(buffer, "%d", &off_set);

		lseek(fd, off_set, SEEK_END);
		sprintf(buffer, "%d", off_set + 1);
		write(fd, buffer, 4); //寫進去改過的值

		if (lockf(fd, F_ULOCK, f_size) < 0) {
            perror("unlockf() 呼叫失敗");
            exit(EXIT_FAILURE);
        }

		usleep(100000);

	}
    
	return 0;
}
