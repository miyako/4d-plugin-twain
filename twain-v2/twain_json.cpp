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
		{
			//generic
			switch(conType)
			{
				case TWON_ARRAY:
					string_or_constant_value = FALSE;
					break;
				case TWON_ENUMERATION:
					switch(pENUMERATION->ItemType)
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
					switch(pONEVALUE->ItemType)
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
			break;
	}
	
	if(string_or_constant_value)
	{
		json_set_s(json_scanner_option, str);
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

TW_UINT16 json_get_cap(JSONNODE *n)
{
	TW_UINT16 cap = 0;
	
	json_char *s = json_as_string(n);
	if(s)
	{
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_XFERCOUNT")
		{
			cap = CAP_XFERCOUNT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_COMPRESSION")
		{
			cap = ICAP_COMPRESSION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PIXELTYPE")
		{
			cap = ICAP_PIXELTYPE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_UNITS")
		{
			cap = ICAP_UNITS;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_XFERMECH")
		{
			cap = ICAP_XFERMECH;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_AUTHOR")
		{
			cap = CAP_AUTHOR;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_CAPTION")
		{
			cap = CAP_CAPTION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_FEEDERENABLED")
		{
			cap = CAP_FEEDERENABLED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_FEEDERLOADED")
		{
			cap = CAP_FEEDERLOADED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_TIMEDATE")
		{
			cap = CAP_TIMEDATE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_SUPPORTEDCAPS")
		{
			cap = CAP_SUPPORTEDCAPS;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_EXTENDEDCAPS")
		{
			cap = CAP_EXTENDEDCAPS;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_AUTOFEED")
		{
			cap = CAP_AUTOFEED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_CLEARPAGE")
		{
			cap = CAP_CLEARPAGE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_FEEDPAGE")
		{
			cap = CAP_FEEDPAGE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_REWINDPAGE")
		{
			cap = CAP_REWINDPAGE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_INDICATORS")
		{
			cap = CAP_INDICATORS;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_SUPPORTEDCAPSEXT")
		{
			cap = CAP_SUPPORTEDCAPSEXT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_PAPERDETECTABLE")
		{
			cap = CAP_PAPERDETECTABLE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_UICONTROLLABLE")
		{
			cap = CAP_UICONTROLLABLE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_DEVICEONLINE")
		{
			cap = CAP_DEVICEONLINE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_AUTOSCAN")
		{
			cap = CAP_AUTOSCAN;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_THUMBNAILSENABLED")
		{
			cap = CAP_THUMBNAILSENABLED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_DUPLEX")
		{
			cap = CAP_DUPLEX;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_DUPLEXENABLED")
		{
			cap = CAP_DUPLEXENABLED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_ENABLEDSUIONLY")
		{
			cap = CAP_ENABLEDSUIONLY;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_CUSTOMDSDATA")
		{
			cap = CAP_CUSTOMDSDATA;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_ENDORSER")
		{
			cap = CAP_ENDORSER;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_JOBCONTROL")
		{
			cap = CAP_JOBCONTROL;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_ALARMS")
		{
			cap = CAP_ALARMS;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_ALARMVOLUME")
		{
			cap = CAP_ALARMVOLUME;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_AUTOMATICCAPTURE")
		{
			cap = CAP_AUTOMATICCAPTURE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_TIMEBEFOREFIRSTCAPTURE")
		{
			cap = CAP_TIMEBEFOREFIRSTCAPTURE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_TIMEBETWEENCAPTURES")
		{
			cap = CAP_TIMEBETWEENCAPTURES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_CLEARBUFFERS")
		{
			cap = CAP_CLEARBUFFERS;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_MAXBATCHBUFFERS")
		{
			cap = CAP_MAXBATCHBUFFERS;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_DEVICETIMEDATE")
		{
			cap = CAP_DEVICETIMEDATE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_POWERSUPPLY")
		{
			cap = CAP_POWERSUPPLY;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_CAMERAPREVIEWUI")
		{
			cap = CAP_CAMERAPREVIEWUI;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_DEVICEEVENT")
		{
			cap = CAP_DEVICEEVENT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_SERIALNUMBER")
		{
			cap = CAP_SERIALNUMBER;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_PRINTER")
		{
			cap = CAP_PRINTER;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_PRINTERENABLED")
		{
			cap = CAP_PRINTERENABLED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_PRINTERINDEX")
		{
			cap = CAP_PRINTERINDEX;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_PRINTERMODE")
		{
			cap = CAP_PRINTERMODE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_PRINTERSTRING")
		{
			cap = CAP_PRINTERSTRING;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_PRINTERSUFFIX")
		{
			cap = CAP_PRINTERSUFFIX;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_LANGUAGE")
		{
			cap = CAP_LANGUAGE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_FEEDERALIGNMENT")
		{
			cap = CAP_FEEDERALIGNMENT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_FEEDERORDER")
		{
			cap = CAP_FEEDERORDER;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_REACQUIREALLOWED")
		{
			cap = CAP_REACQUIREALLOWED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_BATTERYMINUTES")
		{
			cap = CAP_BATTERYMINUTES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"CAP_BATTERYPERCENTAGE")
		{
			cap = CAP_BATTERYPERCENTAGE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_AUTOBRIGHT")
		{
			cap = ICAP_AUTOBRIGHT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BRIGHTNESS")
		{
			cap = ICAP_BRIGHTNESS;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_CONTRAST")
		{
			cap = ICAP_CONTRAST;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_CUSTHALFTONE")
		{
			cap = ICAP_CUSTHALFTONE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_EXPOSURETIME")
		{
			cap = ICAP_EXPOSURETIME;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_FILTER")
		{
			cap = ICAP_FILTER;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_FLASHUSED")
		{
			cap = ICAP_FLASHUSED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_GAMMA")
		{
			cap = ICAP_GAMMA;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_HALFTONES")
		{
			cap = ICAP_HALFTONES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_HIGHLIGHT")
		{
			cap = ICAP_HIGHLIGHT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_IMAGEFILEFORMAT")
		{
			cap = ICAP_IMAGEFILEFORMAT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_LAMPSTATE")
		{
			cap = ICAP_LAMPSTATE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_LIGHTSOURCE")
		{
			cap = ICAP_LIGHTSOURCE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_ORIENTATION")
		{
			cap = ICAP_ORIENTATION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PHYSICALWIDTH")
		{
			cap = ICAP_PHYSICALWIDTH;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PHYSICALHEIGHT")
		{
			cap = ICAP_PHYSICALHEIGHT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_SHADOW")
		{
			cap = ICAP_SHADOW;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_FRAMES")
		{
			cap = ICAP_FRAMES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_XNATIVERESOLUTION")
		{
			cap = ICAP_XNATIVERESOLUTION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_YNATIVERESOLUTION")
		{
			cap = ICAP_YNATIVERESOLUTION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_XRESOLUTION")
		{
			cap = ICAP_XRESOLUTION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_YRESOLUTION")
		{
			cap = ICAP_YRESOLUTION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_MAXFRAMES")
		{
			cap = ICAP_MAXFRAMES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_TILES")
		{
			cap = ICAP_TILES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BITORDER")
		{
			cap = ICAP_BITORDER;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_CCITTKFACTOR")
		{
			cap = ICAP_CCITTKFACTOR;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_LIGHTPATH")
		{
			cap = ICAP_LIGHTPATH;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PIXELFLAVOR")
		{
			cap = ICAP_PIXELFLAVOR;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PLANARCHUNKY")
		{
			cap = ICAP_PLANARCHUNKY;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_ROTATION")
		{
			cap = ICAP_ROTATION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_SUPPORTEDSIZES")
		{
			cap = ICAP_SUPPORTEDSIZES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_THRESHOLD")
		{
			cap = ICAP_THRESHOLD;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_XSCALING")
		{
			cap = ICAP_XSCALING;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_YSCALING")
		{
			cap = ICAP_YSCALING;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BITORDERCODES")
		{
			cap = ICAP_BITORDERCODES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PIXELFLAVORCODES")
		{
			cap = ICAP_PIXELFLAVORCODES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_JPEGPIXELTYPE")
		{
			cap = ICAP_JPEGPIXELTYPE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_TIMEFILL")
		{
			cap = ICAP_TIMEFILL;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BITDEPTH")
		{
			cap = ICAP_BITDEPTH;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BITDEPTHREDUCTION")
		{
			cap = ICAP_BITDEPTHREDUCTION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_UNDEFINEDIMAGESIZE")
		{
			cap = ICAP_UNDEFINEDIMAGESIZE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_IMAGEDATASET")
		{
			cap = ICAP_IMAGEDATASET;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_EXTIMAGEINFO")
		{
			cap = ICAP_EXTIMAGEINFO;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_MINIMUMHEIGHT")
		{
			cap = ICAP_MINIMUMHEIGHT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_MINIMUMWIDTH")
		{
			cap = ICAP_MINIMUMWIDTH;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_FLIPROTATION")
		{
			cap = ICAP_FLIPROTATION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BARCODEDETECTIONENABLED")
		{
			cap = ICAP_BARCODEDETECTIONENABLED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_SUPPORTEDBARCODETYPES")
		{
			cap = ICAP_SUPPORTEDBARCODETYPES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BARCODEMAXSEARCHPRIORITIES")
		{
			cap = ICAP_BARCODEMAXSEARCHPRIORITIES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BARCODESEARCHPRIORITIES")
		{
			cap = ICAP_BARCODESEARCHPRIORITIES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BARCODESEARCHMODE")
		{
			cap = ICAP_BARCODESEARCHMODE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BARCODEMAXRETRIES")
		{
			cap = ICAP_BARCODEMAXRETRIES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_BARCODETIMEOUT")
		{
			cap = ICAP_BARCODETIMEOUT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_ZOOMFACTOR")
		{
			cap = ICAP_ZOOMFACTOR;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PATCHCODEDETECTIONENABLED")
		{
			cap = ICAP_PATCHCODEDETECTIONENABLED;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_SUPPORTEDPATCHCODETYPES")
		{
			cap = ICAP_SUPPORTEDPATCHCODETYPES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PATCHCODEMAXSEARCHPRIORITIES")
		{
			cap = ICAP_PATCHCODEMAXSEARCHPRIORITIES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PATCHCODESEARCHPRIORITIES")
		{
			cap = ICAP_PATCHCODESEARCHPRIORITIES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PATCHCODESEARCHMODE")
		{
			cap = ICAP_PATCHCODESEARCHMODE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PATCHCODEMAXRETRIES")
		{
			cap = ICAP_PATCHCODEMAXRETRIES;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_PATCHCODETIMEOUT")
		{
			cap = ICAP_PATCHCODETIMEOUT;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_FLASHUSED2")
		{
			cap = ICAP_FLASHUSED2;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_IMAGEFILTER")
		{
			cap = ICAP_IMAGEFILTER;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_NOISEFILTER")
		{
			cap = ICAP_NOISEFILTER;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_OVERSCAN")
		{
			cap = ICAP_OVERSCAN;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_AUTOMATICBORDERDETECTION")
		{
			cap = ICAP_AUTOMATICBORDERDETECTION;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_AUTOMATICDESKEW")
		{
			cap = ICAP_AUTOMATICDESKEW;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_AUTOMATICROTATE")
		{
			cap = ICAP_AUTOMATICROTATE;goto exit;
		}
		if (std::wstring((const wchar_t *)s) == (const wchar_t *)"ICAP_JPEGQUALITY")
		{
			cap = ICAP_JPEGQUALITY;goto exit;
		}
		
		json_free(s);
	}
	
exit:
	return cap;
}

int json_get_cap_constant(JSONNODE *n, TW_UINT16 cap)
{
	int v = 0;
	
	json_char *s = json_as_string(n);
	if(s)
	{
		switch(cap)
		{
				//convert to constant
#if USE_TWAIN_DSM
			case ICAP_AUTOSIZE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAS_NONE")
				{
					v = TWAS_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAS_AUTO")
				{
					v = TWAS_AUTO;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAS_CURRENT")
				{
					v = TWAS_CURRENT;
				}
				
			}
				break;
			case ICAP_AUTODISCARDBLANKPAGES:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBP_DISABLE")
				{
					v = TWBP_DISABLE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBP_AUTO")
				{
					v = TWBP_AUTO;
				}
				
			}
				break;
			case CAP_CAMERASIDE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCS_BOTH")
				{
					v = TWCS_BOTH;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCS_TOP")
				{
					v = TWCS_TOP;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCS_BOTTOM")
				{
					v = TWCS_BOTTOM;
				}
				
			}
				break;
			case ICAP_FEEDERTYPE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFE_GENERAL")
				{
					v = TWFE_GENERAL;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFE_PHOTO")
				{
					v = TWFE_PHOTO;
				}
				
			}
				break;
			case CAP_FEEDERPOCKET:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKETERROR")
				{
					v = TWFP_POCKETERROR;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET1")
				{
					v = TWFP_POCKET1;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET2")
				{
					v = TWFP_POCKET2;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET3")
				{
					v = TWFP_POCKET3;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET4")
				{
					v = TWFP_POCKET4;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET5")
				{
					v = TWFP_POCKET5;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET6")
				{
					v = TWFP_POCKET6;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET7")
				{
					v = TWFP_POCKET7;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET8")
				{
					v = TWFP_POCKET8;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET9")
				{
					v = TWFP_POCKET9;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET10")
				{
					v = TWFP_POCKET10;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET11")
				{
					v = TWFP_POCKET11;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET12")
				{
					v = TWFP_POCKET12;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET13")
				{
					v = TWFP_POCKET13;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET14")
				{
					v = TWFP_POCKET14;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET15")
				{
					v = TWFP_POCKET15;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFP_POCKET16")
				{
					v = TWFP_POCKET16;
				}
				
			}
				break;
			case ICAP_ICCPROFILE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIC_NONE")
				{
					v = TWIC_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIC_LINK")
				{
					v = TWIC_LINK;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIC_EMBED")
				{
					v = TWIC_EMBED;
				}
				
			}
				break;
			case ICAP_IMAGEMERGE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIM_NONE")
				{
					v = TWIM_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIM_FRONTONTOP")
				{
					v = TWIM_FRONTONTOP;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIM_FRONTONBOTTOM")
				{
					v = TWIM_FRONTONBOTTOM;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIM_FRONTONLEFT")
				{
					v = TWIM_FRONTONLEFT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIM_FRONTONRIGHT")
				{
					v = TWIM_FRONTONRIGHT;
				}
				
			}
				break;
			case CAP_SEGMENTED:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSG_NONE")
				{
					v = TWSG_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSG_AUTO")
				{
					v = TWSG_AUTO;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSG_MANUAL")
				{
					v = TWSG_MANUAL;
				}
				
			}
				break;
#endif
			case CAP_ALARMS:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_ALARM")
				{
					v = TWAL_ALARM;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_FEEDERERROR")
				{
					v = TWAL_FEEDERERROR;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_FEEDERWARNING")
				{
					v = TWAL_FEEDERWARNING;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_BARCODE")
				{
					v = TWAL_BARCODE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_DOUBLEFEED")
				{
					v = TWAL_DOUBLEFEED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_JAM")
				{
					v = TWAL_JAM;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_PATCHCODE")
				{
					v = TWAL_PATCHCODE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_POWER")
				{
					v = TWAL_POWER;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWAL_SKEW")
				{
					v = TWAL_SKEW;
				}
				
			}
				break;
			case ICAP_COMPRESSION:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_NONE")
				{
					v = TWCP_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_PACKBITS")
				{
					v = TWCP_PACKBITS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_GROUP31D")
				{
					v = TWCP_GROUP31D;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_GROUP31DEOL")
				{
					v = TWCP_GROUP31DEOL;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_GROUP32D")
				{
					v = TWCP_GROUP32D;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_GROUP4")
				{
					v = TWCP_GROUP4;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_JPEG")
				{
					v = TWCP_JPEG;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_LZW")
				{
					v = TWCP_LZW;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_JBIG")
				{
					v = TWCP_JBIG;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_PNG")
				{
					v = TWCP_PNG;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_RLE4")
				{
					v = TWCP_RLE4;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_RLE8")
				{
					v = TWCP_RLE8;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_BITFIELDS")
				{
					v = TWCP_BITFIELDS;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_ZIP")
				//			{
				//				v = TWCP_ZIP;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCP_JPEG2000")
				//			{
				//				v = TWCP_JPEG2000;
				//			}
				
			}
				break;
			case ICAP_BARCODESEARCHMODE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBD_HORZ")
				{
					v = TWBD_HORZ;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBD_VERT")
				{
					v = TWBD_VERT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBD_HORZVERT")
				{
					v = TWBD_HORZVERT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBD_VERTHORZ")
				{
					v = TWBD_VERTHORZ;
				}
				
			}
				break;
			case ICAP_BITORDER:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBO_LSBFIRST")
				{
					v = TWBO_LSBFIRST;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBO_MSBFIRST")
				{
					v = TWBO_MSBFIRST;
				}
				
			}
				break;
			case ICAP_BITDEPTHREDUCTION:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBR_THRESHOLD")
				{
					v = TWBR_THRESHOLD;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBR_HALFTONE")
				{
					v = TWBR_HALFTONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBR_CUSTHALFTONE")
				{
					v = TWBR_CUSTHALFTONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBR_DIFFUSION")
				{
					v = TWBR_DIFFUSION;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBR_DYNAMICTHRESHOLD")
				//			{
				//				v = TWBR_DYNAMICTHRESHOLD;
				//			}
				
			}
				break;
			case ICAP_SUPPORTEDBARCODETYPES:
			case TWEI_BARCODETYPE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_3OF9")
				{
					v = TWBT_3OF9;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_2OF5INTERLEAVED")
				{
					v = TWBT_2OF5INTERLEAVED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_2OF5NONINTERLEAVED")
				{
					v = TWBT_2OF5NONINTERLEAVED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_CODE93")
				{
					v = TWBT_CODE93;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_CODE128")
				{
					v = TWBT_CODE128;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_UCC128")
				{
					v = TWBT_UCC128;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_CODABAR")
				{
					v = TWBT_CODABAR;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_UPCA")
				{
					v = TWBT_UPCA;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_UPCE")
				{
					v = TWBT_UPCE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_EAN8")
				{
					v = TWBT_EAN8;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_EAN13")
				{
					v = TWBT_EAN13;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_POSTNET")
				{
					v = TWBT_POSTNET;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_PDF417")
				{
					v = TWBT_PDF417;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_2OF5INDUSTRIAL")
				{
					v = TWBT_2OF5INDUSTRIAL;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_2OF5MATRIX")
				{
					v = TWBT_2OF5MATRIX;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_2OF5DATALOGIC")
				{
					v = TWBT_2OF5DATALOGIC;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_2OF5IATA")
				{
					v = TWBT_2OF5IATA;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_3OF9FULLASCII")
				{
					v = TWBT_3OF9FULLASCII;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_CODABARWITHSTARTSTOP")
				{
					v = TWBT_CODABARWITHSTARTSTOP;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_MAXICODE")
				{
					v = TWBT_MAXICODE;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWBT_QRCODE")
				//			{
				//				v = TWBT_QRCODE;
				//			}
				
			}
				break;
			case CAP_CLEARBUFFERS:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCB_AUTO")
				{
					v = TWCB_AUTO;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCB_CLEAR")
				{
					v = TWCB_CLEAR;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWCB_NOCLEAR")
				{
					v = TWCB_NOCLEAR;
				}
				
			}
				break;
			case CAP_DEVICEEVENT:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_CUSTOMEVENTS")
				{
					v = TWDE_CUSTOMEVENTS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_CHECKAUTOMATICCAPTURE")
				{
					v = TWDE_CHECKAUTOMATICCAPTURE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_CHECKBATTERY")
				{
					v = TWDE_CHECKBATTERY;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_CHECKDEVICEONLINE")
				{
					v = TWDE_CHECKDEVICEONLINE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_CHECKFLASH")
				{
					v = TWDE_CHECKFLASH;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_CHECKPOWERSUPPLY")
				{
					v = TWDE_CHECKPOWERSUPPLY;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_CHECKRESOLUTION")
				{
					v = TWDE_CHECKRESOLUTION;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_DEVICEADDED")
				{
					v = TWDE_DEVICEADDED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_DEVICEOFFLINE")
				{
					v = TWDE_DEVICEOFFLINE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_DEVICEREADY")
				{
					v = TWDE_DEVICEREADY;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_DEVICEREMOVED")
				{
					v = TWDE_DEVICEREMOVED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_IMAGECAPTURED")
				{
					v = TWDE_IMAGECAPTURED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_IMAGEDELETED")
				{
					v = TWDE_IMAGEDELETED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_PAPERDOUBLEFEED")
				{
					v = TWDE_PAPERDOUBLEFEED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_PAPERJAM")
				{
					v = TWDE_PAPERJAM;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_LAMPFAILURE")
				{
					v = TWDE_LAMPFAILURE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_POWERSAVE")
				{
					v = TWDE_POWERSAVE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDE_POWERSAVENOTIFY")
				{
					v = TWDE_POWERSAVENOTIFY;
				}
				
			}
				break;
			case CAP_DUPLEX:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDX_NONE")
				{
					v = TWDX_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDX_1PASSDUPLEX")
				{
					v = TWDX_1PASSDUPLEX;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWDX_2PASSDUPLEX")
				{
					v = TWDX_2PASSDUPLEX;
				}
				
			}
				break;
			case CAP_FEEDERALIGNMENT:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFA_NONE")
				{
					v = TWFA_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFA_LEFT")
				{
					v = TWFA_LEFT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFA_CENTER")
				{
					v = TWFA_CENTER;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFA_RIGHT")
				{
					v = TWFA_RIGHT;
				}
				
			}
				break;
			case ICAP_IMAGEFILEFORMAT:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_TIFF")
				{
					v = TWFF_TIFF;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_PICT")
				{
					v = TWFF_PICT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_BMP")
				{
					v = TWFF_BMP;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_XBM")
				{
					v = TWFF_XBM;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_JFIF")
				{
					v = TWFF_JFIF;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_FPX")
				{
					v = TWFF_FPX;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_TIFFMULTI")
				{
					v = TWFF_TIFFMULTI;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_PNG")
				{
					v = TWFF_PNG;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_SPIFF")
				{
					v = TWFF_SPIFF;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_EXIF")
				{
					v = TWFF_EXIF;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_PDF")
				//			{
				//				v = TWFF_PDF;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_JP2")
				//			{
				//				v = TWFF_JP2;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_JPX")
				//			{
				//				v = TWFF_JPX;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_DEJAVU")
				//			{
				//				v = TWFF_DEJAVU;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_PDFA")
				//			{
				//				v = TWFF_PDFA;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFF_PDFA2")
				//			{
				//				v = TWFF_PDFA2;
				//			}
				
			}
				break;
			case ICAP_FLASHUSED2:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFL_NONE")
				{
					v = TWFL_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFL_OFF")
				{
					v = TWFL_OFF;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFL_ON")
				{
					v = TWFL_ON;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFL_AUTO")
				{
					v = TWFL_AUTO;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFL_REDEYE")
				{
					v = TWFL_REDEYE;
				}
				
			}
				break;
			case CAP_FEEDERORDER:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFO_FIRSTPAGEFIRST")
				{
					v = TWFO_FIRSTPAGEFIRST;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFO_LASTPAGEFIRST")
				{
					v = TWFO_LASTPAGEFIRST;
				}
				
			}
				break;
			case ICAP_FLIPROTATION:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFR_BOOK")
				{
					v = TWFR_BOOK;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFR_FANFOLD")
				{
					v = TWFR_FANFOLD;
				}
				
			}
				break;
			case ICAP_FILTER:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_RED")
				{
					v = TWFT_RED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_GREEN")
				{
					v = TWFT_GREEN;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_BLUE")
				{
					v = TWFT_BLUE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_NONE")
				{
					v = TWFT_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_WHITE")
				{
					v = TWFT_WHITE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_CYAN")
				{
					v = TWFT_CYAN;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_MAGENTA")
				{
					v = TWFT_MAGENTA;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_YELLOW")
				{
					v = TWFT_YELLOW;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWFT_BLACK")
				{
					v = TWFT_BLACK;
				}
				
			}
				break;
			case ICAP_IMAGEFILTER:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIF_NONE")
				{
					v = TWIF_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIF_AUTO")
				{
					v = TWIF_AUTO;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIF_LOWPASS")
				{
					v = TWIF_LOWPASS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIF_BANDPASS")
				{
					v = TWIF_BANDPASS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIF_HIGHPASS")
				{
					v = TWIF_HIGHPASS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIF_TEXT")
				{
					v = TWIF_TEXT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWIF_FINELINE")
				{
					v = TWIF_FINELINE;
				}
				
			}
				break;
			case CAP_JOBCONTROL:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJC_NONE")
				{
					v = TWJC_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJC_JSIC")
				{
					v = TWJC_JSIC;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJC_JSIS")
				{
					v = TWJC_JSIS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJC_JSXC")
				{
					v = TWJC_JSXC;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJC_JSXS")
				{
					v = TWJC_JSXS;
				}
				
			}
				break;
			case ICAP_JPEGQUALITY:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJQ_UNKNOWN")
				{
					v = TWJQ_UNKNOWN;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJQ_LOW")
				{
					v = TWJQ_LOW;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJQ_MEDIUM")
				{
					v = TWJQ_MEDIUM;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWJQ_HIGH")
				{
					v = TWJQ_HIGH;
				}
				
			}
				break;
			case ICAP_LIGHTPATH:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLP_REFLECTIVE")
				{
					v = TWLP_REFLECTIVE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLP_TRANSMISSIVE")
				{
					v = TWLP_TRANSMISSIVE;
				}
				
			}
				break;
			case ICAP_LIGHTSOURCE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLS_RED")
				{
					v = TWLS_RED;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLS_GREEN")
				{
					v = TWLS_GREEN;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLS_BLUE")
				{
					v = TWLS_BLUE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLS_NONE")
				{
					v = TWLS_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLS_WHITE")
				{
					v = TWLS_WHITE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLS_UV")
				{
					v = TWLS_UV;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWLS_IR")
				{
					v = TWLS_IR;
				}
				
			}
				break;
			case ICAP_NOISEFILTER:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWNF_NONE")
				{
					v = TWNF_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWNF_AUTO")
				{
					v = TWNF_AUTO;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWNF_LONEPIXEL")
				{
					v = TWNF_LONEPIXEL;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWNF_MAJORITYRULE")
				{
					v = TWNF_MAJORITYRULE;
				}
				
			}
				break;
			case ICAP_ORIENTATION:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_ROT0")
				{
					v = TWOR_ROT0;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_ROT90")
				{
					v = TWOR_ROT90;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_ROT180")
				{
					v = TWOR_ROT180;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_ROT270")
				{
					v = TWOR_ROT270;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_PORTRAIT")
				{
					v = TWOR_PORTRAIT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_LANDSCAPE")
				{
					v = TWOR_LANDSCAPE;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_AUTO")
				//			{
				//				v = TWOR_AUTO;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_AUTOTEXT")
				//			{
				//				v = TWOR_AUTOTEXT;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOR_AUTOPICTURE")
				//			{
				//				v = TWOR_AUTOPICTURE;
				//			}
				
			}
				break;
			case ICAP_OVERSCAN:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOV_NONE")
				{
					v = TWOV_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOV_AUTO")
				{
					v = TWOV_AUTO;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOV_TOPBOTTOM")
				{
					v = TWOV_TOPBOTTOM;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOV_LEFTRIGHT")
				{
					v = TWOV_LEFTRIGHT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWOV_ALL")
				{
					v = TWOV_ALL;
				}
				
			}
				break;
			case ICAP_PLANARCHUNKY:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPC_CHUNKY")
				{
					v = TWPC_CHUNKY;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPC_PLANAR")
				{
					v = TWPC_PLANAR;
				}
				
			}
				break;
			case ICAP_PIXELFLAVOR:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPF_CHOCOLATE")
				{
					v = TWPF_CHOCOLATE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPF_VANILLA")
				{
					v = TWPF_VANILLA;
				}
				
			}
				break;
			case CAP_PRINTERMODE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPM_SINGLESTRING")
				{
					v = TWPM_SINGLESTRING;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPM_MULTISTRING")
				{
					v = TWPM_MULTISTRING;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPM_COMPOUNDSTRING")
				{
					v = TWPM_COMPOUNDSTRING;
				}
				
			}
				break;
			case CAP_PRINTER:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPR_IMPRINTERTOPBEFORE")
				{
					v = TWPR_IMPRINTERTOPBEFORE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPR_IMPRINTERTOPAFTER")
				{
					v = TWPR_IMPRINTERTOPAFTER;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPR_IMPRINTERBOTTOMBEFORE")
				{
					v = TWPR_IMPRINTERBOTTOMBEFORE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPR_IMPRINTERBOTTOMAFTER")
				{
					v = TWPR_IMPRINTERBOTTOMAFTER;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPR_ENDORSERTOPBEFORE")
				{
					v = TWPR_ENDORSERTOPBEFORE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPR_ENDORSERTOPAFTER")
				{
					v = TWPR_ENDORSERTOPAFTER;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPR_ENDORSERBOTTOMBEFORE")
				{
					v = TWPR_ENDORSERBOTTOMBEFORE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPR_ENDORSERBOTTOMAFTER")
				{
					v = TWPR_ENDORSERBOTTOMAFTER;
				}
				
			}
				break;
			case CAP_POWERSUPPLY:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPS_EXTERNAL")
				{
					v = TWPS_EXTERNAL;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPS_BATTERY")
				{
					v = TWPS_BATTERY;
				}
				
			}
				break;
			case ICAP_PIXELTYPE:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_BW")
				{
					v = TWPT_BW;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_GRAY")
				{
					v = TWPT_GRAY;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_RGB")
				{
					v = TWPT_RGB;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_PALETTE")
				{
					v = TWPT_PALETTE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_CMY")
				{
					v = TWPT_CMY;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_CMYK")
				{
					v = TWPT_CMYK;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_YUV")
				{
					v = TWPT_YUV;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_YUVK")
				{
					v = TWPT_YUVK;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_CIEXYZ")
				{
					v = TWPT_CIEXYZ;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_LAB")
				//			{
				//				v = TWPT_LAB;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_SRGB")
				//			{
				//				v = TWPT_SRGB;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_SCRGB")
				//			{
				//				v = TWPT_SCRGB;
				//			}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWPT_INFRARED")
				//			{
				//				v = TWPT_INFRARED;
				//			}
				
			}
				break;
			case ICAP_SUPPORTEDSIZES:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_NONE")
				{
					v = TWSS_NONE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A4")
				{
					v = TWSS_A4;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB5")
				{
					v = TWSS_JISB5;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_USLETTER")
				{
					v = TWSS_USLETTER;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_USLEGAL")
				{
					v = TWSS_USLEGAL;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A5")
				{
					v = TWSS_A5;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB4")
				{
					v = TWSS_ISOB4;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB6")
				{
					v = TWSS_ISOB6;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_USLEDGER")
				{
					v = TWSS_USLEDGER;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_USEXECUTIVE")
				{
					v = TWSS_USEXECUTIVE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A3")
				{
					v = TWSS_A3;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB3")
				{
					v = TWSS_ISOB3;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A6")
				{
					v = TWSS_A6;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C4")
				{
					v = TWSS_C4;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C5")
				{
					v = TWSS_C5;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C6")
				{
					v = TWSS_C6;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_4A0")
				{
					v = TWSS_4A0;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_2A0")
				{
					v = TWSS_2A0;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A0")
				{
					v = TWSS_A0;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A1")
				{
					v = TWSS_A1;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A2")
				{
					v = TWSS_A2;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A7")
				{
					v = TWSS_A7;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A8")
				{
					v = TWSS_A8;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A9")
				{
					v = TWSS_A9;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_A10")
				{
					v = TWSS_A10;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB0")
				{
					v = TWSS_ISOB0;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB1")
				{
					v = TWSS_ISOB1;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB2")
				{
					v = TWSS_ISOB2;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB5")
				{
					v = TWSS_ISOB5;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB7")
				{
					v = TWSS_ISOB7;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB8")
				{
					v = TWSS_ISOB8;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB9")
				{
					v = TWSS_ISOB9;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_ISOB10")
				{
					v = TWSS_ISOB10;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB0")
				{
					v = TWSS_JISB0;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB1")
				{
					v = TWSS_JISB1;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB2")
				{
					v = TWSS_JISB2;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB3")
				{
					v = TWSS_JISB3;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB4")
				{
					v = TWSS_JISB4;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB6")
				{
					v = TWSS_JISB6;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB7")
				{
					v = TWSS_JISB7;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB8")
				{
					v = TWSS_JISB8;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB9")
				{
					v = TWSS_JISB9;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_JISB10")
				{
					v = TWSS_JISB10;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C0")
				{
					v = TWSS_C0;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C1")
				{
					v = TWSS_C1;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C2")
				{
					v = TWSS_C2;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C3")
				{
					v = TWSS_C3;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C7")
				{
					v = TWSS_C7;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C8")
				{
					v = TWSS_C8;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C9")
				{
					v = TWSS_C9;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_C10")
				{
					v = TWSS_C10;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_USSTATEMENT")
				{
					v = TWSS_USSTATEMENT;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_BUSINESSCARD")
				{
					v = TWSS_BUSINESSCARD;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSS_MAXSIZE")
				//			{
				//				v = TWSS_MAXSIZE;
				//			}
				
			}
				break;
			case ICAP_XFERMECH:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSX_NATIVE")
				{
					v = TWSX_NATIVE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSX_FILE")
				{
					v = TWSX_FILE;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSX_MEMORY")
				{
					v = TWSX_MEMORY;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWSX_MEMFILE")
				//			{
				//				v = TWSX_MEMFILE;
				//			}
				
			}
				break;
			case ICAP_UNITS:
			{
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWUN_INCHES")
				{
					v = TWUN_INCHES;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWUN_CENTIMETERS")
				{
					v = TWUN_CENTIMETERS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWUN_PICAS")
				{
					v = TWUN_PICAS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWUN_POINTS")
				{
					v = TWUN_POINTS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWUN_TWIPS")
				{
					v = TWUN_TWIPS;
				}
				if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWUN_PIXELS")
				{
					v = TWUN_PIXELS;
				}
				//			if (std::wstring((const wchar_t *)s) == (const wchar_t *)"TWUN_MILLIMETERS")
				//			{
				//				v = TWUN_MILLIMETERS;
				//			}
				
			}
				break;
		}
		json_free(s);
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
