 #include <stdio.h>
 #include "structs.h"
 #include "funcoes.h"
 #include <time.h>
 #include <stdlib.h>
 #include <string.h>
 #include <locale.h>
 #include <ctype.h>


char *forma_pagamento() {
    int opcao;
    while(1){
        printf("\nEscolha a forma de pagamento:\n");
        printf("1 - Dinheiro\n");
        printf("2 - Cartao de Credito\n");
        printf("3 - Cartao de Debito\n");
        printf("4 - Pix\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                return strdup("Dinheiro");

            
            case 2:
                return strdup("Credito");

            case 3:
                return strdup("Debito");
            
            case 4:
                return strdup( "Pix");
                
            default:
                printf("Opcao invalida. Definindo como 'Nao especificado'.\n");
                printf("\nTente novamente.\n");
                
                continue;
        }
    }

    
}


void buscar_veiculo(Veiculo *lista, char *placa) { 

        while (lista != NULL) { 
            if (strcmp(lista->placa, placa) == 0) {
                 printf("\n--- Veiculo Encontrado ---\n"); 
                 printf("\nVaga: %s",lista->vaga_do_veiculo);
                 printf("\nPlaca: %s", lista->placa);
                 printf("\nModelo: %s", lista->modelo); 
                 printf("\nCor: %s", lista->cor); 
                 printf("\nEntrada: %s", lista->hora_entrada);
                 printf("\nData de Pagamento: %s", lista->Data_de_pagamento);
                 printf("\nTempo de Permanencia: %s", lista->tempo_permanencia);
                 printf("\nForma de Pagamento: %s", lista->forma_pagamento);
                 printf("\nValor pago: %s ", lista->valor_pago);
                 printf("\nTipo de Vaga: %s", lista->tipo_vaga);
                 if(lista->condutor){
                    printf("\nProprietario: %s", lista->condutor->nome);
                 }
                 printf("\n-------------------------------\n");
                 


                 return; 
                }
                 
                 lista = lista->prox;
         } 

                 printf("\nVeiculo nao encontrado.\n"); 
}


Veiculo* remover_veiculo(Veiculo *lista, char *placa) {

    Veiculo *atual = lista;
    Veiculo *anterior = NULL;

    while (atual != NULL) {

        if (strcmp(atual->placa, placa) == 0) {

            if (anterior == NULL)
                lista = atual->prox;

            else
                anterior->prox = atual->prox;

            free(atual->placa);
            free(atual->modelo);
            free(atual->cor);
            free(atual->hora_entrada);
            free(atual->Data_de_pagamento);
            free(atual->tempo_permanencia);
            free(atual->forma_pagamento);
            free(atual->valor_pago);
            free(atual->tipo_vaga);
            free(atual->vaga_do_veiculo);

            if(atual->condutor){
                if(atual->condutor->veiculos_cadastrados > 0)
                    atual->condutor->veiculos_cadastrados--;
                
                else
                    atual->condutor->veiculos_cadastrados = 0;
            }
                
             
            
            free(atual);
            reescrever_arquivo_veiculos(lista);

            printf("\nVeiculo removido com sucesso!\n");
            return lista;
        }
        
        anterior = atual;
        atual = atual->prox;
    }
    
    printf("\nVeiculo nao encontrado.\n");
    return lista;
}

