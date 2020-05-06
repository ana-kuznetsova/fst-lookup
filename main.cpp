#include <iostream>
#include <string>
#include <sstream>
#include <set> 
#include <vector>
#include <map>

using namespace std;

class Triplet{
    public:
        char letter;
        char target;
        float weight;

    Triplet(char letter, char target, float weight){
        letter = letter;
        target = target;
        weight = weight;
    }
};

class State{
    public:
        bool final;
        float finalweight;
        map <char, vector<Triplet>> transitionsin; 
        map <char, vector<Triplet>> transitionsout;

    void add_transition(char target, char input, char output, float weight){
        if (transitionsin.find(input) == transitionsin.end()){
            vector<Triplet> triplets;
            transitionsin.insert(input, triplets);            
        } 

        if (transitionsout.find(output) == transitionsout.end()){
            vector<Triplet> triplets;
            transitionsout.insert(output, triplets);            
        }

        Triplet t_in = Triplet(output, target, weight);
        Triplet t_out = Triplet(input, target, weight);
        
        transitionsin.find(input)->second.push_back(t_in);
        transitionsin.find(output)->second.push_back(t_out);
    }

    vector<Triplet> get_transitions(char symbol, string dir){
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
}

int main()
{

return 0;
} 
