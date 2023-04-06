set savedDir [pwd]
set savedDir [file dirname $savedDir]
puts $savedDir
set stringSource ${savedDir}/src/helloworld.c
puts $stringSource
setws ./workspace
cd ./workspace
file copy -force {../../../Vivado/xsa_hardware/cpwm8c_gpio__zedboard.xsa} ./
app create -name test_2 -hw {cpwm8c_gpio__zedboard.xsa} -os standalone -proc ps7_cortexa9_0 -template {Empty Application}
# app build -name test_2
importsources -name test_2 -path $stringSource -soft-link
closehw {cpwm8c_gpio__zedboard.xsa}