Veiculo *inserir_veiculo(Veiculo *lista,Usuario *lista1) {


    Veiculo *novo = malloc(sizeof(Veiculo));
    int verificar_placa;
    int vaga_valida ;
    int vaga_valida_banco;
    char *cpf = NULL  ;
    
    if (!novo) {
        printf("\nErro de memoria.\n");
        return lista;
    }

    printf("\nInsira o cpf do condutor: ");
    
    cpf = ler_string();
    Usuario *dono = buscar_proprietario(lista1,cpf);




    if(dono == NULL){
        printf("\nEste Proprietario nao existe\n");

        free(cpf);
        free(novo);
        return lista;
    }

    printf("\n------ Proprietario Encontrado ------\n");
    printf (" \nProprietario: %s\n",dono->nome);
   


   
    novo->condutor = dono;


    free(cpf);


    do{

        printf("\n Tipo de Vaga (Carro/Moto): ");

        novo->tipo_vaga = ler_string();

        if(novo->tipo_vaga == NULL){
            
            continue;
        }



        if((strcmp(novo->tipo_vaga,"Carro")== 0) || (strcmp(novo->tipo_vaga,"carro")==0)){

             printf("\nVaga de Carro selecionada.\n");

        break;
        }

        else if((strcmp(novo->tipo_vaga,"Moto")== 0)|| (strcmp(novo->tipo_vaga,"moto")==0) || (strcmp(novo->tipo_vaga,"Motocicleta")==0) || (strcmp(novo->tipo_vaga,"motocicleta")==0) ){
             printf("\nVaga de Motocicleta selecionada.\n");
              break;
        }

        else{


            printf("Tipo de Vaga invalido. Por favor, digite 'Carro' ou 'Moto'.\n");
            free(novo->tipo_vaga);
            novo->tipo_vaga = NULL;
            continue;


        }
    }while(1);


    do{

        printf("\nvaga do Veiculo: ");
        printf("\n(Exemplo: A1, B2, C3 etc.)\n");
        novo->vaga_do_veiculo = ler_string();

        if(novo->vaga_do_veiculo == NULL  || novo->vaga_do_veiculo[0] == '\0'){
            printf("\nErro ao ler vaga do veiculo.\n");
            
            
        continue;
        }

        if(strlen(novo->vaga_do_veiculo)<= 1 || strlen(novo->vaga_do_veiculo) > 2 ){

            printf("\nVaga deve conter apenas dois caracteres\n");
            printf("\nPor favor, insira a vaga novamente.\n");
            free(novo->vaga_do_veiculo);
            novo->vaga_do_veiculo = NULL;
            continue;


        }

        vaga_valida_banco = verificar_vaga_banco(novo->vaga_do_veiculo);
        vaga_valida = Id_existe(lista, novo->vaga_do_veiculo);

        if(vaga_valida_banco == 1){
            free(novo->vaga_do_veiculo);
            novo->vaga_do_veiculo = NULL;
            printf("\nErro:  Vaga do veiculo já esta em uso.\n");
            printf("\nPor favor, insira uma vaga diferente.\n");
            
            continue;
        }

        if(vaga_valida == 1){
            free(novo->vaga_do_veiculo);
            printf("\nErro:  Vaga do veiculo já esta em uso.\n");
            printf("\nPor favor, insira uma vaga diferente.\n");
            novo->vaga_do_veiculo = NULL;
            
            continue;
        }
            printf("\nVaga do veiculo cadastrada com sucesso.\n");
            break;
        


    }while(1);


    do{

        printf("\nPlaca: ");
        novo->placa = ler_string();
       
        verificar_placa = verificar_placa_banco_dados(novo->placa ) ;

        if(verificar_placa == 1){
            printf("\nPlaca ja foi registrada\n");
            free(novo->placa);
            novo->placa = NULL;
            continue;


         }

        if(novo->placa == NULL || strlen(novo->placa) < 7 || strlen(novo->placa) > 8 ){
             printf("\nErro: Placa deve conter  7 caracteres.\n");
             printf("\n Tente Novamente \n");
             free(novo->placa);
             novo->placa = NULL;

        }

    }while(novo->placa == NULL || strlen(novo->placa) < 7 || strlen(novo->placa) > 8 );



    printf("\nModelo: ");
    novo->modelo = ler_string();

    printf("\nCor: ");
    novo->cor = ler_string();

    novo->hora_entrada = hora_atual_sistema();
    novo->Data_de_pagamento = data_do_sistema();




    novo->valor_pago = tempo_permanencia_sistema();


    while (1)
    {

        

        if(strcmp(novo->valor_pago, "R$50,00") == 0){
             printf("\nDiaria selecionada.\n");

             novo->tempo_permanencia = malloc(strlen( "Diaria")+1);

             strcpy(novo->tempo_permanencia, "Diaria");
            break;

        }else if(strcmp(novo->valor_pago, "R$150,00") == 0){
            printf("\nMensal selecionada.\n");
            novo->tempo_permanencia = malloc(strlen("Mensal")+1);
            strcpy(novo->tempo_permanencia, "Mensal");
            break;

        }else if(strcmp(novo->valor_pago, "R$30,00") == 0){
            printf("\nPernoite selecionada.\n");
            novo->tempo_permanencia =  malloc(strlen("Pernoite")+1);
            strcpy(novo->tempo_permanencia, "Pernoite");
            break;
        }

        break;
    }


    printf("\nForma de Pagamento:\n ");
    novo->forma_pagamento = forma_pagamento();



    dados_do_veiculo(novo);



    novo->prox = lista;
    lista = novo;

    dono->veiculos_cadastrados++;

    printf("\nVeiculo cadastrado com sucesso!\n");
    return lista;
}

