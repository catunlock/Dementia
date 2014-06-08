// Dementia.cpp: define las funciones exportadas de la aplicación DLL.
//

#include "Dementia.h"

void showErrorMessage(DWORD errorCode)
{
	LPTSTR errorText = NULL;

	FormatMessage(
	   // use system message tables to retrieve error text
	   FORMAT_MESSAGE_FROM_SYSTEM
	   // allocate buffer on local heap for error text
	   |FORMAT_MESSAGE_ALLOCATE_BUFFER
	   // Important! will fail otherwise, since we're not 
	   // (and CANNOT) pass insertion parameters
	   |FORMAT_MESSAGE_IGNORE_INSERTS,  
	   NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
	   errorCode,
	   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	   (LPTSTR)&errorText,  // output 
	   0, // minimum size for output buffer
	   NULL);   // arguments - see note 

	if ( NULL != errorText )
	{
	   // ... do something with the string - log it, display it to the user, etc.
		MessageBox(NULL, errorText, L"Error creating window", MB_OK | MB_ICONERROR);

	   // release memory allocated by FormatMessage()
	   LocalFree(errorText);
	   errorText = NULL;
	}
}
