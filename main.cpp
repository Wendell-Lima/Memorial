#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include "arquivos-lib.h"
#define extensao ((char *) ".cum")
#define s 2000 // Tempo (ms) para o usuario memorizar o tabuleiro

//Prot�tipos
int espacosVazios(char [8][8], int);
void imprimeTabuleiro(char [8][8], int);
int prepararJogo();
void iniciarJogo(char *, int, int);
int dificuldade();
char **criarMatriz(int);
void listarRanking(); 

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
			case 2:
				listarRanking();
				break;
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
	int tamanho;
	int novoJogo=1;
	
	system("cls");
	printf("Digite o nome do jogador: ");
	gets(nome);
	fflush(stdin);
	
	// Verifica se j� existe um jogo
	if (verificarArquivo(nome, extensao)) {
		int escolha;
		do {
			system("cls");
			printf("Um jogo antigo foi encontrado, deseja continuar ou criar um novo jogo?\n");
			printf("1 - Continuar\n");
			printf("2 - Novo jogo\n");
			
			escolha = getche();
			escolha -= 48;
			fflush(stdin);
			
			if (escolha != 1 && escolha != 2) {
				printf("Op��o inv�lida");
				Sleep(800);
			}
		} while (escolha != 1 && escolha != 2);
		if (escolha == 1) novoJogo = 0;
	}
	
	if (novoJogo)
		tamanho = dificuldade();
	
	if (tamanho != 0 || novoJogo == 0)
		iniciarJogo(nome, tamanho, novoJogo);
	return 0;
}

void iniciarJogo(char *jogador, int tamanho, int novoJogo) {
	
	system("cls");
	
	FILE *fp;
	Jogo jogo;
	
	if (novoJogo) {
		strcpy(jogo.jogador, jogador);
		//jogo.tabuleiro = criarMatriz(tamanho);
		//jogo.tabuleiroJogo = criarMatriz(tamanho);
		jogo.score = 0;
		jogo.vidas = 3;
		jogo.dificuldade = tamanho/2;
	} else {
		jogo = carregarJogo(fp);
		tamanho = jogo.dificuldade * 2;
	}
		
	int numCartas = tamanho*tamanho/2;
	char cartas[numCartas];
	int dificuldade = tamanho/2;
	int cont=0, i, j, k;
	int linha[2], coluna[2];
	int invalido=0;
	
	// Inicializando cartas
	for (i=0; i<numCartas; i++)
		cartas[i] = 65 + i; // 65 e o numero na tabela ascii onde comeca o alfabeto maiusculo
	
	if (novoJogo) {
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
				printf("\nVidas: %d", jogo.vidas);
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
				if (jogo.tabuleiroJogo[linha[i]][coluna[i]] == '*') {
					jogo.tabuleiroJogo[linha[i]][coluna[i]] = jogo.tabuleiro[linha[i]][coluna[i]];
					
				}
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
		
		// Errou o par
		if (jogo.tabuleiroJogo[linha[0]][coluna[0]] != jogo.tabuleiroJogo[linha[1]][coluna[1]]) {
			printf("\nNope");
			Sleep(800);
			jogo.tabuleiroJogo[linha[0]][coluna[0]] = '*';
			jogo.tabuleiroJogo[linha[1]][coluna[1]] = '*';
			jogo.vidas--;
		}
		else // Acertou o par
			jogo.score++;
		
		// Grava tudo em cada jogada
		limparArquivo(jogador, extensao);
		fp = abrirArquivo(jogador, extensao);
		gravarJogo(fp, jogo);
		fclose(fp);
		
	} while (espacosVazios(jogo.tabuleiroJogo, tamanho) != 0 && jogo.vidas != 0);
	
	if (jogo.vidas == 0) {
		printf("\nVoc� perdeu, suas vidas chegaram a zero...");
		printf("\nScore: %d\n", jogo.score);
	} else {
		printf("\nParab�ns voc� ganhou!");
		printf("\nScore: %d", jogo.score);
		jogo.score += jogo.vidas;
		printf("\nScore + vidas: %d\n\n", jogo.score);
		//verificarRank(jogo);
	}
	
	// Remove um arquivo assim que o jogo acaba
	apagarArquivo(jogador, extensao);
		
	system("pause");
}

void listarRanking(){
	int i;
	FILE *fp;
	Rank rank;
	
	system("cls");
	printf("\n");
	printf(" ");
	for (i = 0; i < 60; i++) printf("_");
	
	printf("\n| N� | %11sJogador%11s | Score | %1sDificuldade%1s |\n", "", "","",""); // Cabecalho
	printf("|----+-------------------------------+-------+---------------|\n");
	
	// Parte l�gica
	fp = abrirArquivo((char *) "ranking", (char *) ".rf");
	rank = carregarRank(fp);
	
	fseek(fp, 0, SEEK_SET);
	for (i=0; i<10; i++) {
		switch (rank.lista[i].dificuldade) {
			case 1:
				printf("| %2d | %-30s | %5d | Caf� com leite |\n", i+1, rank.lista[i].jogador, rank.lista[i].score);
				break;
			case 2:
				printf("| %2d | %-30s | %5d | Facil          |\n", i+1, rank.lista[i].jogador, rank.lista[i].score, rank.lista[i].dificuldade);
				break;
			case 3:
				printf("| %2d | %-30s | %5d | Medio          |\n", i+1, rank.lista[i].jogador, rank.lista[i].score, rank.lista[i].dificuldade);
				break;
			case 4:
				printf("| %2d | %-30s | %5d | Dificil        |\n", i+1, rank.lista[i].jogador, rank.lista[i].score, rank.lista[i].dificuldade);
				break;
		}
	}
	
	// Linha de baixo da tabela
	printf("|____|_______________________________|_______|_______________|\n");
	system("pause");
}

void verificarRank(Jogo jogo) {
	FILE *fp;
	Rank rank;
	int i, posicaoGarantida=11;
	
	fp = abrirArquivo((char *) "ranking", (char *) ".rf");
	rank = carregarRank(fp);
	
	for (i=10; i>0; i--) {
		if (jogo.score > rank.lista[i].score) posicaoGarantida = i;
		else break;
	}
}

void inicializarRank() {

}

int dificuldade() {
	int continuar = 0;
	int dificuldade;
	
	do {
		system("cls");
		printf("Menu Dificuldade\n");
		printf("\n 1 - Caf� com leite");
		printf("\n 2 - F�cil");
		printf("\n 3 - M�dio");
		printf("\n 4 - Dif�cil");
		printf("\n 0 - Voltar ao Menu");
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

int espacosVazios(char matriz[8][8], int tamanho) {
	int cont=0, i, j;
	for (i=0; i<tamanho; i++)
		for (j=0; j<tamanho; j++) 
			if (matriz[i][j] == ' ' || matriz[i][j] == '*')
				cont++;
	if (cont != 0)
		return cont+1;
	return cont;
}

void imprimeTabuleiro(char matriz[8][8], int tamanho) {
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