void listar_veiculos(Veiculo *lista) {

        if (lista == NULL) {
            printf("\nNenhum veiculo cadastrado.\n");
            return;
        }

    printf("\n--- Veiculos no Estacionamento ---\n");

    while (lista != NULL ) {
        printf("\nVaga: %s", lista->vaga_do_veiculo);
        printf("\nPlaca: %s", lista->placa);
        printf("\nModelo: %s", lista->modelo);
        printf("\nCor: %s", lista->cor);
        printf("\nEntrada: %s", lista->hora_entrada);
        printf("\nData de Pagamento: %s", lista->Data_de_pagamento);
        printf("\nTempo de Permanencia: %s", lista->tempo_permanencia);
        printf("\nForma de Pagamento: %s", lista->forma_pagamento);
        printf("\nValor pago: %s ", lista->valor_pago);
        printf("\nTipo de Vaga: %s", lista->tipo_vaga);
        if(lista->condutor)
          printf("\nProprietario: %s", lista->condutor->nome);

        printf("\n-------------------------------\n");
        lista = lista->prox;
       
    }


}

void dados_do_veiculo(Veiculo *v) {

    FILE *file = fopen("data/Estacionamento.txt", "a+");
    if (!file) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    fprintf(file, "\n---- Dados do Veiculo ----\n");
    fprintf(file, "Vaga: %s\n", v->vaga_do_veiculo);
    fprintf(file, "Placa: %s\n", v->placa);
    fprintf(file, "Modelo: %s\n", v->modelo);
    fprintf(file, "Cor: %s\n", v->cor);
    fprintf(file, "Tipo de Vaga: %s\n", v->tipo_vaga);
    fprintf(file, "Hora Entrada: %s\n", v->hora_entrada);
    fprintf(file, "Data do Pagamento: %s\n", v->Data_de_pagamento);
    fprintf(file, "Tempo Permanencia: %s\n", v->tempo_permanencia);
    fprintf(file, "Forma Pagamento: %s\n", v->forma_pagamento);
    fprintf(file, "Valor Pago: %s\n", v->valor_pago);
    if(v->condutor)
     fprintf(file, "Proprietario: %s\n", v->condutor->nome);

   
   
    fprintf(file, "--------------------------\n");
    printf("\n");

    fclose(file);
}

