//
//  main.cpp
//  p5-ml
//
//  Created by Connor Turco on 4/20/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include <cassert>  //assert
#include <iostream> //ostream
#include <functional> //less
#include "BinarySearchTree.h"
#include "Map.h"
#include "csvstream.h"
#include <string>
#include <algorithm>

using namespace std;

class Classifier {
public:
    void set_numposts(int numposts_in) {
        numposts = numposts_in;
    }
    int get_numposts() {
        return numposts;
    }
    void read_row(set<string> row_in, string label_in) {
        for(auto it : row_in) {
            ++words[it];
            ++cw[label_in][it];
        }
        ++label[label_in];
        
    }
    int get_size() {
        return static_cast<int>(words.size());
    }
    void print_training_data() {
        cout << "classes:" << endl;
        for (auto i : label) {
            cout << "  " << i.first << ", " << i.second
            << " examples, log prior = " << log_prior(i.first) << endl;
        }
        
        cout << "classifier parameters: " << endl;
        for(map<string, map<string, int>>:: iterator outer = cw.begin();
            outer != cw.end(); ++outer) {
            for(map<string, int>::iterator inner = outer->second.begin();
                inner != outer->second.end(); ++inner) {
                cout << "  " << outer->first << ":" << inner->first
                << ", count = "<< inner->second << ", log-likelihood = "
                << log_liklihood(inner->first, outer->first) << endl;
            }
            
        }
    }

    vector<pair<string,double>>::iterator most_probable(const Classifier &a1) const {
        vector<pair<string, double>> scores;
        for (auto i: a1.label) {
            double totalscore = a1.log_prior(i.first);
            for(auto j : words) {
                totalscore += a1.log_liklihood(j.first, i.first);
            }
            pair<string, double> pair1;
            pair1.first = i.first;
            pair1.second = totalscore;
            scores.push_back(pair1);
        }
        auto it = max_element(scores.begin(), scores.end(), SecondElementLess());
        return it;
    }
    double log_prior(string label_in) const {
        double numerator = label.at(label_in);
        return log(numerator/numposts);
    }
    double log_liklihood(string word, string label_in) const {
        if(words.find(word) == words.end()) {
            return log(1.0/numposts);
        }
        if(cw.find(label_in)->second.find(word) == cw.find(label_in)->second.end()) {
            double numerator = static_cast<double>(words.at(word));
            return log(numerator/numposts);
        }
        double numerator = static_cast<double>(cw.find(label_in)->second.at(word));
        double denominator = static_cast<double>(label.at(label_in));
        return log(numerator / denominator);
        
    }
    
    
private:
    map<string, int> words;
    map<string, int> label;
    
    //# posts with label c & contain w, first string is label, second word
    map<string, map<string, int>> cw;
    int numposts;
    
    class SecondElementLess {
    public:
        bool operator() (const pair<string, double> &lhs, const pair<string, double> &rhs) {
            return lhs.second < rhs.second;
        }
    };
    
};

set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;

    // Read word by word from the stringstream and insert into the set
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

void read_in(Classifier &read_to, string filename, bool debug) {
    csvstream csvin(filename);
    int numrows = 0;
    map<string, string> row;
    while (csvin >> row) {
        ++numrows;
        auto set = unique_words(row["content"]);
        read_to.read_row(set, row["tag"]);
        if(debug) {
            cout << "label = " << row["tag"] << ", content = "
            << row["content"] << endl;
        }
        
    }
    read_to.set_numposts(numrows);
}
void read_in_test(Classifier &training, string filename) {
    csvstream csvin(filename);
    map<string, string> row;
    int total_loops = 0;
    int total_correct = 0;
    
    
    while (csvin >> row) {
        ++total_loops;
        Classifier read_to;
        auto set = unique_words(row["content"]);
        read_to.read_row(set, row["tag"]);
        
        cout << "  correct = " << row["tag"] << ", predicted = "
        << read_to.most_probable(training)->first << ", log-probability score = "
        << read_to.most_probable(training)->second << endl;
        
        cout << "  content = " << row["content"] << endl << endl;
        if(row["tag"] == read_to.most_probable(training)->first) {
            ++total_correct;
        }
    }
    cout << "performance: " << total_correct << " / " << total_loops
    << " posts predicted correctly" << endl;
    
   
}


int main(int argc, char* argv[]) {
    //Sets floating point precision, told to add in project spec
    cout.precision(3);
    
    //Check for errors
    if(argc != 3 && argc != 4) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 5;
    }
    
    
    bool debug = false;
    if(argc == 4) {
        string arg3 = string(argv[3]);
        if(arg3 != "--debug") {
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 6;
        }
        if(arg3 == "--debug") {
            debug = true;
        }
        
    }
    
    string trainingfile = string(argv[1]);
    string testingfile = string(argv[2]);
    
    //Catch blocks catch any file opening errors thrown by csvstream
    try {
        csvstream csvin(trainingfile);
    } catch (csvstream_exception) {
        cout << "Error opening file: " << trainingfile << endl;
        return 7;
    }
    
    try {
        csvstream csvin(testingfile);
    } catch (csvstream_exception) {
        cout << "Error opening file: " << testingfile << endl;
        return 7;
    }
    Classifier training;

    read_in(training, trainingfile, debug);
    cout << "trained on " << training.get_numposts() << " examples" << endl;
    if(debug) {
        cout << "vocabulary size = " << training.get_size() << endl << endl;
    }
    if(debug) {
        training.print_training_data();
    }
    cout << endl;
    cout << "test data:" << endl;
    read_in_test(training, testingfile);
    
}

