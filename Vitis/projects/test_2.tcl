setws ./workspace
cd ./workspace
app create -name test_2 -hw ../../../Vivado/xsa_hardware/cpwm8c_1_wrapper.xsa -os standalone -proc ps7_cortexa9_0 -template {Empty Application}
importsources -name test_2 -path ../../src/helloworld.c
app build -name test_2
closehw ../../../Vivado/xsa_hardware/cpwm8c_1_wrapper.xsa