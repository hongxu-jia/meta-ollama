DESCRIPTION = "NVIDIA Linux Driver"
SECTION = "nvidia/drivers"
LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://LICENSE;md5=92aa2e2af6aa0bcba1c3fe49da021937"

inherit nvidia-driver-x86-64 systemd

SRC_URI[sha256sum] = "7e66ff6c8318f3f981d442d7451c791fb1e9cf05f45648a3f081242d056dde4f"

SRC_URI += " \
    file://nvidia-device.service \
"

SRC_SUBDIR += "bin sbin"

SRCNAME = "nvidia_driver"

RDEPENDS:${PN} = " \
    pciutils \
"

NVIDIA_DRIVERS ?= " \
    libnvidia-ml \
    libcuda \
    libcudadebugger \
    libnvidia-nvvm \
    libnvidia-gpucomp \
    libnvidia-ptxjitcompiler \
"

do_install:append () {
    install -d ${D}${base_libdir}/firmware/nvidia/${PV}
    cp ${S}/firmware/* ${D}${base_libdir}/firmware/nvidia/${PV}
    for cuda_lib in $(ls ${D}${base_libdir}/lib*.so.${PV}); do
        # Create libXXX.so.1 -> libXXX.so.${PV}
        sym_link=$(echo $cuda_lib | sed 's/\(.*\.so\)\.\(.*\)/\1.1/')
        ln -snf ${cuda_lib##*/} $sym_link
    done
    ln -snf /lib ${D}/lib64

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${UNPACKDIR}/nvidia-device.service ${D}${systemd_unitdir}/system
}

FILES:${PN} += " \
    ${base_libdir}/nvidia_drv.so \
    ${base_libdir}/firmware \
    /lib64 \
    ${systemd_unitdir} \
"
SYSTEMD_SERVICE:${PN} = "nvidia-device.service"
