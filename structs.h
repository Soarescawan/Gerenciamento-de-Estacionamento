#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct Usuario{
    char *nome;
    char *cpf;
    char *telefone;
    char *email;
    char *endereco;
    int veiculos_cadastrados ;
    
    
    struct Usuario *prox1;
}Usuario;


typedef struct Veiculo {
    char *vaga_do_veiculo;
    char *placa; 
    char *modelo;
    char *cor;
    char *tipo_vaga;
    char *hora_entrada;
    char *Data_de_pagamento;
    char *tempo_permanencia;
    char *forma_pagamento;
    char *valor_pago;
    
    Usuario *condutor;
    struct Veiculo *prox;
} Veiculo;

#endif