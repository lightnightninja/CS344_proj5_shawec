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
from multiprocessing import Lock

##Globals##
mutex = Lock()
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

def JSONparse(data):
	pass
	
def JSONformat(dict):
		
	pass
	

def getRange(ops):
	print "I'm actually freaking here"

	global numChecked
	counter = 0
	with mutex:
		start = numChecked
		end = start
		i = start
		temp = end
		while ((i/2) + temp) < ops:
			counter += 1
			temp += i;
			i += 1;
		numChecked += counter
	end += counter

	return start, end

class Server:
	def __init__(self):
		self.host = host 	#Just setting this for local use
		self.port = port	#two squared numbers that add up to prime :D
		self.size = SIZE 	#should be big enough, if not i'll make it bigger
		self.server = None 	#we dont' have a server yet
		self.pid = os.getpid()	#Uninitizlied
		self.threads = [] 	#holds array of threads
		self.running = 1
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
		self.running = 1
		try:
			#remove the input ready part, as it's not important once kill is good
			while self.running == 1:	
				inputready, outputready, exceptready = select.select(input,[],[])
				for s in inputready:
					if s == self.server:
						# handle the server socket
						(client, (ip, port)) = self.server.accept()
						c = Client(ip, port, client)
						c.start()
						self.threads.append(c)
						global lifeProc
						lifeProc += 1

					elif s == sys.stdin:
						# handle standard input
						junk = sys.stdin.readline()
						self.running = 0 
						
		except KeyboardInterrupt:
			print "exiting now."
			for c in self.threads:
				c.running = 0
			
		except socket.error, msg:
			print "Socket error! %s" % msg

		# close all threads

		
		for c in self.threads:
			c.join()
			
		self.server.close()
			
		sys.stdout.flush() #this way we're not printing extra stuff for no reason

class Client(threading.Thread):
	def __init__(self, ip, port, client):
		threading.Thread.__init__(self)
		self.address = ip
		self.port = port
		self.size = SIZE
		self.pid = os.getpid()
		self.client = client
		self.type = 'NULL'
		self.running = 1
		self.ops = 1250000000
	
	
			
	def run(self):
		self.client.send("Connection openened!") #let's us see that compute connected
		typ = self.client.recv(self.size) #asks for the client type
		clienttype = re.sub(r'[:{}"]+', r'', typ)
		self.type= clienttype.decode('ascii')
		print "[+] New instance of " + self.type + ", PID: " + str(self.pid)
		
		while self.running == 1:
			d = self.client.recv(self.size)
			data = d.decode('ascii')
	
			if re.match(r'compute', self.type):
				start, end = getRange(self.ops)
				
			if data:
				if self.running == 0:
					self.client.send("{\"die\"}")
				else:
					self.client.send("data recieved!")
				print data
				#items = JSONparse(data)
				
			else:
				self.running = 0
				self.client.send("{\"die\"}")
				print "client closed."
		self.client.close()

def main():
	s = Server()
	s.run()

if __name__ == "__main__":
	main()
	
