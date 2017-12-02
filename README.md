# 4d-plugin-twain
[TWAIN](http://www.twain.org) client for Windows and macOS

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

empty string specified the default scanner.

on windows the call is executed in a new thread with [``_beginthreadex``](https://msdn.microsoft.com/en-us/library/kdzttdcb.aspx)
