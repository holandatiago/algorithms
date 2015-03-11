#include "header.cpp"


struct pt{
    double x, y, z;
    pt(double x=0, double y=0, double z=0): x(x), y(y), z(z) {}
    double norm(){return x*x+y*y+z*z;}
    double operator!(){return sqrt(norm());}
    pt rot(double ang){ang*=PI/180; return pt(x*cos(ang)-y*sin(ang),x*sin(ang)+y*cos(ang));}
    bool inBox(pt mx, pt mn){
        if(cmp(mx.x,mn.x)<0) swap(mx.x,mn.x);
        if(cmp(mx.y,mn.y)<0) swap(mx.y,mn.y);
        return !(cmp(x,mn.x)<0||cmp(x,mx.x)>0||cmp(y,mn.y)<0||cmp(y,mx.y)>0);
    }
};
bool operator==(pt p, pt q){return !cmp(p.x,q.x)&&!cmp(p.y,q.y)&&!cmp(p.z,q.z);}
bool operator<(pt p, pt q){return cmp(p.x,q.x)<0||(!cmp(p.x,q.x)&&cmp(p.y,q.y)<0);}
pt operator+(pt p, pt q){return pt(p.x+q.x,p.y+q.y,p.z+q.z);}
pt operator-(pt p, pt q){return pt(p.x-q.x,p.y-q.y,p.z-q.z);}
pt operator*(pt p, double c){return pt(p.x*c,p.y*c,p.z*c);}
pt operator/(pt p, double c){return pt(p.x/c,p.y/c,p.z/c);}
double operator*(pt p, pt q){return p.x*q.x+p.y*q.y+p.z*q.z;}
double operator%(pt p, pt q){return p.x*q.y-p.y*q.x;}
double angle(pt p, pt q, pt o=pt()){p-=o, q-=o; return acos((p*q)/(!p*!q))*180/PI;}
int ccw(pt p, pt q, pt o){p-=o, q-=o; return cmp(p%q);}
ostream &operator<<(ostream &os, pt p){
    os<<'('<<p.x<<','<<p.y<<')';
    return os;
}


struct line{
    double a, b, c;
    line(double a=0, double b=0, double c=0): a(a), b(b), c(c) {}
    line para(pt p=pt()){return line(a,b,-a*p.x-b*p.y);}
    line perp(pt p=pt()){return line(b,-a,a*p.y-b*p.x);}
    pt inter(line l){return pt((b*l.c-l.b*c)/(l.b*a-b*l.a),(a*l.c-l.a*c)/(l.a*b-a*l.b));}
    bool onLine(pt p){return !cmp(a*p.x+b*p.y+c);}
};
bool operator==(line l1, line l2){return !cmp(l1.a*l2.b,l1.b*l2.a)&&!cmp(l1.a*l2.c,l1.c*l2.a);}
line slope(pt p){return line(p.y,-p.x);}
line toLine(pt p, pt q){return slope(p-q).para(p);}
double dist(pt p, line l){return !(l.perp(p).inter(l)-p);}
pt interPt(pt r1, pt r2, pt s1, pt s2){return toLine(r1,r2).inter(toLine(s1,s2));}
int interSeg(pt r1, pt r2, pt s1, pt s2){
    int a=ccw(r1,r2,s1)*ccw(r1,r2,s1), b=ccw(s1,s2,r1)*ccw(s1,s2,r1);
    if(a==b==0) return -(r1.inBox(s1,s2)||r2.inBox(s1,s2)||s1.inBox(r1,r2)||s2.inBox(r1,r2));
    return a<=0&&b<=0;
}


struct ball{
    double r;
    pt c;
    ball(double r=0, pt c=pt()): r(r), c(c) {}
    double peri(){return 2*PI*r;}
    double area(){return PI*r*r;}
    double arc(double ang){return ang*peri()/360;}
    double chord(double ang){return 2*r*sin(ang*PI/360);}
    double sector(double ang){return ang*area()/360;}
    double segment(double ang){return sector(ang)-r*r*sin(ang*PI/180)/2;}
    double sup(){return 4*PI*r*r;}
    double vol(){return 4*PI*r*r*r/3;}
    double greatCD(pt p, pt q){return r*(sin(p.y)*sin(q.y)+cos(p.y)*cos(q.y)*cos(p.x-q.x));}
};


