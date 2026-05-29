//#define _CRT_SECURE_NO_WARNINGS
#include "FormatLastError.h"

LPSTR FormatLastError(DWORD dwError, CHAR szBuffer[])
{
	LPSTR lpBuffer = NULL;
	FormatMessage
	(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&lpBuffer,
		sizeof(lpBuffer),
		NULL
	);
	sprintf(szBuffer, "%i: %s", dwError, lpBuffer);
	LocalFree(lpBuffer);
	return szBuffer;
}