@if exist "%~dp0\_setup_tests.bat" @call "%~dp0\_setup_tests.bat"
@echo OUTROOTPATH=%OUTROOTPATH%
@echo SLN_EXE=%SLN_EXE%
"%SLN_EXE%" < msg.txt  > msg.cpp
"%SLN_EXE%" < msg2.txt > msg2.cpp
"%SLN_EXE%" < msg3.txt > msg3.cpp
"%SLN_EXE%" < msg4.txt > msg4.cpp
"%SLN_EXE%" < msg5.txt > msg5.cpp
"%SLN_EXE%" < msg6.txt > msg6.cpp
"%SLN_EXE%" < msg7.txt > msg7.cpp
