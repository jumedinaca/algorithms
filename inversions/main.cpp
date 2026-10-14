#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


long long brute_force_inversions(vector<int> A);
long long count_inversions(vector<int> &A, int p, int r);
long long merge_count(vector<int> &A, int p, int r, int q);

int comps;

int main(int argc, char **args)
{
    int tries,n,v;
    vector<int> A;

    cin >> tries;
    while(tries > 0)
    {
        cin >> n;
        for(int i = 0; i < n; i++)
        {
            cin >> v;
            A.push_back(v);
        }
        
        // cout << brute_force_inversions(A) << ' ';
        cout << count_inversions(A,0,A.size()) << ' ';
        cout << (n*(n-1))/2 << ' ';
        cout << comps << ' ' << endl;

        comps = 0;
        A.clear();
        tries--;
    }

    return 0;
}

long long brute_force_inversions(vector<int> A)
{
    long long count = 0;
    int n = A.size();
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (A[i] > A[j]) count++;
        }
    }
    return count;
}

long long count_inversions(vector<int> &A, int p, int r){
    if (p + 1 < r)
    {   
        int q      = p+(r-p)/2;
        long long left   = count_inversions(A,p,q);
        long long right  = count_inversions(A,q,r);
        long long merge  = merge_count(A,p,r,q);

        return left + right + merge;
    }
    return 0;
}

long long merge_count(vector<int> &A, int p, int r, int q)
{
    int n_l = q - p;
    int n_r = r - q;

    vector<int> L(n_l);
    vector<int> R(n_r);

    for(int i = 0; i < n_l; i++){ L[i] = A[p + i];}
    for(int i = 0; i < n_r; i++){ R[i] = A[q + i];}

    long long count = 0;
    int k = p, 
    li = 0, 
    ri = 0;

    while(li < n_l && ri < n_r)
    {   
        //Count counts
        comps++;
        if (L[li] <= R[ri])  { A[k++] = L[li++];}
        else                {  A[k++] = R[ri++]; count += ri;}
    }

    while(li < n_l){ A[k++] = L[li++]; }
    while(ri < n_r){ A[k++] = R[ri++]; }

    return count;
}
