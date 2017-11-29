#include "4DPluginAPI.h"
#include "4DPlugin.h"






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
