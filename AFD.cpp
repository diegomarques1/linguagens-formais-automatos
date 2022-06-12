// Diego Souza Lima Marques - TIA: 32039921
// Lucas de Camargo Gonçalves - TIA: 32074964
// Linguagens Formais e Autômatos - Projeto 1 - Simulador de AFD
// AFD.cpp

// Referências para a função stoi()
// https://www.cplusplus.com/reference/string/stoi/
// https://www.geeksforgeeks.org/converting-strings-numbers-cc/

#include "AFD.h"

using namespace std;

// A seguinte função cria e retorna um vetor dinâmico para 
// a função de transição a partir do valor lido no arquivo do AFD

Trans* definirF(int tamanho)
{
	Trans * f = new Trans[tamanho];
	return f;
}

// Aloca um ponteiro para autômato AFD, popula a quíntupla do mesmo com valores neutros
// a partir dos limites definidos no enunciado do projeto, e retorna o autômato

AFD* inicializarAutomato()
{
	AFD* automato = new AFD();
	int i;

	for (i = 0; i < 30; i++)
	{
		automato->Q[i] = -1;
	}

	for (i = 0; i < 12; i++)
	{
		automato->E[i] = ' ';
	}
	
	// sem inicialização para f, visto que
	// será utilizada alocação dinâmica
	
	automato->q0 = 0;

	for (i = 0; i < 30; i++)
	{
		automato->F[i] = -1;
	}
	
	for (i = 0; i < 4; i++)
	{
		automato->vetorTamanho[i] = -1;
	}
	
	return automato;
}

// Imprime na tela mensagens de erro durante a leitura do arquivo
// a partir dos limites definidos no enunciado do projeto.
// As mensagens de erro fornecem referências para limites dos valores digitados

void mostrarErro(int linha, int tamanhoMinimo, int tamanhoMaximo)
{
	cout << "\nOcorreu um erro na leitura do arquivo: "
	<< "foi digitado um valor invalido na linha " << linha << ".\n";
	
	// Linha 1: tamanho do alfabeto E
	// Linha 2: símbolos do alfabeto E (estourou o limite)
	// Linha 3: tamanho do conjunto de estados Q
	if (linha == 1 || (linha == 2 && tamanhoMinimo == 1) || linha == 3)
	{
		cout << "Quantidade minima permitida: " << tamanhoMinimo 
		<< "\nQuantidade maxima permitida: " << tamanhoMaximo;
	}
	
	// linha 2: símbolos do alfabeto E (inconsistente)
	// Linha 5: estados do conjunto de estados finais F
	else if ((linha == 2 && tamanhoMinimo == tamanhoMaximo )|| linha == 5)
	{
		cout << "A quantidade de valores digitada deve ser coerente com o valor da linha anterior: " 
		<< tamanhoMaximo;
	}
	
	// Linha 4: tamanho do conjunto de estados finais F
	else if (linha == 4)
	{
		cout << "A quantidade de F deve ser sempre maior que 1 " 
		<< "e menor ou igual a quantidade de Q.\n"
		<< "Quantidade de Q: " << tamanhoMaximo;
	}
	
	// Linha 7-~: transições da função de transição f
	else if (linha > 6)
	{
		cout << "Expressao de transicao invalida!\n"
		<< "Formato valido: numero simbolo numero\n"
		<< "Quantidade de elementos necessaria: " << tamanhoMaximo;
	}
	
	cout << "\nPor favor, altere o arquivo e tente novamente.\n";
}

// A função abre um arquivo texto e associa as informações de cada linha 
// com um certo atributo da estrutura AFD por meio do método getline(),
// seja até o final da linha ('\n'), seja até um espaço em branco (' ')

