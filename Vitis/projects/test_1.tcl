setws ./workspace
cd ./workspace
app create -name test_1 -hw ../../../Vivado/xsa_hardware/pwm_1_wrapper.xsa -os standalone -proc ps7_cortexa9_0 -template {Empty Application}
importsources -name test_1 -path ../../src/helloworld.c
app build -name test_1
closehw ../../../Vivado/xsa_hardware/pwm_1_wrapper.xsa