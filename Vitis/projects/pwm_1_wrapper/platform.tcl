# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\ahwv\workspace\pwm_1_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\ahwv\workspace\pwm_1_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {pwm_1_wrapper}\
-hw {E:\Repos\POWERLAB-UTFSM\SoC_ZYNQ\Vivado\projects\ax7020_zynq_pwm\pwm_1_wrapper.xsa}\
-out {C:/Users/ahwv/workspace}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {pwm_1_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
