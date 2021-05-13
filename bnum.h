
#ifndef BNUM
#define BNUM
#define STRING(num) #num
#include <string>
#include <math.h>
#include <stack>
#include <iostream>

using namespace std;

struct nodo
{
   int key;
   nodo *next;
   nodo(int x);
};

class bnum
{
protected:
   int d;
   int tamLista;
   nodo *number;
   bnum *ref;

public:
   bnum();
   bnum(int d);
   /**
    * Inicializa um BigNumber com um inteiro
    * */
   bnum(int x, int d);
   /**
    * Inicializa um BigNumber com uma String
    * */
   bnum(string s, int d);
   /**
    * Inicializa um BigNumber com um BigNumber
    * */
   bnum(const bnum &b);
   /**
    * Atribui um BigNumber ao BigNumber origem
    * @param b BigNumber para atribuição 
    * */
   bnum &operator=(const bnum &b);
   /**
    * Soma um BigNumber com um inteiro
    * */
   bnum &operator+(int x);
   /**
    * Soma um BigNumber com um BigNumber
    * */
   bnum &operator+(const bnum &b);
   /**
    * Multiplica um BigNumber com um inteiro
    * */
   bnum &operator*(int x);
   /**
    * Multiplica um BigNumber com um BigNumber
    * */
   bnum &operator*(const bnum &b);
   /**
    * Retorna se dois BigNumbers são iguais
    * */
   bool operator==(const bnum &b);
   /**
    * Retorna a String de um BigNumber
    * */
   string toStr();
   ~bnum();
};

#endif