mu = [];
pre = [];
notp = [];
p = [];maxn=80010
for i in range(maxn) :
    mu.append(0)
    notp.append(0)
    pre.append(0)
mu[1]=1
for i in range(2,maxn):
    if notp[i] == 0 :
        p.append(i)
        mu[i]=-1    
    for j in p:
        if j*i>=maxn : break
        notp[i*j]=1
        if i%j!=0 : mu[i*j]=-mu[i]
for i in range(1,maxn) : pre[i]=pre[i-1]+mu[i]
t=5
while t :
    t-=1
    n=int(input())
    ans=0
    j=0
    i=1
    while i<=n :
        d=n//i
        j=n//d
        ans+=(pre[j]-pre[i-1])*d*d*d*d
        i=j+1
    print(ans)
