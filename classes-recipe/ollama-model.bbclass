OLLAMA_URI = "https://registry.ollama.ai/v2/library/${BPN}"

MODEL_TAG ??= "${PV}"

SRC_URI = " \
    ${OLLAMA_URI}/manifests/${MODEL_TAG};name=manifest; \
    ${OLLAMA_URI}/blobs/sha256-${IMAGE_JSON_SHA256};name=image_json; \
    ${OLLAMA_URI}/blobs/sha256-${PARAMS_SHA256};name=params; \
    ${OLLAMA_URI}/blobs/sha256-${LICESE_SHA256};name=license; \
    ${OLLAMA_URI}/blobs/sha256-${TEMPLATE_SHA256};name=template; \
    ${OLLAMA_URI}/blobs/sha256-${MODEL_SHA256};name=model; \
"

SRC_URI[manifest.sha256sum] = "${MANIFEST_SHA256}"
SRC_URI[image_json.sha256sum] = "${IMAGE_JSON_SHA256}"
SRC_URI[params.sha256sum] = "${PARAMS_SHA256}"
SRC_URI[license.sha256sum] = "${LICESE_SHA256}"
SRC_URI[template.sha256sum] = "${TEMPLATE_SHA256}"
SRC_URI[model.sha256sum] = "${MODEL_SHA256}"

RDEPENDS:${PN} = " \
    ollama \
"

S = "${DL_DIR}"

do_unpack[noexec] = "1"
do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    install -d ${D}${datadir}/ollama/models/manifests/registry.ollama.ai/library/${BPN}
    install -m 0644 ${DL_DIR}/${MODEL_TAG} ${D}${datadir}/ollama/models/manifests/registry.ollama.ai/library/${BPN}/

    install -d ${D}${datadir}/ollama/models/blobs/
    for blob_sha256 in ${IMAGE_JSON_SHA256} ${PARAMS_SHA256} ${LICESE_SHA256} ${TEMPLATE_SHA256} ${MODEL_SHA256}; do
        install -m 0644 ${DL_DIR}/sha256-$blob_sha256 ${D}${datadir}/ollama/models/blobs/
    done
    chown -R ollama:ollama ${D}${datadir}/ollama
}

inherit useradd

USERADD_PACKAGES = "${PN} ${PN}-common"
USERADD_PARAM:${PN} = " \
    --system --shell /bin/false \
    --user-group --groups video,render \
    --create-home --home-dir /usr/share/ollama \
    ollama"
USERADD_PARAM:${PN}-common = " \
    --system --shell /bin/false \
    --user-group --groups video,render \
    --create-home --home-dir /usr/share/ollama \
    ollama"
GROUPADD_PARAM:${PN} = "-r render"
GROUPADD_PARAM:${PN}-common = "-r render"

PACKAGES =+ "${PN}-common"
FILES:${PN}-common = " \
    ${datadir}/ollama/models/blobs/sha256-${LICESE_SHA256} \
"
RPROVIDES:${PN}-common += "${BPN}-common"
RDEPENDS:${PN} += "${BPN}-common"

FILES:${PN} += "${datadir}"

PACKAGE_ARCH = "all"

inherit allarch
