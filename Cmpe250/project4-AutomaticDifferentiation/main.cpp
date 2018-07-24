
#include <iostream>
#include "graph.h"
#include <sstream>
#include <iterator>
#include <vector>
#include <iomanip>

using namespace std;
template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc,char* argv[]){

    Graph graph;
    graph.readGraph(argv[1]);
    ifstream infile(argv[2]);
    //ofstream out(argv[3]);
    //ofstream output(argv[4]);
    ofstream out;
    out.open(argv[3]);
    ofstream output;
    output.open(argv[4]);
    if(!graph.isCyclic()) {
        string line;
        getline(infile, line);
        vector<string> words;
        split1(line, words);
        out << graph.getName() << endl;
        for (int i = 0; i < graph.inputNames.size(); i++) {
            output << "d" << graph.getName() << "/" << "d" << graph.inputNames[i] << " ";
        }
        output << endl;
        while (words.size() != 0) {
            Graph g;
            g.readGraph(argv[1]);
            words.clear();
            getline(infile, line);
            words.clear();
            split1(line, words);
            vector<double> inputt;
            for (int i = 0; i < words.size(); i++) {
                inputt.push_back(stod(words[i]));
            }
            out << setprecision(16);
            out << fixed;
            output << setprecision(16);
            output << fixed;
            if (words.size() != 0) {
                out << g.forwardPass(inputt) << endl;
                vector<double> derivative = g.backwardPass();
                for (int i = 0; i < derivative.size(); i++) {
                    output << derivative[i] << " ";
                }
                output << endl;
            }

        }
    }
    else if(graph.isCyclic()){
        out << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
        output << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
    }
    out.close();
    output.close();
    return 0;
}
