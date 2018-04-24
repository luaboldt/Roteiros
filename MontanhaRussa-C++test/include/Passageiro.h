/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <atomic>
#include <iostream>
#define MaxPassageiros 10


class Carro;
class Parque;

class Passageiro {
public:
	Passageiro(int id, Carro *c);
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();

	void run();
private:
	int id;
	Carro *carro;
};

#endif /* PASSAGEIRO_H_ */
