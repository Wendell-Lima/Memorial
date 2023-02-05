#ifndef arquivoslib
#define arquivoslib

typedef struct {
	char **tabuleiro;
	char **tabuleiroJogo;
	int score;
	int vidas;
	int dificuldade;
} Jogo;

int verificarArquivo(char *, char *);
void criarArquivo(char *, char *);
FILE *abrirArquivo(char *, char *);
void gravarDados(FILE *, Jogo);

#endif
