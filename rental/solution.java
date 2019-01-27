import java.io.*;
import java.util.*;
public class rental {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("rental.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("rental.out")));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int r = Integer.parseInt(st.nextToken());
		int[] milkProduced = new int[n];
		for(int i = 0; i < n; i++) {
			milkProduced[i] = Integer.parseInt(br.readLine());
		}
		sort(milkProduced);
		Shop[] shops = new Shop[m];
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(br.readLine());
			shops[i] = new Shop(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
		}
		Arrays.sort(shops);
		long[] maxProfit = new long[n+1];
		{
			int index = 0;
			for(int i = 0; i < n; i++) {
				maxProfit[i+1] = maxProfit[i];
				while(index < m && milkProduced[i] > 0) {
					int use = Math.min(milkProduced[i], shops[index].quantity);
					maxProfit[i+1] += use * (long)shops[index].price;
					milkProduced[i] -= use;
					shops[index].quantity -= use;
					if(shops[index].quantity == 0) {
						index++;
					}
				}
			}
		}
		int[] rental = new int[r];
		for(int i = 0; i < r; i++) {
			rental[i] = Integer.parseInt(br.readLine());
		}
		sort(rental);
		{
			int a = n-1;
			int rI = 0;
			long rentalSoFar = 0;
			while(a >= 0 && rI < r) {
				rentalSoFar += rental[rI];
				maxProfit[a] += rentalSoFar;
				rI++;
				a--;
			}
		}
		long ret = 0;
		for(long out: maxProfit) {
			ret = Math.max(ret, out);
		}
		pw.println(ret);
		pw.close();
	}

	public static void sort(int[] l) {
		Arrays.sort(l);
		for(int i = 0; i < l.length-1-i; i++) {
			l[i] ^= l[l.length-1-i];
			l[l.length-1-i] ^= l[i];
			l[i] ^= l[l.length-1-i];
		}
	}

	static class Shop implements Comparable<Shop> {
		public int quantity, price;
		public Shop(int a, int b) {
			quantity=a;
			price=b;
		}
		public int compareTo(Shop s) {
			return s.price - price;
		}
	}

