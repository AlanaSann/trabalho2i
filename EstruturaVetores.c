#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

// int *vetorPrincipal[TAM];
struct vetor {
  int vetorAuxiliar;   // guarda os numeros adicionados
  int quantidadeAtual; // quantidade de numeros adicionados
  int tamanhoVAux;     // tamanho do vetor auxiliar.
  int *ponteiro;
};

typedef struct vetor Vetor;

Vetor *VetorPrincipal[TAM]; // matriz

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/

int criarEstruturaAuxiliar(int posicao, int tamanho) {
  int retorno = 0, variavel;
  int i, *ponteiro;
  ponteiro = &posicao;

  // a posicao pode já existir estrutura auxiliar
  if (VetorPrincipal[posicao - 1] != NULL) {
    retorno = JA_TEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }

  // se posição é um valor válido {entre 1 e 10}
  retorno = ehPosicaoValida(posicao);
  if (retorno != SUCESSO) {
    return retorno;
  }

  // o tamanho nao pode ser menor que 1
  if (tamanho < 1) {
    retorno = TAMANHO_INVALIDO;
    return retorno;
  }

  // deu tudo certo, crie
  VetorPrincipal[posicao - 1] = malloc(sizeof(VetorPrincipal) * tamanho);

  // o tamanho ser muito grande
  if (VetorPrincipal[posicao - 1] == NULL) {
    retorno = SEM_ESPACO_DE_MEMORIA;
    return retorno;
  }

  VetorPrincipal[posicao - 1]->tamanhoVAux = tamanho;
  VetorPrincipal[posicao - 1]->quantidadeAtual = 0;

  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor) {
  int retorno = 0;
  int existeEstruturaAuxiliar = 0;
  int temEspaco = 0;
  int posicao_invalida = 0;
  // posicao invalida
  retorno = ehPosicaoValida(posicao);
  if (retorno != SUCESSO) {
    return retorno;
  }
  // se a posicao  já existir estrutura auxiliar
  if (VetorPrincipal[posicao - 1] == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }

  // insere o numero na estrutura
  if (VetorPrincipal[posicao - 1]->quantidadeAtual <
      VetorPrincipal[posicao - 1]->tamanhoVAux) {
    VetorPrincipal[posicao - 1][VetorPrincipal[posicao - 1]->quantidadeAtual]
        .vetorAuxiliar = valor;
    VetorPrincipal[posicao - 1]->quantidadeAtual++;
    retorno = SUCESSO;

  } else {
    retorno = SEM_ESPACO;
  }
  return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar
da seguinte forma [3, 8, 7,  ,  ,  ]. Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao) {
  int retorno;
  retorno = ehPosicaoValida(posicao);
  if (retorno != SUCESSO) {
    return retorno;
  }
  // se a posicao  já existir estrutura auxiliar
  if (VetorPrincipal[posicao - 1] == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }
  // exclusão
  if (VetorPrincipal[posicao - 1]->quantidadeAtual != 0) {
    VetorPrincipal[posicao - 1]->quantidadeAtual--;
    retorno = SUCESSO;
    return retorno;
  } else {
    retorno = ESTRUTURA_AUXILIAR_VAZIA;
    return retorno;
  }
  return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições
anteriores ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o
valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ] Obs. Esta é
uma exclusão lógica Rertono (int) SUCESSO - excluido com sucesso 'valor' da
estrutura na posição 'posicao' ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
  int retorno, i, posicaoExcluir;
  retorno = ehPosicaoValida(posicao);
  if (retorno != SUCESSO) {
    return retorno;
  }
  // se a posicao  já existir estrutura auxiliar
  if (VetorPrincipal[posicao - 1] == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }
  // exclusão
  // printf("qtd %d\n", VetorPrincipal[posicao - 1]->quantidadeAtual);
  if (VetorPrincipal[posicao - 1]->quantidadeAtual != 0) {
    posicaoExcluir = BuscaNumero(posicao, valor);

    if (posicaoExcluir == NUMERO_INEXISTENTE) {
      retorno = NUMERO_INEXISTENTE;
      return retorno;
    }
    for (i = posicaoExcluir; i < VetorPrincipal[posicao - 1]->quantidadeAtual;
         i++) {
      if (i < VetorPrincipal[posicao - 1]->quantidadeAtual - 1) {
        VetorPrincipal[posicao - 1][i].vetorAuxiliar =
            VetorPrincipal[posicao - 1][i + 1].vetorAuxiliar;
      }
    }
    VetorPrincipal[posicao - 1]->quantidadeAtual--;
    
  } else {
    retorno = ESTRUTURA_AUXILIAR_VAZIA;
    return retorno;
  }
  retorno = SUCESSO;
  return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao) {
  int retorno = 0;
  if (posicao < 1 || posicao > 10) {
    retorno = POSICAO_INVALIDA;
    return retorno;
  }

  retorno = SUCESSO;
  return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar POSICAO_INVALIDA -
Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
  int retorno = 0, i;
  retorno = ehPosicaoValida(posicao);
  if (retorno != SUCESSO) {
    return retorno;
  }
  if (VetorPrincipal[posicao - 1] == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }
  for (i = 0; i < VetorPrincipal[posicao - 1]->quantidadeAtual; i++) {
    vetorAux[i] = VetorPrincipal[posicao - 1][i].vetorAuxiliar;
  }
  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao
(1..10)'. os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao
(1..10)' SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar POSICAO_INVALIDA -
Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {

  int retorno = 0, i, qtd;
  retorno = ehPosicaoValida(posicao);
  if (retorno != SUCESSO) {
    return retorno;
  }
  if (VetorPrincipal[posicao - 1] == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }
  for (i = 0; i < VetorPrincipal[posicao - 1]->quantidadeAtual; i++) {
    vetorAux[i] = VetorPrincipal[posicao - 1][i].vetorAuxiliar;
  }
  ordena(VetorPrincipal[posicao - 1]->quantidadeAtual, vetorAux);
  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares
estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {

  int i, j, retorno = 0, qtd = 0, vazias = 0;
  int fim;
  for (i = 0; i <= 9; i++) {
    if (VetorPrincipal[i] == NULL) {
      vazias++;
      continue;
    }
    if ((*VetorPrincipal[i]).quantidadeAtual == 0) {
      vazias++;
      continue;
    }
    fim = VetorPrincipal[i]->quantidadeAtual;
    for (j = 0; j < fim; j++) {
      vetorAux[qtd] = VetorPrincipal[i][j].vetorAuxiliar;
      qtd++;
    }
  }
  if (vazias == 10) {
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    return retorno;
  }
  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição
'posicao' TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares
estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {

  int i, j, retorno = 0, qtd = 0, vazias = 0;
  int fim;
  for (i = 0; i <= 9; i++) {
    if (VetorPrincipal[i] == NULL) {
      vazias++;
      continue;
    }
    if ((*VetorPrincipal[i]).quantidadeAtual == 0) {
      vazias++;
      continue;
    }
    fim = VetorPrincipal[i]->quantidadeAtual;
    for (j = 0; j < fim; j++) {
      vetorAux[qtd] = VetorPrincipal[i][j].vetorAuxiliar;
      qtd++;
    }
  }
  if (vazias == 10) {
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    return retorno;
  }
  ordena(qtd, vetorAux);
  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o
novo tamanho 'novoTamanho' + tamanho atual Suponha o tamanho inicial = x, e novo
tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser
sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {

  int retorno = 0, tamanhoInicial, tamanhoResultante;
  retorno = ehPosicaoValida(posicao);
  if (retorno != SUCESSO) {
    return retorno;
  }
  if (VetorPrincipal[posicao - 1] == NULL) {
    retorno = SEM_ESTRUTURA_AUXILIAR;
    return retorno;
  }
  tamanhoInicial = VetorPrincipal[posicao - 1]->tamanhoVAux;
  tamanhoResultante = tamanhoInicial + novoTamanho;
  if (tamanhoResultante < 1) {
    retorno = NOVO_TAMANHO_INVALIDO;
    return retorno;
  }
  // ponteiro  //tamanho
  VetorPrincipal[posicao - 1] = realloc(
      VetorPrincipal[posicao - 1], sizeof(VetorPrincipal) * tamanhoResultante);
  if (VetorPrincipal[posicao - 1] == NULL) {
    retorno = SEM_ESPACO_DE_MEMORIA;
    return retorno;
  }
  VetorPrincipal[posicao - 1]->tamanhoVAux = tamanhoResultante;
  if (tamanhoResultante < VetorPrincipal[posicao - 1]->quantidadeAtual) {
    VetorPrincipal[posicao - 1]->quantidadeAtual = tamanhoResultante;
  }
  retorno = SUCESSO;
  return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da
posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da
estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
  int retorno = 0;
  return VetorPrincipal[posicao - 1]->quantidadeAtual;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes
em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote() { return NULL; }

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em
vetorAux. Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio) {}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa

*/

void inicializar() {}

/*

Objetivo: finaliza o programa. deve ser chamado ao final do programa
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar() {
  int i;
  for (i = 0; i < 10; i++) {
    if (VetorPrincipal[i] == NULL) {
      free(VetorPrincipal[i]);
    }
  }
}

int BuscaNumero(int posicao, int numero) {
  int i;
  for (i = 0; i < (*VetorPrincipal[posicao - 1]).quantidadeAtual; i++) {
    if (numero == VetorPrincipal[posicao - 1][i].vetorAuxiliar) {
      return i;
    }
  }
  return NUMERO_INEXISTENTE;
}

void ordena(int qtdElementos, int vetor[]) {
  int i, j, aux;
  int n = qtdElementos;
  for (i = 1; i < n; i++) {
    for (j = 0; j < n - i; j++) {
      if (vetor[j] > vetor[j + 1]) {
        aux = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = aux;
      }
    }
  }
}
