# Proyectos ZYNQ (SoC-ZYNQ)

## Descripción

Repositorio con archivos de proyectos de sistemas de control implementados en System-on-chips (SoCs) ZYNQ de Xilinx.

## Requisitos

### Software

* Vitis Core Development Kit. Incluye:
    * Vivado Design Suite.
    * Vitis Model Composer.
    * Vitis High Level Synthesis (HLS).
    * Vitis IDE.
* Git, para control de versiones y manejo de repositorios.

### Hardware

Compatible, según proyecto.

## Contenido de carpetas:

* [Vivado](Vivado): Carpeta con archivos para proyectos de descripción de hardware en Vivado.
    * [ip_repo](Vivado/ip_repo): Repositorio general de IPs para ser usadas en proyectos.
    * [sources](Vivado/sources): códigos fuente para ser reutilizados en distintos proyectos e IPs.
        * [hdl](Vivado/sources/hdl): códigos de *Hardware Description Language* (hdl) (ej.: VHDL, Verilog, SystemVerilog, etc.)
        * [PS tcl](Vivado/sources/tcl): comandos *Tool Command language* (tcl) utilizables en distintos proyectos.
        * [xdc](Vivado/sources/xdc): archivos *Xilinx Design Constraints* (xdc) con restricciones y condicionantes de diseño.
    * [projects](Vivado/projects): Proyectos creados con Vivado.
* [Vitis](Vitis): Carpeta con archivos para proyectos de desarrollo de software en Vitis.

## Más información de interés:


* [README: Administración de proyectos de hardware en Vivado](Vivado/projects/README.md)
    * [README: Definiciones de pinout y restricciones (`xdc`) de tarjetas FPGA/SoC](Vivado/sources/xdc/README.md)
    * [README: Creación de scripts `tcl` para configuración de SoCs ZYNQ](Vivado/sources/tcl/README.md)
    * [README: Creación e inclusión de IPs en proyectos de Vivado](Vivado/ip_repo/README.md)
* [README: Administración de proyectos de software en Vitis IDE](Vivado/sources/tcl/README.md)
