
#ifndef _ERRORCODE_
#define _ERRORCODE_

enum ERROR_CODE
{
	ERROR_NONE,
	ERROR_FILE_ALREADY_EXIST,
	ERROR_FILE_WRITE_ERROR,
	ERROR_FILE_NOT_OPEN,
	ERROR_HOST_NOT_FOUND,
	ERROR_THREAD_NOT_CREATE,
	ERROR_DIFFERENT_FILESIZE,
	ERROR_FREE_SERVER,
	ERROR_FREE_DATA_CORRUPT,
	ERROR_UNKNOWN,
	ERROR_MAX
};

extern char *ERROR_DESC[];

#endif
