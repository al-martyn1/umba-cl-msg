@if exist "%~dp0\_setup_tests.bat" @call "%~dp0\_setup_tests.bat"
@rem echo OUTROOTPATH=%OUTROOTPATH%
@rem echo SLN_EXE=%SLN_EXE%
@set TEST=%TEST_001_EXE%
"%TEST%" < msg1_1.txt > test-001_msg1_1.cpp
"%TEST%" < msg1_2.txt > test-001_msg1_2.cpp
"%TEST%" < msg1_3.txt > test-001_msg1_3.cpp
"%TEST%" < msg1_4.txt > test-001_msg1_4.cpp
"%TEST%" < msg1_5.txt > test-001_msg1_5.cpp
"%TEST%" < msg1_6.txt > test-001_msg1_6.cpp
"%TEST%" < msg1_7.txt > test-001_msg1_7.cpp
