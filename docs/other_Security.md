---
aside: false
---

# Other built-in protections

## Devices in /dev

For /dev, ruri will only create necessary devices on it, so that block devices will always be unavailable in container, and as cap_mknod and cap_sys_admin is dropped by default, you can not escape from ruri container by modifying disk partitions.

## Masked dirs

Ruri will mask some directories with tmpfs in /proc and /sys, this can protect the host to avoid security issues.

## Capabilities

Ruri will drop unneeded capabilities by default, so that it can avoid escaping from container