bool lerArquivoAFD(string nomeArquivo, AFD* automato)
{
	ifstream arquivoAFD;
	int i = 0, k = 0, linha = 1;
	string cadeiaTemp;
	arquivoAFD.open(nomeArquivo);
	if (!arquivoAFD.is_open())
	{
		cout << "Erro na abertura do arquivo";
		return false;
	}
	
	cout << "\nO arquivo foi aberto com sucesso! Lendo o conteudo do arquivo...\n";
	
	getline(arquivoAFD, cadeiaTemp, '\n');
	automato->vetorTamanho[0] = stoi(cadeiaTemp); // quantidade de símbolos de E
	
	// neste momento, se o valor da linha for menor que 1 ou maior que 12: erro
	if (automato->vetorTamanho[0] < 1 || automato->vetorTamanho[0] > 12)
	{
		mostrarErro(linha, 1, 12);
		automato = nullptr;
		return false;
	}
		
	linha++;
	
	getline(arquivoAFD, cadeiaTemp, '\n');  // símbolos de E
	
	// neste momento, se a quantidade de símbolos for menor que 1 ou maior que 12: erro
	// 23 é o tamanho da string contando os espaços em branco que separam os caracteres
	if (cadeiaTemp.length() < 1 || cadeiaTemp.length() > 23)
	{
		mostrarErro(linha, 1, 12);
		automato = nullptr;
		return false;
	}
	
	while (i < cadeiaTemp.length())
	{
		if (cadeiaTemp[i] != ' ')
		{
			automato->E[k] = cadeiaTemp[i];
			k++;
		}
		i++;
	}
	
	// neste ponto, compara-se o valor de símbolos atribuídos com a quantidade
	// definida na linha anterior. se for inconsistente: erro
	if (k != automato->vetorTamanho[0])
	{
		mostrarErro(linha, automato->vetorTamanho[0], automato->vetorTamanho[0]);
		automato = nullptr;
		return false;	
	}	
	
	cout << "\nAlfabeto E lido com sucesso!\n";
	linha++;
	
	getline(arquivoAFD, cadeiaTemp, '\n');
	automato->vetorTamanho[1] = stoi(cadeiaTemp); // quantidade de estados de Q
	
	// nesta posição, se o valor da linha for menor que 1 ou maior que 30: erro
	if (automato->vetorTamanho[1] < 1 || automato->vetorTamanho[1] > 30)
	{
		mostrarErro(linha, 1, 30);
		automato = nullptr;
		return false;
	}
	
	for (i = 0; i < automato->vetorTamanho[1]; i++)
	{
		automato->Q[i] = i;
	}
	
	// q0 já é implícito como 0
	cout << "\nConjunto de estados Q lido com sucesso, bem como o estado q0\n";
	linha++;
	
	getline(arquivoAFD, cadeiaTemp, '\n');
	automato->vetorTamanho[2] = stoi(cadeiaTemp); // quantidade de estados finais de F
	
	// neste momento, se o valor da linha for menor que 1 ou maior que Q: erro
	if (automato->vetorTamanho[2] < 1 || (automato->vetorTamanho[2] > automato->vetorTamanho[1]))
	{
		mostrarErro(linha, 1, automato->vetorTamanho[1]);
		automato = nullptr;
		return false;
	}
	linha++;
	
	i = 0;
	while (i != automato->vetorTamanho[2] - 1)
	{
		getline(arquivoAFD, cadeiaTemp, ' ');
		automato->F[i] = stoi(cadeiaTemp);
		i++;
	}
	
	getline(arquivoAFD, cadeiaTemp, '\n');
	
	if (cadeiaTemp.length() != 1)
	{
		mostrarErro(linha, 1, automato->vetorTamanho[2]);
		automato = nullptr;
		return false;
	}
	
	automato->F[i] = stoi(cadeiaTemp);
	
	cout << "\nConjunto de estados finais F lido com sucesso!\n";
	linha++;
	
	getline(arquivoAFD, cadeiaTemp, '\n');
	automato->vetorTamanho[3] = stoi(cadeiaTemp); // quantidade de transições de f
	
	automato->f = definirF(automato->vetorTamanho[3]); // alocação dinâmica do vetor de f
	
	linha++;
	i = 0;
	bool estadoPertence = false;
	
	// divide-se a função de transição em três a partir dos espaços em branco
	// se o estado atual ou de chegada digitado não pertencer a Q: erro
	// se o tamanho do char for diferente de 1: erro
	while (i != automato->vetorTamanho[3])
	{
		getline(arquivoAFD, cadeiaTemp, ' ');
		automato->f[i].qAtual = stoi(cadeiaTemp);
		for (int q : automato->Q)
		{
			if (automato->f[i].qAtual == q)	estadoPertence = true;
		}
		if (estadoPertence == false)
		{
			mostrarErro(linha, 3, 3);
			cout << "\nO estado atual digitado '" << automato->f[i].qAtual << "' nao pertence a Q\n";
			delete[] automato->f;
			automato = nullptr;
			return false;
		}
		
		getline(arquivoAFD, cadeiaTemp, ' ');
		if (cadeiaTemp.length() != 1)
		{
			mostrarErro(linha, 3, 3);
			automato = nullptr;
			return false;
		}
		automato->f[i].sLido = cadeiaTemp[0];
		
		getline(arquivoAFD, cadeiaTemp, '\n');
		automato->f[i].qChegada = stoi(cadeiaTemp);
		
		estadoPertence = false;
		for (int q : automato->Q)
		{
			if (automato->f[i].qChegada == q)	estadoPertence = true;
		}
		if (estadoPertence == false)
		{
			mostrarErro(linha, 3, 3);
			cout << "\nO estado de chegada digitado '" << automato->f[i].qChegada << "' nao pertence a Q\n";
			delete[] automato->f;
			automato = nullptr;
			return false;
		}
		
		estadoPertence = false;
		i++;
		linha++;
	}
	
	cout << "\nTransicoes lidas com sucesso!\n";
	
	// o arquivo foi lido com sucesso
	return true;
}

// Compara um estado atual e um símbolo lido com uma das expressões
// da função de transição f, retornando o estado de chegada caso
// a expressão seja igual e -1 caso contrário

int analisarFuncao(int qAtual, char s, Trans func)
{
	if (qAtual == func.qAtual && s == func.sLido) return func.qChegada;

	return -1;
}

