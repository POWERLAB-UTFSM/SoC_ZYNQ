set savedDir [pwd]
set savedDir [file dirname $savedDir]
puts $savedDir
set stringSource ${savedDir}/src/helloworld.c
puts $stringSource
setws ./workspace
cd ./workspace
app create -name test_2 -hw {../../../Vivado/xsa_hardware/cpwm8c_1_wrapper.xsa} -os standalone -proc ps7_cortexa9_0 -template {Empty Application}
app build -name test_2
importsources -name test_2 -path $stringSource -soft-link
closehw {../../../Vivado/xsa_hardware/cpwm8c_1_wrapper.xsa}