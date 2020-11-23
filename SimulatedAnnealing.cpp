#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include<ctime>
#include "WriteCSV.h"
#define temp 4000
using namespace std;

int unsolved{0};
void print_matrix(vector<int> queenmatrix) { // printing the matrix
int a;cout<<"\nSolved n-Queen matrix\n";
    for (int queen = 0; queen < queenmatrix.size(); queen++){
            a=queenmatrix[queen];
        for(int j=0;j<queenmatrix.size();j++){
            if(j==a)    cout<<"Q \t";
            else cout<<"--\t";
            
        }cout<<"\n";
    }
    
}

int threat_calculator(int n) { // combination formula for calculating number of pairs of threatened queens
    if (n < 2) return 0;
    if (n == 2) return 1;
    return (n - 1) * n / 2;
}

int cost(vector<int> queenmatrix) { // cost function to count total of pairs of threaten queens
    unsigned long size = queenmatrix.size();
    int threat = 0;
    int m_matrix[size];
    int a_matrix[size];

    for (int i = 0; i < size; i++) {
        a_matrix[i] = i + queenmatrix[i];
        m_matrix[i] = i - queenmatrix[i];
    }

    sort(m_matrix, m_matrix + size);
    sort(a_matrix, a_matrix + size);

    int m_count = 1;
    int a_count = 1;

    for (int i = 0; i < size - 1; i++) {
        int j = i + 1;
        if (m_matrix[i] == m_matrix[j]) m_count += 1;
        else {
            threat += threat_calculator(m_count);
            m_count = 1;
        }
        if (a_matrix[i] == a_matrix[j]) a_count += 1;
        else {
            threat += threat_calculator(a_count);
            a_count = 1;
        }
        if (j == size - 1) {
            threat += threat_calculator(m_count);
            threat += threat_calculator(a_count);
            break;
        }
    }

    return threat;
}

void Solve(int n_queens, map<int, double>&mapp){
    srand((unsigned int) time(nullptr));
    random_device rd;
    mt19937 g(rd());
    int a;
    bool isSolved;
    vector<int> answer;
    // unsigned int n_queens; // number of queens

    // cout << "Number of queens: ";
    // cin >> n_queens;
    
    // creating a random board 
    answer.reserve(n_queens);
    for (int i = 0; i < n_queens; i++) { // create a vector from 0 to N_QUEENS - 1 representing if a given row contains a queen
        answer.emplace_back(i);
    }
    shuffle(answer.begin(), answer.end(), g); //shuffle chess board to make sure it is random
    //  cout<<"\nRandom matrix with queens placed randomly taken as an instance\n"; 
    // for (int queen = 0; queen < answer.size(); queen++){
    //         a=answer[queen];
    //     for(int j=0;j<answer.size();j++){
    //         if(j==a)    cout<<"Q \t";
    //         else cout<<"--\t";
            
    //     }cout<<"\n";
    // }
    // starting after avoiding overloads of loading and IO
    clock_t start = clock();
    int cost_answer = cost(answer); // To avoid recounting in case can not find a better state
   
    // simulated annealing5
    
    vector<int> successor;
    successor.reserve(n_queens);
    double t = temp;
    double sch = 0.99;
    while (t > 0) {
        int rand_col_1;
        int rand_col_2;
        t *= sch;
        successor = answer;
        while (true) { // random 2 queens
            rand_col_1 = (int) rand() % n_queens;
            rand_col_2 = (int) rand() % n_queens;
            if (successor[rand_col_1] != successor[rand_col_2]) break;
        }
        swap(successor[rand_col_1], successor[rand_col_2]); // swap two queens chosen
        double delta = cost(successor) - cost_answer;
        if (delta < 0){
            answer = successor;
            cost_answer = cost(answer);
        }
        else {
            double p = exp(-delta / t);
            if (rand() / double(RAND_MAX) < p) {
                answer = successor;
                cost_answer = cost(answer);
            }
        }

       
        if (cost_answer == 0) {
            // print_matrix(answer);
            isSolved = true;
            // mapp.insert(make_pair(n_queens, Runtime));
            // WriteCSV("SimulatedAnnealing.csv",mapp);
            break;
        }
      
    }
     clock_t stop = clock();
    double Runtime = (float) (stop - start) / 1000000;
    cout << "Runtime: " << "for N: " << n_queens << " is " << Runtime  <<  " seconds" << endl;

      if(isSolved) {
            // print_matrix(answer);
            mapp.clear();
            mapp.insert(make_pair(n_queens, Runtime));
            WriteCSV("SimulatedAnnealing.csv",mapp);
         }
        else{
            mapp.clear();
            double zero = 0;
            mapp.insert(make_pair(n_queens, -1));
            unsolved++;
            cout << "Could not find the solution" << endl;
            WriteCSV("SimulatedAnnealing.csv", mapp);
        }
    
}

int main(){
   
    map<int, double> mapp;
    int n_queens;
    int N = 500;
    for(int i = 4; i< N; i++){
      cin >> n_queens;
       Solve(n_queens,mapp);
    }
    cout << "Unsolved " << unsolved << "\n";
    return 0;
}