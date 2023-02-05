#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verificarArquivo(char *nome, char *extensao) {
	// Verifica se um arquivo existe ou nao no mesmo nivel de pastas
	
	FILE *fp;
	char *nome_arquivo;
	
	nome_arquivo = strcat(nome, extensao);
	fp = fopen(nome_arquivo, "rb");
	if (!fp) return 0; // Nao existe
	return 1; // Existe
}
