# Administración de proyectos en Vitis IDE



# Instalar Petalinux en WSL (Windows Subsystem for Linux)

1. Habilitar WSL (más detalles ver [aquí](https://learn.microsoft.com/en-us/windows/wsl/install-manual#step-3---enable-virtual-machine-feature))
    1. Habilitar Hyper-V (Turn Windows features on-off)
    1. Si no se permite por firmware, habilitar virtualización de CPU en la BIOS
2. Instalar Ubuntu WSL (más información [aquí](https://learn.microsoft.com/en-us/windows/wsl/install))
```powershell
wsl --install --distribution Ubuntu-22.04
```
3. Después de instalar, entrar a WSL
```powershell
wsl
```
4. Configurar WSL

```sh
sudo dpkg --add-architecture i386
```

5. Actualizar apt-get
```sh
sudo apt-get update
```

6. Instalar dependencias 
```sh
sudo apt-get install -y gcc git make net-tools libncursesw5-dev tftpd zlib1g-dev libssl-dev flex bison libselinux1 gnupg wget diffstat chrpath socat xterm autoconf libtool tar unzip texinfo gcc-multilib build-essential libsdl1.2-dev libglib2.0-dev zlib1g:i386 screen pax gzip gawk glibc-doc:i386 locales:i386 ncurses-dev qemu-system-arm:i386 ncurses-dev:i386 libstdc++6:i386 libselinux1:i386 lib32ncurses5-dev
```

```sh
sudo apt-get install iproute2 gawk python3 python build-essential gcc git make net-tools libncurses5-dev tftpd zlib1g-dev libssl-dev flex bison libselinux1 gnupg wget git-core diffstat chrpath socat xterm autoconf libtool tar unzip texinfo zlib1g-dev gcc-multilib automake zlib1g:i386 screen pax gzip cpio python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev pylint3
```

7. Descargar Petalinux [aquí](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools.html)

8. Copiar archivo e instalar

```bash
sudo ln -s /mnt/c/Users/[user]/Downloads ~/WinDownloads
cd ~
mkdir petalinux
cp WinDownloads/petalinux-v2023.1-05012318-installer.run petalinux
cd petalinux
chmod +x petalinux-v2023.1-05012318-installer.run
./petalinux-v2023.1-05012318-installer.run
source settings.sh
```

9. Configurar
```bash
sudo locale-gen en_US.UTF-8
```

10. Generar Proyecto petalinux
```bash
petalinux-create --type project --template zynq --name < NOMBRE_DEL_PROYECTO >

petalinux-config --get-hw-description < NOMBRE_DEL_ARCHIVO_DE_HARDWARE.xsa >
```

Más información:

* [PetaLinux Tools Documentation: Reference Guide (UG1144)](https://docs.xilinx.com/r/en-US/ug1144-petalinux-tools-reference-guide/Overview=)
* [000035006 - PetaLinux 2023.1 - Product Update Release Notes and Known Issues](https://support.xilinx.com/s/article/000035006?language=en_US)