import java.lang.*;
import java.math.*;
import java.util.*;
import java.io.*;
public class Main {
	static int n;
	static BigInteger[] n_pow;
	static BigInteger[] dp;
	static int[] vis;
	static BigInteger[] value;
	static BigInteger[] valuen;
	static BigInteger f(int l, int r, int x, int b) {
		if (l >= r - 1) return value[b];
		int id = (l * (n + 1) + r) * 2 + b;
		if (vis[id] == x) return dp[id];
		vis[id] = x;
		int m=(l+r)/2;
		if(m-l<r-m){
		    dp[id]=f(m,r,x,1).add(
		        f(l,m,x,b).multiply(valuen[n-x]))
		        .add(f(m,r,x,0).multiply(value[x-1])).
		        multiply(n_pow[m-l-1]);
		}
		else if(m-l==r-m){
		    dp[id]=f(m,r,x,1).add(
		        f(l,m,x,b).multiply(value[n-x]))
		        .add(f(m,r,x,0).multiply(value[x-1])).
		        multiply(n_pow[m-l-1]);
		}
		else{
		    dp[id]=f(m,r,x,1)
		    .add(f(m,r,x,0).multiply(valuen[x-1]))
		    .add(f(l,m,x,b).multiply(value[n-x])).multiply(n_pow[r-m-1]);
		}
		return dp[id];
	}
	static BigInteger f1(int l,int r,int b){
	    if (l >= r - 1) return value[b];
		int id = (l * (n + 1) + r) * 2 + b;
		if (vis[id] == 1) return dp[id];
		vis[id] = 1;
		int m = (l + r) / 2;
		if(m-l<r-m){
		    dp[id]=f1(m,r,1)
		    .add(f1(l,m,b).multiply(valuen[n-1]))
		    .multiply(n_pow[m-l-1]);
		}
		else if(m-l>r-m){
		    dp[id]=f1(m,r,1).multiply(value[n])
		    .add(f1(l,m,b).multiply(value[n-1])).multiply(n_pow[r-m-1]);
		}
		else{
		    dp[id]=f1(m,r,1)
		    .add(f1(l,m,b).multiply(value[n-1])).multiply(n_pow[r-m-1]);
		}
		        return dp[id];
	}
	static BigInteger fn(int l,int r,int b){
	    if (l >= r - 1) return value[b];
		int id = (l * (n + 1) + r) * 2 + b;
		if (vis[id] == n) return dp[id];
		vis[id] = n;
		int m = (l + r) / 2;
		dp[id]=fn(m,r,1)
		.add(fn(m,r,0).multiply(value[n-1]))
		.multiply(n_pow[m-l-1]);
		return dp[id];
	}
	public static void main(String[] args) throws java.lang.Exception {
		File fin = new File("binary.in");
		Scanner cin = new Scanner(fin);
		n = cin.nextInt();
		int mid=n/2+1;
		value=new BigInteger[n+3];
		valuen=new BigInteger[n+3];
		n_pow = new BigInteger[n+3];
		value[0]=BigInteger.valueOf(0);
		for(int i=1;i<=n;i++)value[i]=BigInteger.valueOf(i);
		valuen[0]=BigInteger.valueOf(0);
		for(int i=1;i<=n;i++)valuen[i]=BigInteger.valueOf(i*n);
		n_pow[0] =value[1];
		n_pow[1]=value[n];
		for (int i=2; i<=mid;i++)n_pow[i]=n_pow[i/2].multiply(n_pow[i-i/2]);
		dp = new BigInteger[(n + 3) * (n + 3) * 3];
		vis = new int[(n + 3) * (n + 3) * 3];
		for (int j = 0; j < (n + 3) * (n + 3) * 3; j++) vis[j] = -1;
		BigInteger ansl=f1(0,n,0).add(fn(0,n,0));
		BigInteger ansr=f1(0,n,1).add(fn(0,n,1));
		for (int i = 2; i < n; i++) {
			ansl=ansl.add(f(0, n, i, 0));
			ansr=ansr.add(f(0, n, i, 1));
		}
		BigInteger ans;
		if(n==1)ans=BigInteger.valueOf(1);
		else ans=ansl.multiply(value[n-1]).add(ansr);
		FileWriter fw = new FileWriter("binary.out");
		fw.write(ans.toString());
		fw.write("\n");
		fw.flush();
		fw.close();
	}
}
