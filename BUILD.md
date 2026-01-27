# Build and Run
## 1. Clone away
```
$ mkdir <project>
$ cd <project>
$ git clone --branch main https://github.com/hongxu-jia/meta-ollama.git
$ git clone --branch master git://git.openembedded.org/openembedded-core oe-core
$ git clone --branch master git://git.openembedded.org/bitbake oe-core/bitbake
```

## 2. Prepare build
```
$ . <project>/oe-core/oe-init-build-env <build>

# Build qemux86-64 with systemd.
$ echo 'MACHINE = "qemux86-64"' >> conf/local.conf
$ echo 'INIT_MANAGER = "systemd"' >> conf/local.conf

# Enable ollama feature for cmake-native
$ echo 'DISTRO_FEATURES_NATIVE:append = " ollama"' >> conf/local.conf

# Install gemma2:2b model
# https://ollama.com/library/gemma2:2b
$ echo 'IMAGE_INSTALL:append = " gemma2-2b"' >> conf/local.conf

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
$ runqemu tmp/deploy/images/qemux86-64/core-image-minimal-qemux86-64.rootfs.qemuboot.conf slirp kvm qemuparams="-m 10240" snapshot
```

## 5. Run gemma2:2b model
```
root@qemux86-64:~# ollama ps
NAME    ID    SIZE    PROCESSOR    CONTEXT    UNTIL 
root@qemux86-64:~# systemctl status ollama
* ollama.service - Ollama Service
     Loaded: loaded (/usr/lib/systemd/system/ollama.service; enabled; preset: enabled)
     Active: active (running) since Thu 2026-01-29 03:27:41 UTC; 14s ago
 Invocation: 8d0adfb243f44029a27da36676d21b98
   Main PID: 257 (ollama)
      Tasks: 9 (limit: 12020)
     Memory: 50.3M (peak: 60.7M)
        CPU: 169ms
     CGroup: /system.slice/ollama.service
             `-257 /usr/bin/ollama serve

Jan 29 03:27:41 qemux86-64 ollama[257]: time=2026-01-29T03:27:41.506Z level=INFO source=routes.go:1614 msg="server config" env="map[CUDA_VISIBLE_DEVICES: GGML_VK_VISIBLE_DEVICES: G...
Jan 29 03:27:41 qemux86-64 ollama[257]: time=2026-01-29T03:27:41.509Z level=INFO source=images.go:499 msg="total blobs: 5"
Jan 29 03:27:41 qemux86-64 ollama[257]: time=2026-01-29T03:27:41.509Z level=INFO source=images.go:506 msg="total unused blobs removed: 0"
Jan 29 03:27:41 qemux86-64 ollama[257]: time=2026-01-29T03:27:41.509Z level=INFO source=routes.go:1667 msg="Listening on 127.0.0.1:11434 (version 0.14.2)"
Jan 29 03:27:41 qemux86-64 ollama[257]: time=2026-01-29T03:27:41.510Z level=INFO source=runner.go:67 msg="discovering available GPUs..."
Jan 29 03:27:41 qemux86-64 ollama[257]: time=2026-01-29T03:27:41.513Z level=INFO source=server.go:429 msg="starting runner" cmd="/usr/bin/ollama runner --ollama-engine --port 32899"
Jan 29 03:27:41 qemux86-64 ollama[257]: time=2026-01-29T03:27:41.580Z level=INFO source=types.go:60 msg="inference compute" id=cpu library=cpu compute="" name=cpu des...able="9.6 GiB"
Jan 29 03:27:41 qemux86-64 ollama[257]: time=2026-01-29T03:27:41.581Z level=INFO source=routes.go:1708 msg="entering low vram mode" "total vram"="0 B" threshold="20.0 GiB"
Jan 29 03:27:49 qemux86-64 ollama[257]: [GIN] 2026/01/29 - 03:27:49 | 200 |      50.854µs |       127.0.0.1 | HEAD     "/"
Jan 29 03:27:49 qemux86-64 ollama[257]: [GIN] 2026/01/29 - 03:27:49 | 200 |     102.923µs |       127.0.0.1 | GET      "/api/ps"
Hint: Some lines were ellipsized, use -l to show in full.

root@qemux86-64:~# ollama list
NAME         ID              SIZE      MODIFIED     
gemma2:2b    8ccf136fdd52    1.6 GB    14 years ago

root@qemux86-64:~# ollama run gemma2:2b
>>> hi, who are you
Hi there! I'm Gemma, an AI assistant created by the Gemma team. 🤖  I'm here to help with any questions or tasks you might have. 😊 What can I do for you today? 


>>> Send a message (/? for help)
>>> /bye
```

## 6. Verify CPU is used
```
root@qemux86-64:~# ollama ps
NAME         ID              SIZE      PROCESSOR    CONTEXT    UNTIL              
gemma2:2b    8ccf136fdd52    2.1 GB    100% CPU     4096       4 minutes from now
```

