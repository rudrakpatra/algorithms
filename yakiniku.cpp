#include<bits/stdc++.h>
using namespace std;    
using vi = vector<int>;
vector<pair<int,int>> rec_solve(vi&a, vector<vi>&b,int p, int q){
    if(p==q){
        vector<int>temp = b[p];
        vector<pair<int,int>>ans;
        for(auto t: temp){
            ans.push_back({t,p});
        }
        return ans;
    }
    //row p   2 3 4 5 1 2
    //return  {(2,p),(3,p),(4,p),(5,p),(1,p),(2,p)}
    int m=(p+q)/2;
    vector<pair<int,int>>top_ans = rec_solve(a,b,p,m);
    vector<pair<int,int>>bottom_ans = rec_solve(a,b,m+1,q);
    int n=q-p;
    vector<pair<int,int>> ans_crossing;
    int low=n/2, high=(n/2)+1;
    for(int i=0;i<b[0].size();i++){
        if(top_ans[i].first==bottom_ans[i].first){
            ans_crossing.push_back(top_ans[i]);
            if(low>top_ans[i].second || high<bottom_ans[i].second){
                low = top_ans[i].second;
            }
        }
        else if(top_ans[i].first>bottom_ans[i].first){
            ans_crossing.push_back(top_ans[i]);
            if(low>top_ans[i].second){
                low = top_ans[i].second;
            }
        }
        else{
            ans_crossing.push_back(bottom_ans[i]);
            if(high<bottom_ans[i].second){
                high = bottom_ans[i].second;
            }
        }
    }
    int sum=0;
    for(int i=low;i<=high;i++){
        sum+=a[i];
    }
    ans_crossing-=sum;
    int ans_top = 0, ans_bottom = 0;
    for(int i=0;i<m;i++){
        ans_top += top_ans[i].first;
        ans_bottom += bottom_ans[i].first;
    }

    //
    if{ans_crossing,ans_bottom, ans_top});

}

int solve(){
    int n,m;
    cin>>n>>m;
    // vector<int> atop,abottom;
    vector<int>a;
    vector<vector<int>>b;
    // vector<vector<int>>top;
    // vector<vector<int>>bottom;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        a.push_back(x);
        // if(i<(n/2))
        // atop.push_back(x);
        // else
        // abottom.push_back(x);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // if(i<(n/2)){
            //     int x;cin>>x;
            //     top[i].push_back(x);
            // }
            // else{
            //     int x;cin>>x;
            //     bottom[i].push_back(x);
            // }
            int x;
            cin>>x;
            b[i].push_back(x);
        }
    }
    vector<pair<int,int>>top_ans = rec_solve(a,b,0,n/2);
    vector<pair<int,int>>bottom_ans = rec_solve(a,b,(n/2)+1,n-1);
    // vector<pair<int,int>>top_ans = rec_solve(atop,top);
    // vector<pair<int,int>>bottom_ans = rec_solve(abottom,bottom);
    //crossing
    int ans_crossing = 0, low=n/2, high=(n/2)+1;
    for(int i=0;i<m;i++){
        if(top_ans[i].first>bottom_ans[i].first){
            ans_crossing += top_ans[i].first;
            if(low>top_ans[i].second){
                low = top_ans[i].second;
            }
        }
        else{
            ans_crossing += bottom_ans[i].first;
            if(high<bottom_ans[i].second){
                high = bottom_ans[i].second;
            }
        }
    }
    int sum=0;
    for(int i=low;i<=high;i++){
        sum+=a[i];
    }
    ans_crossing-=sum;
    int ans_top = 0, ans_bottom = 0;
    for(int i=0;i<m;i++){
        ans_top += top_ans[i].first;
        ans_bottom += bottom_ans[i].first;
    }
    return max({ans_crossing,ans_bottom, ans_top});
}

int main(){
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
}