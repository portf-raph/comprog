#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string &);

ostream &fout = cout;

void st_push(stack<tuple<int,int, int>> &st, int new_elem) {
    int new_min = st.empty() ? new_elem : min(new_elem, get<1>(st.top()));
    int new_max = st.empty() ? new_elem : max(new_elem, get<2>(st.top()));
    st.push({new_elem, new_min, new_max});
}

vector<float> solve(vector<int> arr, vector<pair<int,int>> queries) {
    vector<float> result;
    int N = arr.size();
    for (size_t i=0; i<queries.size(); i++) {
        int L = queries[i].first;
        int R = queries[i].second;

        // b_min & b_max
        stack<tuple<int,int,int>> LR;
        for (int j=L; j<=R; j++) {
            st_push(LR, arr[j]);
        }

        int b_min = get<1>(LR.top());
        int b_max = get<2>(LR.top());
        // fout << b_min << endl;
        // fout << b_max << endl;

        // max_L
        stack<tuple<int,int,int>> OL;
        float max_L=0;
        if (L>0) {
            for (int j=0; j<L; j++) {
                st_push(OL, arr[j]);
            }
            max_L = b_min + get<2>(OL.top());
            fout << get<2>(OL.top()) << endl;
        }

        // max_R
        stack<tuple<int,int,int>> RN;
        float max_R=0;
        if (R<N-1) {
            for (int j=R+1; j<N; j++) {
                st_push(RN, arr[j]);
            }
            max_R = b_min + get<2>(RN.top());
            fout << get<2>(RN.top()) << endl;
        }

        // max_LR
        float max_LR = b_min + (b_max - b_min) / 2.0;
        
        // max_N
        float res = max(max_L, max_LR);
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
