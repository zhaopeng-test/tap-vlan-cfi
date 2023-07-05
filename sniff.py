#!/usr/bin/env python3

from scapy.all import *


def pkt_callback(packet):
       packet.show()

sniff(prn=pkt_callback, iface="tap1", count=10, timeout=500)
