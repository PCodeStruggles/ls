#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define BUF_SIZE 256

typedef struct {
	struct dirent d_struct_array[BUF_SIZE];
	int counter;
	int capacity;
} d_struct_array;

int main(int argc, char* argv[]) {

	char *directory_path = argv[1];
	char file_path[BUF_SIZE] = {0};

	DIR *d_stream;
	struct dirent *d_struct;
	d_struct_array d_struct_array = {0};

	struct stat file_stat_struct;

	d_stream = opendir(directory_path);
	if (d_stream == NULL) return 1;

	printf("Directory: %s\n", directory_path);

	while ((d_struct = readdir(d_stream)) != NULL) {
		if (!strcmp(d_struct->d_name, ".") || !strcmp(d_struct->d_name, "..")) continue;
		strcpy(file_path, directory_path);
		strcat(file_path, d_struct->d_name);
		stat(file_path, &file_stat_struct);
		d_struct_array.d_struct_array[d_struct_array.counter++] = *d_struct;
		printf("File: %s Last modified: %s", file_path, ctime(&file_stat_struct.st_mtime));
		memset(file_path, 0, BUF_SIZE);
	}
	closedir(d_stream);
	return 0;
}

