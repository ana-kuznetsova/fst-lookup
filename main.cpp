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
        int target;
        float weight;

    Triplet(string letter, int target, float weight){
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

    void add_transition(int target, string input, string output, float weight){
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

        for(auto line_ptr = lines.begin(); line_ptr<lines.end(); line_ptr++){
            vector<string> fields = split_string(*line_ptr);
            if(fields.size() > 3){
                int source = stoi(fields[0]);
                int target = stoi(fields[1]);
                string insym = map_syms(fields[2]);
                string outsym = map_syms(fields[3]);
                float weight = 0.0;
                if(fields.size() > 4){
                    weight = stof(fields[4]);
                }
                alphabet.insert(insym);
                alphabet.insert(outsym);
                if(states.find(source)==states.end()){
                    State nss = State();
                    states[source] = nss;
                }
                if(states.find(target)==states.end()){
                    State nst = State();
                    states[target] = nst;
                }
                states[source].add_transition(target, insym, outsym, weight);
            } else if(fields.size() < 3 && fields.size() > 0){
                int final = stoi(fields[0]);
                float finalweight = 0.0;
                if(fields.size() > 1){
                    finalweight = stof(fields[1]);
                }
                if(states.find(final) == states.end()){
                    State nss = State();
                    states[final] = nss;
                }
                states[final].set_final(finalweight);
            }
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

    //split string by tab
    vector<string> split_string(string s){
        vector<string> tokens;
        string delimiter = "\t";
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos){
            token = s.substr(0, pos);
            tokens.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        return tokens;   
    }

    string splice(string word, int i, int j){
        string sp_word;
        for(int it = i; it < j; it++){
            sp_word.push_back(word.at(it));
        }
        return sp_word;
    }

    vector<string> tokenize(string word){
        vector<string> tokens;
        int start = 0;
        while(start < word.size()){
            string t;
            t.push_back(word.at(start));
            for (int l = 1; l <= word.size() - start; l++){
                string sp_word = splice(word, start, start + l);
                if(alphabet.find(sp_word) != alphabet.end()){
                    t = sp_word;
                } 
            tokens.push_back(t);
            start += t.size();
            }
        }
        return tokens;
    } 
};



int main(int argc, char **argv){
    ATTFST fst = ATTFST(argv[1], "", "", "");
    //vector<string> v = fst.read_lines(argv[1]);
    
	return 0; 
}