#include <stdio.h>

void salvarTabuleiro(char **tabuleiro) {
	FILE *fp;
	fp = fopen("tabuleiro", "a+b");
	fwrite(tabuleiro, sizeof(tabuleiro), 0, fp);
	fclose(fp);
}
