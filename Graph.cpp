#include "header.cpp"


struct edge{
    int from, to, wght;
    edge(int u, int v, int w=0): from(u), to(v), wght(w) {}
};
bool operator>(edge e1, edge e2){return e1.wght>e2.wght;}
bool operator<(edge e1, edge e2){return e1.wght<e2.wght;}
bool operator==(edge e1, edge e2){return (e1.from==e2.from&&e1.to==e2.to)||(e1.from==e2.to&&e1.to==e2.from);}
typedef vector<edge> ve;
typedef vector<ve> me;
ostream &operator<<(ostream &os, edge e){
    os<<e.from<<"->"<<e.to<<'{'<<e.wght<<'}';
    return os;
}

int V, E;
mi AdjMtx;
me AdjLst;
ve EdgeLst;


vi DFS(int s){    //O(V+E)
    int ord=0;
    vi num(V,-1);
    num[s]=ord++;
    stack<ii> stk;
    stk.push(ii(s,0));
    while(!stk.empty()){
        int u=stk.top().fst, k=stk.top().snd;
        stk.pop();
        fr(i,k,AdjLst[u].size()){
            int v=AdjLst[u][i].to;
            if(num[v]<0){
                stk.push(ii(u,i+1));
                num[v]=ord++;
                u=v, i=-1;
            }
        }
    }
    return num;
}

vi BFS(int s){    //O(V+E)
    vi num(V,-1);
    num[s]=0;
    queue<int> que;
    que.push(s);
    while(!que.empty()){
        int u=que.front();
        que.pop();
        fr(i,0,AdjLst[u].size()){
            int v=AdjLst[u][i].to;
            if(num[v]<0){
                que.push(v);
                num[v]=num[u]+1;
            }
        }
    }
    return num;
}

vi topSort(){    //O(V+E)
    vi num(V,0), topsort;
    fr(j,0,V){
        num[j]=1;
        stack<ii> stk;
        stk.push(ii(j,0));
        while(!stk.empty()){
            int u=stk.top().fst, k=stk.top().snd;
            stk.pop();
            fr(i,k,AdjLst[u].size()){
                int v=AdjLst[u][i].to;
                if(!num[v]){
                    stk.push(ii(u,i));
                    num[v]=1;
                    u=v, i=-1;
                }
            }
            topsort.push_back(u);
        }
    }
    return topsort;
}

pair<vb,vector<vb> > APaB(int s){    //O(V+E)
    int ord=0, root=0;
    vi num(V,-1), low(V,-1), par(V,-1);
    vb artPoint(V);
    vector<vb> bridge(V,vb(V));
    num[s]=low[s]=ord++;
    stack<ii> stk;
    stk.push(ii(s,0));
    while(!stk.empty()){
        int u=stk.top().fst, k=stk.top().snd;
        stk.pop();
        fr(i,k,AdjLst[u].size()){
            int v=AdjLst[u][i].to;
            if(num[v]<0){
                if(u==s) root++;
                stk.push(ii(u,i));
                par[v]=u;
                num[v]=low[v]=ord++;
                u=v, i=-1;
            }
            else{
                if(v!=par[u]) low[u]=min(low[u],num[v]);
                if(num[u]<num[v]) low[u]=min(low[u],low[v]);
                if(num[u]<=low[v]) artPoint[u]=1;
                if(num[u]<low[v]) bridge[u][v]=bridge[v][u]=1;
            }
        }
    }
    if(root>1) artPoint[s]=1;
    return pair<vb,vector<vb> >(artPoint,bridge);
}

