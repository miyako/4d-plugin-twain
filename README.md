# 4d-plugin-twain
[TWAIN](http://www.twain.org) client for Windows and macOS

[twain-dsm](https://github.com/twain/twain-dsm) is used for Windows. (native ``TWAIN_32.DLL``is 32-bit only)

``TWAIN.framework`` is used for macOS. see also [4d-plugin-ica](https://github.com/miyako/4d-plugin-ica).

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />

## Syntax

```
TWAIN SCANNERS LIST (scanners)
```

Parameter|Type|Description
------------|------------|----
scanners|ARRAY TEXT|scanner names. ``#0`` is detailed ``JSON``

Properties of ``scanners{0}``

```
Manufacturer : string
ProductFamily : string
ProductName : string
SupportGroup : number
Version:
  Info : string
  MinorNum : number
  MajorNum : number
  Language : number
  Country : number
```

names of all TWAIN scanners installed on the system are returned, whether online or not.

```
default:=TWAIN Get default option (scanner;description)
```

Parameter|Type|Description
------------|------------|----
scanner|TEXT|scanner name
description|TEXT|``JSON``
setting|TEXT|``JSON``

only features included in ``CAP_SUPPORTEDCAPS`` are returned. ``setting`` is the current setting. ``description`` explains valid values for each feature.

empty string specified the default scanner.

on windows the call is executed in a new thread with [``_beginthreadex``](https://msdn.microsoft.com/en-us/library/kdzttdcb.aspx)

the device must be online to retrive values.

```
TWAIN SCAN (scanner;setting;format;images)
```

Parameter|Type|Description
------------|------------|----
scanner|TEXT|scanner name
setting|TEXT|``JSON``
format|LONGINT|``Scanner image type JPEG`` or ``Scanner image type PNG``
images|ARRAY PICTURE|

for efficiency, pass a subset of the setting object that contains properties that are different from the default values.

empty string specified the default scanner.

on windows the call is executed in a new thread with [``_beginthreadex``](https://msdn.microsoft.com/en-us/library/kdzttdcb.aspx)

---

* Sample ``setting`` object

```json
{
	"CAP_DEVICEONLINE": true,
	"CAP_ENABLEDSUIONLY": true,
	"CAP_UICONTROLLABLE": true,
	"CAP_SERIALNUMBER": "TH78N1Q20C",
	"ICAP_AUTOBRIGHT": true,
	"ICAP_UNDEFINEDIMAGESIZE": true,
	"ICAP_AUTOMATICBORDERDETECTION": true,
	"ICAP_AUTOMATICDESKEW": true,
	"ICAP_AUTOMATICROTATE": true,
	"ICAP_BITDEPTHREDUCTION": "TWBR_THRESHOLD",
	"ICAP_HALFTONES": "Default Dither",
	"ICAP_BITORDER": "TWBO_MSBFIRST",
	"ICAP_COMPRESSION": "TWCP_NONE",
	"ICAP_JPEGPIXELTYPE": 2,
	"ICAP_JPEGQUALITY": "",
	"ICAP_IMAGEFILEFORMAT": "TWFF_BMP",
	"ICAP_PLANARCHUNKY": "TWPC_CHUNKY",
	"CAP_INDICATORS": true,
	"ICAP_PIXELFLAVOR": "TWPF_CHOCOLATE",
	"ICAP_PIXELTYPE": "TWPT_RGB",
	"ICAP_BITDEPTH": 24,
	"CAP_XFERCOUNT": -1,
	"ICAP_XFERMECH": "TWSX_NATIVE",
	"ICAP_UNITS": "TWUN_INCHES",
	"CAP_FEEDERENABLED": true,
	"CAP_FEEDERALIGNMENT": "TWFA_LEFT",
	"CAP_FEEDERORDER": "TWFO_FIRSTPAGEFIRST",
	"CAP_REACQUIREALLOWED": false,
	"CAP_FEEDERLOADED": true,
	"CAP_PAPERDETECTABLE": true,
	"CAP_DUPLEX": "TWDX_2PASSDUPLEX",
	"CAP_AUTOFEED": true,
	"ICAP_PHYSICALWIDTH": 8.5,
	"ICAP_PHYSICALHEIGHT": 14,
	"ICAP_MINIMUMWIDTH": 5.82666,
	"ICAP_MINIMUMHEIGHT": 8.266663,
	"ICAP_SUPPORTEDSIZES": "TWSS_USLEGAL",
	"ICAP_GAMMA": 1.799988,
	"ICAP_XRESOLUTION": 200,
	"ICAP_YRESOLUTION": 200,
	"CAP_DUPLEXENABLED": true,
	"ICAP_FLIPROTATION": "TWFR_BOOK",
	"ICAP_XNATIVERESOLUTION": 300,
	"ICAP_YNATIVERESOLUTION": 300,
	"ICAP_THRESHOLD": 128,
	"ICAP_BRIGHTNESS": 0,
	"ICAP_CONTRAST": 0
}
```

* Sample ``description`` object

```json
{
	"CAP_DEVICEONLINE": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_ENABLEDSUIONLY": {
		"values": [
			true
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_UICONTROLLABLE": {
		"values": [
			true
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_SERIALNUMBER": {
		"itemType": "TWON_ONEVALUE"
	},
	"": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_AUTOBRIGHT": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_UNDEFINEDIMAGESIZE": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_AUTOMATICBORDERDETECTION": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_AUTOMATICDESKEW": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_AUTOMATICROTATE": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_BITDEPTHREDUCTION": {
		"values": [
			"TWBR_THRESHOLD",
			"TWBR_HALFTONE",
			"TWBR_DIFFUSION"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_HALFTONES": {
		"values": [
			"Default Dither",
			"Bayer Dither"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_BITORDER": {
		"values": [
			"TWBO_MSBFIRST"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_COMPRESSION": {
		"values": [
			"TWCP_NONE"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_JPEGPIXELTYPE": {
		"values": [
			2
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_JPEGQUALITY": {
		"itemType": "TWON_RANGE",
		"minValue": 0,
		"maxValue": 100,
		"stepSize": 1,
		"defaultValue": 75
	},
	"ICAP_IMAGEFILEFORMAT": {
		"values": [
			"TWFF_BMP",
			"TWFF_JFIF",
			"TWFF_PNG",
			"TWFF_TIFF"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_PLANARCHUNKY": {
		"values": [
			"TWPC_CHUNKY"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_INDICATORS": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_PIXELFLAVOR": {
		"values": [
			"TWPF_CHOCOLATE"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_PIXELTYPE": {
		"values": [
			"TWPT_RGB",
			"TWPT_GRAY",
			"TWPT_BW"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_BITDEPTH": {
		"values": [
			24
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_XFERCOUNT": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_XFERMECH": {
		"values": [
			"TWSX_NATIVE",
			"TWSX_MEMORY",
			"TWSX_FILE"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_UNITS": {
		"values": [
			"TWUN_INCHES",
			"TWUN_CENTIMETERS",
			"TWUN_POINTS",
			"TWUN_PIXELS"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_FEEDERENABLED": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_FEEDERALIGNMENT": {
		"itemType": "TWON_ONEVALUE"
	},
	"CAP_FEEDERORDER": {
		"itemType": "TWON_ONEVALUE"
	},
	"CAP_REACQUIREALLOWED": {
		"values": [
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_FEEDERLOADED": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_PAPERDETECTABLE": {
		"values": [
			true
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_DUPLEX": {
		"itemType": "TWON_ONEVALUE"
	},
	"CAP_AUTOFEED": {
		"values": [
			true
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_PHYSICALWIDTH": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_PHYSICALHEIGHT": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_MINIMUMWIDTH": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_MINIMUMHEIGHT": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_SUPPORTEDSIZES": {
		"values": [
			"TWSS_NONE",
			"TWSS_USLETTER",
			"TWSS_USLEGAL",
			"TWSS_USEXECUTIVE",
			"TWSS_A4LETTER",
			"TWSS_A5",
			"TWSS_ISOB5",
			"TWSS_B5LETTER",
			"TWSS_C5"
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_GAMMA": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_XRESOLUTION": {
		"values": [
			75,
			100,
			200,
			300
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_YRESOLUTION": {
		"values": [
			75,
			100,
			200,
			300
		],
		"itemType": "TWON_ENUMERATION"
	},
	"CAP_DUPLEXENABLED": {
		"values": [
			true,
			false
		],
		"itemType": "TWON_ENUMERATION"
	},
	"ICAP_FLIPROTATION": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_XNATIVERESOLUTION": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_YNATIVERESOLUTION": {
		"itemType": "TWON_ONEVALUE"
	},
	"ICAP_THRESHOLD": {
		"itemType": "TWON_RANGE",
		"minValue": 0,
		"maxValue": 255,
		"stepSize": 1,
		"defaultValue": 128
	},
	"ICAP_BRIGHTNESS": {
		"itemType": "TWON_RANGE",
		"minValue": 64536,
		"maxValue": 1000,
		"stepSize": 1,
		"defaultValue": 0
	},
	"ICAP_CONTRAST": {
		"itemType": "TWON_RANGE",
		"minValue": 64536,
		"maxValue": 1000,
		"stepSize": 1,
		"defaultValue": 0
	}
}
```
