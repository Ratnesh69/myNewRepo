#include "FileApi.h"

int ReadFile(char * path, char** string)
{

	int bufferSize = 0, ret = 0;

	FILE *f1;

	f1 = fopen(path, "r");
	if (f1 == NULL) {
		perror("error in opening file\n");
		exit(EXIT_FAILURE);
	}

	fseek(f1, 0, 2);
	bufferSize = (int) ftell(f1);

	*string = malloc((bufferSize * sizeof(char)) + 1);

	rewind(f1);

	ret = fread(*string, 1, bufferSize, f1);

	if (bufferSize == ret) {
		printf("string: %s \n", *string);
	} else {
		printf("ret : %d !=  buffersize : %d \n", ret, bufferSize);
	}
	fclose(f1);

	return ret;
}

int FindExt(char *fileName, char *str) {
	char *ptr;
	int i = 0;
	ptr = strchr(fileName, '.');
	ptr++;
	i = 0;
	while (*ptr) {
		str[i++] = *(ptr++);
	}
	str[i] = NULL;
}

int IsFile(char *fileName)
{
	DIR* directory = opendir(fileName);

	if (directory != NULL)
	{
		closedir(directory);
		return 0;
	}

	if (errno == ENOTDIR)
	{
		return 1;
	}
	else
	{
		perror(" unknown error\n");
		return -1;
	}
}

int MoveFile(char *destPath, char *sourcePath)
{
	int bufferSize = 0, ret = 0 , sum = 0;
	FILE *f1;
	FILE *f2;
	char newFile[1024];
	char * string;
	struct tm *dateandtime;
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	dateandtime = localtime(&tv.tv_sec);



	f1 = fopen(sourcePath, "r");
	if (f1 == NULL)
	{
		perror("error in opening file\n");
		exit(EXIT_FAILURE);
	}

	fseek(f1, 0, 2);
	bufferSize = (int) ftell(f1);

	string = malloc((bufferSize * sizeof(char)) + 1);
	rewind(f1);

	ret = fread(string, 1, bufferSize, f1);
	if (bufferSize == ret)
	{
		printf("string: %s \n", string);
	}
	else
	{
		printf("ret : %d !=  buffersize : %d \n", ret, bufferSize);
	}
	fclose(f1);

	strcat(destPath,"/");

	snprintf(newFile, sizeof(newFile), "%d-%02d-%02d_%02d-%02d-%02d.txt", (1900 + dateandtime->tm_year), dateandtime->tm_mon,
			dateandtime->tm_mday, dateandtime->tm_hour, dateandtime->tm_min, dateandtime->tm_sec);

	strcat(destPath,newFile);

	f2 = fopen(destPath, "w");
	if (f2 == NULL)
	{
		perror("error in opening file\n");
		exit(EXIT_FAILURE);
	}

	ret = fwrite(string, 1, bufferSize, f2);
	if(ret <= 0)
	{
		perror("error in write file\n");
		exit(EXIT_FAILURE);
	}
	fclose(f2);

	remove(sourcePath);


	return ret;
}
