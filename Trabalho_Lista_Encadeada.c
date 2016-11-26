#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declara��o do tipo de estrutura utilizada, no caso, uma vari�vel do tipo composta
typedef struct nodo{
        int cod; // Variavel que recebera o codigo do cadastra
        char nome [40]; // Variavel do tipo char que armazenara o nome do registro
        char endereco[50]; // Variavel do tipo char que armazenara o endereco do registro
        int telefone; // Variavel do tipo int que armazenara o telefone do registro
        struct nodo *prox; // Ponteiro do tipo struct que apontara para a proxima estrutura do registro
    } Cadastro; // Nome da variavel composta: Cadastro

// Func�o para verificar se o c�digo informado pelo usu�rio j� n�o est� em uso
int verificarDuplicidade(Cadastro *l, int cod){
    int flag = 0; // Declara��o de variavel

    for(;l; l = l->prox){ // Enquanto l (Cadastro), l aponta para a pr�xima estrutura, fazendo a varredura em busca do c�digo
        if(cod == l->cod){ // Se cod for igual ao cod armazenado que aponta para os cadastros criados, entra no la�o
            flag = 1; // Variavel flag recebe o valor "1", caso condi��o seja verdadeira
            printf("\nCodigo ja existente, por favor tente outro!\n"); // Imprime mensagem na tela
        }
    }
    return flag; // Retorna 1 ou 0
}
// Fun��o para inserir novo registro na lista
Cadastro *inserir(Cadastro *l){
    Cadastro *novo, *p; // Criacao de 2 ponteiros para a struct Cadastro
    char nome[40], endereco[50]; // Declaracao de variaveis que irao armazenar o nome e endereco
    int telefone, cod; // Variaveis que armazenarao o codigo e o telefone

    do{
        printf("\nInsira o numero do registro: "); // Imprime na tela, solicita ao usuario o numero do registro
        scanf ("%d", &cod); // Armazena o inteiro digitado na variavel cod, caso nao exista ainda
    } while(verificarDuplicidade(l,cod)==1); // Testar fun��o, enquanto o c�digo digitado j� estiver em uso printar a mensagem


    printf("\nInforme o nome: "); // Imprime na tela
    fflush(stdin); // Limpa o buffer de memoria
    gets(nome); // Captura os caracteres digitados pelo usuario e armazena na variavel nome

    printf("\nInforme o telefone: "); // Imprime na tela
    scanf ("%d", &telefone); // Armazena os caracteres digitados na variavel telefone

    printf("\nInforme o endereco: "); // Imprime na tela
    fflush(stdin); // Limpa o buffer de memoria
    gets(endereco); // Captura os caracteres digitados pelo usuario e armazena na variavel endereco

    novo = (Cadastro *)malloc(sizeof(Cadastro)); // ponteiro novo recebe alocacao de espaco de memoria para a estrutura Cadastro
    novo->cod = cod; // Ponteiro "novo" aponta para cod, essa variavel recebe os valores
    strcpy(novo->nome, nome); // Ponteiro "novo" aponta para nome, essa variavel recebe os valores
    strcpy(novo->endereco, endereco); // Ponteiro "novo" aponta para endereco, onde essa recebe os valores
    novo->telefone = telefone; // Ponteiro "novo" aponta para telefone, essa recebe os valores
    novo->prox = NULL; // Struct prox recebe o valor NULL

    if(!l) return novo; // Testa condicao e retorna novo struct

    for(p=l; p->prox; p = p->prox); // Verifica os paramentros recebidos, para entrar no laco
    p->prox = novo; // variavel auxilia p, aponta para prox, que recebe novo, ou seja, *novo struct

    return l; // Retorna l = Cadastro com os dados criados
}

// Fun��o para excluir o c�digo selecionado
Cadastro * excluirSelecionado(Cadastro *l){ // Recebe os parametros de Cadastro
    Cadastro *pRetaguarda=NULL, *p;  // Criacao de dois ponteiros, sendo que pRetaguarda inicializa com o valor NULL

    if(!l){ // Se diferente de 'l', ou seja, n�o existir nenhum registro criado
        printf("\nLista vazia!!!\n"); // Imprimir mensagem na tela
        return l; // Retorna 'l'
    }
    // Solicita ao usu�rio o n�mero do c�digo a ser exclu�do
    int codExcluir; // Declaracao de variavel a armazenar o codigo a ser excluido
    printf("\nInsira o numero do cadastro a ser excluido: "); // Imprime a mensagem na tela
    scanf("%d", &codExcluir); // Armazena o caracter digitado na variavel 'codExcluir'

    for(p = l; p && p->cod != codExcluir; p = p->prox) // Verifica os paramentros recebidos, para entrar no laco
	pRetaguarda = p; // ponteiro auxiliar 'pRetaguarda', 'recebe p'

    // Se for o primeiro elemento
    if(p==l){ // Se 'p' for igual a 'l' (Cadastro), entra na condicao
        l = l->prox; // 'l' apontara para proxima estrutura
        free(p); // Libera 'p'
        return l; // Retorna l (Cadastro)
    }
    // Se for o �ltimo
    if(!pRetaguarda->prox && pRetaguarda->cod == codExcluir){ // Condicao, se cod de 'pRetaguarda' igual ao 'codExcluir' e 'pRetaguarda' que aponta para o proximo diferente de 'p'
        free(pRetaguarda); // Libera o espaco de pRetaguarda
        return l; // Retorna l (Cadastro)
    }
    // Caso n�o encontre o codExcluir na lista
    if(!pRetaguarda->prox && pRetaguarda->cod != codExcluir){ // Se 'pRetaguarda' apontar para prox e cod de 'pRetaguarda' diferente de 'codExcluir'
        printf("\nDado n encontrado"); // Imprime na tela
        return l; // Retorna l (Cadastro)
    }else{ // Caso contrario
    // No meio
    pRetaguarda->prox = p->prox; // pRet->prox recebe 'p->prox'
    free(p); // Libera o espaco de 'p'
    return l; // Retorna l (Cadastro)
    }
}
    // Exibe o cadastro selecionado
