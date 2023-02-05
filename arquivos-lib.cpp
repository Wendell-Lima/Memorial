#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char jogador;
	char **tabuleiro;
	char **tabuleiroJogo;
	int score;
	int vidas;
	int dificuldade;
} Jogo;

// Verifica se um arquivo existe ou nao no mesmo nivel de pastas
int verificarArquivo(char *nome, char *extensao) {
	FILE *fp;
	char *nome_arquivo = strcat(nome, extensao);
	
	fp = fopen(nome_arquivo, "rb");
	if (!fp) { 
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}

void criarArquivo(char *nome, char *extensao) {
	FILE *fp;
	char *nome_arquivo = strcat(nome, extensao);
	
	fp = fopen(nome_arquivo, "wb");
	fclose(fp);
}

FILE *abrirArquivo(char *nome, char *extensao) {
	FILE *fp;
	char *nome_arquivo = strcat(nome, extensao);
	
	fp = fopen(nome_arquivo, "a+b");
	
	return fp;
}

void gravarJogo(FILE *fp, Jogo jogo) {
	fwrite(&jogo, sizeof(jogo), 1, fp);
}
