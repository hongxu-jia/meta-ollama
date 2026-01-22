do_install:append () {
    rm -f ${D}${libdir}/${TARGET_SYS}/${baselib}/libgcc_s.so*
}
