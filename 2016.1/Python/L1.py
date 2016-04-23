from collections import deque

class Galpao():
	def __init__(self):
		self.__sum = 0
		self.__queue = deque ([])
		
	def incSum(self, w):
		self.__sum +=  w

	def decSum(self, w):
		self.__sum -= w

	def getSum(self):
		return self.__sum

	def insertQueue(self, w):
		self.__queue.append(w)

	def removeQueue(self):
		self.__queue.popleft()

	def getQueue(self):
		return self.__queue

	def reInit(self):
		self.__sum = 0
		self.__queue = deque ([])

class Caminhao():
	def __init__(self):
		self.__sum = 0
		self.__capacity = 0
		self.__stack = []

	def incSum(self, w):
		self.__sum +=  w

	def decSum(self, w):
		self.__sum -= w

	def getSum(self):
		return self.__sum

	def setCapacity(self, w):
		self.__capacity = w

	def getCapacity(self):
		return self.__capacity

	def insertStack(self, w):
		self.__stack.append(w)

	def removeStack(self):
		if len(self.__stack) > 0:
			aux = self.__stack.pop()
			self.__sum -= aux

	def getStack(self):
		return self.__stack

	def loa(self, g):
		while(len(g.getQueue()) > 0):
			x = g.getQueue()[0]
			if(x + self.__sum <= self.__capacity):
				self.__sum += x
				g.decSum(x)
				self.__stack.append(x)
				g.removeQueue()
			else:
				break;


def main():
	end = False; firstTime = True;
	g = Galpao()
	c = []

	while(not end):
		if firstTime :
			n = int(input())
			#print(n)
			firstTime = False

		c = []
		g.reInit()
		for x in range(0,int(n)):
			c.append(Caminhao())
			cap = int(input())
			c[x].setCapacity(cap)
			
		while True:
			try:
				str = input()
				if str != "":
					op = int(str.split()[1])
					str = str.split()[0]			
			except EOFError:
				end = True
				break;
			
			#import pdb; pdb.set_trace();
			if str == "ADD":
				#op = int(input())
				g.incSum(op)
				g.insertQueue(op)
				print("{} {}".format(len(g.getQueue() ), g.getSum() ))

			elif str == "LOA":
				#op = int(input())
				c[op].loa(g)
				print("{} {}".format(op, len(c[op].getStack())))

			elif str == "DEL":
				#op = int(input())
				c[op].removeStack()
				print("{} {}".format(op, len(c[op].getStack())))

			elif str == "INF":
				print("{} {} {}".format(op, len(c[op].getStack()), c[op].getSum()))
	
			else:
				if str == "":
					n = int(input())
					print("")
					#print("n: "),
					#print(n)
					break;















if __name__ == '__main__':
	main()