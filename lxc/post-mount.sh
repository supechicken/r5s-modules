#!/system/bin/sh -eu

if [ -b /dev/block/nvme0n1p1 ] && [ -b /dev/block/mmcblk0p1 ]; then
  mount /dev/block/nvme0n1p1 /data/local
  mount /dev/block/mmcblk0p1 /data/sdcard
fi

if [ ! -f /data/no-lxc ]; then
  lxc-start openwrt || true
  lxc-start ubuntu || true
fi