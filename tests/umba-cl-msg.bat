@if exist "%~dp0\_setup_tests.bat" @call "%~dp0\_setup_tests.bat"
@rem echo OUTROOTPATH=%OUTROOTPATH%
@rem echo SLN_EXE=%SLN_EXE%
@set TEST=%SLN_EXE%
"%TEST%" < msg1.txt > umba-cl-msg_msg1.cpp
"%TEST%" < msg2.txt > umba-cl-msg_msg2.cpp
"%TEST%" < msg3.txt > umba-cl-msg_msg3.cpp
"%TEST%" < msg4.txt > umba-cl-msg_msg4.cpp
"%TEST%" < msg5.txt > umba-cl-msg_msg5.cpp
"%TEST%" < msg6.txt > umba-cl-msg_msg6.cpp
"%TEST%" < msg7.txt > umba-cl-msg_msg7.cpp
