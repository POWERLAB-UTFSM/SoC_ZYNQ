@echo off
set /p "id=Enter your project tcl file: "
echo OKAY! your project tcl file is %id% , right?

set exebat=\Xilinx\Vivado\2023.2\bin\vivado.bat

if exist  C:%exebat% ( C:%exebat% -mode batch -source %id% )
else (

for %%a in ( C D E F G H I J K) do (
	for /f "delims=" %%F in ('dir /b /s "%%a:%exebat%" 2^>nul') do set MyVariable=%%F
)

%MyVariable% -mode batch -source %id%
)
			
pause