#include "header.cpp"


struct bigInt{
    vb v;
    bool sign;
    int base=10;

    int len(){
        while(!v.back()&&!v.empty()) v.pop_back();
        if(v.empty()) sign=false;
        return v.size();
    }
    bigInt(ll n=0){
        ll k=1;
        ts.sign = n<0;
        n=abs(n);
        v.resize(64);
        fr(i,0,64) v[i]=(k<<i)&n;
        len();
    }
    bigInt operator=(ll n){return ts=bigInt(n);}
    vb::reference operator[](int n){return v[n];}
};

bool operator<(bigInt a, bigInt b){
    if(a.sign!=b.sign) return a.sign;
    if(a.len()!=b.len()) return a.sign^(a.len()<b.len());
    for(int i=a.len()-1;i>=0;i--) if(a[i]!=b[i]) return a.sign^(a[i]<b[i]);
    return false;
}
bool operator==(bigInt a, bigInt b){
    if(a.sign!=b.sign) return false;
    if(a.len()!=b.len()) return false;
    for(int i=a.len()-1;i>=0;i--) if(a[i]!=b[i]) return false;
    return true;
}

bigInt operator<<(bigInt a, int b){
    a.v.insert(a.v.begin(),b,false);
    a.len();
    return a;
}
bigInt operator>>(bigInt a, int b){
    b=min(b,a.len());
    a.v.erase(a.v.begin(),a.v.begin()+b);
    a.len();
    return a;
}

bigInt operator!(bigInt n){
    n.sign=false;
    return n;
}
bigInt operator+(bigInt a, bigInt b){    //O(log(a))
    bigInt ans;
    bool c=0;
    int l = max(a.len(),b.len())+1;
    ans.v.resize(l);
    a.v.resize(l);
    b.v.resize(l);
    if(a.sign==b.sign){
        fr(i,0,l){
            ans[i] = (a[i]^b[i])^c;
            c = (a[i]&(b[i]^c))|(b[i]&c);
        }
    } else{
        if(!a<!b) swap(a,b);
        fr(i,0,l){
            ans[i] = (a[i]^b[i])^c;
            c = (!a[i]&(b[i]^c))|(b[i]&c);
        }
    }
    ans.sign=a.sign;
    ans.len();
    return ans;
}
bigInt operator-(bigInt a, bigInt b){    //O(log(a))
    if(b!=0) b.sign=!b.sign;
    return a+b;
}

bigInt operator*(bigInt a, bigInt b){    //O(log^2(a))
    bigInt ans;
    bool s=a.sign^b.sign;
    a.sign=b.sign=false;
    fr(i,0,b.len()){
        if(b[i]) ans+=a;
        a<<=1;
    }
    ans.sign=s;
    ans.len();
    return ans;
}
bigInt operator/(bigInt a, bigInt b){    //O(log^2(a))
    if(b==0) return 0;
    bigInt ans;
    bool s=a.sign^b.sign;
    a.sign=b.sign=false;
    int i;
    for(i=0;b<=a;i++) b<<=1;
    ans.v.resize(i);
    for(;i>0;i--){
        b>>=1;
        if(b<=a){
            a-=b;
            ans[i-1]=1;
        }
    }
    ans.sign=s;
    ans.len();
    return ans;
}
bigInt operator%(bigInt a, bigInt b){    //O(log^2(a))
    if(b==0) return 0;
    bigInt ans;
    bool s=a.sign^b.sign;
    a.sign=b.sign=false;
    int i;
    for(i=0;b<=a;i++) b<<=1;
    for(;i>0;i--){
        b>>=1;
        if(b<=a) a-=b;
    }
    ans.sign=s;
    a.len();
    return a;
}
bigInt operator^(bigInt n, int p){    //O(log(p))
    bigInt ans=1;
    while(p){
        if(p%2) ans*=n;
        n*=n, p/=2;
    }
    return ans;
}

