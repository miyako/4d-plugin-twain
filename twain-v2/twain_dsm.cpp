#include "twain_dsm.h"

TW_INT16 twain_get_condition(TW_IDENTITY *tw_identity)
{
	TW_INT16 condition = 0;
	
	TW_STATUS status;
	memset(&status, 0, sizeof(TW_STATUS));
	
	if(TWRC_SUCCESS == DSM_Entry(
															 tw_identity,
															 0,
															 DG_CONTROL,
															 DAT_STATUS,
															 MSG_GET,
															 (TW_MEMREF)&status))
	{
		condition = status.ConditionCode;
	}
	return condition;
}

TW_UINT16 twain_dsm_open(TW_IDENTITY *tw_identity,
												 TW_USERINTERFACE *tw_userinterface,
												 void *tw_entrypoint,
												 HWND *tw_parent)
{
	TW_UINT16 tw_ret = DSM_Entry(
															 tw_identity,
															 0,
															 DG_CONTROL,
															 DAT_PARENT,
															 MSG_OPENDSM,
															 (TW_MEMREF)tw_parent);
	if(tw_ret == TWRC_SUCCESS)
	{
#if USE_TWAIN_DSM
		tw_userinterface->hParent = (*tw_parent);
		if((tw_identity->SupportedGroups & DF_DSM2) == DF_DSM2)
		{
			DSM_Entry(
								tw_identity,
								0,
								DG_CONTROL,
								DAT_ENTRYPOINT,
								MSG_GET,
								(TW_MEMREF)tw_entrypoint);
		}/* DF_DSM2 */
#endif
	}/* MSG_OPENDSM */
	
	return tw_ret;
}

TW_UINT16 twain_dsm_close(TW_IDENTITY *tw_identity,
												 HWND *tw_parent)
{
	TW_UINT16 tw_ret = DSM_Entry(
															 tw_identity,
															 0,
															 DG_CONTROL,
															 DAT_PARENT,
															 MSG_CLOSEDSM,
															 (TW_MEMREF)tw_parent);
	
	return tw_ret;
}

TW_UINT16 twain_source_open(TW_IDENTITY *tw_identity,
														TW_IDENTITY *tw_source_identity,
														C_TEXT& name)
{
	TW_UINT16 ret = twain_get_source(tw_identity, name, tw_source_identity);
	
	if(TWRC_SUCCESS == ret)
	{
		ret = DSM_Entry(
										tw_identity,
										0,
										DG_CONTROL,
										DAT_IDENTITY,
										MSG_OPENDS,
										(TW_MEMREF)tw_source_identity);
	}
	
	return ret;
}

TW_UINT16 twain_source_close(TW_IDENTITY *tw_identity,
														 TW_IDENTITY *tw_source_identity)
{
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														0,
														DG_CONTROL,
														DAT_IDENTITY,
														MSG_CLOSEDS,
														(TW_MEMREF)tw_source_identity);
	
	return ret;
}

TW_UINT16 twain_source_enable(TW_IDENTITY *tw_identity,
															TW_IDENTITY *tw_source_identity,
															TW_USERINTERFACE *tw_userinterface)
{
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														tw_source_identity,
														DG_CONTROL,
														DAT_USERINTERFACE,
														MSG_ENABLEDS,
														(TW_MEMREF)tw_userinterface);
	
	return ret;
}

TW_UINT16 twain_source_disable(TW_IDENTITY *tw_identity,
															 TW_IDENTITY *tw_source_identity,
															 TW_USERINTERFACE *tw_userinterface)
{
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														tw_source_identity,
														DG_CONTROL,
														DAT_USERINTERFACE,
														MSG_DISABLEDS,
														(TW_MEMREF)tw_userinterface);
	
	return ret;
}


TW_INT16 twain_get_default_source(TW_IDENTITY *tw_identity, TW_IDENTITY *tw_source_identity)
{
	memset(tw_source_identity, 0, sizeof(TW_IDENTITY));
	
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														0,
														DG_CONTROL,
														DAT_IDENTITY,
														MSG_GETDEFAULT,
														(TW_MEMREF)tw_source_identity);
	
	return ret;
}

