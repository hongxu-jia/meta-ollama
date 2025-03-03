HOMEPAGE = "https://ollama.com/library/deepseek-r1"
SUMMARY = "DeepSeek's first-generation of reasoning models with comparable \
performance to OpenAI-o1, including six dense models distilled from \
DeepSeek-R1 based on Llama and Qwen."
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${DL_DIR}/sha256-${LICESE_SHA256};md5=140979a28c4181c91b6216add7b69045"

BPN = "deepseek-r1"

PARAMS_SHA256 = "f4d24e9138dd4603380add165d2b0d970bef471fac194b436ebd50e6147c6588"
LICESE_SHA256 = "6e4c38e1172f42fdbff13edf9a7a017679fb82b0fde415a3e8b3c31c6ed4a4e4"
TEMPLATE_SHA256 = "369ca498f347f710d068cbb38bf0b8692dd3fa30f30ca2ff755e211c94768150"

inherit ollama-model
