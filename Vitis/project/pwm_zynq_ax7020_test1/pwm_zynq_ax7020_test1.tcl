setws ./workspace
cd ./workspace

app create -name pwm_zynq_ax7020_test1 -hw ../system.xsa -os standalone -proc ps7_cortexa9_0 -template {Empty Application}
importsources -name my_app -path ../src/
app build -name my_app