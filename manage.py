#!/usr/bin/env python

#####################################
#  Name : Cierra Shawe				
#  Date : Tue Aug 11				
#  Proj : Assignment 5				
#  Class: CS344						
#####################################

import select
import socket
import sys
import threading
import os
import re

##Globals##
host = 'localhost'	#Just setting this for local use
port = 4936			#two squared numbers that add up to prime :D
SIZE = 1024 		#should be big enough, if not i'll make it bigger
activeProc = 0
lifeProc = 0
numChecked = 0
maxNum = 0
numFound = 0
avgTime = 0
maxNum = 0
counter = 0
kill = False

class Server:
	def __init__(self):
		self.host = host 	#Just setting this for local use
		self.port = port	#two squared numbers that add up to prime :D
		self.size = SIZE 	#should be big enough, if not i'll make it bigger
		self.server = None 	#we dont' have a server yet
		self.pid = os.getpid()	#Uninitizlied
		self.threads = [] 	#holds array of threads
		print "Opening connection..."
		
		
	def open_socket(self):
		try:
			self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.server.bind((self.host, self.port))
			self.server.listen(5)
		except socket.error, (value,message):
			print "Error opening socket :/"
			if self.server:
				self.server.close()
			sys.exit(1)

	# Handles everything going on
	def run(self):
		self.open_socket()
		input = [self.server, sys.stdin]
		running = 1
		try:
			while running:	
				inputready, outputready, exceptready = select.select(input,[],[])
				for s in inputready:
					if s == self.server:
						# handle the server socket
						(client, (ip, port)) = self.server.accept()
						c = Client(ip, port, client)
						c.start()
						self.threads.append(c)

					elif s == sys.stdin:
						# handle standard input
						junk = sys.stdin.readline()
						print junk 
						running = 0 
		except KeyboardInterrupt:
			print "exiting now."
		except socket.error, msg:
			print "Socket error! %s" % msg

		# close all threads
		
		for c in self.threads:
			c.join()
			c.client.close()
		self.server.close()
		sys.stdout.flush() #this way we're not printing extra stuff for not reason

class Client(threading.Thread):
	def __init__(self, ip, port, client):
		threading.Thread.__init__(self)
		self.address = ip
		self.port = port
		self.size = SIZE
		self.pid = os.getpid()
		self.client = client
		self.type = 'NULL'
		
	def run(self):
		running = 1
		self.client.send("Connection openened!") #let's us see that compute connected
		clienttype = self.client.recv(self.size) #asks for the client type
		
		self.type = re.sub(r'[:{}"]+', r'', clienttype)
		print "client type: " + self.type
		
		print "[+] New thread started for " + self.type + ", PID: " + str(self.pid)
		while running:
			d = self.client.recv(self.size)
			data = d.decode('ascii')
			if data:
				self.client.send("data recieved!")
				print data
			else:
				self.client.close()
				running = 0
				print "client closed."

def main():
	s = Server()
	s.run()

if __name__ == "__main__":
	main()
	
