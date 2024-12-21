@if exist "%~dp0\_setup_tests.bat" @call "%~dp0\_setup_tests.bat"
@rem echo OUTROOTPATH=%OUTROOTPATH%
@rem echo SLN_EXE=%SLN_EXE%
@set TEST=%SLN_EXE%
"%TEST%" < msg1_1.txt > umba-cl-msg_msg1_1.cpp
"%TEST%" < msg1_2.txt > umba-cl-msg_msg1_2.cpp
"%TEST%" < msg1_3.txt > umba-cl-msg_msg1_3.cpp
"%TEST%" < msg1_4.txt > umba-cl-msg_msg1_4.cpp
"%TEST%" < msg1_5.txt > umba-cl-msg_msg1_5.cpp
"%TEST%" < msg1_6.txt > umba-cl-msg_msg1_6.cpp
"%TEST%" < msg1_7.txt > umba-cl-msg_msg1_7.cpp

"%TEST%" < msg2_1.txt > umba-cl-msg_msg2_1.cpp
"%TEST%" < msg2_2.txt > umba-cl-msg_msg2_2.cpp
"%TEST%" < msg2_3.txt > umba-cl-msg_msg2_3.cpp
