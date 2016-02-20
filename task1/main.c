#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	int n;
	scanf("%d", &n);
	int* tbl;
	tbl = (int *)malloc((n * n) * sizeof(int));
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			tbl[(i - 1) * n + (j - 1)] = i * j;
		}
	}
	int x1, y1, x2, y2;
	scanf("%d", &x1);
	if (x1 != 0)
		scanf("%d%d%d", &y1, &x2, &y2);
	while (x1 != 0) {
		for (int i = y1; i <= y2; i++) {
			for (int j = x1; j <= x2; j++) {
				printf("%5d", tbl[(i - 1) * n + (j - 1)]);
			}
			printf("\n");
		}
		scanf("%d", &x1);
		if (x1 != 0)
			scanf("%d%d%d", &y1, &x2, &y2);
	}
	free(tbl);
	return 0;
}
