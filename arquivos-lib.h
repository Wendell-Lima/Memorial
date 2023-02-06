#ifndef arquivoslib
#define arquivoslib

typedef struct {
	int dificuldade;
	char jogador[30];
	char tabuleiro[8][8];
	char tabuleiroJogo[8][8];
	int score;
	int vidas;
} Jogo;

typedef struct {
	Jogo lista[10];
} Rank;

char **criarMatriz(int);
int verificarArquivo(char[30], char *);
void criarArquivo(char[30], char *);
FILE *abrirArquivo(char[30], char *);
void gravarJogo(FILE *, Jogo);
Jogo carregarJogo(FILE *);
void limparArquivo(char[30], char *);

#endif
