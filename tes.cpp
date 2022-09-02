#include "iostream"
using namespace std;
//gcd function
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
void solve(){
    //take n as input for size of an array
    int n;
    cin>>n;
    //take input for array
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    //2,2,6
    int G=a[0];
    //run a loop on the array
    for(int i=0;i<n;i++){
       G=gcd(a[i],G);
    }
    cout<<G*n<<endl;
}
int main(){
    //take t as input for number of test cases
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}