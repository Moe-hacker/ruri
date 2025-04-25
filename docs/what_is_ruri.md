---
aside: false
---

# what's ruri

ruri is pronounced as `luli`, or you can call it `[瑠璃/琉璃]` ~~(るり)~~ in Chinese or Japanese as well.

ruri is acronym to Lightweight, User-friendly Linux-container Implementation.

ruri is a powerful container implementation that runs on almost any Linux device, even with incomplete kernel configurations or minimal storage space.

## Why ruri

- Powerful Features

  - Basic container features are all supported, chroot, unshare with pivot_root, capability control, basic cgroup support, no_new_privs, auto set environment variables and change user/workdir, built-in seccomp profile, and more...
  - Built-in support for binfmt_misc & QEMU, so you can run multi-arch container easily.
  - Built-in rootless mode support (need user ns support).
  - Powerful mount option, you can mount image/partition as root, and you can choose every mountpoint to be read-only or rw.
  - Built-in support for config file.

- Ultra-lightweight, Zero runtime Dependencies, Ready Out-of-the-Box

  - Only rootless container need an optional runtime dependency `uidmap`, all feature of chroot/unshare container can be built-in to an all-in-one binary.
  - Ruri provides statically linked binaries for arm64, armv7, armhf, riscv64, i386, loong64, s390x, ppc64le and x86_64 devices.
  - The binary of ruri is very small, after upx, it can even be less than 200k, but it can provide over 30 options and even more features.

- Flexibility, for More Platform

  - From Android devices to IoT gadgets, from amd64 to s390x, ruri can provide basic container support on almost every Linux platforms, the only thing it need is root privilege.

- Secure by Design

  - Built-in rootless container support.
  - Built-in security options, to make container more secure.
  - Built-in read-only filesystem options for more protection.

- Simple for Beginner
  - You can just use ruri as an instead of `chroot` command, and ruri will do all things for you.
  - Ruri empowers you with the freedom to configure everything, but that do not means you need to learn every option to use it.
