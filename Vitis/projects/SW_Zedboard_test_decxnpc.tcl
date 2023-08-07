# workspace folder -> go to the folder
setws ./workspace
cd ./workspace

# automatic/manual
puts -nonewline "Automatic (Y) or manual (N) names for the project:\n"
flush stdout
set strautomanual [gets stdin]

if {[string equal [string tolower $strautomanual] "y"]} {
    set automanual 1
    puts $automanual
    puts "Automatic names \n"
} else {
    set automanual 0
    puts $automanual
    puts "Manual names \n"
}

# platform name
if {$automanual == 0} {
    puts -nonewline "Enter a name for your platform name: \n"
    flush stdout
    set platformname [gets stdin]
} else {
    set platformname "Pform_Zedboard_test_decxnpc"
}
puts "Platform name: $platformname \n"

# hardware location name
if {$automanual == 0} {
    puts -nonewline "Enter the hardware project (.xsa) located in ../../../Vivado/xsa_hardware/: \n"
    flush stdout
    set hardwarename [gets stdin]
} else {
    set hardwarename "HW_Zedboard_test_decxnpc.xsa"
}
puts "Hardware name: $hardwarename \n"

# app name
if {$automanual == 0} {
    puts -nonewline "Enter the name of your application: \n"
    flush stdout
    set appname [gets stdin]
} else {
    set appname "App_Zedboard_test_decxnpc"
}
puts "App name: $appname \n"

# saved directory from local path
set savedDir [pwd]
set savedDir [file dirname $savedDir]
puts $savedDir

#copy hardware
file copy -force ../../../Vivado/xsa_hardware/$hardwarename ./

# create standalone platform from hardware in core 0
platform create -name $platformname -hw $hardwarename -os standalone -proc ps7_cortexa9_0 

# create new app in baremetal domain 
app create -name $appname -platform $platformname -os baremetal -template {Empty Application}

# compile platform
platform generate

# # create platform
# platform create -name $platformname -hw $hardwarename -os linux -proc ps7_cortexa9 

# # create new domain (baremetal) for ARM2
# domain create -name baremetal -proc ps7_cortexa9_1 -os standalone -display-name baremetal

# # create new app in baremetal domain 
# puts -nonewline "Enter the name of your baremetal app: \n"
# flush stdout
# set appname [gets stdin]
# puts $appname
# app create -name $appname -platform $platformname -domain baremetal

# # create new app in linux domain 
# puts -nonewline "Enter the name of your linux app: \n"
# flush stdout
# set linuxappname [gets stdin]
# puts $linuxappname
# app create -name $appname -platform $platformname -domain linux_domain -template "Linux Hello World"

# # compile platform
# platform generate