#include <string>
#include <iostream>
#include <fstream>

using namespace std;
struct Gene;

struct Mutation {
    int cost;
    Gene *target;
};

struct Gene {
    string sq; // Name of gene sequence
    bool seen; // Used in recursive functions to avoid loops
    Mutation mut;
};

const string EVOLVE = "e";
const string E_STEPS = "es";
const string ENE_EVOLVE = "ene";
const string PATH = "path";
const string QUIT = "q";

Gene *read_genes(string filename, int *num_genes);
void populate_nodes(Gene *genes, ifstream *inf, int num_nodes);
void populate_links(Gene *genes, ifstream *inf, int num_nodes);
int index_of(Gene *genes, string seq, int num_nodes);
void init(Gene *genes, int num_nodes);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: No filename provided as an argument" << endl;
        exit(EXIT_FAILURE);
    }

    //After these two lines execute, all_genes is a pointer to the array of gene
    //information read in from a given data file, and num_genes contains the
    //number of genes stored in that array.
    int num_genes;
    Gene *all_genes = read_genes(argv[1], &num_genes);

    //USE all_genes AND num_genes AFTER THIS LINE TO CONTINUE THE COMPUTATION

    return 0;
}

// read_genes
// Input: A file name and a pointer to store the number of genes in the file.
// Description: Read in a file provided the user and use the data to populate an
//              array of Genes.
// Output: Returns a pointer to an array of Genes (populated with the contents
//         of a data file), and indirectly returns the number of array elements
//         through the num_genes pointer.
Gene *read_genes(string filename, int *num_genes)
{
    ifstream inf;
    inf.open(filename);
    if (inf.fail()) {
        cout << "ERROR OPENING FILE: Exiting Program" << endl;
        exit(EXIT_FAILURE);
    }

    inf >> *num_genes;

    // Create and populate the the names in the array of genes
    Gene *dna_p = new Gene[*num_genes];
    init(dna_p, *num_genes);
    populate_nodes(dna_p, &inf, *num_genes);

    // Reset the file to read in the mutation information
    inf.close();
    inf.open(filename);
    inf >> *num_genes; // NEED TO READ "past" NUMBER ON FIRST LINE

    populate_links(dna_p, &inf, *num_genes);

    inf.close();

    return dna_p;
}

// init
// Input: A pointer to an uninitialized array of genes and the size of
//        that array.
// Description: Initializes the array of genes with non-garbage information.
// Output: Initializes the array pointed to by 'dna'.
void init(Gene *dna, int num_nodes)
{
    for (int i = 0; i < num_nodes; i++) {
        dna[i].sq = "";
        dna[i].seen = false;
        dna[i].mut.cost = -1;
        dna[i].mut.target = nullptr;
    }
}

// populate_nodes
// Input: A pointer to an array of genes, a pointer to a file stream,
//        and the size of the array.
// Description: Read the file pointed to and set the sequence name of
//              each gene in the array.
// Output: Populates the sequence information for the gene array pointed to by
//         'dna'. Moves the file pointer further into the file.
void populate_nodes(Gene *dna, ifstream *inf, int num_nodes)
{
    string seq, mut_seq;
    int num_muts, num;
    for (int i = 0; i < num_nodes; i++) {
        *inf >> seq >> num_muts;
        dna[i].sq = seq;
        for (int j = 0; j < num_muts; j++) {
            *inf >> mut_seq >> num;
        }
    }
}

// populate_links
// Input: A pointer to an array of genes, a pointer to a file stream,
//        and the size of the array.
// Description: Read the file pointed to and populate the mutation
//              information between genes in the array. We assume the data file
//              only contains well-formed input.
// Output: Populates the mutation information for the gene array pointed to by
//         'dna'. Moves the file stream pointed to further into the file.
void populate_links(Gene *dna, ifstream *inf, int num_nodes)
{
    string seq, mut_seq;
    int num_muts;
    for (int i = 0; i < num_nodes; i++) {
        *inf >> seq >> num_muts;

        // Add the one mutation if it exists
        if (num_muts == 1) {
            int cost;
            *inf >> mut_seq >> cost;

            int index = index_of(dna, mut_seq, num_nodes);

            dna[i].mut.cost = cost;
            dna[i].mut.target = &dna[index];
        }
    }
}

// index_of
// Input: An array of genes, a gene sequence, and the size of the array.
// Description: Find the index of the given sequence in the array.
// Output: The index of the sequence in the array, or -1 if the sequence is not
//         in the array.
int index_of(Gene *dna, string seq, int num_nodes)
{
    for (int i = 0; i < num_nodes; i++) {
        if (dna[i].sq == seq) {
            return i;
        }
    }
    return -1;
}
// evolution
// Input: Pointer to array of genes, number of genes, source gene, and target gene.
// Description: Checking if evolution is possible or not
// Output: Source can or cannot evolve into target.
bool evolution(Gene *genes, string src, string tgt, int num_genes)
{
    int 1 = 0;
    Gene *new_source = check_existence(genes, num_genes, src, i);
    string new_src;

    if (new_source == nullptr)
    {
        return false;
    }
    else if (new_source->mut.target->sq == tgt)
    {
        return true;
    }
    else if (new_source->mut.target == true)
    {
        return false;
    }
    else if (new_source->seen == true)
    {
        return false;
    }
    else if (new_source->mut.target != nullptr)
    {
        new_source->seen = true;
        new_src = new_source->mut.target->sq;
    }
    return evolution(genes, num_genes, new_src, tgt);
}
// evolution steps
// Input: Pointer to array of genes, number of genes, source gene, and target gene.
// Description: Checking if evolution is possible or not
// Output: Source can or cannot evolve into target.
void evolution_steps_help(Gene *all_genes, int num_nodes)
{
    string src, tgt, new_src;
    cin >> src >> tgt;
    Gene *tgt_g = &all_gene[index_of(all_genes, tgt, num_nodes)];
    Gene *src_g = &all_gene[indez_of(all_genes, src, num_nodes)];

    if (index_of(all_genes, src, num_nodes) == -1)
    {
        cout << "It will take " << -1 << " evolutionary steps to get from " << src << " to " << tgt << endl;
        cout << endl;
        return;
    }
    reset_loop(all_genes, num_nodes);

    int n = 0;

    n = evolution_steps(src_g, tgt_g, n);

    if (n == -1)
    {
        cout << "It will take " << -1 << " evolutionary steps to get from " << src << " to " << tgt << endl;
        cout << endl;
    }
    else
    {
       cout << "It will take " << n << " evolutionary steps to get from " << src << " to " << tgt << endl;
        cout << endl; 
    }
}
