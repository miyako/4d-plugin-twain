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
scanners|ARRAY TEXT|scanner names. ``#0`` is detailed ``JSON`` (out)

Properties of ``scanners{0}``

```
Manufacturer : string
ProductFamily : string
ProductName : string
Version:
  Info : string
  MinorNum : number
  MajorNum : number
  Language : number
  Country : number
```

```
default:=TWAIN Get default option (scanner;settings)
```

Parameter|Type|Description
------------|------------|----
scanner|TEXT|
settings|TEXT|
default|TEXT|