pair<int,vi> SCC_Tarjan(int s){    //O(V+E)
    int ord=0, nSCC=0;
    vi num(V,-1), low(V,-1), SCC(V,-1);
    stack<int> CC;
    num[s]=low[s]=ord++;
    CC.push(s);
    SCC[s]=0;
    stack<ii> stk;
    stk.push(ii(s,0));
    while(!stk.empty()){
        int u=stk.top().fst, k=stk.top().snd;
        stk.pop();
        fr(i,k,AdjLst[u].size()){
            int v=AdjLst[u][i].to;
            if(num[v]<0){
                stk.push(ii(u,i));
                num[v]=low[v]=ord++;
                CC.push(v);
                SCC[v]=0;
                u=v, i=-1;
            }
            else if(!SCC[v]) low[u]=min(low[u],low[v]);
        }
        if(num[u]==low[u]){
            int v;
            nSCC++;
            do{
                v=CC.top();
                CC.pop();
                SCC[v]=nSCC;
            }while(u!=v);
        }
    }
    return pair<int,vi>(nSCC,SCC);
}


pair<int,ve> MST_Kruskal(){    //O(E*log(V))
    int cost=0;
    ve mst;
    djSet ds(V);
    priority_queue<edge,ve> pq;
    fr(i,0,EdgeLst.size()) pq.push(EdgeLst[i]);
    while(ds.qnt>1){
        edge e=pq.top();
        pq.pop();
        int u=e.from, v=e.to, w=e.wght;
        if(!ds.isSameSet(u,v)){
            cost+=w;
            ds.unionSet(u,v);
            mst.push_back(e);
        }
    }
    return pair<int,ve>(cost,mst);
}

pair<int,ve> MST_Prim(){    //O(E*log(V))
    int cost=0;
    ve mst;
    vi dist(V,INF);
    dist[0]=0;
    priority_queue<edge,ve> pq;
    pq.push(edge(0,0));
    while(!pq.empty()){
        edge e=pq.top();
        int d=e.wght, u=e.to;
        pq.pop();
        if(d==dist[u]){
            cost+=d;
            if(u) mst.push_back(e);
            dist[u]=0;
            fr(i,0,AdjLst[u].size()){
                int v=AdjLst[u][i].to, w=AdjLst[u][i].wght;
                if(w<dist[v]){
                    dist[v]=w;
                    pq.push(edge(u,v,w));
                }
            }
        }
    }
    return pair<int,ve>(cost,mst);
}

pair<int,ve> SndST(){    //O(E*log(V)+V^2)
    int cost=0;
    ve mst, nonmst;
    djSet ds(V);
    priority_queue<edge,ve> pq;
    fr(i,0,EdgeLst.size()) pq.push(EdgeLst[i]);
    while(ds.qnt>1){
        edge e=pq.top();
        pq.pop();
        int u=e.from, v=e.to, w=e.wght;
        if(!ds.isSameSet(u,v)){
            cost+=w;
            ds.unionSet(u,v);
            mst.push_back(e);
        }
        else nonmst.push_back(e);
    }
    while(!pq.empty()){
        nonmst.push_back(pq.top());
        pq.pop();
    }

    me mstAL(V);
    fr(i,0,V-1){
        int u=mst[i].from, v=mst[i].to, w=mst[i].wght;
        mstAL[u].push_back(edge(u,v,i));
        mstAL[v].push_back(edge(v,u,i));
    }

    mi maxw(V,vi(V));
    me maxe(V,ve(V,edge(0,0)));
    fr(s,0,V){
        queue<int> que;
        que.push(s);
        while(!que.empty()){
            int u=que.front();
            que.pop();
            fr(i,0,mstAL[u].size()){
                int v=mstAL[u][i].to, w=mstAL[u][i].wght;
                if(!maxw[s][v]){
                    que.push(v);
                    if(maxw[s][u]>w) maxw[s][v]=maxw[s][u], maxe[s][v]=maxe[s][u];
                    else maxw[s][v]=w, maxe[s][v]=mstAL[u][i];
                }
            }
        }
    }

    int m=0;
    fr(i,0,nonmst.size()){
        int u=nonmst[i].from, v=nonmst[i].to, w=nonmst[i].wght;
        int um=nonmst[m].from, vm=nonmst[m].to, wm=nonmst[m].wght;
        if(w-maxw[u][v]<wm-maxw[um][vm]) m=i;
    }

    int um=nonmst[m].from, vm=nonmst[m].to, wm=nonmst[m].wght;
    fr(i,0,mst.size()) if(mst[i]==maxe[um][vm]) mst[i]=nonmst[m];
    cost+=wm-maxw[um][vm];

    return pair<int,ve>(cost,mst);
}


