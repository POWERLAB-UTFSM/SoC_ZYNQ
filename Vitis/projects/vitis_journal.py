#-----------------------------------------------------------------
# Vitis v2024.1 (64-bit)
# Start of session at: Fri May 31 18:48:57 2024
# Current directory: E:\Repos\SoC_ZYNQ\Vitis\projects
# Command line: vitis -i
# Journal file: vitis_journal.py
# Batch mode: $XILINX_VITIS/bin/vitis -new -s E:\Repos\SoC_ZYNQ\Vitis\projects\vitis_journal.py
#-----------------------------------------------------------------

#!/usr/bin/env python3
import vitis
import os
import shutil
path_workspace=os.path.normpath(os.getcwd() + '\\workspace')
path_swrepo=os.path.normpath(os.getcwd() + os.sep + os.pardir + '\\drivers')
file_hw='HW_Zedboard_test_cdma.xsa'
path_hw=os.path.normpath(os.getcwd() + os.sep + os.pardir + os.sep + os.pardir + '\\Vivado\\xsa_hardware\\' + file_hw )
if (os.path.isdir(path_workspace)):
    shutil.rmtree(path_workspace)
    print(f"Deleted workspace {path_workspace}")
    
client = vitis.create_client()   
client.set_workspace(path_workspace)
#[Out]# True
client.set_embedded_sw_repo(level='LOCAL',path=path_swrepo)
#[Out]# True
vitis.cli_client
#[Out]# <module 'vitis.cli_client' from 'C:\\Xilinx\\Vitis\\2024.1\\cli\\vitis\\cli_client.py'>
vitis.os
#[Out]# <module 'os' from 'C:\\Xilinx\\Vitis\\2024.1\\tps\\win64\\python-3.8.3\\lib\\os.py'>
vitis.os_platform.release()
#[Out]# '10'
vitis.cli_client.os_platform.version
#[Out]# <function platform.version()>
platform =client.create_platform_component(name = 'pform', hw_design = path_hw)
platform.update_desc(desc = 'pform')
#[Out]# True
domain_standalone = platform.add_domain(cpu = 'ps7_cortexa9_1', os = 'standalone', name = 'standalone_domain', display_name = 'standalone on ps7_cortexa9_1')
domain_standalone.set_lib('xilffs')
#[Out]# True
domain_standalone.set_lib('xilrsa')
#[Out]# True
domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='"-g -Wall -Wextra -fno-tree-loop-distribute-patterns -DUSE_AMP=1"')
#[Out]# True
platform.build()
#[Out]# 0
app = client.create_app_component(name = 'app', platform = client.get_workspace() + '/pform/export/pform/pform.xpfm', domain = 'standalone_domain', template = 'empty_application')
app.set_app_config(key='USER_COMPILE_DEBUG_LEVEL', values=['-g3'])
#[Out]# True
app.set_app_config(key='USER_COMPILE_OTHER_FLAGS', values='"-fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard"')
#[Out]# True
app.set_app_config(key='USER_LINK_OTHER_FLAGS', values='"-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none -Wl,-Map,output.map"')
#[Out]# True
app.set_app_config(key='USER_LINKER_SCRIPT', values=['../src/lscript.ld'])
#[Out]# True
path_src=os.getcwd() + os.sep + os.pardir + '\\src\\test_vitis_unified2023p2'
app.set_app_config(key='USER_LINK_LIBRARIES', values=['m'])
#[Out]# True
path_src_main=os.getcwd() + os.sep + os.pardir + '\\src\\test_vitis_unified2023p2'
path_dst_main=app.component_location + '\\src'
for src_item in os.listdir(path_src_main):
    os.symlink(path_src_main + os.sep + src_item, app.component_location + '\\src\\' + src_item)
    
import json
with open(app.component_location + "\\_ide\\.theia\\launch.json", "r") as jsonFile:
    jsonData = json.load(jsonFile)
    
jsonData["configurations"][0]['targetSetup']['zynqInitialization']['usingPs7Init']['ps7InitTclFile']='${workspaceFolder}\\app\\_ide\\psinit\\ps7_init.tcl'
with open(app.component_location + "\\_ide\\.theia\\launch.json", 'w', encoding='utf-8') as jsonFile:
    json.dump(jsonData, jsonFile)
    
jsonFile.close()
linker = app.get_ld_script()
linker.regenerate()
#[Out]# True
linker.update_memory_region(name = 'ps7_ddr_0', base_address = '0x1f000000', size = '0x00100000')
#[Out]# True
system_project = client.create_sys_project(name = 'app_system', platform = client.get_workspace() + '/pform/export/pform/pform.xpfm')
system_project.add_component(name = 'app')
#[Out]# 'project_name'    : app_system
#[Out]# 'project_location': 'E:\Repos\SoC_ZYNQ\Vitis\projects\workspace/app_system'
#[Out]# 'project_type'    : 'UNKNOWN'
#[Out]# 'platform'        : 'E:\Repos\SoC_ZYNQ\Vitis\projects\workspace/pform/export/pform/pform.xpfm'
#[Out]# 'components'      :'
#[Out]# 'app'
app.build()
#[Out]# 1
vitis.dispose()
exit()
vitis.dispose()
