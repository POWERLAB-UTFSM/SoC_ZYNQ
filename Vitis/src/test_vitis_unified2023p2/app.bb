#
# This file is the app recipe.
#

SUMMARY = "Simple app application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://app.elf \
	"

S = "${WORKDIR}"

INSANE_SKIP:${PN} = "arch"
RDEPENDS:${PN} += " \
libmetal \
"

do_install() {
	install -d ${D}${base_libdir}/firmware
	install -m 0644 ${S}/app.elf ${D}${base_libdir}/firmware/app.elf
}

FILES:${PN} = "${base_libdir}/firmware/app.elf"