pair<vi,vi> SSSP_Dijkstra(int s){    //O(E*log(V))
    vi dist(V,INF), p(V,s);
    dist[s]=0;
    priority_queue<edge,ve> pq;
    pq.push(edge(s,s));
    while(!pq.empty()){
        int d=pq.top().wght, u=pq.top().to;
        pq.pop();
        if(d==dist[u]){
            fr(i,0,AdjLst[u].size()){
                int v=AdjLst[u][i].to, w=AdjLst[u][i].wght;
                if(dist[v]>dist[u]+w){
                    dist[v]=dist[u]+w;
                    p[v]=u;
                    pq.push(edge(u,v,dist[v]));
                }
            }
        }
    }
    return pair<vi,vi>(dist,p);
}

pair<vi,vi> SSSP_BellmanFord(int s){    //O(V*E)
    vi dist(V,INF), p(V,s);
    dist[s]=0;
    fr(k,0,V){
        fr(u,0,V){
            fr(i,0,AdjLst[u].size()){
                int v=AdjLst[u][i].to, w=AdjLst[u][i].wght;
                if(dist[v]>dist[u]+w){
                    dist[v]=dist[u]+w;
                    p[v]=u;
                }
            }
        }
    }
    return pair<vi,vi>(dist,p);
}

bool negativeCycle(int s){    //O(V*E)
    vi dist = SSSP_BellmanFord(s).fst;
    fr(u,0,V){
        fr(i,0,AdjLst[u].size()){
            int v=AdjLst[u][i].to, w=AdjLst[u][i].wght;
            if(dist[v]>dist[u]+w) return true;
        }
    }
    return false;
}