ll btoi(bigInt n){
    ll a=0, k=1;
    n.v.resize(63);
    fr(i,0,63) if(n[i]) a+=(k<<i);
    if(n.sign) a*=-1;
    return a;
}
char toChar(int n){return n<10 ? n+'0' : n-10+'a';}
int toInt(char c){return c<'a' ? c-'0' : c+10-'a';}
istream &operator>>(istream &is, bigInt &n){
    string s;
    is>>s;
    reverse(s.begin(),s.end());
    n=0;
    bigInt p=1;
    fr(i,0,s.size()){
        if(s[i]=='-') n*=-1;
        else{
            n+=toInt(s[i])*p;
            p*=n.base;
        }
    }
    return is;
}
ostream &operator<<(ostream &os, bigInt n){
    stack<char> stk;
    if(n.sign) os<<'-';
    if(!(n.len())) os<<'0';
    while(n!=0){
        stk.push(toChar(btoi(n%n.base)));
        n/=n.base;
    }
    while(!stk.empty()){
        os<<stk.top();
        stk.pop();
    }
    return os;
}


struct rational{
    ll up, lw;
    rational(double a=0, ll b=1): up(a), lw(b) {    //O(log(b))
        while(a!=up) up=a*=10, lw*=10;
        ll d=GCD(up,lw);
        up/=d, lw/=d;
        if(lw<0) up*=-1, lw*=-1;
    }
    rational &operator=(double n){return ts=rational(n);}
    double operator!(){return (double)up/lw;}
};
bool operator<(rational a, rational b){return a.up*b.lw<a.lw*b.up;}
bool operator==(rational a, rational b){return a.up*b.lw==a.lw*b.up;}
rational operator+(rational a, rational b){return rational(a.up*b.lw+a.lw*b.up, a.lw*b.lw);}
rational operator-(rational a, rational b){return rational(a.up*b.lw-a.lw*b.up, a.lw*b.lw);}
rational operator*(rational a, rational b){return rational(a.up*b.up, a.lw*b.lw);}
rational operator/(rational a, rational b){return rational(a.up*b.lw, a.lw*b.up);}
rational operator^(rational n, int p){    //O(log(p))
    rational ans=1;
    while(p){
        if(p%2) ans.up*=n.up, ans.lw*=n.lw;
        n.up*=n.up, n.lw*=n.lw;
        p/=2;
    }
    return ans;
}
istream &operator>>(istream &is, rational &n){
    int k;
    is>>k;
    n=k;
    return is;
}
ostream &operator<<(ostream &os, rational n){
    os<<n.up;
    if(n.lw!=1) os<<'/'<<n.lw;
    return os;
}


struct polynomial{
    int n;
    vector<rational> v;
    rational trsh;
    polynomial(int d=0, rational e=0): v(d+1,e), n(d+1) {}
    int operator!(){return n-1;}
    polynomial operator=(rational r){return ts=polynomial(1,r);}
    rational &operator[](int i){return i>=n ? trsh=0 : v[i];}
    polynomial jus(){    //O(n)
        for(;!v[!ts]&&!ts;n--) v.pop_back();
        return ts;
    }
    rational operator|(rational x){    //O(n)
        rational ans;
        fr(i,0,n) ans=ans*x+v[!ts-i];
        return ans;
    }
};
polynomial operator+(polynomial a, polynomial b){    //O(n)
    polynomial c(max(!a,!b));
    fr(i,0,!c+1) c[i]=a[i]+b[i];
    return c.jus();
}
polynomial operator-(polynomial a, polynomial b){    //O(n)
    polynomial c(max(!a,!b));
    fr(i,0,!c+1) c[i]=a[i]-b[i];
    return c.jus();
}
polynomial operator*(polynomial a, polynomial b){    //O(n^2)
    polynomial c(!a+!b);
    fr(i,0,!a+1)
        fr(j,0,!b+1)
            c[i+j]+=a[i]*b[j];
    return c.jus();
}
polynomial operator&(polynomial a){    //O(n)
    polynomial c(!a-1);
    fr(i,0,!a) c[i]=a[i+1]*(i+1);
    return c.jus();
}
polynomial operator*(polynomial a){    //O(n)
    polynomial c(!a+1);
    fr(i,0,!c) c[i+1]=a[i]/(i+1);
    return c.jus();
}
polynomial operator<<(polynomial a, rational b){    //O(n)
    polynomial c(!a+1,b);
    fr(i,0,!c) c[i+1]=a[i];
    return c.jus();
}
ostream &operator<<(ostream &os, polynomial p){
    for(int i=!p;i>0;i--) os<<p[i]<<"x^"<<i<<" + ";
    os<<p[0];
    return os;
}


int main(){}
