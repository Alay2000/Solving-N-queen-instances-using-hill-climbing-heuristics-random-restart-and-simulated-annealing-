#include <functional>

namespace hash_tuple {
template <typename TT> struct hash {
    size_t operator()(TT const &tt) const { return std::hash<TT>()(tt); }
};
template <class T> inline void hash_combine(std::size_t &seed, T const &v) {
    seed ^= hash_tuple::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
    void operator()(size_t &seed, Tuple const &tuple) const {
        HashValueImpl<Tuple, Index - 1>{}(seed, tuple);
        hash_combine(seed, std::get<Index>(tuple));
    }
};
template <class Tuple> struct HashValueImpl<Tuple, 0> {
    void operator()(size_t &seed, Tuple const &tuple) const {
        hash_combine(seed, std::get<0>(tuple));
    }
};

template <typename... TT> struct hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const &tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>{}(seed, tt);
        return seed;
    }
};
template <typename T> inline void hash_val(std::size_t &seed, const T &val) {
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}
template <typename... Types>
inline std::size_t hash_val(const Types &... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};
}


#include<bits/stdc++.h>
using namespace std;
#ifndef Head_Queen
#define Head_Queen
vector<int>start;



#define OFF 0 //Representing 0 as stop
#define ON 1 // Representing 1 as go_on

class N_Queen
{
    public:
        N_Queen(int, int);
        virtual ~N_Queen();
        int find_x();
        int find_y();
        void select_x(int);
        void select_y(int);
        int walking_up(int); // taking upward one step
        int walking_down(int); // taking one step downward
    protected:
    private:
        int xval; // xval  on the screen_board
        int yval; // yval  on the screen_board
};

#endif // H_Queen

#ifndef Head_state
#define Head_state


class States
{
    public:
        States();
        States(int);
        virtual ~States();
        vector<N_Queen> find_queens();
        void append_queen(N_Queen); // add queens_arrray on the screen_board
        vector<States> possible_sates(); // possible states for this state
        States best_possible_states(); // finding best possible state for this  state
        int attacking_count(); // number of possible attks between 2 queens_arrray
        int get_n();
        void print_board(); // print the screen_board
    protected:
    private:
        vector<N_Queen> queens_arrray; // list of on the screen_board
        int no; // screen_board dimension_size
};

#endif // Head_state

States::States() {
    // constructor
}

/* sets dimension_size of screen_board */
States::States(int dimension_size) {
    no = dimension_size;
    start.clear();
    for(int i = 0; i < no; i++) {
        int number = rand() % no;
        start.push_back(number);
        N_Queen q(number, i); // setting value for random rows and different columns
        this->append_queen(q);
    }
}

/* calling the destructor */
States::~States() {
   
}

/* Getter method for n */
int States::get_n() {
    return no;
}

/* Adding a queen to the list of queens */
void States::append_queen(N_Queen q) {
    if((int)queens_arrray.size() < no) {
        queens_arrray.push_back(q); // pushing the queen in the list
    }
}

/* Getting all possible states from this state by making each of the queen on the screen_board 
// manipulating  its x_value, but with  fixed */
vector<States> States::possible_sates() {
    vector<States> pos_staes;
    int x_already, y_already;
    for(int i = 0; i < no; i++) {
        // position initially
        x_already = queens_arrray[i].find_x();
        y_already = queens_arrray[i].find_y();
        while(queens_arrray[i].walking_up(no) != OFF)
            pos_staes.push_back(*this);
        queens_arrray[i].select_x(x_already);
        queens_arrray[i].select_y(y_already);
        while(queens_arrray[i].walking_down(no) != OFF)
            pos_staes.push_back(*this);
        queens_arrray[i].select_x(x_already);
        queens_arrray[i].select_y(y_already);
    }
    return pos_staes;
}

