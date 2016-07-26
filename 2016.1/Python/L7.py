def backtrack(A, Q, i, p, M, qtd, L):
    if p > Q or qtd + (L - qtd) < M:
        return 0
    if i == L:
        if p <= Q and qtd >= M:
            return 1
        return 0
    retorno = backtrack(A, Q, i + 1, p, M, qtd, L)
    retorno += backtrack(A, Q, i + 1, p + int(A[i]), M, qtd + 1, L)
    return retorno

K = int(raw_input())
raw_input()
casos = 0
while casos < K:
    L = int(raw_input())
    p = raw_input().split(' ')

    MQ = raw_input().split(' ')

    tmp = backtrack(p, int(MQ[1]), 0, 0, int(MQ[0]), 0, L)
    s = 'caso '+ str(casos) + ': ' + str(tmp)
    casos = casos + 1
    print (s)	
    if casos != K:
        raw_input()
