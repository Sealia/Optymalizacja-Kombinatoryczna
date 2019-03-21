#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;


int n;
int k;
int nr=1;
int sr1=-1,sr2=-1;
string nazwapliku="1.txt";

template<typename T>
std::string to_string(const T& obj)
{
    std::stringstream ss;
    ss << obj;
    return ss.str();
}

struct przerwa
{
    int czas;
    string id;
    int poczatek;
    int maszyna;
};
struct operacja
{
    int czas,czas_r, czas_z;
    string id;
};

struct zadanie
{

    operacja op1;
    operacja op2;
    int id;
};

struct rozwiazanie
{
    int id;
    vector <zadanie> maszyna1;
    vector <zadanie> maszyna2;
    int czas;
    int czas2;
};

vector<zadanie> zadania;
vector<przerwa> przerwy;
vector <rozwiazanie> populacja;
vector<rozwiazanie> selekcja;

void najlepsze()
{
    int temp, id,id2;
    bool zamiana;
    vector<rozwiazanie>::iterator it;
    vector<rozwiazanie>::iterator it2;
    it=it2=populacja.begin();
    ++it2;
    int cz1,cz2;
    rozwiazanie r,r2,r3;
   // r=new rozwiazanie;

    while(true)
    {
        zamiana=false;
        for(int i=0; i<populacja.size()-1;i++,it++,it++)
        {
            cz1=populacja[i].czas;
               cz2=populacja[i+1].czas;
               id=populacja[i].id;
               id2=populacja[i+1].id;
            if(populacja[i].czas>populacja[i+1].czas)
            {
                zamiana=true;
                r=populacja[i];
                r2=populacja[i+1];
                populacja[i]=r2;
                populacja[i+1]=r;
                cz1=populacja[i].czas;
            cz2=populacja[i+1].czas;
             id=populacja[i].id;
               id2=populacja[i+1].id;
            }
        }
        if(!zamiana)
        {
            break;
        }

    }
    int c=populacja[75].id;
     vector<rozwiazanie>::iterator it5;
        it5=populacja.begin();
        while(it5->id!=c)
        {
            it5++;
        }
        selekcja.assign(populacja.begin(),it5);



}

bool szukaj(vector<zadanie> w, string id)
{
    vector<zadanie>::iterator it;
    for(it=w.begin();it!=w.end();++it)
    {
        if(it->op1.id==id)
        {
            return false;
        }
    }

    return true;
}
bool szukaj2(vector<rozwiazanie> w, int id)
{
    vector<rozwiazanie>::iterator it;
    for(it=w.begin();it!=w.end();++it)
    {
        if(it->id==id)
        {
            return false;
        }
    }

    return true;
}

bool szukaj3(vector<int> w, int id)
{
    vector<int>::iterator it;
    for(it=w.begin();it!=w.end();++it)
    {
        if(*it==id)
        {
            return false;
        }
    }

    return true;
}
void generator_instacji()
{
    n=20;
    zadanie *zad;
    int q=1;
    string o="op";
    for(int i=0;i<n;i++)
    {
        zad = new zadanie;
        zad->id=q;
        zad->op1.id=o + to_string(1) + "_" + to_string(q);
        zad->op2.id=o + to_string(2) + "_" + to_string(q);
        zad->op1.czas=(rand()%20)+1;
        zad->op2.czas=(rand()%20)+1;
        zadania.push_back(*zad);
        q++;

    }

    przerwa *p;
    k=(rand()%9)+n/10;
    int pocz=0;
    int m=1;
    int w=1;
    for(int i=0;i<k;i++)
    {
        p=new przerwa;
        p->id="maint" + to_string(w) + "_M" + to_string(m);
        p->poczatek=rand()%10+pocz;
        p->czas=(rand()%10)+1;

        pocz=p->poczatek+p->czas+rand()%10;
        p->maszyna=m;
        if(m==1)
        {
            m=2;
        }
        else
        {
            m=1;
            w++;
        }
        przerwy.push_back(*p);

    }


}

