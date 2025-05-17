#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER_ARRAY queries
 */
ostream &fout = cout;
int cnt_add=0;
void print_queue(deque<pair<int,int>> q)
{
  while (!q.empty())
  {
    fout << q.front().first << " ";
    q.pop_front();
  }
  fout << endl;
}

void q_push(deque<pair<int,int>> &q, int new_element) {
    while (!q.empty() && q.back().first < new_element)
        q.pop_back();
    q.push_back({new_element,cnt_add});
    cnt_add +=1;
}

void st_push(stack<pair<int,int>> &st, int new_element) {
    int new_min = st.empty() ? new_element : min(new_element, st.top().second);
    st.push({new_element, new_min});
}

vector<int> solve(vector<int> arr, vector<int> queries) {
    vector<int> minima;

    int i;
    for (i = 0; i < queries.size(); i++) {
        int d = queries[i];
        deque<pair<int,int>> q;
        stack<pair<int,int>> maxima;

        // first d elements
        int j;
        for (j=0; j < d; j++) {
            q_push(q, arr[j]);
        }
	//fout << cnt_add << " ";
	//print_queue(q);
        st_push(maxima, q.front().first);

	// remaining elements
        for (j=d; j < arr.size(); j++) {    // risk
            q_push(q, arr[j]);
            if (q.back().second - q.front().second == d) {
                q.pop_front();
            }
	    
	    //fout << cnt_add << " ";
	    //print_queue(q);
            st_push(maxima, q.front().first);
        }
        int min_d = maxima.top().second;
        minima.push_back(min_d);
    }
    return minima;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int q = stoi(first_multiple_input[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<int> queries(q);

    for (int i = 0; i < q; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }
    
    vector<int> result = solve(arr, queries);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
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
