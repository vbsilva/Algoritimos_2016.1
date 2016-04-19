class bolas():
	def __init__(self):
		self.__vet = []

	def insertBall(self, w):
		self.__vet.append(w)

	def getVal(self, v):
		return self.__vet[v]

	def sort(self):
		self.__vet.sort()




class jogador():
	def __init__(self):
		self.__score = 0

	def getScore(self):
		return self.__score
	
	def setScore(self, n, v, b):
		l = 0; r = n-1;

		while l <= r:
			m = int((l+r)/2)
			if v == b.getVal(m):
				return m

			elif v < b.getVal(m):
				r = m-1

			elif v > b.getVal(m):
				l = m+1

	def addScore(self, v):
		self.__score += v




def main():
	caso = 0
	while(True):
		try:
			n = input()
			if n == "":
				n = input()	
		except EOFError:
			break

		m = int(n.split()[1])
		k = int(n.split()[2])
		p = int(n.split()[3])
		a = int(n.split()[4])
		n = int(n.split()[0])

		print("caso {}:".format(caso), end="")
		caso += 1

		b = bolas()
		j = []

		for x in range(0,n):
			aux = int(input())
			b.insertBall(aux)

		b.sort()

		for i in range(0,p):
			for t in range(0,k):
				aux = int(input())
				j.append(jogador())
				j[i].addScore(j[i].setScore(n, aux, b))

			#print("jogador {}: {}".format(i, j[i].getScore()))	
			if j[i].getScore() == a:
				print (" {}".format(i), end ="")

		print(""); print("");



if __name__ == '__main__':
	main()