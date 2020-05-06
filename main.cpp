#include <iostream>
#include <string>
#include <sstream>
#include <set> 
#include <vector>
#include <map>

using namespace std;

class Triplet{
    public:
        string letter;
        string target;
        float weight;

    Triplet(string letter, string target, float weight){
        letter = letter;
        target = target;
        weight = weight;
    }
};

class State{
    public:
        bool final;
        float finalweight;
        map <string, vector<Triplet>> transitionsin; 
        map <string, vector<Triplet>> transitionsout;

    void add_transition(string target, string input, string output, float weight){
        if (transitionsin.find(input) == transitionsin.end()){
            vector<Triplet> triplets;
            transitionsin[input]= triplets;            
        } 

        if (transitionsout.find(output) == transitionsout.end()){
            vector<Triplet> triplets;
            transitionsout[output] = triplets;            
        }

        Triplet t_in = Triplet(output, target, weight);
        Triplet t_out = Triplet(input, target, weight);
        
        transitionsin.find(input)->second.push_back(t_in);
        transitionsin.find(output)->second.push_back(t_out);
    }

    vector<Triplet> get_transitions(string symbol, string dir){
        if (dir.compare("down")==0){
            if (transitionsin.find(symbol)==transitionsin.end()){
                vector<Triplet> v;
                return v;
            } else {
                return transitionsin.find(symbol)->second;
            }
        } else {
            if (transitionsout.find(symbol)==transitionsout.end()){
                vector<Triplet> v;
                return v;
            } else {
                return transitionsout.find(symbol)->second;
            }
        }
    }

    void set_final(float finalweight){
        final = true;
        finalweight = finalweight;
    }
};

class ATTFST{
    public:
        string epsilon_symbol;
        string identity_symbol;
        string unknown_symbol;
        map<int, State> states;
        set<string> alphabet;

    ATTFST(char* filename, string epsilon_symbol, string identity_symbol, string unknown_symbol){
        epsilon_symbol = epsilon_symbol;
        identity_symbol = identity_symbol;
        unknown_symbol = unknown_symbol;
        
        //read lines from att file
        vector<string> lines = read_lines(filename);

        for(auto i = lines.begin(); i<lines.end(); i++){
            cout << *i << endl;
        }
    }

    vector<string> read_lines(char* filename){
        char *cvalue = NULL;
        int c;

        FILE *f = fopen(filename, "r");		
        c = fgetc(f); // get one character from the input

        vector<string> lines;
        string line;

        while(c != EOF){	
        if((char)c !='\n'){ 
            line+=(char) c;
            }else{
                lines.push_back(line);
                line="";                
            }
        c = fgetc(f);	
        } 
        return lines;
    }

    string map_syms(string s){
        if(s.compare(epsilon_symbol)==0){
            return "";
        }
        return s;
    }

};



int main(int argc, char **argv){
    ATTFST fst = ATTFST(argv[1], "", "", "");
    //vector<string> v = fst.read_lines(argv[1]);
    
	return 0; 
}