#include "twain_json.h"

void json_wconv(const char *value, std::wstring &u32)
{
	if((value) && strlen(value))
	{
		C_TEXT t;
		CUTF8String u8 = CUTF8String((const uint8_t *)value);
		
		t.setUTF8String(&u8);
		
#if VERSIONWIN
		u32 = std::wstring((wchar_t *)t.getUTF16StringPtr());
#else
		uint32_t dataSize = (t.getUTF16Length() * sizeof(wchar_t))+ sizeof(wchar_t);
		std::vector<char> buf(dataSize);
		
		PA_ConvertCharsetToCharset((char *)t.getUTF16StringPtr(),
															 t.getUTF16Length() * sizeof(PA_Unichar),
															 eVTC_UTF_16,
															 (char *)&buf[0],
															 dataSize,
															 eVTC_UTF_32);
		
		u32 = std::wstring((wchar_t *)&buf[0]);
#endif
	}else
	{
		u32 = L"";
	}
	
}

void json_push_back_s(JSONNODE *n, const char *value)
{
	if(n)
	{
		if(value)
		{
			std::wstring w32;
			json_wconv(value, w32);
			
			JSONNODE *e = json_new(JSON_STRING);
			json_set_a(e, w32.c_str());
			json_push_back(n, e);
		}else
		{
			JSONNODE *e = json_new(JSON_STRING);
			json_nullify(e);
			json_push_back(n, e);
		}
	}
	
}

void json_set_s(JSONNODE *n, const char *value)
{
	if(n)
	{
		if(value)
		{
			std::wstring w32;
			json_wconv(value, w32);
			json_set_a(n, w32.c_str());
		}else
		{
			json_nullify(n);
		}
	}
}

void json_set_s_for_key(JSONNODE *n, json_char *key, const char *value)
{
	if(n)
	{
		if(value)
		{
			std::wstring w32;
			json_wconv(value, w32);
			
			JSONNODE *e = json_get(n, key);
			if(e)
			{
				json_set_a(e, w32.c_str());//over-write existing value
			}else
			{
				json_push_back(n, json_new_a(key, w32.c_str()));
			}
			
		}else
		{
			JSONNODE *e = json_get(n, key);
			if(e)
			{
				json_nullify(e);//over-write existing value
			}else
			{
				JSONNODE *node = json_new_a(key, L"");
				json_nullify(node);
				json_push_back(n, node);
			}
		}
	}
}

void json_set_b_for_key(JSONNODE *n, json_char *key, json_bool_t value)
{
	if(n)
	{
		JSONNODE *e = json_get(n, key);
		if(e)
		{
			json_set_b(e, value);//over-write existing value
		}else
		{
			json_push_back(n, json_new_b(key, value));
		}
	}
}

void json_set_i_for_key(JSONNODE *n, json_char *key, json_int_t value)
{
	if(n)
	{
		JSONNODE *e = json_get(n, key);
		if(e)
		{
			json_set_i(e, value);//over-write existing value
		}else
		{
			json_push_back(n, json_new_i(key, value));
		}
	}
}

void json_stringify(JSONNODE *json, CUTF16String &t, BOOL pretty)
{
	json_char *json_string = pretty ? json_write_formatted(json) : json_write(json);
	std::wstring wstr = std::wstring(json_string);
#if VERSIONWIN
	t = CUTF16String((const PA_Unichar *)wstr.c_str(), (uint32_t)wstr.length());
#else
	uint32_t dataSize = (uint32_t)((wstr.length() * sizeof(wchar_t))+ sizeof(PA_Unichar));
	std::vector<char> buf(dataSize);
	//returns byte size in toString (in this case, need to /2 to get characters)
	uint32_t len = PA_ConvertCharsetToCharset((char *)wstr.c_str(),
																						(PA_long32)(wstr.length() * sizeof(wchar_t)),
																						eVTC_UTF_32,
																						(char *)&buf[0],
																						dataSize,
																						eVTC_UTF_16);
	t = CUTF16String((const PA_Unichar *)&buf[0], len/sizeof(PA_Unichar));
#endif
	json_free(json_string);
}

void json_push_back_i(JSONNODE *json_scanner_option_values, TW_UINT16 cap, TW_UINT32 item)
{
	if(json_scanner_option_values)
	{
		char str[CAP_VALUE_BUF_SIZE];
		memset(str, 0, sizeof(str));
		
		BOOL string_or_constant_value = TRUE;
		
		switch(cap)
		{
				//convert to constant
#if USE_TWAIN_DSM
			case ICAP_AUTOSIZE:
			{
				switch(item)
				{
					case TWAS_NONE:
						sprintf(str, "%s", "TWAS_NONE");break;
					case TWAS_AUTO:
						sprintf(str, "%s", "TWAS_AUTO");break;
					case TWAS_CURRENT:
						sprintf(str, "%s", "TWAS_CURRENT");break;
				}
			}
				break;
			case ICAP_AUTODISCARDBLANKPAGES:
			{
				switch(item)
				{
					case TWBP_DISABLE:
						sprintf(str, "%s", "TWBP_DISABLE");break;
					case TWBP_AUTO:
						sprintf(str, "%s", "TWBP_AUTO");break;
				}
			}
				break;
			case CAP_CAMERASIDE:
			{
				switch(item)
				{
					case TWCS_BOTH:
						sprintf(str, "%s", "TWCS_BOTH");break;
					case TWCS_TOP:
						sprintf(str, "%s", "TWCS_TOP");break;
					case TWCS_BOTTOM:
						sprintf(str, "%s", "TWCS_BOTTOM");break;
				}
			}
				break;
			case ICAP_FEEDERTYPE:
			{
				switch(item)
				{
					case TWFE_GENERAL:
						sprintf(str, "%s", "TWFE_GENERAL");break;
					case TWFE_PHOTO:
						sprintf(str, "%s", "TWFE_PHOTO");break;
				}
			}
				break;
			case CAP_FEEDERPOCKET:
			{
				switch(item)
				{
					case TWFP_POCKETERROR:
						sprintf(str, "%s", "TWFP_POCKETERROR");break;
					case TWFP_POCKET1:
						sprintf(str, "%s", "TWFP_POCKET1");break;
					case TWFP_POCKET2:
						sprintf(str, "%s", "TWFP_POCKET2");break;
					case TWFP_POCKET3:
						sprintf(str, "%s", "TWFP_POCKET3");break;
					case TWFP_POCKET4:
						sprintf(str, "%s", "TWFP_POCKET4");break;
					case TWFP_POCKET5:
						sprintf(str, "%s", "TWFP_POCKET5");break;
					case TWFP_POCKET6:
						sprintf(str, "%s", "TWFP_POCKET6");break;
					case TWFP_POCKET7:
						sprintf(str, "%s", "TWFP_POCKET7");break;
					case TWFP_POCKET8:
						sprintf(str, "%s", "TWFP_POCKET8");break;
					case TWFP_POCKET9:
						sprintf(str, "%s", "TWFP_POCKET9");break;
					case TWFP_POCKET10:
						sprintf(str, "%s", "TWFP_POCKET10");break;
					case TWFP_POCKET11:
						sprintf(str, "%s", "TWFP_POCKET11");break;
					case TWFP_POCKET12:
						sprintf(str, "%s", "TWFP_POCKET12");break;
					case TWFP_POCKET13:
						sprintf(str, "%s", "TWFP_POCKET13");break;
					case TWFP_POCKET14:
						sprintf(str, "%s", "TWFP_POCKET14");break;
					case TWFP_POCKET15:
						sprintf(str, "%s", "TWFP_POCKET15");break;
					case TWFP_POCKET16:
						sprintf(str, "%s", "TWFP_POCKET16");break;
				}
			}
				break;
			case ICAP_ICCPROFILE:
			{
				switch(item)
				{
					case TWIC_NONE:
						sprintf(str, "%s", "TWIC_NONE");break;
					case TWIC_LINK:
						sprintf(str, "%s", "TWIC_LINK");break;
					case TWIC_EMBED:
						sprintf(str, "%s", "TWIC_EMBED");break;
				}
			}
				break;
			case ICAP_IMAGEMERGE:
			{
				switch(item)
				{
					case TWIM_NONE:
						sprintf(str, "%s", "TWIM_NONE");break;
					case TWIM_FRONTONTOP:
						sprintf(str, "%s", "TWIM_FRONTONTOP");break;
					case TWIM_FRONTONBOTTOM:
						sprintf(str, "%s", "TWIM_FRONTONBOTTOM");break;
					case TWIM_FRONTONLEFT:
						sprintf(str, "%s", "TWIM_FRONTONLEFT");break;
					case TWIM_FRONTONRIGHT:
						sprintf(str, "%s", "TWIM_FRONTONRIGHT");break;
				}
			}
				break;
			case CAP_SEGMENTED:
			{
				switch(item)
				{
					case TWSG_NONE:
						sprintf(str, "%s", "TWSG_NONE");break;
					case TWSG_AUTO:
						sprintf(str, "%s", "TWSG_AUTO");break;
					case TWSG_MANUAL:
						sprintf(str, "%s", "TWSG_MANUAL");break;
				}
			}
				break;
#endif
			case CAP_ALARMS:
			{
				switch(item)
				{
					case TWAL_ALARM:
						sprintf(str, "%s", "TWAL_ALARM");break;
					case TWAL_FEEDERERROR:
						sprintf(str, "%s", "TWAL_FEEDERERROR");break;
					case TWAL_FEEDERWARNING:
						sprintf(str, "%s", "TWAL_FEEDERWARNING");break;
					case TWAL_BARCODE:
						sprintf(str, "%s", "TWAL_BARCODE");break;
					case TWAL_DOUBLEFEED:
						sprintf(str, "%s", "TWAL_DOUBLEFEED");break;
					case TWAL_JAM:
						sprintf(str, "%s", "TWAL_JAM");break;
					case TWAL_PATCHCODE:
						sprintf(str, "%s", "TWAL_PATCHCODE");break;
					case TWAL_POWER:
						sprintf(str, "%s", "TWAL_POWER");break;
					case TWAL_SKEW:
						sprintf(str, "%s", "TWAL_SKEW");break;
				}
			}
				break;
			case ICAP_COMPRESSION:
			{
				switch(item)
				{
					case TWCP_NONE:
						sprintf(str, "%s", "TWCP_NONE");break;
					case TWCP_PACKBITS:
						sprintf(str, "%s", "TWCP_PACKBITS");break;
					case TWCP_GROUP31D:
						sprintf(str, "%s", "TWCP_GROUP31D");break;
					case TWCP_GROUP31DEOL:
						sprintf(str, "%s", "TWCP_GROUP31DEOL");break;
					case TWCP_GROUP32D:
						sprintf(str, "%s", "TWCP_GROUP32D");break;
					case TWCP_GROUP4:
						sprintf(str, "%s", "TWCP_GROUP4");break;
					case TWCP_JPEG:
						sprintf(str, "%s", "TWCP_JPEG");break;
					case TWCP_LZW:
						sprintf(str, "%s", "TWCP_LZW");break;
					case TWCP_JBIG:
						sprintf(str, "%s", "TWCP_JBIG");break;
					case TWCP_PNG:
						sprintf(str, "%s", "TWCP_PNG");break;
					case TWCP_RLE4:
						sprintf(str, "%s", "TWCP_RLE4");break;
					case TWCP_RLE8:
						sprintf(str, "%s", "TWCP_RLE8");break;
					case TWCP_BITFIELDS:
						sprintf(str, "%s", "TWCP_BITFIELDS");break;
				}
			}
				break;
			case ICAP_BARCODESEARCHMODE:
			{
				switch(item)
				{
					case TWBD_HORZ:
						sprintf(str, "%s", "TWBD_HORZ");break;
					case TWBD_VERT:
						sprintf(str, "%s", "TWBD_VERT");break;
					case TWBD_HORZVERT:
						sprintf(str, "%s", "TWBD_HORZVERT");break;
					case TWBD_VERTHORZ:
						sprintf(str, "%s", "TWBD_VERTHORZ");break;
				}
			}
				break;
			case ICAP_BITORDER:
			{
				switch(item)
				{
					case TWBO_LSBFIRST:
						sprintf(str, "%s", "TWBO_LSBFIRST");break;
					case TWBO_MSBFIRST:
						sprintf(str, "%s", "TWBO_MSBFIRST");break;
				}
			}
				break;
			case ICAP_BITDEPTHREDUCTION:
			{
				switch(item)
				{
					case TWBR_THRESHOLD:
						sprintf(str, "%s", "TWBR_THRESHOLD");break;
					case TWBR_HALFTONE:
						sprintf(str, "%s", "TWBR_HALFTONE");break;
					case TWBR_CUSTHALFTONE:
						sprintf(str, "%s", "TWBR_CUSTHALFTONE");break;
					case TWBR_DIFFUSION:
						sprintf(str, "%s", "TWBR_DIFFUSION");break;
				}
			}
				break;
			case ICAP_SUPPORTEDBARCODETYPES:
			case TWEI_BARCODETYPE:
			{
				switch(item)
				{
					case TWBT_3OF9:
						sprintf(str, "%s", "TWBT_3OF9");break;
					case TWBT_2OF5INTERLEAVED:
						sprintf(str, "%s", "TWBT_2OF5INTERLEAVED");break;
					case TWBT_2OF5NONINTERLEAVED:
						sprintf(str, "%s", "TWBT_2OF5NONINTERLEAVED");break;
					case TWBT_CODE93:
						sprintf(str, "%s", "TWBT_CODE93");break;
					case TWBT_CODE128:
						sprintf(str, "%s", "TWBT_CODE128");break;
					case TWBT_UCC128:
						sprintf(str, "%s", "TWBT_UCC128");break;
					case TWBT_CODABAR:
						sprintf(str, "%s", "TWBT_CODABAR");break;
					case TWBT_UPCA:
						sprintf(str, "%s", "TWBT_UPCA");break;
					case TWBT_UPCE:
						sprintf(str, "%s", "TWBT_UPCE");break;
					case TWBT_EAN8:
						sprintf(str, "%s", "TWBT_EAN8");break;
					case TWBT_EAN13:
						sprintf(str, "%s", "TWBT_EAN13");break;
					case TWBT_POSTNET:
						sprintf(str, "%s", "TWBT_POSTNET");break;
					case TWBT_PDF417:
						sprintf(str, "%s", "TWBT_PDF417");break;
					case TWBT_2OF5INDUSTRIAL:
						sprintf(str, "%s", "TWBT_2OF5INDUSTRIAL");break;
					case TWBT_2OF5MATRIX:
						sprintf(str, "%s", "TWBT_2OF5MATRIX");break;
					case TWBT_2OF5DATALOGIC:
						sprintf(str, "%s", "TWBT_2OF5DATALOGIC");break;
					case TWBT_2OF5IATA:
						sprintf(str, "%s", "TWBT_2OF5IATA");break;
					case TWBT_3OF9FULLASCII:
						sprintf(str, "%s", "TWBT_3OF9FULLASCII");break;
					case TWBT_CODABARWITHSTARTSTOP:
						sprintf(str, "%s", "TWBT_CODABARWITHSTARTSTOP");break;
					case TWBT_MAXICODE:
						sprintf(str, "%s", "TWBT_MAXICODE");break;
				}
			}
				break;
			case CAP_CLEARBUFFERS:
			{
				switch(item)
				{
					case TWCB_AUTO:
						sprintf(str, "%s", "TWCB_AUTO");break;
					case TWCB_CLEAR:
						sprintf(str, "%s", "TWCB_CLEAR");break;
					case TWCB_NOCLEAR:
						sprintf(str, "%s", "TWCB_NOCLEAR");break;
				}
			}
				break;
			case CAP_DEVICEEVENT:
			{
				switch(item)
				{
					case TWDE_CUSTOMEVENTS:
						sprintf(str, "%s", "TWDE_CUSTOMEVENTS");break;
					case TWDE_CHECKAUTOMATICCAPTURE:
						sprintf(str, "%s", "TWDE_CHECKAUTOMATICCAPTURE");break;
					case TWDE_CHECKBATTERY:
						sprintf(str, "%s", "TWDE_CHECKBATTERY");break;
					case TWDE_CHECKDEVICEONLINE:
						sprintf(str, "%s", "TWDE_CHECKDEVICEONLINE");break;
					case TWDE_CHECKFLASH:
						sprintf(str, "%s", "TWDE_CHECKFLASH");break;
					case TWDE_CHECKPOWERSUPPLY:
						sprintf(str, "%s", "TWDE_CHECKPOWERSUPPLY");break;
					case TWDE_CHECKRESOLUTION:
						sprintf(str, "%s", "TWDE_CHECKRESOLUTION");break;
					case TWDE_DEVICEADDED:
						sprintf(str, "%s", "TWDE_DEVICEADDED");break;
					case TWDE_DEVICEOFFLINE:
						sprintf(str, "%s", "TWDE_DEVICEOFFLINE");break;
					case TWDE_DEVICEREADY:
						sprintf(str, "%s", "TWDE_DEVICEREADY");break;
					case TWDE_DEVICEREMOVED:
						sprintf(str, "%s", "TWDE_DEVICEREMOVED");break;
					case TWDE_IMAGECAPTURED:
						sprintf(str, "%s", "TWDE_IMAGECAPTURED");break;
					case TWDE_IMAGEDELETED:
						sprintf(str, "%s", "TWDE_IMAGEDELETED");break;
					case TWDE_PAPERDOUBLEFEED:
						sprintf(str, "%s", "TWDE_PAPERDOUBLEFEED");break;
					case TWDE_PAPERJAM:
						sprintf(str, "%s", "TWDE_PAPERJAM");break;
					case TWDE_LAMPFAILURE:
						sprintf(str, "%s", "TWDE_LAMPFAILURE");break;
					case TWDE_POWERSAVE:
						sprintf(str, "%s", "TWDE_POWERSAVE");break;
					case TWDE_POWERSAVENOTIFY:
						sprintf(str, "%s", "TWDE_POWERSAVENOTIFY");break;
				}
			}
				break;
			case CAP_DUPLEX:
			{
				switch(item)
				{
					case TWDX_NONE:
						sprintf(str, "%s", "TWDX_NONE");break;
					case TWDX_1PASSDUPLEX:
						sprintf(str, "%s", "TWDX_1PASSDUPLEX");break;
					case TWDX_2PASSDUPLEX:
						sprintf(str, "%s", "TWDX_2PASSDUPLEX");break;
				}
			}
				break;
			case CAP_FEEDERALIGNMENT:
			{
				switch(item)
				{
					case TWFA_NONE:
						sprintf(str, "%s", "TWFA_NONE");break;
					case TWFA_LEFT:
						sprintf(str, "%s", "TWFA_LEFT");break;
					case TWFA_CENTER:
						sprintf(str, "%s", "TWFA_CENTER");break;
					case TWFA_RIGHT:
						sprintf(str, "%s", "TWFA_RIGHT");break;
				}
			}
				break;
			case ICAP_IMAGEFILEFORMAT:
			{
				switch(item)
				{
					case TWFF_TIFF:
						sprintf(str, "%s", "TWFF_TIFF");break;
					case TWFF_PICT:
						sprintf(str, "%s", "TWFF_PICT");break;
					case TWFF_BMP:
						sprintf(str, "%s", "TWFF_BMP");break;
					case TWFF_XBM:
						sprintf(str, "%s", "TWFF_XBM");break;
					case TWFF_JFIF:
						sprintf(str, "%s", "TWFF_JFIF");break;
					case TWFF_FPX:
						sprintf(str, "%s", "TWFF_FPX");break;
					case TWFF_TIFFMULTI:
						sprintf(str, "%s", "TWFF_TIFFMULTI");break;
					case TWFF_PNG:
						sprintf(str, "%s", "TWFF_PNG");break;
					case TWFF_SPIFF:
						sprintf(str, "%s", "TWFF_SPIFF");break;
					case TWFF_EXIF:
						sprintf(str, "%s", "TWFF_EXIF");break;
				}
			}
				break;
			case ICAP_FLASHUSED2:
			{
				switch(item)
				{
					case TWFL_NONE:
						sprintf(str, "%s", "TWFL_NONE");break;
					case TWFL_OFF:
						sprintf(str, "%s", "TWFL_OFF");break;
					case TWFL_ON:
						sprintf(str, "%s", "TWFL_ON");break;
					case TWFL_AUTO:
						sprintf(str, "%s", "TWFL_AUTO");break;
					case TWFL_REDEYE:
						sprintf(str, "%s", "TWFL_REDEYE");break;
				}
			}
				break;
			case CAP_FEEDERORDER:
			{
				switch(item)
				{
					case TWFO_FIRSTPAGEFIRST:
						sprintf(str, "%s", "TWFO_FIRSTPAGEFIRST");break;
					case TWFO_LASTPAGEFIRST:
						sprintf(str, "%s", "TWFO_LASTPAGEFIRST");break;
				}
			}
				break;
			case ICAP_FLIPROTATION:
			{
				switch(item)
				{
					case TWFR_BOOK:
						sprintf(str, "%s", "TWFR_BOOK");break;
					case TWFR_FANFOLD:
						sprintf(str, "%s", "TWFR_FANFOLD");break;
				}
			}
				break;
			case ICAP_FILTER:
			{
				switch(item)
				{
					case TWFT_RED:
						sprintf(str, "%s", "TWFT_RED");break;
					case TWFT_GREEN:
						sprintf(str, "%s", "TWFT_GREEN");break;
					case TWFT_BLUE:
						sprintf(str, "%s", "TWFT_BLUE");break;
					case TWFT_NONE:
						sprintf(str, "%s", "TWFT_NONE");break;
					case TWFT_WHITE:
						sprintf(str, "%s", "TWFT_WHITE");break;
					case TWFT_CYAN:
						sprintf(str, "%s", "TWFT_CYAN");break;
					case TWFT_MAGENTA:
						sprintf(str, "%s", "TWFT_MAGENTA");break;
					case TWFT_YELLOW:
						sprintf(str, "%s", "TWFT_YELLOW");break;
					case TWFT_BLACK:
						sprintf(str, "%s", "TWFT_BLACK");break;
				}
			}
				break;
			case ICAP_IMAGEFILTER:
			{
				switch(item)
				{
					case TWIF_NONE:
						sprintf(str, "%s", "TWIF_NONE");break;
					case TWIF_AUTO:
						sprintf(str, "%s", "TWIF_AUTO");break;
					case TWIF_LOWPASS:
						sprintf(str, "%s", "TWIF_LOWPASS");break;
					case TWIF_BANDPASS:
						sprintf(str, "%s", "TWIF_BANDPASS");break;
					case TWIF_HIGHPASS:
						sprintf(str, "%s", "TWIF_HIGHPASS");break;
						//				case TWIF_TEXT:
						//					sprintf(str, "%s", "TWIF_TEXT");break;
						//				case TWIF_FINELINE:
						//					sprintf(str, "%s", "TWIF_FINELINE");break;
				}
			}
				break;
			case CAP_JOBCONTROL:
			{
				switch(item)
				{
					case TWJC_NONE:
						sprintf(str, "%s", "TWJC_NONE");break;
					case TWJC_JSIC:
						sprintf(str, "%s", "TWJC_JSIC");break;
					case TWJC_JSIS:
						sprintf(str, "%s", "TWJC_JSIS");break;
					case TWJC_JSXC:
						sprintf(str, "%s", "TWJC_JSXC");break;
					case TWJC_JSXS:
						sprintf(str, "%s", "TWJC_JSXS");break;
				}
			}
				break;
			case ICAP_JPEGQUALITY:
			{
				switch(item)
				{
					case TWJQ_UNKNOWN:
						sprintf(str, "%s", "TWJQ_UNKNOWN");break;
					case TWJQ_LOW:
						sprintf(str, "%s", "TWJQ_LOW");break;
					case TWJQ_MEDIUM:
						sprintf(str, "%s", "TWJQ_MEDIUM");break;
					case TWJQ_HIGH:
						sprintf(str, "%s", "TWJQ_HIGH");break;
				}
			}
				break;
			case ICAP_LIGHTPATH:
			{
				switch(item)
				{
					case TWLP_REFLECTIVE:
						sprintf(str, "%s", "TWLP_REFLECTIVE");break;
					case TWLP_TRANSMISSIVE:
						sprintf(str, "%s", "TWLP_TRANSMISSIVE");break;
				}
			}
				break;
			case ICAP_LIGHTSOURCE:
			{
				switch(item)
				{
					case TWLS_RED:
						sprintf(str, "%s", "TWLS_RED");break;
					case TWLS_GREEN:
						sprintf(str, "%s", "TWLS_GREEN");break;
					case TWLS_BLUE:
						sprintf(str, "%s", "TWLS_BLUE");break;
					case TWLS_NONE:
						sprintf(str, "%s", "TWLS_NONE");break;
					case TWLS_WHITE:
						sprintf(str, "%s", "TWLS_WHITE");break;
					case TWLS_UV:
						sprintf(str, "%s", "TWLS_UV");break;
					case TWLS_IR:
						sprintf(str, "%s", "TWLS_IR");break;
				}
			}
				break;
			case ICAP_NOISEFILTER:
			{
				switch(item)
				{
					case TWNF_NONE:
						sprintf(str, "%s", "TWNF_NONE");break;
					case TWNF_AUTO:
						sprintf(str, "%s", "TWNF_AUTO");break;
					case TWNF_LONEPIXEL:
						sprintf(str, "%s", "TWNF_LONEPIXEL");break;
					case TWNF_MAJORITYRULE:
						sprintf(str, "%s", "TWNF_MAJORITYRULE");break;
				}
			}
				break;
			case ICAP_ORIENTATION:
			{
				switch(item)
				{
					case TWOR_ROT0:
						sprintf(str, "%s", "TWOR_ROT0");break;
					case TWOR_ROT90:
						sprintf(str, "%s", "TWOR_ROT90");break;
					case TWOR_ROT180:
						sprintf(str, "%s", "TWOR_ROT180");break;
					case TWOR_ROT270:
						sprintf(str, "%s", "TWOR_ROT270");break;
						//				case TWOR_PORTRAIT:
						//					sprintf(str, "%s", "TWOR_PORTRAIT");break;
						//				case TWOR_LANDSCAPE:
						//					sprintf(str, "%s", "TWOR_LANDSCAPE");break;
				}
			}
				break;
			case ICAP_OVERSCAN:
			{
				switch(item)
				{
					case TWOV_NONE:
						sprintf(str, "%s", "TWOV_NONE");break;
					case TWOV_AUTO:
						sprintf(str, "%s", "TWOV_AUTO");break;
					case TWOV_TOPBOTTOM:
						sprintf(str, "%s", "TWOV_TOPBOTTOM");break;
					case TWOV_LEFTRIGHT:
						sprintf(str, "%s", "TWOV_LEFTRIGHT");break;
					case TWOV_ALL:
						sprintf(str, "%s", "TWOV_ALL");break;
				}
			}
				break;
			case ICAP_PLANARCHUNKY:
			{
				switch(item)
				{
					case TWPC_CHUNKY:
						sprintf(str, "%s", "TWPC_CHUNKY");break;
					case TWPC_PLANAR:
						sprintf(str, "%s", "TWPC_PLANAR");break;
				}
			}
				break;
			case ICAP_PIXELFLAVOR:
			{
				switch(item)
				{
					case TWPF_CHOCOLATE:
						sprintf(str, "%s", "TWPF_CHOCOLATE");break;
					case TWPF_VANILLA:
						sprintf(str, "%s", "TWPF_VANILLA");break;
				}
			}
				break;
			case CAP_PRINTERMODE:
			{
				switch(item)
				{
					case TWPM_SINGLESTRING:
						sprintf(str, "%s", "TWPM_SINGLESTRING");break;
					case TWPM_MULTISTRING:
						sprintf(str, "%s", "TWPM_MULTISTRING");break;
					case TWPM_COMPOUNDSTRING:
						sprintf(str, "%s", "TWPM_COMPOUNDSTRING");break;
				}
			}
				break;
			case CAP_PRINTER:
			{
				switch(item)
				{
					case TWPR_IMPRINTERTOPBEFORE:
						sprintf(str, "%s", "TWPR_IMPRINTERTOPBEFORE");break;
					case TWPR_IMPRINTERTOPAFTER:
						sprintf(str, "%s", "TWPR_IMPRINTERTOPAFTER");break;
					case TWPR_IMPRINTERBOTTOMBEFORE:
						sprintf(str, "%s", "TWPR_IMPRINTERBOTTOMBEFORE");break;
					case TWPR_IMPRINTERBOTTOMAFTER:
						sprintf(str, "%s", "TWPR_IMPRINTERBOTTOMAFTER");break;
					case TWPR_ENDORSERTOPBEFORE:
						sprintf(str, "%s", "TWPR_ENDORSERTOPBEFORE");break;
					case TWPR_ENDORSERTOPAFTER:
						sprintf(str, "%s", "TWPR_ENDORSERTOPAFTER");break;
					case TWPR_ENDORSERBOTTOMBEFORE:
						sprintf(str, "%s", "TWPR_ENDORSERBOTTOMBEFORE");break;
					case TWPR_ENDORSERBOTTOMAFTER:
						sprintf(str, "%s", "TWPR_ENDORSERBOTTOMAFTER");break;
				}
			}
				break;
			case CAP_POWERSUPPLY:
			{
				switch(item)
				{
					case TWPS_EXTERNAL:
						sprintf(str, "%s", "TWPS_EXTERNAL");break;
					case TWPS_BATTERY:
						sprintf(str, "%s", "TWPS_BATTERY");break;
				}
			}
				break;
			case ICAP_PIXELTYPE:
			{
				switch(item)
				{
					case TWPT_BW:
						sprintf(str, "%s", "TWPT_BW");break;
					case TWPT_GRAY:
						sprintf(str, "%s", "TWPT_GRAY");break;
					case TWPT_RGB:
						sprintf(str, "%s", "TWPT_RGB");break;
					case TWPT_PALETTE:
						sprintf(str, "%s", "TWPT_PALETTE");break;
					case TWPT_CMY:
						sprintf(str, "%s", "TWPT_CMY");break;
					case TWPT_CMYK:
						sprintf(str, "%s", "TWPT_CMYK");break;
					case TWPT_YUV:
						sprintf(str, "%s", "TWPT_YUV");break;
					case TWPT_YUVK:
						sprintf(str, "%s", "TWPT_YUVK");break;
					case TWPT_CIEXYZ:
						sprintf(str, "%s", "TWPT_CIEXYZ");break;
				}
			}
				break;
			case ICAP_SUPPORTEDSIZES:
			{
				switch(item)
				{
					case TWSS_NONE:
						sprintf(str, "%s", "TWSS_NONE");break;
					case TWSS_A4LETTER:
						sprintf(str, "%s", "TWSS_A4LETTER");break;
					case TWSS_B5LETTER:
						sprintf(str, "%s", "TWSS_B5LETTER");break;
					case TWSS_USLETTER:
						sprintf(str, "%s", "TWSS_USLETTER");break;
					case TWSS_USLEGAL:
						sprintf(str, "%s", "TWSS_USLEGAL");break;
					case TWSS_A5:
						sprintf(str, "%s", "TWSS_A5");break;
					case TWSS_B4:
						sprintf(str, "%s", "TWSS_B4");break;
					case TWSS_B6:
						sprintf(str, "%s", "TWSS_B6");break;
						//				case TWSS_B:
						//					sprintf(str, "%s", "TWSS_B");break;
					case TWSS_USLEDGER:
						sprintf(str, "%s", "TWSS_USLEDGER");break;
					case TWSS_USEXECUTIVE:
						sprintf(str, "%s", "TWSS_USEXECUTIVE");break;
					case TWSS_A3:
						sprintf(str, "%s", "TWSS_A3");break;
					case TWSS_B3:
						sprintf(str, "%s", "TWSS_B3");break;
					case TWSS_A6:
						sprintf(str, "%s", "TWSS_A6");break;
					case TWSS_C4:
						sprintf(str, "%s", "TWSS_C4");break;
					case TWSS_C5:
						sprintf(str, "%s", "TWSS_C5");break;
					case TWSS_C6:
						sprintf(str, "%s", "TWSS_C6");break;
					case TWSS_4A0:
						sprintf(str, "%s", "TWSS_4A0");break;
					case TWSS_2A0:
						sprintf(str, "%s", "TWSS_2A0");break;
					case TWSS_A0:
						sprintf(str, "%s", "TWSS_A0");break;
					case TWSS_A1:
						sprintf(str, "%s", "TWSS_A1");break;
					case TWSS_A2:
						sprintf(str, "%s", "TWSS_A2");break;
						//				case TWSS_A4:
						//					sprintf(str, "%s", "TWSS_A4");break;
					case TWSS_A7:
						sprintf(str, "%s", "TWSS_A7");break;
					case TWSS_A8:
						sprintf(str, "%s", "TWSS_A8");break;
					case TWSS_A9:
						sprintf(str, "%s", "TWSS_A9");break;
					case TWSS_A10:
						sprintf(str, "%s", "TWSS_A10");break;
					case TWSS_ISOB0:
						sprintf(str, "%s", "TWSS_ISOB0");break;
					case TWSS_ISOB1:
						sprintf(str, "%s", "TWSS_ISOB1");break;
					case TWSS_ISOB2:
						sprintf(str, "%s", "TWSS_ISOB2");break;
						//				case TWSS_ISOB3:
						//					sprintf(str, "%s", "TWSS_ISOB3");break;
						//				case TWSS_ISOB4:
						//					sprintf(str, "%s", "TWSS_ISOB4");break;
					case TWSS_ISOB5:
						sprintf(str, "%s", "TWSS_ISOB5");break;
						//				case TWSS_ISOB6:
						//					sprintf(str, "%s", "TWSS_ISOB6");break;
					case TWSS_ISOB7:
						sprintf(str, "%s", "TWSS_ISOB7");break;
					case TWSS_ISOB8:
						sprintf(str, "%s", "TWSS_ISOB8");break;
					case TWSS_ISOB9:
						sprintf(str, "%s", "TWSS_ISOB9");break;
					case TWSS_ISOB10:
						sprintf(str, "%s", "TWSS_ISOB10");break;
					case TWSS_JISB0:
						sprintf(str, "%s", "TWSS_JISB0");break;
					case TWSS_JISB1:
						sprintf(str, "%s", "TWSS_JISB1");break;
					case TWSS_JISB2:
						sprintf(str, "%s", "TWSS_JISB2");break;
					case TWSS_JISB3:
						sprintf(str, "%s", "TWSS_JISB3");break;
					case TWSS_JISB4:
						sprintf(str, "%s", "TWSS_JISB4");break;
						//				case TWSS_JISB5:
						//					sprintf(str, "%s", "TWSS_JISB5");break;
					case TWSS_JISB6:
						sprintf(str, "%s", "TWSS_JISB6");break;
					case TWSS_JISB7:
						sprintf(str, "%s", "TWSS_JISB7");break;
					case TWSS_JISB8:
						sprintf(str, "%s", "TWSS_JISB8");break;
					case TWSS_JISB9:
						sprintf(str, "%s", "TWSS_JISB9");break;
					case TWSS_JISB10:
						sprintf(str, "%s", "TWSS_JISB10");break;
					case TWSS_C0:
						sprintf(str, "%s", "TWSS_C0");break;
					case TWSS_C1:
						sprintf(str, "%s", "TWSS_C1");break;
					case TWSS_C2:
						sprintf(str, "%s", "TWSS_C2");break;
					case TWSS_C3:
						sprintf(str, "%s", "TWSS_C3");break;
					case TWSS_C7:
						sprintf(str, "%s", "TWSS_C7");break;
					case TWSS_C8:
						sprintf(str, "%s", "TWSS_C8");break;
					case TWSS_C9:
						sprintf(str, "%s", "TWSS_C9");break;
					case TWSS_C10:
						sprintf(str, "%s", "TWSS_C10");break;
					case TWSS_USSTATEMENT:
						sprintf(str, "%s", "TWSS_USSTATEMENT");break;
					case TWSS_BUSINESSCARD:
						sprintf(str, "%s", "TWSS_BUSINESSCARD");break;
				}
			}
				break;
			case ICAP_XFERMECH:
			{
				switch(item)
				{
					case TWSX_NATIVE:
						sprintf(str, "%s", "TWSX_NATIVE");break;
					case TWSX_FILE:
						sprintf(str, "%s", "TWSX_FILE");break;
					case TWSX_MEMORY:
						sprintf(str, "%s", "TWSX_MEMORY");break;
					case TWSX_FILE2:
						sprintf(str, "%s", "TWSX_FILE2");break;
				}
			}
				break;
			case ICAP_UNITS:
			{
				switch(item)
				{
					case TWUN_INCHES:
						sprintf(str, "%s", "TWUN_INCHES");break;
					case TWUN_CENTIMETERS:
						sprintf(str, "%s", "TWUN_CENTIMETERS");break;
					case TWUN_PICAS:
						sprintf(str, "%s", "TWUN_PICAS");break;
					case TWUN_POINTS:
						sprintf(str, "%s", "TWUN_POINTS");break;
					case TWUN_TWIPS:
						sprintf(str, "%s", "TWUN_TWIPS");break;
					case TWUN_PIXELS:
						sprintf(str, "%s", "TWUN_PIXELS");break;
				}
			}
				break;
			default:
			{
				string_or_constant_value = FALSE;
				JSONNODE *json_number = json_new(JSON_NUMBER);
				json_set_i(json_number, item);
				json_push_back(json_scanner_option_values, json_number);
			}
				break;
		}
		
		if(string_or_constant_value)
		{
			if (strlen(str))
			{
				json_push_back_s(json_scanner_option_values, str);
			}
			else
			{
				JSONNODE *json_number = json_new(JSON_NUMBER);
				json_set_i(json_number, item);
				json_push_back(json_scanner_option_values, json_number);
			}
		}
	}
}

