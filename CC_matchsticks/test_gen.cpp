#include <bits/stdc++.h>
#include <random>
using namespace std;

int main() {
    int min_rand = 1;
    int max_rand = 30;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min_rand, max_rand);

    int n = distrib(gen);
    // array
    cout << n << endl;
    for (int i=0; i<n; i++) {
        cout << distrib(gen);
        if (!(i==n-1)) {
            cout << " ";
        }
    }
    cout << endl;
    
    // queries
    int q = distrib(gen);
    cout << q << endl;

    random_device rd_q;
    mt19937 gen_q(rd_q());
    uniform_int_distribution<> distrib_q(1, n-1);

    for (int i=0; i<q; i++) {
        int q_1 = distrib_q(gen_q);
        int q_2 = distrib_q(gen_q);
        
        int L = (q_1 <= q_2) ? q_1 : q_2;
        int R = (L == q_1) ? q_2 : q_1;

        cout << L << " " << R << endl;
    }
}
