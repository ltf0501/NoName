#include <stdio.h>
#include <algorithm>
using namespace std;


constexpr int kN = int(1E2 + 100);


bool used[kN][kN][kN];

int main() {
	int a, b, c, cnt = 0;
	scanf("%d%d%d", &a, &b, &c);
	// a -> xy, b -> xz, c -> yz

	if (max(b, c) <= a && b * c >= a) {
		if (b <= c) {
			for (int i = 1; i <= b; i++) used[i][i][1] = true;
			for (int i = b + 1; i <= c; i++) used[b][i][1] = true;
			a -= c;
			for (int i = 1; i <= b; i++) for (int j = 1; j <= c; j++) 
				if (!used[i][j][1] && a-- > 0) used[i][j][1] = true;
		}
		else {
			for (int i = 1; i <= c; i++) used[i][i][1] = true;
			for (int i = c + 1; i <= b; i++) used[i][c][1] = true;
			a -= b;
			for (int i = 1; i <= b; i++) for (int j = 1; j <= c; j++) 
				if (!used[i][j][1] && a-- > 0) used[i][j][1] = true;
		}
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) cnt++;
		printf("%d\n", cnt);
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) printf("%d %d %d\n", x, y, z);
		return 0;
	}

	if (max(a, c) <= b && a * c >= b) {
		if (a <= c) {
			for (int i = 1; i <= a; i++) used[i][1][i] = true;
			for (int i = a + 1; i <= c; i++) used[a][1][i] = true;
			b -= c;
			for (int i = 1; i <= a; i++) for (int j = 1; j <= c; j++) 
				if (!used[i][1][j] && b-- > 0) used[i][1][j] = true;
		}
		else {
			for (int i = 1; i <= c; i++) used[i][1][i] = true;
			for (int i = c + 1; i <= a; i++) used[i][1][c] = true;
			b -= a;
			for (int i = 1; i <= a; i++) for (int j = 1; j <= c; j++) 
				if (!used[i][1][j] && b-- > 0) used[i][1][j] = true;
		}
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) cnt++;
		printf("%d\n", cnt);
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) printf("%d %d %d\n", x, y, z);
		return 0;
	}

	if (max(a, b) <= c && a * b >= c) {
		if (b <= a) {
			for (int i = 1; i <= b; i++) used[1][i][i] = true;
			for (int i = b + 1; i <= a; i++) used[1][i][b] = true;
			c -= a;
			for (int i = 1; i <= a; i++) for (int j = 1; j <= b; j++) 
				if (!used[1][i][j] && c-- > 0) used[1][i][j] = true;
		}
		else {
			for (int i = 1; i <= a; i++) used[1][i][i] = true;
			for (int i = a + 1; i <= b; i++) used[1][a][i] = true;
			c -= b;
			for (int i = 1; i <= a; i++) for (int j = 1; j <= b; j++) 
				if (!used[1][i][j] && c-- > 0) used[1][i][j] = true;
		}
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) cnt++;
		printf("%d\n", cnt);
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) printf("%d %d %d\n", x, y, z);
		return 0;
		
	}



	if (b * c - 1 >= a && b - 1 + c - 1 <= a && b != 1 && c != 1) {
		for (int i = 2; i <= b; i++) used[i][1][1] = true;
		for (int i = 2; i <= c; i++) used[1][i][1] = true;
		a -= b - 1 + c - 1;
		for (int i = 2; i <= b; i++) for (int j = 2; j <= c; j++) if (a-- > 0) used[i][j][1] = true;

		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) cnt++;
		printf("%d\n", cnt);
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) printf("%d %d %d\n", x, y, z);
		return 0;
	}

	if (a * c - 1 >= b && c - 1 + a - 1 <= b && a != 1 && c != 1) {
		for (int i = 2; i <= c; i++) used[1][1][i] = true;
		for (int i = 2; i <= a; i++) used[i][1][1] = true;
		b -= c - 1 + a - 1;
		for (int i = 2; i <= a; i++) for (int j = 2; j <= c; j++) if (b-- > 0) used[i][1][j] = true;

		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) cnt++;
		printf("%d\n", cnt);
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) printf("%d %d %d\n", x, y, z);
		return 0;
	}

	if (a * b - 1 >= c && a - 1 + b - 1 <= c && a != 1 && b != 1) {
		for (int i = 2; i <= a; i++) used[1][i][1] = true;
		for (int i = 2; i <= b; i++) used[1][1][i] = true;
		c -= a - 1 + b - 1;
		for (int i = 2; i <= a; i++) for (int j = 1; j <= b; j++) if (c-- > 0) used[1][i][j] = true;

		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) cnt++;
		printf("%d\n", cnt);
		for (int x = 1; x < kN; x++) for (int y = 1; y < kN; y++) for (int z = 1; z < kN; z++) 
			if (used[x][y][z]) printf("%d %d %d\n", x, y, z);
		return 0;
	}

	for (int i = 1; i < kN; i++) for (int j = 1; j < kN; j++) for (int k = 1; k < kN; k++) {
		if (i * j >= a && i + j - 1 <= a && 
				i * k >= b && i + k - 1 <= b && 
				j * k >= c && j + k - 1 <= c) {
			for (int x = 1; x <= i; x++) used[x][1][1] = true;
			for (int x = 1; x <= j; x++) used[1][x][1] = true;
			for (int x = 1; x <= k; x++) used[1][1][x] = true;
			a -= i + j - 1;
			b -= i + k - 1;
			c -= j + k - 1;
			for (int x = 2; x <= i; x++) for (int y = 2; y <= j; y++) if (a-- > 0) used[x][y][1] = true;
			for (int x = 2; x <= i; x++) for (int y = 2; y <= k; y++) if (b-- > 0) used[x][1][y] = true;
			for (int x = 2; x <= j; x++) for (int y = 2; y <= k; y++) if (c-- > 0) used[1][x][y] = true;

			for (int x = 1; x <= i; x++) for (int y = 1; y <= j; y++) for (int z = 1; z <= k; z++) 
				if (used[x][y][z]) cnt++;
			printf("%d\n", cnt);
			for (int x = 1; x <= i; x++) for (int y = 1; y <= j; y++) for (int z = 1; z <= k; z++) 
				if (used[x][y][z]) printf("%d %d %d\n", x, y, z);

			return 0;
		}
	}
	printf("-1\n");
} 
