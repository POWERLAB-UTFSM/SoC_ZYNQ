# automatic/manual
puts -nonewline "Automatic (Y) or manual (N) script for the project?:\n"
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

# platform name CPU0
if {$automanual == 0} {
    puts -nonewline "Enter a name for your CPU0 platform name: \n"
    flush stdout
    set pformcpu0name [gets stdin]
} else {
    set pformcpu0name "pform_fsbl"
}
puts "Platform name: $pformcpu0name \n"

# platform name CPU1
if {$automanual == 0} {
    puts -nonewline "Enter a name for your CPU0 platform name: \n"
    flush stdout
    set pformcpu1name [gets stdin]
} else {
    set pformcpu1name "pform"
}
puts "Platform name: $pformcpu1name \n"

# hardware location name
if {$automanual == 0} {
    puts -nonewline "Enter the hardware project (.xsa) located in ../../../Vivado/xsa_hardware/: \n"
    flush stdout
    set hardwarename [gets stdin]
} else {
    set hardwarename "HW_Zedboard_test_decxnpc.xsa"
}
puts "Hardware name: $hardwarename \n"

# app FSBL name
if {$automanual == 0} {
    puts -nonewline "Enter the name of your FSBL application: \n"
    flush stdout
    set appfsblname [gets stdin]
} else {
    set appfsblname "app_fsbl"
}
puts "App name: $appfsblname \n"

# app CPU1 name (bare metal)
if {$automanual == 0} {
    puts -nonewline "Enter the name of your CPU1 bare metal application: \n"
    flush stdout
    set appcpu1name [gets stdin]
} else {
    set appcpu1name "app_cpu1"
}
puts "App name: $appcpu1name \n"

# workspace folder -> go to the folder
setws ./workspace
cd ./workspace

# saved directories from local path
set savedDir [pwd]
set savedDir [file dirname $savedDir]
set savedDir [file dirname $savedDir]
puts "Local directory: $savedDir \n"
set hardwarepath [pwd]
set hardwarepath [file dirname $hardwarepath]
set hardwarepath [file dirname $hardwarepath]
set hardwarepath [file dirname $hardwarepath]
set hardwarepath $hardwarepath/Vivado/xsa_hardware
puts "Hardware path: $hardwarepath  \n"

#delete directories with the same project name
file delete -force $savedDir/projects/workspace

# workspace folder -> go to the folder
setws ./workspace
cd ./workspace

#copy hardware
file copy -force $hardwarepath/$hardwarename ./

# # create standalone platform from hardware in CPU0
# platform create -name $pformcpu0name -hw $hardwarename -os standalone -proc ps7_cortexa9_0 
# platform generate

# # create new FSBL app in baremetal domain for CPU0
# app create -name $appfsblname -platform $pformcpu0name -os standalone -template "Zynq FSBL"

# create standalone platform from hardware in CPU1
platform create -name $pformcpu1name -hw $hardwarename -os standalone -proc ps7_cortexa9_1 
platform generate
platform active $pformcpu1name

# set active domain
domain active standalone_domain
domain active

# add compiler flag to domain
bsp config -append extra_compiler_flags {-DUSE_AMP=1}

# create new app in baremetal domain for CPU1
app create -name $appcpu1name -platform $pformcpu1name -os standalone -template {Empty Application} -domain standalone_domain

# included source name
if {$automanual == 0} {
    puts -nonewline "Enter the name of your source file: \n"
    flush stdout
    set includeSource [gets stdin]
} else {
    set includeSource "main.c"
}
puts "\n Source name: $includeSource \n"
set stringSource ${savedDir}/src/SW_Zedboard_test_decxnpc/$includeSource
puts "Source path: $stringSource \n"

# import sources
importsources -name $appcpu1name -path $stringSource -soft-link -linker-script

# included source name
if {$automanual == 0} {
    puts -nonewline "Enter the name of your source file: \n"
    flush stdout
    set includeSource [gets stdin]
} else {
    set includeSource "hw_zedboard_test_decxnpc.c"
}
puts "\n Source name: $includeSource \n"
set stringSource ${savedDir}/src/SW_Zedboard_test_decxnpc/$includeSource
puts "Source path: $stringSource \n"

# import sources
importsources -name $appcpu1name -path $stringSource -soft-link -linker-script

# configure app to include the "m" (math.h) library
app config -name $appcpu1name -add libraries {m}

# set active domain
domain active standalone_domain
domain active

# add compiler flag to domain
bsp config -append extra_compiler_flags {-DUSE_AMP=1}

# create new FSBL app for CPU0
app create -name $appfsblname -platform $pformcpu1name -os standalone -template {Zynq FSBL}