#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
#define temp 4000
#define LI long int
#define pb push_back
#define mp make_pair
#define FO(i, n) for (long int i = 0; i < n; i++)
#define endl "\n"

// printing the matrix
void print_matrix(vector<LI> Q_matrix)
{
    LI check;
    cout << "\nSolved n-Queen matrix\n";
    FO(i, Q_matrix.size())
    {
        check = Q_matrix[i];
        FO(j, Q_matrix.size())
        {
            if (j == check)
                cout << "Q \t";
            else
                cout << "--\t";
        }
        cout << "\n";
    }
}

// combination formula for calculating number of pairs of threatened queens
LI threat_calc(LI n)
{
    if (n < 2)
        return 0;
    if (n == 2)
        return 1;
    return (n - 1) * n / 2;
}

LI cost(vector<LI> Q_matrix)
{ // cost function to count total of pairs of threaten queens
    unsigned long size = Q_matrix.size();
    LI threat = 0;
    LI m_matrix[size];
    LI n_matrix[size];

    FO(i, size)
    {
        n_matrix[i] = i + Q_matrix[i];
        m_matrix[i] = i - Q_matrix[i];
    }

    sort(m_matrix, m_matrix + size);
    sort(n_matrix, n_matrix + size);

    LI m_count = 1;
    LI n_count = 1;

    FO(i, size - 1)
    {
        LI j = i + 1;
        if (m_matrix[i] == m_matrix[j])
            m_count += 1;
        else
        {
            threat += threat_calc(m_count);
            m_count = 1;
        }
        if (n_matrix[i] == n_matrix[j])
            n_count += 1;
        else
        {
            threat += threat_calc(n_count);
            n_count = 1;
        }
        if (j == size - 1)
        {
            threat += threat_calc(m_count);
            threat += threat_calc(n_count);
            break;
        }
    }

    return threat;
}

int main()
{
    clock_t start = clock();
    srand((unsigned int)time(nullptr));
    random_device rd;
    mt19937 g(rd());
    LI check;
    vector<LI> answer;

    // number of queens
    LI n_queens;
    cout << "Number of queens: ";
    cin >> n_queens;

    // create a random board
    answer.reserve(n_queens);
    FO(i, n_queens)
    {
        // create a vector from 0 to N_QUEENS - 1
        answer.emplace_back(i);
    }
    //shuffle chess board to make sure it is random
    shuffle(answer.begin(), answer.end(), g);
    // To avoid recounting in case can not find a better state
    LI cost_answer = cost(answer);
    cout << "\nRandom matrix with queens placed randomly taken as an instance\n";
    FO(i, answer.size())
    {
        check = answer[i];
        FO(j, answer.size())
        {
            if (j == check)
                cout << "Q \t";
            else
                cout << "--\t";
        }
        cout << "\n";
    }

    // simulated annealing5
    vector<LI> successor;
    successor.reserve(n_queens);
    double t = temp;
    double sch = 0.99;
    while (t > 0)
    {
        LI rand_col_1;
        LI rand_col_2;
        t *= sch;
        successor = answer;
        while (true)
        {
            // random 2 queens
            rand_col_1 = (LI)rand() % n_queens;
            rand_col_2 = (LI)rand() % n_queens;
            if (successor[rand_col_1] != successor[rand_col_2])
                break;
        }
        swap(successor[rand_col_1], successor[rand_col_2]); // swap two queens chosen
        double delta = cost(successor) - cost_answer;
        if (delta < 0)
        {
            answer = successor;
            cost_answer = cost(answer);
        }
        else
        {
            double p = exp(-delta / t);
            if (rand() / double(RAND_MAX) < p)
            {
                answer = successor;
                cost_answer = cost(answer);
            }
        }
        if (cost_answer == 0)
        {
            print_matrix(answer);
            break;
        }
    }

    clock_t stop = clock();
    cout << "Runtime: " << (float)(stop - start) / 1000000 << " seconds" << endl;

    return 0;
}