# meta-ollama

## Overview
```
Get up and running with large language models. 
(https://ollama.com/)

This layer integrates ollama to OE/Yocto platform
```

## Prerequisite(s)
### 1. Based on Yocto
Yocto layer dependencies
```
URI: git://github.com/openembedded/openembedded-core.git
branch: master
revision: HEAD

URI: git://github.com/openembedded/bitbake.git
branch: master
revision: HEAD

URI: git://git.yoctoproject.org/meta-yocto optional for genericx86-64
branch: master
revision: HEAD

URI: https://github.com/OE4T/meta-tegra.git optional for CUDA with NVIDIA GPU
branch: master
revision: HEAD

```

## Project License
```
Copyright (C) 2026 Wind River Systems, Inc.

All metadata is MIT licensed unless otherwise stated. Source code included
in tree for individual recipes is under the LICENSE stated in each recipe
(.bb file) unless otherwise stated.
```

## Legal Notices
```
If product is based on Wind River Linux:

All product names, logos, and brands are property of their respective owners.
All company, product and service names used in this software are for identification
purposes only. Wind River are registered trademarks of Wind River Systems.

Disclaimer of Warranty / No Support: Wind River does not provide support and
maintenance services for this software, under Wind River’s standard Software
Support and Maintenance Agreement or otherwise. Unless required by applicable
law, Wind River provides the software (and each contributor provides its
contribution) on an “AS IS” BASIS, WITHOUT WARRANTIES OF ANY KIND, either express
or implied, including, without limitation, any warranties of TITLE, NONINFRINGEMENT,
MERCHANTABILITY, or FITNESS FOR A PARTICULAR PURPOSE. You are solely responsible
for determining the appropriateness of using or redistributing the software
and assume ay risks associated with your exercise of permissions under the license.
```

## Build
See BUILD.md and BUILD-cuda-x86-64.md for detail

## Maintainer
See MAINTAINERS.md for detail
layer maintainer: Hongxu Jia <hongxu.jia@windriver.com>

## Send patch
See MAINTAINERS.md for detail
