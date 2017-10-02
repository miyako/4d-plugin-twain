#include "twain_methods.h"

void setCapabilityValueString(TW_CAPABILITY *tw_capability, void *p, C_TEXT& value)
{
	TW_UINT16 cap = tw_capability->Cap;
	TW_UINT16 conType = tw_capability->ConType;
	
	pTW_ENUMERATION pENUMERATION = (pTW_ENUMERATION)p;
	pTW_ONEVALUE pONEVALUE = (pTW_ONEVALUE)p;
	pTW_RANGE pRANGE = (pTW_RANGE)p;
	
	//buffer holding string representation
	char str[CAP_VALUE_BUF_SIZE];
	memset(str, 0, sizeof(str));
	
	CUTF8String u8value;
	value.copyUTF8String(&u8value);
	memcpy(str, u8value.c_str(), u8value.length());
	
	int i_value = atoi(str);
	double f_value = atof(str);
	
	std::string option = str;
	
	TW_BOOL b_value = FALSE;
	
	if((option.length() == 4) && (0 == strncmp("true", str, 4)))
		b_value = TRUE;
	
	if((option.length() == 4) && (0 == strncmp("vrai", str, 4)))
		b_value = TRUE;
	
	if((option.length() == 1) && (0 == strncmp("1", str, 1)))
		b_value = TRUE;
	
	if((option.length() == 5) && (0 == strncmp("false", str, 5)))
		b_value = FALSE;

	if((option.length()== 4) && (0 == strncmp("faux", str, 4)))
		b_value = FALSE;
	
	if((option.length() == 1) && (0 == strncmp("0", str, 1)))
		b_value = FALSE;
	
	TW_FIX32 tw_fix32;
	
	//constant matching
	switch(cap)
	{
			//convert to constant
#if USE_TWAIN_DSM
		case ICAP_AUTOSIZE:
		{
			if (option == (const char *)"TWAS_NONE")
			{
				i_value = TWAS_NONE;
			}
			if (option == (const char *)"TWAS_AUTO")
			{
				i_value = TWAS_AUTO;
			}
			if (option == (const char *)"TWAS_CURRENT")
			{
				i_value = TWAS_CURRENT;
			} 

		}
			break;
		case ICAP_AUTODISCARDBLANKPAGES:
		{
			if (option == (const char *)"TWBP_DISABLE")
			{
				i_value = TWBP_DISABLE;
			}
			if (option == (const char *)"TWBP_AUTO")
			{
				i_value = TWBP_AUTO;
			} 

		}
			break;
		case CAP_CAMERASIDE:
		{
			if (option == (const char *)"TWCS_BOTH")
			{
				i_value = TWCS_BOTH;
			}
			if (option == (const char *)"TWCS_TOP")
			{
				i_value = TWCS_TOP;
			}
			if (option == (const char *)"TWCS_BOTTOM")
			{
				i_value = TWCS_BOTTOM;
			} 

		}
			break;
		case ICAP_FEEDERTYPE:
		{
			if (option == (const char *)"TWFE_GENERAL")
			{
				i_value = TWFE_GENERAL;
			}
			if (option == (const char *)"TWFE_PHOTO")
			{
				i_value = TWFE_PHOTO;
			} 

		}
			break;
		case CAP_FEEDERPOCKET:
		{
			if (option == (const char *)"TWFP_POCKETERROR")
			{
				i_value = TWFP_POCKETERROR;
			}
			if (option == (const char *)"TWFP_POCKET1")
			{
				i_value = TWFP_POCKET1;
			}
			if (option == (const char *)"TWFP_POCKET2")
			{
				i_value = TWFP_POCKET2;
			}
			if (option == (const char *)"TWFP_POCKET3")
			{
				i_value = TWFP_POCKET3;
			}
			if (option == (const char *)"TWFP_POCKET4")
			{
				i_value = TWFP_POCKET4;
			}
			if (option == (const char *)"TWFP_POCKET5")
			{
				i_value = TWFP_POCKET5;
			}
			if (option == (const char *)"TWFP_POCKET6")
			{
				i_value = TWFP_POCKET6;
			}
			if (option == (const char *)"TWFP_POCKET7")
			{
				i_value = TWFP_POCKET7;
			}
			if (option == (const char *)"TWFP_POCKET8")
			{
				i_value = TWFP_POCKET8;
			}
			if (option == (const char *)"TWFP_POCKET9")
			{
				i_value = TWFP_POCKET9;
			}
			if (option == (const char *)"TWFP_POCKET10")
			{
				i_value = TWFP_POCKET10;
			}
			if (option == (const char *)"TWFP_POCKET11")
			{
				i_value = TWFP_POCKET11;
			}
			if (option == (const char *)"TWFP_POCKET12")
			{
				i_value = TWFP_POCKET12;
			}
			if (option == (const char *)"TWFP_POCKET13")
			{
				i_value = TWFP_POCKET13;
			}
			if (option == (const char *)"TWFP_POCKET14")
			{
				i_value = TWFP_POCKET14;
			} 
			if (option == (const char *)"TWFP_POCKET15")
			{
				i_value = TWFP_POCKET15;
			} 
			if (option == (const char *)"TWFP_POCKET16")
			{
				i_value = TWFP_POCKET16;
			} 

		}
			break;
		case ICAP_ICCPROFILE:
		{
			if (option == (const char *)"TWIC_NONE")
			{
				i_value = TWIC_NONE;
			}
			if (option == (const char *)"TWIC_LINK")
			{
				i_value = TWIC_LINK;
			}
			if (option == (const char *)"TWIC_EMBED")
			{
				i_value = TWIC_EMBED;
			} 

		}
			break;
		case ICAP_IMAGEMERGE:
		{
			if (option == (const char *)"TWIM_NONE")
			{
				i_value = TWIM_NONE;
			}
			if (option == (const char *)"TWIM_FRONTONTOP")
			{
				i_value = TWIM_FRONTONTOP;
			}
			if (option == (const char *)"TWIM_FRONTONBOTTOM")
			{
				i_value = TWIM_FRONTONBOTTOM;
			}
			if (option == (const char *)"TWIM_FRONTONLEFT")
			{
				i_value = TWIM_FRONTONLEFT;
			}
			if (option == (const char *)"TWIM_FRONTONRIGHT")
			{
				i_value = TWIM_FRONTONRIGHT;
			} 

		}
			break;
		case CAP_SEGMENTED:
		{
			if (option == (const char *)"TWSG_NONE")
			{
				i_value = TWSG_NONE;
			}
			if (option == (const char *)"TWSG_AUTO")
			{
				i_value = TWSG_AUTO;
			}
			if (option == (const char *)"TWSG_MANUAL")
			{
				i_value = TWSG_MANUAL;
			} 

		}
			break;
#endif
		case CAP_ALARMS:
		{
			if (option == (const char *)"TWAL_ALARM")
			{
				i_value = TWAL_ALARM;
			}
			if (option == (const char *)"TWAL_FEEDERERROR")
			{
				i_value = TWAL_FEEDERERROR;
			}
			if (option == (const char *)"TWAL_FEEDERWARNING")
			{
				i_value = TWAL_FEEDERWARNING;
			}
			if (option == (const char *)"TWAL_BARCODE")
			{
				i_value = TWAL_BARCODE;
			}
			if (option == (const char *)"TWAL_DOUBLEFEED")
			{
				i_value = TWAL_DOUBLEFEED;
			}
			if (option == (const char *)"TWAL_JAM")
			{
				i_value = TWAL_JAM;
			}
			if (option == (const char *)"TWAL_PATCHCODE")
			{
				i_value = TWAL_PATCHCODE;
			}
			if (option == (const char *)"TWAL_POWER")
			{
				i_value = TWAL_POWER;
			} 
			if (option == (const char *)"TWAL_SKEW")
			{
				i_value = TWAL_SKEW;
			} 

		}
			break;
		case ICAP_COMPRESSION:
		{
			if (option == (const char *)"TWCP_NONE")
			{
				i_value = TWCP_NONE;
			}
			if (option == (const char *)"TWCP_PACKBITS")
			{
				i_value = TWCP_PACKBITS;
			}
			if (option == (const char *)"TWCP_GROUP31D")
			{
				i_value = TWCP_GROUP31D;
			}
			if (option == (const char *)"TWCP_GROUP31DEOL")
			{
				i_value = TWCP_GROUP31DEOL;
			}
			if (option == (const char *)"TWCP_GROUP32D")
			{
				i_value = TWCP_GROUP32D;
			}
			if (option == (const char *)"TWCP_GROUP4")
			{
				i_value = TWCP_GROUP4;
			}
			if (option == (const char *)"TWCP_JPEG")
			{
				i_value = TWCP_JPEG;
			}
			if (option == (const char *)"TWCP_LZW")
			{
				i_value = TWCP_LZW;
			}
			if (option == (const char *)"TWCP_JBIG")
			{
				i_value = TWCP_JBIG;
			}
			if (option == (const char *)"TWCP_PNG")
			{
				i_value = TWCP_PNG;
			}
			if (option == (const char *)"TWCP_RLE4")
			{
				i_value = TWCP_RLE4;
			}
			if (option == (const char *)"TWCP_RLE8")
			{
				i_value = TWCP_RLE8;
			}
			if (option == (const char *)"TWCP_BITFIELDS")
			{
				i_value = TWCP_BITFIELDS;
			} 
//			if (option == (const char *)"TWCP_ZIP")
//			{
//				i_value = TWCP_ZIP;
//			} 
//			if (option == (const char *)"TWCP_JPEG2000")
//			{
//				i_value = TWCP_JPEG2000;
//			} 

		}
			break;
		case ICAP_BARCODESEARCHMODE:
		{
			if (option == (const char *)"TWBD_HORZ")
			{
				i_value = TWBD_HORZ;
			}
			if (option == (const char *)"TWBD_VERT")
			{
				i_value = TWBD_VERT;
			}
			if (option == (const char *)"TWBD_HORZVERT")
			{
				i_value = TWBD_HORZVERT;
			}
			if (option == (const char *)"TWBD_VERTHORZ")
			{
				i_value = TWBD_VERTHORZ;
			} 

		}
			break;
		case ICAP_BITORDER:
		{
			if (option == (const char *)"TWBO_LSBFIRST")
			{
				i_value = TWBO_LSBFIRST;
			}
			if (option == (const char *)"TWBO_MSBFIRST")
			{
				i_value = TWBO_MSBFIRST;
			} 

		}
			break;
		case ICAP_BITDEPTHREDUCTION:
		{
			if (option == (const char *)"TWBR_THRESHOLD")
			{
				i_value = TWBR_THRESHOLD;
			}
			if (option == (const char *)"TWBR_HALFTONE")
			{
				i_value = TWBR_HALFTONE;
			}
			if (option == (const char *)"TWBR_CUSTHALFTONE")
			{
				i_value = TWBR_CUSTHALFTONE;
			}
			if (option == (const char *)"TWBR_DIFFUSION")
			{
				i_value = TWBR_DIFFUSION;
			}
//			if (option == (const char *)"TWBR_DYNAMICTHRESHOLD")
//			{
//				i_value = TWBR_DYNAMICTHRESHOLD;
//			} 

		}
			break;
		case ICAP_SUPPORTEDBARCODETYPES:
		case TWEI_BARCODETYPE:
		{
			if (option == (const char *)"TWBT_3OF9")
			{
				i_value = TWBT_3OF9;
			}
			if (option == (const char *)"TWBT_2OF5INTERLEAVED")
			{
				i_value = TWBT_2OF5INTERLEAVED;
			}
			if (option == (const char *)"TWBT_2OF5NONINTERLEAVED")
			{
				i_value = TWBT_2OF5NONINTERLEAVED;
			}
			if (option == (const char *)"TWBT_CODE93")
			{
				i_value = TWBT_CODE93;
			}
			if (option == (const char *)"TWBT_CODE128")
			{
				i_value = TWBT_CODE128;
			}
			if (option == (const char *)"TWBT_UCC128")
			{
				i_value = TWBT_UCC128;
			}
			if (option == (const char *)"TWBT_CODABAR")
			{
				i_value = TWBT_CODABAR;
			}
			if (option == (const char *)"TWBT_UPCA")
			{
				i_value = TWBT_UPCA;
			}
			if (option == (const char *)"TWBT_UPCE")
			{
				i_value = TWBT_UPCE;
			}
			if (option == (const char *)"TWBT_EAN8")
			{
				i_value = TWBT_EAN8;
			}
			if (option == (const char *)"TWBT_EAN13")
			{
				i_value = TWBT_EAN13;
			}
			if (option == (const char *)"TWBT_POSTNET")
			{
				i_value = TWBT_POSTNET;
			}
			if (option == (const char *)"TWBT_PDF417")
			{
				i_value = TWBT_PDF417;
			}
			if (option == (const char *)"TWBT_2OF5INDUSTRIAL")
			{
				i_value = TWBT_2OF5INDUSTRIAL;
			}
			if (option == (const char *)"TWBT_2OF5MATRIX")
			{
				i_value = TWBT_2OF5MATRIX;
			}
			if (option == (const char *)"TWBT_2OF5DATALOGIC")
			{
				i_value = TWBT_2OF5DATALOGIC;
			}
			if (option == (const char *)"TWBT_2OF5IATA")
			{
				i_value = TWBT_2OF5IATA;
			}
			if (option == (const char *)"TWBT_3OF9FULLASCII")
			{
				i_value = TWBT_3OF9FULLASCII;
			}
			if (option == (const char *)"TWBT_CODABARWITHSTARTSTOP")
			{
				i_value = TWBT_CODABARWITHSTARTSTOP;
			} 
			if (option == (const char *)"TWBT_MAXICODE")
			{
				i_value = TWBT_MAXICODE;
			} 
//			if (option == (const char *)"TWBT_QRCODE")
//			{
//				i_value = TWBT_QRCODE;
//			} 

		}
			break;
		case CAP_CLEARBUFFERS:
		{
			if (option == (const char *)"TWCB_AUTO")
			{
				i_value = TWCB_AUTO;
			}
			if (option == (const char *)"TWCB_CLEAR")
			{
				i_value = TWCB_CLEAR;
			}
			if (option == (const char *)"TWCB_NOCLEAR")
			{
				i_value = TWCB_NOCLEAR;
			} 

		}
			break;
		case CAP_DEVICEEVENT:
		{
			if (option == (const char *)"TWDE_CUSTOMEVENTS")
			{
				i_value = TWDE_CUSTOMEVENTS;
			}
			if (option == (const char *)"TWDE_CHECKAUTOMATICCAPTURE")
			{
				i_value = TWDE_CHECKAUTOMATICCAPTURE;
			}
			if (option == (const char *)"TWDE_CHECKBATTERY")
			{
				i_value = TWDE_CHECKBATTERY;
			}
			if (option == (const char *)"TWDE_CHECKDEVICEONLINE")
			{
				i_value = TWDE_CHECKDEVICEONLINE;
			}
			if (option == (const char *)"TWDE_CHECKFLASH")
			{
				i_value = TWDE_CHECKFLASH;
			}
			if (option == (const char *)"TWDE_CHECKPOWERSUPPLY")
			{
				i_value = TWDE_CHECKPOWERSUPPLY;
			}
			if (option == (const char *)"TWDE_CHECKRESOLUTION")
			{
				i_value = TWDE_CHECKRESOLUTION;
			}
			if (option == (const char *)"TWDE_DEVICEADDED")
			{
				i_value = TWDE_DEVICEADDED;
			}
			if (option == (const char *)"TWDE_DEVICEOFFLINE")
			{
				i_value = TWDE_DEVICEOFFLINE;
			}
			if (option == (const char *)"TWDE_DEVICEREADY")
			{
				i_value = TWDE_DEVICEREADY;
			}
			if (option == (const char *)"TWDE_DEVICEREMOVED")
			{
				i_value = TWDE_DEVICEREMOVED;
			}
			if (option == (const char *)"TWDE_IMAGECAPTURED")
			{
				i_value = TWDE_IMAGECAPTURED;
			}
			if (option == (const char *)"TWDE_IMAGEDELETED")
			{
				i_value = TWDE_IMAGEDELETED;
			}
			if (option == (const char *)"TWDE_PAPERDOUBLEFEED")
			{
				i_value = TWDE_PAPERDOUBLEFEED;
			}
			if (option == (const char *)"TWDE_PAPERJAM")
			{
				i_value = TWDE_PAPERJAM;
			}
			if (option == (const char *)"TWDE_LAMPFAILURE")
			{
				i_value = TWDE_LAMPFAILURE;
			} 
			if (option == (const char *)"TWDE_POWERSAVE")
			{
				i_value = TWDE_POWERSAVE;
			} 
			if (option == (const char *)"TWDE_POWERSAVENOTIFY")
			{
				i_value = TWDE_POWERSAVENOTIFY;
			} 

		}
			break;
		case CAP_DUPLEX:
		{
			if (option == (const char *)"TWDX_NONE")
			{
				i_value = TWDX_NONE;
			}
			if (option == (const char *)"TWDX_1PASSDUPLEX")
			{
				i_value = TWDX_1PASSDUPLEX;
			}
			if (option == (const char *)"TWDX_2PASSDUPLEX")
			{
				i_value = TWDX_2PASSDUPLEX;
			} 

		}
			break;
		case CAP_FEEDERALIGNMENT:
		{
			if (option == (const char *)"TWFA_NONE")
			{
				i_value = TWFA_NONE;
			}
			if (option == (const char *)"TWFA_LEFT")
			{
				i_value = TWFA_LEFT;
			}
			if (option == (const char *)"TWFA_CENTER")
			{
				i_value = TWFA_CENTER;
			}
			if (option == (const char *)"TWFA_RIGHT")
			{
				i_value = TWFA_RIGHT;
			} 

		}
			break;
		case ICAP_IMAGEFILEFORMAT:
		{
			if (option == (const char *)"TWFF_TIFF")
			{
				i_value = TWFF_TIFF;
			}
			if (option == (const char *)"TWFF_PICT")
			{
				i_value = TWFF_PICT;
			}
			if (option == (const char *)"TWFF_BMP")
			{
				i_value = TWFF_BMP;
			}
			if (option == (const char *)"TWFF_XBM")
			{
				i_value = TWFF_XBM;
			}
			if (option == (const char *)"TWFF_JFIF")
			{
				i_value = TWFF_JFIF;
			}
			if (option == (const char *)"TWFF_FPX")
			{
				i_value = TWFF_FPX;
			}
			if (option == (const char *)"TWFF_TIFFMULTI")
			{
				i_value = TWFF_TIFFMULTI;
			}
			if (option == (const char *)"TWFF_PNG")
			{
				i_value = TWFF_PNG;
			}
			if (option == (const char *)"TWFF_SPIFF")
			{
				i_value = TWFF_SPIFF;
			}
			if (option == (const char *)"TWFF_EXIF")
			{
				i_value = TWFF_EXIF;
			}
//			if (option == (const char *)"TWFF_PDF")
//			{
//				i_value = TWFF_PDF;
//			}
//			if (option == (const char *)"TWFF_JP2")
//			{
//				i_value = TWFF_JP2;
//			}
//			if (option == (const char *)"TWFF_JPX")
//			{
//				i_value = TWFF_JPX;
//			}
//			if (option == (const char *)"TWFF_DEJAVU")
//			{
//				i_value = TWFF_DEJAVU;
//			} 
//			if (option == (const char *)"TWFF_PDFA")
//			{
//				i_value = TWFF_PDFA;
//			} 
//			if (option == (const char *)"TWFF_PDFA2")
//			{
//				i_value = TWFF_PDFA2;
//			} 

		}
			break;
		case ICAP_FLASHUSED2:
		{
			if (option == (const char *)"TWFL_NONE")
			{
				i_value = TWFL_NONE;
			}
			if (option == (const char *)"TWFL_OFF")
			{
				i_value = TWFL_OFF;
			}
			if (option == (const char *)"TWFL_ON")
			{
				i_value = TWFL_ON;
			}
			if (option == (const char *)"TWFL_AUTO")
			{
				i_value = TWFL_AUTO;
			}
			if (option == (const char *)"TWFL_REDEYE")
			{
				i_value = TWFL_REDEYE;
			} 

		}
			break;
		case CAP_FEEDERORDER:
		{
			if (option == (const char *)"TWFO_FIRSTPAGEFIRST")
			{
				i_value = TWFO_FIRSTPAGEFIRST;
			}
			if (option == (const char *)"TWFO_LASTPAGEFIRST")
			{
				i_value = TWFO_LASTPAGEFIRST;
			} 

		}
			break;
		case ICAP_FLIPROTATION:
		{
			if (option == (const char *)"TWFR_BOOK")
			{
				i_value = TWFR_BOOK;
			}
			if (option == (const char *)"TWFR_FANFOLD")
			{
				i_value = TWFR_FANFOLD;
			} 

		}
			break;
		case ICAP_FILTER:
		{
			if (option == (const char *)"TWFT_RED")
			{
				i_value = TWFT_RED;
			}
			if (option == (const char *)"TWFT_GREEN")
			{
				i_value = TWFT_GREEN;
			}
			if (option == (const char *)"TWFT_BLUE")
			{
				i_value = TWFT_BLUE;
			}
			if (option == (const char *)"TWFT_NONE")
			{
				i_value = TWFT_NONE;
			}
			if (option == (const char *)"TWFT_WHITE")
			{
				i_value = TWFT_WHITE;
			}
			if (option == (const char *)"TWFT_CYAN")
			{
				i_value = TWFT_CYAN;
			}
			if (option == (const char *)"TWFT_MAGENTA")
			{
				i_value = TWFT_MAGENTA;
			}
			if (option == (const char *)"TWFT_YELLOW")
			{
				i_value = TWFT_YELLOW;
			} 
			if (option == (const char *)"TWFT_BLACK")
			{
				i_value = TWFT_BLACK;
			} 

		}
			break;
		case ICAP_IMAGEFILTER:
		{
			if (option == (const char *)"TWIF_NONE")
			{
				i_value = TWIF_NONE;
			}
			if (option == (const char *)"TWIF_AUTO")
			{
				i_value = TWIF_AUTO;
			}
			if (option == (const char *)"TWIF_LOWPASS")
			{
				i_value = TWIF_LOWPASS;
			}
			if (option == (const char *)"TWIF_BANDPASS")
			{
				i_value = TWIF_BANDPASS;
			}
			if (option == (const char *)"TWIF_HIGHPASS")
			{
				i_value = TWIF_HIGHPASS;
			}
			if (option == (const char *)"TWIF_TEXT")
			{
				i_value = TWIF_TEXT;
			}
			if (option == (const char *)"TWIF_FINELINE")
			{
				i_value = TWIF_FINELINE;
			} 

		}
			break;
		case CAP_JOBCONTROL:
		{
			if (option == (const char *)"TWJC_NONE")
			{
				i_value = TWJC_NONE;
			}
			if (option == (const char *)"TWJC_JSIC")
			{
				i_value = TWJC_JSIC;
			}
			if (option == (const char *)"TWJC_JSIS")
			{
				i_value = TWJC_JSIS;
			}
			if (option == (const char *)"TWJC_JSXC")
			{
				i_value = TWJC_JSXC;
			}
			if (option == (const char *)"TWJC_JSXS")
			{
				i_value = TWJC_JSXS;
			} 

		}
			break;
		case ICAP_JPEGQUALITY:
		{
			if (option == (const char *)"TWJQ_UNKNOWN")
			{
				i_value = TWJQ_UNKNOWN;
			}
			if (option == (const char *)"TWJQ_LOW")
			{
				i_value = TWJQ_LOW;
			}
			if (option == (const char *)"TWJQ_MEDIUM")
			{
				i_value = TWJQ_MEDIUM;
			}
			if (option == (const char *)"TWJQ_HIGH")
			{
				i_value = TWJQ_HIGH;
			} 

		}
			break;
		case ICAP_LIGHTPATH:
		{
			if (option == (const char *)"TWLP_REFLECTIVE")
			{
				i_value = TWLP_REFLECTIVE;
			}
			if (option == (const char *)"TWLP_TRANSMISSIVE")
			{
				i_value = TWLP_TRANSMISSIVE;
			} 

		}
			break;
		case ICAP_LIGHTSOURCE:
		{
			if (option == (const char *)"TWLS_RED")
			{
				i_value = TWLS_RED;
			}
			if (option == (const char *)"TWLS_GREEN")
			{
				i_value = TWLS_GREEN;
			}
			if (option == (const char *)"TWLS_BLUE")
			{
				i_value = TWLS_BLUE;
			}
			if (option == (const char *)"TWLS_NONE")
			{
				i_value = TWLS_NONE;
			}
			if (option == (const char *)"TWLS_WHITE")
			{
				i_value = TWLS_WHITE;
			}
			if (option == (const char *)"TWLS_UV")
			{
				i_value = TWLS_UV;
			} 
			if (option == (const char *)"TWLS_IR")
			{
				i_value = TWLS_IR;
			} 

		}
			break;
		case ICAP_NOISEFILTER:
		{
			if (option == (const char *)"TWNF_NONE")
			{
				i_value = TWNF_NONE;
			}
			if (option == (const char *)"TWNF_AUTO")
			{
				i_value = TWNF_AUTO;
			}
			if (option == (const char *)"TWNF_LONEPIXEL")
			{
				i_value = TWNF_LONEPIXEL;
			}
			if (option == (const char *)"TWNF_MAJORITYRULE")
			{
				i_value = TWNF_MAJORITYRULE;
			} 

		}
			break;
		case ICAP_ORIENTATION:
		{
			if (option == (const char *)"TWOR_ROT0")
			{
				i_value = TWOR_ROT0;
			}
			if (option == (const char *)"TWOR_ROT90")
			{
				i_value = TWOR_ROT90;
			}
			if (option == (const char *)"TWOR_ROT180")
			{
				i_value = TWOR_ROT180;
			}
			if (option == (const char *)"TWOR_ROT270")
			{
				i_value = TWOR_ROT270;
			}
			if (option == (const char *)"TWOR_PORTRAIT")
			{
				i_value = TWOR_PORTRAIT;
			}
			if (option == (const char *)"TWOR_LANDSCAPE")
			{
				i_value = TWOR_LANDSCAPE;
			}
//			if (option == (const char *)"TWOR_AUTO")
//			{
//				i_value = TWOR_AUTO;
//			}
//			if (option == (const char *)"TWOR_AUTOTEXT")
//			{
//				i_value = TWOR_AUTOTEXT;
//			} 
//			if (option == (const char *)"TWOR_AUTOPICTURE")
//			{
//				i_value = TWOR_AUTOPICTURE;
//			} 

		}
			break;
		case ICAP_OVERSCAN:
		{
			if (option == (const char *)"TWOV_NONE")
			{
				i_value = TWOV_NONE;
			}
			if (option == (const char *)"TWOV_AUTO")
			{
				i_value = TWOV_AUTO;
			}
			if (option == (const char *)"TWOV_TOPBOTTOM")
			{
				i_value = TWOV_TOPBOTTOM;
			}
			if (option == (const char *)"TWOV_LEFTRIGHT")
			{
				i_value = TWOV_LEFTRIGHT;
			}
			if (option == (const char *)"TWOV_ALL")
			{
				i_value = TWOV_ALL;
			} 

		}
			break;
		case ICAP_PLANARCHUNKY:
		{
			if (option == (const char *)"TWPC_CHUNKY")
			{
				i_value = TWPC_CHUNKY;
			}
			if (option == (const char *)"TWPC_PLANAR")
			{
				i_value = TWPC_PLANAR;
			} 

		}
			break;
		case ICAP_PIXELFLAVOR:
		{
			if (option == (const char *)"TWPF_CHOCOLATE")
			{
				i_value = TWPF_CHOCOLATE;
			}
			if (option == (const char *)"TWPF_VANILLA")
			{
				i_value = TWPF_VANILLA;
			} 

		}
			break;
		case CAP_PRINTERMODE:
		{
			if (option == (const char *)"TWPM_SINGLESTRING")
			{
				i_value = TWPM_SINGLESTRING;
			}
			if (option == (const char *)"TWPM_MULTISTRING")
			{
				i_value = TWPM_MULTISTRING;
			}
			if (option == (const char *)"TWPM_COMPOUNDSTRING")
			{
				i_value = TWPM_COMPOUNDSTRING;
			} 

		}
			break;
		case CAP_PRINTER:
		{
			if (option == (const char *)"TWPR_IMPRINTERTOPBEFORE")
			{
				i_value = TWPR_IMPRINTERTOPBEFORE;
			}
			if (option == (const char *)"TWPR_IMPRINTERTOPAFTER")
			{
				i_value = TWPR_IMPRINTERTOPAFTER;
			}
			if (option == (const char *)"TWPR_IMPRINTERBOTTOMBEFORE")
			{
				i_value = TWPR_IMPRINTERBOTTOMBEFORE;
			}
			if (option == (const char *)"TWPR_IMPRINTERBOTTOMAFTER")
			{
				i_value = TWPR_IMPRINTERBOTTOMAFTER;
			}
			if (option == (const char *)"TWPR_ENDORSERTOPBEFORE")
			{
				i_value = TWPR_ENDORSERTOPBEFORE;
			}
			if (option == (const char *)"TWPR_ENDORSERTOPAFTER")
			{
				i_value = TWPR_ENDORSERTOPAFTER;
			}
			if (option == (const char *)"TWPR_ENDORSERBOTTOMBEFORE")
			{
				i_value = TWPR_ENDORSERBOTTOMBEFORE;
			}
			if (option == (const char *)"TWPR_ENDORSERBOTTOMAFTER")
			{
				i_value = TWPR_ENDORSERBOTTOMAFTER;
			} 

		}
			break;
		case CAP_POWERSUPPLY:
		{
			if (option == (const char *)"TWPS_EXTERNAL")
			{
				i_value = TWPS_EXTERNAL;
			}
			if (option == (const char *)"TWPS_BATTERY")
			{
				i_value = TWPS_BATTERY;
			} 

		}
			break;
		case ICAP_PIXELTYPE:
		{
			if (option == (const char *)"TWPT_BW")
			{
				i_value = TWPT_BW;
			}
			if (option == (const char *)"TWPT_GRAY")
			{
				i_value = TWPT_GRAY;
			}
			if (option == (const char *)"TWPT_RGB")
			{
				i_value = TWPT_RGB;
			}
			if (option == (const char *)"TWPT_PALETTE")
			{
				i_value = TWPT_PALETTE;
			}
			if (option == (const char *)"TWPT_CMY")
			{
				i_value = TWPT_CMY;
			}
			if (option == (const char *)"TWPT_CMYK")
			{
				i_value = TWPT_CMYK;
			}
			if (option == (const char *)"TWPT_YUV")
			{
				i_value = TWPT_YUV;
			}
			if (option == (const char *)"TWPT_YUVK")
			{
				i_value = TWPT_YUVK;
			}
			if (option == (const char *)"TWPT_CIEXYZ")
			{
				i_value = TWPT_CIEXYZ;
			}
//			if (option == (const char *)"TWPT_LAB")
//			{
//				i_value = TWPT_LAB;
//			}
//			if (option == (const char *)"TWPT_SRGB")
//			{
//				i_value = TWPT_SRGB;
//			}
//			if (option == (const char *)"TWPT_SCRGB")
//			{
//				i_value = TWPT_SCRGB;
//			} 
//			if (option == (const char *)"TWPT_INFRARED")
//			{
//				i_value = TWPT_INFRARED;
//			} 

		}
			break;
		case ICAP_SUPPORTEDSIZES:
		{
			if (option == (const char *)"TWSS_NONE")
			{
				i_value = TWSS_NONE;
			}
			if (option == (const char *)"TWSS_A4")
			{
				i_value = TWSS_A4;
			}
			if (option == (const char *)"TWSS_JISB5")
			{
				i_value = TWSS_JISB5;
			}
			if (option == (const char *)"TWSS_USLETTER")
			{
				i_value = TWSS_USLETTER;
			}
			if (option == (const char *)"TWSS_USLEGAL")
			{
				i_value = TWSS_USLEGAL;
			}
			if (option == (const char *)"TWSS_A5")
			{
				i_value = TWSS_A5;
			}
			if (option == (const char *)"TWSS_ISOB4")
			{
				i_value = TWSS_ISOB4;
			}
			if (option == (const char *)"TWSS_ISOB6")
			{
				i_value = TWSS_ISOB6;
			}
			if (option == (const char *)"TWSS_USLEDGER")
			{
				i_value = TWSS_USLEDGER;
			}
			if (option == (const char *)"TWSS_USEXECUTIVE")
			{
				i_value = TWSS_USEXECUTIVE;
			}
			if (option == (const char *)"TWSS_A3")
			{
				i_value = TWSS_A3;
			}
			if (option == (const char *)"TWSS_ISOB3")
			{
				i_value = TWSS_ISOB3;
			}
			if (option == (const char *)"TWSS_A6")
			{
				i_value = TWSS_A6;
			}
			if (option == (const char *)"TWSS_C4")
			{
				i_value = TWSS_C4;
			}
			if (option == (const char *)"TWSS_C5")
			{
				i_value = TWSS_C5;
			}
			if (option == (const char *)"TWSS_C6")
			{
				i_value = TWSS_C6;
			}
			if (option == (const char *)"TWSS_4A0")
			{
				i_value = TWSS_4A0;
			}
			if (option == (const char *)"TWSS_2A0")
			{
				i_value = TWSS_2A0;
			}
			if (option == (const char *)"TWSS_A0")
			{
				i_value = TWSS_A0;
			}
			if (option == (const char *)"TWSS_A1")
			{
				i_value = TWSS_A1;
			}
			if (option == (const char *)"TWSS_A2")
			{
				i_value = TWSS_A2;
			}
			if (option == (const char *)"TWSS_A7")
			{
				i_value = TWSS_A7;
			}
			if (option == (const char *)"TWSS_A8")
			{
				i_value = TWSS_A8;
			}
			if (option == (const char *)"TWSS_A9")
			{
				i_value = TWSS_A9;
			}
			if (option == (const char *)"TWSS_A10")
			{
				i_value = TWSS_A10;
			}
			if (option == (const char *)"TWSS_ISOB0")
			{
				i_value = TWSS_ISOB0;
			}
			if (option == (const char *)"TWSS_ISOB1")
			{
				i_value = TWSS_ISOB1;
			}
			if (option == (const char *)"TWSS_ISOB2")
			{
				i_value = TWSS_ISOB2;
			}
			if (option == (const char *)"TWSS_ISOB5")
			{
				i_value = TWSS_ISOB5;
			}
			if (option == (const char *)"TWSS_ISOB7")
			{
				i_value = TWSS_ISOB7;
			}
			if (option == (const char *)"TWSS_ISOB8")
			{
				i_value = TWSS_ISOB8;
			}
			if (option == (const char *)"TWSS_ISOB9")
			{
				i_value = TWSS_ISOB9;
			}
			if (option == (const char *)"TWSS_ISOB10")
			{
				i_value = TWSS_ISOB10;
			}
			if (option == (const char *)"TWSS_JISB0")
			{
				i_value = TWSS_JISB0;
			}
			if (option == (const char *)"TWSS_JISB1")
			{
				i_value = TWSS_JISB1;
			}
			if (option == (const char *)"TWSS_JISB2")
			{
				i_value = TWSS_JISB2;
			}
			if (option == (const char *)"TWSS_JISB3")
			{
				i_value = TWSS_JISB3;
			}
			if (option == (const char *)"TWSS_JISB4")
			{
				i_value = TWSS_JISB4;
			}
			if (option == (const char *)"TWSS_JISB6")
			{
				i_value = TWSS_JISB6;
			}
			if (option == (const char *)"TWSS_JISB7")
			{
				i_value = TWSS_JISB7;
			}
			if (option == (const char *)"TWSS_JISB8")
			{
				i_value = TWSS_JISB8;
			}
			if (option == (const char *)"TWSS_JISB9")
			{
				i_value = TWSS_JISB9;
			}
			if (option == (const char *)"TWSS_JISB10")
			{
				i_value = TWSS_JISB10;
			}
			if (option == (const char *)"TWSS_C0")
			{
				i_value = TWSS_C0;
			}
			if (option == (const char *)"TWSS_C1")
			{
				i_value = TWSS_C1;
			}
			if (option == (const char *)"TWSS_C2")
			{
				i_value = TWSS_C2;
			} 
			if (option == (const char *)"TWSS_C3")
			{
				i_value = TWSS_C3;
			} 
			if (option == (const char *)"TWSS_C7")
			{
				i_value = TWSS_C7;
			} 
			if (option == (const char *)"TWSS_C8")
			{
				i_value = TWSS_C8;
			} 
			if (option == (const char *)"TWSS_C9")
			{
				i_value = TWSS_C9;
			} 
			if (option == (const char *)"TWSS_C10")
			{
				i_value = TWSS_C10;
			} 
			if (option == (const char *)"TWSS_USSTATEMENT")
			{
				i_value = TWSS_USSTATEMENT;
			} 
			if (option == (const char *)"TWSS_BUSINESSCARD")
			{
				i_value = TWSS_BUSINESSCARD;
			} 
//			if (option == (const char *)"TWSS_MAXSIZE")
//			{
//				i_value = TWSS_MAXSIZE;
//			} 

		}
			break;
		case ICAP_XFERMECH:
		{
			if (option == (const char *)"TWSX_NATIVE")
			{
				i_value = TWSX_NATIVE;
			}
			if (option == (const char *)"TWSX_FILE")
			{
				i_value = TWSX_FILE;
			}
			if (option == (const char *)"TWSX_MEMORY")
			{
				i_value = TWSX_MEMORY;
			}
//			if (option == (const char *)"TWSX_MEMFILE")
//			{
//				i_value = TWSX_MEMFILE;
//			} 

		}
			break;
		case ICAP_UNITS:
		{
			if (option == (const char *)"TWUN_INCHES")
			{
				i_value = TWUN_INCHES;
			}
			if (option == (const char *)"TWUN_CENTIMETERS")
			{
				i_value = TWUN_CENTIMETERS;
			}
			if (option == (const char *)"TWUN_PICAS")
			{
				i_value = TWUN_PICAS;
			}
			if (option == (const char *)"TWUN_POINTS")
			{
				i_value = TWUN_POINTS;
			}
			if (option == (const char *)"TWUN_TWIPS")
			{
				i_value = TWUN_TWIPS;
			}
			if (option == (const char *)"TWUN_PIXELS")
			{
				i_value = TWUN_PIXELS;
			}
//			if (option == (const char *)"TWUN_MILLIMETERS")
//			{
//				i_value = TWUN_MILLIMETERS;
//			} 

		}
			break;
	}
	
	switch(conType)
	{
		case TWON_ARRAY:

			break;
			
		case TWON_ENUMERATION:
			for(int i = 0; i< pENUMERATION->NumItems; ++i)
			{
				if(i_value == (pENUMERATION->ItemList)[i])
				{
					pENUMERATION->CurrentIndex = i;
					break;
				}
			}
			break;
			
		case TWON_ONEVALUE:
			switch(pONEVALUE->ItemType)
		{
			case TWTY_FIX32:
			{
				TW_INT32 value = (TW_INT32) (f_value * 65536.0 + ((f_value < 0) ? (-0.5) : 0.5));
				tw_fix32.Whole = (TW_UINT16)(value >> 16);
				tw_fix32.Frac = (TW_UINT16)(value & 0x0000ffffL);
				memcpy((void *)&pONEVALUE->Item, (const void *)&tw_fix32, sizeof(TW_FIX32));
			}
				break;
			case TWTY_FRAME:
			{
				//not implemented!
			}
				break;
			case TWTY_INT8:
			{
				TW_INT8 tw_int8 = (TW_INT8)i_value;
				memcpy((void *)&pONEVALUE->Item, (const void *)&tw_int8, sizeof(TW_INT8));
			}
				break;
			case TWTY_INT16:
			{
				TW_INT16 tw_int16 = (TW_INT16)i_value;
				memcpy((void *)&pONEVALUE->Item, (const void *)&tw_int16, sizeof(TW_INT16));
			}
				break;
			case TWTY_INT32:
			{
				TW_INT32 tw_int32 = (TW_INT32)i_value;
				memcpy((void *)&pONEVALUE->Item, (const void *)&tw_int32, sizeof(TW_INT32));
			}
				break;
			case TWTY_UINT8:
			{
				TW_UINT8 tw_uint8 = (TW_UINT8)i_value;
				memcpy((void *)&pONEVALUE->Item, (const void *)&tw_uint8, sizeof(TW_UINT8));
			}
				break;
			case TWTY_UINT16:
			{
				TW_UINT16 tw_uint16 = (TW_UINT16)i_value;
				memcpy((void *)&pONEVALUE->Item, (const void *)&tw_uint16, sizeof(TW_UINT16));
			}
				break;
			case TWTY_UINT32:
			{
				TW_UINT32 tw_uint32 = (TW_UINT32)i_value;
				memcpy((void *)&pONEVALUE->Item, (const void *)&tw_uint32, sizeof(TW_UINT32));
			}
				break;
			case TWTY_BOOL:
			{
				memcpy((void *)&pONEVALUE->Item, (const void *)&b_value, sizeof(TW_BOOL));
			}
				break;
			case TWTY_STR32:
			case TWTY_STR64:
			case TWTY_STR128:
			case TWTY_STR255:
			{
				
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
			switch(((pTW_RANGE)tw_capability)->ItemType)
		{
			case TWTY_FIX32:
			{
				double f_value = atof(str);
				TW_INT32 value = (TW_INT32) (f_value * 65536.0 + ((f_value < 0) ? (-0.5) : 0.5));
				tw_fix32.Whole = (TW_UINT16)(value >> 16);
				tw_fix32.Frac = (TW_UINT16)(value & 0x0000ffffL);
				memcpy((void *)&((pTW_RANGE)tw_capability)->CurrentValue, (const void *)&tw_fix32, sizeof(TW_FIX32));
			}
				break;
			case TWTY_FRAME:
			{
				//not implemented!
			}
				break;
			case TWTY_INT8:
			{
				TW_INT8 tw_int8 = (TW_INT8)i_value;
				memcpy((void *)&pRANGE->CurrentValue, (const void *)&tw_int8, sizeof(TW_INT8));
			}
				break;
			case TWTY_INT16:
			{
				TW_INT16 tw_int16 = (TW_INT16)i_value;
				memcpy((void *)&pRANGE->CurrentValue, (const void *)&tw_int16, sizeof(TW_INT16));
			}
				break;
			case TWTY_INT32:
			{
				TW_INT32 tw_int32 = (TW_INT32)i_value;
				memcpy((void *)&pRANGE->CurrentValue, (const void *)&tw_int32, sizeof(TW_INT32));
			}
				break;
			case TWTY_UINT8:
			{
				TW_UINT8 tw_uint8 = (TW_UINT8)i_value;
				memcpy((void *)&pRANGE->CurrentValue, (const void *)&tw_uint8, sizeof(TW_UINT8));
			}
				break;
			case TWTY_UINT16:
			{
				TW_UINT16 tw_uint16 = (TW_UINT16)i_value;
				memcpy((void *)&pRANGE->CurrentValue, (const void *)&tw_uint16, sizeof(TW_UINT16));
			}
				break;
			case TWTY_UINT32:
			{
				TW_UINT32 tw_uint32 = (TW_UINT32)i_value;
				memcpy((void *)&pRANGE->CurrentValue, (const void *)&tw_uint32, sizeof(TW_UINT32));
			}
				break;
			case TWTY_BOOL:
			{
				memcpy((void *)&pRANGE->CurrentValue, (const void *)&b_value, sizeof(TW_BOOL));
			}
				break;
			case TWTY_STR32:
			case TWTY_STR64:
			case TWTY_STR128:
			case TWTY_STR255:
			{
				
			}
				break;
				//					case TWTY_STR1024:
				//					case TWTY_UNI512:
				//						break;
			default:
				break;
		}
			break;
			
	}

}

void getCapabilityValueString(TW_CAPABILITY *tw_capability, void *p, C_TEXT& value)
{
	TW_UINT16 cap = tw_capability->Cap;
	TW_UINT16 conType = tw_capability->ConType;

	pTW_ENUMERATION pENUMERATION = (pTW_ENUMERATION)p;
	pTW_ONEVALUE pONEVALUE = (pTW_ONEVALUE)p;
	pTW_RANGE pRANGE = (pTW_RANGE)p;
	
	char str[CAP_VALUE_BUF_SIZE];
	memset(str, 0, sizeof(str));
	
	TW_UINT32 item = 0;
	
	switch(conType)
	{
		case TWON_ARRAY:
			
			break;
		case TWON_ENUMERATION:
			item = pENUMERATION->ItemList[pENUMERATION->CurrentIndex];
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

					break;
				case TWON_ENUMERATION:
					switch(pENUMERATION->ItemType)
				{
					case TWTY_FIX32:
					{
						pTW_FIX32 pFix32 = &((pTW_FIX32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
						sprintf(str, "%d.%u", pFix32->Whole, pFix32->Frac);
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
						TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
						sprintf(str, "%d", currentValue);
					}
						break;
					case TWTY_UINT8:
					case TWTY_UINT16:
					case TWTY_UINT32:
					{
						TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
						sprintf(str, "%u", currentValue);
					}
						break;
					case TWTY_BOOL:
					{
						TW_UINT32 currentValue = ((pTW_UINT32)(&pENUMERATION->ItemList))[pENUMERATION->CurrentIndex];
						sprintf(str, "%s", currentValue ? "true" : "false");
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
						pTW_FIX32 pFix32 = (pTW_FIX32)&pONEVALUE->Item;
						sprintf(str, "%d.%u", pFix32->Whole, pFix32->Frac);
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
						TW_UINT32 currentValue = pONEVALUE->Item;
						sprintf(str, "%d", currentValue);
					}
						break;
					case TWTY_UINT8:
					case TWTY_UINT16:
					case TWTY_UINT32:
					{
						TW_UINT32 currentValue = pONEVALUE->Item;
						sprintf(str, "%u", currentValue);
					}
						break;
					case TWTY_BOOL:
					{
						TW_UINT32 currentValue = pONEVALUE->Item;
						sprintf(str, "%s", currentValue ? "true" : "false");
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
					TW_UINT32 currentValue = pRANGE->CurrentValue;
					sprintf(str, "%u", currentValue);
					break;
			}
		}
			break;
	}
	CUTF8String u8value = (const uint8_t *)str;
	value.setUTF8String(&u8value);
}

void getStringFromCapability(TW_UINT16 cap, std::wstring &stringValue)
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

TW_UINT16 getCapabilityFromString(C_TEXT& Param2)
{
	CUTF8String option;
	Param2.copyUTF8String(&option);
	
	if (option == (const uint8_t *)"CAP_XFERCOUNT")
	{
		return CAP_XFERCOUNT;
	}
	if (option == (const uint8_t *)"ICAP_COMPRESSION")
	{
		return ICAP_COMPRESSION;
	}
	if (option == (const uint8_t *)"ICAP_PIXELTYPE")
	{
		return ICAP_PIXELTYPE;
	}
	if (option == (const uint8_t *)"ICAP_UNITS")
	{
		return ICAP_UNITS;
	}
	if (option == (const uint8_t *)"ICAP_XFERMECH")
	{
		return ICAP_XFERMECH;
	}
	if (option == (const uint8_t *)"CAP_AUTHOR")
	{
		return CAP_AUTHOR;
	}
	if (option == (const uint8_t *)"CAP_CAPTION")
	{
		return CAP_CAPTION;
	}
	if (option == (const uint8_t *)"CAP_FEEDERENABLED")
	{
		return CAP_FEEDERENABLED;
	}
	if (option == (const uint8_t *)"CAP_FEEDERLOADED")
	{
		return CAP_FEEDERLOADED;
	}
	if (option == (const uint8_t *)"CAP_TIMEDATE")
	{
		return CAP_TIMEDATE;
	}
	if (option == (const uint8_t *)"CAP_SUPPORTEDCAPS")
	{
		return CAP_SUPPORTEDCAPS;
	}
	if (option == (const uint8_t *)"CAP_EXTENDEDCAPS")
	{
		return CAP_EXTENDEDCAPS;
	}
	if (option == (const uint8_t *)"CAP_AUTOFEED")
	{
		return CAP_AUTOFEED;
	}
	if (option == (const uint8_t *)"CAP_CLEARPAGE")
	{
		return CAP_CLEARPAGE;
	}
	if (option == (const uint8_t *)"CAP_FEEDPAGE")
	{
		return CAP_FEEDPAGE;
	}
	if (option == (const uint8_t *)"CAP_REWINDPAGE")
	{
		return CAP_REWINDPAGE;
	}
	if (option == (const uint8_t *)"CAP_INDICATORS")
	{
		return CAP_INDICATORS;
	}
	if (option == (const uint8_t *)"CAP_SUPPORTEDCAPSEXT")
	{
		return CAP_SUPPORTEDCAPSEXT;
	}
	if (option == (const uint8_t *)"CAP_PAPERDETECTABLE")
	{
		return CAP_PAPERDETECTABLE;
	}
	if (option == (const uint8_t *)"CAP_UICONTROLLABLE")
	{
		return CAP_UICONTROLLABLE;
	}
	if (option == (const uint8_t *)"CAP_DEVICEONLINE")
	{
		return CAP_DEVICEONLINE;
	}
	if (option == (const uint8_t *)"CAP_AUTOSCAN")
	{
		return CAP_AUTOSCAN;
	}
	if (option == (const uint8_t *)"CAP_THUMBNAILSENABLED")
	{
		return CAP_THUMBNAILSENABLED;
	}
	if (option == (const uint8_t *)"CAP_DUPLEX")
	{
		return CAP_DUPLEX;
	}
	if (option == (const uint8_t *)"CAP_DUPLEXENABLED")
	{
		return CAP_DUPLEXENABLED;
	}
	if (option == (const uint8_t *)"CAP_ENABLEDSUIONLY")
	{
		return CAP_ENABLEDSUIONLY;
	}
	if (option == (const uint8_t *)"CAP_CUSTOMDSDATA")
	{
		return CAP_CUSTOMDSDATA;
	}
	if (option == (const uint8_t *)"CAP_ENDORSER")
	{
		return CAP_ENDORSER;
	}
	if (option == (const uint8_t *)"CAP_JOBCONTROL")
	{
		return CAP_JOBCONTROL;
	}
	if (option == (const uint8_t *)"CAP_ALARMS")
	{
		return CAP_ALARMS;
	}
	if (option == (const uint8_t *)"CAP_ALARMVOLUME")
	{
		return CAP_ALARMVOLUME;
	}
	if (option == (const uint8_t *)"CAP_AUTOMATICCAPTURE")
	{
		return CAP_AUTOMATICCAPTURE;
	}
	if (option == (const uint8_t *)"CAP_TIMEBEFOREFIRSTCAPTURE")
	{
		return CAP_TIMEBEFOREFIRSTCAPTURE;
	}
	if (option == (const uint8_t *)"CAP_TIMEBETWEENCAPTURES")
	{
		return CAP_TIMEBETWEENCAPTURES;
	}
	if (option == (const uint8_t *)"CAP_CLEARBUFFERS")
	{
		return CAP_CLEARBUFFERS;
	}
	if (option == (const uint8_t *)"CAP_MAXBATCHBUFFERS")
	{
		return CAP_MAXBATCHBUFFERS;
	}
	if (option == (const uint8_t *)"CAP_DEVICETIMEDATE")
	{
		return CAP_DEVICETIMEDATE;
	}
	if (option == (const uint8_t *)"CAP_POWERSUPPLY")
	{
		return CAP_POWERSUPPLY;
	}
	if (option == (const uint8_t *)"CAP_CAMERAPREVIEWUI")
	{
		return CAP_CAMERAPREVIEWUI;
	}
	if (option == (const uint8_t *)"CAP_DEVICEEVENT")
	{
		return CAP_DEVICEEVENT;
	}
	if (option == (const uint8_t *)"CAP_SERIALNUMBER")
	{
		return CAP_SERIALNUMBER;
	}
	if (option == (const uint8_t *)"CAP_PRINTER")
	{
		return CAP_PRINTER;
	}
	if (option == (const uint8_t *)"CAP_PRINTERENABLED")
	{
		return CAP_PRINTERENABLED;
	}
	if (option == (const uint8_t *)"CAP_PRINTERINDEX")
	{
		return CAP_PRINTERINDEX;
	}
	if (option == (const uint8_t *)"CAP_PRINTERMODE")
	{
		return CAP_PRINTERMODE;
	}
	if (option == (const uint8_t *)"CAP_PRINTERSTRING")
	{
		return CAP_PRINTERSTRING;
	}
	if (option == (const uint8_t *)"CAP_PRINTERSUFFIX")
	{
		return CAP_PRINTERSUFFIX;
	}
	if (option == (const uint8_t *)"CAP_LANGUAGE")
	{
		return CAP_LANGUAGE;
	}
	if (option == (const uint8_t *)"CAP_FEEDERALIGNMENT")
	{
		return CAP_FEEDERALIGNMENT;
	}
	if (option == (const uint8_t *)"CAP_FEEDERORDER")
	{
		return CAP_FEEDERORDER;
	}
	if (option == (const uint8_t *)"CAP_REACQUIREALLOWED")
	{
		return CAP_REACQUIREALLOWED;
	}
	if (option == (const uint8_t *)"CAP_BATTERYMINUTES")
	{
		return CAP_BATTERYMINUTES;
	}
	if (option == (const uint8_t *)"CAP_BATTERYPERCENTAGE")
	{
		return CAP_BATTERYPERCENTAGE;
	}
	if (option == (const uint8_t *)"ICAP_AUTOBRIGHT")
	{
		return ICAP_AUTOBRIGHT;
	}
	if (option == (const uint8_t *)"ICAP_BRIGHTNESS")
	{
		return ICAP_BRIGHTNESS;
	}
	if (option == (const uint8_t *)"ICAP_CONTRAST")
	{
		return ICAP_CONTRAST;
	}
	if (option == (const uint8_t *)"ICAP_CUSTHALFTONE")
	{
		return ICAP_CUSTHALFTONE;
	}
	if (option == (const uint8_t *)"ICAP_EXPOSURETIME")
	{
		return ICAP_EXPOSURETIME;
	}
	if (option == (const uint8_t *)"ICAP_FILTER")
	{
		return ICAP_FILTER;
	}
	if (option == (const uint8_t *)"ICAP_FLASHUSED")
	{
		return ICAP_FLASHUSED;
	}
	if (option == (const uint8_t *)"ICAP_GAMMA")
	{
		return ICAP_GAMMA;
	}
	if (option == (const uint8_t *)"ICAP_HALFTONES")
	{
		return ICAP_HALFTONES;
	}
	if (option == (const uint8_t *)"ICAP_HIGHLIGHT")
	{
		return ICAP_HIGHLIGHT;
	}
	if (option == (const uint8_t *)"ICAP_IMAGEFILEFORMAT")
	{
		return ICAP_IMAGEFILEFORMAT;
	}
	if (option == (const uint8_t *)"ICAP_LAMPSTATE")
	{
		return ICAP_LAMPSTATE;
	}
	if (option == (const uint8_t *)"ICAP_LIGHTSOURCE")
	{
		return ICAP_LIGHTSOURCE;
	}
	if (option == (const uint8_t *)"ICAP_ORIENTATION")
	{
		return ICAP_ORIENTATION;
	}
	if (option == (const uint8_t *)"ICAP_PHYSICALWIDTH")
	{
		return ICAP_PHYSICALWIDTH;
	}
	if (option == (const uint8_t *)"ICAP_PHYSICALHEIGHT")
	{
		return ICAP_PHYSICALHEIGHT;
	}
	if (option == (const uint8_t *)"ICAP_SHADOW")
	{
		return ICAP_SHADOW;
	}
	if (option == (const uint8_t *)"ICAP_FRAMES")
	{
		return ICAP_FRAMES;
	}
	if (option == (const uint8_t *)"ICAP_XNATIVERESOLUTION")
	{
		return ICAP_XNATIVERESOLUTION;
	}
	if (option == (const uint8_t *)"ICAP_YNATIVERESOLUTION")
	{
		return ICAP_YNATIVERESOLUTION;
	}
	if (option == (const uint8_t *)"ICAP_XRESOLUTION")
	{
		return ICAP_XRESOLUTION;
	}
	if (option == (const uint8_t *)"ICAP_YRESOLUTION")
	{
		return ICAP_YRESOLUTION;
	}
	if (option == (const uint8_t *)"ICAP_MAXFRAMES")
	{
		return ICAP_MAXFRAMES;
	}
	if (option == (const uint8_t *)"ICAP_TILES")
	{
		return ICAP_TILES;
	}
	if (option == (const uint8_t *)"ICAP_BITORDER")
	{
		return ICAP_BITORDER;
	}
	if (option == (const uint8_t *)"ICAP_CCITTKFACTOR")
	{
		return ICAP_CCITTKFACTOR;
	}
	if (option == (const uint8_t *)"ICAP_LIGHTPATH")
	{
		return ICAP_LIGHTPATH;
	}
	if (option == (const uint8_t *)"ICAP_PIXELFLAVOR")
	{
		return ICAP_PIXELFLAVOR;
	}
	if (option == (const uint8_t *)"ICAP_PLANARCHUNKY")
	{
		return ICAP_PLANARCHUNKY;
	}
	if (option == (const uint8_t *)"ICAP_ROTATION")
	{
		return ICAP_ROTATION;
	}
	if (option == (const uint8_t *)"ICAP_SUPPORTEDSIZES")
	{
		return ICAP_SUPPORTEDSIZES;
	}
	if (option == (const uint8_t *)"ICAP_THRESHOLD")
	{
		return ICAP_THRESHOLD;
	}
	if (option == (const uint8_t *)"ICAP_XSCALING")
	{
		return ICAP_XSCALING;
	}
	if (option == (const uint8_t *)"ICAP_YSCALING")
	{
		return ICAP_YSCALING;
	}
	if (option == (const uint8_t *)"ICAP_BITORDERCODES")
	{
		return ICAP_BITORDERCODES;
	}
	if (option == (const uint8_t *)"ICAP_PIXELFLAVORCODES")
	{
		return ICAP_PIXELFLAVORCODES;
	}
	if (option == (const uint8_t *)"ICAP_JPEGPIXELTYPE")
	{
		return ICAP_JPEGPIXELTYPE;
	}
	if (option == (const uint8_t *)"ICAP_TIMEFILL")
	{
		return ICAP_TIMEFILL;
	}
	if (option == (const uint8_t *)"ICAP_BITDEPTH")
	{
		return ICAP_BITDEPTH;
	}
	if (option == (const uint8_t *)"ICAP_BITDEPTHREDUCTION")
	{
		return ICAP_BITDEPTHREDUCTION;
	}
	if (option == (const uint8_t *)"ICAP_UNDEFINEDIMAGESIZE")
	{
		return ICAP_UNDEFINEDIMAGESIZE;
	}
	if (option == (const uint8_t *)"ICAP_IMAGEDATASET")
	{
		return ICAP_IMAGEDATASET;
	}
	if (option == (const uint8_t *)"ICAP_EXTIMAGEINFO")
	{
		return ICAP_EXTIMAGEINFO;
	}
	if (option == (const uint8_t *)"ICAP_MINIMUMHEIGHT")
	{
		return ICAP_MINIMUMHEIGHT;
	}
	if (option == (const uint8_t *)"ICAP_MINIMUMWIDTH")
	{
		return ICAP_MINIMUMWIDTH;
	}
	if (option == (const uint8_t *)"ICAP_FLIPROTATION")
	{
		return ICAP_FLIPROTATION;
	}
	if (option == (const uint8_t *)"ICAP_BARCODEDETECTIONENABLED")
	{
		return ICAP_BARCODEDETECTIONENABLED;
	}
	if (option == (const uint8_t *)"ICAP_SUPPORTEDBARCODETYPES")
	{
		return ICAP_SUPPORTEDBARCODETYPES;
	}
	if (option == (const uint8_t *)"ICAP_BARCODEMAXSEARCHPRIORITIES")
	{
		return ICAP_BARCODEMAXSEARCHPRIORITIES;
	}
	if (option == (const uint8_t *)"ICAP_BARCODESEARCHPRIORITIES")
	{
		return ICAP_BARCODESEARCHPRIORITIES;
	}
	if (option == (const uint8_t *)"ICAP_BARCODESEARCHMODE")
	{
		return ICAP_BARCODESEARCHMODE;
	}
	if (option == (const uint8_t *)"ICAP_BARCODEMAXRETRIES")
	{
		return ICAP_BARCODEMAXRETRIES;
	}
	if (option == (const uint8_t *)"ICAP_BARCODETIMEOUT")
	{
		return ICAP_BARCODETIMEOUT;
	}
	if (option == (const uint8_t *)"ICAP_ZOOMFACTOR")
	{
		return ICAP_ZOOMFACTOR;
	}
	if (option == (const uint8_t *)"ICAP_PATCHCODEDETECTIONENABLED")
	{
		return ICAP_PATCHCODEDETECTIONENABLED;
	}
	if (option == (const uint8_t *)"ICAP_SUPPORTEDPATCHCODETYPES")
	{
		return ICAP_SUPPORTEDPATCHCODETYPES;
	}
	if (option == (const uint8_t *)"ICAP_PATCHCODEMAXSEARCHPRIORITIES")
	{
		return ICAP_PATCHCODEMAXSEARCHPRIORITIES;
	}
	if (option == (const uint8_t *)"ICAP_PATCHCODESEARCHPRIORITIES")
	{
		return ICAP_PATCHCODESEARCHPRIORITIES;
	}
	if (option == (const uint8_t *)"ICAP_PATCHCODESEARCHMODE")
	{
		return ICAP_PATCHCODESEARCHMODE;
	}
	if (option == (const uint8_t *)"ICAP_PATCHCODEMAXRETRIES")
	{
		return ICAP_PATCHCODEMAXRETRIES;
	}
	if (option == (const uint8_t *)"ICAP_PATCHCODETIMEOUT")
	{
		return ICAP_PATCHCODETIMEOUT;
	}
	if (option == (const uint8_t *)"ICAP_FLASHUSED2")
	{
		return ICAP_FLASHUSED2;
	}
	if (option == (const uint8_t *)"ICAP_IMAGEFILTER")
	{
		return ICAP_IMAGEFILTER;
	}
	if (option == (const uint8_t *)"ICAP_NOISEFILTER")
	{
		return ICAP_NOISEFILTER;
	}
	if (option == (const uint8_t *)"ICAP_OVERSCAN")
	{
		return ICAP_OVERSCAN;
	}
	if (option == (const uint8_t *)"ICAP_AUTOMATICBORDERDETECTION")
	{
		return ICAP_AUTOMATICBORDERDETECTION;
	}
	if (option == (const uint8_t *)"ICAP_AUTOMATICDESKEW")
	{
		return ICAP_AUTOMATICDESKEW;
	}
	if (option == (const uint8_t *)"ICAP_AUTOMATICROTATE")
	{
		return ICAP_AUTOMATICROTATE;
	}
	if (option == (const uint8_t *)"ICAP_JPEGQUALITY")
	{
		return ICAP_JPEGQUALITY;
	}
	
	return 0;
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
