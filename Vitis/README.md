# Administración de proyectos en Vitis IDE

# Creación de proyectos y aplicaciones con Petalinux

1. Generar Proyecto Petalinux (el nombre no debe llevar espacio ni barra baja [``_``])
    ```bash
    foo@bar:~$ petalinux-create --type project --template zynq --name < NOMBRE_DEL_PROYECTO >
    foo@bar:~$ cd < NOMBRE_DEL_PROYECTO >
    foo@bar:~$ petalinux-config --get-hw-description < RUTA/NOMBRE_DEL_ARCHIVO_DE_HARDWARE.xsa >
    ```

1. Generar Aplicación Petalinux (el nombre no debe llevar espacio ni barra baja [``_``])
    ```bash
    foo@bar:~$ petalinux-create -t apps --template install -n <app-name> --enable
    ```

1. Copiar firmware (``.elf``) en la carpeta ``project-spec/meta-user/recipes-apps/<app-name>/files/``
    ```bash
    foo@bar:~$ cp <path/to/elf> project-spec/meta-user/recipes-apps/<app-name>/files/
    ```

1. Modificar el archivo ``project-spec/meta-user/recipes-apps/<app_name>/<app_name>.bb``. Como ejemplo:

    ```
    Recipe needs to be changed due to syntax changes in yocto

    Please use recipe content below

    SUMMARY = "Simple freertos-amp-demos application"

    SECTION = "PETALINUX/apps"

    LICENSE = "MIT"

    LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

    SRC_URI = "file://<myfirmware> \

    "

    S = "${WORKDIR}"

    INSANE_SKIP:${PN} = "arch"

    RDEPENDS:${PN} += " \

    libmetal \

    "

    do_install() {

    install -d ${D}${base_libdir}/firmware

    install -m 0644 ${S}/<myfirmware> ${D}${base_libdir}/firmware/<myfirmware>

    }

    FILES:${PN} = "${base_libdir}/firmware/<myfirmware>"

    ```


# Instalar Petalinux en WSL (Windows Subsystem for Linux)

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

Más información:

* [PetaLinux Tools Documentation: Reference Guide (UG1144)](https://docs.xilinx.com/r/en-US/ug1144-petalinux-tools-reference-guide)
* [000035006 - PetaLinux 2023.1 - Product Update Release Notes and Known Issues](https://support.xilinx.com/s/article/000035006?language=en_US)
* [Libmetal y OpenAMP user guide (UG1186)](https://docs.xilinx.com/r/en-US/ug1186-zynq-openamp-gsg)