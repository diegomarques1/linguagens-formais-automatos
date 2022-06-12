// Diego Souza Lima Marques - TIA: 32039921
// Lucas de Camargo Gonçalves - TIA: 32074964
// Linguagens Formais e Autômatos - Projeto 1 - Simulador de AFD
// main.cpp

#include <iostream>
#include "AFD.h"

using namespace std;

// A função seguinte mostra o menu do programa na tela do usuário

void mostrarMenu()
{
	cout << "\n--------------- Projeto 01 - LFA ---------------\n"
	<< "\n--------------------- MENU ---------------------\n"
	<< "Operacoes validas:\n"
	<< "\na) Ler dados do AFD de arquivo"
	<< "\nb) Mostrar a quintupla para o AFD lido"
	<< "\nc) Avaliar cadeias lidas de arquivo"
	<< "\nd) Avaliar novas cadeias pelo teclado"
	<< "\ne) Encerrar a aplicacao\n";
}

// Permite que o usuário realize a operação novamente ou volte ao menu

string voltarMenu()
{
	string temp;
	cout << "\n- Digite 0 para voltar ao menu\n\nOU\n\n- Digite 1 para realizar a operacao novamente\n\nOpcao escolhida: ";
	getline(cin, temp);
	while (temp != "0" && temp != "1")
	{
		cout << "\nOpcao invalida!\n\n0 -> Menu\n1 -> Repetir a operacao\n\nPor favor, digite novamente: ";
		getline(cin, temp);
	}
	return temp;
}

// Na função main(), o menu é constantemente executado por um laço do-while,
// exigindo nomes de arquivos para o usuário, cadeias de entrada, 
// ou simplesmente a operação desejada, caso seja suficiente

int main()
{
	AFD* M = nullptr;
	string op = " ", nomeArquivo, voltar;
	bool erro;
	
	// o laço permite que o programa continue em execução
	// até ser digitado a palavra-chave 'e'
	do
	{
		mostrarMenu();
		cout << "\nOpcao escolhida: ";
		getline(cin, op);
		while (op != "a" && op != "b" && op != "c" && op != "d" && op != "e") // validação de dados
		{
			cout << "\nOpcao invalida! Por favor, digite novamente a opcao em letra minuscula: ";
			getline(cin, op);
		}

		if (op == "a")
		{
			M = inicializarAutomato(); // alocação dinâmica
			cout << "Digite o nome do arquivo .txt com o AFD M: ";
			getline(cin, nomeArquivo);
			erro = lerArquivoAFD(nomeArquivo, M);
			if (erro == true) cout << "\nO arquivo foi lido com sucesso!\n";
			else
			{
				cout << "\nHouve erro na leitura do arquivo.\n";
				M = nullptr;
			}
			voltar = voltarMenu();
			while (voltar == "1")
			{
				cout << "Digite o nome do arquivo .txt com o AFD M: ";
				getline(cin, nomeArquivo);
				lerArquivoAFD(nomeArquivo, M);
				voltar = voltarMenu();
			}
			cout << "\nVoltando ao menu...\n";
		}

		// neste ponto, caso um arquivo válido do autômato não tenha sido fornecido,
		// não é permitido realizar qualquer outra operação efetiva

		else if (op == "b")
		{
			if (M == nullptr) cout << "Erro: arquivo do AFD ainda nao foi lido!\n";
			else
			{
				mostrarQuintupla(M);
				voltar = voltarMenu();
				while (voltar == "1")
				{
					mostrarQuintupla(M);
					voltar = voltarMenu();
				}
			}
			cout << "\nVoltando ao menu...\n";	
		}

		else if (op == "c")
		{
			cout << "Digite o nome do arquivo .txt com as cadeias para teste: ";
			getline(cin, nomeArquivo);
			if (M == nullptr) cout << "Erro: arquivo do AFD ainda nao foi lido!\n";
			else
			{
				erro = lerArquivoCadeia(nomeArquivo, M);
				(erro == true) ? cout << "\nO arquivo foi lido com sucesso!\n" : cout << "\nHouve erro na leitura do arquivo.\n";
				voltar = voltarMenu();
				while (voltar == "1")
				{
					cout << "Digite o nome do arquivo .txt com o AFD M: ";
					getline(cin, nomeArquivo);
					lerArquivoCadeia(nomeArquivo, M);
					voltar = voltarMenu();
				}
			}
			cout << "\nVoltando ao menu...\n";
		}

		else if (op == "d")
		{
			if (M == nullptr) cout << "Erro: arquivo do AFD ainda nao foi lido!\n";
			else
			{
				responderCadeia(M);
				voltar = voltarMenu();
				while (voltar == "1")
				{
					responderCadeia(M);
					voltar = voltarMenu();
				}
			}
			cout << "\nVoltando ao menu...\n";
		}

	} while (op != "e");

	cout << "\nEncerrando o programa...\n";
	
	// desalocar a memória para o autômato 
	// caso este tenha sido inicializado
	if (M != nullptr) 
	{
		delete[] M->f;
		delete M;	
	}
	
	return 0;
}