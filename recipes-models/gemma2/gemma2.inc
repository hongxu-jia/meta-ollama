HOMEPAGE = "https://ollama.com/library/gemma2"
SUMMARY = "Google Gemma 2 is a high-performing and efficient model"
LICENSE = "Gemma2"
NO_GENERIC_LICENSE[Gemma2] = "sha256-${LICESE_SHA256}"
LIC_FILES_CHKSUM = "file://sha256-${LICESE_SHA256};md5=6221cfd561a8c353616ebcf1a287b242"
BPN = "gemma2"

PARAMS_SHA256 = "2490e7468436707d5156d7959cf3c6341cc46ee323084cfa3fcf30fe76e397dc"
LICESE_SHA256 = "097a36493f718248845233af1d3fefe7a303f864fae13bc31a3a9704229378ca"

inherit ollama-model
