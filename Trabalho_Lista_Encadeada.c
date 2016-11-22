#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct nodo{
        int cod;
        char nome [40];
        char endereco[50];
        int telefone;
        struct nodo *prox;
    }Cadastro;

// Verifica se o código já não está em uso
int verificarDuplicidade(Cadastro *l, int cod){
    int flag = 0;

    for(;l; l = l->prox){
        if(cod == l->cod){
            flag = 1;
            printf("\nCodigo ja existente, por favor tente outro!\n");
        }
    }
    return flag;
}
// Função para inserir novo registro na lista
Cadastro *inserir(Cadastro *l){
    Cadastro *novo, *p;
    char nome[40], endereco[50];
    int telefone, cod;

    printf("\nInforme o nome: ");
    fflush(stdin);
    gets(nome);

    do{
        printf("\nInsira o numero do registro: ");
        scanf ("%d", &cod);
    }while(verificarDuplicidade(l,cod)==1); // Testar função, enquanto o código digitado já estiver em uso printar a mensagem

    printf("\nInforme o telefone: ");
    scanf ("%d", &telefone);

    printf("\nInforme o endereco: ");
    fflush(stdin);
    gets(endereco);

    novo = (Cadastro *)malloc(sizeof(Cadastro));
    novo->cod = cod;
    strcpy(novo->nome, nome);
    strcpy(novo->endereco, endereco);
    novo->telefone = telefone;
    novo->prox = NULL;

    if(!l)return novo;

    for(p=l; p->prox; p = p->prox);
    p->prox = novo;

    return l;
}

// Função para excluir o código selecionado
Cadastro * excluirSelecionado(Cadastro *l){
    Cadastro *pRetaguarda=NULL, *p;
    
    if(!l){
        printf("\nLista vazia!!!\n");
        return l;
    }
    // Solicita ao usuário o número do código a ser excluído
    int codExcluir;
    printf("\nInsira o numero do cadastro a ser excluido: ");
    scanf("%d", &codExcluir);

    for(p = l;p && p->cod != codExcluir; p = p->prox) pRetaguarda = p;

    // Se for o primeiro elemento

    if(p==l){
        l = l->prox;
        free(p);
        return l;
    }
    // Se for o último

    if(!pRetaguarda->prox && pRetaguarda->cod == codExcluir){
        free(pRetaguarda);
        return l;
    }
    // Caso não encontre o codExcluir na lista
    if(!pRetaguarda->prox && pRetaguarda->cod != codExcluir){
        printf("\nDado n encontrado");
        return l;
    }else{
    // No meio
    pRetaguarda->prox = p->prox;
    free(p);
    return l;
    }
}
    // Exibe o cadastro selecionado
void exibir(Cadastro *l){
    Cadastro *p;

    for(;l; l = l->prox){
        printf("Nome: %s \n",l->nome);
        printf("Codigo: %d \n",l->cod);
        printf("Telefone: %d \n",l->telefone);
        printf("Endereco: %s \n",l->endereco);
    }
    return;
}
    // Função para varres a lista e buscar o código
void buscarCadastro(Cadastro *l){
    Cadastro *p;

    if(!l){
        printf("\nLista vazia!!!\n");
        return ;
    }
    int codBusca;
    printf("\nInsira o numero do cadastro a ser buscado: ");
    scanf("%d", &codBusca);

    for(;l; l = l->prox){
        if(codBusca == l->cod){
            printf("Nome: %s \n",l->nome);
            printf("Codigo: %d \n",l->cod);
            printf("Telefone: %d \n",l->telefone);
            printf("Endereco: %s \n",l->endereco);
            return;
        }
    }
    printf("\nCodigo nao encontrado!\n");
    return;
}
    // Função main que imprime o Menu na tela
void menu(){
    system("color a");
    printf("\n\t\t#### Menu Principal ####\n");
    printf("\n1- Inserir Registro");
    printf("\n2- Buscar Registro");
    printf("\n3- Excluir Registro");
    printf("\n4- Creditos");
    printf("\n5- Sair do Programa");
    printf("\n\nDigite a opcao desejada: ");
}
    // Função para imprimir os créditos na tela
void creditos(){
    system("cls"); // Limpa a tela
    printf("\t\t\t\tCREDITOS\n\n");
    printf("Programa desenvolvido pelos alunos:\n\n");
    printf("Juliana Xavier\n");
    printf("Alana Azevedo\n");
    printf("Erico Edu Correa\n\n");
}
    // Função principal
main(){
    Cadastro *listaCliente = NULL;
    int opMenu = 0;
    // Verifica a opção escolhida pelo usuário
    for(;opMenu != 5;){
        system("cls");
        menu();
        scanf("%d", &opMenu);

        switch (opMenu){
    // Chama a função para inserir novo registro  
            case 1:
                listaCliente = inserir(listaCliente);
                system("pause");
                break;
    // Função para varrer a lista e buscar o registro
            case 2:
                buscarCadastro(listaCliente);
                system("pause");
                break;
    // Cahama a função para excluir o registro           
            case 3:
                listaCliente = excluirSelecionado(listaCliente);
                system("pause");
                break;
    // Chama a função creditos          
            case 4:
                creditos(listaCliente);
                system("pause");
                break;
    // Sai do programa            
            case 5:
                printf("\nFim do programa!!!");
                return;
    // Caso o usuário não digite nenhuma das opções do menu         
            default:
                printf("\nOpcao invalida, escolha uma das opcoes do menu!\n");
                system("pause");

        }
    }
}
