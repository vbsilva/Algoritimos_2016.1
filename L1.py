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

	def insQueue(self, w):
		self.__queue.append(w)

	def rmQueue(self):
		self.__queue.popleft()

	def getQueue(self):
		return self.__queue


def main():
	newCase = False; firstTime = True
	g = Galpao()

	while(not newCase):
		if firstTime :
			n = int(input())
			firstTime = False


		for x in range(0,int(n)):
			print(x)
		while True:
			str = input()
			if str == "ADD":
				op = int(input())
				g.incSum(op)
				g.insQueue(op)
				print(g.getQueue())

			elif str == "LOA":
				op = int(input())

			elif str == "DEL":
				op = int(input())

			elif str == "INF":
				op = int(input())
			elif str == "QUIT":
				newCase = True
				break	
			else:
				op = int(input())















if __name__ == '__main__':
	main()