char *tempo_permanencia_sistema() {
    

        int opcao;
        char *valor = NULL;

    while(1){
        printf("\n====== Escolha o tempo de permanencia ======\n");
        printf("1  - Diaria: 24 horas Valor: R$50,00\n");
        printf("2  - Mensal: 30 dias Valor: R$150,00\n");
        printf("3  - Pernoite: 12 horas Valor: R$30,00\n");

        printf("\nInsira o tempo de permanencia desejado: ");
        scanf("%d", &opcao);
        
        limpar_buffer();

        switch (opcao)
        {
        case 1:
        printf("\nDiaria selecionada.\n");
        printf("\nO valor da diaria e R$ 50,00\n");
        valor = malloc(strlen("R$50,00")+1);
        if(!valor) 
            return NULL;

        strcpy(valor, "R$50,00");
    
        return  valor;
            
           
        case 2:
        printf("\nMensal selecionada.\n");
        printf("\nO valor do mensal e R$ 150,00\n");
            valor = malloc(strlen("R$150,00")+1);
            if(!valor) 
                return NULL;

            strcpy(valor, "R$150,00");
            return valor;
           
        case 3:
        printf("\nPernoite selecionada.\n");
        printf("\nO valor do pernoite e R$ 30,00\n");
        
            valor = malloc(strlen("R$30,00")+1);
            if(!valor)
             return NULL;

            strcpy(valor, "R$30,00");
            return valor;
           
        
        default:
        printf("\nTempo invalido\n");
        printf("\n Tente novamente.\n");
            
        }
    }
    
}
char *data_do_sistema(void) {
    time_t agora;
    struct tm *tempo;
    char *data = malloc(11); 

    if (data == NULL) {
        return NULL;
    }

    time(&agora);
    tempo = localtime(&agora);

    if (tempo == NULL) {
        free(data);
        return NULL;
    }

    unsigned short dia  = tempo->tm_mday;
    unsigned short mes  = tempo->tm_mon + 1;
    unsigned short ano  = tempo->tm_year + 1900;

    snprintf(data, 11, "%02hu/%02hu/%04hu", dia, mes, ano);

    

    return data;

}



char *hora_atual_sistema() {

    
    time_t agora;
    struct tm *tempo;
    char *hora = malloc(20); 
    if (hora == NULL) {
        return NULL;
    }

    
    
    time(&agora);
    tempo = localtime(&agora);

    if(tempo == NULL){
        free(hora);
        return NULL;
    }

    snprintf(hora, 20, "%02d:%02d", tempo->tm_hour, tempo->tm_min);


    return hora;
}

int Id_existe(Veiculo *lista, char *id_vaga) {

    Veiculo *atual = lista;

    if(id_vaga == NULL){
        return 0;
    }

    while (atual != NULL) {
        if (atual->vaga_do_veiculo && strcmp(atual->vaga_do_veiculo, id_vaga) == 0) { 
            return 1; 
        }
        atual = atual->prox;
    }
    return 0; 
}

void reescrever_arquivo_veiculos(Veiculo *lista) {
    FILE *file = fopen("data/Estacionamento.txt", "w");
    if (!file) {
        printf("Erro ao reescrever arquivo.\n");
        return;
    }

    while (lista != NULL) {
        fprintf(file, "\n---- Dados do Veiculo ----\n");
        fprintf(file, "Vaga: %s\n", lista->vaga_do_veiculo);
        fprintf(file, "Placa: %s\n", lista->placa);
        fprintf(file, "Modelo: %s\n", lista->modelo);
        fprintf(file, "Cor: %s\n", lista->cor);
        fprintf(file, "Tipo de Vaga: %s\n", lista->tipo_vaga);
        fprintf(file, "Hora Entrada: %s\n", lista->hora_entrada);
        fprintf(file, "Data do Pagamento: %s\n", lista->Data_de_pagamento);
        fprintf(file, "Tempo Permanencia: %s\n", lista->tempo_permanencia);
        fprintf(file, "Forma Pagamento: %s\n", lista->forma_pagamento);
        fprintf(file, "Valor Pago: %s\n", lista->valor_pago);

       
       
        fprintf(file, "--------------------------\n");

        lista = lista->prox;
    }

    fclose(file);
}

char *ler_string() {
    char memoria[256];

    while(1){
        if(fgets(memoria, sizeof(memoria), stdin) == NULL){
            return NULL;
        }


        if (memoria[0]  == '\n' ){

            printf("\nErro o campo nao pode ser vazio\n");
            printf("\nTente Novamente:\n");

            continue; }
            
            
            memoria[strcspn(memoria, "\n")] = '\0'; 
            char *palavra = malloc(strlen(memoria) + 1);
        
        if (palavra == NULL)
            return NULL;

        strcpy(palavra, memoria);
        return palavra;
    }

}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
     
}