void twain_configure(TW_IDENTITY *tw_identity,
										 TW_USERINTERFACE *tw_userinterface,
										 void *_entrypoint,
										 HWND *tw_parent,
										 TW_UINT16 majorNum, TW_UINT16 minorNum, TW_UINT16 language, TW_UINT16 country)
{
	/* init */
	memset(tw_identity, 0, sizeof(TW_IDENTITY));
	memset(tw_userinterface, 0, sizeof(TW_USERINTERFACE));
	
	tw_userinterface->ShowUI = false;
	tw_userinterface->ModalUI = false;
	
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	memset(tw_entrypoint, 0, sizeof(TW_ENTRYPOINT));
	tw_entrypoint->Size = sizeof(TW_ENTRYPOINT);
#endif
	
	*tw_parent = NULL;
	
	tw_identity->Version.Language = language;
	tw_identity->Version.Country = country;
	
	char _majorNum[3];
	sprintf(_majorNum, "%X", majorNum);
	char _minorNum[3];
	sprintf(_minorNum, "%X", minorNum);
	tw_identity->Id = 0;//always 0
	tw_identity->Version.MajorNum = atoi(_majorNum);
	tw_identity->Version.MinorNum = atoi(_minorNum);
	char _versionInfo[6];
	sprintf(_versionInfo, "%X.%X", majorNum, minorNum);
	SSTRCPY(tw_identity->Version.Info, sizeof(tw_identity->Version.Info), _versionInfo);
	
	//protocol
	tw_identity->ProtocolMajor = TWON_PROTOCOLMAJOR;
	tw_identity->ProtocolMinor = TWON_PROTOCOLMINOR;
	/*
	 note: TWAIN.framework on Mac is 1.9
	 TWAIN_32.DLL on Windows is 1.x and 32-bit only
	 TWAINDSM.DLL on Windows is 2.3 and 32-bit or 64-bit
	 TWAINDSM.DYLIB does not work on Mac (dlopen can't open .ds)
	 */
#if USE_TWAIN_DSM
	tw_identity->SupportedGroups = DF_APP2 | DG_IMAGE | DG_CONTROL;
#else
	tw_identity->SupportedGroups = DG_IMAGE | DG_CONTROL;
#endif
	
	SSTRCPY(tw_identity->Manufacturer, sizeof(tw_identity->Manufacturer), PRODUCT_VENDOR_NAME);
	SSTRCPY(tw_identity->ProductFamily, sizeof(tw_identity->ProductFamily), PRODUCT_FAMILY_NAME);
	SSTRCPY(tw_identity->ProductName, sizeof(tw_identity->ProductName), PRODUCT_NAME);
}

TW_INT16 twain_get_source(TW_IDENTITY *tw_identity, C_TEXT& name, TW_IDENTITY *tw_source_identity)
{
	TW_UINT16 ret = TWRC_FAILURE;
	
	CUTF8String _name;
	name.copyUTF8String(&_name);
	
	std::vector<TW_IDENTITY>sources;
	
	twain_get_sources_list(tw_identity, sources);
	
	for(std::vector<TW_IDENTITY>::iterator it = sources.begin(); it < sources.end(); it++)
	{
		TW_IDENTITY identity = *it;
		
		size_t len = strlen((char *)identity.ProductName);
		if(len == _name.length())
		{
			if(0 == strncmp((char *)identity.ProductName, (char *)_name.c_str(), len))
			{
				memcpy(tw_source_identity, &identity, sizeof(TW_IDENTITY));
				ret = TWRC_SUCCESS;
				break;
			}
		}
	}
	if(ret != TWRC_SUCCESS)
	{
		ret = twain_get_default_source(tw_identity, tw_source_identity);
	}
	
	return ret;
}

void twain_get_sources_list(TW_IDENTITY *tw_identity, std::vector<TW_IDENTITY>& sources)
{
	TW_INT16 condition = 0;
	
	TW_IDENTITY tw_source_identity;
	memset(&tw_source_identity, 0, sizeof(TW_IDENTITY));
	
	TW_UINT16 ret = DSM_Entry(
														tw_identity,
														0,
														DG_CONTROL,
														DAT_IDENTITY,
														MSG_GETFIRST,
														(TW_MEMREF)&tw_source_identity);
	switch (ret)
	{
		case TWRC_SUCCESS:
			sources.push_back(tw_source_identity);
			do
			{
				memset(&tw_source_identity, 0, sizeof(TW_IDENTITY));
				ret = DSM_Entry(
												tw_identity,
												0,
												DG_CONTROL,
												DAT_IDENTITY,
												MSG_GETNEXT,
												(TW_MEMREF)&tw_source_identity);
				switch (ret)
				{
					case TWRC_SUCCESS:
						sources.push_back(tw_source_identity);
						break;
					case TWRC_ENDOFLIST:
						//TWRC_ENDOFLIST
						break;
					case TWRC_FAILURE:
						condition = twain_get_condition(tw_identity);
						break;
					default:
						
						break;
				}
			}
			while (TWRC_SUCCESS == ret);
			break;
		case TWRC_ENDOFLIST:
			//TWRC_ENDOFLIST
			break;
		case TWRC_FAILURE:
			condition = twain_get_condition(tw_identity);
			break;
		default:
			
			break;
	}
}

TW_HANDLE DSM::Alloc(void *_entrypoint, TW_UINT32 size)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	if(tw_entrypoint->DSM_MemAllocate)
	{
		return tw_entrypoint->DSM_MemAllocate(size);
	}
	return ::GlobalAlloc(GPTR, size);
#endif
	
	return 0;
}
void DSM::Free(void *_entrypoint, TW_HANDLE h)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	if(tw_entrypoint->DSM_MemFree)
	{
		return tw_entrypoint->DSM_MemFree(h);
	}
	::GlobalFree(h);
#endif
	
	return;
}
TW_MEMREF DSM::Lock(void *_entrypoint, TW_HANDLE h)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	if(tw_entrypoint->DSM_MemLock)
	{
		return tw_entrypoint->DSM_MemLock(h);
	}
	return ::GlobalLock(h);
#endif
	
	return 0;
}
void DSM::Unlock(void *_entrypoint, TW_HANDLE h)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
	if(tw_entrypoint->DSM_MemUnlock)
	{
		return tw_entrypoint->DSM_MemUnlock(h);
	}
	::GlobalUnlock(h);
#endif
	
	return;
}
