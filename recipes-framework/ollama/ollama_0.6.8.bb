HOMEPAGE = "https://ollama.com"
SUMMARY = "Get up and running with large language models."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://src/import/LICENSE;md5=a8abe7311c869aba169d640cf367a4af"

# Specify the first two important SRCREVs as the format
SRCREV_FORMAT = "ollama_cgroups"
SRCREV_ollama = "6a74bba7e7e19bf5f5aeacb039a1537afa3522a5"

SRC_URI = " \
    git://github.com/ollama/ollama.git;name=ollama;branch=main;protocol=https;destsuffix=${GO_SRCURI_DESTSUFFIX} \
    file://ollama.service \
    file://modules.txt \
"

include src_uri.inc
inherit go goarch
inherit systemd cmake useradd

GO_IMPORT = "import"

DEPENDS += " \
    rsync-native \
"

OECMAKE_SOURCEPATH = "${S}/src/import"

export OECMAKE_FORCE_CROSSCOMPILING = '1'

PIEFLAG = "${@bb.utils.contains('GOBUILDFLAGS', '-buildmode=pie', '-buildmode=pie', '', d)}"

do_compile:append() {

    cd ${S}/src/import

    # Pass the needed cflags/ldflags so that cgo
    # can find the needed headers files and libraries
    export GOARCH=${TARGET_GOARCH}
    export CGO_ENABLED="1"
    export CGO_CFLAGS="${CFLAGS} --sysroot=${STAGING_DIR_TARGET}"
    export CGO_LDFLAGS="${LDFLAGS} --sysroot=${STAGING_DIR_TARGET}"

    export GOFLAGS="-mod=vendor -trimpath ${PIEFLAG}"

    # our copied .go files are to be used for the build
    ln -sf vendor.copy vendor
    # inform go that we know what we are doing
    cp ${UNPACKDIR}/modules.txt vendor/

    ${GO} build -v ${GOBUILDFLAGS} -o ${B}/bin/ollama
}

do_install:append() {
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${UNPACKDIR}/ollama.service ${D}${systemd_unitdir}/system

    install -d ${D}/${bindir}
    install ${B}/bin/ollama ${D}/${bindir}
}

FILES:${PN} += "${systemd_unitdir} ${nonarch_libdir}/ollama"

USERADD_PACKAGES = "${PN}"
USERADD_PARAM:${PN} = " \
    --system --shell /bin/false \
    --user-group --groups video,render \
    --create-home --home-dir /usr/share/ollama \
    ollama"
GROUPADD_PARAM:${PN} = "-r render"

INSANE_SKIP:${PN} += "libdir"
INSANE_SKIP:${PN}-dbg += "libdir"

SYSTEMD_SERVICE:${PN} = "ollama.service"

include relocation.inc
