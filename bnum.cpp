#include "bnum.h"

nodo::nodo(int x)
{
    key = x;
    next = 0;
};
bnum::bnum(int x, int d)
{
    int resto = -1, div = x, num, pot, verDiv, tv, pos = 0;
    double tam, dAux = d;
    this->d = d;
    string s = to_string(x);
    tam = s.length();
    tv = ceil(tam / d);
    int vet[tv];
    pot = pow(10, d);
    verDiv = (pow(10, d) - 1);
    while (div != 0)
    {
        if (div > verDiv)
        {
            resto = div % pot;
            vet[pos] = resto;
            div = div / pot;
            pos++;
        }
        else
        {
            vet[pos] = div;
            div = 0;
        }
    }
    if (tv > 2)
    {
        number = new nodo(vet[0]);
        nodo *temp = new nodo(vet[1]);
        number->next = temp;
        this->tamLista = 2;
        for (int i = 2; i < tv; i++)
        {
            nodo *aux = new nodo(vet[i]);
            temp->next = aux;
            temp = temp->next;
            this->tamLista++;
        }
    }
    else if (tv == 2)
    {
        number = new nodo(vet[0]);
        nodo *temp = new nodo(vet[1]);
        number->next = temp;
        this->tamLista = 2;
    }
    else
    {
        number = new nodo(vet[0]);
        this->tamLista = 1;
    }
}

bnum::bnum(string s, int d)
{
    this->d = d;
    int tv, cont = 0, posStr;
    double tam, dAux = d;
    string auxStr = "";
    nodo *temp;
    nodo *aux;
    tam = s.length();
    tv = ceil(tam / d);
    string vet[tv];
    for (int i = (tam - 1), n = 0; i >= 0; i--)
    {
        if (tam == d)
        {
            vet[n] = s;
        }
        else
        {
            if (i - (d - 1) >= 0)
            {
                i++;
                for (int a = (i - d); a < i; a++)
                {
                    auxStr += s[a];
                }
                vet[n] = auxStr;
                n++;
                auxStr = "";
                i -= d;
            }
            else
            {
                i++;
                for (int a = 0; a < i; a++)
                {
                    auxStr += s[a];
                }
                vet[n] = auxStr;
                break;
            }
        }
    }
    if (tv > 2)
    {
        number = new nodo(stoi(vet[0]));
        nodo *temp = new nodo(stoi(vet[1]));
        number->next = temp;
        this->tamLista = 2;
        for (int i = 2; i < tv; i++)
        {
            nodo *aux = new nodo(stoi(vet[i]));
            temp->next = aux;
            temp = temp->next;
            this->tamLista++;
        }
    }
    else if (tv == 2)
    {
        number = new nodo(stoi(vet[0]));
        nodo *temp = new nodo(stoi(vet[1]));
        number->next = temp;
        this->tamLista = 2;
    }
    else
    {
        this->tamLista = 1;
        number = new nodo(stoi(vet[0]));
    }
}

bnum::bnum(const bnum &b)
{
    nodo *a = b.number;
    number = new nodo(a->key);
    nodo *c = number;
    a = a->next;
    while (a != 0)
    {
        nodo *aux = new nodo(a->key);
        c->next = aux;
        c = c->next;
        a = a->next;
    }
    d = b.d;
    tamLista = b.tamLista;
}
bnum::bnum(int d)
{
    this->d = d;
}
bnum::bnum()
{
    number = new nodo(0);
}
bnum &bnum::operator=(const bnum &b)
{
    while (number != 0)
    {
        nodo *temp = number;
        number = number->next;
        delete temp;
    }
    nodo *a = b.number;
    number = new nodo(a->key);
    nodo *c = number;
    a = a->next;
    while (a != 0)
    {
        nodo *aux = new nodo(a->key);
        c->next = aux;
        c = c->next;
        a = a->next;
    }
    d = b.d;
    tamLista = b.tamLista;
    return *this;
}

