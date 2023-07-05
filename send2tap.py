#!/usr/bin/env python3

from scapy.all import *

pkt=Ether()/Dot1Q(prio=3,id=1,vlan=1)/IP()/UDP()
pkt.show()

sendp(pkt, iface="tap0")


