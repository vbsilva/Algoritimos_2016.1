class Palavras(object):
	def __init__(self, word):
		self.__palavra = word
		self.__size = len(word)
		self.__hashcode = 0

	def getHashcode(self):
		return self.__hashcode

	def setHashcode(self):
		global char_a
		for index, letter in enumerate(self.__palavra, start = 1):
			ordChar = ord(letter) - char_a
			self.__hashcode += (ordChar*(26**(self.__size - index)))



char_a = ord('a')

def main():
	line = input()
	#import pdb; pdb.set_trace();
	if line == "$TEXTO":
		line = input()
		if line == "$CONSULTAS":
			print("todo")
		else:
			for word in line.split():
				w = Palavras(word)
				w.setHashcode()
				print(w.getHashcode())







if __name__ == '__main__':
	main()