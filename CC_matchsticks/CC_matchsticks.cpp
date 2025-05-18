#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string &);

ostream &fout = cout;
vector<float> solve(vector<int> arr, vector<pair<int,int>> queries) {
    // sparse table
    int N = arr.size();
    
    // log table
    int lg[N+1];
    lg[1] = 0;
    for (int i=2; i <= N; i++) {
        lg[i] = lg[i/2] + 1;
    } 

    // precompute min and max table
    int K = lg[N];
    int st_min[K+1][N];
    int st_max[K+1][N];
    copy(arr.begin(), arr.end(), st_min[0]);
    copy(arr.begin(), arr.end(), st_max[0]);

    for (int i=1; i <= K; i++) {
        for (int j=0; j + (1 << i) <= N; j++) {
            st_min[i][j] = min(st_min[i-1][j], st_min[i-1][j+(1<<(i-1))]);
            st_max[i][j] = max(st_max[i-1][j], st_max[i-1][j+(1<<(i-1))]);
        }
    }

    // results vector
    vector<float> result;
    for (size_t i=0; i < queries.size(); i++) {
        int L = queries[i].first;
        int R = queries[i].second;
        int k = lg[R-L+1];
        int b_min = min(st_min[k][L], st_min[k][R - (1 << k)+1]);
        int b_max = max(st_max[k][L], st_max[k][R - (1 << k)+1]);
        float max_LR = b_min + (b_max - b_min) / 2.0;
        //fout << b_min << endl;
        //fout << b_max << endl;
        //fout << max_LR << endl;
        //fout << endl;
        
        float max_L = 0;
        if (L > 0) {
            int k_L = lg[L-1+1];
            max_L = max(st_max[k_L][0], st_max[k_L][L-1 - (1 << k_L) + 1]) + b_min;
            //fout << max_L << endl;
        }

        float max_R = 0;
        if (R < N-1) {
            int k_R = lg[N-1 - (R+1) + 1];
            max_R = max(st_max[k_R][R+1], st_max[k_R][N-1 - (1 << k_R) + 1]) + b_min;
            //fout << max_R << endl;
        }

        float res = max(max_LR, max_L);
        float max_N = max(res, max_R);
        result.push_back(max_N);
    }
    return result;
}

int main() {
    string first_single_input;
    getline(cin, first_single_input);
    int n = stoi(first_single_input);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);
    vector<string> arr_temp = split(arr_temp_temp);
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    string second_single_input;
    getline(cin, second_single_input);
    int q = stoi(second_single_input);
    
    vector<pair<int,int>> queries(q);
    for (int i = 0; i < q; i++) {
        string queries_multiple_temp_temp;
        getline(cin, queries_multiple_temp_temp);
        vector<string> queries_multiple_temp = split(queries_multiple_temp_temp);
        
        pair<int,int> queries_multiple;
        int first_item = stoi(queries_multiple_temp[0]);
        int second_item = stoi(queries_multiple_temp[1]);
        queries_multiple.first = first_item;
        queries_multiple.second = second_item;

        queries[i] = queries_multiple;
    }
    
    vector<float> result = solve(arr, queries);
    
    fout << fixed << setprecision(1);
    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    return 0;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
