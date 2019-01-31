#include <iostream>
#include "SampleDecoder.h"
#include "MTRand.h"
#include "BRKGA_torneio.h"
#include "VetorGanhoPeso.h"
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>


#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
#define MICRO_PER_SECOND 1000000


using namespace std;

vector<GanhoPeso> VetorGanhoPeso;

int sizeknapsack;

void decodificador(std::vector< double > chromosome);

int main(int argc, char* argv[]) {

	ifstream file("test50.txt");

	file >> sizeknapsack;

	const unsigned n = 50;		// size of chromosomes
	const unsigned p = 100;	// size of population
	const double pe = 0.20;		// fraction of population to be the elite-set
	const double pm = 0.10;		// fraction of population to be replaced by mutants
	const double rhoe = 0.80;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 1;		// number of independent populations
	const unsigned MAXT = 1;	// number of threads for parallel decoding
	
	int peso, ganho;

	struct timeval start, end;
	double time;


	VetorGanhoPeso.resize(n);
 

	for (int i = 0; i < n; ++i)
	{
		//unused = fscanf(arq,"%d %d", &ganho, &peso);
		file >> ganho;
		VetorGanhoPeso[i].first = ganho;
		file >> peso;
		VetorGanhoPeso[i].second = peso; 		
	}


	SampleDecoder decoder;			// initialize the decoder

	
	const long unsigned rngSeed = 9;	// seed to the random number generator 
	MTRand rng(rngSeed);				// initialize the random number generator
	//MTRand roleta();
	
	// initialize the BRKGA-based heuristic
	BRKGA_torneio< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
	
	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 1;	// run for 1000 gens

	gettimeofday(&start, NULL);
	do {
		algorithm.evolve();	// evolve the population for one generation
		
		//if((++generation) % X_INTVL == 0) {
		//	algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		//}
		++generation;
	} while (generation < MAX_GENS);
	gettimeofday(&end, NULL);
	
	time = (double)(end.tv_sec - start.tv_sec);
    time += (end.tv_usec - start.tv_usec)/(double)MICRO_PER_SECOND;
	
	std::cout << "\n\nBest solution found has objective value = " << algorithm.getBestFitness() << std::endl;
	//std::cout << "\nsemente: "<< rngSeed << std::endl;
	cout << "\n\nTotal Time: " << time;
	//algorthm.getPopulation(0).getChromosome(0);
	 cout<<" \n";
	/*
	for(int i=0;i<p;i++){
		cout<<" \n"<<algorithm.getPopulation(0).getFitness(i);	
	}
	cout<<" \n";
	*/
	std::vector< double > bestChromosome;

	bestChromosome = algorithm.getPopulation(0).getChromosome(0);

	decodificador(bestChromosome);
	
	
	return 0;
}


void decodificador(std::vector< double > chromosome){  // Procedimento decoder


	typedef std::pair< double, double  > RandomKeyItem;

	std::vector<RandomKeyItem> VetorItemRK(chromosome.size());


	typedef std::pair< double, double  > ItensAlocados;

	std::vector<ItensAlocados> VetorItensAlocados(chromosome.size());


	std::vector<unsigned>  ItemAlocado(chromosome.size());


	unsigned pesoAlocado = 0, ganhoAlocado = 0, item;

	int peso, ganho;

	VetorGanhoPeso.resize(chromosome.size());

	FILE *teste;


	ifstream file("test10000.txt");

	file >> sizeknapsack;

	
	VetorGanhoPeso.resize(chromosome.size());

	for (int i = 0; i < chromosome.size(); ++i)
	{
		//unused = fscanf(arq,"%d %d", &ganho, &peso);
		file >> ganho;
		VetorGanhoPeso[i].first = ganho;
		file >> peso;
		VetorGanhoPeso[i].second = peso; 		
	}

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

	
	for (int i = 0; i < chromosome.size(); ++i)
	{
		VetorItensAlocados[i].first = VetorItemRK[i].second;
 		VetorItensAlocados[i].second = ItemAlocado[i];
 	}


	std::sort(VetorItensAlocados.begin(),VetorItensAlocados.end());
	
		teste = fopen("ArqGrav.txt", "w");


	for (int i = 0; i < chromosome.size(); ++i)
	{
		fprintf(teste, "%f  ",VetorItensAlocados[i].second);
		fprintf(teste, "  \n");
	}

	double fclose(FILE *teste);
	
}
	

