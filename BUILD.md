# Build and Run
## 1. Clone away
```
$ mkdir <project>
$ cd <project>
$ git clone --branch main https://github.com/hongxu-jia/meta-ollama.git
$ git clone --branch master https://git.yoctoproject.org/poky
```

## 2. Prepare build
```
$ . <project>/poky/oe-init-build-env <build>

# Build qemux86-64 with systemd.
$ echo 'MACHINE = "qemux86-64"' >> conf/local.conf
$ echo 'INIT_MANAGER = "systemd"' >> conf/local.conf

# Enable ollama feature
$ echo 'DISTRO_FEATURES_NATIVE:append = " ollama"' >> conf/local.conf
$ echo 'IMAGE_INSTALL:append = " deepseek-r1-7b"' >> conf/local.conf

# Add layer meta-ollama to build
$ bitbake-layers add-layer <project>/meta-ollama
```

## 3. Build image
```
cd <build>
$ bitbake core-image-minimal
```

## 4. Start qemu with slrip + kvm + 10GB memory:
```
$ runqemu tmp/deploy/images/qemux86-64/core-image-minimal-qemux86-64.rootfs.qemuboot.conf slirp kvm qemuparams="-m 10240"
```

## 5. Run deepseek-r1:7b model
```
root@qemux86-64:~# systemctl status ollama
* ollama.service - Ollama Service
     Loaded: loaded (/usr/lib/systemd/system/ollama.service; enabled; preset: enabled)
     Active: active (running) since Fri 2025-03-07 13:51:48 UTC; 8s ago
 Invocation: 7e9d8924ee9f4ffcbb2bdd65800e9545
   Main PID: 254 (ollama)
      Tasks: 8 (limit: 12019)
     Memory: 33.2M (peak: 33.5M)
        CPU: 310ms
     CGroup: /system.slice/ollama.service
             `-254 /usr/bin/ollama serve

Mar 07 13:51:48 qemux86-64 ollama[254]: [GIN-debug] POST   /api/embeddings           --> github.com/ollama/ollama/server.(*Server).EmbeddingsHandler-fm (5 handlers)
Mar 07 13:51:48 qemux86-64 ollama[254]: [GIN-debug] POST   /v1/chat/completions      --> github.com/ollama/ollama/server.(*Server).ChatHandler-fm (6 handlers)
Mar 07 13:51:48 qemux86-64 ollama[254]: [GIN-debug] POST   /v1/completions           --> github.com/ollama/ollama/server.(*Server).GenerateHandler-fm (6 handlers)
Mar 07 13:51:48 qemux86-64 ollama[254]: [GIN-debug] POST   /v1/embeddings            --> github.com/ollama/ollama/server.(*Server).EmbedHandler-fm (6 handlers)
Mar 07 13:51:48 qemux86-64 ollama[254]: [GIN-debug] GET    /v1/models                --> github.com/ollama/ollama/server.(*Server).ListHandler-fm (6 handlers)
Mar 07 13:51:48 qemux86-64 ollama[254]: [GIN-debug] GET    /v1/models/:model         --> github.com/ollama/ollama/server.(*Server).ShowHandler-fm (6 handlers)
Mar 07 13:51:48 qemux86-64 ollama[254]: time=2025-03-07T13:51:48.859Z level=INFO source=routes.go:1256 msg="Listening on 127.0.0.1:11434 (version 0.0.0)"
Mar 07 13:51:48 qemux86-64 ollama[254]: time=2025-03-07T13:51:48.860Z level=INFO source=gpu.go:217 msg="looking for compatible GPUs"
Mar 07 13:51:48 qemux86-64 ollama[254]: time=2025-03-07T13:51:48.872Z level=INFO source=gpu.go:377 msg="no compatible GPUs were discovered"
Mar 07 13:51:48 qemux86-64 ollama[254]: time=2025-03-07T13:51:48.872Z level=INFO source=types.go:130 msg="inference compute" id=0 library=cpu variant="" compute="" dr...able="9.6 GiB"
Hint: Some lines were ellipsized, use -l to show in full.

root@qemux86-64:~# ollama list
NAME              ID              SIZE      MODIFIED     
deepseek-r1:7b    0a8c26691023    4.7 GB    13 years ago    

root@qemux86-64:~# ollama run deepseek-r1:7b
>>> Send a message (/? for help)
```