void exibir(Cadastro *l){
    Cadastro *p; // Criacao de ponteiro auxilial

    for(;l; l = l->prox){ // Testa condicao para entrar no laco, inicializa com cadastro, aponta para proximo
        printf("Codigo: %d \n",l->cod); // Imprime na tela
        printf("Nome: %s \n",l->nome); // Imprime na tela
        printf("Telefone: %d \n",l->telefone); // Imprime na tela
        printf("Endereco: %s \n",l->endereco); // Imprime na tela
    }
    return; // Retorna vazio
}
    // Fun��o para varres a lista e buscar o c�digo
void buscarCadastro(Cadastro *l){
    Cadastro *p; // Criacao de ponteiro auxiliar

    if(!l){ // Se diferente de l (Cadastro)
        printf("\nLista vazia!!!\n"); // Imprime na tela
        return; // Retorna vazio
    }
    int codBusca; // Declaracao de variavel do tipo int
    printf("\nInsira o numero do cadastro a ser buscado: "); // Imprime na tela
    scanf("%d", &codBusca); // Armazena na variavel codBusca o caractere digitado

    for(;l; l = l->prox){ // Testa condicao para entrar no laco, inicializa l, l aponta para proximo
        if(codBusca == l->cod){ // Se 'codBusca' igual ao cod da struct
            printf("Codigo: %d \n",l->cod); // Imprime na tela
            printf("Nome: %s \n",l->nome); // Imprime na tela
            printf("Telefone: %d \n",l->telefone); // Imprime na tela
            printf("Endereco: %s \n",l->endereco); // Imprime na tela
            return; // Retorna vazio
        }
    }
    printf("\nCodigo nao encontrado!\n"); // Imprime na tela
    return; // Retorna vazio
}
    // Fun��o main que imprime o Menu na tela
void menu(){
    system("color a"); // Altera a cor padrao dos caracteres a serem mostrados na tela
    printf("\n\t\t#### Menu Principal ####\n"); // Imprime na tela
    printf("\n1- Inserir Registro"); // Imprime na tela
    printf("\n2- Buscar Registro"); // Imprime na tela
    printf("\n3- Excluir Registro"); // Imprime na tela
    printf("\n4- Creditos"); // Imprime na tela
    printf("\n5- Sair do Programa"); // Imprime na tela
    printf("\n\nDigite a opcao desejada: "); // Imprime na tela: solicita ao usuario selecionar uma opcao
}
    // Fun��o para imprimir os cr�ditos na tela
void creditos(){
    system("cls"); // Limpa a tela
    printf("\t\t\t\tCREDITOS\n\n"); // Imprime na tela
    printf("Programa desenvolvido pelos alunos:\n\n"); // Imprime na tela
    printf("Juliana Xavier\n"); // Imprime na tela
    printf("Alana Azevedo\n"); // Imprime na tela
    printf("Erico Edu Correa\n\n"); // Imprime na tela
}
    // Fun��o principal
main(){
    Cadastro *listaCliente = NULL; // Criacao de ponteiro auxiliar tipo Cadastro, que recebe valor de NULL
    int opMenu = 0; // Variavel 'opMenu', inicializa com valor zero
    // Verifica a op��o escolhida pelo usu�rio
    for(;opMenu != 5;){ // Testa condicao para entrar no laco for
        system("cls"); // Limpar a tela
        menu(); // inicializa menu
        scanf("%d", &opMenu); // Armazena o caracter digitado pelo usuario na variavel 'opMenu'

        switch (opMenu){
    // Chama a fun��o para inserir novo registro
            case 1:
                listaCliente = inserir(listaCliente); // ponteiro auxiliar recebe funcao 'inserir', com parametros 'listaCliente'
                system("pause"); // Pausa o programa, solicita pressionar uma tecla para continuar
                break; // Sair do switch
    // Fun��o para varrer a lista e buscar o registro
            case 2:
                buscarCadastro(listaCliente); // Chama a funcao 'buscarCadastro', recebe parametros 'listaCliente'
                system("pause"); // Pausa o programa, solicita pressionar uma tecla para continuar
                break; // Sair do switch
    // Cahama a fun��o para excluir o registro,
            case 3:
                listaCliente = excluirSelecionado(listaCliente); // ponteiro auxiliar recebe funcao 'excluirSelecionad'o com parametros 'listaCliente'
                system("pause"); // Pausa o programa, solicita pressionar uma tecla para continuar
                break; // Sair do switch
    // Chama a fun��o creditos, se o usuario digitar a tecla '4'
            case 4:
                creditos(listaCliente);
                system("pause"); // Pausa o programa, solicita pressionar uma tecla para continuar
                break; // Sair do switch
    // Sai do programa caso o usuario digite a tecla '5'
            case 5:
                printf("\nFim do programa!!!"); // Imprime na tela
                return; // Sair do switch
    // Caso o usu�rio n�o digite nenhuma das op��es do menu
            default:
                printf("\nOpcao invalida, escolha uma das opcoes do menu!\n"); // Imprime na tela
                system("pause"); // Pausa o programa, solicita pressionar uma tecla para continuar

        }
    }
}