struct triangle{
    pt p1, p2, p3;
    double l1, l2, l3;
    double a1, a2, a3;
    double P, S, A, SQ, M;
    triangle(pt p1, pt p2, pt p3): p1(p1), p2(p2), p3(p3) {
        l1=!(p2-p3), l2=!(p3-p1), l3=!(p1-p2);
        P=l1+l2+l3; S=P/2; A=sqrt(S*(S-l1)*(S-l2)*(S-l3));
        SQ=(l1*l1+l2*l2+l3*l3)/2; M=l1*l2*l3;
        a1=acos((SQ-l1*l1)*l1/M);
        a2=acos((SQ-l2*l2)*l2/M);
        a3=acos((SQ-l3*l3)*l3/M);
    }
    ball innerCircle(){
        ball circ;
        circ.r=A/S;
        pt p = p2+(p3-p2)*(l3/(l2+l3));
        line s1=toLine(p1,p);
        p = p1+(p3-p1)*(l3/(l1+l3));
        line s2=toLine(p1,p);
        circ.c=s1.inter(s2);
        return circ;
    }
    ball outerCircle(){
        ball circ;
        circ.r=M/(4*A);
        pt p = p2+(p3-p2)/2;
        line s1=toLine(p3,p2).perp(p);
        p = p1+(p3-p1)/2;
        line s2=toLine(p3,p1).perp(p);
        circ.c=s1.inter(s2);
        return circ;
    }
};


struct polygon{
    vector<pt> pl;
    int sz(){return pl.size();}
    polygon(vector<pt> v=vector<pt>()): pl(v) {}
    void operator+=(pt p){pl.push_back(p);}
    void operator--(){pl.pop_back();}
    pt &operator[](int i){return pl[i%sz()];}
    pt last(int i=0){return ts[sz()-1-i];}
    double peri(){    //O(V)
        double peri=0;
        fr(i,0,sz()) peri+=!(ts[i]-ts[i+1]);
        return peri;
    }
    double area(){    //O(V)
        double area=0;
        fr(i,0,sz()) area+=ts[i]%ts[i+1];
        return area/2;
    }
    bool isConvex(bool b=0){    //O(V)
        fr(i,0,sz()){
            int t=ccw(pl[i],pl[i+1],pl[i+2]);
            if(t<0||!(b||t)) return 0;
        }
        return 1;
    }
    bool inPolygon(pt p, bool b=0){    //O(V)
        double sum=0;
        fr(i,0,sz()){
            if(ccw(pl[i],pl[i+1],p)>0) sum+=angle(pl[i],pl[i+1],p);
            else sum-=angle(pl[i],pl[i+1],p);
        }
        return !cmp(sum,360);
    }
    polygon crop(pt p, pt q){    //O(V)
        polygon cut;
        fr(i,0,sz()){
            if(ccw(p,q,pl[i])>=0) cut+=pl[i];
            if(ccw(p,q,pl[i])*ccw(p,q,pl[i+1])>0) cut+=toLine(p,q).inter(toLine(pl[i],pl[i+1]));
        }
        return cut;
    }
};

pt pvt;
bool angCmp(pt a, pt b){
    int t=ccw(pvt,a,b);
    if(t) return t<0?0:1;
    return cmp(!(pvt-a),!(pvt-b))<0;
}
polygon convexHull(vector<pt> pnts){    //O(V*log(V))
    polygon ch;
    swap(pnts[0],*min_element(pnts.begin(),pnts.end()));
    pvt=pnts[0];
    sort(++pnts.begin(),pnts.end(),angCmp);
    ch+=pnts.back();
    ch+=pnts[0];
    fr(i,1,pnts.size()){
        while(ccw(ch.last(1),ch.last(),pnts[i])<=0) --ch;
        ch+=pnts[i];
    }
    --ch;
    return ch;
}


double f(double){}
double bisection(double ans, double hi, double lo){    //O(log(hi-lo))
	double x;
	while(cmp(hi,lo)){
		x=(lo+hi)/2;
		if(f(x)>ans) hi=x;
		else lo=x;
	}
	return x;
}

//Pick(lattice): A=I+B/2-1;


int main(){}
