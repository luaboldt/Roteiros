/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_
#include <unistd.h>
#include <atomic>
#include <thread>

using namespace std;

class Parque;

class Carro {
public:
	static const int CAPACIDADE;
	static atomic <int> numPassageiros;
	bool carroCheio;
	static atomic <bool> voltaAcabou;

	Carro();
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	void setNVoltas();
	void run();

private:
	int voltas;

};

#endif /* CARRO_H_ */
