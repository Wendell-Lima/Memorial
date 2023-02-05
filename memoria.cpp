#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#define s 5000 // Tempo (ms) para o usuario memorizar o tabuleiro

//Protótipos
int espacosVazios(char **, int);
void imprimeTabuleiro(char **, int);
void jogar(int);
int dificuldade();
char **criarMatriz(int);
int iniciarJogo();

int main() {
	setlocale(LC_ALL, "Portuguese");
	int continuar = 0, escolha;

	do {
		system("cls");
		printf("Seja bem vindo ao jogo da memória!\n");
		printf("\n 1 - Jogar");
		printf("\n 2 - Highscores");
		printf("\n 0 - Sair");
		
		printf("\n\nDigite a opção que desejar: ");
		
		escolha = getche();
		escolha -= 48;
		fflush(stdin);
		
		switch (escolha) {
			case 1:
				iniciarJogo();
				break;
			/*case 2:
				ranking();
				break*/
			case 0: // Sair / Fechar
				printf("\nFechando...\n");
				Sleep(500);
				continuar = 1;
				break;
			default:
				printf("Opção inválida!\n");
				Sleep(500);
				break;
		}
	} while(!continuar);

	system("pause");
	return 0;
}

int iniciarJogo() {
	char nome[30];
	char *nome_arquivo;
	int tamanho;
	
	system("cls");
	printf("Digite o nome do jogador: ");
	gets(nome);
	
	nome_arquivo = strcat(nome, ".cum");
	if (fopen(nome, "rb")) {
		
	} else {
		
	}
	
	tamanho = dificuldade();
	if (tamanho != 0)
		jogar(tamanho);
	return 0;
}

void jogar(int tamanho) {
	
	system("cls");
	
	char **tabuleiro, **tabuleiroJogo;
	int numCartas = tamanho*tamanho/2;
	char cartas[numCartas];
	int cont=0, i, j, k;
	int linha[2], coluna[2];
	int invalido=0;
	int score = 0;
	int vidas = 3;
	
	tabuleiro = criarMatriz(tamanho);
	tabuleiroJogo = criarMatriz(tamanho);
	
	// Inicializando cartas
	for (i=0; i<numCartas; i++)
		cartas[i] = 65 + i; // 65 e o numero na tabela ascii onde comeca o alfabeto maiusculo
	
	// Inicializando o tabuleiro e tabuleiroJogo
	for (i=0; i<tamanho; i++) 
		for (j=0; j<tamanho; j++) {
			tabuleiro[i][j] = ' ';
			tabuleiroJogo[i][j] = '*';
		}
	
	// Monta o tabuleiro
	srand(time(NULL));
	while (espacosVazios(tabuleiro, tamanho) > 0) {
		for (k=0; k<numCartas; k++) {
			cont=0;
			while (cont<2) {
				i=rand()%tamanho;
				j=rand()%tamanho;
				if (tabuleiro[i][j] == ' ') {
					tabuleiro[i][j] = cartas[k];
					cont++;
				}
			}
		}
	}
	
	// Mostra o tabuleiro
	printf("Memorize o tabuleiro...\n");
	imprimeTabuleiro(tabuleiro, tamanho);
	
	// Informa o tempo até que o jogo comece
	printf("\nIniciando jogo em:");
	for (i=s/1000; i>=0; i--) {
		printf(" %d", i);
		Sleep(1000);
	}
	
	// Inicia Jogo
	do {
		for (i=0; i<2; i++) {
			system("cls");
			imprimeTabuleiro(tabuleiroJogo, tamanho);
			linha[i] = -1;
			coluna[i] = -1;
			do {
				invalido = 0;
				printf("\nScore: %d",score);
				printf("\nDigite a linha e a coluna da carta (separados por espaco): ");
				scanf("%d %d", &linha[i], &coluna[i]);
				fflush(stdin);
				
				// Verifica se o valor de linha e coluna estao dentro do intervalo possivel
				if ((linha[i] < 0 || linha[i] >= tamanho || coluna[i] < 0 || coluna[i] >= tamanho)) {
					printf("Posicao invalida!");
					Sleep(800);
					system("cls");
					imprimeTabuleiro(tabuleiroJogo, tamanho);
					invalido = 1;
					continue;
				}
				
				// Verifica se a posicao nao esta ocupada
				if (tabuleiroJogo[linha[i]][coluna[i]] == '*')
					tabuleiroJogo[linha[i]][coluna[i]] = tabuleiro[linha[i]][coluna[i]];
				else {
					printf("A posicao ja foi revelada!");
					Sleep(800);
					system("cls");
					imprimeTabuleiro(tabuleiroJogo, tamanho);
					invalido = 1;
				}
			} while (invalido == 1);
		}
		system("cls");
		imprimeTabuleiro(tabuleiroJogo, tamanho);
		if (tabuleiroJogo[linha[0]][coluna[0]] != tabuleiroJogo[linha[1]][coluna[1]]) {
			printf("\nNope");
			Sleep(800);
			tabuleiroJogo[linha[0]][coluna[0]] = '*';
			tabuleiroJogo[linha[1]][coluna[1]] = '*';
		}
		else //caso não tenha errado, score +1
			score++;
			
	} while (linha[i]+coluna[i]!=6);
}

int dificuldade() {
	int continuar = 0;
	int dificuldade;
	
	do{
		system("cls");
		printf("\n 0 - Voltar ao Menu");
		printf("\n 1 - Fácil");
		printf("\n 2 - Médio");
		printf("\n 3 - Difícil");
		printf("\n\nEscolha a dificuldade: ");
		
		dificuldade = getche();
		dificuldade -= 48;
		fflush(stdin);
		
		continuar = 1;
		switch(dificuldade)	{
			case 0:
				return 0;
				break;
			case 1:
				return 4;
				break;
			case 2:
				return 5;
				break;
			case 3:
				return 6;
				break;
			default:
				continuar = 0;
				printf("Opção inválida!\n");
				Sleep(500);
				break;
		}	
	} while(!continuar);
}

int espacosVazios(char **matriz, int tamanho) {
	int cont=0, i, j;
	for (i=0; i<tamanho; i++)
		for (j=0; j<tamanho; j++) 
			if (matriz[i][j] == ' ')
				cont++;
	if (cont != 0)
		return cont+1;
	return cont;
}

void imprimeTabuleiro(char **matriz, int tamanho) {
	int i, j;
	printf("  | ");
	for (i=0; i<tamanho; i++)
		printf("%d  ", i);
	printf("\n");
	printf("--+-");
	for (i=0; i<tamanho; i++)
		printf("---", i);
	printf("\n");
	for (i=0; i<tamanho; i++) {
		printf("%d | ", i);
		for (j=0; j<tamanho; j++) {
			printf("%c  ", matriz[i][j]);
		}
		printf("\n");
	}
}

char **criarMatriz(int tamanho) {
	char **matriz;
	int i;
	
	for (i=0; i<tamanho; i++) {
		matriz = (char **) calloc(tamanho, tamanho*sizeof(char));
		if (matriz == NULL) return NULL;
	}
		
	for (i=0; i<tamanho; i++) {
		matriz[i] = (char *) calloc(tamanho, tamanho*sizeof(char));
		if (matriz[i] == NULL) return NULL;
	}
		
	return matriz;
}
