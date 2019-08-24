//Knights Tour

/*******To compile: g++ main.cpp -std=c++11 -> ./a.out (don't forget to add mentioned -std=c++11)
//(OR) 
// make main -> make run -> make clean(to clear the files)
*******/

#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <tuple>
#include <algorithm>

using namespace std;
 
template<int N = 8>
class chessBoard {
    public:
    array<pair<int, int>, 8> move;
    array<array<int, N>, N> data;
    
    //potential moves for the knight
    chessBoard() {
        move[0] = make_pair(2, 1);
        move[1] = make_pair(1, 2);
        move[2] = make_pair(-1, 2);
        move[3] = make_pair(-2, 1);
        move[4] = make_pair(-2, -1);
        move[5] = make_pair(-1, -2);
        move[6] = make_pair(1, -2);
        move[7] = make_pair(2, -1);
    }
 
    array<int, 8> makeMoves(int x, int y) const {
        array<tuple<int, int>, 8> counts;
        int i;
        for(i = 0; i < 8; ++i) {
            int dataX = get<0>(move[i]);
            int dataY = get<1>(move[i]);
 
            int c = 0;
            int j;
            for(j = 0; j < 8; ++j) {
                int xTwo = x + dataX + get<0>(move[j]);
                int yTwo = y + dataY + get<1>(move[j]);
 
                if (xTwo < 0 || xTwo >= N || yTwo < 0 || yTwo >= N)
                    continue;
                if(data[yTwo][xTwo] != 0)
                    continue;

                c++; //increment
            } // end for
            counts[i] = make_tuple(c, i);
        } // end for
 
        // randomly shuffle to break ties
        random_shuffle(counts.begin(), counts.end());
 
        // sort it out
        sort(counts.begin(), counts.end());
 
        array<int, 8> out;
        for(int i = 0; i < 8; ++i)
            out[i] = get<1>(counts[i]);
        return out;
    } // end array
    
    // knightTour the solution 
    void knightTour(string start) {
        for(int v = 0; v < N; ++v)
            for(int u = 0; u < N; ++u)
                data[v][u] = 0;
 
        int x0 = start[0] - 'a';
        int y0 = N - (start[1] - '0');
        data[y0][x0] = 1;
 
        array<tuple<int, int, int, array<int, 8>>, N*N> order;
        order[0] = make_tuple(x0, y0, 0, makeMoves(x0, y0));
 
        int n = 0;
        while(n < N*N-1) {
            int x = get<0>(order[n]);
            int y = get<1>(order[n]);
 
            bool fine = false;
            for(int i = get<2>(order[n]); i < 8; ++i) {
                int dataX = move[get<3>(order[n])[i]].first;
                int dataY = move[get<3>(order[n])[i]].second;
 
                if(x+dataX < 0 || x+dataX >= N || y+dataY < 0 || y+dataY >= N)
                    continue;
                if(data[y + dataY][x + dataX] != 0) 
                    continue;
 
                ++n;
                get<2>(order[n]) = i + 1;
                data[y+dataY][x+dataX] = n + 1;
                order[n] = make_tuple(x+dataX, y+dataY, 0, makeMoves(x+dataX, y+dataY));
                fine = true;
                break;
            } // end for
 
            if(!fine) // if failed, let's backtrack
            {
                data[y][x] = 0;
                --n;
            } //end if
        } // end while
    } //end knightTour
 
    template<int N1>
    friend ostream& operator<<(ostream &out, const chessBoard<N1> &b);
}; // end chessBoard

//print the results
template<int N> 
ostream& operator<<(ostream &out, const chessBoard<N> &b) {
    cout << "" << endl;
    cout << "Here is the result: " << endl;
    cout << "" << endl;
    for (int v = 0; v < N; ++v) {
        for (int u = 0; u < N; ++u) {
            if (u != 0) out << " ";
            out << setw(3) << b.data[v][u];
        } // end for 
        out << endl;
    } // end for
    return out;
}

//driver function
int main() {
    chessBoard<8> b2;
    b2.knightTour("b5");
    cout << b2 << endl;

    /*If you uncomment the code below you can print even different sizes of boards(must be >= 5) */
    /* If you try to print two 8x8 boards you will get two different solutions ;) */

    // chessBoard<6> b1; 
    // b1.knightTour("c3");
    // cout << b1 << endl;
 
    // chessBoard<10> b3; 
    // b3.knightTour("a1");
    // cout << b3 << endl;

    return 0;
} // end main
