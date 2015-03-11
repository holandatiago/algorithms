#include "header.cpp"


ll LCM(int a, int b){    //O(log(b))
    return a*(b/GCD(a,b));
}

ii euclid(int a, int b){    //O(log(b))
    if(!b) return ii(1,0);
    ii p=euclid(b,a%b);
    return ii(p.snd,p.fst-p.snd*(a/b));
}

ii diophantine(int a, int b, int c){    //O(log(b))
    int d=GCD(a,b);
    if(c%d) return ii(0,0);
    ii p=euclid(a,b);
    return ii(p.fst*(c/d),p.snd*(c/d));
}

ll CRT(vii cngr){    //O(log(m))
    ll m=1, ans=0;
    fr(i,0,cngr.size()) m*=cngr[i].snd;
    fr(i,0,cngr.size()){
        int a=cngr[i].fst, n=cngr[i].snd;
        int z=euclid(m/n,n).fst;
        if(z<0) z+=n;
        ans+=a*(m/n)*z;
    }
    return ans%m;
}


struct sieve{
    vb ip;
    vi primes;
    ll nmax=1;
    int size(){return primes.size();}
    ll operator[](int i){return i<size() ? primes[i] : INF;}
    vi up(ll n){    //O(n*log(log(n)))
        if(n>nmax){
            ip.resize(n+1,1);
            for(ll i=2;i<=n;i++) if(ip[i]){
                for(ll j=i*i;j<=n;j+=i) ip[j]=0;
                if(i>nmax) primes.push_back(i);
            }
            nmax=n;
        }
        return primes;
    }
    sieve(ll n=0){ip.resize(2); up(n);}
};
sieve s;

bool isPrime(ll n){    //O(sqrt(n)/ln(sqrt(n)))
    if(n<=s.nmax) return s.ip[n];
    s.up(sqrt(n));
    for(int i=0;s[i]*s[i]<=n;i++) if(!(n%s[i])) return false;
    return true;
}

vii primeFactors(ll n){    //O(sqrt(n)/ln(sqrt(n)))
    vii factors;
    s.up(sqrt(n));
    for(int i=0;s[i]*s[i]<=n;i++){
        if(!(n%s[i])){
            n/=s[i];
            factors.push_back(ii(s[i],1));
        }
        while(!(n%s[i])){
            n/=s[i];
            factors.back().snd++;
        }
    }
    if(n!=1) factors.push_back(ii(n,1));
    return factors;
}

ll sumDiv(ll n){    //O(sqrt(n)/ln(sqrt(n)))
    ll ans=1;
    vii pf = primeFactors(n);
    fr(i,0,pf.size()) ans*=(modExp(pf[i].fst,pf[i].snd+1)-1)/(pf[i].fst-1);
    return ans;
}

ll numCop(ll n){    //O(sqrt(n)/ln(sqrt(n)))
    ll ans=n;
    vii pf = primeFactors(n);
    fr(i,0,pf.size()) ans-=ans/pf[i].fst;
    return ans;
}

vi modfSieve(int n){    //O(n*log(log(n)))
    vi ip(++n);
    fr(i,2,n) if(!ip[i]){
        for(int j=i;j<n;j+=i) ip[j]++;
    }
    return ip;
}

bool carmichael(int n){    //O(sqrt(n)*log(n))
    int prime=1, sr=sqrt(n);
    fr(a,2,n){
        if(!(n%a)) prime=0;
        if(a>sr&&prime) return 0;
        if(a!=modExp(a,n,n)) return 0;
    }
    return !prime;
}


int main(){
    int a, b, c;
    cin>>a>>b>>c;

    vii cngr;
    cngr.push_back(ii(a,3));
    cngr.push_back(ii(b,4));
    cngr.push_back(ii(c,5));

    cout<<"GCD: "<<GCD(a,b)<<endl;
    cout<<"LCM: "<<LCM(a,b)<<endl;
    cout<<"Diophantine: "<<diophantine(a,b,c)<<endl;
    cout<<"CRT: "<<CRT(cngr)<<endl;
    cout<<"Primes: "<<s.up(a)<<endl;
    cout<<"Is it prime? "<<isPrime(a)<<endl;
    cout<<"Prime factors: "<<primeFactors(a)<<endl;
    cout<<"Sum of divisors: "<<sumDiv(a)<<endl;
    cout<<"Number of coprimes: "<<numCop(a)<<endl;
    cout<<"Number of different PFs: "<<modfSieve(a)<<endl;
    cout<<"Is it Carmichael? "<<carmichael(a)<<endl;
}
