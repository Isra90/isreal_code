#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Mutation; 
struct Gene; 

Gene *read_mutations(string filename, int *num_gene_p);
int count_students(string filename);
int print_file(Gene * genes, int num_genes);
int check_genes(Gene * genes, int num_genes, string source, string target);
int check_energy(Gene * genes, int num_genes, string source, string target, int energy);

struct Gene {
    string g_name;
    int total_mutations;
    Mutation *receiver;
};

struct Mutation {
    string m_name;
    int energy_received;
    //Mutation *receiver;
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

    //now get user info
    string userInput;
   cout << "Enter query prompt ";
   cin >> userInput;

   //cout<<"user input is "<< userInput <<endl;

   while(userInput != "q"){
    
    if(userInput == "p") print_file(genes, num_genes);

    if(userInput == "m") {
        string source;
        string target;
        cin>> source;
        cin>> target;
        //cout<< "target " <<target<< " and source "<<source<<endl;
        check_genes(genes, num_genes, target, source);
    }

    if(userInput == "me") {
        string source;
        string target;
        int energy;
        cin>> source;
        cin>> target;
        cin>>energy;
        //cout<< "target " <<target<< " and source "<<source<<endl;
        check_energy(genes, num_genes, target, source, energy);
    }

    cout << "Enter Another query prompt ";
    cin >> userInput;    
    //cout<<"user input is "<< userInput <<endl;

   }
   cout<<"query ended!" <<endl;

}

int check_energy(Gene * genes, int num_genes, string source, string target, int energy){
    bool mutationFound = false;
    for (int i = 0; i < num_genes; i++){
        //cout<< genes[i].g_name <<" "<<genes[i].total_mutations<<" ";
        if(genes[i].g_name == source){
            for(int j =0; j < genes[i].total_mutations; j++){
                if(genes[i].receiver[j].m_name == target && energy >= genes[i].receiver[j].energy_received  ){
                    mutationFound = true;
                }
                //cout<<genes[i].receiver[j].m_name<<" ";
                //cout<<genes[i].receiver[j].energy_received<<" ";
            }
            //cout<<endl;
        }
   }

   if(mutationFound == 1){
    cout<< "mutation can happen"<<endl;
   }else{
    cout<< "mutation can NOT happen"<<endl;
   }
    return 0;
}


int check_genes(Gene * genes, int num_genes, string source, string target){
    bool mutationFound = false;
    for (int i = 0; i < num_genes; i++){
        //cout<< genes[i].g_name <<" "<<genes[i].total_mutations<<" ";
        if(genes[i].g_name == source){
            for(int j =0; j < genes[i].total_mutations; j++){
                if(genes[i].receiver[j].m_name == target){
                    mutationFound = true;
                }
                //cout<<genes[i].receiver[j].m_name<<" ";
                //cout<<genes[i].receiver[j].energy_received<<" ";
            }
            //cout<<endl;
        }
   }

   if(mutationFound == 1){
    cout<< "mutation exists"<<endl;
   }else{
    cout<< "mutation does NOT exists"<<endl;
   }
    return 0;
}

int print_file(Gene * genes, int num_genes){
    for (int i = 0; i < num_genes; i++){
    cout<< genes[i].g_name <<" "<<genes[i].total_mutations<<" ";
        for(int j =0; j < genes[i].total_mutations; j++){
            cout<<genes[i].receiver[j].m_name<<" ";
            cout<<genes[i].receiver[j].energy_received<<" ";
        }
        cout<<endl;
   }
    return 0;
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

    for (int i = 0; i < *num_gene_p; i++) {
        infile >> firstGene >> num_mutations_p;
        genes[i].g_name = firstGene;
        genes[i].total_mutations = num_mutations_p;
        //cout << "gene "<<firstGene<<" total mutation "<<num_mutations_p <<endl;
        string MutationName;
        int energy;
        Mutation *mutations = new Mutation[num_mutations_p];
        for(int j =0; j < num_mutations_p; j++){
            infile >> MutationName >> energy;
            //cout<< "energy: "<< energy<< " and the name is "<< MutationName<<endl;
            mutations[j].m_name = MutationName;
            mutations[j].energy_received = energy;
        }
        genes[i].receiver = mutations;
    }
    infile.close();
    
    return genes;
}


