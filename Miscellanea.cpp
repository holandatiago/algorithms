#include "header.cpp"


vi countingSort(int k, vi vin, vi stb=vi()){    //O(n+k)
    int n=vin.size();
    vi vout(n), cnt(k);
    fr(i,0,n) cnt[vin[i]]++;
    fr(i,1,k) cnt[i]+=cnt[i-1];
    for(int i=n-1;i>=0;i--){
        vout[cnt[vin[i]]-1]=stb.size()?stb[i]:vin[i];
        cnt[vin[i]]--;
    }
    return vout;
}

vi radixSort(int k, vi v, int b=10){    //O(n*log(k))
    int n=v.size();
    vi dgt(n);
    for(int d=1;d<k;d*=b){
        fr(i,0,n) dgt[i]=(v[i]/d)%b;
        v=countingSort(b,dgt,v);
    }
    return v;
}

bool pntCmp(vi::iterator a, vi::iterator b){return *a<*b;}
vi LIS(vi v){    //O(n*log(n))
    int l;
    vi prnt, last, lis;
    fr(i,0,v.size()){
        int j = lower_bound(last.begin(),last.end(),v.begin()+i,pntCmp)-last.begin();
        prnt[i]=j?last[j-1]:-1;

    }
    return lis;
/*
     L = 0
 for i = 1, 2, ... n:
    binary search for the largest positive j ≤ L
      such that X[M[j]] < X[i] (or set j = 0 if no such value exists)
    P[i] = M[j]
    if j == L or X[i] < X[M[j+1]]:
       M[j+1] = i
       L = max(L, j+1)*/
}


ii cycleFinding(int (*f)(int), int x0){    //O(mu+lambda)
    int mu=0, lambda=1, tortoise = f(x0), hare = f(f(x0));
    while(tortoise!=hare){
        tortoise = f(tortoise);
        hare = f(f(hare));
    }
    hare = tortoise; tortoise = x0;
    while(tortoise!=hare){
        tortoise = f(tortoise);
        hare = f(hare);
        mu++;
    }
    hare = f(tortoise);
    while(tortoise!=hare){
        hare = f(hare);
        lambda++;
    }
    return ii
    (mu,lambda);
}

nim game()

//linear algebra(gaussian elimination)
//matrixmult
//matrix chain

struct segmentTree{
    vi st, A;
    int pwr=1;
    int left(int p){return st[2*p+1];}
    int right(int p){return st[2*(p+1)];}
    segmentTree(vi v): A(v) {    //O(n)
        int n=A.size()-1;
        while(n/=2) pwr++;
        pwr=pow(2,pwr);
        A.resize(pwr,INF);
        st.resize(2*pwr-1);
        fr(i,0,pwr) st[i+pwr-1]=i;
        for(int i=pwr-2;i>=0;i--) st[i] = A[left(i)]<=A[right(i)] ? left(i) : right(i);
    }
    void update(int p, int n){    //O(log(n))
        A[p]=n;
        p+=pwr-1;
        while(p){
            p/=2;
            st[p] = A[left(p)]<=A[right(p)] ? left(p) : right(p);
        }
    }
    int RMQ(int L, int R){    //O(log(n))
        L+=pwr-1, R+=pwr-1;
        int qL=st[L], qR=st[R];
        if(R==L) return A[qL];
        while(L+1<R){
            if(L%2) qL = A[qL]<=A[st[L+1]] ? qL : st[L+1];
            if(R%2-1) qR = A[st[R-1]]<=A[qR] ? st[R-1] : qR;
            L/=2, R/=2;
        }
        return A[qL]<=A[qR] ? qL : qR;
    }
};

struct fenwickTree{
    vi ft;
    int lsb(int p){return p&-p;}
    fenwickTree(int n){ft.resize(n+1);}    //O(n)
    void update(int p, int n){    //O(log(n))
        for(;p<ft.size();p+=lsb(p)) ft[p]+=n;
    }
    int RSQ(int L, int R){    //O(log(n))
        int sum=0;
        for(;R>0;R-=lsb(R)) sum+=ft[R];
        for(L--;L>0;L-=lsb(L)) sum-=ft[L];
        return sum;
    }
};

bool cond(int c){}
void backtrack(int d, int b, int l, vi v){    //<O(b^d)
    if(d==l) cout<<v<<endl;
    fr(i,0,b){
        if(cond(i)){
            v[d]=i;
            backtrack(d+1,b,l,v);
        }
    }
}

bool fstCmp(ii a, ii b){return a.fst<b.fst;}
vi intvCover(vii intv){    //O(n)
    sort(intv.begin(),intv.end(),fstCmp);
    vi cover;
    int t=0, k=0;
    fr(i,0,intv.size()){
        if(intv[i].fst>t){
            cover.push_back(k);
            t=intv[k].snd;
        }
        if(intv[i].snd>intv[k].snd) k=i;
    }
    cover.push_back(k);
    return cover;
}

bool sndCmp(ii a, ii b){return a.snd<b.snd;}
vi intvSchd(vii intv){    //O(n)
    sort(intv.begin(),intv.end(),sndCmp);
    vi schd;
    int k=0;
    schd.push_back(k);
    fr(i,1,intv.size()){
        if(intv[i].fst>intv[k].snd){
            schd.push_back(i);
            k=i;
        }
    }
    return schd;
}

int MRS(vi v){    //O(n)
    int sum=0, ans=0;
    fr(i,0,v.size()){
        sum+=v[i];
        ans=max(ans,sum);
        if(sum<0) sum=0;
    }
    return ans;
}

mi
int rec(int S, int O){
    if(dp[S][O]>=0) return dp[S][O];
    return dp[S][O] = max(obj[O].fst+rec(S-obj[O].snd,O-1),rec(S,O-1));
}

int knapsack(int S, vii obj){

}
//cut sticks
//first
int coinChange(int S, vii obj){

}


int main(){
    int n, k;
    cin>>n>>k;
    vi v(n);
    fr(i,0,n) cin>>v[i];
    string text,word;
    int p=0,m=0;
    while(p!=string::npos){
        p=text.find(word,p);
        m++;
    }
    vector<int>::iterator it;
    it=lower_bound(v.begin(), v.end(), 20);
    vi c=countingSort(k,v); fr(i,0,n) cout<<c[i]<<ends; cout<<endl;
    vi r=radixSort(k,v); fr(i,0,n) cout<<r[i]<<ends; cout<<endl;
    //itvShed(itv);
}
