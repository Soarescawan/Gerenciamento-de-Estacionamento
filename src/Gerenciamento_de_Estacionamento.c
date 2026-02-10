#include "structs.h"
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h> 
#include <string.h>


/* Código Cawan Soares e Árthur Gandra - Gerenciamento de Estacionamento 
    Versão: 1.0
    Data: 20/12/2025 OBS: Data quando o codigo foi iniciado
    Descrição: Sistema de gerenciamento de estacionamento com cadastro, remoção, listagem e busca de veículos.
*/    




int main(){

setlocale(LC_ALL, "PORTUGUESE");

Veiculo *lista = NULL;
Usuario *lista1= NULL;
Usuario *encontrado = NULL;

int opcao;
char *placa = NULL;
char *confirma =NULL;
char *cpf= NULL;




    do {
        menu();
        printf("\n==== Escolha a opcao desejada ==== \n");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {

            case 1:
                printf(" \n===== Cadastrar Proprietários =====");
                lista1 = cadastrarCondutor(lista1);
                break;

            case 2:
                printf("\n ======  Cadastrar Veiculos ======");
                lista = inserir_veiculo(lista,lista1);
                break;

            case 3:
                printf("\n===== Digite a placa  =====: ");
                placa = ler_string();



                printf("\nVoce realmente deseja remover este veiculo da Placa %s ? (s/n): ",placa);
                confirma = ler_string();



                if (strcmp(confirma,"n") == 0 || strcmp(confirma, "N") == 0 || strcmp(confirma,"Nao") == 0 || strcmp(confirma ,"NAO") == 0 ) {
                    printf("\nRemocao cancelada.\n");
                    free(confirma);
                    free(placa);
                    break;

                }else{
                    printf("\nRemovendo veiculo com placa: %s", placa);
                    lista = remover_veiculo(lista, placa);
                    free(confirma);
                    free(placa);

                    break;
                }

            case 4:
                printf("\n ======= Veiculos no Estacionamento ======= \n");
                listar_veiculos(lista);
                break;

            case 5:
                printf("\n ===== Digite a Placa ===== \n");
                placa = ler_string();
                buscar_veiculo(lista, placa);
                free(placa);
                break;



            case 6:

            printf("\n ===== Digite o CPF ===== \n");
            cpf = ler_string();
                encontrado = buscar_proprietario(lista1,cpf);
            

                if(!encontrado){
                    printf("\n------ Proprietario não encontrado ------\n");
                    free(cpf);
                    break;

                }else{

                     printf("\n------ Proprietario encontrado ------\n");
                     imprime_proprietario(encontrado);
                     free(cpf);

                }



                break;


            case 7:
                printf("\n ===== Remover Proprietario ===== \n");
                printf("\nInsira o CPF para a exclusao do cadastro do proprietario: \n");
                cpf = ler_string();

                printf("\nOBS: Ao remover o proprietario, todos os veiculos associados a ele serão removidos tambem, pois nao pode haver veiculos sem dono.\n");


                printf("\nVoce realmente deseja remover este Proprietario? (s/n): ");
                confirma = ler_string();


                if (strcmp(confirma, "N") == 0 || strcmp(confirma, "n") == 0 || strcmp(confirma, "Nao") == 0 || strcmp(confirma ,"NAO") == 0) {
                    printf("\nRemocao cancelada.\n");
                    free(cpf);
                    free(confirma);
                    break;

                }else{
                    printf("\nRemovendo Proprietario: \n");
                    lista1 = remover_proprietario(lista1,&lista, cpf);


                    printf("\n");
                    free(cpf);
                    free(confirma);
                    break;
                }

            case 8:
                printf("\n---------- Exibindo todos os Proprietarios ja Cadastrados ----------\n");

                bancoDeDadosProprietarios();

                break;
            
            case 9:

            printf("\n---------- Exibindo Todos Os veiculos ja cadastrados ----------\n");
            bancoDeDadosVeiculos();
            break;



            case 10:
                printf("\nEncerrando sistema...\n");
                break;
            

            default:
                printf("\nOpcao invalida!\n");

         }


    } while (opcao != 9);

    return 0;
}

