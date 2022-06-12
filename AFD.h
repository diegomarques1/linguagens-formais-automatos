// Diego Souza Lima Marques - TIA: 32039921
// Lucas de Camargo Gonçalves - TIA: 32074964
// Linguagens Formais e Autômatos - Projeto 1 - Simulador de AFD
// AFD.h

#include <string>
#include <fstream>
#include <iostream>

// Estrutura para armazenar os valores de uma transição:
// f(estado, símbolo) = estado

struct Trans
{
	int qAtual; 			 // estado atual
	char sLido;   			 // símbolo lido
	int qChegada;   		 // estado de chegada
};

#ifndef __AFD_H__
#define __AFD_H__

// Estrutura para armazenar a quíntupla do autômato finito
// determinístico - AFD M: (Q, E, f, q0, F), bem como os
// tamanhos dessas estruturas identificados no arquivo

struct AFD
{
	int Q[30];             	 // conjunto de estados
	char E[12]; 			 // alfabeto
	Trans* f; 			 	 // função de transição
	int q0;					 // estado inicial
	int F[30];  			 // conjunto de estados finais
	int vetorTamanho[4];     // tamanhos de E [0], Q [1], F [2], f [3]
};

// Assinaturas das funções utilizadas no projeto

Trans* definirF(int tamanho);

AFD* inicializarAutomato();

void mostrarErro(int linha, int tamanhoMinimo, int tamanhoMaximo);

bool lerArquivoAFD(std::string nomeArquivo, AFD* automato);

int analisarFuncao(int qAtual, char s, Trans func);

bool avaliarCadeia(std::string cadeia, AFD* automato);

bool lerArquivoCadeia(std::string nomeArquivo, AFD* automato);

void mostrarQuintupla(const AFD* automato);

void responderCadeia(AFD* automato);

#endif // __AFD_H__