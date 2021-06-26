#/bin/sh

ADC0=/sys/bus/iio/devices/iio:device0/in_voltage0_raw

while [ 1 ] ; do cat $ADC0 ;done
