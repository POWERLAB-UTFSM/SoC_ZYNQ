#!/usr/bin/env python3
import vitis
import os
import shutil

# This script is auto-generated by Vitis IDE

print("\n---------------------------------------------------------")
print("  Creating Vitis Unified IDE workspace ")
print("---------------------------------------------------------")

# Delete the workspace if already exists.
path_workspace=os.path.normpath(os.getcwd() + '\\workspace')
path_swrepo=os.path.normpath(os.getcwd() + os.sep + os.pardir + '\\drivers')
file_hw='HW_Zedboard_test_cdma.xsa'
path_hw=os.path.normpath(os.getcwd() + os.sep + os.pardir + os.sep + os.pardir + '\\Vivado\\xsa_hardware\\' + file_hw )

if (os.path.isdir(path_workspace)):
    shutil.rmtree(path_workspace)
    print(f"Deleted workspace {path_workspace}")

# Create Vitis client
client = vitis.create_client()        
client.set_workspace(path_workspace)
print('Successfully created Vitis client on workspace {}'.format(client.get_workspace()))

# Set software repository (custom drivers)
client.set_sw_repo(level='LOCAL',path=path_swrepo)
print("Software repository in " + path_swrepo)

# Creating platform
print("Creating platform component 'pform'")
print("Importing hardware " + file_hw)
platform = client.create_platform_component(name = 'pform', hw = path_hw)
platform.update_desc(desc = 'pform')
print("Adding new domain 'domain_standalone' for cpu: 'ps7_cortexa9_1' and OS: 'standalone'")
domain_standalone = platform.add_domain(cpu = 'ps7_cortexa9_1', os = 'standalone', name = 'standalone_domain', display_name = 'standalone on ps7_cortexa9_1')
print("Configuring the domain 'domain_standalone'...")
domain_standalone.set_lib('xilffs')
domain_standalone.set_lib('xilrsa')
domain_standalone.set_lib('libmetal')
# domain_standalone.set_lib('openamp')

print("Migrating BSP settings for the domain 'domain_standalone'")

# Building platform
platform.build()

# Creating application
print("Creating application component 'app'")
app = client.create_app_component(name = 'app', platform = client.get_workspace() + '/pform/export/pform/pform.xpfm', domain = 'standalone_domain', template = 'empty_application')

# Configuration options
app.set_app_config(key='USER_COMPILE_DEBUG_LEVEL', values=['-g3'])
app.set_app_config(key='USER_COMPILE_OTHER_FLAGS', values='"-fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -DUSE_AMP=1"')
app.set_app_config(key='USER_LINK_OTHER_FLAGS', values='"-mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none -Wl,-Map,output.map"')
app.set_app_config(key='USER_LINKER_SCRIPT', values=['../src/lscript.ld'])

# Add symbolic links to sources
path_src=os.getcwd() + os.sep + os.pardir + '\\src\\test_vitis_unified2023p2'
# app.import_files(from_loc=path_src, files=["hw_zedboard.c", "hw_zedboard.h"], dest_dir_in_cmp = "src")
app.set_app_config(key='USER_LINK_LIBRARIES', values=['m'])
path_src_main=os.getcwd() + os.sep + os.pardir + '\\src\\test_vitis_unified2023p2'
path_dst_main=app.component_location + '\\src'
print("Add source symbolic links from "+ path_src)
for src_item in os.listdir(path_src_main):
    os.symlink(path_src_main + os.sep + src_item, app.component_location + '\\src\\' + src_item)

# Editing launch configuration in 'launch.json'
print("Editing launch configuration")
import json
with open(app.component_location + "\\_ide\\.theia\\launch.json", "r") as jsonFile:
    jsonData = json.load(jsonFile)

jsonData["configurations"][0]['targetSetup']['zynqInitialization']['usingPs7Init']['ps7InitTclFile']='${workspaceFolder}\\app\\_ide\\psinit\\ps7_init.tcl'

with open(app.component_location + "\\_ide\\.theia\\launch.json", 'w', encoding='utf-8') as jsonFile:
    json.dump(jsonData, jsonFile)
jsonFile.close()

# Get the linker script from the app component
linker = app.get_ld_script()
# Regenerate ld file with default values
linker.regenerate()

# Creating system project : 'app_system'
print("Creating system project 'app_system'")
system_project = client.create_sys_project(name = 'app_system', platform = client.get_workspace() + '/pform/export/pform/pform.xpfm')
system_project.add_component(name = 'app')

# Building app 
app.build()

# Terminate Vitis client
vitis.dispose()