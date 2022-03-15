#include<iostream>
#include <fstream>


int main()
{
    double t0, N0,N20,N30, tn, h,N1n,N2n,N3n;
    int i;
    N0=10000;
    tn=2;
    t0=0;
    N20=0;
    N30=0;
    int n=20000;
    double marr1[2] [n];
    double marr2[2] [n];
    double marr3[2] [n];
    h = (tn-t0)/n;

    for(i=0; i<n; i++){
        marr1[0] [i]=i*h;
        marr2[0] [i]=i*h;
        marr3[0] [i]=i*h;
    }

    for(i=0; i < n; i++)
    {
        N1n = N0-(N0*6*h);
        marr1[1] [i] =N0;
        N0 = N1n;
        N2n = N20+N0*6*h-(6*N20*h);
        marr2[1] [i] =N20;
        N20 =N2n;
        N3n =6*N20*h+N30;
        marr3[1] [i] =N30;
        N30 =N3n;
        t0 = t0+h;


    }

    ofstream os;
    os.open("data.txt");
    for(int j=0;j<20000;++j){
        os<<marr1[0] [j]<<"\t"<<marr1[1] [j]<<"\r"<<endl;
        }

    os.close();
    os.open("data2.txt");
    for(int j=0;j<20000;++j){
        os<<marr2[0] [j]<<"\t"<<marr2[1] [j]<<"\r"<<endl;
    }

    os.close();
    os.open("data3.txt");
    for(int j=0;j<20000;++j){
        os<<marr3[0] [j]<<"\t"<<marr3[1] [j]<<"\r"<<endl;
    }

    os.close();
    return 0;
}
