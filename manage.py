#!/usr/bin/env python

"""
Name : Cierra Shawe
Date : Tue Aug 11
Proj : Assignment 5
Class: CS344
"""

import select
import socket
import sys
import threading

class Server:
	def __init__(self):
		self.host = 'localhost'
		self.port = 4936
		self.backlog = 5
		self.size = 1024
		self.server = None
		self.threads = []
		

	def open_socket(self):
		try:
			self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			self.server.bind((self.host,self.port))
			self.server.listen(5)
		except socket.error, (value,message):
			if self.server:
				self.server.close()
			print "Could not open socket: " + message
			sys.exit(1)

	def run(self):
		self.open_socket()
		input = [self.server,sys.stdin]
		running = 1
		while running:
			inputready,outputready,exceptready = select.select(input,[],[])

			try:
				for s in inputready:
					if s == self.server:
						# handle the server socket
						c = Client(self.server.accept())
						c.start()
						self.threads.append(c)

					elif s == sys.stdin:
						# handle standard input
						junk = sys.stdin.readline()
						print junk
						running = 0 
			except KeyboardInterrupt:
				print "exiting now."
				break; 
				
					
		# close all threads
		self.server.close()
		for c in self.threads:
			c.join()

class Client(threading.Thread):
	def __init__(self, (client, address)):
		threading.Thread.__init__(self)
		self.client = client
		self.address = address
		self.size = 1024

	def run(self):
		print "New client"
		running = 1
		while running:
			data = self.client.recv(self.size)
			try:
				if data:
					self.client.send(data)
					print data
				else:
					self.client.close()
					running = 0
					print "client closed."
			except KeyboardInterrupt:
				print "exiting now."
				running = 0;

if __name__ == "__main__":
	s = Server()
	s.run()

