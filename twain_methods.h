#ifndef __TWAIN_METHODS_H__
#define __TWAIN_METHODS_H__ 1

#include "4DPluginAPI.h"

#if VERSIONWIN
#define USE_TWAIN_DSM 1
#define _false FALSE
#define _true TRUE
#else
#define USE_TWAIN_DSM 0
#endif

#if USE_TWAIN_DSM
#include "dsm.h"
#else
#if VERSIONMAC
#include <TWAIN/TWAIN.h>
#define SSTRCPY(d,z,s) strlcpy((char *)d,(const char *)s,(size_t)z)
#define SSTRCAT(d,z,s) strcat(d,s)
#define SSTRNCPY(d,z,s,m) strncpy(d,s,m)
#define SGETENV(d,z,n) strcpy(d,getenv(n)?getenv(n):"")
typedef void* HWND;
#endif
#endif

#define CAP_VALUE_BUF_SIZE 1024

typedef struct
{
	TW_IDENTITY identity;
	BOOL isValid;
}tw_source_t;

TW_UINT16 getCapabilityFromString(C_TEXT& Param2);
void getStringFromCapability(TW_UINT16 cap, std::wstring &stringValue);
void getCapabilityValueString(TW_CAPABILITY *tw_capability, void *p, C_TEXT& returnValue);
void setCapabilityValueString(TW_CAPABILITY *tw_capability, pTW_ONEVALUE p, char *str);
int getSizeForItemType(TW_UINT16 itemType);

#endif
