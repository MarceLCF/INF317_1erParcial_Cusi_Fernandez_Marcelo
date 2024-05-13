#include <bits/stdc++.h>
using namespace std;

void suma(int*a, int*b, int*r){
    *r = *a + *b;
}

void resta(int*a, int*b, int*r){
    *r = *a - *b;
}

void multiplicacion(int*a, int*b, int*r){
    *r = 0;
    for(int i=0; i<*b; i++){
        suma(r, a, r);
        //suma(&*r, a, &*r);
    }
}

void division(int*a, int*b, int*r){
    *r = 0;
    while(*a >= *b){
        resta(a,b,a);
        *r += 1;
    }
}

int main(){
    //valores
    int x,y,res;
    cout<<"Introduzca valor x: ";
    cin>>x;
    cout<<"Introduzca valor y: ";
    cin>>y;
    
    //punteros
    int*p1 = &x;
    int*p2 = &y;
    
    suma(p1,p2,&res);
    cout<<"\nSUMA: "<<*p1<<"+"<<*p2<<" = "<<res<<endl<<endl;
    
    resta(p1,p2, &res);
    cout<<"RESTA: "<<*p1<<"-"<<*p2<<" = "<<res<<endl<<endl;
    
    multiplicacion(p1,p2,&res);
    cout<<"MULTIPLICACION: "<<*p1<<"*"<<*p2<<" = "<<res<<endl<<endl;
    
    cout<<"DIVISION: "<<*p1<<"/"<<*p2<<" = ";
    division(p1,p2,&res);
    cout<<res;
}



