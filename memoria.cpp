#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#define m 4 // Largura/altura da matriz quadrada
#define s 5000 // Tempo (ms) para o usuario memorizar o tabuleiro

/*
void imprimirMatriz(char matriz[m][m]) {
	int i, j;
	for (i=0; i<m; i++) {
		printf("%d | ", i);
		for (j=0; j<m; j++) {
			printf("%c  ", matriz[i][j]);
		}
	}
}
*/

//Protótipos
int espacosVazios(char [][m]);
void imprimeTabuleiro(char [][m]);
void jogar();
void dificuldade();


int main() {
	setlocale(LC_ALL, "Portuguese");
	int continuar = 0, escolha;
	
	do{
		system("cls");
		printf("Seja bem vindo ao jogo da memória!\n");
		printf("\n 1 - Jogar");
		printf("\n 2 - Placar");
		printf("\n 0 - Sair");
		
		printf("\n\nDigite a opção que desejar: ");
		escolha = getche();
		escolha -= 48;
		fflush(stdin);
		
		switch (escolha) {
			case 1:
				jogar();
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
	}while(!continuar);

	system("pause");
	return 0;
}

void jogar(){
	
	system("cls");
	
	char tabuleiro[m][m], tabuleiroJogo[m][m];
	int numCartas = m*m/2;
	char cartas[numCartas];
	int cont=0, i, j, k;
	int linha[2], coluna[2];
	int invalido=0;
	int score = 0;
	
	//Pergunta ao usuário a dificuldade
	dificuldade();
	
	// Inicializando cartas
	for (i=0; i<numCartas; i++)
		cartas[i] = 65 + i; // 65 e o numero na tabela ascii onde comeca o alfabeto maiusculo
	
	// Inicializando o tabuleiro e tabuleiroJogo
	for (i=0; i<m; i++) 
		for (j=0; j<m; j++) {
			tabuleiro[i][j] = ' ';
			tabuleiroJogo[i][j] = '*';
		}
	
	// Monta o tabuleiro
	srand(time(NULL));
	while (espacosVazios(tabuleiro) > 0) {
		for (k=0; k<numCartas; k++) {
			cont=0;
			while (cont<2) {
				i=rand()%m;
				j=rand()%m;
				if (tabuleiro[i][j] == ' ') {
					tabuleiro[i][j] = cartas[k];
					cont++;
				}
			}
		}
	}
	
	// Mostra o tabuleiro
	printf("Memorize o tabuleiro...\n");
	imprimeTabuleiro(tabuleiro);
	
	// Informa o tempo até que o jogo comece
	printf("\nIniciando jogo em:");
	for (i=s/1000; i>=0; i--) {
		printf(" %d", i);
		Sleep(s/(s/1000));
	}
	
	// Inicia Jogo
	do {
		for (i=0; i<2; i++) {
			system("cls");
			imprimeTabuleiro(tabuleiroJogo);
			linha[i] = -1;
			coluna[i] = -1;
			do {
				invalido = 0;
				printf("\nScore: %d",score);
				printf("\nDigite a linha e a coluna da carta (separados por espaco): ");
				scanf("%d %d", &linha[i], &coluna[i]);
				fflush(stdin);
				
				// Verifica se o valor de linha e coluna estao dentro do intervalo possivel
				if ((linha[i] < 0 || linha[i] >= m || coluna[i] < 0 || coluna[i] >= m)) {
					printf("Posicao invalida!");
					invalido = 1;
					continue;
				}
				
				// Verifica se a posicao nao esta ocupada
				if (tabuleiroJogo[linha[i]][coluna[i]] == '*')
					tabuleiroJogo[linha[i]][coluna[i]] = tabuleiro[linha[i]][coluna[i]];
				else {
					printf("A posicao ja foi revelada!");
					invalido = 1;
				}
			} while (invalido == 1);
		}
		system("cls");
		imprimeTabuleiro(tabuleiroJogo);
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

void dificuldade(){
	int continuar = 0;
	int dificuldade;
	
	do{
		printf("\n 0 - Voltar ao Menu");
		printf("\n 1 - Fácil");
		printf("\n 2 - Médio");
		printf("\n 3 - Difícil");
		printf("\n\nEscolha a dificuldade: ");
		scanf("%d",&dificuldade);
		
		dificuldade = getche();
		dificuldade -= 48;
		fflush(stdin);
		
		switch(dificuldade){
			case 0:
				main();
				break;
			case 1:
				#define m 4
				continuar = 1;
				break;
			case 2:
				#define m 5
				continuar = 1;
				break;
			case 3:
				#define m 6
				continuar = 1;
				break;
			default:
				printf("Opção inválida!\n");
				Sleep(500);
				break;
			
		}	
	}while(!continuar);
}

int espacosVazios(char matriz[m][m]) {
	int cont=0, i, j;
	for (i=0; i<m; i++)
		for (j=0; j<m; j++) 
			if (matriz[i][j] == ' ')
				cont++;
	if (cont != 0)
		return cont+1;
	return cont;
}

void imprimeTabuleiro(char matriz[m][m]) {
	int i, j;
	printf("  | ");
	for (i=0; i<m; i++)
		printf("%d  ", i);
	printf("\n");
	printf("--+-");
	for (i=0; i<m; i++)
		printf("---", i);
	printf("\n");
	for (i=0; i<m; i++) {
		printf("%d | ", i);
		for (j=0; j<m; j++) {
			printf("%c  ", matriz[i][j]);
		}
		printf("\n");
	}
}




