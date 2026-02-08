#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs.h"

Usuario *buscar_proprietario(Usuario *lista1, char *cpf);

Usuario *cadastrarCondutor(Usuario *lista);

void dados_do_condutor(Usuario *proprietario);

void imprime_proprietario(Usuario *lista1);

int verificar_cpf(Usuario *lista1, char *cpf);

void reescrever_arquivo_prorpietario(Usuario *lista1);

Usuario *remover_proprietario(Usuario *lista1,Veiculo **lista, char *cpf);





Veiculo  *remover_veiculos_do_proprietario(Veiculo *lista, Usuario *proprietario);

Veiculo *inserir_veiculo(Veiculo *lista,Usuario *lista1);

Veiculo* remover_veiculo(Veiculo *lista, char *placa); 

void buscar_veiculo(Veiculo *lista, char *placa);

void reescrever_arquivo_veiculos(Veiculo *lista);

void listar_veiculos(Veiculo *lista);

void dados_do_veiculo(Veiculo *v);

char *tempo_permanencia_sistema(); 

char *forma_pagamento();


int Id_existe(Veiculo *lista, char *id_vaga);

int verificar_placa_banco_dados(char *placa);

int verificar_banco_dados_usuario(char *cpf);




void limpar_buffer();

void menu();

char *ler_string();

char *hora_atual_sistema();

char *data_do_sistema();

char *ajustar_placa(char *placa);

int verificar_vaga_banco(char *vaga);




#endif