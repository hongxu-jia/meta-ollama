# Build and Run ollama with CUDA for x86-64
## 1. Clone away
```
$ mkdir <project>
$ cd <project>
$ git clone --branch main https://github.com/hongxu-jia/meta-ollama.git
$ git clone --branch master git://git.openembedded.org/openembedded-core oe-core
$ git clone --branch master git://git.openembedded.org/bitbake oe-core/bitbake
$ git clone --branch master git://git.yoctoproject.org/meta-yocto
$ git clone --branch master https://github.com/OE4T/meta-tegra.git
```

## 2. Prepare build
```
$ . <project>/oe-core/oe-init-build-env <build>

# Build genericx86-64 with systemd. 
$ echo 'MACHINE = "genericx86-64"' >> conf/local.conf
$ echo 'INIT_MANAGER = "systemd"' >> conf/local.conf

# Enable ollama feature for cmake-native
$ echo 'DISTRO_FEATURES_NATIVE:append = " ollama"' >> conf/local.conf

# Enable cuda for x86-64
$ echo 'require conf/distro/include/cuda-x86-64.inc' >> conf/local.conf

# Install gemma2:2b model 
# https://ollama.com/library/gemma2:2b 
$ echo 'IMAGE_INSTALL:append = " gemma2-2b"' >> conf/local.conf

# Generate wic.zst image 
$ echo 'IMAGE_FSTYPES += "wic.zst"' >> conf/local.conf

# Add layer meta-ollama to build 
$ bitbake-layers add-layer <project>/meta-ollama

# Add layer meta-yocto to build 
$ bitbake-layers add-layer <project>/meta-yocto/meta-yocto-bsp

# Add layer meta-tegra to build 
$ bitbake-layers add-layer <project>/meta-tegra
```

## 3. Build image
```
cd <build>
$ bitbake core-image-minimal

# Extract wic image
$ unzstd tmp/deploy/images/genericx86-64/core-image-minimal-genericx86-64.rootfs.wic.zst

## 4. Burn USB stick
# Plug in USB stick and umount
$ sudo umount /dev/sdX

# Burn image
$ sudo dd if=tmp/deploy/images/genericx86-64/core-image-minimal-genericx86-64.rootfs.wic of=/dev/sdX
```

## 4. Boot x86-64 board from USB stick
```
Last login: Wed Jan 28 05:02:27 2026 from 128.224.34.164
root@genericx86-64:~# 
```

