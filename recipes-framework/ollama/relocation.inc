export sites = "golang.org/x/exp:golang.org/x/exp:force \
           golang.org/x/net:golang.org/x/net:force \
           golang.org/x/sys:golang.org/x/sys:force \
           gopkg.in/yaml.v3:gopkg.in/yaml.v3:force \
           golang.org/x/sync:golang.org/x/sync:force \
           golang.org/x/arch:golang.org/x/arch:force \
           golang.org/x/term:golang.org/x/term:force \
           golang.org/x/text:golang.org/x/text:force \
           golang.org/x/image:golang.org/x/image:force \
           golang.org/x/tools:golang.org/x/tools:force \
           github.com/kr/text:github.com/kr/text:force \
           gonum.org/v1/gonum:gonum.org/v1/gonum:force \
           github.com/xtgo/set:github.com/xtgo/set:force \
           gorgonia.org/vecf32:gorgonia.org/vecf32:force \
           gorgonia.org/vecf64:gorgonia.org/vecf64:force \
           golang.org/x/crypto:golang.org/x/crypto:force \
           github.com/chewxy/hm:github.com/chewxy/hm:force \
           golang.org/x/xerrors:golang.org/x/xerrors:force \
           github.com/pkg/errors:github.com/pkg/errors:force \
           github.com/google/uuid:github.com/google/uuid:force \
           github.com/spf13/cobra:github.com/spf13/cobra:force \
           github.com/rivo/uniseg:github.com/rivo/uniseg:force \
           github.com/spf13/pflag:github.com/spf13/pflag:force \
           github.com/x448/float16:github.com/x448/float16:force \
           github.com/gin-gonic/gin:github.com/gin-gonic/gin:force \
           github.com/google/go-cmp:github.com/google/go-cmp:force \
           github.com/chewxy/math32:github.com/chewxy/math32:force \
           github.com/gogo/protobuf:github.com/gogo/protobuf:force \
           github.com/goccy/go-json:github.com/goccy/go-json:force \
           github.com/pdevine/tensor:github.com/pdevine/tensor:force \
           github.com/cloudwego/iasm:github.com/cloudwego/iasm:force \
           github.com/leodido/go-urn:github.com/leodido/go-urn:force \
           github.com/golang/protobuf:github.com/golang/protobuf:force \
           github.com/dlclark/regexp2:github.com/dlclark/regexp2:force \
           github.com/davecgh/go-spew:github.com/davecgh/go-spew:force \
           github.com/bytedance/sonic:github.com/bytedance/sonic:force \
           github.com/gin-contrib/sse:github.com/gin-contrib/sse:force \
           github.com/mattn/go-isatty:github.com/mattn/go-isatty:force \
           google.golang.org/protobuf:google.golang.org/protobuf:force \
           github.com/stretchr/testify:github.com/stretchr/testify:force \
           github.com/gin-contrib/cors:github.com/gin-contrib/cors:force \
           github.com/json-iterator/go:github.com/json-iterator/go:force \
           github.com/d4l3k/go-bfloat16:github.com/d4l3k/go-bfloat16:force \
           github.com/emirpasic/gods/v2:github.com/emirpasic/gods/v2:force \
           github.com/cloudwego/base64x:github.com/cloudwego/base64x:force \
           github.com/containerd/console:github.com/containerd/console:force \
           github.com/mattn/go-runewidth:github.com/mattn/go-runewidth:force \
           github.com/google/flatbuffers:github.com/google/flatbuffers:force \
           github.com/pmezard/go-difflib:github.com/pmezard/go-difflib:force \
           github.com/klauspost/cpuid/v2:github.com/klauspost/cpuid/v2:force \
           github.com/modern-go/reflect2:github.com/modern-go/reflect2:force \
           github.com/ugorji/go/codec:github.com/ugorji/go/codec/codec:force \
           github.com/nlpodyssey/gopickle:github.com/nlpodyssey/gopickle:force \
           github.com/agnivade/levenshtein:github.com/agnivade/levenshtein:force \
           github.com/modern-go/concurrent:github.com/modern-go/concurrent:force \
           github.com/pelletier/go-toml/v2:github.com/pelletier/go-toml/v2:force \
           github.com/go-playground/locales:github.com/go-playground/locales:force \
           github.com/olekukonko/tablewriter:github.com/olekukonko/tablewriter:force \
           go4.org/unsafe/assume-no-moving-gc:go4.org/unsafe/assume-no-moving-gc:force \
           github.com/gabriel-vasile/mimetype:github.com/gabriel-vasile/mimetype:force \
           github.com/inconshreveable/mousetrap:github.com/inconshreveable/mousetrap:force \
           github.com/apache/arrow/go/arrow:github.com/apache/arrow/go/arrow/go/arrow:force \
           github.com/bytedance/sonic/loader:github.com/bytedance/sonic/loader/loader:force \
           github.com/twitchyliquid64/golang-asm:github.com/twitchyliquid64/golang-asm:force \
           github.com/go-playground/validator/v10:github.com/go-playground/validator/v10:force \
           github.com/go-playground/universal-translator:github.com/go-playground/universal-translator:force"

do_compile:prepend() {
    cd ${S}/src/import
    for s in $sites; do
        site_dest=$(echo $s | cut -d: -f1)
        site_source=$(echo $s | cut -d: -f2)
        force_flag=$(echo $s | cut -d: -f3)

        mkdir -p vendor.copy/$site_dest

        # create a temporary exclude file
        exclude_file=$(mktemp)

        find vendor.fetch/$site_source -type d -print0 |         xargs -0 du -sBM 2>/dev/null |         awk '{if ($1+0 > 500) print substr($0, index($0,$2))}' |         sed 's|^vendor.fetch/||' > "$exclude_file"

        if [ -n "$force_flag" ]; then
            echo "[INFO] $site_dest: force copying .go files"
            rm -rf vendor.copy/$site_dest
            rsync -a                 --exclude='vendor/'                 --exclude='.git/'                 --exclude-from="$exclude_file"                 vendor.fetch/$site_source/ vendor.copy/$site_dest
        else
            if [ -n "$(ls -A vendor.copy/$site_dest/*.go 2> /dev/null)" ]; then
                echo "[INFO] vendor.fetch/$site_source -> $site_dest: go copy skipped (files present)"
                true
            else
                echo "[INFO] $site_dest: copying .go files"
                rsync -a                     --exclude='vendor/'                     --exclude='.git/'                     --exclude-from="$exclude_file"                     vendor.fetch/$site_source/ vendor.copy/$site_dest
            fi
        fi

        rm -f "$exclude_file"
    done
}