void wczytaj()
{
    ifstream plik;
    string wiersz;
    plik.open("1.txt");
    if(!plik.good())
    {
        cout<<"nie udalo sie wczytac pliku"<<endl;
    }
    string ile;
    getline(plik,wiersz);
    getline(plik,wiersz);
    getline(plik,ile);
    n=atoi(ile.c_str());
    zadanie *zad;
    przerwa *p;
    int m=1;
    int q=1;
    int w=1;
    getline(plik,wiersz);
    cout<<"rozmiar: "<<n<<endl;
    while(getline(plik,wiersz,' '))
    {
        if(zadania.size()==n)
        {

            k=atoi(wiersz.c_str());
            while(getline(plik,wiersz,' '))
            {
                vector<string> temp;
                p=new przerwa;
                temp.push_back(wiersz);
                getline(plik,wiersz,' ');
                temp.push_back(wiersz);
                p->id="maint" + to_string(w) + "_M" + to_string(m);
                p->poczatek=atoi(temp[0].c_str());
                p->czas=atoi(temp[1].c_str());
                p->maszyna=m;
                if(m==1)
                {
                    m=2;
                }
                else
                {
                    m=1;
                    w++;
                }

                przerwy.push_back(*p);
                temp.clear();
            }
            break;

        }
        vector<string> temp;
        temp.push_back(wiersz);
        getline(plik,wiersz,' ');
        temp.push_back(wiersz);
        zad = new zadanie;
        zad->id=q;
        zad->op1.id="op" + to_string(1) + "_" + to_string(q);
        zad->op2.id="op" + to_string(2) + "_" + to_string(q);
        zad->op1.czas=atoi(temp[0].c_str());
        zad->op2.czas=atoi(temp[1].c_str());
        zadania.push_back(*zad);
        q++;
        temp.clear();

    }
    plik.close();

     vector<zadanie>::iterator it;
        for(it=zadania.begin();it!=zadania.end();++it)
        {
            cout<<it->op1.id<<": "<<it->op1.czas<<"\t"<<it->op2.id<<": "<<it->op2.czas<<endl;
        }

        cout<<"k: "<<k<<endl;
        vector<przerwa>::iterator it2;
        for(it2=przerwy.begin();it2!=przerwy.end();++it2)
        {
            cout<<it2->id<<"\t"<<"poczatek:" <<it2->poczatek<<"\t"<<"czas:"<<it2->czas<<"\t"<<"maszyna: "<<it2->maszyna<<endl;
        }
}

void instancja()
{
    fstream plik;
    string nazwa;
    nazwa=to_string(16)+".txt";
    plik.open(nazwa,ios::out);
    nr+=1;
    if(!plik.good())
    {
        cout<<"nie udalo sie wcyztac pliku"<<endl<<endl;
    }
    plik<<n<<endl<<" "<<endl;

    vector<zadanie>::iterator it;
    for(it=zadania.begin();it!=zadania.end();++it)
    {
        plik<<it->op1.czas<<" "<<it->op2.czas<<" "<<endl;
    }
    plik<<endl<<k<<endl<<" "<<endl;;
    vector<przerwa>::iterator it2;
    for(it2=przerwy.begin();it2!=przerwy.end();++it2)
        {
            plik<<it2->poczatek<<" "<<it2->czas<<" ";
            if(it2!=przerwy.end()-1)
            {
                plik<<endl;
            }

        }
     plik.close();
     zadania.clear();
     przerwy.clear();

}
int czy_przerwa(int czas2,int cz,vector<zadanie> tempz2, vector<przerwa> tempp)
{
    int pom=-1;
    for(int i=0; i<tempp.size();i++)
    {

        if(cz>=tempp[i].poczatek && tempp[i].maszyna==2 && czas2<=tempp[i].poczatek)
        {
            pom=i;
            return pom;
        }
    }
    if(pom==-1)
    {
         return -1;
    }

}