Usuario *cadastrarCondutor(Usuario *lista1){

     Usuario *novo = malloc(sizeof(Usuario)); 

     if(!novo){
    printf("Erro de memoria\n");
    return lista1;
}


     
     int opcao;
     int contador =0;
     int chances = 3;
     char *telefone = NULL;

     novo->veiculos_cadastrados = 0;

    do{
        printf("\nInsira o nome do Condutor:  ");
            novo->nome = ler_string();

            if(novo->nome == NULL){
                
                printf("\nEste campo n pode ser vazio\n");
                continue;
            }else{
                break;
            }

    }while(1);




    do {
        printf("\nInsira o CPF do Proprietario: ");
        novo->cpf = ler_string();

        

        if(contador == 2){
            printf("\nNumero maximo de tentativas atingido. Retornando ao menu principal.\n");
            free(novo->cpf);
            free(novo);
            return lista1;
        }

        if (novo->cpf == NULL) {
            printf("Erro ao ler CPF.\n");
            continue;
        }

        if (strlen(novo->cpf) != 11) {
            printf("Erro: CPF deve conter exatamente 11 numeros.\n");
            free(novo->cpf);
            novo->cpf = NULL;
            continue;
        }
        

        if (verificar_banco_dados_usuario(novo->cpf) ) {
            printf("Erro: CPF ja cadastrado \n");
           

           printf("\nDigite 1 - Para tentar novamente\nDigite 2 - Para sair \n");
           
           scanf("%d",&opcao);
           limpar_buffer();

           if(opcao == 1){
            printf("Voce tera %d chances para digitar um CPF valido.\n",chances -1);
               free(novo->cpf);
               novo->cpf = NULL;
               chances--;
               contador++;
               continue;

           }
            if(opcao == 2){
                free(novo->cpf);
                novo->cpf = NULL;
             printf("\n--- Saindo -- \n");
           return lista1;
           }
           continue;
        }

        if (verificar_cpf(lista1, novo->cpf)) {
            printf("Erro: CPF ja cadastrado \n");
            printf("Voce tera %d chances para digitar um CPF valido.\n",chances -1);
            free(novo->cpf);
            novo->cpf = NULL;
            chances--;
            contador++;
            continue;
        }
        
        break; 
    } while (1);


    do{
        printf("\nInsira o telefone do Condutor: ");
    

        telefone = ler_string();
        novo->telefone = analizar_telefone(telefone);
        free(telefone);
          


        if(novo->telefone == NULL){
          
            continue;
        }

        if( strlen(novo->telefone) < 11 || strlen(novo->telefone) > 11){
       
            printf("\nTelefone deve Conter DD + 9 Digitos\n");
            free(novo->telefone);
            novo->telefone = NULL;
            continue;
        }

       
        
        break;

    }while(1 );

                    
               
                    
    printf("\nInsira seu email: ");
        novo->email = ler_string();

    printf("\nInsira seu Endereço: ");
        novo->endereco = ler_string();

     dados_do_condutor(novo);




    novo->prox1 = lista1;

     return novo;


}

        

void menu() {
    
    printf(" \033[32m ==== Gerenciamento de Estacionamento ====\n");
    printf("1 - Cadastrar Condutor\n");
    printf("2 - Cadastrar Veiculo\n");
    printf("3 - Remover Veiculo\n");
    printf("4 - Listar Veiculos cadastradados Recentemete \n");
    printf("5 - Buscar Veiculo pela Placa\n");
    printf("6 - Buscar Condutor Pelo CPF\n");
    printf("7 - Remover Proprietario\n");
    printf("8 - Listar todos Usuarios ja cadastrados\n");
    printf("9 - Listar todos os Veiculos ja cadastrados\n");
    printf("10 - Sair\n");

}

void dados_do_condutor(Usuario *proprietario) {
   
    FILE *file = fopen("data/Cadastro_de_usuario.txt", "a+"); 
    if (!file) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    
    fprintf(file, "\n---- Dados do Condutor ----\n");
    fprintf(file, "Nome do Condutor: %s\n", proprietario->nome);
    fprintf(file, "Telefone: %s\n", proprietario->telefone);
    fprintf(file, "Email: %s\n", proprietario->email);
    fprintf(file, "Endereço: %s\n", proprietario->endereco);
    fprintf(file, "Cpf: %s\n", proprietario->cpf);
  
  
    fprintf(file, "--------------------------\n");
    printf("\n");

    fclose(file);
}


