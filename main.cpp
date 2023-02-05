#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include "arquivos-lib.h"
#define extensao ((char *) ".cum")
#define s 5000 // Tempo (ms) para o usuario memorizar o tabuleiro

//Prot�tipos
int espacosVazios(char **, int);
void imprimeTabuleiro(char **, int);
int prepararJogo();
void iniciarJogo(char *, int);
int dificuldade();
char **criarMatriz(int);

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	int continuar = 0, escolha;

	do {
		system("cls");
		printf("Seja bem vindo ao jogo da mem�ria!\n");
		printf("\n 1 - Jogar");
		printf("\n 2 - Highscores");
		printf("\n 0 - Sair");
		
		printf("\n\nDigite a op��o que desejar: ");
		
		escolha = getche();
		escolha -= 48;
		fflush(stdin);
		
		switch (escolha) {
			case 1:
				prepararJogo();
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
				printf("Op��o inv�lida!\n");
				Sleep(500);
				break;
		}
	} while(!continuar);

	system("pause");
	return 0;
}

int prepararJogo() {
	char nome[30];
	char *nome_arquivo;
	int tamanho;
	
	system("cls");
	printf("Digite o nome do jogador: ");
	gets(nome);
	
	tamanho = dificuldade();
	if (tamanho != 0)
		iniciarJogo(nome, tamanho);
	return 0;
}

void iniciarJogo(char *jogador, int tamanho) {
	
	system("cls");
	
	int numCartas = tamanho*tamanho/2;
	char cartas[numCartas];
	int cont=0, i, j, k;
	int linha[2], coluna[2];
	int invalido=0;
	
	Jogo jogo;
	jogo.jogador = nome;
	jogo.tabuleiro = criarMatriz(tamanho);
	jogo.tabuleiroJogo = criarMatriz(tamanho);
	jogo.score = 0;
	jogo.vidas = 3;
	jogo.dificuldade = tamanho/2;
	
	FILE *fp = abrirArquivo(jogador, extensao);
	
	// Inicializando cartas
	for (i=0; i<numCartas; i++)
		cartas[i] = 65 + i; // 65 e o numero na tabela ascii onde comeca o alfabeto maiusculo
	
	// Inicializando o tabuleiro e tabuleiroJogo
	for (i=0; i<tamanho; i++) {
		for (j=0; j<tamanho; j++) {
			jogo.tabuleiro[i][j] = ' ';
			jogo.tabuleiroJogo[i][j] = '*';
		}
	}
	
	// Monta o tabuleiro
	srand(time(NULL));
	while (espacosVazios(jogo.tabuleiro, tamanho) > 0) {
		for (k=0; k<numCartas; k++) {
			cont=0;
			while (cont<2) {
				i=rand()%tamanho;
				j=rand()%tamanho;
				if (jogo.tabuleiro[i][j] == ' ') {
					jogo.tabuleiro[i][j] = cartas[k];
					cont++;
				}
			}
		}
	}
	
	// Mostra o tabuleiro
	printf("Memorize o tabuleiro...\n");
	imprimeTabuleiro(jogo.tabuleiro, tamanho);
	
	// Informa o tempo at� que o jogo comece
	printf("\nIniciando jogo em:");
	for (i=s/1000; i>=0; i--) {
		printf(" %d", i);
		Sleep(1000);
	}
	
	// Inicia Jogo
	do {
		for (i=0; i<2; i++) {
			system("cls");
			imprimeTabuleiro(jogo.tabuleiroJogo, tamanho);
			linha[i] = -1;
			coluna[i] = -1;
			do {
				invalido = 0;
				printf("\nScore: %d", jogo.score);
				printf("\nDigite a linha e a coluna da carta (separados por espaco): ");
				scanf("%d %d", &linha[i], &coluna[i]);
				fflush(stdin);
				
				// Verifica se o valor de linha e coluna estao dentro do intervalo possivel
				if ((linha[i] < 0 || linha[i] >= tamanho || coluna[i] < 0 || coluna[i] >= tamanho)) {
					printf("Posicao invalida!");
					Sleep(800);
					system("cls");
					imprimeTabuleiro(jogo.tabuleiroJogo, tamanho);
					invalido = 1;
					continue;
				}
				
				// Verifica se a posicao nao esta ocupada
				if (jogo.tabuleiroJogo[linha[i]][coluna[i]] == '*')
					jogo.tabuleiroJogo[linha[i]][coluna[i]] = jogo.tabuleiro[linha[i]][coluna[i]];
				else {
					printf("A posicao ja foi revelada!");
					Sleep(800);
					system("cls");
					imprimeTabuleiro(jogo.tabuleiroJogo, tamanho);
					invalido = 1;
				}
			} while (invalido == 1);
		}
		system("cls");
		imprimeTabuleiro(jogo.tabuleiroJogo, tamanho);
		if (jogo.tabuleiroJogo[linha[0]][coluna[0]] != jogo.tabuleiroJogo[linha[1]][coluna[1]]) {
			printf("\nNope");
			Sleep(800);
			jogo.tabuleiroJogo[linha[0]][coluna[0]] = '*';
			jogo.tabuleiroJogo[linha[1]][coluna[1]] = '*';
		}
		else //caso n�o tenha errado, score +1
			jogo.score++;
			
	} while (linha[i]+coluna[i]!=6);
}

int dificuldade() {
	int continuar = 0;
	int dificuldade;
	
	do{
		system("cls");
		printf("\n 0 - Voltar ao Menu");
		printf("\n 1 - Caf� com leite");
		printf("\n 2 - F�cil");
		printf("\n 3 - M�dio");
		printf("\n 4 - Dif�cil");
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
				return 2;
				break;
			case 2:
				return 4;
				break;
			case 3:
				return 6;
				break;
			case 4:
				return 8;
				break;
			default:
				continuar = 0;
				printf("Op��o inv�lida!\n");
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
