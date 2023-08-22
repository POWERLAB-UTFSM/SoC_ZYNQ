# Administración de proyectos en Vivado

## Desempaquetar proyecto Vivado desde Tool Command Language (`tcl`)

1. Ejecutar el archivo `_VIVADO_PROJECT_GENERATOR.bat`. Desde Windows Powershell, ingrese: 
```powershell
& "./_VIVADO_PROJECT_GENERATOR"
```
2. Ingresar en consola el archivo `.tcl` correspondiente al proyecto a desempaquetar.
3. Ir a la subcarpeta creada, y abrir el archivo `.xpr` creado.

<!--- **Nota**: Toda subcarpeta desde esta posición raíz, junto a sus archivos, será ignorada a la hora de ejecutar comandos de captura de repositorios en git (como `git commit`). Cualquier archivo que necesite para guardar y subir al repositorio deberá guardarlo directamente acá o en carpetas anteriores. Para más detalle, abra [.gitignore](.gitignore).
-->

## Reempaquetar proyecto en `tcl`

0. (De ser necesario) eliminar desde Vivado cualquier archivo auxiliar que no se desee regenerar, como por ejemplo los archivos de síntesis en "Utility Sources".
1. Ir a "File -> Project -> Write Tcl..."
2. Seleccionar "Copy resources to new project" y "Recreate block designs using Tcl"
3. Presionar OK 

## Instalar archivos de preconfiguración de tarjetas

Dependiendo de qué tarjeta se esté ocupando en un determinado proyecto, será necesario instalar archivos de preconfiguración antes de crear o regenerar un proyecto desde un `tcl`. Para ello, se accede a:

* Vivado -> Vivado Store -> Boards -> {Tarjeta a elección}.

## Crear archivo de diseño de hardware `xsa` para Vitis

0. (Si no ha sido creado) Buscar el *block design* (`bd`), click derecho y seleccionar "Create HDL wrapper" con las opciones por defecto.
1. Crear *bitstream*.
2. Buscar el ícono de *block design* (`bd`), click derecho y seleccionar "Generate output products" con las opciones por defecto
3. Ir a "File -> Export -> Export Hardware", seleccionar "Include bitstream" y crear archivo `.xsa`, dejándolo en la carpeta [/xsa_hardware](../xsa_hardware/)

<!--- [^1]: **Nota**: Toda subcarpeta desde esta posición raíz, junto a sus archivos, será ignorada a la hora de ejecutar comandos de captura de repositorios en git (como `git commit`). Cualquier archivo que necesite para guardar y subir al repositorio deberá guardarlo directamente acá o en carpetas anteriores. Para más detalle, abra [.gitignore](.gitignore).-->
# Descripción de proyectos

<!------------------------------------->
## Proyecto `HW_Zedboard_test_decxnpc`

Proyecto de pruebas en Vivado que implementa en FPGA un modulador LS-PWM [axi_cpwm8c](../ip_repo/AXI4lte/axi_cpwm8c_1_0/) y una máquina de estado para el disparo de convertidores 3L-(X)NPC-VSC [axi_dec3lxnpc](../ip_repo/AXI4lite/axi_dec3lxnpc_1_0/) para ser controlado vía AXI mediante el MCU Zynq-7000, utilizando la plataforma Zedboard.

### Autores

* [Alan Wilson](mailto:alan.wilson@usm.cl)

### Hardware

* Plataforma Zedboard con SoC Zynq 7020

### Software

* Vitis Core Development Kit. Incluye:
    * Vivado Design Suite
    * Vitis Model Composer
    * Vitis HLS

* [Zedboard](https://github.com/Xilinx/XilinxBoardStore/tree/2023.1/boards/Avnet/zedboard/1.4) (Vivado Store -> Boards)

### Contenido

* [HW_Zedboard_test_decxnpc.tcl](HW_Zedboard_test_decxnpc.tcl): Archivo `tcl` con comandos de desempaquetado para Vivado.

<!------------------------------------->

## Proyecto `pwm_zynq_ax7020`

### Descripción

Proyecto en Vivado que implementa en FPGA una PWM desde un periférico IP [AXI_CPWM](../ip_repo/AXI4/AXI_CPWM_power_1_0/) para ser controlado vía AXI mediante el MCU Zynq-7000.

Este proyecto fue empaquetado en [pwm_zynq_ax7020.tcl](pwm_zynq_ax7020.tcl), para mejor manejo de control de versiones vía Git.

### Autores

* [Alan Wilson](mailto:alan.wilson@usm.cl)

### Requisitos 

#### Hardware

* Plataforma Alinx AX7020 con SoC Zynq 7020 (xc7z020clg400-2)

#### Software

* Vitis Core Development Kit. Incluye:
    * Vivado Design Suite
    * Vitis Model Composer
    * Vitis HLS

### Contenido

* [pwm_zynq_ax7020.tcl](pwm_zynq_ax7020.tcl): Archivo `tcl` con comandos de desempaquetado para Vivado