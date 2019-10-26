#include <bits/stdc++.h>
using namespace std;
char *c = "URDL";
int main() {
	srand(time(NULL));
	for(int i = 0; i < 50000; i++)
		printf("%c", c[rand() % 4]);
	puts("");
	return 0;
}
