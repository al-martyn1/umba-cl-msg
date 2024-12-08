@if exist "%~dp0\set_sln.bat"    @call "%~dp0\set_sln.bat"

@rem %UMBA_TOOLS% - eg F:\umba-tools

@if "%UMBA_TOOLS%"=="" goto UMBA_TOOLS_VAR_NOT_SET
@goto UMBA_TOOLS_VAR_IS_SET

:UMBA_TOOLS_VAR_NOT_SET
@echo UMBA_TOOLS environmetnt variable is not set
@exit /B 1

:UMBA_TOOLS_VAR_IS_SET

@call "%~dp0\.bat\setup_out_root_paths.bat"

@if not exist "%UMBA_TOOLS%\bin"    mkdir "%UMBA_TOOLS%\bin"
@if not exist "%UMBA_TOOLS%\conf"   mkdir "%UMBA_TOOLS%\conf"

@IF "%OUTROOTPATH%"=="" @(
    @echo OUTROOTPATH not found
    exit /B 1
)

copy /Y "%OUTROOTPATH%\Release\%SLN%.exe"         "%UMBA_TOOLS%\bin\"

@if exist _distr_conf @xcopy /Y /S /E /I /F /R "%~dp0\_distr_conf\conf\*"               "%UMBA_TOOLS%\conf"

@rem umba-brief-scanner --help > help.txt