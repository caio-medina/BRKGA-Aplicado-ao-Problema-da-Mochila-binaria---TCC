/*
 * SampleDecoder.cpp
 *
 *  Criado em: Agosto, 2018
 *      Autor: Caio & Patricia 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <sys/time.h>
#include "SampleDecoder.h"
#include "VetorGanhoPeso.h"

SampleDecoder::SampleDecoder() { }

SampleDecoder::~SampleDecoder() { }

// Runs in \Theta(n \log n):
double SampleDecoder::decode(const std::vector< double >& chromosome) const {


	//Struct with the pair: Item and Random Keys
	typedef std::pair< double, double  > RandomKeyItem;

	std::vector<RandomKeyItem> VetorItemRK(chromosome.size());


	unsigned pesoAlocado = 0, ganhoAlocado = 0, item;


	std::vector<unsigned>  ItemAlocado(chromosome.size());

	

	for(int i = 0; i <chromosome.size();i++)
	{
		VetorItemRK[i].first = chromosome[i];  // first é a chave aleatória
		VetorItemRK[i].second = i; // second é a posição do item
		ItemAlocado[i] = 0; // vetor que informa se o item foi alocado "1" ou não "0"
	}

	// ordena as chaves em ordem crescente 
	std::sort(VetorItemRK.begin(),VetorItemRK.end());

	// Verifica se o item pode ser alocado na mochila e calcula o valor de todos os itens  
	for (int i; (i < chromosome.size()) && (pesoAlocado < sizeknapsack);i++){   
		item = VetorItemRK[i].second; 
	
			if (pesoAlocado + VetorGanhoPeso[item].second <= sizeknapsack)
			{
	
				pesoAlocado = VetorGanhoPeso[item].second + pesoAlocado;
				ganhoAlocado = VetorGanhoPeso[item].first + ganhoAlocado;
				ItemAlocado[i] = 1;

			}
 			
	}

	// sample fitness is the first allele
	return ganhoAlocado; // return ganhoTotalAlocado;
}
