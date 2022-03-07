#include<iostream>


using namespace std;

int main()
{
    float t0, N0, tn, h, N1n,N2n,N3n,N20,N30;
    int i, n;
    cout<<"Enter Initial Condition"<< endl;
    cout<<"t0 = ";
    cin>> t0;
    cout<<"N0 = ";
    cin >> N0;
    cout<<"Enter calculation point tn = ";
    cin>>tn;
    cout<<"Enter number of steps: ";
    cin>> n;
    cout<<"N20=";
    cin>>N20;
    cout<<"N30=";
    cin>>N30;

    h = (tn-t0)/n;



    for(i=0; i < n; i++)
    {
        N1n = N0-(N0*6*h);
        N0 = N1n;
        N2n = N20+N0*6*h-(6*N20*h);
        N20 =N2n;
        N3n =6*N20*h+N30;
        N30 =N3n;
        t0 = t0+h;
        cout<< N1n<<"\t"<< N2n<<"\t"<<N3n<< endl;
    }


    cout<<"\ntime"<< tn<< "\nn1 " << N1n;
    cout<<"\ntime"<< tn<< "\nn2 " << N2n;
    cout<<"\ntime"<< tn<< "\nn3 " << N3n;
    return 0;
}
