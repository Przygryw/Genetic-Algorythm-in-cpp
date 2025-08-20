# Genetic-Algorythm-in-cpp

Genetic algorythm that generates population with declared size, then crosses individuals, to create new population.
Object geneticAlgorythm contains such methods as: 

-generate population- initial function to generate first population

-crossing- program randomly chooses 2 individuals, combines genotypes of each individual and then creates feature of new individuals

-mutations- program goes through each chromosome of all individual's features and chooses if mutate the chromosomes or not. Mutation is just changing bool value of chromosome to opposite

-objectiveFunction- program calculates each individual's objectiveFunction, with declared factors.

Internal methods:

-chromosomize- method converts feature from decimal to binary (puts feature into separate chromosomes)

-genotypize- method converts chormosomal (binary) value back to decimal.


External function:
-showPopulation- displays each individual with it's features.
