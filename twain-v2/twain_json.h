#ifndef _TWAIN_JSON_H__
#define _TWAIN_JSON_H__ 1

#include "libjson.h"

#include "4DPluginAPI.h"
#include "4DPlugin.h"

#include "twain_dsm.h"

#ifdef __cplusplus
extern "C" {
#endif
	
	void json_wconv(const char *value, std::wstring &u32);
	void json_push_back_s(JSONNODE *n, const char *value);
	void json_stringify(JSONNODE *json, CUTF16String &t, BOOL pretty);
	
	void json_set_s(JSONNODE *n, const char *value);
	void json_set_s_for_key(JSONNODE *n, json_char *key, const char *value);
	void json_set_b_for_key(JSONNODE *n, json_char *key, json_bool_t value);
	void json_set_i_for_key(JSONNODE *n, json_char *key, json_int_t value);
	
	void json_push_back_i(JSONNODE *json_scanner_option_values, TW_UINT16 cap, TW_UINT32 item);

	void twain_get_capability_value(TW_CAPABILITY *tw_capability, void *p, JSONNODE *json_scanner_option);
	void twain_get_capability_param(TW_CAPABILITY *tw_capability, void *p, JSONNODE *json_scanner_option);
	void twain_get_capability_option_name(TW_UINT16 cap, std::wstring &stringValue);
	void twain_get_option_value(TW_IDENTITY *tw_identity,
															TW_IDENTITY *tw_source_identity,
															TW_CAPABILITY *tw_capability,
															void *_entrypoint,
															JSONNODE *json_scanner_options);
	
	TW_UINT16 json_get_cap(json_char *n);
	int json_get_cap_constant(JSONNODE *n, TW_UINT16 cap);
	int getSizeForItemType(TW_UINT16 itemType);
	
#ifdef __cplusplus
}
#endif

#endif
