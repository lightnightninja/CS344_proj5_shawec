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
s.send(bytes("\"report\"", 'ASCII'))

x = s.recv(size) #should be conecction message
print(x)
json = s.recv(size).decode() #this should be the string
print(json)
pattern = re.compile(':([0-9]+),')
active = 0
lifeProc = 0
maxChecked =0 
avgTime= 0
found = 0
threads = []
#thread{PID:{"ops":num, "time":num, "calced":num}

js = re.sub(r'"', r"'", json)
pattern = re.compile(r'(\'[a-zA-z0-9]+)\'\s*:\s*([0-9])')
threadpat = re.compile(r'(\"[0-9]+\"\s*:([\[\:\"\,]*[0-9a-zA-Z]+[\:\"\,]+[0-9a-zA-Z]+)*\])')
j = list(js)

for i in threadpat.finditer(js):
	j = list(i.group())

#j = dict([(i.group(1),i.group(2))] )
print (j)
Jlist = {}
#s = JSON
Jlist = dict(e.split(':') for e in js.split(','))
jlist = re.findall(pattern, js)
jdict = {c:b for a,b,c in my_list}
#for things in Jlist:
#	things = re.sub(r'\"|\{', r'', things)

#print Jlist

if len(sys.argv) < 2:
	s.send(bytes("\"alive\"", 'ascii'))
	
else:
	if sys.argv[1]:
		s.send(bytes("\"quit\"", 'ascii'))
		print("everyone must die!")
	
s.close()