#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int dificuldade;
	char jogador[30];
	char **tabuleiro;
	char **tabuleiroJogo;
	int score;
	int vidas;
} Jogo;

typedef struct {
	Jogo lista[10];
} Rank;

// Verifica se um arquivo existe ou nao no mesmo nivel de pastas
int verificarArquivo(char nome[30], char *extensao) {
	FILE *fp;
	char nome_arquivo[40];
	strcpy(nome_arquivo, nome);
	strcat(nome_arquivo, extensao);
	
	fp = fopen(nome_arquivo, "rb");
	if (!fp) { 
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}

void criarArquivo(char nome[30], char *extensao) {
	FILE *fp;
	char nome_arquivo[40];
	strcpy(nome_arquivo, nome);
	strcat(nome_arquivo, extensao);
	
	fp = fopen(nome_arquivo, "wb");
	fclose(fp);
}

FILE *abrirArquivo(char nome[30], char *extensao) {
	FILE *fp;
	char nome_arquivo[40];
	strcpy(nome_arquivo, nome);
	strcat(nome_arquivo, extensao);
	
	fp = fopen(nome_arquivo, "a+b");
	return fp;
}

void gravarJogo(FILE *fp, Jogo jogo) {
	fseek(fp, 0, SEEK_SET);
	fwrite(&jogo, sizeof(jogo), 1, fp);
}

Jogo carregarJogo(FILE *fp) {
	Jogo jogo;
	
	fseek(fp, 0, SEEK_SET);
	fread(&jogo, sizeof(Jogo), 1, fp);
	return jogo;
}

void limparArquivo(char nome[30], char *extensao) {
	FILE *fp;
	char nome_arquivo[40];
	strcpy(nome_arquivo, nome);
	strcat(nome_arquivo, extensao);
	
	fp = fopen(nome_arquivo, "wb");
	
	fclose(fp);
}
