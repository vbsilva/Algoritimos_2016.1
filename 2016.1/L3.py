class wordNode(object):
	def __init__(self, word, line):
		self.__word = word
		self.__size = len(word)
		self.__hashcode = 0
		self.__left = None
		self.__right = None
		self.__occurrence = []
		self.__line = line

	def getHashcode(self):
		return self.__hashcode

	def getWord(self):
		return self.__word

	def setHashcode(self):
		global char_a
		for index, letter in enumerate(self.__word, start = 1):
			ordChar = ord(letter) - char_a
			self.__hashcode += (ordChar*(26**(self.__size - index)))


class AVLTree(object):
	def __init__(self):
		self.__node = None
		self.__height = -1
		self.__balance = 0

	def insert(self, wordNode):

		if self.__node == None:
			self.__node = wordNode
			self.__node.__left = AVLTree()
			self.__node.__right = AVLTree()

		elif wordNode.getHashcode() < self.__node.getHashcode():
			self.__node.__left.insert(wordNode)

		elif wordNode.getHashcode() > self.__node.getHashcode():
			self.__node.__right.insert(wordNode)

		elif wordNode.getHashcode() == self.__node.getHashcode():
			if wordNode.getWord() == self.__node.getWord():
				print("todo")
			else:
				print("todo")

		self.rebalance()

	def searchWord(self, wordNode):


	def update_heights(self, recursive = True):
		if self.__node:
			if recursive:
				if self.__node.__left:
					self.__node.__left.update_heights()
				if self.__node.__right:
					self.__node.__right.update_heights()
			self.__height = 1 + max(self.__node.__left.__height, self.__node.__right.__height)
		else:
			self.__height = -1

	def update_balances(self, recursive = True):
		if self.__node:
			if recursive:
				if self.__node.__left:
					self.__node.__left.update_balances()
				if self.__node.__right:
					self.__node.__right.update_balances()
			self.__balance = self.__node.__left.__height - self.__node.__right.__height
		else:
			self.__balance = 0

	def rotate_right(self):
		newRoot = self.__node.__left.__node
		newLeftSub = newRoot.__right.__node
		oldRoot = self.__node

		self.__node = newRoot
		oldRoot.__left.__node = newLeftSub
		newRoot.__right.__node = oldRoot

	def rotate_left(self):
		newRoot = self.__node.__right.__node
		newLeftSub = newRoot.__left.__node
		oldRoot = self.__node

		self.__node = newRoot
		oldRoot.__right.__node = newLeftSub
		newRoot.__left.__node = oldRoot

	def rebalance(self):
		self.update_heights(recursive = False)
		self.update_balances(False)

		while self.__balance < -1 or self.__balance > 1:
			if self.__balance > 1:

				if self.__node.__left.__balance < 0:
					self.__node.__left.rotate_left()
					self.update_heights()
					self.update_balances()

				self.rotate_right()
				self.update_heights()
				self.update_balances()

			if self.__balance < -1:
				if self.__node.__right.__balance > 0:
					self.__node.__right.rotate_right()
					self.update_heights()
					self.update_balances()

				self.rotate_left()
				self.update_heights()
				self.update_balances()

	def inOrderTransverse(self):
		result = []

		if not self.__node:
			return result

		result.extend(self.__node.__left.inOrderTransverse())
		result.append(self.__node)
		result.extend(self.__node.__right.inOrderTransverse())

		return result

char_a = ord('a')

def main():
	avl = AVLTree()
	line = input()
	i = 0
	#import pdb; pdb.set_trace();
	if line == "$TEXTO":
		while True:
			line = input()
			if line == "$CONSULTAS":
				print("todo")
				r = avl.inOrderTransverse()
				for x in r:
					print("{}: {}".format(x.getHashcode(), x.getWord()))
				break
			else:
				i += 1
				for word in line.split():
					w = wordNode(word, i)
					w.setHashcode()
					avl.insert(w)







if __name__ == '__main__':
	main()