@echo off
set /p "id=Enter your .tcl script file: "
echo OKAY! your project tcl file is %id% , right?

set exebat=\xilinx\Vitis\2022.2\bin\xsct.bat


if exist  C:%exebat% (
	C:%exebat% %id%
	)
else if exist  D:%exebat% (
	D:%exebat% %id%
	)
else if exist  E:%exebat% (
	E:%exebat% %id%
	)
else if exist  F:%exebat% (
	F:%exebat% %id%
	)
else if exist  G:%exebat% (
	G:%exebat% %id%
	)