bnum &bnum::operator+(int x)
{
    bnum som(x, d);
    int verDiv = (pow(10, d) - 1), div, resto, pot = pow(10, d), carry = 0;
    nodo *auxPrinc = number;
    nodo *auxSom = som.number;
    ref = new bnum(d);
    nodo *temp, *aux;
    ref->number = new nodo(auxPrinc->key + auxSom->key);
    ref->tamLista++;
    auxPrinc = auxPrinc->next;
    auxSom = auxSom->next;
    if (auxPrinc != 0 || auxSom != 0)
    {
        if (auxPrinc != 0 && auxSom != 0)
        {
            temp = new nodo(auxPrinc->key + auxSom->key);
            auxPrinc = auxPrinc->next;
            auxSom = auxSom->next;
        }
        else if (auxPrinc != 0)
        {
            temp = new nodo(auxPrinc->key);
            auxPrinc = auxPrinc->next;
        }
        else
        {
            temp = new nodo(auxSom->key);
            auxSom = auxSom->next;
        }
        ref->number->next = temp;
        ref->tamLista++;
    }

    if (ref->number->key > verDiv)
    {
        resto = ref->number->key % pot;
        carry = ref->number->key / pot;
        ref->number->key = resto;
    }
    if (ref->number->next != 0 && (temp->key + carry) > verDiv)
    {
        resto = (temp->key + carry) % pot;
        carry = (temp->key + carry) / pot;
        temp->key = resto;
    }
    if (auxPrinc == 0 && auxSom == 0 && carry != 0)
    {
        aux = new nodo(carry);
        ref->number->next = aux;
        ref->tamLista++;
    }
    while (auxPrinc != 0 || auxSom != 0)
    {
        if (auxPrinc != 0 && auxSom != 0)
        {
            if ((auxPrinc->key + auxSom->key + carry) > verDiv)
            {
                div = auxPrinc->key + auxSom->key + carry;
                resto = div % pot;
                carry = div / pot;
                aux = new nodo(resto);
                temp->next = aux;
                temp = temp->next;
                auxPrinc = auxPrinc->next;
                auxSom = auxSom->next;
            }
            else
            {
                aux = new nodo((auxPrinc->key + auxSom->key + carry));
                temp->next = aux;
                temp = temp->next;
                carry = 0;
                auxPrinc = auxPrinc->next;
                auxSom = auxSom->next;
            }
        }
        else if (auxPrinc != 0)
        {
            if (auxPrinc->key + carry > verDiv)
            {
                div = auxPrinc->key + carry;
                resto = div % pot;
                carry = div / pot;
                aux = new nodo(resto);
                temp->next = aux;
                temp = temp->next;
                auxPrinc = auxPrinc->next;
            }
            else
            {
                aux = new nodo(auxPrinc->key + carry);
                temp->next = aux;
                temp = temp->next;
                carry = 0;
                auxPrinc = auxPrinc->next;
            }
        }
        else
        {
            if (carry + auxSom->key > verDiv)
            {
                div = auxSom->key + carry;
                resto = div % pot;
                carry = div / pot;
                aux = new nodo(resto);
                temp->next = aux;
                temp = temp->next;
                auxSom = auxSom->next;
            }
            else
            {
                aux = new nodo(auxSom->key + carry);
                temp->next = aux;
                temp = temp->next;
                carry = 0;
                auxSom = auxSom->next;
            }
        }
    }
    if (carry != 0)
    {
        aux = new nodo(carry);
        temp->next = aux;
        temp = temp->next;
    }
    return *ref;
}