void twain_get_capability_value(TW_CAPABILITY *tw_capability, void *p, JSONNODE *json_scanner_option)
{
	TW_UINT16 cap = tw_capability->Cap;
	TW_UINT16 conType = tw_capability->ConType;
	
	pTW_ENUMERATION pENUMERATION = (pTW_ENUMERATION)p;
	pTW_ONEVALUE pONEVALUE = (pTW_ONEVALUE)p;
	pTW_RANGE pRANGE = (pTW_RANGE)p;
	
	char str[CAP_VALUE_BUF_SIZE];
	memset(str, 0, sizeof(str));
	
	BOOL string_or_constant_value = TRUE;
	
	TW_UINT32 item = 0;
	
	switch(conType)
	{
		case TWON_ARRAY:
			
			break;
		case TWON_ENUMERATION:
			item = (pENUMERATION->ItemList[pENUMERATION->CurrentIndex]);
			break;
		case TWON_ONEVALUE:
			item = pONEVALUE->Item;
			break;
		case TWON_RANGE:
			item = pRANGE->CurrentValue;
			break;
	}
	
	switch(cap)
	{
			//convert to constant
#if USE_TWAIN_DSM
		case ICAP_AUTOSIZE:
		{
			switch(item)
			{
				case TWAS_NONE:
					sprintf(str, "%s", "TWAS_NONE");break;
				case TWAS_AUTO:
					sprintf(str, "%s", "TWAS_AUTO");break;
				case TWAS_CURRENT:
					sprintf(str, "%s", "TWAS_CURRENT");break;
			}
		}
			break;
		case ICAP_AUTODISCARDBLANKPAGES:
		{
			switch(item)
			{
				case TWBP_DISABLE:
					sprintf(str, "%s", "TWBP_DISABLE");break;
				case TWBP_AUTO:
					sprintf(str, "%s", "TWBP_AUTO");break;
			}
		}
			break;
		case CAP_CAMERASIDE:
		{
			switch(item)
			{
				case TWCS_BOTH:
					sprintf(str, "%s", "TWCS_BOTH");break;
				case TWCS_TOP:
					sprintf(str, "%s", "TWCS_TOP");break;
				case TWCS_BOTTOM:
					sprintf(str, "%s", "TWCS_BOTTOM");break;
			}
		}
			break;
		case ICAP_FEEDERTYPE:
		{
			switch(item)
			{
				case TWFE_GENERAL:
					sprintf(str, "%s", "TWFE_GENERAL");break;
				case TWFE_PHOTO:
					sprintf(str, "%s", "TWFE_PHOTO");break;
			}
		}
			break;
		case CAP_FEEDERPOCKET:
		{
			switch(item)
			{
				case TWFP_POCKETERROR:
					sprintf(str, "%s", "TWFP_POCKETERROR");break;
				case TWFP_POCKET1:
					sprintf(str, "%s", "TWFP_POCKET1");break;
				case TWFP_POCKET2:
					sprintf(str, "%s", "TWFP_POCKET2");break;
				case TWFP_POCKET3:
					sprintf(str, "%s", "TWFP_POCKET3");break;
				case TWFP_POCKET4:
					sprintf(str, "%s", "TWFP_POCKET4");break;
				case TWFP_POCKET5:
					sprintf(str, "%s", "TWFP_POCKET5");break;
				case TWFP_POCKET6:
					sprintf(str, "%s", "TWFP_POCKET6");break;
				case TWFP_POCKET7:
					sprintf(str, "%s", "TWFP_POCKET7");break;
				case TWFP_POCKET8:
					sprintf(str, "%s", "TWFP_POCKET8");break;
				case TWFP_POCKET9:
					sprintf(str, "%s", "TWFP_POCKET9");break;
				case TWFP_POCKET10:
					sprintf(str, "%s", "TWFP_POCKET10");break;
				case TWFP_POCKET11:
					sprintf(str, "%s", "TWFP_POCKET11");break;
				case TWFP_POCKET12:
					sprintf(str, "%s", "TWFP_POCKET12");break;
				case TWFP_POCKET13:
					sprintf(str, "%s", "TWFP_POCKET13");break;
				case TWFP_POCKET14:
					sprintf(str, "%s", "TWFP_POCKET14");break;
				case TWFP_POCKET15:
					sprintf(str, "%s", "TWFP_POCKET15");break;
				case TWFP_POCKET16:
					sprintf(str, "%s", "TWFP_POCKET16");break;
			}
		}
			break;
		case ICAP_ICCPROFILE:
		{
			switch(item)
			{
				case TWIC_NONE:
					sprintf(str, "%s", "TWIC_NONE");break;
				case TWIC_LINK:
					sprintf(str, "%s", "TWIC_LINK");break;
				case TWIC_EMBED:
					sprintf(str, "%s", "TWIC_EMBED");break;
			}
		}
			break;
		case ICAP_IMAGEMERGE:
		{
			switch(item)
			{
				case TWIM_NONE:
					sprintf(str, "%s", "TWIM_NONE");break;
				case TWIM_FRONTONTOP:
					sprintf(str, "%s", "TWIM_FRONTONTOP");break;
				case TWIM_FRONTONBOTTOM:
					sprintf(str, "%s", "TWIM_FRONTONBOTTOM");break;
				case TWIM_FRONTONLEFT:
					sprintf(str, "%s", "TWIM_FRONTONLEFT");break;
				case TWIM_FRONTONRIGHT:
					sprintf(str, "%s", "TWIM_FRONTONRIGHT");break;
			}
		}
			break;
		case CAP_SEGMENTED:
		{
			switch(item)
			{
				case TWSG_NONE:
					sprintf(str, "%s", "TWSG_NONE");break;
				case TWSG_AUTO:
					sprintf(str, "%s", "TWSG_AUTO");break;
				case TWSG_MANUAL:
					sprintf(str, "%s", "TWSG_MANUAL");break;
			}
		}
			break;
#endif
		case CAP_ALARMS:
		{
			switch(item)
			{
				case TWAL_ALARM:
					sprintf(str, "%s", "TWAL_ALARM");break;
				case TWAL_FEEDERERROR:
					sprintf(str, "%s", "TWAL_FEEDERERROR");break;
				case TWAL_FEEDERWARNING:
					sprintf(str, "%s", "TWAL_FEEDERWARNING");break;
				case TWAL_BARCODE:
					sprintf(str, "%s", "TWAL_BARCODE");break;
				case TWAL_DOUBLEFEED:
					sprintf(str, "%s", "TWAL_DOUBLEFEED");break;
				case TWAL_JAM:
					sprintf(str, "%s", "TWAL_JAM");break;
				case TWAL_PATCHCODE:
					sprintf(str, "%s", "TWAL_PATCHCODE");break;
				case TWAL_POWER:
					sprintf(str, "%s", "TWAL_POWER");break;
				case TWAL_SKEW:
					sprintf(str, "%s", "TWAL_SKEW");break;
			}
		}
			break;
		case ICAP_COMPRESSION:
		{
			switch(item)
			{
				case TWCP_NONE:
					sprintf(str, "%s", "TWCP_NONE");break;
				case TWCP_PACKBITS:
					sprintf(str, "%s", "TWCP_PACKBITS");break;
				case TWCP_GROUP31D:
					sprintf(str, "%s", "TWCP_GROUP31D");break;
				case TWCP_GROUP31DEOL:
					sprintf(str, "%s", "TWCP_GROUP31DEOL");break;
				case TWCP_GROUP32D:
					sprintf(str, "%s", "TWCP_GROUP32D");break;
				case TWCP_GROUP4:
					sprintf(str, "%s", "TWCP_GROUP4");break;
				case TWCP_JPEG:
					sprintf(str, "%s", "TWCP_JPEG");break;
				case TWCP_LZW:
					sprintf(str, "%s", "TWCP_LZW");break;
				case TWCP_JBIG:
					sprintf(str, "%s", "TWCP_JBIG");break;
				case TWCP_PNG:
					sprintf(str, "%s", "TWCP_PNG");break;
				case TWCP_RLE4:
					sprintf(str, "%s", "TWCP_RLE4");break;
				case TWCP_RLE8:
					sprintf(str, "%s", "TWCP_RLE8");break;
				case TWCP_BITFIELDS:
					sprintf(str, "%s", "TWCP_BITFIELDS");break;
			}
		}
			break;
		case ICAP_BARCODESEARCHMODE:
		{
			switch(item)
			{
				case TWBD_HORZ:
					sprintf(str, "%s", "TWBD_HORZ");break;
				case TWBD_VERT:
					sprintf(str, "%s", "TWBD_VERT");break;
				case TWBD_HORZVERT:
					sprintf(str, "%s", "TWBD_HORZVERT");break;
				case TWBD_VERTHORZ:
					sprintf(str, "%s", "TWBD_VERTHORZ");break;
			}
		}
			break;
		case ICAP_BITORDER:
		{
			switch(item)
			{
				case TWBO_LSBFIRST:
					sprintf(str, "%s", "TWBO_LSBFIRST");break;
				case TWBO_MSBFIRST:
					sprintf(str, "%s", "TWBO_MSBFIRST");break;
			}
		}
			break;
		case ICAP_BITDEPTHREDUCTION:
		{
			switch(item)
			{
				case TWBR_THRESHOLD:
					sprintf(str, "%s", "TWBR_THRESHOLD");break;
				case TWBR_HALFTONE:
					sprintf(str, "%s", "TWBR_HALFTONE");break;
				case TWBR_CUSTHALFTONE:
					sprintf(str, "%s", "TWBR_CUSTHALFTONE");break;
				case TWBR_DIFFUSION:
					sprintf(str, "%s", "TWBR_DIFFUSION");break;
			}
		}
			break;
		case ICAP_SUPPORTEDBARCODETYPES:
		case TWEI_BARCODETYPE:
		{
			switch(item)
			{
				case TWBT_3OF9:
					sprintf(str, "%s", "TWBT_3OF9");break;
				case TWBT_2OF5INTERLEAVED:
					sprintf(str, "%s", "TWBT_2OF5INTERLEAVED");break;
				case TWBT_2OF5NONINTERLEAVED:
					sprintf(str, "%s", "TWBT_2OF5NONINTERLEAVED");break;
				case TWBT_CODE93:
					sprintf(str, "%s", "TWBT_CODE93");break;
				case TWBT_CODE128:
					sprintf(str, "%s", "TWBT_CODE128");break;
				case TWBT_UCC128:
					sprintf(str, "%s", "TWBT_UCC128");break;
				case TWBT_CODABAR:
					sprintf(str, "%s", "TWBT_CODABAR");break;
				case TWBT_UPCA:
					sprintf(str, "%s", "TWBT_UPCA");break;
				case TWBT_UPCE:
					sprintf(str, "%s", "TWBT_UPCE");break;
				case TWBT_EAN8:
					sprintf(str, "%s", "TWBT_EAN8");break;
				case TWBT_EAN13:
					sprintf(str, "%s", "TWBT_EAN13");break;
				case TWBT_POSTNET:
					sprintf(str, "%s", "TWBT_POSTNET");break;
				case TWBT_PDF417:
					sprintf(str, "%s", "TWBT_PDF417");break;
				case TWBT_2OF5INDUSTRIAL:
					sprintf(str, "%s", "TWBT_2OF5INDUSTRIAL");break;
				case TWBT_2OF5MATRIX:
					sprintf(str, "%s", "TWBT_2OF5MATRIX");break;
				case TWBT_2OF5DATALOGIC:
					sprintf(str, "%s", "TWBT_2OF5DATALOGIC");break;
				case TWBT_2OF5IATA:
					sprintf(str, "%s", "TWBT_2OF5IATA");break;
				case TWBT_3OF9FULLASCII:
					sprintf(str, "%s", "TWBT_3OF9FULLASCII");break;
				case TWBT_CODABARWITHSTARTSTOP:
					sprintf(str, "%s", "TWBT_CODABARWITHSTARTSTOP");break;
				case TWBT_MAXICODE:
					sprintf(str, "%s", "TWBT_MAXICODE");break;
			}
		}
			break;
		case CAP_CLEARBUFFERS:
		{
			switch(item)
			{
				case TWCB_AUTO:
					sprintf(str, "%s", "TWCB_AUTO");break;
				case TWCB_CLEAR:
					sprintf(str, "%s", "TWCB_CLEAR");break;
				case TWCB_NOCLEAR:
					sprintf(str, "%s", "TWCB_NOCLEAR");break;
			}
		}
			break;
		case CAP_DEVICEEVENT:
		{
			switch(item)
			{
				case TWDE_CUSTOMEVENTS:
					sprintf(str, "%s", "TWDE_CUSTOMEVENTS");break;
				case TWDE_CHECKAUTOMATICCAPTURE:
					sprintf(str, "%s", "TWDE_CHECKAUTOMATICCAPTURE");break;
				case TWDE_CHECKBATTERY:
					sprintf(str, "%s", "TWDE_CHECKBATTERY");break;
				case TWDE_CHECKDEVICEONLINE:
					sprintf(str, "%s", "TWDE_CHECKDEVICEONLINE");break;
				case TWDE_CHECKFLASH:
					sprintf(str, "%s", "TWDE_CHECKFLASH");break;
				case TWDE_CHECKPOWERSUPPLY:
					sprintf(str, "%s", "TWDE_CHECKPOWERSUPPLY");break;
				case TWDE_CHECKRESOLUTION:
					sprintf(str, "%s", "TWDE_CHECKRESOLUTION");break;
				case TWDE_DEVICEADDED:
					sprintf(str, "%s", "TWDE_DEVICEADDED");break;
				case TWDE_DEVICEOFFLINE:
					sprintf(str, "%s", "TWDE_DEVICEOFFLINE");break;
				case TWDE_DEVICEREADY:
					sprintf(str, "%s", "TWDE_DEVICEREADY");break;
				case TWDE_DEVICEREMOVED:
					sprintf(str, "%s", "TWDE_DEVICEREMOVED");break;
				case TWDE_IMAGECAPTURED:
					sprintf(str, "%s", "TWDE_IMAGECAPTURED");break;
				case TWDE_IMAGEDELETED:
					sprintf(str, "%s", "TWDE_IMAGEDELETED");break;
				case TWDE_PAPERDOUBLEFEED:
					sprintf(str, "%s", "TWDE_PAPERDOUBLEFEED");break;
				case TWDE_PAPERJAM:
					sprintf(str, "%s", "TWDE_PAPERJAM");break;
				case TWDE_LAMPFAILURE:
					sprintf(str, "%s", "TWDE_LAMPFAILURE");break;
				case TWDE_POWERSAVE:
					sprintf(str, "%s", "TWDE_POWERSAVE");break;
				case TWDE_POWERSAVENOTIFY:
					sprintf(str, "%s", "TWDE_POWERSAVENOTIFY");break;
			}
		}
			break;
		case CAP_DUPLEX:
		{
			switch(item)
			{
				case TWDX_NONE:
					sprintf(str, "%s", "TWDX_NONE");break;
				case TWDX_1PASSDUPLEX:
					sprintf(str, "%s", "TWDX_1PASSDUPLEX");break;
				case TWDX_2PASSDUPLEX:
					sprintf(str, "%s", "TWDX_2PASSDUPLEX");break;
			}
		}
			break;
		case CAP_FEEDERALIGNMENT:
		{
			switch(item)
			{
				case TWFA_NONE:
					sprintf(str, "%s", "TWFA_NONE");break;
				case TWFA_LEFT:
					sprintf(str, "%s", "TWFA_LEFT");break;
				case TWFA_CENTER:
					sprintf(str, "%s", "TWFA_CENTER");break;
				case TWFA_RIGHT:
					sprintf(str, "%s", "TWFA_RIGHT");break;
			}
		}
			break;
		case ICAP_IMAGEFILEFORMAT:
		{
			switch(item)
			{
				case TWFF_TIFF:
					sprintf(str, "%s", "TWFF_TIFF");break;
				case TWFF_PICT:
					sprintf(str, "%s", "TWFF_PICT");break;
				case TWFF_BMP:
					sprintf(str, "%s", "TWFF_BMP");break;
				case TWFF_XBM:
					sprintf(str, "%s", "TWFF_XBM");break;
				case TWFF_JFIF:
					sprintf(str, "%s", "TWFF_JFIF");break;
				case TWFF_FPX:
					sprintf(str, "%s", "TWFF_FPX");break;
				case TWFF_TIFFMULTI:
					sprintf(str, "%s", "TWFF_TIFFMULTI");break;
				case TWFF_PNG:
					sprintf(str, "%s", "TWFF_PNG");break;
				case TWFF_SPIFF:
					sprintf(str, "%s", "TWFF_SPIFF");break;
				case TWFF_EXIF:
					sprintf(str, "%s", "TWFF_EXIF");break;
			}
		}
			break;
		case ICAP_FLASHUSED2:
		{
			switch(item)
			{
				case TWFL_NONE:
					sprintf(str, "%s", "TWFL_NONE");break;
				case TWFL_OFF:
					sprintf(str, "%s", "TWFL_OFF");break;
				case TWFL_ON:
					sprintf(str, "%s", "TWFL_ON");break;
				case TWFL_AUTO:
					sprintf(str, "%s", "TWFL_AUTO");break;
				case TWFL_REDEYE:
					sprintf(str, "%s", "TWFL_REDEYE");break;
			}
		}
			break;
		case CAP_FEEDERORDER:
		{
			switch(item)
			{
				case TWFO_FIRSTPAGEFIRST:
					sprintf(str, "%s", "TWFO_FIRSTPAGEFIRST");break;
				case TWFO_LASTPAGEFIRST:
					sprintf(str, "%s", "TWFO_LASTPAGEFIRST");break;
			}
		}
			break;
		case ICAP_FLIPROTATION:
		{
			switch(item)
			{
				case TWFR_BOOK:
					sprintf(str, "%s", "TWFR_BOOK");break;
				case TWFR_FANFOLD:
					sprintf(str, "%s", "TWFR_FANFOLD");break;
			}
		}
			break;
		case ICAP_FILTER:
		{
			switch(item)
			{
				case TWFT_RED:
					sprintf(str, "%s", "TWFT_RED");break;
				case TWFT_GREEN:
					sprintf(str, "%s", "TWFT_GREEN");break;
				case TWFT_BLUE:
					sprintf(str, "%s", "TWFT_BLUE");break;
				case TWFT_NONE:
					sprintf(str, "%s", "TWFT_NONE");break;
				case TWFT_WHITE:
					sprintf(str, "%s", "TWFT_WHITE");break;
				case TWFT_CYAN:
					sprintf(str, "%s", "TWFT_CYAN");break;
				case TWFT_MAGENTA:
					sprintf(str, "%s", "TWFT_MAGENTA");break;
				case TWFT_YELLOW:
					sprintf(str, "%s", "TWFT_YELLOW");break;
				case TWFT_BLACK:
					sprintf(str, "%s", "TWFT_BLACK");break;
			}
		}
			break;
		case ICAP_IMAGEFILTER:
		{
			switch(item)
			{
				case TWIF_NONE:
					sprintf(str, "%s", "TWIF_NONE");break;
				case TWIF_AUTO:
					sprintf(str, "%s", "TWIF_AUTO");break;
				case TWIF_LOWPASS:
					sprintf(str, "%s", "TWIF_LOWPASS");break;
				case TWIF_BANDPASS:
					sprintf(str, "%s", "TWIF_BANDPASS");break;
				case TWIF_HIGHPASS:
					sprintf(str, "%s", "TWIF_HIGHPASS");break;
					//				case TWIF_TEXT:
					//					sprintf(str, "%s", "TWIF_TEXT");break;
					//				case TWIF_FINELINE:
					//					sprintf(str, "%s", "TWIF_FINELINE");break;
			}
		}
			break;
		case CAP_JOBCONTROL:
		{
			switch(item)
			{
				case TWJC_NONE:
					sprintf(str, "%s", "TWJC_NONE");break;
				case TWJC_JSIC:
					sprintf(str, "%s", "TWJC_JSIC");break;
				case TWJC_JSIS:
					sprintf(str, "%s", "TWJC_JSIS");break;
				case TWJC_JSXC:
					sprintf(str, "%s", "TWJC_JSXC");break;
				case TWJC_JSXS:
					sprintf(str, "%s", "TWJC_JSXS");break;
			}
		}
			break;
		case ICAP_JPEGQUALITY:
		{
			switch(item)
			{
				case TWJQ_UNKNOWN:
					sprintf(str, "%s", "TWJQ_UNKNOWN");break;
				case TWJQ_LOW:
					sprintf(str, "%s", "TWJQ_LOW");break;
				case TWJQ_MEDIUM:
					sprintf(str, "%s", "TWJQ_MEDIUM");break;
				case TWJQ_HIGH:
					sprintf(str, "%s", "TWJQ_HIGH");break;
			}
		}
			break;
		case ICAP_LIGHTPATH:
		{
			switch(item)
			{
				case TWLP_REFLECTIVE:
					sprintf(str, "%s", "TWLP_REFLECTIVE");break;
				case TWLP_TRANSMISSIVE:
					sprintf(str, "%s", "TWLP_TRANSMISSIVE");break;
			}
		}
			break;
		case ICAP_LIGHTSOURCE:
		{
			switch(item)
			{
				case TWLS_RED:
					sprintf(str, "%s", "TWLS_RED");break;
				case TWLS_GREEN:
					sprintf(str, "%s", "TWLS_GREEN");break;
				case TWLS_BLUE:
					sprintf(str, "%s", "TWLS_BLUE");break;
				case TWLS_NONE:
					sprintf(str, "%s", "TWLS_NONE");break;
				case TWLS_WHITE:
					sprintf(str, "%s", "TWLS_WHITE");break;
				case TWLS_UV:
					sprintf(str, "%s", "TWLS_UV");break;
				case TWLS_IR:
					sprintf(str, "%s", "TWLS_IR");break;
			}
		}
			break;
		case ICAP_NOISEFILTER:
		{
			switch(item)
			{
				case TWNF_NONE:
					sprintf(str, "%s", "TWNF_NONE");break;
				case TWNF_AUTO:
					sprintf(str, "%s", "TWNF_AUTO");break;
				case TWNF_LONEPIXEL:
					sprintf(str, "%s", "TWNF_LONEPIXEL");break;
				case TWNF_MAJORITYRULE:
					sprintf(str, "%s", "TWNF_MAJORITYRULE");break;
			}
		}
			break;
		case ICAP_ORIENTATION:
		{
			switch(item)
			{
				case TWOR_ROT0:
					sprintf(str, "%s", "TWOR_ROT0");break;
				case TWOR_ROT90:
					sprintf(str, "%s", "TWOR_ROT90");break;
				case TWOR_ROT180:
					sprintf(str, "%s", "TWOR_ROT180");break;
				case TWOR_ROT270:
					sprintf(str, "%s", "TWOR_ROT270");break;
					//				case TWOR_PORTRAIT:
					//					sprintf(str, "%s", "TWOR_PORTRAIT");break;
					//				case TWOR_LANDSCAPE:
					//					sprintf(str, "%s", "TWOR_LANDSCAPE");break;
			}
		}
			break;
		case ICAP_OVERSCAN:
		{
			switch(item)
			{
				case TWOV_NONE:
					sprintf(str, "%s", "TWOV_NONE");break;
				case TWOV_AUTO:
					sprintf(str, "%s", "TWOV_AUTO");break;
				case TWOV_TOPBOTTOM:
					sprintf(str, "%s", "TWOV_TOPBOTTOM");break;
				case TWOV_LEFTRIGHT:
					sprintf(str, "%s", "TWOV_LEFTRIGHT");break;
				case TWOV_ALL:
					sprintf(str, "%s", "TWOV_ALL");break;
			}
		}
			break;
		case ICAP_PLANARCHUNKY:
		{
			switch(item)
			{
				case TWPC_CHUNKY:
					sprintf(str, "%s", "TWPC_CHUNKY");break;
				case TWPC_PLANAR:
					sprintf(str, "%s", "TWPC_PLANAR");break;
			}
		}
			break;
		case ICAP_PIXELFLAVOR:
		{
			switch(item)
			{
				case TWPF_CHOCOLATE:
					sprintf(str, "%s", "TWPF_CHOCOLATE");break;
				case TWPF_VANILLA:
					sprintf(str, "%s", "TWPF_VANILLA");break;
			}
		}
			break;
		case CAP_PRINTERMODE:
		{
			switch(item)
			{
				case TWPM_SINGLESTRING:
					sprintf(str, "%s", "TWPM_SINGLESTRING");break;
				case TWPM_MULTISTRING:
					sprintf(str, "%s", "TWPM_MULTISTRING");break;
				case TWPM_COMPOUNDSTRING:
					sprintf(str, "%s", "TWPM_COMPOUNDSTRING");break;
			}
		}
			break;
		case CAP_PRINTER:
		{
			switch(item)
			{
				case TWPR_IMPRINTERTOPBEFORE:
					sprintf(str, "%s", "TWPR_IMPRINTERTOPBEFORE");break;
				case TWPR_IMPRINTERTOPAFTER:
					sprintf(str, "%s", "TWPR_IMPRINTERTOPAFTER");break;
				case TWPR_IMPRINTERBOTTOMBEFORE:
					sprintf(str, "%s", "TWPR_IMPRINTERBOTTOMBEFORE");break;
				case TWPR_IMPRINTERBOTTOMAFTER:
					sprintf(str, "%s", "TWPR_IMPRINTERBOTTOMAFTER");break;
				case TWPR_ENDORSERTOPBEFORE:
					sprintf(str, "%s", "TWPR_ENDORSERTOPBEFORE");break;
				case TWPR_ENDORSERTOPAFTER:
					sprintf(str, "%s", "TWPR_ENDORSERTOPAFTER");break;
				case TWPR_ENDORSERBOTTOMBEFORE:
					sprintf(str, "%s", "TWPR_ENDORSERBOTTOMBEFORE");break;
				case TWPR_ENDORSERBOTTOMAFTER:
					sprintf(str, "%s", "TWPR_ENDORSERBOTTOMAFTER");break;
			}
		}
			break;
		case CAP_POWERSUPPLY:
		{
			switch(item)
			{
				case TWPS_EXTERNAL:
					sprintf(str, "%s", "TWPS_EXTERNAL");break;
				case TWPS_BATTERY:
					sprintf(str, "%s", "TWPS_BATTERY");break;
			}
		}
			break;
		case ICAP_PIXELTYPE:
		{
			switch(item)
			{
				case TWPT_BW:
					sprintf(str, "%s", "TWPT_BW");break;
				case TWPT_GRAY:
					sprintf(str, "%s", "TWPT_GRAY");break;
				case TWPT_RGB:
					sprintf(str, "%s", "TWPT_RGB");break;
				case TWPT_PALETTE:
					sprintf(str, "%s", "TWPT_PALETTE");break;
				case TWPT_CMY:
					sprintf(str, "%s", "TWPT_CMY");break;
				case TWPT_CMYK:
					sprintf(str, "%s", "TWPT_CMYK");break;
				case TWPT_YUV:
					sprintf(str, "%s", "TWPT_YUV");break;
				case TWPT_YUVK:
					sprintf(str, "%s", "TWPT_YUVK");break;
				case TWPT_CIEXYZ:
					sprintf(str, "%s", "TWPT_CIEXYZ");break;
			}
		}
			break;
		case ICAP_SUPPORTEDSIZES:
		{
			switch(item)
			{
				case TWSS_NONE:
					sprintf(str, "%s", "TWSS_NONE");break;
				case TWSS_A4LETTER:
					sprintf(str, "%s", "TWSS_A4LETTER");break;
				case TWSS_B5LETTER:
					sprintf(str, "%s", "TWSS_B5LETTER");break;
				case TWSS_USLETTER:
					sprintf(str, "%s", "TWSS_USLETTER");break;
				case TWSS_USLEGAL:
					sprintf(str, "%s", "TWSS_USLEGAL");break;
				case TWSS_A5:
					sprintf(str, "%s", "TWSS_A5");break;
				case TWSS_B4:
					sprintf(str, "%s", "TWSS_B4");break;
				case TWSS_B6:
					sprintf(str, "%s", "TWSS_B6");break;
					//				case TWSS_B:
					//					sprintf(str, "%s", "TWSS_B");break;
				case TWSS_USLEDGER:
					sprintf(str, "%s", "TWSS_USLEDGER");break;
				case TWSS_USEXECUTIVE:
					sprintf(str, "%s", "TWSS_USEXECUTIVE");break;
				case TWSS_A3:
					sprintf(str, "%s", "TWSS_A3");break;
				case TWSS_B3:
					sprintf(str, "%s", "TWSS_B3");break;
				case TWSS_A6:
					sprintf(str, "%s", "TWSS_A6");break;
				case TWSS_C4:
					sprintf(str, "%s", "TWSS_C4");break;
				case TWSS_C5:
					sprintf(str, "%s", "TWSS_C5");break;
				case TWSS_C6:
					sprintf(str, "%s", "TWSS_C6");break;
				case TWSS_4A0:
					sprintf(str, "%s", "TWSS_4A0");break;
				case TWSS_2A0:
					sprintf(str, "%s", "TWSS_2A0");break;
				case TWSS_A0:
					sprintf(str, "%s", "TWSS_A0");break;
				case TWSS_A1:
					sprintf(str, "%s", "TWSS_A1");break;
				case TWSS_A2:
					sprintf(str, "%s", "TWSS_A2");break;
					//				case TWSS_A4:
					//					sprintf(str, "%s", "TWSS_A4");break;
				case TWSS_A7:
					sprintf(str, "%s", "TWSS_A7");break;
				case TWSS_A8:
					sprintf(str, "%s", "TWSS_A8");break;
				case TWSS_A9:
					sprintf(str, "%s", "TWSS_A9");break;
				case TWSS_A10:
					sprintf(str, "%s", "TWSS_A10");break;
				case TWSS_ISOB0:
					sprintf(str, "%s", "TWSS_ISOB0");break;
				case TWSS_ISOB1:
					sprintf(str, "%s", "TWSS_ISOB1");break;
				case TWSS_ISOB2:
					sprintf(str, "%s", "TWSS_ISOB2");break;
					//				case TWSS_ISOB3:
					//					sprintf(str, "%s", "TWSS_ISOB3");break;
					//				case TWSS_ISOB4:
					//					sprintf(str, "%s", "TWSS_ISOB4");break;
				case TWSS_ISOB5:
					sprintf(str, "%s", "TWSS_ISOB5");break;
					//				case TWSS_ISOB6:
					//					sprintf(str, "%s", "TWSS_ISOB6");break;
				case TWSS_ISOB7:
					sprintf(str, "%s", "TWSS_ISOB7");break;
				case TWSS_ISOB8:
					sprintf(str, "%s", "TWSS_ISOB8");break;
				case TWSS_ISOB9:
					sprintf(str, "%s", "TWSS_ISOB9");break;
				case TWSS_ISOB10:
					sprintf(str, "%s", "TWSS_ISOB10");break;
				case TWSS_JISB0:
					sprintf(str, "%s", "TWSS_JISB0");break;
				case TWSS_JISB1:
					sprintf(str, "%s", "TWSS_JISB1");break;
				case TWSS_JISB2:
					sprintf(str, "%s", "TWSS_JISB2");break;
				case TWSS_JISB3:
					sprintf(str, "%s", "TWSS_JISB3");break;
				case TWSS_JISB4:
					sprintf(str, "%s", "TWSS_JISB4");break;
					//				case TWSS_JISB5:
					//					sprintf(str, "%s", "TWSS_JISB5");break;
				case TWSS_JISB6:
					sprintf(str, "%s", "TWSS_JISB6");break;
				case TWSS_JISB7:
					sprintf(str, "%s", "TWSS_JISB7");break;
				case TWSS_JISB8:
					sprintf(str, "%s", "TWSS_JISB8");break;
				case TWSS_JISB9:
					sprintf(str, "%s", "TWSS_JISB9");break;
				case TWSS_JISB10:
					sprintf(str, "%s", "TWSS_JISB10");break;
				case TWSS_C0:
					sprintf(str, "%s", "TWSS_C0");break;
				case TWSS_C1:
					sprintf(str, "%s", "TWSS_C1");break;
				case TWSS_C2:
					sprintf(str, "%s", "TWSS_C2");break;
				case TWSS_C3:
					sprintf(str, "%s", "TWSS_C3");break;
				case TWSS_C7:
					sprintf(str, "%s", "TWSS_C7");break;
				case TWSS_C8:
					sprintf(str, "%s", "TWSS_C8");break;
				case TWSS_C9:
					sprintf(str, "%s", "TWSS_C9");break;
				case TWSS_C10:
					sprintf(str, "%s", "TWSS_C10");break;
				case TWSS_USSTATEMENT:
					sprintf(str, "%s", "TWSS_USSTATEMENT");break;
				case TWSS_BUSINESSCARD:
					sprintf(str, "%s", "TWSS_BUSINESSCARD");break;
			}
		}
			break;
		case ICAP_XFERMECH:
		{
			switch(item)
			{
				case TWSX_NATIVE:
					sprintf(str, "%s", "TWSX_NATIVE");break;
				case TWSX_FILE:
					sprintf(str, "%s", "TWSX_FILE");break;
				case TWSX_MEMORY:
					sprintf(str, "%s", "TWSX_MEMORY");break;
				case TWSX_FILE2:
					sprintf(str, "%s", "TWSX_FILE2");break;
			}
		}
			break;
		case ICAP_UNITS:
		{
			switch(item)
			{
				case TWUN_INCHES:
					sprintf(str, "%s", "TWUN_INCHES");break;
				case TWUN_CENTIMETERS:
					sprintf(str, "%s", "TWUN_CENTIMETERS");break;
				case TWUN_PICAS:
					sprintf(str, "%s", "TWUN_PICAS");break;
				case TWUN_POINTS:
					sprintf(str, "%s", "TWUN_POINTS");break;
				case TWUN_TWIPS:
					sprintf(str, "%s", "TWUN_TWIPS");break;
				case TWUN_PIXELS:
					sprintf(str, "%s", "TWUN_PIXELS");break;
			}
		}
			break;
		default:
			string_or_constant_value = FALSE;
			break;
	}
	
	if(string_or_constant_value)
	{
		json_set_s(json_scanner_option, str);
	}
	else
	{
		//generic
		switch (conType)
		{
		case TWON_ARRAY:
			string_or_constant_value = FALSE;
			break;
		case TWON_ENUMERATION:
			switch (pENUMERATION->ItemType)
			{
			case TWTY_FIX32:
			{
				string_or_constant_value = FALSE;
				pTW_FIX32 pFix32 = &((pTW_FIX32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				json_set_f(json_scanner_option, float(pFix32->Whole) + float(pFix32->Frac / 65536.0));
			}
			break;
			case TWTY_FRAME:
			{
				pTW_FRAME pframe = &((pTW_FRAME)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				sprintf(str, "%d.%u,%d.%u,%d.%u,%d.%u",
					pframe->Top.Whole, pframe->Top.Frac,
					pframe->Left.Whole, pframe->Left.Frac,
					pframe->Right.Whole, pframe->Right.Frac,
					pframe->Bottom.Whole, pframe->Bottom.Frac);
			}
			break;
			case TWTY_INT8:
			case TWTY_INT16:
			case TWTY_INT32:
			{
				string_or_constant_value = FALSE;
				TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				json_set_i(json_scanner_option, currentValue);
			}
			break;
			case TWTY_UINT8:
			case TWTY_UINT16:
			case TWTY_UINT32:
			{
				string_or_constant_value = FALSE;
				TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				json_set_i(json_scanner_option, currentValue);
			}
			break;
			case TWTY_BOOL:
			{
				string_or_constant_value = FALSE;
				TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				json_set_b(json_scanner_option, currentValue);
			}
			break;
			case TWTY_STR32:
			{
				pTW_STR32 pStr32 = &((pTW_STR32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				sprintf(str, "%s", pStr32);
			}
			break;
			case TWTY_STR64:
			{
				pTW_STR64 pStr64 = &((pTW_STR64)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				sprintf(str, "%s", pStr64);
			}
			break;
			case TWTY_STR128:
			{
				pTW_STR128 pStr128 = &((pTW_STR128)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				sprintf(str, "%s", pStr128);
			}
			break;
			case TWTY_STR255:
			{
				pTW_STR255 pStr255 = &((pTW_STR255)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
				sprintf(str, "%s", pStr255);
			}
			break;
			//					case TWTY_STR1024:
			//					case TWTY_UNI512:
			//						break;
			default:
				break;
			}
			break;
		case TWON_ONEVALUE:
			switch (pONEVALUE->ItemType)
			{
			case TWTY_FIX32:
			{
				string_or_constant_value = FALSE;
				pTW_FIX32 pFix32 = (pTW_FIX32)&pONEVALUE->Item;
				json_set_f(json_scanner_option, float(pFix32->Whole) + float(pFix32->Frac / 65536.0));
			}
			break;
			case TWTY_FRAME:
			{
				pTW_FRAME pframe = (pTW_FRAME)&pONEVALUE->Item;
				sprintf(str, "%d.%u,%d.%u,%d.%u,%d.%u",
					pframe->Top.Whole, pframe->Top.Frac,
					pframe->Left.Whole, pframe->Left.Frac,
					pframe->Right.Whole, pframe->Right.Frac,
					pframe->Bottom.Whole, pframe->Bottom.Frac);
			}
			break;
			case TWTY_INT8:
			case TWTY_INT16:
			case TWTY_INT32:
			{
				string_or_constant_value = FALSE;
				TW_UINT32 currentValue = pONEVALUE->Item;
				json_set_i(json_scanner_option, currentValue);
			}
			break;
			case TWTY_UINT8:
			case TWTY_UINT16:
			case TWTY_UINT32:
			{
				string_or_constant_value = FALSE;
				TW_UINT32 currentValue = pONEVALUE->Item;
				json_set_i(json_scanner_option, currentValue);
			}
			break;
			case TWTY_BOOL:
			{
				string_or_constant_value = FALSE;
				TW_UINT32 currentValue = pONEVALUE->Item;
				json_set_b(json_scanner_option, currentValue);
			}
			break;
			case TWTY_STR32:
			{
				pTW_STR32 pStr32 = (pTW_STR32)&pONEVALUE->Item;
				sprintf(str, "%s", pStr32);
			}
			break;
			case TWTY_STR64:
			{
				pTW_STR64 pStr64 = (pTW_STR64)&pONEVALUE->Item;
				sprintf(str, "%s", pStr64);
			}
			break;
			case TWTY_STR128:
			{
				pTW_STR128 pStr128 = (pTW_STR128)&pONEVALUE->Item;
				sprintf(str, "%s", pStr128);
			}
			break;
			case TWTY_STR255:
			{
				pTW_STR255 pStr255 = (pTW_STR255)&pONEVALUE->Item;
				sprintf(str, "%s", pStr255);
			}
			break;
			//					case TWTY_STR1024:
			//					case TWTY_UNI512:
			//						break;
			default:
				break;
			}
			break;
		case TWON_RANGE:
			string_or_constant_value = FALSE;
			TW_UINT32 currentValue = pRANGE->CurrentValue;
			json_set_i(json_scanner_option, currentValue);
			break;
		}
	}
	
}

void twain_get_capability_param(TW_CAPABILITY *tw_capability, void *p, JSONNODE *json_scanner_option)
{
	TW_UINT16 cap = tw_capability->Cap;
	TW_UINT16 conType = tw_capability->ConType;
	
	pTW_ENUMERATION pENUMERATION = (pTW_ENUMERATION)p;
	pTW_ONEVALUE pONEVALUE = (pTW_ONEVALUE)p;
	pTW_RANGE pRANGE = (pTW_RANGE)p;
	pTW_ARRAY pARRAY = (pTW_ARRAY)p;
	
	char str[CAP_VALUE_BUF_SIZE];
	memset(str, 0, sizeof(str));
	
	switch(conType)
	{
		case TWON_ARRAY:
		{
			JSONNODE *json_scanner_option_values = json_new(JSON_ARRAY);
			json_set_name(json_scanner_option_values, L"values");
			for (int i = 0; i < pARRAY->NumItems;++i)
			{
				switch(pARRAY->ItemType)
				{
					case TWTY_FIX32:
					{
						pTW_FIX32 pFix32 = &((pTW_FIX32)(&pARRAY->ItemList))[i];
						JSONNODE *json_number = json_new(JSON_NUMBER);
						json_set_f(json_number, float(pFix32->Whole) + float(pFix32->Frac / 65536.0));
						json_push_back(json_scanner_option_values, json_number);
					}
						break;
					case TWTY_FRAME:
					{
						pTW_FRAME pframe = &((pTW_FRAME)(&pARRAY->ItemList))[i];
						sprintf(str, "%d.%u,%d.%u,%d.%u,%d.%u",
										pframe->Top.Whole, pframe->Top.Frac,
										pframe->Left.Whole, pframe->Left.Frac,
										pframe->Right.Whole, pframe->Right.Frac,
										pframe->Bottom.Whole, pframe->Bottom.Frac);
					}
						break;
					case TWTY_INT8:
					{
						TW_INT8 currentValue = ((pTW_INT8)(&pARRAY->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_INT16:
					{
						TW_INT16 currentValue = ((pTW_INT16)(&pARRAY->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_INT32:
					{
						TW_INT32 currentValue = ((pTW_INT32)(&pARRAY->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_UINT8:
					{
						TW_UINT8 currentValue = ((pTW_UINT8)(&pARRAY->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_UINT16:
					{
						TW_UINT16 currentValue = ((pTW_UINT16)(&pARRAY->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_UINT32:
					{
						TW_UINT32 currentValue = ((pTW_UINT32)(&pARRAY->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_BOOL:
					{
						TW_UINT32 currentValue = ((pTW_UINT32)(&pARRAY->ItemList))[i];
						JSONNODE *json_bool = json_new(JSON_BOOL);
						json_set_b(json_bool, currentValue);
						json_push_back(json_scanner_option_values, json_bool);
					}
						break;
					case TWTY_STR32:
					{
						pTW_STR32 pStr32 = &((pTW_STR32)(&pARRAY->ItemList))[i];
						sprintf(str, "%s", pStr32);
						JSONNODE *json_text = json_new(JSON_STRING);
						json_set_s(json_text, str);
						json_push_back(json_scanner_option_values, json_text);
					}
						break;
					case TWTY_STR64:
					{
						pTW_STR64 pStr64 = &((pTW_STR64)(&pARRAY->ItemList))[i];
						sprintf(str, "%s", pStr64);
						JSONNODE *json_text = json_new(JSON_STRING);
						json_set_s(json_text, str);
						json_push_back(json_scanner_option_values, json_text);
					}
						break;
					case TWTY_STR128:
					{
						pTW_STR128 pStr128 = &((pTW_STR128)(&pARRAY->ItemList))[i];
						sprintf(str, "%s", pStr128);
						JSONNODE *json_text = json_new(JSON_STRING);
						json_set_s(json_text, str);
						json_push_back(json_scanner_option_values, json_text);
					}
						break;
					case TWTY_STR255:
					{
						pTW_STR255 pStr255 = &((pTW_STR255)(&pARRAY->ItemList))[i];
						sprintf(str, "%s", pStr255);
						JSONNODE *json_text = json_new(JSON_STRING);
						json_set_s(json_text, str);
						json_push_back(json_scanner_option_values, json_text);
					}
						break;
						//					case TWTY_STR1024:
						//					case TWTY_UNI512:
						//						break;
					default:
						break;
				}
			}
			json_push_back(json_scanner_option, json_scanner_option_values);
		}
			json_set_s_for_key(json_scanner_option, L"itemType", "TWON_ARRAY");
			break;
		case TWON_ENUMERATION:
		{
			JSONNODE *json_scanner_option_values = json_new(JSON_ARRAY);
			json_set_name(json_scanner_option_values, L"values");
			for (int i = 0; i < pENUMERATION->NumItems;++i)
			{
				switch(pENUMERATION->ItemType)
				{
					case TWTY_FIX32:
					{
						pTW_FIX32 pFix32 = &((pTW_FIX32)(&pENUMERATION->ItemList))[i];
						JSONNODE *json_number = json_new(JSON_NUMBER);
						json_set_f(json_number, float(pFix32->Whole) + float(pFix32->Frac / 65536.0));
						json_push_back(json_scanner_option_values, json_number);
					}
						break;
					case TWTY_FRAME:
					{
						pTW_FRAME pframe = &((pTW_FRAME)(&pENUMERATION->ItemList))[i];
						sprintf(str, "%d.%u,%d.%u,%d.%u,%d.%u",
										pframe->Top.Whole, pframe->Top.Frac,
										pframe->Left.Whole, pframe->Left.Frac,
										pframe->Right.Whole, pframe->Right.Frac,
										pframe->Bottom.Whole, pframe->Bottom.Frac);
					}
						break;
					case TWTY_INT8:
					{
						TW_INT8 currentValue = ((pTW_INT8)(&pENUMERATION->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_INT16:
					{
						TW_INT16 currentValue = ((pTW_INT16)(&pENUMERATION->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_INT32:
					{
						TW_INT32 currentValue = ((pTW_INT32)(&pENUMERATION->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_UINT8:
					{
						TW_UINT8 currentValue = ((pTW_UINT8)(&pENUMERATION->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_UINT16:
					{
						TW_UINT16 currentValue = ((pTW_UINT16)(&pENUMERATION->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_UINT32:
					{
						TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[i];
						json_push_back_i(json_scanner_option_values, cap, currentValue);
					}
						break;
					case TWTY_BOOL:
					{
						TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[i];
						JSONNODE *json_bool = json_new(JSON_BOOL);
						json_set_b(json_bool, currentValue);
						json_push_back(json_scanner_option_values, json_bool);
					}
						break;
						/* important to count the null byte */
					case TWTY_STR32:
					{
						pTW_STR32 pStr32 = &((pTW_STR32)(&pENUMERATION->ItemList))[i];
						pStr32 += (i * 33);
						sprintf(str, "%s", pStr32);
						JSONNODE *json_text = json_new(JSON_STRING);
						json_set_s(json_text, str);
						json_push_back(json_scanner_option_values, json_text);
					}
						break;
					case TWTY_STR64:
					{
						pTW_STR64 pStr64 = &((pTW_STR64)(&pENUMERATION->ItemList))[i];
						pStr64 += (i * 65);
						sprintf(str, "%s", pStr64);
						JSONNODE *json_text = json_new(JSON_STRING);
						json_set_s(json_text, str);
						json_push_back(json_scanner_option_values, json_text);
					}
						break;
					case TWTY_STR128:
					{
						pTW_STR128 pStr128 = &((pTW_STR128)(&pENUMERATION->ItemList))[i];
						pStr128 += (i * 129);
						sprintf(str, "%s", pStr128);
						JSONNODE *json_text = json_new(JSON_STRING);
						json_set_s(json_text, str);
						json_push_back(json_scanner_option_values, json_text);
					}
						break;
					case TWTY_STR255:
					{
						pTW_STR255 pStr255 = &((pTW_STR255)(&pENUMERATION->ItemList))[i];
						pStr255 += (i * 256);
						sprintf(str, "%s", pStr255);
						JSONNODE *json_text = json_new(JSON_STRING);
						json_set_s(json_text, str);
						json_push_back(json_scanner_option_values, json_text);
					}
						break;
						//					case TWTY_STR1024:
						//					case TWTY_UNI512:
						//						break;
					default:
						break;
				}
			}
			json_push_back(json_scanner_option, json_scanner_option_values);
		}
			json_set_s_for_key(json_scanner_option, L"itemType", "TWON_ENUMERATION");
			break;
		case TWON_ONEVALUE:
			json_set_s_for_key(json_scanner_option, L"itemType", "TWON_ONEVALUE");
			break;
		case TWON_RANGE:
			json_set_s_for_key(json_scanner_option, L"itemType", "TWON_RANGE");
			json_set_i_for_key(json_scanner_option, L"minValue", pRANGE->MinValue);
			json_set_i_for_key(json_scanner_option, L"maxValue", pRANGE->MaxValue);
			json_set_i_for_key(json_scanner_option, L"stepSize", pRANGE->StepSize);
			json_set_i_for_key(json_scanner_option, L"defaultValue", pRANGE->DefaultValue);
			break;
	}
	
}

void twain_get_capability_option_name(TW_UINT16 cap, std::wstring &stringValue)
{
	switch(cap)
	{
		case CAP_XFERCOUNT:
			stringValue = L"CAP_XFERCOUNT";
			break;
		case ICAP_COMPRESSION:
			stringValue = L"ICAP_COMPRESSION";
			break;
		case ICAP_PIXELTYPE:
			stringValue = L"ICAP_PIXELTYPE";
			break;
		case ICAP_UNITS:
			stringValue = L"ICAP_UNITS";
			break;
		case ICAP_XFERMECH:
			stringValue = L"ICAP_XFERMECH";
			break;
		case CAP_AUTHOR:
			stringValue = L"CAP_AUTHOR";
			break;
		case CAP_CAPTION:
			stringValue = L"CAP_CAPTION";
			break;
		case CAP_FEEDERENABLED:
			stringValue = L"CAP_FEEDERENABLED";
			break;
		case CAP_FEEDERLOADED:
			stringValue = L"CAP_FEEDERLOADED";
			break;
		case CAP_TIMEDATE:
			stringValue = L"CAP_TIMEDATE";
			break;
		case CAP_SUPPORTEDCAPS:
			stringValue = L"CAP_SUPPORTEDCAPS";
			break;
		case CAP_EXTENDEDCAPS:
			stringValue = L"CAP_EXTENDEDCAPS";
			break;
		case CAP_AUTOFEED:
			stringValue = L"CAP_AUTOFEED";
			break;
		case CAP_CLEARPAGE:
			stringValue = L"CAP_CLEARPAGE";
			break;
		case CAP_FEEDPAGE:
			stringValue = L"CAP_FEEDPAGE";
			break;
		case CAP_REWINDPAGE:
			stringValue = L"CAP_REWINDPAGE";
			break;
		case CAP_INDICATORS:
			stringValue = L"CAP_INDICATORS";
			break;
		case CAP_SUPPORTEDCAPSEXT:
			stringValue = L"CAP_SUPPORTEDCAPSEXT";
			break;
		case CAP_PAPERDETECTABLE:
			stringValue = L"CAP_PAPERDETECTABLE";
			break;
		case CAP_UICONTROLLABLE:
			stringValue = L"CAP_UICONTROLLABLE";
			break;
		case CAP_DEVICEONLINE:
			stringValue = L"CAP_DEVICEONLINE";
			break;
		case CAP_AUTOSCAN:
			stringValue = L"CAP_AUTOSCAN";
			break;
		case CAP_THUMBNAILSENABLED:
			stringValue = L"CAP_THUMBNAILSENABLED";
			break;
		case CAP_DUPLEX:
			stringValue = L"CAP_DUPLEX";
			break;
		case CAP_DUPLEXENABLED:
			stringValue = L"CAP_DUPLEXENABLED";
			break;
		case CAP_ENABLEDSUIONLY:
			stringValue = L"CAP_ENABLEDSUIONLY";
			break;
		case CAP_CUSTOMDSDATA:
			stringValue = L"CAP_CUSTOMDSDATA";
			break;
		case CAP_ENDORSER:
			stringValue = L"CAP_ENDORSER";
			break;
		case CAP_JOBCONTROL:
			stringValue = L"CAP_JOBCONTROL";
			break;
		case CAP_ALARMS:
			stringValue = L"CAP_ALARMS";
			break;
		case CAP_ALARMVOLUME:
			stringValue = L"CAP_ALARMVOLUME";
			break;
		case CAP_AUTOMATICCAPTURE:
			stringValue = L"CAP_AUTOMATICCAPTURE";
			break;
		case CAP_TIMEBEFOREFIRSTCAPTURE:
			stringValue = L"CAP_TIMEBEFOREFIRSTCAPTURE";
			break;
		case CAP_TIMEBETWEENCAPTURES:
			stringValue = L"CAP_TIMEBETWEENCAPTURES";
			break;
		case CAP_CLEARBUFFERS:
			stringValue = L"CAP_CLEARBUFFERS";
			break;
		case CAP_MAXBATCHBUFFERS:
			stringValue = L"CAP_MAXBATCHBUFFERS";
			break;
		case CAP_DEVICETIMEDATE:
			stringValue = L"CAP_DEVICETIMEDATE";
			break;
		case CAP_POWERSUPPLY:
			stringValue = L"CAP_POWERSUPPLY";
			break;
		case CAP_CAMERAPREVIEWUI:
			stringValue = L"CAP_CAMERAPREVIEWUI";
			break;
		case CAP_DEVICEEVENT:
			stringValue = L"CAP_DEVICEEVENT";
			break;
		case CAP_SERIALNUMBER:
			stringValue = L"CAP_SERIALNUMBER";
			break;
		case CAP_PRINTER:
			stringValue = L"CAP_PRINTER";
			break;
		case CAP_PRINTERENABLED:
			stringValue = L"CAP_PRINTERENABLED";
			break;
		case CAP_PRINTERINDEX:
			stringValue = L"CAP_PRINTERINDEX";
			break;
		case CAP_PRINTERMODE:
			stringValue = L"CAP_PRINTERMODE";
			break;
		case CAP_PRINTERSTRING:
			stringValue = L"CAP_PRINTERSTRING";
			break;
		case CAP_PRINTERSUFFIX:
			stringValue = L"CAP_PRINTERSUFFIX";
			break;
		case CAP_LANGUAGE:
			stringValue = L"CAP_LANGUAGE";
			break;
		case CAP_FEEDERALIGNMENT:
			stringValue = L"CAP_FEEDERALIGNMENT";
			break;
		case CAP_FEEDERORDER:
			stringValue = L"CAP_FEEDERORDER";
			break;
		case CAP_REACQUIREALLOWED:
			stringValue = L"CAP_REACQUIREALLOWED";
			break;
		case CAP_BATTERYMINUTES:
			stringValue = L"CAP_BATTERYMINUTES";
			break;
		case CAP_BATTERYPERCENTAGE:
			stringValue = L"CAP_BATTERYPERCENTAGE";
			break;
			/* was missing */
#if USE_TWAIN_DSM
		case CAP_CAMERASIDE:
			stringValue = L"CAP_CAMERASIDE";
			break;
		case CAP_SEGMENTED:
			stringValue = L"CAP_SEGMENTED";
			break;
		case CAP_CAMERAENABLED:
			stringValue = L"CAP_CAMERAENABLED";
			break;
		case CAP_CAMERAORDER:
			stringValue = L"CAP_CAMERAORDER";
			break;
		case CAP_MICRENABLED:
			stringValue = L"CAP_MICRENABLED";
			break;
		case CAP_FEEDERPREP:
			stringValue = L"CAP_FEEDERPREP";
			break;
		case CAP_FEEDERPOCKET:
			stringValue = L"CAP_FEEDERPOCKET";
			break;
		case CAP_AUTOMATICSENSEMEDIUM:
			stringValue = L"CAP_AUTOMATICSENSEMEDIUM";
			break;
		case CAP_CUSTOMINTERFACEGUID:
			stringValue = L"CAP_CUSTOMINTERFACEGUID";
			break;
		case CAP_SUPPORTEDCAPSSEGMENTUNIQUE:
			stringValue = L"CAP_SUPPORTEDCAPSSEGMENTUNIQUE";
			break;
		case CAP_SUPPORTEDDATS:
			stringValue = L"CAP_SUPPORTEDDATS";
			break;
		case CAP_DOUBLEFEEDDETECTION:
			stringValue = L"CAP_DOUBLEFEEDDETECTION";
			break;
		case CAP_DOUBLEFEEDDETECTIONLENGTH:
			stringValue = L"CAP_DOUBLEFEEDDETECTIONLENGTH";
			break;
		case CAP_DOUBLEFEEDDETECTIONSENSITIVITY:
			stringValue = L"CAP_DOUBLEFEEDDETECTIONSENSITIVITY";
			break;
		case CAP_DOUBLEFEEDDETECTIONRESPONSE:
			stringValue = L"CAP_DOUBLEFEEDDETECTIONRESPONSE";
			break;
		case CAP_PAPERHANDLING:
			stringValue = L"CAP_PAPERHANDLING";
			break;
		case CAP_INDICATORSMODE:
			stringValue = L"CAP_INDICATORSMODE";
			break;
		case CAP_PRINTERVERTICALOFFSET:
			stringValue = L"CAP_PRINTERVERTICALOFFSET";
			break;
		case CAP_POWERSAVETIME:
			stringValue = L"CAP_POWERSAVETIME";
			break;
		case CAP_PRINTERCHARROTATION:
			stringValue = L"CAP_PRINTERCHARROTATION";
			break;
		case CAP_PRINTERFONTSTYLE:
			stringValue = L"CAP_PRINTERFONTSTYLE";
			break;
		case CAP_PRINTERINDEXLEADCHAR:
			stringValue = L"CAP_PRINTERINDEXLEADCHAR";
			break;
		case CAP_PRINTERINDEXMAXVALUE:
			stringValue = L"CAP_PRINTERINDEXMAXVALUE";
			break;
		case CAP_PRINTERINDEXNUMDIGITS:
			stringValue = L"CAP_PRINTERINDEXNUMDIGITS";
			break;
		case CAP_PRINTERINDEXSTEP:
			stringValue = L"CAP_PRINTERINDEXSTEP";
			break;
		case CAP_PRINTERINDEXTRIGGER:
			stringValue = L"CAP_PRINTERINDEXTRIGGER";
			break;
		case CAP_PRINTERSTRINGPREVIEW:
			stringValue = L"CAP_PRINTERSTRINGPREVIEW";
			break;
#endif
		case ICAP_AUTOBRIGHT:
			stringValue = L"ICAP_AUTOBRIGHT";
			break;
		case ICAP_BRIGHTNESS:
			stringValue = L"ICAP_BRIGHTNESS";
			break;
		case ICAP_CONTRAST:
			stringValue = L"ICAP_CONTRAST";
			break;
		case ICAP_CUSTHALFTONE:
			stringValue = L"ICAP_CUSTHALFTONE";
			break;
		case ICAP_EXPOSURETIME:
			stringValue = L"ICAP_EXPOSURETIME";
			break;
		case ICAP_FILTER:
			stringValue = L"ICAP_FILTER";
			break;
		case ICAP_FLASHUSED:
			stringValue = L"ICAP_FLASHUSED";
			break;
		case ICAP_GAMMA:
			stringValue = L"ICAP_GAMMA";
			break;
		case ICAP_HALFTONES:
			stringValue = L"ICAP_HALFTONES";
			break;
		case ICAP_HIGHLIGHT:
			stringValue = L"ICAP_HIGHLIGHT";
			break;
		case ICAP_IMAGEFILEFORMAT:
			stringValue = L"ICAP_IMAGEFILEFORMAT";
			break;
		case ICAP_LAMPSTATE:
			stringValue = L"ICAP_LAMPSTATE";
			break;
		case ICAP_LIGHTSOURCE:
			stringValue = L"ICAP_LIGHTSOURCE";
			break;
		case ICAP_ORIENTATION:
			stringValue = L"ICAP_ORIENTATION";
			break;
		case ICAP_PHYSICALWIDTH:
			stringValue = L"ICAP_PHYSICALWIDTH";
			break;
		case ICAP_PHYSICALHEIGHT:
			stringValue = L"ICAP_PHYSICALHEIGHT";
			break;
		case ICAP_SHADOW:
			stringValue = L"ICAP_SHADOW";
			break;
		case ICAP_FRAMES:
			stringValue = L"ICAP_FRAMES";
			break;
		case ICAP_XNATIVERESOLUTION:
			stringValue = L"ICAP_XNATIVERESOLUTION";
			break;
		case ICAP_YNATIVERESOLUTION:
			stringValue = L"ICAP_YNATIVERESOLUTION";
			break;
		case ICAP_XRESOLUTION:
			stringValue = L"ICAP_XRESOLUTION";
			break;
		case ICAP_YRESOLUTION:
			stringValue = L"ICAP_YRESOLUTION";
			break;
		case ICAP_MAXFRAMES:
			stringValue = L"ICAP_MAXFRAMES";
			break;
		case ICAP_TILES:
			stringValue = L"ICAP_TILES";
			break;
		case ICAP_BITORDER:
			stringValue = L"ICAP_BITORDER";
			break;
		case ICAP_CCITTKFACTOR:
			stringValue = L"ICAP_CCITTKFACTOR";
			break;
		case ICAP_LIGHTPATH:
			stringValue = L"ICAP_LIGHTPATH";
			break;
		case ICAP_PIXELFLAVOR:
			stringValue = L"ICAP_PIXELFLAVOR";
			break;
		case ICAP_PLANARCHUNKY:
			stringValue = L"ICAP_PLANARCHUNKY";
			break;
		case ICAP_ROTATION:
			stringValue = L"ICAP_ROTATION";
			break;
		case ICAP_SUPPORTEDSIZES:
			stringValue = L"ICAP_SUPPORTEDSIZES";
			break;
		case ICAP_THRESHOLD:
			stringValue = L"ICAP_THRESHOLD";
			break;
		case ICAP_XSCALING:
			stringValue = L"ICAP_XSCALING";
			break;
		case ICAP_YSCALING:
			stringValue = L"ICAP_YSCALING";
			break;
		case ICAP_BITORDERCODES:
			stringValue = L"ICAP_BITORDERCODES";
			break;
		case ICAP_PIXELFLAVORCODES:
			stringValue = L"ICAP_PIXELFLAVORCODES";
			break;
		case ICAP_JPEGPIXELTYPE:
			stringValue = L"ICAP_JPEGPIXELTYPE";
			break;
		case ICAP_TIMEFILL:
			stringValue = L"ICAP_TIMEFILL";
			break;
		case ICAP_BITDEPTH:
			stringValue = L"ICAP_BITDEPTH";
			break;
		case ICAP_BITDEPTHREDUCTION:
			stringValue = L"ICAP_BITDEPTHREDUCTION";
			break;
		case ICAP_UNDEFINEDIMAGESIZE:
			stringValue = L"ICAP_UNDEFINEDIMAGESIZE";
			break;
		case ICAP_IMAGEDATASET:
			stringValue = L"ICAP_IMAGEDATASET";
			break;
		case ICAP_EXTIMAGEINFO:
			stringValue = L"ICAP_EXTIMAGEINFO";
			break;
		case ICAP_MINIMUMHEIGHT:
			stringValue = L"ICAP_MINIMUMHEIGHT";
			break;
		case ICAP_MINIMUMWIDTH:
			stringValue = L"ICAP_MINIMUMWIDTH";
			break;
		case ICAP_FLIPROTATION:
			stringValue = L"ICAP_FLIPROTATION";
			break;
		case ICAP_BARCODEDETECTIONENABLED:
			stringValue = L"ICAP_BARCODEDETECTIONENABLED";
			break;
		case ICAP_SUPPORTEDBARCODETYPES:
			stringValue = L"ICAP_SUPPORTEDBARCODETYPES";
			break;
		case ICAP_BARCODEMAXSEARCHPRIORITIES:
			stringValue = L"ICAP_BARCODEMAXSEARCHPRIORITIES";
			break;
		case ICAP_BARCODESEARCHPRIORITIES:
			stringValue = L"ICAP_BARCODESEARCHPRIORITIES";
			break;
		case ICAP_BARCODESEARCHMODE:
			stringValue = L"ICAP_BARCODESEARCHMODE";
			break;
		case ICAP_BARCODEMAXRETRIES:
			stringValue = L"ICAP_BARCODEMAXRETRIES";
			break;
		case ICAP_BARCODETIMEOUT:
			stringValue = L"ICAP_BARCODETIMEOUT";
			break;
		case ICAP_ZOOMFACTOR:
			stringValue = L"ICAP_ZOOMFACTOR";
			break;
		case ICAP_PATCHCODEDETECTIONENABLED:
			stringValue = L"ICAP_PATCHCODEDETECTIONENABLED";
			break;
		case ICAP_SUPPORTEDPATCHCODETYPES:
			stringValue = L"ICAP_SUPPORTEDPATCHCODETYPES";
			break;
		case ICAP_PATCHCODEMAXSEARCHPRIORITIES:
			stringValue = L"ICAP_PATCHCODEMAXSEARCHPRIORITIES";
			break;
		case ICAP_PATCHCODESEARCHPRIORITIES:
			stringValue = L"ICAP_PATCHCODESEARCHPRIORITIES";
			break;
		case ICAP_PATCHCODESEARCHMODE:
			stringValue = L"ICAP_PATCHCODESEARCHMODE";
			break;
		case ICAP_PATCHCODEMAXRETRIES:
			stringValue = L"ICAP_PATCHCODEMAXRETRIES";
			break;
		case ICAP_PATCHCODETIMEOUT:
			stringValue = L"ICAP_PATCHCODETIMEOUT";
			break;
		case ICAP_FLASHUSED2:
			stringValue = L"ICAP_FLASHUSED2";
			break;
		case ICAP_IMAGEFILTER:
			stringValue = L"ICAP_IMAGEFILTER";
			break;
		case ICAP_NOISEFILTER:
			stringValue = L"ICAP_NOISEFILTER";
			break;
		case ICAP_OVERSCAN:
			stringValue = L"ICAP_OVERSCAN";
			break;
		case ICAP_AUTOMATICBORDERDETECTION:
			stringValue = L"ICAP_AUTOMATICBORDERDETECTION";
			break;
		case ICAP_AUTOMATICDESKEW:
			stringValue = L"ICAP_AUTOMATICDESKEW";
			break;
		case ICAP_AUTOMATICROTATE:
			stringValue = L"ICAP_AUTOMATICROTATE";
			break;
		case ICAP_JPEGQUALITY:
			stringValue = L"ICAP_JPEGQUALITY";
			break;
#if USE_TWAIN_DSM
		case ICAP_AUTODISCARDBLANKPAGES:
			stringValue = L"ICAP_AUTODISCARDBLANKPAGES";
			break;
		case ICAP_FEEDERTYPE:
			stringValue = L"ICAP_FEEDERTYPE";
			break;
		case ICAP_ICCPROFILE:
			stringValue = L"ICAP_ICCPROFILE";
			break;
		case ICAP_AUTOSIZE:
			stringValue = L"ICAP_AUTOSIZE";
			break;
		case ICAP_AUTOMATICCROPUSESFRAME:
			stringValue = L"ICAP_AUTOMATICCROPUSESFRAME";
			break;
		case ICAP_AUTOMATICLENGTHDETECTION:
			stringValue = L"ICAP_AUTOMATICLENGTHDETECTION";
			break;
		case ICAP_AUTOMATICCOLORENABLED:
			stringValue = L"ICAP_AUTOMATICCOLORENABLED";
			break;
		case ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE:
			stringValue = L"ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE";
			break;
		case ICAP_COLORMANAGEMENTENABLED:
			stringValue = L"ICAP_COLORMANAGEMENTENABLED";
			break;
		case ICAP_IMAGEMERGE:
			stringValue = L"ICAP_IMAGEMERGE";
			break;
		case ICAP_IMAGEMERGEHEIGHTTHRESHOLD:
			stringValue = L"ICAP_IMAGEMERGEHEIGHTTHRESHOLD";
			break;
		case ICAP_SUPPORTEDEXTIMAGEINFO:
			stringValue = L"ICAP_SUPPORTEDEXTIMAGEINFO";
			break;
		case ICAP_FILMTYPE:
			stringValue = L"ICAP_FILMTYPE";
			break;
		case ICAP_MIRROR:
			stringValue = L"ICAP_MIRROR";
			break;
		case ICAP_JPEGSUBSAMPLING:
			stringValue = L"ICAP_JPEGSUBSAMPLING";
			break;
#endif
		default:
		{
			wchar_t buf[33];
#if VERSIONWIN
			stringValue = _itow(cap, buf, 10);
#else
			swprintf(buf, 33, L"%d", cap);
			stringValue = buf;
#endif
		}
			break;
	}
}

void twain_get_option_value(TW_IDENTITY *tw_identity,
														TW_IDENTITY *tw_source_identity,
														TW_CAPABILITY *tw_capability,
														void *_entrypoint,
														JSONNODE *json_scanner_options)
{
#if USE_TWAIN_DSM
	TW_ENTRYPOINT *tw_entrypoint = (TW_ENTRYPOINT *)_entrypoint;
#else
	void *tw_entrypoint = 0;
#endif
	
	std::wstring optionName;
	twain_get_capability_option_name(tw_capability->Cap, optionName);
	
	/* name */
	JSONNODE *json_scanner_option = json_new(JSON_NODE);
	json_set_name(json_scanner_option, optionName.c_str());
	
	tw_capability->ConType = TWON_ONEVALUE;
	tw_capability->hContainer = 0;
	
	if(TWRC_SUCCESS == DSM_Entry(
															 tw_identity,
															 tw_source_identity,
															 DG_CONTROL,
															 DAT_CAPABILITY,
															 MSG_GET,
															 (TW_MEMREF)tw_capability))
	{
		twain_get_capability_value(tw_capability,
															 DSM::Lock(tw_entrypoint, tw_capability->hContainer),
															 json_scanner_option);
		
		DSM::Unlock(tw_entrypoint, tw_capability->hContainer);
		DSM::Free(tw_entrypoint, tw_capability->hContainer);
	}
	
	json_push_back(json_scanner_options, json_scanner_option);
}

TW_UINT16 json_get_cap(json_char *name)
{
	TW_UINT16 cap = 0;

#if VERSIONWIN
	cap = _wtoi(name);
#else
	std::wstringstream conv;
	conv << name;
	conv >> cap;
#endif
	
	std::wstring s = std::wstring((const wchar_t *)name);
	
	if (s.compare(L"CAP_XFERCOUNT") == 0)
	{
		cap = CAP_XFERCOUNT;goto exit;
	}
	if (s.compare(L"ICAP_COMPRESSION") == 0)
	{
		cap = ICAP_COMPRESSION;goto exit;
	}
	if (s.compare(L"ICAP_PIXELTYPE") == 0)
	{
		cap = ICAP_PIXELTYPE;goto exit;
	}
	if (s.compare(L"ICAP_UNITS") == 0)
	{
		cap = ICAP_UNITS;goto exit;
	}
	if (s.compare(L"ICAP_XFERMECH") == 0)
	{
		cap = ICAP_XFERMECH;goto exit;
	}
	if (s.compare(L"CAP_AUTHOR") == 0)
	{
		cap = CAP_AUTHOR;goto exit;
	}
	if (s.compare(L"CAP_CAPTION") == 0)
	{
		cap = CAP_CAPTION;goto exit;
	}
	if (s.compare(L"CAP_FEEDERENABLED") == 0)
	{
		cap = CAP_FEEDERENABLED;goto exit;
	}
	if (s.compare(L"CAP_FEEDERLOADED") == 0)
	{
		cap = CAP_FEEDERLOADED;goto exit;
	}
	if (s.compare(L"CAP_TIMEDATE") == 0)
	{
		cap = CAP_TIMEDATE;goto exit;
	}
	if (s.compare(L"CAP_SUPPORTEDCAPS") == 0)
	{
		cap = CAP_SUPPORTEDCAPS;goto exit;
	}
	if (s.compare(L"CAP_EXTENDEDCAPS") == 0)
	{
		cap = CAP_EXTENDEDCAPS;goto exit;
	}
	if (s.compare(L"CAP_AUTOFEED") == 0)
	{
		cap = CAP_AUTOFEED;goto exit;
	}
	if (s.compare(L"CAP_CLEARPAGE") == 0)
	{
		cap = CAP_CLEARPAGE;goto exit;
	}
	if (s.compare(L"CAP_FEEDPAGE") == 0)
	{
		cap = CAP_FEEDPAGE;goto exit;
	}
	if (s.compare(L"CAP_REWINDPAGE") == 0)
	{
		cap = CAP_REWINDPAGE;goto exit;
	}
	if (s.compare(L"CAP_INDICATORS") == 0)
	{
		cap = CAP_INDICATORS;goto exit;
	}
	if (s.compare(L"CAP_SUPPORTEDCAPSEXT") == 0)
	{
		cap = CAP_SUPPORTEDCAPSEXT;goto exit;
	}
	if (s.compare(L"CAP_PAPERDETECTABLE") == 0)
	{
		cap = CAP_PAPERDETECTABLE;goto exit;
	}
	if (s.compare(L"CAP_UICONTROLLABLE") == 0)
	{
		cap = CAP_UICONTROLLABLE;goto exit;
	}
	if (s.compare(L"CAP_DEVICEONLINE") == 0)
	{
		cap = CAP_DEVICEONLINE;goto exit;
	}
	if (s.compare(L"CAP_AUTOSCAN") == 0)
	{
		cap = CAP_AUTOSCAN;goto exit;
	}
	if (s.compare(L"CAP_THUMBNAILSENABLED") == 0)
	{
		cap = CAP_THUMBNAILSENABLED;goto exit;
	}
	if (s.compare(L"CAP_DUPLEX") == 0)
	{
		cap = CAP_DUPLEX;goto exit;
	}
	if (s.compare(L"CAP_DUPLEXENABLED") == 0)
	{
		cap = CAP_DUPLEXENABLED;goto exit;
	}
	if (s.compare(L"CAP_ENABLEDSUIONLY") == 0)
	{
		cap = CAP_ENABLEDSUIONLY;goto exit;
	}
	if (s.compare(L"CAP_CUSTOMDSDATA") == 0)
	{
		cap = CAP_CUSTOMDSDATA;goto exit;
	}
	if (s.compare(L"CAP_ENDORSER") == 0)
	{
		cap = CAP_ENDORSER;goto exit;
	}
	if (s.compare(L"CAP_JOBCONTROL") == 0)
	{
		cap = CAP_JOBCONTROL;goto exit;
	}
	if (s.compare(L"CAP_ALARMS") == 0)
	{
		cap = CAP_ALARMS;goto exit;
	}
	if (s.compare(L"CAP_ALARMVOLUME") == 0)
	{
		cap = CAP_ALARMVOLUME;goto exit;
	}
	if (s.compare(L"CAP_AUTOMATICCAPTURE") == 0)
	{
		cap = CAP_AUTOMATICCAPTURE;goto exit;
	}
	if (s.compare(L"CAP_TIMEBEFOREFIRSTCAPTURE") == 0)
	{
		cap = CAP_TIMEBEFOREFIRSTCAPTURE;goto exit;
	}
	if (s.compare(L"CAP_TIMEBETWEENCAPTURES") == 0)
	{
		cap = CAP_TIMEBETWEENCAPTURES;goto exit;
	}
	if (s.compare(L"CAP_CLEARBUFFERS") == 0)
	{
		cap = CAP_CLEARBUFFERS;goto exit;
	}
	if (s.compare(L"CAP_MAXBATCHBUFFERS") == 0)
	{
		cap = CAP_MAXBATCHBUFFERS;goto exit;
	}
	if (s.compare(L"CAP_DEVICETIMEDATE") == 0)
	{
		cap = CAP_DEVICETIMEDATE;goto exit;
	}
	if (s.compare(L"CAP_POWERSUPPLY") == 0)
	{
		cap = CAP_POWERSUPPLY;goto exit;
	}
	if (s.compare(L"CAP_CAMERAPREVIEWUI") == 0)
	{
		cap = CAP_CAMERAPREVIEWUI;goto exit;
	}
	if (s.compare(L"CAP_DEVICEEVENT") == 0)
	{
		cap = CAP_DEVICEEVENT;goto exit;
	}
	if (s.compare(L"CAP_SERIALNUMBER") == 0)
	{
		cap = CAP_SERIALNUMBER;goto exit;
	}
	if (s.compare(L"CAP_PRINTER") == 0)
	{
		cap = CAP_PRINTER;goto exit;
	}
	if (s.compare(L"CAP_PRINTERENABLED") == 0)
	{
		cap = CAP_PRINTERENABLED;goto exit;
	}
	if (s.compare(L"CAP_PRINTERINDEX") == 0)
	{
		cap = CAP_PRINTERINDEX;goto exit;
	}
	if (s.compare(L"CAP_PRINTERMODE") == 0)
	{
		cap = CAP_PRINTERMODE;goto exit;
	}
	if (s.compare(L"CAP_PRINTERSTRING") == 0)
	{
		cap = CAP_PRINTERSTRING;goto exit;
	}
	if (s.compare(L"CAP_PRINTERSUFFIX") == 0)
	{
		cap = CAP_PRINTERSUFFIX;goto exit;
	}
	if (s.compare(L"CAP_LANGUAGE") == 0)
	{
		cap = CAP_LANGUAGE;goto exit;
	}
	if (s.compare(L"CAP_FEEDERALIGNMENT") == 0)
	{
		cap = CAP_FEEDERALIGNMENT;goto exit;
	}
	if (s.compare(L"CAP_FEEDERORDER") == 0)
	{
		cap = CAP_FEEDERORDER;goto exit;
	}
	if (s.compare(L"CAP_REACQUIREALLOWED") == 0)
	{
		cap = CAP_REACQUIREALLOWED;goto exit;
	}
	if (s.compare(L"CAP_BATTERYMINUTES") == 0)
	{
		cap = CAP_BATTERYMINUTES;goto exit;
	}
	if (s.compare(L"CAP_BATTERYPERCENTAGE") == 0)
	{
		cap = CAP_BATTERYPERCENTAGE;goto exit;
	}
#if USE_TWAIN_DSM
	if (s.compare(L"CAP_CAMERASIDE") == 0)
	{
		cap = CAP_CAMERASIDE;goto exit;
	}
	if (s.compare(L"CAP_SEGMENTED") == 0)
	{
		cap = CAP_SEGMENTED;goto exit;
	}
	if (s.compare(L"CAP_CAMERAENABLED") == 0)
	{
		cap = CAP_CAMERAENABLED;goto exit;
	}
	if (s.compare(L"CAP_CAMERAORDER") == 0)
	{
		cap = CAP_CAMERAORDER;goto exit;
	}
	if (s.compare(L"CAP_MICRENABLED") == 0)
	{
		cap = CAP_MICRENABLED;goto exit;
	}
	if (s.compare(L"CAP_FEEDERPREP") == 0)
	{
		cap = CAP_FEEDERPREP;goto exit;
	}
	if (s.compare(L"CAP_FEEDERPOCKET") == 0)
	{
		cap = CAP_FEEDERPOCKET;goto exit;
	}
	if (s.compare(L"CAP_AUTOMATICSENSEMEDIUM") == 0)
	{
		cap = CAP_AUTOMATICSENSEMEDIUM;goto exit;
	}
	if (s.compare(L"CAP_CUSTOMINTERFACEGUID") == 0)
	{
		cap = CAP_CUSTOMINTERFACEGUID;goto exit;
	}
	if (s.compare(L"CAP_SUPPORTEDCAPSSEGMENTUNIQUE") == 0)
	{
		cap = CAP_SUPPORTEDCAPSSEGMENTUNIQUE;goto exit;
	}
	if (s.compare(L"CAP_SUPPORTEDDATS") == 0)
	{
		cap = CAP_SUPPORTEDDATS;goto exit;
	}
	if (s.compare(L"CAP_DOUBLEFEEDDETECTION") == 0)
	{
		cap = CAP_DOUBLEFEEDDETECTION;goto exit;
	}
	if (s.compare(L"CAP_DOUBLEFEEDDETECTIONLENGTH") == 0)
	{
		cap = CAP_DOUBLEFEEDDETECTIONLENGTH;goto exit;
	}
	if (s.compare(L"CAP_DOUBLEFEEDDETECTIONSENSITIVITY") == 0)
	{
		cap = CAP_DOUBLEFEEDDETECTIONSENSITIVITY;goto exit;
	}
	if (s.compare(L"CAP_DOUBLEFEEDDETECTIONRESPONSE") == 0)
	{
		cap = CAP_DOUBLEFEEDDETECTIONRESPONSE;goto exit;
	}
	if (s.compare(L"CAP_PAPERHANDLING") == 0)
	{
		cap = CAP_PAPERHANDLING;goto exit;
	}
	if (s.compare(L"CAP_INDICATORSMODE") == 0)
	{
		cap = CAP_INDICATORSMODE;goto exit;
	}
	if (s.compare(L"CAP_PRINTERVERTICALOFFSET") == 0)
	{
		cap = CAP_PRINTERVERTICALOFFSET;goto exit;
	}
	if (s.compare(L"CAP_POWERSAVETIME") == 0)
	{
		cap = CAP_POWERSAVETIME;goto exit;
	}
	if (s.compare(L"CAP_PRINTERCHARROTATION") == 0)
	{
		cap = CAP_PRINTERCHARROTATION;goto exit;
	}
	if (s.compare(L"CAP_PRINTERFONTSTYLE") == 0)
	{
		cap = CAP_PRINTERFONTSTYLE;goto exit;
	}
	if (s.compare(L"CAP_PRINTERINDEXLEADCHAR") == 0)
	{
		cap = CAP_PRINTERINDEXLEADCHAR;goto exit;
	}
	if (s.compare(L"CAP_PRINTERINDEXMAXVALUE") == 0)
	{
		cap = CAP_PRINTERINDEXMAXVALUE;goto exit;
	}
	if (s.compare(L"CAP_PRINTERINDEXNUMDIGITS") == 0)
	{
		cap = CAP_PRINTERINDEXNUMDIGITS;goto exit;
	}
	if (s.compare(L"CAP_PRINTERINDEXSTEP") == 0)
	{
		cap = CAP_PRINTERINDEXSTEP;goto exit;
	}
	if (s.compare(L"CAP_PRINTERINDEXTRIGGER") == 0)
	{
		cap = CAP_PRINTERINDEXTRIGGER;goto exit;
	}
	if (s.compare(L"CAP_PRINTERSTRINGPREVIEW") == 0)
	{
		cap = CAP_PRINTERSTRINGPREVIEW;goto exit;
	}
	if (s.compare(L"ICAP_AUTODISCARDBLANKPAGES") == 0)
	{
		cap = ICAP_AUTODISCARDBLANKPAGES;goto exit;
	}
	if (s.compare(L"ICAP_FEEDERTYPE") == 0)
	{
		cap = ICAP_FEEDERTYPE;goto exit;
	}
	if (s.compare(L"ICAP_ICCPROFILE") == 0)
	{
		cap = ICAP_ICCPROFILE;goto exit;
	}
	if (s.compare(L"ICAP_AUTOSIZE") == 0)
	{
		cap = ICAP_AUTOSIZE;goto exit;
	}
	if (s.compare(L"ICAP_AUTOMATICCROPUSESFRAME") == 0)
	{
		cap = ICAP_AUTOMATICCROPUSESFRAME;goto exit;
	}
	if (s.compare(L"ICAP_AUTOMATICLENGTHDETECTION") == 0)
	{
		cap = ICAP_AUTOMATICLENGTHDETECTION;goto exit;
	}
	if (s.compare(L"ICAP_AUTOMATICCOLORENABLED") == 0)
	{
		cap = ICAP_AUTOMATICCOLORENABLED;goto exit;
	}
	if (s.compare(L"ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE") == 0)
	{
		cap = ICAP_AUTOMATICCOLORNONCOLORPIXELTYPE;goto exit;
	}
	if (s.compare(L"ICAP_COLORMANAGEMENTENABLED") == 0)
	{
		cap = ICAP_COLORMANAGEMENTENABLED;goto exit;
	}
	if (s.compare(L"ICAP_IMAGEMERGE") == 0)
	{
		cap = ICAP_IMAGEMERGE;goto exit;
	}
	if (s.compare(L"ICAP_IMAGEMERGEHEIGHTTHRESHOLD") == 0)
	{
		cap = ICAP_IMAGEMERGEHEIGHTTHRESHOLD;goto exit;
	}
	if (s.compare(L"ICAP_SUPPORTEDEXTIMAGEINFO") == 0)
	{
		cap = ICAP_SUPPORTEDEXTIMAGEINFO;goto exit;
	}
	if (s.compare(L"ICAP_FILMTYPE") == 0)
	{
		cap = ICAP_FILMTYPE;goto exit;
	}
	if (s.compare(L"ICAP_MIRROR") == 0)
	{
		cap = ICAP_MIRROR;goto exit;
	}
	if (s.compare(L"ICAP_JPEGSUBSAMPLING") == 0)
	{
		cap = ICAP_JPEGSUBSAMPLING;goto exit;
	}
#endif
	if (s.compare(L"ICAP_AUTOBRIGHT") == 0)
	{
		cap = ICAP_AUTOBRIGHT;goto exit;
	}
	if (s.compare(L"ICAP_BRIGHTNESS") == 0)
	{
		cap = ICAP_BRIGHTNESS;goto exit;
	}
	if (s.compare(L"ICAP_CONTRAST") == 0)
	{
		cap = ICAP_CONTRAST;goto exit;
	}
	if (s.compare(L"ICAP_CUSTHALFTONE") == 0)
	{
		cap = ICAP_CUSTHALFTONE;goto exit;
	}
	if (s.compare(L"ICAP_EXPOSURETIME") == 0)
	{
		cap = ICAP_EXPOSURETIME;goto exit;
	}
	if (s.compare(L"ICAP_FILTER") == 0)
	{
		cap = ICAP_FILTER;goto exit;
	}
	if (s.compare(L"ICAP_FLASHUSED") == 0)
	{
		cap = ICAP_FLASHUSED;goto exit;
	}
	if (s.compare(L"ICAP_GAMMA") == 0)
	{
		cap = ICAP_GAMMA;goto exit;
	}
	if (s.compare(L"ICAP_HALFTONES") == 0)
	{
		cap = ICAP_HALFTONES;goto exit;
	}
	if (s.compare(L"ICAP_HIGHLIGHT") == 0)
	{
		cap = ICAP_HIGHLIGHT;goto exit;
	}
	if (s.compare(L"ICAP_IMAGEFILEFORMAT") == 0)
	{
		cap = ICAP_IMAGEFILEFORMAT;goto exit;
	}
	if (s.compare(L"ICAP_LAMPSTATE") == 0)
	{
		cap = ICAP_LAMPSTATE;goto exit;
	}
	if (s.compare(L"ICAP_LIGHTSOURCE") == 0)
	{
		cap = ICAP_LIGHTSOURCE;goto exit;
	}
	if (s.compare(L"ICAP_ORIENTATION") == 0)
	{
		cap = ICAP_ORIENTATION;goto exit;
	}
	if (s.compare(L"ICAP_PHYSICALWIDTH") == 0)
	{
		cap = ICAP_PHYSICALWIDTH;goto exit;
	}
	if (s.compare(L"ICAP_PHYSICALHEIGHT") == 0)
	{
		cap = ICAP_PHYSICALHEIGHT;goto exit;
	}
	if (s.compare(L"ICAP_SHADOW") == 0)
	{
		cap = ICAP_SHADOW;goto exit;
	}
	if (s.compare(L"ICAP_FRAMES") == 0)
	{
		cap = ICAP_FRAMES;goto exit;
	}
	if (s.compare(L"ICAP_XNATIVERESOLUTION") == 0)
	{
		cap = ICAP_XNATIVERESOLUTION;goto exit;
	}
	if (s.compare(L"ICAP_YNATIVERESOLUTION") == 0)
	{
		cap = ICAP_YNATIVERESOLUTION;goto exit;
	}
	if (s.compare(L"ICAP_XRESOLUTION") == 0)
	{
		cap = ICAP_XRESOLUTION;goto exit;
	}
	if (s.compare(L"ICAP_YRESOLUTION") == 0)
	{
		cap = ICAP_YRESOLUTION;goto exit;
	}
	if (s.compare(L"ICAP_MAXFRAMES") == 0)
	{
		cap = ICAP_MAXFRAMES;goto exit;
	}
	if (s.compare(L"ICAP_TILES") == 0)
	{
		cap = ICAP_TILES;goto exit;
	}
	if (s.compare(L"ICAP_BITORDER") == 0)
	{
		cap = ICAP_BITORDER;goto exit;
	}
	if (s.compare(L"ICAP_CCITTKFACTOR") == 0)
	{
		cap = ICAP_CCITTKFACTOR;goto exit;
	}
	if (s.compare(L"ICAP_LIGHTPATH") == 0)
	{
		cap = ICAP_LIGHTPATH;goto exit;
	}
	if (s.compare(L"ICAP_PIXELFLAVOR") == 0)
	{
		cap = ICAP_PIXELFLAVOR;goto exit;
	}
	if (s.compare(L"ICAP_PLANARCHUNKY") == 0)
	{
		cap = ICAP_PLANARCHUNKY;goto exit;
	}
	if (s.compare(L"ICAP_ROTATION") == 0)
	{
		cap = ICAP_ROTATION;goto exit;
	}
	if (s.compare(L"ICAP_SUPPORTEDSIZES") == 0)
	{
		cap = ICAP_SUPPORTEDSIZES;goto exit;
	}
	if (s.compare(L"ICAP_THRESHOLD") == 0)
	{
		cap = ICAP_THRESHOLD;goto exit;
	}
	if (s.compare(L"ICAP_XSCALING") == 0)
	{
		cap = ICAP_XSCALING;goto exit;
	}
	if (s.compare(L"ICAP_YSCALING") == 0)
	{
		cap = ICAP_YSCALING;goto exit;
	}
	if (s.compare(L"ICAP_BITORDERCODES") == 0)
	{
		cap = ICAP_BITORDERCODES;goto exit;
	}
	if (s.compare(L"ICAP_PIXELFLAVORCODES") == 0)
	{
		cap = ICAP_PIXELFLAVORCODES;goto exit;
	}
	if (s.compare(L"ICAP_JPEGPIXELTYPE") == 0)
	{
		cap = ICAP_JPEGPIXELTYPE;goto exit;
	}
	if (s.compare(L"ICAP_TIMEFILL") == 0)
	{
		cap = ICAP_TIMEFILL;goto exit;
	}
	if (s.compare(L"ICAP_BITDEPTH") == 0)
	{
		cap = ICAP_BITDEPTH;goto exit;
	}
	if (s.compare(L"ICAP_BITDEPTHREDUCTION") == 0)
	{
		cap = ICAP_BITDEPTHREDUCTION;goto exit;
	}
	if (s.compare(L"ICAP_UNDEFINEDIMAGESIZE") == 0)
	{
		cap = ICAP_UNDEFINEDIMAGESIZE;goto exit;
	}
	if (s.compare(L"ICAP_IMAGEDATASET") == 0)
	{
		cap = ICAP_IMAGEDATASET;goto exit;
	}
	if (s.compare(L"ICAP_EXTIMAGEINFO") == 0)
	{
		cap = ICAP_EXTIMAGEINFO;goto exit;
	}
	if (s.compare(L"ICAP_MINIMUMHEIGHT") == 0)
	{
		cap = ICAP_MINIMUMHEIGHT;goto exit;
	}
	if (s.compare(L"ICAP_MINIMUMWIDTH") == 0)
	{
		cap = ICAP_MINIMUMWIDTH;goto exit;
	}
	if (s.compare(L"ICAP_FLIPROTATION") == 0)
	{
		cap = ICAP_FLIPROTATION;goto exit;
	}
	if (s.compare(L"ICAP_BARCODEDETECTIONENABLED") == 0)
	{
		cap = ICAP_BARCODEDETECTIONENABLED;goto exit;
	}
	if (s.compare(L"ICAP_SUPPORTEDBARCODETYPES") == 0)
	{
		cap = ICAP_SUPPORTEDBARCODETYPES;goto exit;
	}
	if (s.compare(L"ICAP_BARCODEMAXSEARCHPRIORITIES") == 0)
	{
		cap = ICAP_BARCODEMAXSEARCHPRIORITIES;goto exit;
	}
	if (s.compare(L"ICAP_BARCODESEARCHPRIORITIES") == 0)
	{
		cap = ICAP_BARCODESEARCHPRIORITIES;goto exit;
	}
	if (s.compare(L"ICAP_BARCODESEARCHMODE") == 0)
	{
		cap = ICAP_BARCODESEARCHMODE;goto exit;
	}
	if (s.compare(L"ICAP_BARCODEMAXRETRIES") == 0)
	{
		cap = ICAP_BARCODEMAXRETRIES;goto exit;
	}
	if (s.compare(L"ICAP_BARCODETIMEOUT") == 0)
	{
		cap = ICAP_BARCODETIMEOUT;goto exit;
	}
	if (s.compare(L"ICAP_ZOOMFACTOR") == 0)
	{
		cap = ICAP_ZOOMFACTOR;goto exit;
	}
	if (s.compare(L"ICAP_PATCHCODEDETECTIONENABLED") == 0)
	{
		cap = ICAP_PATCHCODEDETECTIONENABLED;goto exit;
	}
	if (s.compare(L"ICAP_SUPPORTEDPATCHCODETYPES") == 0)
	{
		cap = ICAP_SUPPORTEDPATCHCODETYPES;goto exit;
	}
	if (s.compare(L"ICAP_PATCHCODEMAXSEARCHPRIORITIES") == 0)
	{
		cap = ICAP_PATCHCODEMAXSEARCHPRIORITIES;goto exit;
	}
	if (s.compare(L"ICAP_PATCHCODESEARCHPRIORITIES") == 0)
	{
		cap = ICAP_PATCHCODESEARCHPRIORITIES;goto exit;
	}
	if (s.compare(L"ICAP_PATCHCODESEARCHMODE") == 0)
	{
		cap = ICAP_PATCHCODESEARCHMODE;goto exit;
	}
	if (s.compare(L"ICAP_PATCHCODEMAXRETRIES") == 0)
	{
		cap = ICAP_PATCHCODEMAXRETRIES;goto exit;
	}
	if (s.compare(L"ICAP_PATCHCODETIMEOUT") == 0)
	{
		cap = ICAP_PATCHCODETIMEOUT;goto exit;
	}
	if (s.compare(L"ICAP_FLASHUSED2") == 0)
	{
		cap = ICAP_FLASHUSED2;goto exit;
	}
	if (s.compare(L"ICAP_IMAGEFILTER") == 0)
	{
		cap = ICAP_IMAGEFILTER;goto exit;
	}
	if (s.compare(L"ICAP_NOISEFILTER") == 0)
	{
		cap = ICAP_NOISEFILTER;goto exit;
	}
	if (s.compare(L"ICAP_OVERSCAN") == 0)
	{
		cap = ICAP_OVERSCAN;goto exit;
	}
	if (s.compare(L"ICAP_AUTOMATICBORDERDETECTION") == 0)
	{
		cap = ICAP_AUTOMATICBORDERDETECTION;goto exit;
	}
	if (s.compare(L"ICAP_AUTOMATICDESKEW") == 0)
	{
		cap = ICAP_AUTOMATICDESKEW;goto exit;
	}
	if (s.compare(L"ICAP_AUTOMATICROTATE") == 0)
	{
		cap = ICAP_AUTOMATICROTATE;goto exit;
	}
	if (s.compare(L"ICAP_JPEGQUALITY") == 0)
	{
		cap = ICAP_JPEGQUALITY;goto exit;
	}
	
exit:
	return cap;
}

int json_get_cap_constant(JSONNODE *n, TW_UINT16 cap)
{
	int v = json_as_int(n);

	json_char *name = json_as_string(n);

	if (name)
	{
		std::wstring s = std::wstring((const wchar_t *)name);
		switch (cap)
		{
			//convert to constant
#if USE_TWAIN_DSM
		case ICAP_AUTOSIZE:
		{
			if (s.compare(L"TWAS_NONE") == 0)
			{
				v = TWAS_NONE;goto exit2;
			}
			if (s.compare(L"TWAS_AUTO") == 0)
			{
				v = TWAS_AUTO;goto exit2;
			}
			if (s.compare(L"TWAS_CURRENT") == 0)
			{
				v = TWAS_CURRENT;goto exit2;
			}

		}
		break;
		case ICAP_AUTODISCARDBLANKPAGES:
		{
			if (s.compare(L"TWBP_DISABLE") == 0)
			{
				v = TWBP_DISABLE;goto exit2;
			}
			if (s.compare(L"TWBP_AUTO") == 0)
			{
				v = TWBP_AUTO;goto exit2;
			}

		}
		break;
		case CAP_CAMERASIDE:
		{
			if (s.compare(L"TWCS_BOTH") == 0)
			{
				v = TWCS_BOTH;goto exit2;
			}
			if (s.compare(L"TWCS_TOP") == 0)
			{
				v = TWCS_TOP;goto exit2;
			}
			if (s.compare(L"TWCS_BOTTOM") == 0)
			{
				v = TWCS_BOTTOM;goto exit2;
			}

		}
		break;
		case ICAP_FEEDERTYPE:
		{
			if (s.compare(L"TWFE_GENERAL") == 0)
			{
				v = TWFE_GENERAL;goto exit2;
			}
			if (s.compare(L"TWFE_PHOTO") == 0)
			{
				v = TWFE_PHOTO;goto exit2;
			}

		}
		break;
		case CAP_FEEDERPOCKET:
		{
			if (s.compare(L"TWFP_POCKETERROR") == 0)
			{
				v = TWFP_POCKETERROR;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET1") == 0)
			{
				v = TWFP_POCKET1;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET2") == 0)
			{
				v = TWFP_POCKET2;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET3") == 0)
			{
				v = TWFP_POCKET3;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET4") == 0)
			{
				v = TWFP_POCKET4;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET5") == 0)
			{
				v = TWFP_POCKET5;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET6") == 0)
			{
				v = TWFP_POCKET6;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET7") == 0)
			{
				v = TWFP_POCKET7;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET8") == 0)
			{
				v = TWFP_POCKET8;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET9") == 0)
			{
				v = TWFP_POCKET9;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET10") == 0)
			{
				v = TWFP_POCKET10;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET11") == 0)
			{
				v = TWFP_POCKET11;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET12") == 0)
			{
				v = TWFP_POCKET12;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET13") == 0)
			{
				v = TWFP_POCKET13;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET14") == 0)
			{
				v = TWFP_POCKET14;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET15") == 0)
			{
				v = TWFP_POCKET15;goto exit2;
			}
			if (s.compare(L"TWFP_POCKET16") == 0)
			{
				v = TWFP_POCKET16;goto exit2;
			}

		}
		break;
		case ICAP_ICCPROFILE:
		{
			if (s.compare(L"TWIC_NONE") == 0)
			{
				v = TWIC_NONE;goto exit2;
			}
			if (s.compare(L"TWIC_LINK") == 0)
			{
				v = TWIC_LINK;goto exit2;
			}
			if (s.compare(L"TWIC_EMBED") == 0)
			{
				v = TWIC_EMBED;goto exit2;
			}

		}
		break;
		case ICAP_IMAGEMERGE:
		{
			if (s.compare(L"TWIM_NONE") == 0)
			{
				v = TWIM_NONE;goto exit2;
			}
			if (s.compare(L"TWIM_FRONTONTOP") == 0)
			{
				v = TWIM_FRONTONTOP;goto exit2;
			}
			if (s.compare(L"TWIM_FRONTONBOTTOM") == 0)
			{
				v = TWIM_FRONTONBOTTOM;goto exit2;
			}
			if (s.compare(L"TWIM_FRONTONLEFT") == 0)
			{
				v = TWIM_FRONTONLEFT;goto exit2;
			}
			if (s.compare(L"TWIM_FRONTONRIGHT") == 0)
			{
				v = TWIM_FRONTONRIGHT;goto exit2;
			}

		}
		break;
		case CAP_SEGMENTED:
		{
			if (s.compare(L"TWSG_NONE") == 0)
			{
				v = TWSG_NONE;goto exit2;
			}
			if (s.compare(L"TWSG_AUTO") == 0)
			{
				v = TWSG_AUTO;goto exit2;
			}
			if (s.compare(L"TWSG_MANUAL") == 0)
			{
				v = TWSG_MANUAL;goto exit2;
			}

		}
		break;
#endif
		case CAP_ALARMS:
		{
			if (s.compare(L"TWAL_ALARM") == 0)
			{
				v = TWAL_ALARM;goto exit2;
			}
			if (s.compare(L"TWAL_FEEDERERROR") == 0)
			{
				v = TWAL_FEEDERERROR;goto exit2;
			}
			if (s.compare(L"TWAL_FEEDERWARNING") == 0)
			{
				v = TWAL_FEEDERWARNING;goto exit2;
			}
			if (s.compare(L"TWAL_BARCODE") == 0)
			{
				v = TWAL_BARCODE;goto exit2;
			}
			if (s.compare(L"TWAL_DOUBLEFEED") == 0)
			{
				v = TWAL_DOUBLEFEED;goto exit2;
			}
			if (s.compare(L"TWAL_JAM") == 0)
			{
				v = TWAL_JAM;goto exit2;
			}
			if (s.compare(L"TWAL_PATCHCODE") == 0)
			{
				v = TWAL_PATCHCODE;goto exit2;
			}
			if (s.compare(L"TWAL_POWER") == 0)
			{
				v = TWAL_POWER;goto exit2;
			}
			if (s.compare(L"TWAL_SKEW") == 0)
			{
				v = TWAL_SKEW;goto exit2;
			}

		}
		break;
		case ICAP_COMPRESSION:
		{
			if (s.compare(L"TWCP_NONE") == 0)
			{
				v = TWCP_NONE;goto exit2;
			}
			if (s.compare(L"TWCP_PACKBITS") == 0)
			{
				v = TWCP_PACKBITS;goto exit2;
			}
			if (s.compare(L"TWCP_GROUP31D") == 0)
			{
				v = TWCP_GROUP31D;goto exit2;
			}
			if (s.compare(L"TWCP_GROUP31DEOL") == 0)
			{
				v = TWCP_GROUP31DEOL;goto exit2;
			}
			if (s.compare(L"TWCP_GROUP32D") == 0)
			{
				v = TWCP_GROUP32D;goto exit2;
			}
			if (s.compare(L"TWCP_GROUP4") == 0)
			{
				v = TWCP_GROUP4;goto exit2;
			}
			if (s.compare(L"TWCP_JPEG") == 0)
			{
				v = TWCP_JPEG;goto exit2;
			}
			if (s.compare(L"TWCP_LZW") == 0)
			{
				v = TWCP_LZW;goto exit2;
			}
			if (s.compare(L"TWCP_JBIG") == 0)
			{
				v = TWCP_JBIG;goto exit2;
			}
			if (s.compare(L"TWCP_PNG") == 0)
			{
				v = TWCP_PNG;goto exit2;
			}
			if (s.compare(L"TWCP_RLE4") == 0)
			{
				v = TWCP_RLE4;goto exit2;
			}
			if (s.compare(L"TWCP_RLE8") == 0)
			{
				v = TWCP_RLE8;goto exit2;
			}
			if (s.compare(L"TWCP_BITFIELDS") == 0)
			{
				v = TWCP_BITFIELDS;goto exit2;
			}

		}
		break;
		case ICAP_BARCODESEARCHMODE:
		{
			if (s.compare(L"TWBD_HORZ") == 0)
			{
				v = TWBD_HORZ;goto exit2;
			}
			if (s.compare(L"TWBD_VERT") == 0)
			{
				v = TWBD_VERT;goto exit2;
			}
			if (s.compare(L"TWBD_HORZVERT") == 0)
			{
				v = TWBD_HORZVERT;goto exit2;
			}
			if (s.compare(L"TWBD_VERTHORZ") == 0)
			{
				v = TWBD_VERTHORZ;goto exit2;
			}

		}
		break;
		case ICAP_BITORDER:
		{
			if (s.compare(L"TWBO_LSBFIRST") == 0)
			{
				v = TWBO_LSBFIRST;goto exit2;
			}
			if (s.compare(L"TWBO_MSBFIRST") == 0)
			{
				v = TWBO_MSBFIRST;goto exit2;
			}

		}
		break;
		case ICAP_BITDEPTHREDUCTION:
		{
			if (s.compare(L"TWBR_THRESHOLD") == 0)
			{
				v = TWBR_THRESHOLD;goto exit2;
			}
			if (s.compare(L"TWBR_HALFTONE") == 0)
			{
				v = TWBR_HALFTONE;goto exit2;
			}
			if (s.compare(L"TWBR_CUSTHALFTONE") == 0)
			{
				v = TWBR_CUSTHALFTONE;goto exit2;
			}
			if (s.compare(L"TWBR_DIFFUSION") == 0)
			{
				v = TWBR_DIFFUSION;goto exit2;
			}

		}
		break;
		case ICAP_SUPPORTEDBARCODETYPES:
		case TWEI_BARCODETYPE:
		{
			if (s.compare(L"TWBT_3OF9") == 0)
			{
				v = TWBT_3OF9;goto exit2;
			}
			if (s.compare(L"TWBT_2OF5INTERLEAVED") == 0)
			{
				v = TWBT_2OF5INTERLEAVED;goto exit2;
			}
			if (s.compare(L"TWBT_2OF5NONINTERLEAVED") == 0)
			{
				v = TWBT_2OF5NONINTERLEAVED;goto exit2;
			}
			if (s.compare(L"TWBT_CODE93") == 0)
			{
				v = TWBT_CODE93;goto exit2;
			}
			if (s.compare(L"TWBT_CODE128") == 0)
			{
				v = TWBT_CODE128;goto exit2;
			}
			if (s.compare(L"TWBT_UCC128") == 0)
			{
				v = TWBT_UCC128;goto exit2;
			}
			if (s.compare(L"TWBT_CODABAR") == 0)
			{
				v = TWBT_CODABAR;goto exit2;
			}
			if (s.compare(L"TWBT_UPCA") == 0)
			{
				v = TWBT_UPCA;goto exit2;
			}
			if (s.compare(L"TWBT_UPCE") == 0)
			{
				v = TWBT_UPCE;goto exit2;
			}
			if (s.compare(L"TWBT_EAN8") == 0)
			{
				v = TWBT_EAN8;goto exit2;
			}
			if (s.compare(L"TWBT_EAN13") == 0)
			{
				v = TWBT_EAN13;goto exit2;
			}
			if (s.compare(L"TWBT_POSTNET") == 0)
			{
				v = TWBT_POSTNET;goto exit2;
			}
			if (s.compare(L"TWBT_PDF417") == 0)
			{
				v = TWBT_PDF417;goto exit2;
			}
			if (s.compare(L"TWBT_2OF5INDUSTRIAL") == 0)
			{
				v = TWBT_2OF5INDUSTRIAL;goto exit2;
			}
			if (s.compare(L"TWBT_2OF5MATRIX") == 0)
			{
				v = TWBT_2OF5MATRIX;goto exit2;
			}
			if (s.compare(L"TWBT_2OF5DATALOGIC") == 0)
			{
				v = TWBT_2OF5DATALOGIC;goto exit2;
			}
			if (s.compare(L"TWBT_2OF5IATA") == 0)
			{
				v = TWBT_2OF5IATA;goto exit2;
			}
			if (s.compare(L"TWBT_3OF9FULLASCII") == 0)
			{
				v = TWBT_3OF9FULLASCII;goto exit2;
			}
			if (s.compare(L"TWBT_CODABARWITHSTARTSTOP") == 0)
			{
				v = TWBT_CODABARWITHSTARTSTOP;goto exit2;
			}
			if (s.compare(L"TWBT_MAXICODE") == 0)
			{
				v = TWBT_MAXICODE;goto exit2;
			}

		}
		break;
		case CAP_CLEARBUFFERS:
		{
			if (s.compare(L"TWCB_AUTO") == 0)
			{
				v = TWCB_AUTO;goto exit2;
			}
			if (s.compare(L"TWCB_CLEAR") == 0)
			{
				v = TWCB_CLEAR;goto exit2;
			}
			if (s.compare(L"TWCB_NOCLEAR") == 0)
			{
				v = TWCB_NOCLEAR;goto exit2;
			}

		}
		break;
		case CAP_DEVICEEVENT:
		{
			if (s.compare(L"TWDE_CUSTOMEVENTS") == 0)
			{
				v = TWDE_CUSTOMEVENTS;goto exit2;
			}
			if (s.compare(L"TWDE_CHECKAUTOMATICCAPTURE") == 0)
			{
				v = TWDE_CHECKAUTOMATICCAPTURE;goto exit2;
			}
			if (s.compare(L"TWDE_CHECKBATTERY") == 0)
			{
				v = TWDE_CHECKBATTERY;goto exit2;
			}
			if (s.compare(L"TWDE_CHECKDEVICEONLINE") == 0)
			{
				v = TWDE_CHECKDEVICEONLINE;goto exit2;
			}
			if (s.compare(L"TWDE_CHECKFLASH") == 0)
			{
				v = TWDE_CHECKFLASH;goto exit2;
			}
			if (s.compare(L"TWDE_CHECKPOWERSUPPLY") == 0)
			{
				v = TWDE_CHECKPOWERSUPPLY;goto exit2;
			}
			if (s.compare(L"TWDE_CHECKRESOLUTION") == 0)
			{
				v = TWDE_CHECKRESOLUTION;goto exit2;
			}
			if (s.compare(L"TWDE_DEVICEADDED") == 0)
			{
				v = TWDE_DEVICEADDED;goto exit2;
			}
			if (s.compare(L"TWDE_DEVICEOFFLINE") == 0)
			{
				v = TWDE_DEVICEOFFLINE;goto exit2;
			}
			if (s.compare(L"TWDE_DEVICEREADY") == 0)
			{
				v = TWDE_DEVICEREADY;goto exit2;
			}
			if (s.compare(L"TWDE_DEVICEREMOVED") == 0)
			{
				v = TWDE_DEVICEREMOVED;goto exit2;
			}
			if (s.compare(L"TWDE_IMAGECAPTURED") == 0)
			{
				v = TWDE_IMAGECAPTURED;goto exit2;
			}
			if (s.compare(L"TWDE_IMAGEDELETED") == 0)
			{
				v = TWDE_IMAGEDELETED;goto exit2;
			}
			if (s.compare(L"TWDE_PAPERDOUBLEFEED") == 0)
			{
				v = TWDE_PAPERDOUBLEFEED;goto exit2;
			}
			if (s.compare(L"TWDE_PAPERJAM") == 0)
			{
				v = TWDE_PAPERJAM;goto exit2;
			}
			if (s.compare(L"TWDE_LAMPFAILURE") == 0)
			{
				v = TWDE_LAMPFAILURE;goto exit2;
			}
			if (s.compare(L"TWDE_POWERSAVE") == 0)
			{
				v = TWDE_POWERSAVE;goto exit2;
			}
			if (s.compare(L"TWDE_POWERSAVENOTIFY") == 0)
			{
				v = TWDE_POWERSAVENOTIFY;goto exit2;
			}

		}
		break;
		case CAP_DUPLEX:
		{
			if (s.compare(L"TWDX_NONE") == 0)
			{
				v = TWDX_NONE;goto exit2;
			}
			if (s.compare(L"TWDX_1PASSDUPLEX") == 0)
			{
				v = TWDX_1PASSDUPLEX;goto exit2;
			}
			if (s.compare(L"TWDX_2PASSDUPLEX") == 0)
			{
				v = TWDX_2PASSDUPLEX;goto exit2;
			}

		}
		break;
		case CAP_FEEDERALIGNMENT:
		{
			if (s.compare(L"TWFA_NONE") == 0)
			{
				v = TWFA_NONE;goto exit2;
			}
			if (s.compare(L"TWFA_LEFT") == 0)
			{
				v = TWFA_LEFT;goto exit2;
			}
			if (s.compare(L"TWFA_CENTER") == 0)
			{
				v = TWFA_CENTER;goto exit2;
			}
			if (s.compare(L"TWFA_RIGHT") == 0)
			{
				v = TWFA_RIGHT;goto exit2;
			}

		}
		break;
		case ICAP_IMAGEFILEFORMAT:
		{
			if (s.compare(L"TWFF_TIFF") == 0)
			{
				v = TWFF_TIFF;goto exit2;
			}
			if (s.compare(L"TWFF_PICT") == 0)
			{
				v = TWFF_PICT;goto exit2;
			}
			if (s.compare(L"TWFF_BMP") == 0)
			{
				v = TWFF_BMP;goto exit2;
			}
			if (s.compare(L"TWFF_XBM") == 0)
			{
				v = TWFF_XBM;goto exit2;
			}
			if (s.compare(L"TWFF_JFIF") == 0)
			{
				v = TWFF_JFIF;goto exit2;
			}
			if (s.compare(L"TWFF_FPX") == 0)
			{
				v = TWFF_FPX;goto exit2;
			}
			if (s.compare(L"TWFF_TIFFMULTI") == 0)
			{
				v = TWFF_TIFFMULTI;goto exit2;
			}
			if (s.compare(L"TWFF_PNG") == 0)
			{
				v = TWFF_PNG;goto exit2;
			}
			if (s.compare(L"TWFF_SPIFF") == 0)
			{
				v = TWFF_SPIFF;goto exit2;
			}
			if (s.compare(L"TWFF_EXIF") == 0)
			{
				v = TWFF_EXIF;goto exit2;
			}
			if (s.compare(L"TWFF_PDF") == 0)
			{
				v = 10;goto exit2;
			}
			if (s.compare(L"TWFF_JP2") == 0)
			{
				v = 11;goto exit2;
			}
			if (s.compare(L"TWFF_JPN") == 0)
			{
				v = 12;goto exit2;
			}
			if (s.compare(L"TWFF_JPX") == 0)
			{
				v = 13;goto exit2;
			}
			if (s.compare(L"TWFF_DEJAVU") == 0)
			{
				v = 14;goto exit2;
			}
			if (s.compare(L"TWFF_PDFA") == 0)
			{
				v = 15;goto exit2;
			}
			if (s.compare(L"TWFF_PDFA2") == 0)
			{
				v = 16;goto exit2;
			}
		}
		break;
		case ICAP_FLASHUSED2:
		{
			if (s.compare(L"TWFL_NONE") == 0)
			{
				v = TWFL_NONE;goto exit2;
			}
			if (s.compare(L"TWFL_OFF") == 0)
			{
				v = TWFL_OFF;goto exit2;
			}
			if (s.compare(L"TWFL_ON") == 0)
			{
				v = TWFL_ON;goto exit2;
			}
			if (s.compare(L"TWFL_AUTO") == 0)
			{
				v = TWFL_AUTO;goto exit2;
			}
			if (s.compare(L"TWFL_REDEYE") == 0)
			{
				v = TWFL_REDEYE;goto exit2;
			}

		}
		break;
		case CAP_FEEDERORDER:
		{
			if (s.compare(L"TWFO_FIRSTPAGEFIRST") == 0)
			{
				v = TWFO_FIRSTPAGEFIRST;goto exit2;
			}
			if (s.compare(L"TWFO_LASTPAGEFIRST") == 0)
			{
				v = TWFO_LASTPAGEFIRST;goto exit2;
			}

		}
		break;
		case ICAP_FLIPROTATION:
		{
			if (s.compare(L"TWFR_BOOK") == 0)
			{
				v = TWFR_BOOK;goto exit2;
			}
			if (s.compare(L"TWFR_FANFOLD") == 0)
			{
				v = TWFR_FANFOLD;goto exit2;
			}

		}
		break;
		case ICAP_FILTER:
		{
			if (s.compare(L"TWFT_RED") == 0)
			{
				v = TWFT_RED;goto exit2;
			}
			if (s.compare(L"TWFT_GREEN") == 0)
			{
				v = TWFT_GREEN;goto exit2;
			}
			if (s.compare(L"TWFT_BLUE") == 0)
			{
				v = TWFT_BLUE;goto exit2;
			}
			if (s.compare(L"TWFT_NONE") == 0)
			{
				v = TWFT_NONE;goto exit2;
			}
			if (s.compare(L"TWFT_WHITE") == 0)
			{
				v = TWFT_WHITE;goto exit2;
			}
			if (s.compare(L"TWFT_CYAN") == 0)
			{
				v = TWFT_CYAN;goto exit2;
			}
			if (s.compare(L"TWFT_MAGENTA") == 0)
			{
				v = TWFT_MAGENTA;goto exit2;
			}
			if (s.compare(L"TWFT_YELLOW") == 0)
			{
				v = TWFT_YELLOW;goto exit2;
			}
			if (s.compare(L"TWFT_BLACK") == 0)
			{
				v = TWFT_BLACK;goto exit2;
			}

		}
		break;
		case ICAP_IMAGEFILTER:
		{
			if (s.compare(L"TWIF_NONE") == 0)
			{
				v = TWIF_NONE;goto exit2;
			}
			if (s.compare(L"TWIF_AUTO") == 0)
			{
				v = TWIF_AUTO;goto exit2;
			}
			if (s.compare(L"TWIF_LOWPASS") == 0)
			{
				v = TWIF_LOWPASS;goto exit2;
			}
			if (s.compare(L"TWIF_BANDPASS") == 0)
			{
				v = TWIF_BANDPASS;goto exit2;
			}
			if (s.compare(L"TWIF_HIGHPASS") == 0)
			{
				v = TWIF_HIGHPASS;goto exit2;
			}
			if (s.compare(L"TWIF_TEXT") == 0)
			{
				v = TWIF_TEXT;goto exit2;
			}
			if (s.compare(L"TWIF_FINELINE") == 0)
			{
				v = TWIF_FINELINE;goto exit2;
			}

		}
		break;
		case CAP_JOBCONTROL:
		{
			if (s.compare(L"TWJC_NONE") == 0)
			{
				v = TWJC_NONE;goto exit2;
			}
			if (s.compare(L"TWJC_JSIC") == 0)
			{
				v = TWJC_JSIC;goto exit2;
			}
			if (s.compare(L"TWJC_JSIS") == 0)
			{
				v = TWJC_JSIS;goto exit2;
			}
			if (s.compare(L"TWJC_JSXC") == 0)
			{
				v = TWJC_JSXC;goto exit2;
			}
			if (s.compare(L"TWJC_JSXS") == 0)
			{
				v = TWJC_JSXS;goto exit2;
			}

		}
		break;
		case ICAP_JPEGQUALITY:
		{
			if (s.compare(L"TWJQ_UNKNOWN") == 0)
			{
				v = TWJQ_UNKNOWN;goto exit2;
			}
			if (s.compare(L"TWJQ_LOW") == 0)
			{
				v = TWJQ_LOW;goto exit2;
			}
			if (s.compare(L"TWJQ_MEDIUM") == 0)
			{
				v = TWJQ_MEDIUM;goto exit2;
			}
			if (s.compare(L"TWJQ_HIGH") == 0)
			{
				v = TWJQ_HIGH;goto exit2;
			}

		}
		break;
		case ICAP_LIGHTPATH:
		{
			if (s.compare(L"TWLP_REFLECTIVE") == 0)
			{
				v = TWLP_REFLECTIVE;goto exit2;
			}
			if (s.compare(L"TWLP_TRANSMISSIVE") == 0)
			{
				v = TWLP_TRANSMISSIVE;goto exit2;
			}

		}
		break;
		case ICAP_LIGHTSOURCE:
		{
			if (s.compare(L"TWLS_RED") == 0)
			{
				v = TWLS_RED;goto exit2;
			}
			if (s.compare(L"TWLS_GREEN") == 0)
			{
				v = TWLS_GREEN;goto exit2;
			}
			if (s.compare(L"TWLS_BLUE") == 0)
			{
				v = TWLS_BLUE;goto exit2;
			}
			if (s.compare(L"TWLS_NONE") == 0)
			{
				v = TWLS_NONE;goto exit2;
			}
			if (s.compare(L"TWLS_WHITE") == 0)
			{
				v = TWLS_WHITE;goto exit2;
			}
			if (s.compare(L"TWLS_UV") == 0)
			{
				v = TWLS_UV;goto exit2;
			}
			if (s.compare(L"TWLS_IR") == 0)
			{
				v = TWLS_IR;goto exit2;
			}

		}
		break;
		case ICAP_NOISEFILTER:
		{
			if (s.compare(L"TWNF_NONE") == 0)
			{
				v = TWNF_NONE;goto exit2;
			}
			if (s.compare(L"TWNF_AUTO") == 0)
			{
				v = TWNF_AUTO;goto exit2;
			}
			if (s.compare(L"TWNF_LONEPIXEL") == 0)
			{
				v = TWNF_LONEPIXEL;goto exit2;
			}
			if (s.compare(L"TWNF_MAJORITYRULE") == 0)
			{
				v = TWNF_MAJORITYRULE;goto exit2;
			}

		}
		break;
		case ICAP_ORIENTATION:
		{
			if (s.compare(L"TWOR_ROT0") == 0)
			{
				v = TWOR_ROT0;goto exit2;
			}
			if (s.compare(L"TWOR_ROT90") == 0)
			{
				v = TWOR_ROT90;goto exit2;
			}
			if (s.compare(L"TWOR_ROT180") == 0)
			{
				v = TWOR_ROT180;goto exit2;
			}
			if (s.compare(L"TWOR_ROT270") == 0)
			{
				v = TWOR_ROT270;goto exit2;
			}
			if (s.compare(L"TWOR_PORTRAIT") == 0)
			{
				v = TWOR_PORTRAIT;goto exit2;
			}
			if (s.compare(L"TWOR_LANDSCAPE") == 0)
			{
				v = TWOR_LANDSCAPE;goto exit2;
			}

		}
		break;
		case ICAP_OVERSCAN:
		{
			if (s.compare(L"TWOV_NONE") == 0)
			{
				v = TWOV_NONE;goto exit2;
			}
			if (s.compare(L"TWOV_AUTO") == 0)
			{
				v = TWOV_AUTO;goto exit2;
			}
			if (s.compare(L"TWOV_TOPBOTTOM") == 0)
			{
				v = TWOV_TOPBOTTOM;goto exit2;
			}
			if (s.compare(L"TWOV_LEFTRIGHT") == 0)
			{
				v = TWOV_LEFTRIGHT;goto exit2;
			}
			if (s.compare(L"TWOV_ALL") == 0)
			{
				v = TWOV_ALL;goto exit2;
			}

		}
		break;
		case ICAP_PLANARCHUNKY:
		{
			if (s.compare(L"TWPC_CHUNKY") == 0)
			{
				v = TWPC_CHUNKY;goto exit2;
			}
			if (s.compare(L"TWPC_PLANAR") == 0)
			{
				v = TWPC_PLANAR;goto exit2;
			}

		}
		break;
		case ICAP_PIXELFLAVOR:
		{
			if (s.compare(L"TWPF_CHOCOLATE") == 0)
			{
				v = TWPF_CHOCOLATE;goto exit2;
			}
			if (s.compare(L"TWPF_VANILLA") == 0)
			{
				v = TWPF_VANILLA;goto exit2;
			}

		}
		break;
		case CAP_PRINTERMODE:
		{
			if (s.compare(L"TWPM_SINGLESTRING") == 0)
			{
				v = TWPM_SINGLESTRING;goto exit2;
			}
			if (s.compare(L"TWPM_MULTISTRING") == 0)
			{
				v = TWPM_MULTISTRING;goto exit2;
			}
			if (s.compare(L"TWPM_COMPOUNDSTRING") == 0)
			{
				v = TWPM_COMPOUNDSTRING;goto exit2;
			}

		}
		break;
		case CAP_PRINTER:
		{
			if (s.compare(L"TWPR_IMPRINTERTOPBEFORE") == 0)
			{
				v = TWPR_IMPRINTERTOPBEFORE;goto exit2;
			}
			if (s.compare(L"TWPR_IMPRINTERTOPAFTER") == 0)
			{
				v = TWPR_IMPRINTERTOPAFTER;goto exit2;
			}
			if (s.compare(L"TWPR_IMPRINTERBOTTOMBEFORE") == 0)
			{
				v = TWPR_IMPRINTERBOTTOMBEFORE;goto exit2;
			}
			if (s.compare(L"TWPR_IMPRINTERBOTTOMAFTER") == 0)
			{
				v = TWPR_IMPRINTERBOTTOMAFTER;goto exit2;
			}
			if (s.compare(L"TWPR_ENDORSERTOPBEFORE") == 0)
			{
				v = TWPR_ENDORSERTOPBEFORE;goto exit2;
			}
			if (s.compare(L"TWPR_ENDORSERTOPAFTER") == 0)
			{
				v = TWPR_ENDORSERTOPAFTER;goto exit2;
			}
			if (s.compare(L"TWPR_ENDORSERBOTTOMBEFORE") == 0)
			{
				v = TWPR_ENDORSERBOTTOMBEFORE;goto exit2;
			}
			if (s.compare(L"TWPR_ENDORSERBOTTOMAFTER") == 0)
			{
				v = TWPR_ENDORSERBOTTOMAFTER;goto exit2;
			}

		}
		break;
		case CAP_POWERSUPPLY:
		{
			if (s.compare(L"TWPS_EXTERNAL") == 0)
			{
				v = TWPS_EXTERNAL;goto exit2;
			}
			if (s.compare(L"TWPS_BATTERY") == 0)
			{
				v = TWPS_BATTERY;goto exit2;
			}

		}
		break;
		case ICAP_PIXELTYPE:
		{
			if (s.compare(L"TWPT_BW") == 0)
			{
				v = TWPT_BW;goto exit2;
			}
			if (s.compare(L"TWPT_GRAY") == 0)
			{
				v = TWPT_GRAY;goto exit2;
			}
			if (s.compare(L"TWPT_RGB") == 0)
			{
				v = TWPT_RGB;goto exit2;
			}
			if (s.compare(L"TWPT_PALETTE") == 0)
			{
				v = TWPT_PALETTE;goto exit2;
			}
			if (s.compare(L"TWPT_CMY") == 0)
			{
				v = TWPT_CMY;goto exit2;
			}
			if (s.compare(L"TWPT_CMYK") == 0)
			{
				v = TWPT_CMYK;goto exit2;
			}
			if (s.compare(L"TWPT_YUV") == 0)
			{
				v = TWPT_YUV;goto exit2;
			}
			if (s.compare(L"TWPT_YUVK") == 0)
			{
				v = TWPT_YUVK;goto exit2;
			}
			if (s.compare(L"TWPT_CIEXYZ") == 0)
			{
				v = TWPT_CIEXYZ;goto exit2;
			}

		}
		break;
		case ICAP_SUPPORTEDSIZES:
		{
			if (s.compare(L"TWSS_NONE") == 0)
			{
				v = TWSS_NONE;goto exit2;
			}
			if (s.compare(L"TWSS_A4") == 0)
			{
				v = TWSS_A4;goto exit2;
			}
			if (s.compare(L"TWSS_JISB5") == 0)
			{
				v = TWSS_JISB5;goto exit2;
			}
			if (s.compare(L"TWSS_USLETTER") == 0)
			{
				v = TWSS_USLETTER;goto exit2;
			}
			if (s.compare(L"TWSS_USLEGAL") == 0)
			{
				v = TWSS_USLEGAL;goto exit2;
			}
			if (s.compare(L"TWSS_A5") == 0)
			{
				v = TWSS_A5;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB4") == 0)
			{
				v = TWSS_ISOB4;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB6") == 0)
			{
				v = TWSS_ISOB6;goto exit2;
			}
			if (s.compare(L"TWSS_USLEDGER") == 0)
			{
				v = TWSS_USLEDGER;goto exit2;
			}
			if (s.compare(L"TWSS_USEXECUTIVE") == 0)
			{
				v = TWSS_USEXECUTIVE;goto exit2;
			}
			if (s.compare(L"TWSS_A3") == 0)
			{
				v = TWSS_A3;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB3") == 0)
			{
				v = TWSS_ISOB3;goto exit2;
			}
			if (s.compare(L"TWSS_A6") == 0)
			{
				v = TWSS_A6;goto exit2;
			}
			if (s.compare(L"TWSS_C4") == 0)
			{
				v = TWSS_C4;goto exit2;
			}
			if (s.compare(L"TWSS_C5") == 0)
			{
				v = TWSS_C5;goto exit2;
			}
			if (s.compare(L"TWSS_C6") == 0)
			{
				v = TWSS_C6;goto exit2;
			}
			if (s.compare(L"TWSS_4A0") == 0)
			{
				v = TWSS_4A0;goto exit2;
			}
			if (s.compare(L"TWSS_2A0") == 0)
			{
				v = TWSS_2A0;goto exit2;
			}
			if (s.compare(L"TWSS_A0") == 0)
			{
				v = TWSS_A0;goto exit2;
			}
			if (s.compare(L"TWSS_A1") == 0)
			{
				v = TWSS_A1;goto exit2;
			}
			if (s.compare(L"TWSS_A2") == 0)
			{
				v = TWSS_A2;goto exit2;
			}
			if (s.compare(L"TWSS_A7") == 0)
			{
				v = TWSS_A7;goto exit2;
			}
			if (s.compare(L"TWSS_A8") == 0)
			{
				v = TWSS_A8;goto exit2;
			}
			if (s.compare(L"TWSS_A9") == 0)
			{
				v = TWSS_A9;goto exit2;
			}
			if (s.compare(L"TWSS_A10") == 0)
			{
				v = TWSS_A10;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB0") == 0)
			{
				v = TWSS_ISOB0;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB1") == 0)
			{
				v = TWSS_ISOB1;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB2") == 0)
			{
				v = TWSS_ISOB2;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB5") == 0)
			{
				v = TWSS_ISOB5;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB7") == 0)
			{
				v = TWSS_ISOB7;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB8") == 0)
			{
				v = TWSS_ISOB8;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB9") == 0)
			{
				v = TWSS_ISOB9;goto exit2;
			}
			if (s.compare(L"TWSS_ISOB10") == 0)
			{
				v = TWSS_ISOB10;goto exit2;
			}
			if (s.compare(L"TWSS_JISB0") == 0)
			{
				v = TWSS_JISB0;goto exit2;
			}
			if (s.compare(L"TWSS_JISB1") == 0)
			{
				v = TWSS_JISB1;goto exit2;
			}
			if (s.compare(L"TWSS_JISB2") == 0)
			{
				v = TWSS_JISB2;goto exit2;
			}
			if (s.compare(L"TWSS_JISB3") == 0)
			{
				v = TWSS_JISB3;goto exit2;
			}
			if (s.compare(L"TWSS_JISB4") == 0)
			{
				v = TWSS_JISB4;goto exit2;
			}
			if (s.compare(L"TWSS_JISB6") == 0)
			{
				v = TWSS_JISB6;goto exit2;
			}
			if (s.compare(L"TWSS_JISB7") == 0)
			{
				v = TWSS_JISB7;goto exit2;
			}
			if (s.compare(L"TWSS_JISB8") == 0)
			{
				v = TWSS_JISB8;goto exit2;
			}
			if (s.compare(L"TWSS_JISB9") == 0)
			{
				v = TWSS_JISB9;goto exit2;
			}
			if (s.compare(L"TWSS_JISB10") == 0)
			{
				v = TWSS_JISB10;goto exit2;
			}
			if (s.compare(L"TWSS_C0") == 0)
			{
				v = TWSS_C0;goto exit2;
			}
			if (s.compare(L"TWSS_C1") == 0)
			{
				v = TWSS_C1;goto exit2;
			}
			if (s.compare(L"TWSS_C2") == 0)
			{
				v = TWSS_C2;goto exit2;
			}
			if (s.compare(L"TWSS_C3") == 0)
			{
				v = TWSS_C3;goto exit2;
			}
			if (s.compare(L"TWSS_C7") == 0)
			{
				v = TWSS_C7;goto exit2;
			}
			if (s.compare(L"TWSS_C8") == 0)
			{
				v = TWSS_C8;goto exit2;
			}
			if (s.compare(L"TWSS_C9") == 0)
			{
				v = TWSS_C9;goto exit2;
			}
			if (s.compare(L"TWSS_C10") == 0)
			{
				v = TWSS_C10;goto exit2;
			}
			if (s.compare(L"TWSS_USSTATEMENT") == 0)
			{
				v = TWSS_USSTATEMENT;goto exit2;
			}
			if (s.compare(L"TWSS_BUSINESSCARD") == 0)
			{
				v = TWSS_BUSINESSCARD;goto exit2;
			}

		}
		break;
		case ICAP_XFERMECH:
		{
			if (s.compare(L"TWSX_NATIVE") == 0)
			{
				v = TWSX_NATIVE;goto exit2;
			}
			if (s.compare(L"TWSX_FILE") == 0)
			{
				v = TWSX_FILE;goto exit2;
			}
			if (s.compare(L"TWSX_MEMORY") == 0)
			{
				v = TWSX_MEMORY;goto exit2;
			}

		}
		break;
		case ICAP_UNITS:
		{
			if (s.compare(L"TWUN_INCHES") == 0)
			{
				v = TWUN_INCHES;goto exit2;
			}
			if (s.compare(L"TWUN_CENTIMETERS") == 0)
			{
				v = TWUN_CENTIMETERS;goto exit2;
			}
			if (s.compare(L"TWUN_PICAS") == 0)
			{
				v = TWUN_PICAS;goto exit2;
			}
			if (s.compare(L"TWUN_POINTS") == 0)
			{
				v = TWUN_POINTS;goto exit2;
			}
			if (s.compare(L"TWUN_TWIPS") == 0)
			{
				v = TWUN_TWIPS;goto exit2;
			}
			if (s.compare(L"TWUN_PIXELS") == 0)
			{
				v = TWUN_PIXELS;goto exit2;
			}

		}
		break;
		}

	exit2:
		json_free(name);
	}

	return v;
}
int getSizeForItemType(TW_UINT16 itemType)
{
	switch(itemType)
	{
  case TWTY_INT8:
			return sizeof(TW_INT8);
			break;
  case TWTY_INT16:
			return sizeof(TW_INT16);
			break;
  case TWTY_INT32:
			return sizeof(TW_INT32);
			break;
  case TWTY_UINT8:
			return sizeof(TW_UINT8);
			break;
  case TWTY_UINT16:
			return sizeof(TW_UINT16);
			break;
  case TWTY_UINT32:
			return sizeof(TW_UINT32);
			break;
  case TWTY_BOOL:
			return sizeof(TW_BOOL);
			break;
  case TWTY_FIX32:
			return sizeof(TW_FIX32);
			break;
  case TWTY_FRAME:
			return sizeof(TW_FRAME);
			break;
  case TWTY_STR32:
			return sizeof(TW_STR32);
			break;
  case TWTY_STR64:
			return sizeof(TW_STR64);
			break;
  case TWTY_STR128:
			return sizeof(TW_STR128);
			break;
  case TWTY_STR255:
			return sizeof(TW_STR255);
			break;
#if USE_TWAIN_DSM
  case TWTY_STR1024:
			return sizeof(TW_STR1024);
			break;
  case TWTY_UNI512:
			return sizeof(TW_UNI512);
			break;
  case TWTY_HANDLE:
			return sizeof(TW_HANDLE);
			break;
#endif
  default:
			break;
	}
	return 0;
}
