#!/usr/bin/env python3

"""
	An echo client that allows the user to send multiple lines to the server.
	Entering a blank line will exit the client.
"""

import socket
import sys
import re

host = 'localhost'
port = 4936
size = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host,port))
s.send(bytes("\"report\"", 'ascii'))

x = s.recv(size) #should be conecction message

JSON = s.recv(size).decode() #this should be the string


pattern = re.compile(r'\"([a-z]+|[0-9]+)\":([0-9]+)')
json = dict([(i.group(1),i.group(2)) for i in pattern.finditer(JSON)])

print(json)
#Jlist = {}
#s = JSON
#Jlist = dict(e.split(':') for e in s.split(','))

#print Jlist

if len(sys.argv) < 2:
	s.send(bytes("\"alive\"", 'ascii')
	
elif sys.argv[1]:
	s.send(bytes("\"quit\"", 'ascii')
	print("everyone must die!")
	
s.close()