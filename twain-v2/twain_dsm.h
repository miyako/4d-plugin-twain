#ifndef _TWAIN_DSM_H__
#define _TWAIN_DSM_H__ 1

#include "C_TEXT.h"
#include <vector>

#define TWAIN_PROCESS_EVENT_TIMEOUT 30

#ifdef __APPLE__
#define USE_TWAIN_DSM 0
#else
#include <process.h>
#define USE_TWAIN_DSM 1
#define _false FALSE
#define _true TRUE
#endif

#if USE_TWAIN_DSM
#include "dsm.h"
#else
#if __APPLE__
#include <TWAIN/TWAIN.h>
#define SSTRCPY(d,z,s) strlcpy((char *)d,(const char *)s,(size_t)z)
#define SSTRCAT(d,z,s) strcat(d,s)
#define SSTRNCPY(d,z,s,m) strncpy(d,s,m)
#define SGETENV(d,z,n) strcpy(d,getenv(n)?getenv(n):"")
typedef void* HWND;
#endif
#endif

#define PRODUCT_VENDOR_NAME "4D"
#define PRODUCT_FAMILY_NAME "4D"
#define PRODUCT_NAME "4D"

#ifdef __cplusplus
extern "C" {
#endif
	
	TW_INT16 twain_get_condition(TW_IDENTITY *tw_identity);

	TW_UINT16 twain_dsm_open(TW_IDENTITY *tw_identity,
													 TW_USERINTERFACE *tw_userinterface,
													 void *tw_entrypoint,
													 HWND *tw_parent);
	
	TW_UINT16 twain_dsm_close(TW_IDENTITY *tw_identity,
														HWND *tw_parent);
	
	TW_UINT16 twain_source_open(TW_IDENTITY *tw_identity,
															TW_IDENTITY *tw_source_identity,
															C_TEXT& name);

	TW_UINT16 twain_source_close(TW_IDENTITY *tw_identity,
															 TW_IDENTITY *tw_source_identity);
	
	TW_UINT16 twain_source_enable(TW_IDENTITY *tw_identity,
																TW_IDENTITY *tw_source_identity,
																TW_USERINTERFACE *tw_userinterface);
	
	TW_UINT16 twain_source_disable(TW_IDENTITY *tw_identity,
																 TW_IDENTITY *tw_source_identity,
																 TW_USERINTERFACE *tw_userinterface);

	TW_INT16 twain_get_default_source(TW_IDENTITY *tw_identity, TW_IDENTITY *tw_source_identity);

	TW_INT16 twain_get_source(TW_IDENTITY *tw_identity, C_TEXT& name, TW_IDENTITY *tw_source_identity);
	
	void twain_get_sources_list(TW_IDENTITY *tw_identity, std::vector<TW_IDENTITY>& sources);

	void twain_configure(TW_IDENTITY *tw_identity,
											 TW_USERINTERFACE *tw_userinterface,
											 void *_entrypoint,
											 HWND *tw_parent,
											 TW_UINT16 majorNum, TW_UINT16 minorNum, TW_UINT16 language, TW_UINT16 country);
	
	namespace DSM
	{
		TW_HANDLE Alloc(void *_entrypoint, TW_UINT32 size);
		void Free(void *_entrypoint, TW_HANDLE h);
		TW_MEMREF Lock(void *_entrypoint, TW_HANDLE h);
		void Unlock(void *_entrypoint, TW_HANDLE h);
	}
	
#ifdef __cplusplus
}
#endif

#endif
