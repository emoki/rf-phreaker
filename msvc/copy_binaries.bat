ECHO ON

set dir=%1
set config=%2
set platform=%3
set dll_name=%4

if "%platform%" == "Win32" set binary_dir=%dir%..\%config%\MS32\dll

if "%platfrom%"=="X64" set binary_dir=%dir%..\%config%\MS64\dll

mkdir "%binary_dir%"


set include_dir=%dir%..\%config%\include\%dll_name%

mkdir %include_dir%

copy %dir%..\libusb\libusb.h %include_dir%

copy %dir%..\%platform%\%config%\dll\%dll_name%.dll %binary_dir%
copy %dir%..\%platform%\%config%\dll\%dll_name%.lib %binary_dir%