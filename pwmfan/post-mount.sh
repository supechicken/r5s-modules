#!/system/bin/sh -eu
exec > /data/pwmfan.log 2>&1

echo 'step_wise' > /sys/class/thermal/thermal_zone0/policy
echo '5500'      > /sys/class/thermal/thermal_zone0/trip_point_3_hyst
echo '3000'      > /sys/class/thermal/thermal_zone0/trip_point_4_hyst
echo '30000'     > /sys/class/thermal/thermal_zone0/trip_point_3_temp
echo '50000'     > /sys/class/thermal/thermal_zone0/trip_point_4_temp

nohup /data/adb/modules/pwmfan/system/bin/pwmfan &
