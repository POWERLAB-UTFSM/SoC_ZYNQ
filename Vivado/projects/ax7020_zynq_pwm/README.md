# Proyecto `ax7020_zynq_pwm`

## Descripción

Proyecto en Vivado que implementa en FPGA una PWM desde un periférico IP [AXI_CPWM](../../ip_repo/AXI4/AXI_CPWM_power_1_0/) para ser controlado vía AXI mediante el MCU Zynq-7000.

Este proyecto fue empaquetado en [ax7020_zynq_pwm.tcl](ax7020_zynq_pwm.tcl), para mejor manejo de control de versiones vía Git.

## Autores

* [Alan Wilson](mailto:alan.wilson@usm.cl)

## Requisitos 

### Hardware

Plataforma Alinx AX7020 con SoC Zynq 7020 (xc7z020clg400-2)

### Software

Vitis Core Development Kit. Incluye:
* Vivado Design Suite
* Vitis Model Composer
* Vitis HLS

## Contenido [^1]

* [ax7020_zynq_pwm.bat](ax7020_zynq_pwm.bat): Archivo batch para automatizar desempaquetado de proyectos
* [ax7020_zynq_pwm.tcl](ax7020_zynq_pwm.tcl): Archivo `tcl` con comandos de desempaquetado para Vivado
* `.xsa`: Archivo *Xilinx Support Archive* con el diseño de hardware, a ser utilizado por Vitis e incorporarlo en el desarrollo de software.

## Desempaquetar proyecto [^1] desde Tool Command Language (`tcl`)

1. Ejecutar el archivo [ax7020_zynq_pwm.bat](ax7020_zynq_pwm.bat) el cual referencia al archivo [ax7020_zynq_pwm.tcl](ax7020_zynq_pwm.tcl)
2. Ir a la subcarpeta creada, y abrir el archivo `.xpr` creado

**Nota**: Toda subcarpeta desde esta posición raíz, junto a sus archivos, será ignorada a la hora de ejecutar comandos de captura de repositorios en git (como `git commit`). Cualquier archivo que necesite para guardar y subir al repositorio deberá guardarlo directamente acá o en carpetas anteriores. Para más detalle, abra [.gitignore](.gitignore).

## Reempaquetar proyecto en `tcl`

1. Ir a "File -> Project -> Write Tcl..."
2. Seleccionar "Copy resources to new project" y "Recreate block designs using Tcl"
3. Presionar OK 

## Crear archivo de diseño de hardware para Vitis

0. (Si no ha sido creado) Buscar el *block design* (`bd`), click derecho y seleccionar "Create HDL wrapper" con las opciones por defecto.
1. Crear *bitstream*.
2. Buscar el ícono de *block design* (`bd`), click derecho y seleccionar "Generate output products" con las opciones por defecto
3. Ir a "File -> Export -> Export Hardware", seleccionar "Include bitstream" y crear archivo `.xsa` [^1].

[^1]: **Nota**: Toda subcarpeta desde esta posición raíz, junto a sus archivos, será ignorada a la hora de ejecutar comandos de captura de repositorios en git (como `git commit`). Cualquier archivo que necesite para guardar y subir al repositorio deberá guardarlo directamente acá o en carpetas anteriores. Para más detalle, abra [.gitignore](.gitignore).