Usuario *buscar_proprietario(Usuario *lista1, char *cpf) { 
 


    while (lista1 != NULL) { 
        if ( strcmp(lista1->cpf, cpf) == 0  ) {

          return lista1;
        }

         lista1 = lista1->prox1;
    } 


    return NULL;
}





void reescrever_arquivo_prorpietario(Usuario *lista1) {
         
        
        FILE *file = fopen("data/Cadastro_de_usuario.txt", "w");
        if (!file) {
            printf("Erro ao abrir arquivo.\n");
            return;
        }
        while(lista1 != NULL){
                fprintf(file, "\n---- Dados do Condutor ----\n");
                fprintf(file, "Nome do Condutor: %s\n", lista1->nome);
                fprintf(file, "Telefone: %s\n", lista1->telefone);
                fprintf(file, "Email: %s\n", lista1->email);
                fprintf(file, "Endereço: %s\n", lista1->endereco);
                fprintf(file, "Cpf: %s\n",lista1->cpf);
               
            
                fprintf(file, "\n--------------------------\n");
                printf("\n");
                lista1 = lista1->prox1;
                
            }
        fclose(file);
}

 Usuario *remover_proprietario(Usuario *lista1,Veiculo **lista, char *cpf){
     Usuario *atual = lista1;
     Usuario *anterior = NULL;

     
     
     while (atual != NULL) {
         
         if (strcmp(atual->cpf, cpf) == 0) {

             *lista = remover_veiculos_do_proprietario(*lista,atual);
             reescrever_arquivo_veiculos(*lista);

             if (anterior == NULL)
             lista1 = atual->prox1;
            else
            anterior->prox1 = atual->prox1;
        

            free(atual->cpf);
            free(atual->email);
            free(atual->endereco);
            free(atual->telefone);
            free(atual->nome);
            
            free(atual);
             
            reescrever_arquivo_prorpietario(lista1);

            
            printf("\nProprietario removido com sucesso!\n");
            return lista1;
        }

        anterior = atual;
        atual = atual->prox1;
    }

    printf("\nProprietario nao encontrado.\n");
    return lista1;
}


int verificar_cpf(Usuario *lista1, char *cpf) {
    Usuario *atual = lista1;

    

    while (atual != NULL) {
        if (strcmp(atual->cpf, cpf) == 0) {
            return 1; 
        }
        atual = atual->prox1;
    }
    return 0; 
}