void rozwiazanie_losowe()
{
    rozwiazanie *r;
    int licznik=0;
    int c=-1;
    bool dobrze=false;
    vector <zadanie> maszyna1;
    vector <zadanie> maszyna2;
    vector <zadanie> tempz1;
    vector <zadanie> tempz2;
    vector <przerwa> tempp;
    int czas=0,czas2=0, losowe=0,d=0;
    bool ok=true,ok2=true;
    int pom=NULL,pom2=-1;
    vector<zadanie>::iterator it;
    while(licznik!=400)
    {

    tempz1.assign(zadania.begin(),zadania.end());
    tempz2.assign(zadania.begin(),zadania.end());
    tempp.assign(przerwy.begin(), przerwy.end());


        while(!tempz1.empty())
        {
            losowe =(rand()%tempz1.size())+0;
            if(!tempp.empty())
            {
                 for(int i=0; i<tempp.size();i++)
                {
                    if(tempz1[losowe].op1.czas+czas>tempp[i].poczatek && tempp[i].maszyna==1 &&  czas==tempp[i].poczatek)
                        {
                            czas+=tempp[i].czas;
                        }
                    if(tempz1[losowe].op1.czas+czas>tempp[i].poczatek && tempp[i].maszyna==1 && czas<tempp[i].poczatek)
                    {
                        ok=false;
                        pom=i;
                        break;
                    }
                }

            }
            if(ok==true)
            {
                maszyna1.push_back(tempz1[losowe]);
                maszyna1.back().op1.czas_r=czas;
                czas+=tempz1[losowe].op1.czas;
                maszyna1.back().op1.czas_z=czas;
                tempz1.erase(tempz1.begin()+losowe);

            }

            else
            {
                maszyna1.push_back(tempz1[losowe]);
                maszyna1.back().op1.czas_r=czas;
                czas+=ceil(1.2*tempz1[losowe].op1.czas)+tempp[pom].czas;
                maszyna1.back().op1.czas_z=czas;
                tempz1.erase(tempz1.begin()+losowe);
                tempp.erase(tempp.begin()+pom);


            }

            ok=true;
            pom=-1;
        }

    czas2=0;
    pom=-1;
    ok=true;
    for(int i=0; i<maszyna1.size();i++)
    {
        losowe =(rand()%maszyna1.size())+0;
        if(maszyna2.empty())
        {
            losowe=0;
            czas2=maszyna1[losowe].op1.czas_z;
        }
        else
        {


       int f=-1;
        for(int z=0;z<maszyna1.size();z++)
        {
            if(maszyna1[z].op1.czas_z<=czas2 && szukaj(maszyna2,maszyna1[z].op1.id))
            {
                losowe=z;
                break;
            }
            if(z==maszyna1.size()-1)
            {
                for(int o=0;o<maszyna1.size();o++)
                {
                    c=czy_przerwa(czas2,maszyna1[o].op2.czas+maszyna1[o].op1.czas_z,maszyna1,tempp);
                    if(maszyna1[o].op1.czas_z>czas2 && maszyna1[o].op1.czas_r<czas2 && szukaj(maszyna2,maszyna1[o].op1.id))
                    {
                        if(c==-1 && szukaj(maszyna2,maszyna1[o].op1.id))
                        {
                            czas2=maszyna1[o].op1.czas_z;
                            dobrze=true;

                            losowe=o;
                        }
                        else if(c>=0 && szukaj(maszyna2,maszyna1[o].op1.id))
                        {


                            if(maszyna1[o].op1.czas_z<tempp[c].poczatek && szukaj(maszyna2,maszyna1[o].op1.id))
                           {
                               czas2=maszyna1[o].op1.czas_z;
                               dobrze=true;
                           }

                           else if( szukaj(maszyna2,maszyna1[o].op1.id))
                           {
                               if(tempp[c].poczatek+tempp[c].czas>maszyna1[o].op1.czas_z && szukaj(maszyna2,maszyna1[o].op1.id))
                               {
                                   czas2=tempp[c].poczatek+tempp[c].czas;
                                   dobrze=true;
                               }
                               else if( szukaj(maszyna2,maszyna1[o].op1.id))
                               {
                                   czas2=maszyna1[o].op1.czas_z;
                                   dobrze=true;
                               }

                           }

                            losowe=o;

                        }

                        break;
                    }

                    else if(dobrze==false && o==maszyna1.size()-1 )
                        {

                            int zap=200;
                            int bld=-1;
                            for(int y=0;y<maszyna1.size();y++)
                            {
                                if(maszyna1[y].op1.czas_z-czas2<zap && maszyna1[y].op1.czas_z-czas2>0)
                                {
                                    zap=maszyna1[y].op1.czas_z-czas2;
                                    bld=y;

                                }
                            }
                            czas2=maszyna1[bld].op1.czas_z;
                            z=-1;
                            dobrze=false;
                        }
                }
            }
             if(z==maszyna1.size()-1)
             {
                 break;
                  c=-1;
             }

        }


        }

        for(int j=0; j<tempp.size();j++)
        {
            if(maszyna1[losowe].op2.czas+czas2>tempp[j].poczatek && tempp[j].maszyna==2 &&  czas2==tempp[j].poczatek)
                {
                    czas2+=tempp[j].czas;
                }
            if(maszyna1[losowe].op2.czas+czas2>tempp[j].poczatek && tempp[j].maszyna==2 && czas2<tempp[j].poczatek)
                {
                    ok=false;
                    pom=j;
                    break;
                }
        }


        if(ok==true)
        {
            maszyna2.push_back(maszyna1[losowe]);
            maszyna2.back().op2.czas_r=czas2;
            czas2+=maszyna2.back().op2.czas;
            maszyna2.back().op2.czas_z=czas2;

        }
        else
        {
            maszyna2.push_back(maszyna1[losowe]);
            maszyna2.back().op2.czas_r=czas2;
            czas2+=ceil(1.2*maszyna2.back().op2.czas)+tempp[pom].czas;
            maszyna2.back().op2.czas_z=czas2;

        }
        ok=true;
        dobrze=false;


    }


       r=new rozwiazanie;
        r->id=d;
        d+=1;
        r->maszyna1.assign(maszyna1.begin(),maszyna1.end());
        r->maszyna2.assign(maszyna2.begin(),maszyna2.end());
        r->czas=(czas>czas2 ? czas:czas2);
        populacja.push_back(*r);
        maszyna1.clear();
        maszyna2.clear();
        licznik+=1;
        czas=0,czas2=0, losowe=0;
    }

}


