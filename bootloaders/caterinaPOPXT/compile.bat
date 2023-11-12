set BASEDIR=c:\arduino\hardware
set DIRAVRUTIL=%BASEDIR%\tools\avr\utils\bin
set DIRAVRBIN=%BASEDIR%\tools\avr\bin
set DIRAVRAVR=%BASEDIR%\tools\avr\avr\bin
set DIRLIBEXEC=%BASEDIR%\tools\avr\libexec\gcc\avr\4.3.2
set OLDPATH=%PATH%
@path %DIRAVRUTIL%;%DIRAVRBIN%;%DIRAVRAVR%;%DIRLIBEXEC%;%PATH%
cd %BASEDIR%\arduino\bootloaders\caterinaPOPXT
%DIRAVRUTIL%\make.exe clean
%DIRAVRUTIL%\make.exe all VID=0x2341 PID=0x0036
copy Caterina.hex NewPOPXT.hex
%DIRAVRUTIL%\make.exe clean
@path %OLDPATH%
