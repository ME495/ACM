import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws IOException {
		Scanner in = new Scanner(new File("derangements.in"));
		PrintWriter out = new PrintWriter(new File("derangements.out"));
		int n = in.nextInt();
		if(n==1) {
			out.println(1);
		} else if(n==2) {
			out.println(5);
		} else {
			BigInteger[] dp = new BigInteger[n+1];
			dp[1] = BigInteger.ONE;
			dp[2] = BigInteger.valueOf(5);
			for(int i=3;i<=n;++i) {
				dp[i] = BigInteger.ZERO;
				dp[i] = dp[i].add(dp[i-1].multiply(BigInteger.valueOf(2*i-1)));
				dp[i] = dp[i].add(dp[i-2].multiply(BigInteger.valueOf(2*(i-1))));
			}
			out.println(dp[n]);
		}
		in.close();
		out.close();
	}
}