void genetyczny()
{
    time_t start;
    vector<zadanie>::iterator t;
    time_t stop;
    int czas=0,a=0;
    time(&start);
    time(&stop);
    vector<int> indeksy1,indeksy2;
    vector<int>::iterator it2;
    vector<zadanie>::iterator it;
    rozwiazanie *r;
    int losowe,losowe2,licznik=0,in,id=populacja.back().id+1,pom=-1,l=0;
    bool ok=true;
     najlepsze();
        vector<rozwiazanie>::iterator s;
        int sr=0;
        for(s=populacja.begin();s!=populacja.end();++s)
        {
            sr+=s->czas;
        }
        sr1=round(sr/populacja.size());
    bool dobrze=false;
    while(difftime(stop,start)<40)
    {
        licznik=0;

        while(selekcja.size()<100)
        {
            losowe =(rand()%populacja.size())+0;
            if(szukaj2(selekcja,populacja[losowe].id))
            {
                selekcja.push_back(populacja[losowe]);
            }

        }


        while(licznik<100)
        {

            losowe =(rand()%99)+0;
            czas=0;
            it=selekcja[losowe].maszyna1.begin();

            losowe2 =(rand()%99)+0;
            while(selekcja[losowe2].id==selekcja[losowe].id)
            {
                 losowe2 =(rand()%99)+0;
            }


            for(int i=0; i<(zadania.size())/2;)
            {
                in =(rand()%zadania.size())+0;
                if(szukaj3(indeksy1,in))
                {
                    indeksy1.push_back(in);
                    i++;
                }

            }


            sort(indeksy1.begin(),indeksy1.end());
            for(int i=0;i<indeksy1.size();i++)
            {
                for(int j=0; j<zadania.size();j++)
                {
                    if(selekcja[losowe].maszyna1[indeksy1[i]].id==selekcja[losowe2].maszyna1[j].id)
                    {
                        indeksy2.push_back(j);
                    }
                }
            }
            r=new rozwiazanie;
            r->id=id;
            for(int i=0;i<zadania.size();i++)
            {
                if(szukaj3(indeksy2,i))
                {
                    r->maszyna1.push_back(selekcja[losowe2].maszyna1[i]);
                    for(int j=0; j<przerwy.size();j++)
                    {
                        if(r->maszyna1.back().op1.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==1 &&  czas==przerwy[j].poczatek)
                        {
                            czas+=przerwy[j].czas;
                        }
                        if(r->maszyna1.back().op1.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==1 && czas<przerwy[j].poczatek)
                        {
                            ok=false;
                            pom=j;
                            break;
                        }

                    }

                    r->maszyna1.back().op1.czas_r=czas;


                    if(ok==true)
                    {
                        czas+=r->maszyna1.back().op1.czas;
                    }
                    else
                    {
                        czas+=ceil(1.2*r->maszyna1.back().op1.czas)+przerwy[pom].czas;

                    }
                    r->maszyna1.back().op1.czas_z=czas;

                }


                else
                {
                    r->maszyna1.push_back(selekcja[losowe].maszyna1[indeksy1[a]]);
                    a++;
                    for(int j=0; j<przerwy.size();j++)
                    {
                        if(r->maszyna1.back().op1.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==1 &&  czas==przerwy[j].poczatek)
                        {
                            czas+=przerwy[j].czas;
                        }
                        if(r->maszyna1.back().op1.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==1 && czas<przerwy[j].poczatek)
                        {
                            ok=false;
                            pom=j;
                            break;
                        }

                    }

                    r->maszyna1.back().op1.czas_r=czas;


                    if(ok==true)
                    {
                        czas+=r->maszyna1.back().op1.czas;
                    }
                    else
                    {
                        czas+=ceil(1.2*r->maszyna1.back().op1.czas)+przerwy[pom].czas;

                    }
                    r->maszyna1.back().op1.czas_z=czas;
                }
                ok=true;
            }


            czas=0;
            ok=true;
            pom=0;

          //  wstaw_na_2(r->id);


czas=0;
int c=-1;


    for(int i=0; i<r->maszyna1.size();i++)
    {
        losowe =(rand()%r->maszyna1.size())+0;
        if(r->maszyna2.empty())
        {
            losowe=0;
            czas=r->maszyna1[losowe].op1.czas_z;
        }
        else
        {

        for(int z=0;z<r->maszyna1.size();z++)
        {
            if(r->maszyna1[z].op1.czas_z<=czas && szukaj(r->maszyna2,r->maszyna1[z].op1.id))
            {
                losowe=z;
                break;
            }
            if(z==r->maszyna1.size()-1)
            {
                for(int o=0;o<r->maszyna1.size();o++)
                {
                    c=czy_przerwa(czas,r->maszyna1[o].op2.czas+r->maszyna1[o].op1.czas_z,r->maszyna1,przerwy);
                    if(r->maszyna1[o].op1.czas_z>czas && r->maszyna1[o].op1.czas_r<czas && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                    {
                        if(c==-1 && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                        {
                            czas=r->maszyna1[o].op1.czas_z;
                            dobrze=true;
                            losowe=o;
                        }
                        else if(c>=0 && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                        {


                            if(r->maszyna1[o].op1.czas_z<przerwy[c].poczatek && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                           {
                               czas=r->maszyna1[o].op1.czas_z;
                               dobrze=true;

                           }

                           else if( szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                           {
                               int w=r->maszyna1[o].op1.czas_z;
                               if(przerwy[c].poczatek+przerwy[c].czas>r->maszyna1[o].op1.czas_z && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                               {
                                   czas=przerwy[c].poczatek+przerwy[c].czas;
                                   dobrze=true;
                               }
                               else if( szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                               {
                                   czas=r->maszyna1[o].op1.czas_z;
                                   dobrze=true;

                               }

                           }

                            losowe=o;

                        }

                        break;
                    }
                    else if(dobrze==false && o==r->maszyna1.size()-1 )
                        {

                            int zap=200;
                            int bld=-1;
                            for(int y=0;y<r->maszyna1.size();y++)
                            {
                                if(r->maszyna1[y].op1.czas_z-czas<zap && r->maszyna1[y].op1.czas_z-czas>0)
                                {
                                    zap=r->maszyna1[y].op1.czas_z-czas;
                                    bld=y;
                                }
                            }
                            czas=r->maszyna1[bld].op1.czas_z;
                            z=-1;
                            dobrze=false;
                        }
                }
            }
             if(z==r->maszyna1.size()-1)
             {
                 break;
                  c=-1;
             }

        }


        }
        l=0;

        for(int j=0; j<przerwy.size();j++)
        {
            if(r->maszyna1[losowe].op2.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==2 &&  czas==przerwy[j].poczatek)
                {
                    czas+=przerwy[j].czas;
                }
            if(r->maszyna1[losowe].op2.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==2 && czas<przerwy[j].poczatek)
                {
                    ok=false;
                    pom=j;
                    break;
                }
        }


        if(ok==true)
        {
            r->maszyna2.push_back(r->maszyna1[losowe]);
            r->maszyna2.back().op2.czas_r=czas;
            czas+=r->maszyna2.back().op2.czas;
        r->maszyna2.back().op2.czas_z=czas;
          //  temp.erase(temp.begin()+losowe);
        }
        else
        {
            r->maszyna2.push_back(r->maszyna1[losowe]);
            r->maszyna2.back().op2.czas_r=czas;
            czas+=ceil(1.2*r->maszyna2.back().op2.czas)+przerwy[pom].czas;
            r->maszyna2.back().op2.czas_z=czas;
         //   temp.erase(temp.begin()+losowe);

        }
        ok=true;
        dobrze=false;

    }









            id++;
            a=0;
            r->czas=(r->maszyna1.back().op1.czas_z>r->maszyna2.back().op2.czas_z ?r->maszyna1.back().op1.czas_z:r->maszyna2.back().op2.czas_z);
            selekcja.push_back(*r);
        //    selekcja.back().czas=(selekcja.back().maszyna1.back().op1.czas_z>selekcja.back().maszyna2.back().op2.czas_z ?selekcja.back().maszyna1.back().op1.czas_z:selekcja.back().maszyna2.back().op2.czas_z);
            indeksy1.clear();
            indeksy2.clear();
            licznik+=1;


        }



            //MUTACJE

            for(int i=0;i<0.1*(populacja.size()-1);i++)
            {
                r = new rozwiazanie;
                r->id=id;
                id++;

                losowe =(rand()%selekcja.size())+0;
                losowe2=(rand()%selekcja[losowe].maszyna1.size())+0;
                int losowe3=(rand()%selekcja[losowe].maszyna1.size())+0;
                while(losowe2==losowe3)
                {
                    losowe3=(rand()%selekcja[losowe].maszyna1.size())+0;
                }

                r->maszyna1.assign(selekcja[losowe].maszyna1.begin(),selekcja[losowe].maszyna1.end());
                r->maszyna1[losowe2]=selekcja[losowe].maszyna1[losowe3];
                r->maszyna1[losowe3]=selekcja[losowe].maszyna1[losowe2];

                int temp=losowe2<losowe3?losowe2:losowe3;
                if(temp==0)
                {
                    czas=0;
                }
                else
                {
                     czas=selekcja[losowe].maszyna1[temp-1].op1.czas_z;
                }

                for(int i=temp; i<selekcja[losowe].maszyna1.size();i++)
                {

                    for(int j=0; j<przerwy.size();j++)
                    {
                        if(r->maszyna1[i].op1.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==1 &&  czas==przerwy[j].poczatek)
                        {
                            czas+=przerwy[j].czas;
                        }

                        if(r->maszyna1[i].op1.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==1 && czas<przerwy[j].poczatek)
                        {
                            ok=false;
                            pom=j;
                            break;
                        }

                    }
                    if(ok==true)
                    {
                        r->maszyna1[i].op1.czas_r=czas;
                        czas+=r->maszyna1[i].op1.czas;
                        r->maszyna1[i].op1.czas_z=czas;
                    }

                    else
                    {
                        r->maszyna1[i].op1.czas_r=czas;
                        czas+=ceil(1.2*r->maszyna1[i].op1.czas)+przerwy[pom].czas;
                        r->maszyna1[i].op1.czas_z=czas;
                    }

                    ok=true;

                }


    czas=0;
    l=0;
    pom=-1;
    ok=true;
    dobrze=false;
    int  c=-1;
    for(int i=0; i<r->maszyna1.size();i++)
    {
        losowe =(rand()%r->maszyna1.size())+0;
        if(r->maszyna2.empty())
        {
            losowe=0;
            czas=r->maszyna1[losowe].op1.czas_z;
        }
        else
        {

        for(int z=0;z<r->maszyna1.size();z++)
        {
            if(r->maszyna1[z].op1.czas_z<=czas && szukaj(r->maszyna2,r->maszyna1[z].op1.id))
            {
                losowe=z;
                break;
            }
            if(z==r->maszyna1.size()-1)
            {
                for(int o=0;o<r->maszyna1.size();o++)
                {
                    c=czy_przerwa(czas,r->maszyna1[o].op2.czas+r->maszyna1[o].op1.czas_z,r->maszyna1,przerwy);
                    if(r->maszyna1[o].op1.czas_z>czas && r->maszyna1[o].op1.czas_r<czas && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                    {
                        if(c==-1 && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                        {
                            czas=r->maszyna1[o].op1.czas_z;
                            dobrze=true;
                            losowe=o;
                        }
                        else if(c>=0 && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                        {


                            if(r->maszyna1[o].op1.czas_z<przerwy[c].poczatek && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                           {
                               czas=r->maszyna1[o].op1.czas_z;
                               dobrze=true;
                           }

                           else
                           {
                               int w=r->maszyna1[o].op1.czas_z;
                               if(przerwy[c].poczatek+przerwy[c].czas>r->maszyna1[o].op1.czas_z && szukaj(r->maszyna2,r->maszyna1[o].op1.id))
                               {
                                   czas=przerwy[c].poczatek+przerwy[c].czas;
                                   dobrze=true;
                               }
                               else
                               {
                                   czas=r->maszyna1[o].op1.czas_z;
                                   dobrze=true;
                               }

                           }

                            losowe=o;

                        }

                        break;
                    }
                        else if(dobrze==false && o==r->maszyna1.size()-1 )
                        {

                            int zap=200;
                            int bld=-1;
                            for(int y=0;y<r->maszyna1.size();y++)
                            {
                                if(r->maszyna1[y].op1.czas_z-czas<zap && r->maszyna1[y].op1.czas_z-czas>0)
                                {
                                    zap=r->maszyna1[y].op1.czas_z-czas;
                                    bld=y;
                                }
                            }
                            czas=r->maszyna1[bld].op1.czas_z;
                            z=-1;
                            dobrze=false;
                        }
                }
            }
             if(z==r->maszyna1.size()-1)
             {
                 break;
                  c=-1;
             }

        }


        }
        l=0;

        for(int j=0; j<przerwy.size();j++)
        {
            if(r->maszyna1[losowe].op2.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==2 &&  czas==przerwy[j].poczatek)
                {
                    czas+=przerwy[j].czas;
                }
            if(r->maszyna1[losowe].op2.czas+czas>przerwy[j].poczatek && przerwy[j].maszyna==2 && czas<przerwy[j].poczatek)
                {
                    ok=false;
                    pom=j;
                    break;
                }
        }


        if(ok==true)
        {
            r->maszyna2.push_back(r->maszyna1[losowe]);
            r->maszyna2.back().op2.czas_r=czas;
            czas+=r->maszyna2.back().op2.czas;
            r->maszyna2.back().op2.czas_z=czas;
          //  temp.erase(temp.begin()+losowe);
        }
        else
        {
            r->maszyna2.push_back(r->maszyna1[losowe]);
            r->maszyna2.back().op2.czas_r=czas;
            czas+=ceil(1.2*r->maszyna2.back().op2.czas)+przerwy[pom].czas;
            r->maszyna2.back().op2.czas_z=czas;
         //   temp.erase(temp.begin()+losowe);

        }
        ok=true;

    }

r->czas=(r->maszyna1.back().op1.czas_z>r->maszyna2.back().op2.czas_z ?r->maszyna1.back().op1.czas_z:r->maszyna2.back().op2.czas_z);
            selekcja.push_back(*r);



            }

        populacja.clear();
        populacja.assign(selekcja.begin(),selekcja.end());
        najlepsze();
        populacja.erase(populacja.begin()+200,populacja.end());
        selekcja.clear();

        vector<rozwiazanie>::iterator it;






       time(&stop);
    /*   int u=difftime(stop,start);
       if(u>e)
       {
           cout<<u<<" - "<<sr2<<endl;
       }*/
               int sr=0;
        for(s=populacja.begin();s!=populacja.end();++s)
        {
            sr+=s->czas;
        }
        sr2=round(sr/populacja.size());
        cout<<difftime(stop, start)<<" - "<<sr2<<endl;

    }

}

void zapisz()
{
    nr=1;
    int r=1;
    int w=1;
    fstream plik;
            int l=0;
        int sum=0;

    vector<rozwiazanie>::iterator it;
    for(it=populacja.begin();it!=populacja.end();++it)
    {
        string nazwa=to_string(nr)+"_"+to_string(r)+".txt";
    plik.open(nazwa,ios::out);
    if(!plik.good())
    {
        cout<<"nie udalo sie wczytac pliku"<<endl<<endl;
    }
        plik<<"*** "<<to_string(nr)+"_"+to_string(r)<<" ***"<<endl;
        r++;
        plik<<sr2<<","<<sr1<<endl;
        vector<zadanie>::iterator it2;
        int czas=0;

        plik<<"M1:";
        for(int j=0; j<it->maszyna1.size();j++)
        {
            if(it->maszyna1[j].op1.czas!=it->maszyna1[j].op1.czas_z-it->maszyna1[j].op1.czas_r)
            {
                for(int i=0;i<przerwy.size();i++)
                {
                    if(przerwy[i].poczatek>it->maszyna1[j].op1.czas_r && przerwy[i].czas+przerwy[i].poczatek<it->maszyna1[j].op1.czas_z && przerwy[i].maszyna==1)
                    {
                        plik<<it->maszyna1[j].op1.id<<","<<it->maszyna1[j].op1.czas_r<<","<<it->maszyna1[j].op1.czas<<","<<it->maszyna1[j].op1.czas_z-it->maszyna1[j].op1.czas_r<<";"<<przerwy[i].id<<","<<przerwy[i].poczatek<<","<<przerwy[i].czas<<";";

                    }
                }
                czas=it->maszyna1[j].op1.czas_z;
            }
            else if(czas!=it->maszyna1[j].op1.czas_r)
            {
                bool ok=false;
                for(int i=0;i<przerwy.size();i++)
                {
                    if(przerwy[i].poczatek==czas && przerwy[i].czas+przerwy[i].poczatek<=it->maszyna1[j].op1.czas_z && przerwy[i].maszyna==1)
                    {
                        plik<<przerwy[i].id<<","<<przerwy[i].poczatek<<","<<przerwy[i].czas<<";";
                        j-=1;
                        ok=true;
                        czas+=przerwy[i].czas;
                    }
                }
                if(ok==false)
                {

                    plik<<"idle"<<w<<"M1,"<<czas<<","<<it->maszyna1[j+1].op1.czas-czas<<";";
                    czas=it->maszyna1[j+1].op1.czas_r;
                    j-=1;
                    w++;
                }
            }
            else if(it->maszyna1[j].op1.czas_r==czas)
            {
                 plik<<it->maszyna1[j].op1.id<<","<<it->maszyna1[j].op1.czas_r<<","<<it->maszyna1[j].op1.czas<<";";
                 czas+=it->maszyna1[j].op1.czas;
            }

        }

        czas=it->maszyna2[0].op2.czas_r;
        w=0;
        plik<<endl;
        plik<<"M2:";
        for(int j=0; j<it->maszyna2.size();j++)
        {
            if(it->maszyna2[j].op2.czas!=it->maszyna2[j].op2.czas_z-it->maszyna2[j].op2.czas_r)
            {
                for(int i=0;i<przerwy.size();i++)
                {
                    if(przerwy[i].poczatek>it->maszyna2[j].op2.czas_r && przerwy[i].czas+przerwy[i].poczatek<it->maszyna2[j].op2.czas_z && przerwy[i].maszyna==2)
                    {
                        plik<<it->maszyna2[j].op2.id<<","<<it->maszyna2[j].op2.czas_r<<","<<it->maszyna2[j].op2.czas<<","<<it->maszyna2[j].op2.czas_z-it->maszyna2[j].op2.czas_r<<";"<<przerwy[i].id<<","<<przerwy[i].poczatek<<","<<przerwy[i].czas<<";";

                    }
                }
                czas=it->maszyna2[j].op2.czas_z;
            }
            else if(czas!=it->maszyna2[j].op2.czas_r)
            {
                bool ok=false;
                for(int i=0;i<przerwy.size();i++)
                {
                    if(przerwy[i].poczatek==czas && przerwy[i].czas+przerwy[i].poczatek<=it->maszyna2[j].op2.czas_z && przerwy[i].maszyna==2)
                    {
                        plik<<przerwy[i].id<<","<<przerwy[i].poczatek<<","<<przerwy[i].czas<<";";
                        j-=1;
                        ok=true;
                        czas+=przerwy[i].czas;
                    }
                }
                if(ok==false)
                {

                    plik<<"idle"<<w<<"M2,"<<czas<<","<<it->maszyna2[j].op2.czas_r-czas<<";";
                    l+=1;
                    sum+=it->maszyna2[j].op2.czas_r-czas;
                    czas=it->maszyna2[j].op2.czas_r;
                    j-=1;
                    w++;
                }
            }
            else if(it->maszyna2[j].op2.czas_r==czas)
            {
                 plik<<it->maszyna2[j].op2.id<<","<<it->maszyna2[j].op2.czas_r<<","<<it->maszyna2[j].op2.czas<<";";
                 czas+=it->maszyna2[j].op2.czas;
            }

        }
        czas=0;
        w=1;
        int g=0;
        int s=0;
        plik<<endl;
        for(int i=0;i<przerwy.size();i++)
        {
            if(przerwy[i].maszyna==1)
            {
                g+=1;
                s+=przerwy[i].czas;
            }

        }
        plik<<g<<","<<s<<endl;
        g=0;
        s=0;
        for(int i=0;i<przerwy.size();i++)
        {
            if(przerwy[i].maszyna==2)
            {
                g+=1;
                s+=przerwy[i].czas;
            }

        }
        plik<<g<<","<<s<<endl;
        plik<<0<<endl;
        plik<<l<<","<<sum<<endl;
        l=0;
        sum=0;
        plik<<"***EOF***";





        plik.close();
    }

}

int main()
{
 srand( time( NULL ) );
//while(nr!=11)
//{

//   generator_instacji();
  //instancja();
//}


    wczytaj();
   rozwiazanie_losowe();
   genetyczny();
   vector<zadanie>::iterator it;
   najlepsze();


    cout<<" Pierwsza: "<<sr1<<endl;
    zapisz();
    Beep(1000,1000);


    return 0;
}
