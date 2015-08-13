#!/usr/bin/env python3

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
quit = False

def JSONparse(data):
	pass
	
def JSONformat(dict):
	pass
	

def getRange(ops):
	global numChecked
	counter = 0
	with mutex:
		i, end, temp, start = numChecked, numChecked, numChecked, numChecked
		while ((i>>2) + temp) < ops:
			counter += 1
			temp += i;
			i += 1;
		numChecked += counter+1
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
		print ("Opening connection...")
		
		
	def open_socket(self):
		try:
			self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.server.bind((self.host, self.port))
			self.server.listen(5)
		except SocketError:
			print ("Error opening socket :/")
			if self.server:
				self.server.close()
			sys.exit(1)

	# Handles everything going on
	def run(self):
		self.open_socket()
		input = [self.server, sys.stdin]
		self.running = 1
		global lifeProc
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
						lifeProc += 1
						
					elif s == sys.stdin:
						# handle standard input
						junk = sys.stdin.readline()
						self.running = 0 
						
		except KeyboardInterrupt:
			print()
			print ("RAMPAGEEEEEEEEEEEE.")
			
		except SocketError:
			print ("Socket error! %s" % msg)
		except quit == True:
			print ("Time to die!")

		# close all threads
		try:
			for c in self.threads:
				if c.is_alive():
					c.client. send(bytes(("\"die\""), 'ascii'))
				c.running = 0
				if c.is_alive():
					c.join()
		finally:
			self.server.close()
		
		sys.stdout.flush() #this way we're not printing extra stuff for no reason

class Client(threading.Thread):
	def __init__(self, ip, port, client):
		threading.Thread.__init__(self)
		self.address = ip
		self.port = port
		self.size = SIZE
		self.pid = int(os.getpid() + lifeProc)
		self.client = client
		self.type = 'NULL'
		
		self.running = 1
		self.ops = 1250000000
		self.seconds = 15
		self.loops = 0
		self.avgtime = 0
		self.calced = 0
	
		
	def run(self):
		global maxNum
		self.client.send(bytes('Connection opened!', 'ascii'))
		typ = self.client.recv(self.size).decode() #asks for the client type
		self.type = re.sub(r'[:{}"]+', r'', typ)
		print ("[+] New instance of " + self.type + ", PID: " + str(self.pid))
		
		if re.match(r'compute', self.type):
			while self.running == 1:
				start, end = getRange(self.ops)
				args = '{' + '\"start\":' + str(start) + ',' + '\"end\":' + str(end) + '}'
				print (args)
				self.client.send(bytes((args), 'ascii'))
				d = self.client.recv(self.size)
				data = d.decode('ascii')
				if data:
					dat = data.strip('\0')
					self.ops = int(dat)
					print (self.ops)
					seconds = 15
					self.loops += 1
					self.seconds += seconds
					self.avgtime += self.seconds/self.loops
					if end > maxNum:
						maxNum = end
					self.calced += end - start
					#items = JSONparse(data)
				else:
					self.running = 0
					self.client.close()
					print ("Client closed.")
					
		elif re.match(r'report', self.type):
			global activeProc, lifeProc, quit
			
			lifeProc 	-= 1 # this is because we don't need it to count itself
			activeProc 	= len(s.threads)
			
			stuff = '{\"active\":' + str(activeProc) + ',\"lifeProc\":' + str(lifeProc) + ',\"calced":' + str(maxNum) + ',\"threads\":{'
			for thing in s.threads:
				if not s.threads[0]:
					stuff += ','
				if thing.is_alive() and thing is not self:
					opssec = int((thing.ops/thing.seconds + 0.5)/1000000)
					stuff += '\"' + str(thing.pid) + '\":{\"ops\":' + str(opssec) + ',\"time\":' + str(self.avgtime) + ',\"procd\":' + str(self.calced) + '}'
					
			stuff += '}}'
			self.client.send(bytes((stuff), 'ascii'))
			k = self.client.recv(self.size)
			kill = k.decode('ascii')
			if kill == '\"quit\"':
				quit = True
				
				
				
if __name__ == "__main__":
	s = Server()
	s.run()
	print ("Everyone is dead. Good job.")
	
