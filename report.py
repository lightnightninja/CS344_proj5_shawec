#!/usr/bin/env python

"""
	An echo client that allows the user to send multiple lines to the server.
	Entering a blank line will exit the client.
"""

import socket
import sys

host = 'localhost'
port = 4936
size = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host,port))


while 1:
	# read from keyboard
	sys.stdout.write('%')
	line = sys.stdin.readline()
	if line == '\n':
		break
	s.send(line)
	data = s.recv(size)
	sys.stdout.write(data)
s.close()