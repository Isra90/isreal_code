#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Mutation; 
struct Gene; 

Gene *read_mutations(string filename, int *num_gene_p);
int count_students(string filename);

struct Gene {
    string g_name;
    int total_mutations;
    Mutation *receiver;
};

struct Mutation {
    string m_name;
    int energy_received;
    Mutation *receiver;
};

int main(int argc, char *argv[]) {
    //Make sure I was actually given a filename on the command-line
    if (argc < 2) {
        cerr << "ERROR: Expecting a file name as a command-line argument." << endl;
        exit(EXIT_FAILURE);
    }

    //Read in the genes from the provided file
    int num_genes;
    Gene *genes = read_mutations(argv[1], &num_genes);

    //
   for (int i = 0; i < num_genes; i++){
    cout<< genes[i].g_name<<endl;
    cout<<genes[i].total_mutations<<endl;
    cout<<"_______________"<<endl;
   }


}

Gene *read_mutations(string filename, int *num_gene_p) {
    
    
    ifstream infile(filename.c_str());
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: " 
             << filename << endl;
        exit(EXIT_FAILURE);
    }

     int gene_count = 0;
    //first line is the total genes
    infile >> gene_count;
    *num_gene_p = gene_count;
    //build the list to hold the genes
    Gene *genes = new Gene[*num_gene_p];


    string firstGene;
    int num_mutations_p;
    Mutation partner;

    for (int i = 0; i < *num_gene_p; i++) {
        infile >> firstGene >> num_mutations_p;
        genes[i].g_name = firstGene;
        genes[i].total_mutations = num_mutations_p;
        //cout << infile <<endl;

    }
    infile.close();
    
    return genes;
}