Veiculo *remover_veiculos_do_proprietario(Veiculo *lista, Usuario *proprietario) {
    Veiculo *atual = lista;
    Veiculo *anterior = NULL;

    while (atual != NULL) {

        if (atual->condutor == proprietario) {
            Veiculo *remover = atual;

           
            if (anterior == NULL) {
                lista = atual->prox;
                atual = lista;
            } 
           
            else {
                anterior->prox = atual->prox;
                atual = atual->prox;
            }

            
            free(remover->vaga_do_veiculo);
            free(remover->placa);
            free(remover->modelo);
            free(remover->cor);
            free(remover->tipo_vaga);
            free(remover->hora_entrada);
            free(remover->Data_de_pagamento);
            free(remover->tempo_permanencia);
            free(remover->forma_pagamento);
            free(remover->valor_pago);

           
            free(remover);

           
        } 
        else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return lista;
}


void imprime_proprietario(Usuario *lista1){

    if(lista1!= NULL){

    printf( "---- Dados do Condutor ----\n");
    printf( "Nome do Condutor: %s\n", lista1->nome);
    printf( "Telefone: %s\n", lista1->telefone);
    printf( "Email: %s\n", lista1->email);
    printf( "Endereço: %s\n", lista1->endereco);
    printf( "Cpf: %s\n", lista1->cpf);
    printf( "Veiculos Cadastrados: %d\n", lista1->veiculos_cadastrados);

    printf( "--------------------------\n");}
   
    




}



int verificar_banco_dados_usuario(char *cpf) {

    char *cpf_arquivo;
    char linha[256];

    FILE *file = fopen("data/Cadastro_de_usuario.txt", "r");
    if (!file) {
        perror("Erro ao abrir arquivo");
        return 0;
    }


    while (fgets(linha, sizeof(linha), file)) {

        if (strstr(linha, "Cpf:") != NULL) {

             cpf_arquivo = strchr(linha, ':');

            if (cpf_arquivo) {

                cpf_arquivo++; 
                while (*cpf_arquivo == ' ') cpf_arquivo++;

                cpf_arquivo[strcspn(cpf_arquivo, "\n")] = '\0';

                if (strcmp(cpf_arquivo, cpf) == 0) {
                    fclose(file);
                    return 1; // CPF encontrado
                }
            }
        }
    }

    fclose(file);
    return 0;
}

int verificar_placa_banco_dados(char *placa){

    char linhas[256];
    char *placa_arquivo;

    FILE *file = fopen("data/Estacionamento.txt","r");

    if(!file) {
        printf("erro ao abrir arquivo");
     return 0;}


    while(fgets(linhas,sizeof(linhas),file)){

        if(strstr(linhas,"Placa:")!=NULL){
            placa_arquivo = strchr(linhas,':');

            if(placa_arquivo){

                placa_arquivo++;

                while(*placa_arquivo == ' '){
                     placa_arquivo++;

                }

                 placa_arquivo[strcspn( placa_arquivo,"\n")] = '\0';

                 if(strcmp(placa_arquivo,placa)==0){
                   
                    fclose(file);
                    return 1;
                 }


            }
           

        }

    }
    fclose(file);

    return 0;





}


int verificar_vaga_banco(char *vaga){

    char linhas[256];
    char *vaga_procurada;

    FILE *file = fopen("data/Estacionamento.txt", "r");
    if(!file){

        printf("\nErro ao abrir arquivo\n");
        return 0;
    }



    while(fgets(linhas,sizeof(linhas),file)){

        if(strstr(linhas,"Vaga:")!=NULL){
            vaga_procurada = strchr(linhas,':');

            if(vaga_procurada){
                vaga_procurada++;

                while(*vaga_procurada == ' '){
                    vaga_procurada++;
                }

                vaga_procurada[strcspn(vaga_procurada,"\n")]= '\0';

                if(strcmp(vaga_procurada,vaga) == 0){

              
                fclose(file);
                return 1;
                }

            }
        }


    }
    fclose(file);

    return 0;

}

char *analizar_telefone(char *telefone){
    int i = 0;
    int j =0;
    
        if(telefone== NULL) 
        return NULL;


    char *telefone_valido = malloc(strlen(telefone)+1);

    if(telefone_valido == NULL){
        return NULL;
    }
    for(i =0; telefone[i]!='\0';i++){

        

        if(isdigit((unsigned char)telefone[i])){
            telefone_valido[j++] = telefone[i];
        }



    }

    telefone_valido[j] = '\0';

    return telefone_valido;



}


void bancoDeDadosProprietarios(){

    char linhas[256];

    FILE *arquivos = fopen("data/Cadastro_de_usuario.txt", "r");

    if(arquivos == NULL){

        printf("\n Erro ao abrir arquivos\n");
        return ;

    }
       printf("\n---------- Exibindo todos os Proprietarios ja Cadastrados ----------\n");
    while(fgets(linhas,sizeof(linhas),arquivos)){
    
        printf("%s",linhas);
        printf("\n");
    }

    fclose(arquivos);

}

void bancoDeDadosVeiculos(){

    char linhas[256];

    FILE *arquivos = fopen("data/Estacionamento.txt", "r");

    if(arquivos == NULL){

        printf("\n Erro ao abrir arquivos\n");
        return ;
    }

   printf("\n---------- Exibindo todos os Veiculos ja Cadastrados ----------\n");
   
    while(fgets(linhas,sizeof(linhas),arquivos)){

        printf("%s",linhas);
        printf("\n");
    }

    fclose(arquivos);

}