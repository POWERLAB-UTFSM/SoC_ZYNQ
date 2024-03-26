# Regeneración automatizada de proyectos en Vitis Unified 2023.2 desde script de Python

## Requisitos
- Vitis 2023.2 en adelante (incluyendo Vivado y Vitis Unified)

## Ejecutar script

1. Ejecutar script Python
	```Powershell
	> vitis -s <script_proyecto>.py
	```
	Creandose su proyecto (BSP y aplicaciones) en la carpeta [\workspace](./workspace/)
	- Dependiendo del contenido del script, puede que necesite privilegios de administrador. Para ello (Windows), puede instalar [gsudo](https://github.com/gerardog/gsudo), y anteceder ``gsudo`` al comando anterior.
	- Opcionalmente, puede crear un script interactivo con
		```Powershell
		> vitis -i
		```

1. Abrir el entorno de trabajo (workspace) Vitis Unified con
	```Powershell
	> vitis -w ./workspace
	```

## Más información

- [Documentación Oficial - Vitis Scripting](https://github.com/Xilinx/Vitis-Tutorials/tree/2023.2/Embedded_Software/Feature_Tutorials/04-vitis_scripting_flows)

# Regeneración automatizada de proyectos en Vitis desde script `.tcl`

1. Ejecute el archivo `.bat` [_VITIS_PROJECT_GENERATOR](_VITIS_PROJECT_GENERATOR.bat). Desde Windows Powershell, ingrese:
```powershell
& "./_VITIS_PROJECT_GENERATOR"
```
2. Ingrese el archivo `.tcl` correspondiente al proyecto a generar
3. Seleccione las alternativas que la consola le pregunta.
4. Abrir Vitis, e importar el proyecto generado desde la carpeta [workspace](./workspace/). En adelante, el proyecto estará en la ruta `workspace` auxiliar, pero el código fuente linkeado desde la carpeta [src](../src/) será actualizado.

# Descripción de proyectos en Vitis

## Aplicación [SW_Zedboard_test_decxnpc.tcl](./SW_Zedboard_test_decxnpc.tcl)

### Descripción

Aplicación que utiliza el hardware [HW_Zedboard_test_decxnpc.xsa](../../Vivado/xsa_hardware/HW_Zedboard_test_decxnpc.xsa) sintetizado desde el archivo [HW_Zedboard_testdecxnpc.tcl](../../Vivado/projects/HW_Zedboard_test_decxnpc.tcl) para modular 3L-(X)NPC-VSC desde el SoC Zynq 7000 de la plataforma Zedboard

### Autores

* [Alan Wilson](mailto:alan.wilson@usm.cl)

### Archivos dependientes

* [SW_Zedboard_test_decxnpc.tcl](./SW_Zedboard_test_decxnpc.tcl): Script `.tcl` desde donde se regenera el proyecto.
* [helloworld.c](../src/helloworld.c): Código fuente con el código a ejecutar, linkeado virtualmente desde la carpeta [src](../src/)
* [HW_Zedboard_test_decxnpc.xsa](../../Vivado/xsa_hardware/HW_Zedboard_test_decxnpc.xsa): Archivo con el empaquetamiento de hardware (plataforma) necesario para que la aplicación corra en el hardware implementado.