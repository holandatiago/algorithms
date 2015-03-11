#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fr(i,a,b) for(int i=a; i<b; i++)
#define ts (*this)
#define fst first
#define snd second

using namespace std;

typedef vector<int> vi;
typedef vector<vi> mi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> mll;
typedef vector<bool> vb;

const int rx[]={1,0,-1,0,1,-1,-1,1,1}, *ry=rx+1;
const ll INF = 1e9;
const double EPS = 1e-9, PI = acos(-1);

struct djSet{
    vi pset;
    int qnt;
    djSet(int n){pset.resize(n); fr(i,0,n) pset[i]=i; qnt=n;}
    int findSet(int a){return (pset[a]==a)?a:(pset[a]=findSet(pset[a]));}
    bool isSameSet(int a, int b){return findSet(a)==findSet(b);}
    void unionSet(int a, int b){if(!isSameSet(a,b)){pset[findSet(a)]=findSet(b); qnt--;}}
};


template <class T, class U> bool operator>(T a, U b){return !(a<=b);}
template <class T, class U> bool operator!=(T a, U b){return !(a==b);}
template <class T, class U> bool operator<=(T a, U b){return a<b||a==b;}
template <class T, class U> bool operator>=(T a, U b){return a>b||a==b;}
template <class T, class U> T operator<<=(T &a, U b){return a=a<<b;}
template <class T, class U> T operator>>=(T &a, U b){return a=a>>b;}
template <class T, class U> T operator+=(T &a, U b){return a=a+b;}
template <class T, class U> T operator-=(T &a, U b){return a=a-b;}
template <class T, class U> T operator*=(T &a, U b){return a=a*b;}
template <class T, class U> T operator/=(T &a, U b){return a=a/b;}
template <class T, class U> T operator%=(T &a, U b){return a=a%b;}
template <class T, class U> T operator^=(T &a, U b){return a=a^b;}

template <class T>
ostream &operator<<(ostream &os, vector<T> v){
    if(v.size()) os<<v[0];
    fr(i,1,v.size()) os<<' '<<v[i];
    return os;
}

template <class T, class U>
ostream &operator<<(ostream &os, pair<T,U> p){
    os<<p.fst<<','<<p.snd;
    return os;
}

int cmp(double a, double b=0){
    if(fabs(a-b)<EPS) return 0;
    return (a<b)?-1:1;
}

ll modExp(ll n, int p, ll mod=INF){    //O(log(p))
    ll ans=1;
    while(p){
        if(p%2) ans=(ans*n)%mod;
        n=(n*n)%mod;
        p/=2;
    }
    return ans;
}

ll GCD(int a, int b){    //O(log(b))
    while(b){
        a%=b;
        swap(a,b);
    }
    return a;
}


//int main(){}
