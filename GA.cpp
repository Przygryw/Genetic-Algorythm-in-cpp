#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>

class geneticAlgorythm
{
    private:
        int sizePop;

    int genotypize(bool *chromosomes)
    {
        int a = 0;
        for(int i = 3; i >= 0; i--)
        {
            a += chromosomes[3-i]*(int)pow(2,i);
        }
        return a;
    }

    bool *chromosomize(int genotype)
    {
        bool *chromosomes = new bool[4];
        int gen = genotype;
        for(char i = 3; i >= 0; i--)
        {
            chromosomes[i] = gen%2;
            gen = gen/2;
        }
        return chromosomes;
    }

    public:
    geneticAlgorythm(int population_Size)
    {
        this->sizePop = population_Size;
    }
    
    void generatePopulation(int **populationArray)
    {
        for(int i =0; i < sizePop; i++)
        {
            for(int j = 0; j < 3; j++) populationArray[i][j] = rand()% 15;
        }
    }

    void crossing(int **populationArray, int **newPopulation)
    {
        std::cout <<"Crossing: \n";
        int id0, id1;
        bool newIndividual[4];
        for(int individual = 0; individual < sizePop; individual++)
       {
            id0 = rand()%sizePop;
            id1 = id0;
            while(id0 == id1) id1 = rand()%sizePop;
            std::cout << "\n\nID 1: " << id0 << " with  ID 2: " << id1<<std::endl;
            bool fIndividual[4];
            bool sIndividual[4];
            for(int i = 0; i < 3; i++)
            {
                std::cout<<"Feature : "<<i+1<<std::endl;
                bool* tmp0 = chromosomize(populationArray[id0][i]);
                bool* tmp1 = chromosomize(populationArray[id1][i]);
                for(int j =0; j < 4; j++) {fIndividual[j] = tmp0[j]; sIndividual[j] = tmp1[j];}
                delete[] tmp0; delete[] tmp1;
                for(int a = 0; a<4; a++)
                {
                    std::cout<<fIndividual[a];
                }
                std::cout<<" ";
                for(int a = 0; a<4; a++)
                {
                    std::cout<<sIndividual[a];
                }
                
                char hM = rand()%5;
                std::cout<<" Chs "<< (int)hM<<" ";
                for(char k =0; k < 4; k++)
                {
                    if(k < hM) newIndividual[k] = fIndividual[k];
                    else newIndividual[k] = sIndividual[k];
                    std::cout << newIndividual[k];
                }
                newPopulation[individual][i] = genotypize(newIndividual);
                std::cout <<"\nNEW: "<< newPopulation[individual][i]<<"\n";
            }
        }
    }

    void mutations(int **population, int sizePop)
    {
        std::cout<<"Mutations in progress\n";
        for(int individual = 0; individual < sizePop; individual++)
        {
            for(char feature =0; feature < 3; feature++)
            {
                bool* chromes = chromosomize(population[individual][feature]);
                for(int ch = 0; ch < 4; ch++)
                {
                    float chance = rand()%101;
                    if(chance > 80) chromes[ch] = !chromes[ch];
                }
                population[individual][feature] = genotypize(chromes);
                delete[] chromes;
            }
        }
    }
    float *objectiveFunction(int **population, int sizePop, float factor1, float factor2, float factor3)
    {
        std::cout<<"Objective functions\n";
        float* oF = new float[sizePop];
        for(int individual = 0; individual < sizePop; individual++)
        {
            oF[individual] = factor1*population[individual][0]+factor2*population[individual][1]+factor3*population[individual][2];
            std::cout<<individual<<": "<<oF[individual]<<"\n";
        }
        return oF;
    }
};


void showPopulation(int **population, int sizePop)
{
    std::cout << "Population: \n";
    for(int i =0; i < sizePop; i++)
    {
        std::cout << "I "<< i <<"| ";
        for(int j = 0; j < 3; j++)
        {
            std::cout << population[i][j] <<" ";
        } std::cout<<std::endl;
    }
}
int main()
{
    int popSize, generations;
    srand(time (NULL));
    std::cout<<"Declare size of population: "; std::cin >> popSize;
    std::cout<<"How many generations?: "; std::cin>> generations;
    int **population = new int*[popSize];
    int **newPopulation = new int*[popSize];
    float* objectiveFunctions = new float[popSize];
    for(int i =0; i < popSize; i++)
    {
        population[i] = new int[3];
        newPopulation[i]= new int[3];
    }
    geneticAlgorythm Algorythm1(popSize);
    Algorythm1.generatePopulation(population);
    showPopulation(population,popSize);
    for(int j =0; j<generations; j++)
    {
        std::cout<<"GENERATION: "<<j<<"\n\n\n";
        Algorythm1.crossing(population, newPopulation);
        showPopulation(newPopulation,popSize);
        Algorythm1.mutations(newPopulation,popSize);
        showPopulation(newPopulation,popSize);
        Algorythm1.objectiveFunction(newPopulation,popSize,1.5,2.0,0.4);
        population = newPopulation;
    }
    while(1);
}