bnum &bnum::operator+(const bnum &b)
{
    bnum mud(b);
    string bn = mud.toStr();
    bnum som(bn, d);
    int verDiv = (pow(10, d) - 1), div, resto, pot = pow(10, d), carry = 0;
    nodo *auxPrinc = number;
    nodo *auxSom = som.number;
    ref = new bnum(d);
    nodo *temp, *aux;
    ref->number = new nodo(auxPrinc->key + auxSom->key);
    ref->tamLista++;
    auxPrinc = auxPrinc->next;
    auxSom = auxSom->next;
    if (auxPrinc != 0 || auxSom != 0)
    {
        if (auxPrinc != 0 && auxSom != 0)
        {
            temp = new nodo(auxPrinc->key + auxSom->key);
            auxPrinc = auxPrinc->next;
            auxSom = auxSom->next;
        }
        else if (auxPrinc != 0)
        {
            temp = new nodo(auxPrinc->key);
            auxPrinc = auxPrinc->next;
        }
        else
        {
            temp = new nodo(auxSom->key);
            auxSom = auxSom->next;
        }
        ref->number->next = temp;
        ref->tamLista++;
    }

    if (ref->number->key > verDiv)
    {
        resto = ref->number->key % pot;
        carry = ref->number->key / pot;
        ref->number->key = resto;
    }
    if (ref->number->next != 0 && (temp->key + carry) > verDiv)
    {
        resto = (temp->key + carry) % pot;
        carry = (temp->key + carry) / pot;
        temp->key = resto;
    }
    if (auxPrinc == 0 && auxSom == 0 && carry != 0)
    {
        aux = new nodo(carry);
        ref->number->next = aux;
        ref->tamLista++;
    }
    while (auxPrinc != 0 || auxSom != 0)
    {
        if (auxPrinc != 0 && auxSom != 0)
        {
            if ((auxPrinc->key + auxSom->key + carry) > verDiv)
            {
                div = auxPrinc->key + auxSom->key + carry;
                resto = div % pot;
                carry = div / pot;
                aux = new nodo(resto);
                temp->next = aux;
                temp = temp->next;
                auxPrinc = auxPrinc->next;
                auxSom = auxSom->next;
            }
            else
            {
                aux = new nodo((auxPrinc->key + auxSom->key + carry));
                temp->next = aux;
                temp = temp->next;
                carry = 0;
                auxPrinc = auxPrinc->next;
                auxSom = auxSom->next;
            }
        }
        else if (auxPrinc != 0)
        {
            if (auxPrinc->key + carry > verDiv)
            {
                div = auxPrinc->key + carry;
                resto = div % pot;
                carry = div / pot;
                aux = new nodo(resto);
                temp->next = aux;
                temp = temp->next;
                auxPrinc = auxPrinc->next;
            }
            else
            {
                aux = new nodo(auxPrinc->key + carry);
                temp->next = aux;
                temp = temp->next;
                carry = 0;
                auxPrinc = auxPrinc->next;
            }
        }
        else
        {
            if (carry + auxSom->key > verDiv)
            {
                div = auxSom->key + carry;
                resto = div % pot;
                carry = div / pot;
                aux = new nodo(resto);
                temp->next = aux;
                temp = temp->next;
                auxSom = auxSom->next;
            }
            else
            {
                aux = new nodo(auxSom->key + carry);
                temp->next = aux;
                temp = temp->next;
                carry = 0;
                auxSom = auxSom->next;
            }
        }
    }
    if (carry != 0)
    {
        aux = new nodo(carry);
        temp->next = aux;
        temp = temp->next;
    }
    return *ref;
}

bnum &bnum::operator*(int x)
{
    string bn = "0", salva;
    bnum som(x, d);
    bnum somAux(som.toStr(), d);
    bnum pinAux(toStr(), d);
    bnum result("0", d);
    int verDiv = (pow(10, d) - 1), div, resto, pot = pow(10, d), carry = 0, cont = 0, contAux, pos = 0;
    bnum vet[som.tamLista];
    nodo *auxPrinc = pinAux.number;
    nodo *auxSom = somAux.number;
    nodo *temp, *aux, *auxPer;
    while (auxSom != 0)
    {
        contAux = cont;
        while (contAux--)
        {
            for (int i = 0; i < d; i++)
            {
                bn += "0";
            }
        }
        bnum auxiliar(bn, d);
        bn = "";
        while (auxPrinc != 0)
        {
            if (cont == 0)
            {
                if ((auxSom->key * auxPrinc->key + carry) > verDiv)
                {
                    resto = (auxSom->key * auxPrinc->key + carry) % pot;
                    carry = (auxSom->key * auxPrinc->key + carry) / pot;
                    auxPrinc->key = resto;
                }
                else
                {
                    auxPrinc->key = (auxSom->key * auxPrinc->key + carry);
                    carry = 0;
                }
                if (auxPrinc->next == 0 && carry != 0)
                {
                    aux = new nodo(carry);
                    auxPrinc->next = aux;
                    auxPrinc = auxPrinc->next;
                    carry = 0;
                }
            }
            else
            {
                auxPer = auxiliar.number;
                while (auxPer->next != 0)
                {
                    auxPer = auxPer->next;
                }
                if ((auxSom->key * auxPrinc->key + carry) > verDiv)
                {
                    resto = (auxSom->key * auxPrinc->key + carry) % pot;
                    carry = (auxSom->key * auxPrinc->key + carry) / pot;
                    aux = new nodo(resto);
                    auxPer->next = aux;
                    auxPer = auxPer->next;
                }
                else
                {
                    aux = new nodo((auxSom->key * auxPrinc->key + carry));
                    auxPer->next = aux;
                    auxPer = auxPer->next;
                    carry = 0;
                }
                if (auxPrinc->next == 0 && carry != 0)
                {
                    aux = new nodo(carry);
                    auxPer->next = aux;
                    carry = 0;
                }
                salva = auxiliar.toStr();
            }
            auxPrinc = auxPrinc->next;
        }
        if (cont == 0)
        {
            vet[pos] = pinAux;
            pos++;
        }
        else
        {
            vet[pos] = bnum(salva, d);
            pos++;
        }
        auxPrinc = number;
        cont++;
        auxSom = auxSom->next;
    }
    for (int i = 0; i < som.tamLista; i++)
    {
        bnum soma(vet[i]);
        result = result + soma;
    }
    ref = new bnum(result);
    return *ref;
}

