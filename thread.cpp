//Buscas com threads
//by: Gustavo Souza Neves
#include <iostream>
#include <thread>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <random>
#include <atomic>

using namespace std;

atomic<bool> terminou(false); //incia a variável "terminou" com falsa, posteriormente usada para saber quem terminou primeiro.

//-----------------------lógica da busca binária------------------------
int buscaBinaria(vector<int>& v, int x) {

    int inicio = 0;
    int fim = v.size() - 1;

    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;

        if (v[meio] == x)
            return meio;

        if (x > v[meio])
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

//------------------------função de busca linear ----------------------
void bus1(int t, int x) {

    vector<int> v;

    for(int i = 0; i < t; i++)
        v.push_back(i);

    shuffle(v.begin(), v.end(), default_random_engine(time(0)));

    for(int i = 0; i < v.size(); i++) {

        //verifica se alguém terminou antes se sim só return, se não vai para o próximo if
        if(terminou) return;

        if(v[i] == x) {
            //se ninguém terminou, então vai entrar no if e não vai deixar o outro thread executar também
            if(!terminou.exchange(true)) {
                cout << "busca Linear: " << endl;
                for (int i = 0; i < t; i++){
                    cout << v[i] << ", ";
                }
                cout << endl;
                cout << "Achou no indice " << i << endl;
            }

            return;
        }
    }
}

//------------------------função de busca binária ----------------------
void bus2(int t, int x) {

    vector<int> v;

    for(int i = 0; i < t; i++)
        v.push_back(i);

    sort(v.begin(), v.end());

    int pos = buscaBinaria(v, x);
    //verifica se alguém terminou antes se sim só return, se não vai para o próximo if
    if(terminou) return;

    if(pos != -1) {
        //se ninguém terminou, então vai entrar no if e não vai deixar o outro thread executar também
        if(!terminou.exchange(true)) {
            cout << "busca binaria: " << endl;
            for (int i = 0; i < t; i++){
                    cout << v[i] << ", ";
                }
            cout << endl;
            cout << "Achou no indice " << pos << endl;
        }
    }
}

int main() {

    srand(time(0));
    //variáveis centrais que controlam o tamanho do vetor e busca do digito, respectivamente.
    int t;
    int x;

    cout << "tamanho do vetor: ";
    cin >> t;
    cout << "número buscadoc: ";
    cin >> x;

    //executam e passam os argumentos para as funções 
    thread t1(bus1, t, x);
    thread t2(bus2, t, x);

    //"join()" faz com que a thread não termine antes da função terminar 
    t1.join();
    t2.join();

    return 0;
}
