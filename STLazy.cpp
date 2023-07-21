#include <bits/stdc++.h>
using namespace std;
class ST
{
private:
    vector<int> st, lazy;

public:
    ST(int n)
    {
        st.resize(4 * n);
        lazy.resize(4 * n);
    }
    void build(int ind, int low, int high, int arr[])
    {
        if (low == high)
        {
            st[ind] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        st[ind] = st[2 * ind + 1] + st[2 * ind + 2];
    }
    void updateLazy(int ind, int low, int high, int l, int r, int val){
        // update the previous remaining updates and propogate downwards
        if(lazy[ind]!=0){
            st[ind] += (high - low + 1) * lazy[ind];
            // propogate the lazy update downwards
            // for the remaining nodes to get updated
            if(low!=high){
                lazy[2 * ind + 1]+= lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;

            // no overlap
            //we dont do anything and return
            // low high l r or l r low high
            if(high < l or r< low){
                return;
            }
            // complete overlap
            // l low high r
            // l low  high r
            if(low>=l&&r>=high){
                st[ind] += (high - low + 1) * val;
                // if a non leaf node, it will have children
                if(low!=high){
                    lazy[2 * ind + 1] += val;
                    lazy[2 * ind + 2] += val;
                }
                return;
            }
            // partial overlap
            int mid = (low + high) >> 1;
            updateLazy(2 * ind + 1, low, mid, l, r, val);
            updateLazy(2 * ind + 2, mid + 1, high, l, r, val);
            st[ind] = st[2 * ind + 1] + st[2 * ind + 2];
        }
    }
    int queryLazy(int ind, int low, int high, int l, int r){
        if(lazy[ind]!=0){
            st[ind] += (high - low + 1) * lazy[ind];
            // propogate the lazy update downwards
            // for the remaining nodes to get updated
            if(low!=high){
                lazy[2 * ind + 1]+= lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
        // no overlap 
        if(high < l or r< low){
                return;
            }
            // complete overlap
            // l low high r
            if(low>=l&&r>=high){
                return st[ind];
            }
            int mid = (low + high) >> 1;
            int left = queryLazy(2 * ind + 1, low, mid, l, r);
            int right = queryLazy(2 * ind + 2, mid + 1, high, l, r);
            return left+right;

    }
};