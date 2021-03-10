#!/bin/bash
ip1="www.ntcu.edu.tw"
ip2=localhost
zero=0
case ${1} in
	"")
		./getHostaddr
		./getHostname
		./getip ${ip1}
		./getip ${ip2}
		;;
	"addr")
		./getHostaddr
		;;
	"name")
		./getHostname
		;;
	"ip")
		./getip ${2}
		;;
esac	