bnum &bnum::operator*(const bnum &b)
{
    bnum mud(b);
    string troca = mud.toStr();
    string bn = "0", salva;
    bnum som(troca, d);
    bnum somAux(som.toStr(), d);
    bnum pinAux(toStr(), d);
    bnum result("0", d);
    int verDiv = (pow(10, d) - 1), div, resto, pot = pow(10, d), carry = 0, cont = 0, contAux, pos = 0;
    bnum vet[som.tamLista];
    nodo *auxPrinc = pinAux.number;
    nodo *auxSom = somAux.number;
    nodo *temp, *aux, *auxPer;
    while (auxSom != 0)
    {
        contAux = cont;
        while (contAux--)
        {
            for (int i = 0; i < d; i++)
            {
                bn += "0";
            }
        }
        bnum auxiliar(bn, d);
        bn = "";
        while (auxPrinc != 0)
        {
            if (cont == 0)
            {
                if ((auxSom->key * auxPrinc->key + carry) > verDiv)
                {
                    resto = (auxSom->key * auxPrinc->key + carry) % pot;
                    carry = (auxSom->key * auxPrinc->key + carry) / pot;
                    auxPrinc->key = resto;
                }
                else
                {
                    auxPrinc->key = (auxSom->key * auxPrinc->key + carry);
                    carry = 0;
                }
                if (auxPrinc->next == 0 && carry != 0)
                {
                    aux = new nodo(carry);
                    auxPrinc->next = aux;
                    auxPrinc = auxPrinc->next;
                    carry = 0;
                }
            }
            else
            {
                auxPer = auxiliar.number;
                while (auxPer->next != 0)
                {
                    auxPer = auxPer->next;
                }
                if ((auxSom->key * auxPrinc->key + carry) > verDiv)
                {
                    resto = (auxSom->key * auxPrinc->key + carry) % pot;
                    carry = (auxSom->key * auxPrinc->key + carry) / pot;
                    aux = new nodo(resto);
                    auxPer->next = aux;
                    auxPer = auxPer->next;
                }
                else
                {
                    aux = new nodo((auxSom->key * auxPrinc->key + carry));
                    auxPer->next = aux;
                    auxPer = auxPer->next;
                    carry = 0;
                }
                if (auxPrinc->next == 0 && carry != 0)
                {
                    aux = new nodo(carry);
                    auxPer->next = aux;
                    carry = 0;
                }
                salva = auxiliar.toStr();
            }
            auxPrinc = auxPrinc->next;
        }
        if (cont == 0)
        {
            vet[pos] = pinAux;
            pos++;
        }
        else
        {
            vet[pos] = bnum(salva, d);
            pos++;
        }
        auxPrinc = number;
        cont++;
        auxSom = auxSom->next;
    }
    for (int i = 0; i < som.tamLista; i++)
    {
        bnum soma(vet[i]);
        result = result + soma;
    }
    ref = new bnum(result);
    return *ref;
}

bool bnum::operator==(const bnum &b)
{
    bnum a(b);
    string bnum1 = toStr();
    string bnum2 = a.toStr();
    if (bnum1 == bnum2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string bnum::toStr()
{
    stack<int> pilha;
    string lin = "";
    nodo *aux = number;
    while (aux != 0)
    {
        pilha.push(aux->key);
        aux = aux->next;
    }
    int tamPilha = pilha.size();
    while (!pilha.empty())
    {
        string auxStr = to_string(pilha.top());
        if (pilha.size() < tamPilha && auxStr.length() < d)
        {
            for (int i = 0; i < (d - auxStr.length()); i++)
            {
                lin += "0";
            }
            lin += auxStr;
        }
        else
        {
            lin += auxStr;
        }
        pilha.pop();
    }
    return lin;
}

bnum::~bnum()
{
    while (number != 0)
    {
        nodo *aux = number;
        number = number->next;
        delete aux;
    }
}