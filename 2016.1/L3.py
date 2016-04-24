class wordNode(object):
	def __init__(self, word):
		self.__word = word
		self.__size = len(word)
		self.__hashcode = 0
		self.__left = None
		self.__right = None
		self.__occurrence = []

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

		#self.rebalance()

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
					w = wordNode(word)
					w.setHashcode()
					avl.insert(w)







if __name__ == '__main__':
	main()