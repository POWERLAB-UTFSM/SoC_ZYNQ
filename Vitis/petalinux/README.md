# Petalinux

## Contenidos
1. [Requisitos](#requisitos)
1. [Instalación](#instalación-de-instalacion_petalinuxrun)
1. [Creación de proyectos Petalinux](#creación-de-proyectos-y-aplicaciones-con-petalinux)
1. [Windows Subsystem for Linux (WSL)](#instalar-petalinux-en-wsl-windows-subsystem-for-linux)
1. [Links adicionales](#links-adicionales-con-más-información)

## Requisitos:

- PC y distribución de Linux compatible con Petalinux. [Más informacion](https://docs.amd.com/r/en-US/ug1144-petalinux-tools-reference-guide/Installation-Requirements).
- Descargar Petalinux [desde este link](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools.html).

## Instalación de ``<instalacion_petalinux>.run``

```bash
foo@bar:~$ cd ~ #ir a carpeta de usuario principal
foo@bar:~$ mkdir petalinux #crear directorio
foo@bar:~$ cd petalinux #ir a directorio
foo@bar:~$ cp </path/to/instalacion_petalinux.run> . #copiar archivo a actual ruta
foo@bar:~$ chmod +x <instalacion_petalinux>.run #transformar en ejecutable
foo@bar:~$ ./<instalacion_petalinux>.run #instalar ejecutable
foo@bar:~$ source settings.sh #ejecutar script
```

## Creación de proyectos y aplicaciones con Petalinux

1. Habilitar el uso de comandos de Petalinux, ejecutando en la carpeta de instalación:
    ```bash
    foo@bar:~$ source settings.sh
    ```

1. Generar Proyecto Petalinux de nombre ``< NOMBRE_DEL_PROYECTO >`` (el nombre no debe llevar espacio ni barra baja [``_``]) con el comando
    ```bash
    foo@bar:~$ petalinux-create --type project --template zynq --name < NOMBRE_DEL_PROYECTO >
    ```

1. Ir a la carpeta del proyecto y configurar según el BSP ``< NOMBRE_DEL_ARCHIVO_DE_HARDWARE.xsa >``:
    ```bash
    foo@bar:~$ cd < NOMBRE_DEL_PROYECTO >
    foo@bar:~$ petalinux-config --get-hw-description < RUTA/NOMBRE_DEL_ARCHIVO_DE_HARDWARE.xsa >
    ```

1. De la ventana de configuración de ``petalinux-config``, agregue el argumento extra ``clk_ignore_unused`` en
    ```
    DTG settings -> 
        Kernel Bootargs extra -> 
            "clk_ignore_unused"
    ```
    Lo anterior, para asegurarse de no desactivar los relojes de los periféricos de la lógica programable (PL) no utilizados directamente desde Linux (OpenAMP, por ejemplo).

    - Opcional: Se puede cambiar la configuración de inicio para que quede el sistema de archivos ``root`` en la unidad SD en vez de cargarlo en RAM (``INITRD``, por defecto en Zynq7)
        ```
        Image Package Configuration ->
            Root filesystem type ->
                ( ) INITRD
                (X) EXT4 (SD/eMMC/SATA/USB)
        ```
    - Opcional: Se puede cambiar la configuración de Ethernet para deahabilitar la IP automática (DHCP) y fijar una estática:
        ```
        Subsystem AUTO Hardware Settings ->
            Ethernet Settings ->
                [ ] Obtain IP address automatically
                (xxx.xxx.xxx.xxx) Static IP address
                (255.255.255.0) Static IP netmask
                (xxx.xxx.xxx.xxx) Static IP gateway
        ```

1. Crear Aplicación Petalinux de nombre ``<app-name>`` (el nombre no debe llevar espacio ni barra baja [``_``])
    ```bash
    foo@bar:~$ petalinux-create -t apps --template install -n <app-name> --enable
    ```

1. Copiar firmware de aplicación a ejecutar de forma independiente (``.elf``) en la carpeta ``project-spec/meta-user/recipes-apps/<app-name>/files/``
    ```bash
    foo@bar:~$ cp <path/to/elf> project-spec/meta-user/recipes-apps/<app-name>/files/
    ```

1. Modificar el archivo ``project-spec/meta-user/recipes-apps/<app_name>/<app_name>.bb``. de manera que el ejecutable ``.elf``, de nombre ``<app_name>.elf``, se ubique en la carpeta de Linux ``\lib\firmware``. Como ejemplo:

    ```
    #
    # This file is the app recipe.
    #

    SUMMARY = "Simple app application"
    SECTION = "PETALINUX/apps"
    LICENSE = "MIT"
    LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

    SRC_URI = "file://<app_name>.elf \
        "

    S = "${WORKDIR}"

    INSANE_SKIP:${PN} = "arch"
    RDEPENDS:${PN} += " \
    libmetal \
    "

    do_install() {
        install -d ${D}${base_libdir}/firmware
        install -m 0644 ${S}/app.elf ${D}${base_libdir}/firmware/<app_name>.elf
    }

    FILES:${PN} = "${base_libdir}/firmware/<app_name>.elf"
    ```

1. Configurar el Kernel de Petalinux (toma tiempo) con el comando
    ```bash
    foo@bar:~$ petalinux-config -c kernel
    ```
    Y asegúrese que esté configurado modularmente (``<M>``) los drivers:
    ```
    Device Drivers ->
        Remoteproc drivers ->
            <M> Support ZYNQ remoteproc
        Rpmsg drivers ->
            <M> RPMSG device interface
            <M> RPMSG control interface
    ```

1. Configurar el sistema de archivos de ``root`` con
    ```bash
    foo@bar:~$ petalinux-config -c rootfs
    ```
    Y seleccione según preferencias

1. Configurar el árbol de dispositivos con
    ```bash
    foo@bar:~$ petalinux-config -c device-tree
    ```
    Y seleccione según preferencias

1. Modifique el árbol de dispositivos ubicado en ``project-spec/meta-user/recipes-bsp/device-tree/files/system-user.dtsi``, según las necesidades y requerimientos. Como ejemplo, para utilizar OpenAMP/Remoteproc y ejecutar su firmware en la otra CPU de una SoC ZYNQ 7000:
    ```
    /include/ "system-conf.dtsi"
    / {
        reserved-memory {
            #address-cells = <1>;
            #size-cells = <1>;
            ranges;
            rproc_0_reserved: rproc@1f000000 {
                no-map;
                compatible = "shared-dma-pool";
                reg = <0x1f000000 0x00100000>;
            };
            vdev0vring0: vdev0vring0@1f100000 {
                no-map;
                compatible = "shared-dma-pool";
                reg = <0x1f100000 0x4000>;
                };
            vdev0vring1: vdev0vring1@1f104000 {
                no-map;
                compatible = "shared-dma-pool";
                reg = <0x1f104000 0x4000>;
                };
            vdev0buffer: vdev0buffer@1f108000 {
                no-map;
                compatible = "shared-dma-pool";
                reg = <0x1f108000 0x100000>;
            };
        };
        /*amba {
            elf_ddr_0: ddr@0 {
                compatible = "mmio-sram";
                reg = <0x1f000000 0x00100000>;
            };
        };*/
        remoteproc0: remoteproc@0 {
            compatible = "xlnx,zynq_remoteproc";
            firmware = "firmware";
            vring0 = <15>;
            vring1 = <14>;
            memory-region = <&rproc_0_reserved>, <&vdev0buffer>, <&vdev0vring0>, <&vdev0vring1>;
            interrupt-parent = <&intc>; 
        };
    };
    /*DTG settings -> Kernel Bootargs extra -> "clk_ignore_unused" */
    &gpio0 {
        status = "disabled";
    };
    &axi_cpwm8c_0 {
        status = "disabled";
    };
    &axi_dec3lxnpc_0 {
        status = "disabled";
    };
    &axi_dec3lxnpc_1 {
        status = "disabled";
    };
    &axi_cdma_0 {
        status = "disabled";
    };
    ```
    - Si utiliza ``remoteproc`` para multiproceso asimétrico (AMP), asegúrese que la memoria del nodo ``rproc_0_reserved`` concuerde con el espacio de memoria utilizado en la aplicación paralela ``<app_name>.elf``, configurado en el archivo ``lscript.ld`` del proyecto de aplicación, y con la cantidad de memoria disponible en su SoC. El ejemplo consecuente, de utilizar solo la memoria DDR, para una tarjeta de desarrollo Zedboard de 512MB de RAM, sería:
        ```
        ps7_ddr_0 : ORIGIN = 0x1f000000, LENGTH = 0x00100000
	    ps7_ram_0 : ORIGIN = 0x0, LENGTH = 0x30000
	    ps7_ram_1 : ORIGIN = 0xffff0000, LENGTH = 0xfe00
        ```
    - Si utiliza un periférico ``<p_node0>`` en su aplicación ``<app_name>.elf`` vía ``remoteproc``, deshabilítelos de Petalinux desde ``system-user.dtsi``, mediante:
        ```
        &<p_node0> {
            status = "disabled";
        };
        ```
        Esos nodos dentro de su proyecto están definidos en los archivos ``dts`` y ``dtsi`` ubicados en ``components/plnx_workspace/device-tree``.

1. Construya su proyecto ejecutando
    ```bash
    foo@bar:~$ petalinux-build
    ```

1. Cree los archivos de Petalinux que irán a su tarjeta SD, mediante
    ```bash
    foo@bar:~$ petalinux-package --boot --fsbl images/linux/zynq_fsbl.elf --fpga images/linux/system.bit --u-boot --force
    ```
    - Opcional: De querer colocar el sistema de archivos ``root`` en SD en vez de RAM, se recomienda generar, después de ``petalinux-package``, una imagen ``.wic`` mediante
        ```bash
            foo@bar:~$ petalinux-package --wic
        ```
    y esa imagen se puede grabar en creadores de discos de boot, como [Rufus](https://rufus.ie/) para Windows.

1. Mueva los archivos creados en ``images/linux`` a su tarjeta SD.
    - Para ejecutar en RAM, copie los siguientes archivos en la partición "boot" (Fat32):
        - BOOT.bin
        - image.ub
        - image.src

1. Inserte su disco SD en su SoC. La primera vez, se pedirá crear una contraseña de usuario ``petalinux``:
    ```
    login: petalinux
    pass: <propia_password>
    ```

## Instalar Petalinux en WSL (Windows Subsystem for Linux)

Petalinux puede ser instalado desde una máquina virtual con [Windows Subsystem for Linux](https://learn.microsoft.com/en-us/windows/wsl/about), en vez de instalar físicamente Linux o mediante una máquina virtual tradicional.

- **Nota:** WSL tiene limitaciones respecto de una instalación full de Linux como:
    - Por defecto no instala entorno gráfico de escritorio (si se quiere ejecutar Vitis desde Linux).
    - Falta de acceso a drivers USB (JTAG, USB Disc Drivers, etc.).
    - No se puede debuggear vía JTAG.

### Pasos de instalación:

1. Habilitar WSL (más detalles ver [aquí](https://learn.microsoft.com/en-us/windows/wsl/install-manual#step-3---enable-virtual-machine-feature))
    1. Habilitar Hyper-V (Turn Windows features on-off)
    1. Si no se permite por firmware, habilitar virtualización de CPU en la BIOS

1. Instalar Ubuntu WSL (más información [aquí](https://learn.microsoft.com/en-us/windows/wsl/install))

    ```powershell
    wsl --install --distribution Ubuntu-22.04
    ```

1. Después de instalar, entrar a WSL

    ```powershell
    wsl
    ```

1. Configurar

    ```bash
    sudo dpkg --add-architecture i386
    sudo apt-get update
    sudo locale-gen en_US.UTF-8
    sudo dpkg-reconfigure dash
    ```

1. Instalar dependencias (ver [aquí](https://support.xilinx.com/s/article/000035006?language=en_US))
    ```bash
    sudo apt-get install iproute2 gawk python3 python-is-python3 build-essential gcc git make net-tools libncurses5-dev tftpd zlib1g-dev libssl-dev flex bison libselinux1 gnupg wget git-core diffstat chrpath socat xterm autoconf libtool tar unzip texinfo zlib1g-dev gcc-multilib automake zlib1g:i386 screen pax gzip cpio python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev bc libtinfo5
    ```

1. Actualizar (opcional)
    ```bash
    sudo apt-get upgrade
    ```

1. Descargar Petalinux [aquí](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools.html)

1. Copiar archivo e instalar (en este caso, la versión ``petalinux-v2023.1-05012318-installer.run``)

    ```bash
    cd ~ #ir a carpeta de usuario principal
    mkdir petalinux #crear directorio
    cd petalinux #ir a directorio
    cp </path/to/source.run> . #copiar archivo a actual ruta
    chmod +x petalinux-v2023.1-05012318-installer.run #transformar en ejecutable
    ./petalinux-v2023.1-05012318-installer.run #instalar ejecutable
    source settings.sh #ejecutar script
    ```

## Links adicionales con más información:

* [PetaLinux Tools Documentation: Reference Guide (UG1144)](https://docs.xilinx.com/r/en-US/ug1144-petalinux-tools-reference-guide)
* [000035006 - PetaLinux 2023.1 - Product Update Release Notes and Known Issues](https://support.xilinx.com/s/article/000035006?language=en_US)
* [Libmetal y OpenAMP user guide (UG1186)](https://docs.xilinx.com/r/en-US/ug1186-zynq-openamp-gsg)