pair<mi,mi> APSP_FloydWarshall(){    //O(V^3)
    mi dist(AdjMtx), p(V);
    fr(i,0,V) p[i]=vi(V,i);
    fr(k,0,V){
        fr(i,0,V){
            fr(j,0,V){
                if(dist[i][j]>dist[i][k]+dist[k][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                    p[i][j]=p[k][j];
                }
            }
        }
    }
    return pair<mi,mi>(dist,p);
}


pair<int,ve> MF_EdmondsKarp(int s, int t){    //O(V*E^2)
    int f, maxFlow=0;
    ve minCut;
    vector<vi> res(AdjMtx);
    while(1){
        vi num(V,-1), p(V,-1);
        num[s]=0;
        queue<int> que;
        que.push(s);
        while(!que.empty()){
            int u=que.front();
            que.pop();
            if(u==t) break;
            fr(i,0,AdjLst[u].size()){
                int v=AdjLst[u][i].to;
                if(res[u][v]&&num[v]<0){
                    que.push(v);
                    num[v]=num[u]+1;
                    p[v]=u;
                }
            }
        }
        if(p[t]==-1) break;
        f=INF;
        for(int u=t;u!=s;u=p[u]) f=min(f,res[p[u]][u]);
        for(int u=t;u!=s;u=p[u]) res[p[u]][u]-=f, res[u][p[u]]+=f;
        maxFlow+=f;
    }
    fr(u,0,V){
        fr(i,0,AdjLst[u].size()){
            int v=AdjLst[u][i].to;
            if(!res[u][v]) minCut.push_back(AdjLst[u][i]);
        }
    }
    return pair<int,ve>(maxFlow,minCut);
}

int MCF(int s, int t, int flow){    //O(V^2*E^2)
    int f, cost=0;
    ve minCut;
    vector<vi> res(AdjMtx);
    while(1){
        vi dist(V,INF), p(V,-1);
        dist[s]=0;
        fr(k,0,V){
            fr(u,0,V){
                fr(i,0,AdjLst[u].size()){
                    int v=AdjLst[u][i].to, w=AdjLst[u][i].wght;
                    if(res[u][v]&&dist[v]<dist[u]+w){
                        dist[v]=dist[u]+w;
                        p[v]=u;
                    }
                }
            }
        }
        if(p[t]==-1) break;
        f=flow;
        for(int u=t;u!=s;u=p[u]) f=min(f,res[p[u]][u]);
        for(int u=t;u!=s;u=p[u]) res[p[u]][u]-=f, res[u][p[u]]+=f;
        flow-=f;
    }
    fr(u,0,V){
        fr(i,0,AdjLst[u].size()){
            int v=AdjLst[u][i].to, w=AdjLst[u][i].wght, c=AdjMtx[u][v]-res[u][v];
            if(c>0) cost+=c*w;
        }
    }
    return cost;
}


list<int> cyc;
vector<vb> mark(V,vb(V));
void eulerRec(list<int>::iterator add, int u){
    fr(i,0,AdjLst[u].size()){
        int v=AdjLst[u][i].to;
        if(!mark[u][v]){
            mark[u][v]=mark[v][u]=1;
            eulerRec(cyc.insert(add,u),v);
        }
    }
}
vi eulerTour(int s){    //O(V+E)
    vi v;
    eulerRec(cyc.begin(),s);
    for(list<int>::iterator it=cyc.begin();it!=cyc.end();it++) v.push_back(*it);
    return v;
}

vi match(V,-1);
int augPath(int u){
    if(match[u]) return 0;
    match[u]=1;
    fr(i,0,AdjLst[u].size()){
        int v=AdjLst[u][i].to;
        if(match[v]<0||augPath(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
int MCBM(int l){    //O(V*E)
    int maxm=0;
    fr(i,0,l){
        fr(j,0,l) match[j]=0;
        maxm+=augPath(i);
    }
    return maxm;
}
//MIS = V - MCBM
//MVC = MCBM


//Genius is one percent inspiration, ninety-nine percent perspiration
int main(){
    cin>>V>>E;
    AdjMtx=mi(V,vi(V,INF));
    AdjLst=me(V);
    int s,t,f;
    bool dir;
    cin>>s>>t>>f;
    fr(i,0,E){
        int u,v,w;
        cin>>u>>v>>w;
        AdjMtx[u][v]=w;
        AdjLst[u].push_back(edge(u,v,w));
        EdgeLst.push_back(edge(u,v,w));
        if(!dir){
            AdjMtx[v][u]=w;
            AdjLst[v].push_back(edge(v,u,w));
        }
    }

    cout<<"DFS: "<<DFS(s)<<endl;
    cout<<"BFS: "<<BFS(s)<<endl;
    cout<<"Top Sort: "<<topSort()<<endl;
    cout<<"AP&B: "<<APaB(s)<<endl;
    cout<<"SCC Tarjan: "<<SCC_Tarjan(s)<<endl;
    cout<<"MST Kruskal: "<<MST_Kruskal()<<endl;
    cout<<"MST Prim: "<<MST_Prim()<<endl;
    cout<<"Second ST: "<<SndST()<<endl;
    cout<<"SSSP Dijkstra: "<<SSSP_Dijkstra(s)<<endl;
    cout<<"SSSP Bellman Ford: "<<SSSP_BellmanFord(s)<<endl;
    cout<<"Has negative cycle? "<<negativeCycle(s)<<endl;
    cout<<"APSP Floyd Warshall: "<<APSP_FloydWarshall()<<endl;
    cout<<"MF Edmonds Karp: "<<MF_EdmondsKarp(s,t)<<endl;
    cout<<"MCF: "<<MCF(s,t,f)<<endl;
    cout<<"Euler Tour: "<<eulerTour(s)<<endl;
    cout<<"MCBM: "<<MCBM(s)<<endl;
}