/* possible number attacks counting */
int States::attacking_count() {
    // counting number of attacks in rows
    int attack_row = 0;
    int row_queen[no];
    for(int i = 0; i < no; i++)
        row_queen[i] = 0;
    // counting number of attacks in diagonals
    int diagonally_attacks = 0;
    int queens_by_diagonal[2*no-1], queens_by_diagonal_2[2*no-1];
    for(int i = 0; i < 2*no-1; i++) {
        queens_by_diagonal[i] = 0;
        queens_by_diagonal_2[i] = 0;
    }
    // counting number of queens
    int xval, yval;
    for(int i = 0; i < no; i++) {
        xval = queens_arrray[i].find_x();
        yval = queens_arrray[i].find_y();
        ++row_queen[xval]; // for each row
        ++queens_by_diagonal[xval+yval]; // antidiagonal direction
        ++queens_by_diagonal_2[no-1+yval-xval]; // in each primary diagonal direction
    }
    // row_wise number of attks
    for(int i = 0; i < no; i++)
        if(row_queen[i] > 1)
            attack_row += row_queen[i] - 1;
    // Diagonally number of attckks
    for(int i = 0; i < 2*no-1; i++) {
        if(queens_by_diagonal[i] > 1)
            diagonally_attacks += queens_by_diagonal[i] - 1;
        if(queens_by_diagonal_2[i] > 1)
            diagonally_attacks += queens_by_diagonal_2[i] - 1;
    }
    return diagonally_attacks + attack_row;
}


States States::best_possible_states() {
    vector<States> pos_staes = possible_sates();
    int number_of_possible_states = pos_staes.size();
    vector<int> best_possible;
    int minimum_index; // index for best possible successor
    int attacks_min = no*no; 
    int attks;
    for(int i = 0; i < number_of_possible_states; i++) {
        attks = pos_staes[i].attacking_count();
        if(attks < attacks_min) { // trying to find a new minimum
            attacks_min = attks;
            best_possible.clear(); // restart the vector
            best_possible.push_back(i); // adding the new minimum value
        }
        else if(attks == attacks_min) 
            best_possible.push_back(i); // adds to list of best possible states
    }
    

    //initializing random number
    minimum_index = rand() % (int)best_possible.size();
    return pos_staes[best_possible[minimum_index]];
}

/* Printing the screen_board */
void States::print_board() {
    char screen_board[no][no];
    // initializing with underscores
    for(int i = 0; i < no; i++)
        for(int j = 0; j < no; j++)
            screen_board[i][j] = '_';
    // putting on screen_board the queens
    for(int i = 0; i < no; i++)
        screen_board[queens_arrray[i].find_x()][queens_arrray[i].find_y()] = 'Q';
    // now prining :::
    for(int i = 0; i < no; i++)
        for(int j = 0; j < no; j++)
            cout << screen_board[i][j] << (j == no-1 ? "\n" : " ");
}

/*  Constructor function */
N_Queen::N_Queen(int coord_x, int coord_y) {
    xval = coord_x;
    yval = coord_y;
}

/* Destructor function */
N_Queen::~N_Queen() {

}

/* Getter method funcion for x_value */
int N_Queen::find_x() {
    return xval;
}

/* Getter method function for y_value */
int N_Queen::find_y() {
    return yval;
}

/* Setter method function for x_value */
void N_Queen::select_x(int coord_x) {
    xval = coord_x;
}

/* Setter method function  for y_value */
void N_Queen::select_y(int coord_y) {
    yval = coord_y;
}


int N_Queen::walking_up(int no) {
    if(xval > 0) {
        --xval; // down step
        return ON;
    }
    return OFF;
}


int N_Queen::walking_down(int no) {
    if(xval < no-1) {
        ++xval; // up step
        return ON;
    }
    return OFF;
}


/* Finally Hill_climb algo for finding the min number of attacks */
States Hill_climb(States now) {
    States further;
    int no_of_iteration = 1; // iteration counting
    while(true) { // find the solution unless an error occur
        further = now.best_possible_states();
        if(now.attacking_count() <= further.attacking_count()) {
            return now;
        }
        now = further;
        ++no_of_iteration;
    }
    // error case
    return States(-1);
}

int main() {
    int dimension_size;
    cout << "Enter the Dimension Size: \n";
    cin >> dimension_size;
    States initial_state(dimension_size);

    States solution = Hill_climb(initial_state);
    // if in the case not able to find the solution ::
    // reset the inital stage and trying again 
    while(solution.attacking_count() > 0) {
        States initial_state(dimension_size);
        solution = Hill_climb(initial_state);
    }
    cout << "\nInitial States of Queens:\n\n";
    for(int i=0;i<dimension_size;i++){
        for(int j=0;j<dimension_size;j++){
            if(start[i]==j){
                cout << 'Q' << " ";
            }
            else{
                cout << "_" << " ";
            }
        }
        cout << "\n";
    }
    cout << "\nFinal Output:\n" << endl;
    if(solution.get_n() == -1)
        cout << "Error" << endl;
    else {
        solution.print_board();
        
    }
    return 0;
}