// A função avalia se, no estado atual, cada símbolo de uma cadeia fornecida 
// (usuário ou arquivo) tem um estado de chegada. Se todos os símbolos
// forem identificados dentro das expressões do vetor de transição,
// sai do loop. Caso contrário, retorna false. Saindo do loop, caso o estado atual
// seja um estado final pertencente a F, retorna true

bool avaliarCadeia(string cadeia, AFD* automato)
{
	int q1, q0 = 0, i = 0;
	
	// cadeia vazia
	if (cadeia == " ")
	{
		for (i = 0; i < automato->vetorTamanho[2]; i++)
		{
			if (automato->q0 == automato->F[i]) return true;
		}
	}
	
	i = 0;
	for (char c : cadeia)
	{
		q1 = analisarFuncao(q0, c, automato->f[i]);
		while (q1 == -1)
		{
			i++;
			q1 = analisarFuncao(q0, c, automato->f[i]);
			if (i == automato->vetorTamanho[3]) break;
		}

		if (q1 == -1) return false;

		q0 = q1;
		i = 0;
	}
	
	for (i = 0; i < automato->vetorTamanho[2]; i++)
	{
		if (q0 == automato->F[i])
		{
			return true;
		}
	}
	
	return false;
}

// Lê um arquivo com um valor n na primeira linha e n cadeias a serem avaliadas
// Caso o tamanho da cadeia seja maior que 100, ela não é processada.
// Caso contrário, chama o método avaliarCadeia() para realizar a análise

bool lerArquivoCadeia(string nomeArquivo, AFD* automato)
{
	ifstream arquivoCadeia;
	int quantidadeC, i = 0;
	bool flag;
	string cadeia;
	arquivoCadeia.open(nomeArquivo);
	if (!arquivoCadeia.is_open())
	{
		cout << "Erro na abertura do arquivo";
		return false;
	}
	getline(arquivoCadeia, cadeia, '\n');
	quantidadeC = stoi(cadeia);
	cout << "\n";
	while (i != quantidadeC)
	{
		getline(arquivoCadeia, cadeia, '\n');
		if (cadeia.length() > 100)
		{
			flag = (cadeia.length() < 1);
			cout << "Cadeia " << i + 1 << ": Nao-processada -> ";
			(flag == true) ? cout << "Contem 0 simbolos na cadeia\n"
			: cout << "Contem mais que 100 simbolos concatenados\n";
		}
		else
		{
			string resposta = " ";
			flag = avaliarCadeia(cadeia, automato);
			(flag == true) ? resposta = "Aceita\n" : resposta = "Rejeitada\n";
			cout << "Cadeia " << i + 1 << ": " << cadeia << " -> " << resposta;
		}
		i++;
	}
	return true;
}

// Imprime os valores de cada atributo da quíntupla do autômato - 
// (Q, E, q0, f, F) - com formatação adequada e laços que utilizam
// os tamanhos dos atributos especificados no arquivo AFD de entrada

void mostrarQuintupla(const AFD* automato)
{
	int i;
	cout << "\nMostrando a 5-tupla do AFD M: \n\n";

	cout << "- Conjunto de estados:\nQ = {";
	for (i = 0; i < automato->vetorTamanho[1]; i++)
	{
		if (automato->Q[i + 1] == -1)
		{
			cout << "q" << automato->Q[i] << "}\n\n";
			break;
		}
		else cout << "q" << automato->Q[i] << ", ";
	}

	cout << "- Alfabeto:\nE = {";
	for (i = 0; i < automato->vetorTamanho[0]; i++)
	{
		if (automato->E[i + 1] == ' ')
		{
			cout << automato->E[i] << "}\n\n";
			break;
		}
		else cout << automato->E[i] << ", ";
	}

	cout << "- Estado inicial:\nq0 = q" << automato->q0 << "\n\n";

	cout << "- Conjunto de estados finais:\nF = {";
	for (i = 0; i < automato->vetorTamanho[2]; i++)
	{
		if (automato->F[i + 1] == -1)
		{
			cout << "q" << automato->F[i] << "}\n\n";
			break;
		}
		else cout << "q" << automato->F[i] << ", ";
	}

	cout << "- Funcao de transicao:\n";
	for (i = 0; i < automato->vetorTamanho[3]; i++)
	{
		cout << "f(q" << automato->f[i].qAtual << ", "
			 << automato->f[i].sLido << ") = q"
			 << automato->f[i].qChegada << "\n";
		if (automato->f[i + 1].qAtual == -1) break;
	}

}

// Exige uma cadeia de entrada do usuário e chama
// o método avaliarCadeia() para analisá-la

void responderCadeia(AFD* automato)
{
	string cadeia;
	cout << "Digite uma cadeia para ser avaliada pelo AFD M: ";
	getline(cin, cadeia);
	bool resposta = avaliarCadeia(cadeia, automato);
	(resposta == true) ? cout << "\nCadeia aceita!\n" : cout << "\nCadeia rejeitada!\n";
}