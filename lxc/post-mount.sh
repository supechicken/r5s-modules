#!/system/bin/sh -eu

[ ! -f /data/no-lxc ] && lxc-autostart --groups autoboot
