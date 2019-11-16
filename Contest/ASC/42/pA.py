N = 61
dp1 = [0 for i in range(N + 1)]
dp2 = [0 for i in range(N)]

a = [[0 for i in range(N)] for i in range(N)]
b = [[0 for i in range(N)] for i in range(N)]

a[0][0] = b[0][0] = dp1[1] = dp2[0] = 1

def gcd(a, b) :
    while b != 0 :
        a, b = b, a % b
    return a

def C(n, m) :
    res = 1
    for i in range(m) :
        res = res * (n - i) // (i + 1)
    return res

def H(n, m) :
    return C(n + m - 1, m)

for i in range(1, N) :
    for j in range(1, i + 1) :
        for k in range(i) :
            a[i][k + 1] += a[i - j][k] * dp1[j]

    for j in range(1, i + 1) :
        tmp = 0
        for k in range(j) :
            d = gcd(k, j)
            if i % (j // d) == 0 :
                t = i // (j // d)
                tmp += a[t][d] 
        tmp //= j
        dp2[i] += tmp

    for j in range(1, i + 1) :
        for k in range(1, i // j + 1) :
            tmp = 0
            for l in range(j) :
                tmp += b[i - j * k][l] 
            b[i][j] += tmp * H(dp2[j], k) 
        dp1[i + 1] += b[i][j]

for i in range(1, N) :
    print('"%d",' % dp2[i])
