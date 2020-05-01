import fractions
from fractions import Fraction

dp = []
n = 16
mx_inv = n * (n - 1) // 2
for i in range(n + 1): dp.append([Fraction(0, 1)] * (mx_inv + 1))
dp[0][0] = Fraction(1, 1)
for i in range(1, n + 1):
    for j in range(0, mx_inv + 1):
        for k in range(i):
            if j - k >= 0:
                dp[i][j] += dp[i - 1][j - k]
        dp[i][j] /= i

z = int(input())
for t in range(z):
    n, a, b, c, d = map(int, input().split())
    mx_inv = n * (n - 1) // 2
    ex = [Fraction(0, 1)] * (mx_inv + 1)
    ex_pre = [Fraction(0, 1)] * (mx_inv + 2)
    pr_pre = [Fraction(0, 1)] * (mx_inv + 2)
    for i in range(mx_inv + 1):
        cost = min(a * i, a * (mx_inv - i) + b)
        ex[i] = cost * dp[n][i]
        ex_pre[i + 1] = ex_pre[i] + ex[i]
        pr_pre[i + 1] = pr_pre[i] + dp[n][i]
    ans = (Fraction(int(1e9), 1), -1, -1)
    for l in range(1, mx_inv + 1):
        for r in range(l, mx_inv + 1):
            ex_sum = ex_pre[r + 1] - ex_pre[l]
            pr_sum = pr_pre[r + 1] - pr_pre[l]
            ans = min(ans, ((c + ex_pre[mx_inv + 1] - ex_sum) / (1 - pr_sum), l, r))
    for i in range(d):
        seq = list(map(int, input().split()))
        inv = 0
        for j in range(len(seq)):
            for k in range(j, len(seq)):
                if seq[j] > seq[k]:
                    inv += 1
        ret = min([a * inv, a * (mx_inv - inv) + b, ans[0]])
        print("%d/%d" % (ret.numerator, ret.denominator))

