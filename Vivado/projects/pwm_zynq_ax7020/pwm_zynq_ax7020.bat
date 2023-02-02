for %%a in ( C D E F G H I J K) do (
	for /f "delims=" %%F in ('dir /b /s "%%a:\vivado.bat" 2^>nul') do set MyVariable=%%F
)

%MyVariable% -mode batch -source pwm_zynq_ax7020.tcl

:: C:\Xilinx\Vivado\2022.2\bin\vivado.bat -mode batch -source pwm_zynq_ax7020.tcl