# project name
set proyName "test_zedboard_2023"
puts $proyName
set savedDir [pwd]
set savedDir [file dirname $savedDir]
puts $savedDir
# main source file
set includeSource "helloworld.c"
puts $includeSource
set stringSource ${savedDir}/src/$includeSource
puts $stringSource
# hardware file
set savedHardware "test_zedboard_2023.xsa"
puts $savedHardware

setws ./workspace
cd ./workspace

file copy -force ../../../Vivado/xsa_hardware/$savedHardware ./
app create -name $proyName -hw $savedHardware -os standalone -proc ps7_cortexa9_0 -template {Empty Application}
# app build -name $proyName
importsources -name $proyName -path $stringSource -soft-link
closehw $savedHardware


