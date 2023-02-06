#ifndef arquivoslib
#define arquivoslib

typedef struct {
	int dificuldade;
	char jogador[30];
	char **tabuleiro;
	char **tabuleiroJogo;
	int score;
	int vidas;
} Jogo;

int verificarArquivo(char[30], char *);
void criarArquivo(char[30], char *);
FILE *abrirArquivo(char[30], char *);
void gravarJogo(FILE *, Jogo);
Jogo carregarJogo(FILE *);
void limparArquivo(char[30], char *);

#endif
