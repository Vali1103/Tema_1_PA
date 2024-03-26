/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */
#include <limits>
#include <algorithm>

#include <cstdint>

#include <fstream>

#include <vector>

using namespace std;

int compare(const void * a,
  const void * b) {
  int int_a = * static_cast <
    const int * > (a);
  int int_b = * static_cast <
    const int * > (b);

  return (int_a > int_b) - (int_a < int_b);
}


int64_t SolveTask1(const vector < int > & a,
  const vector < int > & b) {
  // la nr nelimitat de mutari determin vectorul
  // mai mare, fiind sortati si le parcurg in pararel pe unul crescator
  // si pe celalalt descrescator si pun elementele mai mari
  int bigger_a = 1;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] < b[i]) {
      bigger_a = 0;
      break;
    } else if (a[i] > b[i]) {
      break;
    }
  }
  int64_t n = a.size() - 1;
  int64_t sum = 0;
  int64_t i = 0, j = a.size() - 1;
  if (bigger_a == 0) {
    while (i <= n) {
      if (a[j] > b[i])
        sum += a[j];
      else
        sum += b[i];
      i++;
      j--;
    }
  } else {
    while (i <= n) {
      if (b[j] > a[i])
        sum += b[j];
      else
        sum += a[i];
      i++;
      j--;
    }
  }

  return sum;
}

int64_t SolveTask2(vector < int > & a, vector < int > & b, int moves) {
  // parcurg cele 2 vectori si creez alti 2 unul cu elemente
  // ce intra deja la scor, fiind mai mari, si unul cu restul elementelor.
  int n = a.size();
  vector<int> sum(n);
  vector<int> rest(n);
  int64_t i = 0;
  while (i < n) {
    if (a[i] > b[i]) {
      sum[i] = a[i];
      rest[i] = b[i];
    } else {
      sum[i] = b[i];
      rest[i] = a[i];
    }
    i++;
  }
  // le sortez, apoi parcurg acesti 2 vectori si cat timp
  // am mutari fac mutari cu elementele mai mari, daca nu
  // adaug pur si simplu la scor
  qsort( &sum[0], n, sizeof(int), compare);
  qsort( &rest[0], n, sizeof(int), compare);

  int64_t score = 0;

  i = 0;
  int64_t j = n - 1;
  while (i < n) {
    if (sum[i] < rest[j] && moves > 0) {
      score += rest[j];
      moves--;
    } else {
      score += sum[i];
    }
    j--;
    i++;
  }



  return score;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
  ifstream fin("nostory.in");
  ofstream fout("nostory.out");
  // scheletul este preluat din fisierul oferit, fiind facuta doar citirea
  // si determinarea task-ului
  int task;
  fin >> task;

  int n, moves;
  if (task == 1) {
    fin >> n;
  } else {
    fin >> n >> moves;
  }

  auto a = ReadVector(fin, n);
  auto b = ReadVector(fin, n);
  if (task == 1) {
    qsort( & a[0], n, sizeof(int), compare);
    qsort( & b[0], n, sizeof(int), compare);
  }

  auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
  fout << res << "\n";
  return 0;
}
