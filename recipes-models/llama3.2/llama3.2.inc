HOMEPAGE = "https://ollama.com/library/llama3.2"
SUMMARY = "The Meta Llama 3.2 collection of multilingual large language models \
(LLMs) is a collection of pretrained and instruction-tuned generative models in \
1B and 3B sizes (text in/text out)."
LICENSE = "LLAMA-3.2 & LLAMA-3.2-2"
NO_GENERIC_LICENSE[LLAMA-3.2] = "sha256-${LICESE_SHA256}"
NO_GENERIC_LICENSE[LLAMA-3.2-2] = "sha256-${LICESE_2_SHA256}"
LIC_FILES_CHKSUM = "file://sha256-${LICESE_SHA256};md5=f8d143628e4773e848402cebd9b250f2 \
                    file://sha256-${LICESE_2_SHA256};md5=423c3b7ac3dfdf9c524afcef8eeaf5a2 \
"
BPN = "llama3.2"

LICESE_SHA256 = "fcc5a6bec9daf9b561a68827b67ab6088e1dba9d1fa2a50d7bbcc8384e0a265d"
LICESE_2_SHA256 = "a70ff7e570d97baaf4e62ac6e6ad9975e04caa6d900d3742d37698494479e0cd"
TEMPLATE_SHA256 = "966de95ca8a62200913e3f8bfbf84c8494536f1b94b49166851e76644e966396"
inherit ollama-model

SRC_URI += " \
    ${OLLAMA_URI}/blobs/sha256-${LICESE_2_SHA256};name=license-2; \
"

SRC_URI[license-2.sha256sum] = "${LICESE_2_SHA256}"

do_install:append() {
    for blob_sha256 in ${LICESE_2_SHA256}; do
        install -m 0644 ${DL_DIR}/sha256-$blob_sha256 ${D}${datadir}/ollama/models/blobs/
    done
    chown -R ollama:ollama ${D}${datadir}/ollama
}

FILES:${PN}-common += " \
    ${datadir}/ollama/models/blobs/sha256-${LICESE_2_SHA256} \
    ${datadir}/ollama/models/blobs/sha256-${TEMPLATE_SHA256} \
"
