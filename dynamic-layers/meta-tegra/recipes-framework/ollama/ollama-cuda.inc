FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += " \
    file://0001-support-cross-compiling.patch \
"

inherit cuda

PRIVATE_LIBS:${PN} = "libcublas.so.12 libcublasLt.so.12 libcudart.so.12"
INSANE_SKIP:${PN} += "already-stripped buildpaths"