## 5. Run gemma2:2b model
```
root@genericx86-64:~# systemctl status ollama
● ollama.service - Ollama Service
     Loaded: loaded (/usr/lib/systemd/system/ollama.service; enabled; preset: enabled)
     Active: active (running) since Wed 2026-01-28 05:01:33 UTC; 35min ago
 Invocation: bb2c22b5b1084fe3bc99a406f309622e
TriggeredBy: ● ollama.path
   Main PID: 373 (ollama)
      Tasks: 14 (limit: 76913)
     Memory: 1.7G (peak: 2G)
        CPU: 25.793s
     CGroup: /system.slice/ollama.service
             └─373 /usr/bin/ollama serve

Jan 28 05:05:38 genericx86-64 ollama[373]: [GIN] 2026/01/28 - 05:05:38 | 200 | 48.334870965s |       127.0.0.1 | POST     "/api/generate"
Jan 28 05:07:10 genericx86-64 ollama[373]: [GIN] 2026/01/28 - 05:07:10 | 200 |  605.647173ms |       127.0.0.1 | POST     "/api/chat"
Jan 28 05:07:14 genericx86-64 ollama[373]: [GIN] 2026/01/28 - 05:07:14 | 200 |      23.668µs |       127.0.0.1 | HEAD     "/"
Jan 28 05:07:14 genericx86-64 ollama[373]: [GIN] 2026/01/28 - 05:07:14 | 200 |      50.532µs |       127.0.0.1 | GET      "/api/ps"
Jan 28 05:07:37 genericx86-64 ollama[373]: [GIN] 2026/01/28 - 05:07:37 | 200 |    2.0415891s |       127.0.0.1 | POST     "/api/chat"
Jan 28 05:07:54 genericx86-64 ollama[373]: [GIN] 2026/01/28 - 05:07:54 | 200 |  8.594067789s |       127.0.0.1 | POST     "/api/chat"
Jan 28 05:07:59 genericx86-64 ollama[373]: [GIN] 2026/01/28 - 05:07:59 | 200 |      20.445µs |       127.0.0.1 | HEAD     "/"
Jan 28 05:07:59 genericx86-64 ollama[373]: [GIN] 2026/01/28 - 05:07:59 | 200 |      14.962µs |       127.0.0.1 | GET      "/api/ps"
Jan 28 05:12:54 genericx86-64 ollama[373]: time=2026-01-28T05:12:54.068Z level=INFO source=server.go:429 msg="starting runner" cmd="/usr/bin/ollama runner --ollama-engine --port 44607"
Jan 28 05:12:54 genericx86-64 ollama[373]: time=2026-01-28T05:12:54.477Z level=INFO source=server.go:429 msg="starting runner" cmd="/usr/bin/ollama runner --ollama-engine --port 34029"

root@genericx86-64:~# ollama list
NAME         ID              SIZE      MODIFIED     
gemma2:2b    8ccf136fdd52    1.6 GB    14 years ago

root@genericx86-64:~# ollama run gemma2:2b
>>> do you know yocto project?
Yes, I know about the Yocto Project! 

**What is the Yocto Project?**

The Yocto Project is an open-source framework for building and customizing embedded Linux systems.  It's used extensively by developers to create custom operating system images, deploy onto devices like microcontrollers, single-board 
computers (SBCs), and other embedded hardware, and to manage device-specific software components. 

**Key Features:**

* **Modular Design:** Yocto breaks down the system into manageable modules, making it easy to adapt for different target platforms and use cases.
* **Cross-platform:** It's used on multiple architectures (x86, ARM, MIPS) and can be easily adapted for various device types. 
* **Open Source:** The core components are completely open source, allowing collaboration and contribution from the wider community.
* **Comprehensive Toolchain:**  It provides a comprehensive set of tools to build an OS, including build automation scripts, compilers, and packaging systems.

**Where is Yocto Used?**

The Yocto Project finds application in various fields: 

* **Embedded Systems Development:** Creating custom operating systems for diverse devices like IoT devices, medical devices, industrial control systems.
* **Device-specific Software:**  Packaging software tailored to specific hardware platforms.
* **Software Engineering & Research:**  Facilitating reproducible and customizable environments for testing and prototyping.
* **Corporate Innovation:**  Building custom operating systems to suit individual needs and requirements.

**How Yocto Works:**

1. **Project Setup:** You define your target device, its specifications, and desired software components. 
2. **Component Management:** Yocto provides a library of "bitbake" files that list the necessary software packages for your project (e.g., kernel, libraries, application software). 
3. **Build Automation:**  Yocto uses tools to automatically download, compile, and package these components into an image suitable for your target device. 


**I can help you with Yocto in various ways:**

* Explain specific Yocto concepts like bitbake or recipes.
* Offer guidance on how to start using Yocto for a project.
* Help understand the process of building custom Linux images.
* Discuss best practices and common problems encountered during the Yocto development process.


**How can I assist you with Yocto today?** Do you have any specific questions or tasks in mind?  Let me know! 

>>> Send a message (/? for help)
```

## 6. Verify CUDA with NVIDIA GPU is supported
```
root@genericx86-64:~# ollama ps
NAME         ID              SIZE      PROCESSOR    CONTEXT    UNTIL              
gemma2:2b    8ccf136fdd52    2.6 GB    100% GPU     4096       4 minutes from now

root@genericx86-64:~# nvidia-smi 
Wed Jan 28 05:40:31 2026       
+-----------------------------------------------------------------------------------------+
| NVIDIA-SMI 590.48.01              Driver Version: 590.48.01      CUDA Version: 13.1     |
+-----------------------------------------+------------------------+----------------------+
| GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
|                                         |                        |               MIG M. |
|=========================================+========================+======================|
|   0  NVIDIA RTX A400                Off |   00000000:01:00.0 Off |                  N/A |
| 30%   41C    P8            N/A  /   50W |    2576MiB /   4094MiB |      0%      Default |
|                                         |                        |                  N/A |
+-----------------------------------------+------------------------+----------------------+

+-----------------------------------------------------------------------------------------+
| Processes:                                                                              |
|  GPU   GI   CI              PID   Type   Process name                        GPU Memory |
|        ID   ID                                                               Usage      |
|=========================================================================================|
|    0   N/A  N/A             669      C   /usr/bin/ollama                        2570MiB |
+-----------------------------------------------------------------------------------------+
```
