#-----------------------------------------------------------------
# Vitis v2023.1 (64-bit)
# Start of session at: Tue Mar 12 23:04:15 2024
# Current directory: E:\Repos\SoC_ZYNQ\Vitis\projects
# Command line: vitis -i
# Journal file: vitis_journal.py
# Batch mode: $XILINX_VITIS/bin/vitis -new -s E:\Repos\SoC_ZYNQ\Vitis\projects\vitis_journal.py
#-----------------------------------------------------------------

#!/usr/bin/env python3
import vitis
import os
import shutil
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
#[Out]# True
domain_standalone.list_params('proc')
#[Out]# [{'parameter_name': 'proc_archiver',
#[Out]#   'description': 'Archiver',
#[Out]#   'default_value': 'arm-none-eabi-gcc-ar.exe',
#[Out]#   'value': 'arm-none-eabi-gcc-ar.exe',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'readonly'},
#[Out]#  {'parameter_name': 'proc_assembler',
#[Out]#   'description': 'Assembler',
#[Out]#   'default_value': 'arm-none-eabi-gcc',
#[Out]#   'value': 'arm-none-eabi-gcc',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'readonly'},
#[Out]#  {'parameter_name': 'proc_compiler',
#[Out]#   'description': 'Compiler',
#[Out]#   'default_value': 'arm-none-eabi-gcc.exe',
#[Out]#   'value': 'arm-none-eabi-gcc.exe',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'readonly'},
#[Out]#  {'parameter_name': 'proc_compiler_flags',
#[Out]#   'description': 'Compiler Flags',
#[Out]#   'default_value': ' -O2 -DSDT -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard;-c',
#[Out]#   'value': ' -O2 -DSDT -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard;-c',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'readonly'},
#[Out]#  {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#   'description': 'Extra Compiler Flags',
#[Out]#   'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#   'value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'read_write'}]
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
procsx
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value=' -g')
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value=f' -g')
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value=d)
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value=-g)
domain_standalone.list_params('os')
#[Out]# [{'parameter_name': 'standalone_stdin',
#[Out]#   'description': 'stdin peripheral',
#[Out]#   'default_value': 'ps7_uart_1',
#[Out]#   'value': 'ps7_uart_1',
#[Out]#   'possible_options': ['None', 'ps7_uart_1', 'ps7_coresight_comp_0'],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'read_write'},
#[Out]#  {'parameter_name': 'standalone_stdout',
#[Out]#   'description': 'stdout peripheral',
#[Out]#   'default_value': 'ps7_uart_1',
#[Out]#   'value': 'ps7_uart_1',
#[Out]#   'possible_options': ['None', 'ps7_uart_1', 'ps7_coresight_comp_0'],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'read_write'}]
procsx=domain_standalone.get_config(option='os',param='standalone_stdout')
procsx=domain_standalone.set_config(option='os',param='standalone_stdout',value='ps7_uart_1')
domain_standalone.get_config(option='os',param='standalone_stdout')
#[Out]# {'parameter_name': 'standalone_stdout',
#[Out]#  'description': 'stdout peripheral',
#[Out]#  'default_value': 'ps7_uart_1',
#[Out]#  'value': "'ps7_uart_1'",
#[Out]#  'possible_options': ['None', 'ps7_uart_1', 'ps7_coresight_comp_0'],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
domain_standalone.get_config(option='os',param="'standalone_stdout'")
domain_standalone.get_config(option='os',param="'standalone_stdout')
domain_standalone.get_config(option='os',param="standalone_stdout")
#[Out]# {'parameter_name': 'standalone_stdout',
#[Out]#  'description': 'stdout peripheral',
#[Out]#  'default_value': 'ps7_uart_1',
#[Out]#  'value': "'ps7_uart_1'",
#[Out]#  'possible_options': ['None', 'ps7_uart_1', 'ps7_coresight_comp_0'],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option='os',param='standalone_stdout',value="'ps7_uart_1'")
domain_standalone.get_config(option='os',param="standalone_stdout")
#[Out]# {'parameter_name': 'standalone_stdout',
#[Out]#  'description': 'stdout peripheral',
#[Out]#  'default_value': 'ps7_uart_1',
#[Out]#  'value': "''ps7_uart_1''",
#[Out]#  'possible_options': ['None', 'ps7_uart_1', 'ps7_coresight_comp_0'],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option='os',param='standalone_stdout',value="'ps7_uart_1 '")
procsx=domain_standalone.set_config(option='os',param='standalone_stdout',value="'ps7_uart_1'")
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value="'-g -Wall'")
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value="' -g'")
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',values="' -g'")
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value="' -g'")
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value="'-g'")
procsx=domain_standalone.set_config(option='proc',param='proc_extra_compiler_flags',value="' -g -Wl'")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="' -g -Wl'")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="_\-g -Wl \' ")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=":\-g \'")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=":\-g")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=":\'-g")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=":\' \'")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=":\''")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=":\'-g'")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="-g\:")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g\\",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='-g\:')
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g\\",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='-g\:'')
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='-g\:'")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="-g\'")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g''",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="-g\' ")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="-g\' -W")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=join(["-g"]))
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="".join(["-g"]))
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="".join(["-g","-Wl"]))
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g-Wl'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=" ".join(["-g","-Wl"]))
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=f"{word1} {word2}")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=f"fsd")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'fsd'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=f"{g}")
word1='-g'
word2='-Wl'
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=f"{word1}")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=f"{word1} {word2}")
domain_standalone.list_params()
domain_standalone.list_params('proc')
#[Out]# [{'parameter_name': 'proc_archiver',
#[Out]#   'description': 'Archiver',
#[Out]#   'default_value': 'arm-none-eabi-gcc-ar.exe',
#[Out]#   'value': 'arm-none-eabi-gcc-ar.exe',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'readonly'},
#[Out]#  {'parameter_name': 'proc_assembler',
#[Out]#   'description': 'Assembler',
#[Out]#   'default_value': 'arm-none-eabi-gcc',
#[Out]#   'value': 'arm-none-eabi-gcc',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'readonly'},
#[Out]#  {'parameter_name': 'proc_compiler',
#[Out]#   'description': 'Compiler',
#[Out]#   'default_value': 'arm-none-eabi-gcc.exe',
#[Out]#   'value': 'arm-none-eabi-gcc.exe',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'readonly'},
#[Out]#  {'parameter_name': 'proc_compiler_flags',
#[Out]#   'description': 'Compiler Flags',
#[Out]#   'default_value': ' -O2 -DSDT -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard;-c',
#[Out]#   'value': ' -O2 -DSDT -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard;-c',
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'readonly'},
#[Out]#  {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#   'description': 'Extra Compiler Flags',
#[Out]#   'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#   'value': "'-g'",
#[Out]#   'possible_options': [],
#[Out]#   'datatype': 'string',
#[Out]#   'permission': 'read_write'}]
domain_standalone.get_config('param')
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=str(g))
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=str('g'))
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'g'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=str('g '))
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=str('\sg '))
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=str("\sg "))
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="\sg ")
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="\sg")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'\\sg'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value="\s-g\s")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'\\s-g\\s'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value=f"\s-g\s")
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'\\s-g\\s'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
domain_standalone.get_config(option='proc',param={'-g'})
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'\\s-g\\s'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value={'g'})
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'{'g'}'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value={'-g'})
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'{'-g'}'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value={"-g"})
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'{'-g'}'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value={"-g","-W"})
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value={"-g","W"})
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value={"-g",'-W'})
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value={'-g','-W'})
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='"g"')
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'g'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='"-g -W"')
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g -W'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='"-g -Wall -Wextra -fno-tree-loop-distribute-patterns"')
domain_standalone.get_config(option='proc',param='proc_extra_compiler_flags')
#[Out]# {'parameter_name': 'proc_extra_compiler_flags',
#[Out]#  'description': 'Extra Compiler Flags',
#[Out]#  'default_value': ' -g -Wall -Wextra -fno-tree-loop-distribute-patterns',
#[Out]#  'value': "'-g -Wall -Wextra -fno-tree-loop-distribute-patterns'",
#[Out]#  'possible_options': [],
#[Out]#  'datatype': 'string',
#[Out]#  'permission': 'read_write'}
procsx=domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='"-g -Wall -Wextra -fno-tree-loop-distribute-patterns -DUSE_AMP=1"')
domain_standalone.set_config(option="proc",param="proc_extra_compiler_flags",value='"-g -Wall -Wextra -fno-tree-loop-distribute-patterns -DUSE_AMP=1"')
#[Out]# True
vitis.dispose()
exit()
vitis.dispose()
