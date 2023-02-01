:: for /f "delims=" %%F in ('dir /b /s "C:\vivado.bat" 2^>nul') do set MyVariable=%%F

:: %MyVariable% -mode batch -source ax7020_zynq_pwm.tcl



:: @echo off

@REM    for %%a in ( C D E F G H I J K) do (
@REM       if exist "%%a:\" dir "%%a:\vivado.bat" /b /s /a-d (

@REM       )
@REM    )
@REM  -mode batch -source ax7020_zynq_pwm.tcl

for %%a in ( C D E F G H I J K) do (
    for /f "delims=" %%F in ('dir /b /s "%%a:\vivado.bat" 2^>nul') do set MyVariable=%%F
)

%MyVariable% -mode batch -source ax7020_zynq_pwm.tcl