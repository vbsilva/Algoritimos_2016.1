class MyClass():
	def __init__(self):
		self._nome = ""
	def setNome(self, nome):
		self._nome = nome;
	def getNome(self):
		return self._nome


def main():
	x = MyClass()
	x.setNome("olar mundo!")
	print(x.getNome())


if __name__ == "__main__":
	main()