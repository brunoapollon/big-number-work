#include "app.h"
#include <fstream>
#include <sstream>
void app::factorial(const bnum &number)
{
  bnum fat(number);
  ofstream stream("fatorial.txt", ofstream::out);
  int num = stoi(fat.toStr());
  while (--num != 0)
  {
    fat = fat * num;
  }
  stream << fat.toStr() << endl;
  stream.close();
}
void app::frequenceTable(const bnum &number)
{
  ofstream stream("frequenceTable.txt", ofstream::out);
  bnum freq(number);
  string percorre = freq.toStr();
  int vet[10];
  for (int i = 0; i < 10; i++)
  {
    vet[i] = 0;
  }

  for (int i = 0; i < percorre.length(); i++)
  {
    switch (percorre[i])
    {
    case '0':
      vet[0]++;
      break;
    case '1':
      vet[1]++;
      break;
    case '2':
      vet[2]++;
      break;
    case '3':
      vet[3]++;
      break;
    case '4':
      vet[4]++;
      break;
    case '5':
      vet[5]++;
      break;
    case '6':
      vet[6]++;
      break;
    case '7':
      vet[7]++;
      break;
    case '8':
      vet[8]++;
      break;
    case '9':
      vet[9]++;
      break;
    default:
      break;
    }
  }
  for (int i = 0; i < 10; i++)
  {
    stream << i << "    " << vet[i] << endl;
  }
  stream.close();
}
