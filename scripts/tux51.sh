#!/bin/bash
/etc/init.d/networking restart
ifconfig eth0 up
ifconfig eth0 172.16.50.1/24
route add -net 172.16.51.0/24 gw 172.16.50.254
route -n
#after route config
route add default gw 172.16.50.254