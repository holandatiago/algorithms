#include "header.cpp"


ll factorial(int n){    //O(n)
    ll ans=1;
    fr(i,1,n+1) ans=(ans*i)%INF;
    return ans;
}

ll zeros(int n, int f){    //O(log(n))
    ll ans=0, d=f;
    while(d<=n){
        ans+=n/d;
        d*=f;
    }
    return ans;
}

ll fibonacci(int n){    //O(log(n))
    ll a=0, b=1, x=1, y=0, k;
    while(n>0){
        if(n%2){
            k = (a*x)%INF;
            a = (a*y + b*x + k)%INF;
            b = (b*y + k)%INF;
        }
        k = (x*x)%INF;
        x = (2*x*y + k)%INF;
        y = (y*y + k)%INF;
        n/=2;
    }
    return a;
}

vi zeckendorf(int n){    //O(log(n))
    vi v;
    int f1=0, f2=1;
    while(f2<=n){
        f2+=f1;
        f1=f2-f1;
    }
    v.push_back(f1);
    n-=f1;
    while(n>0){
        while(f1>n){
            f1=f2-f1;
            f2-=f1;
        }
        v.push_back(f1);
        n-=f1;
    }
    return v;
}

ll combination(int n, int k){    //O(k)
    ll ans=1;
    if(k>n/2) k=n-k;
    fr(i,1,k+1){
        ans*=n;
        ans/=i;
        n--;
    }
    return ans;
}

ll catalan(int n){    //O(n) - Monotonic paths in n×n grid not passing above the diagonal
    ll ans=combination(2*n,n);
    ans/=n+1;
    return ans;
}

ll eulerian(int n, int k){    //O(n^2) - Permutations of n with k elements greater than the previous
    mll nmbrs(n+1,vll(n+1));
    fr(i,1,n+1){
        nmbrs[i][0]=1;
        nmbrs[i][i-1]=1;
    }
    fr(i,2,n+1){
        fr(j,1,i-1){
            nmbrs[i][j] = (j+1)*nmbrs[i-1][j] + (i-j)*nmbrs[i-1][j-1];
        }
    }
    return nmbrs[n][k];
}

ll stirlingFst(int n, int k){    //O(n^2) - Permutations of n with k cycles
    mll nmbrs(n+1,vll(n+1));
    fr(i,0,n+1){
        nmbrs[i][0]=0;
        nmbrs[i][i]=1;
    }
    fr(i,1,n+1){
        fr(j,1,i){
            nmbrs[i][j] = (i-1)*nmbrs[i-1][j] + nmbrs[i-1][j-1];
        }
    }
    return nmbrs[n][k];
}

ll stirlingSnd(int n, int k){    //O(n^2) - Partition n itens in k sets
    mll nmbrs(n+1,vll(n+1));
    fr(i,0,n+1){
        nmbrs[i][0]=0;
        nmbrs[i][i]=1;
    }
    fr(i,1,n+1){
        fr(j,1,i){
            nmbrs[i][j] = j*nmbrs[i-1][j] + nmbrs[i-1][j-1];
        }
    }
    return nmbrs[n][k];
}

ll intPart(int n, int k){    //O(n^2) - Partition n similar itens in k sets
    mll nmbrs(n+1,vll(n+1));
    fr(i,1,n+1){
        nmbrs[i][1]=1;
        nmbrs[i][i]=1;
    }
    fr(i,1,n+1){
        fr(j,2,i){
            nmbrs[i][j] = nmbrs[i-j][j] + nmbrs[i-1][j-1];
        }
    }
    return nmbrs[n][k];
}

ll josephus(int n, int k){    //O(k*log(n))
    if(n==1) return 0;
    if(k==1) return n-1;
    if(k>n) return (josephus(n-1,k)+k)%n;
    int j=josephus(n-n/k,k)-(n%k);
    if(j<0) j+=n;
    else j+=j/(k-1);
    return j;
}


int main(){
    int n, k;
    cin>>n>>k;

    cout<<"Power: "<<modExp(n,k)<<endl;
    cout<<"Factorial: "<<factorial(n)<<endl;
    cout<<"Trailing zeros: "<<zeros(n,k)<<endl;
    cout<<"Fibonacci: "<<fibonacci(n)<<endl;
    cout<<"Zeckendorf: "<<zeckendorf(n)<<endl;
    cout<<"Combination: "<<combination(n,k)<<endl;
    cout<<"Catalan: "<<catalan(n)<<endl;
    cout<<"Eulerian: "<<eulerian(n,k)<<endl;
    cout<<"Stirling 1st: "<<stirlingFst(n,k)<<endl;
    cout<<"Stirling 2nd: "<<stirlingSnd(n,k)<<endl;
    cout<<"Integer Partitions: "<<intPart(n,k)<<endl;
    cout<<"Josephus: "<<josephus(n,k)<<endl;
}
