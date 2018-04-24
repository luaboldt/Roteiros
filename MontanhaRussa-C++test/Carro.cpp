/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"
#include <iostream>

std::atomic_flag lockcarro = ATOMIC_FLAG_INIT;
std::atomic <int> Carro::numPassageiros = ATOMIC_VAR_INIT(0);
std::atomic <bool> Carro::voltaAcabou = ATOMIC_VAR_INIT(false);

const int Carro::CAPACIDADE = 5;

Carro::Carro() {
	this->voltas = 0;
	this->carroCheio = false;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	while (numPassageiros < CAPACIDADE) { sleep(0.5); }
}

void Carro::daUmaVolta() {
	while(lockcarro.test_and_set()){};
	std::cout << "O carro está dando uma volta..." << endl;
	sleep(5);
	setNVoltas();
	std::cout << "A volta acabou." << endl;
	voltaAcabou = true;
	lockcarro.clear();
}

void Carro::esperaEsvaziar() {
	while (numPassageiros > 0) { sleep(1); }
}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::setNVoltas()	{
	voltas++;
}

void Carro::run() {
	while (Parque::numPessoas > 0) {
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

		voltas++;
	}
}
