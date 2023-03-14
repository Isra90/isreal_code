#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Mutation; 

Mutation *read_mutations(string filename, int *num_mutations_p);

const int NUM_ENERGY = 5;

struct Gene {
    string g_name;
    Mutation *receiver;
};

struct Mutation {
    string m_name;
    int energy_received;
    Gene transactions[NUM_ENERGY];
};