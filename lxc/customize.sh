#!/system/bin/sh -eu
SKIPUNZIP=0

# Set permissions
for file in $MODPATH/post-fs-data.sh \
            $MODPATH/system/bin/* \
            $MODPATH/system/libexec/lxc/lxc-* \
            $MODPATH/system/libexec/lxc/hooks/* \
            $MODPATH/system/share/lxc/hooks/* \
            $MODPATH/system/share/lxc/templates/*; do

  ui_print "- Setting permissions for $file"
  set_perm $file 0 0 0755
done