/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include "include/Carro.h"
#include "include/Parque.h"

#define MAX_NUM_VOLTAS 5
int last[MaxPassageiros -1], in[MaxPassageiros-1];
int j, k, cont;
std::atomic_flag lock = ATOMIC_FLAG_INIT;
std::atomic_flag lock1 =  ATOMIC_FLAG_INIT;


Passageiro::Passageiro(int id, Carro *c) {
	this->id = id;
	this->carro = c;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
	// Protocolo de entrada do Algoritmo Justo
	// Incrementa o numero de passageiros no carro

		for(j = 0; j < Parque::numPessoas; j++){
			last[j] = id; in[id] = j;
		}

		for(k = 0; k < Parque::numPessoas; k++){
			if(k == id){
				continue;
			}
				while((in[k] >= in[id]) && (last[j] == id)){
					sleep(1);
				}
				while(lock.test_and_set()){sleep(1);};
				while(carro->carroCheio);
				lock.clear();
			}

		while(lock.test_and_set()){sleep(1);};
		carro->numPassageiros.fetch_add(1, memory_order_seq_cst);
		std::cout << "passageiro " << id << " entrou no carro" << endl;
		if(carro->numPassageiros == carro->CAPACIDADE){
			carro->carroCheio = true;
		}
		lock.clear();
}

void Passageiro::esperaVoltaAcabar() {
	while (!carro->voltaAcabou){ sleep(1); }
}

void Passageiro::saiDoCarro() {
	// Decrementa o numero de passageiros no carro
	// Protocolo de saida do Algoritmo Justo
	while(lock1.test_and_set()){
		sleep(1);
	}
	carro->numPassageiros.fetch_sub(1, memory_order_seq_cst);
	std::cout << "o passageiro: " << id << " saiu do carro" << endl;
	if(carro->numPassageiros == 0){
		carro->carroCheio = false;
		carro->voltaAcabou = true;
	}
	lock1.clear();
}

void Passageiro::passeiaPeloParque() {
	sleep((rand()%20)+1);
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS)
		return false;

	std::cout << "O parque está fechado" << endl;

	return true;
}

void Passageiro::run() {
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de pessoas no parque
}
