@if exist "%~dp0\_setup_tests.bat" @call "%~dp0\_setup_tests.bat"
@rem echo OUTROOTPATH=%OUTROOTPATH%
@rem echo SLN_EXE=%SLN_EXE%
@set TEST=%TEST_001_EXE%
"%TEST%" < msg1.txt > test-001_msg1.cpp
"%TEST%" < msg2.txt > test-001_msg2.cpp
"%TEST%" < msg3.txt > test-001_msg3.cpp
"%TEST%" < msg4.txt > test-001_msg4.cpp
"%TEST%" < msg5.txt > test-001_msg5.cpp
"%TEST%" < msg6.txt > test-001_msg6.cpp
"%TEST%" < msg7.txt > test-001_msg7.cpp
