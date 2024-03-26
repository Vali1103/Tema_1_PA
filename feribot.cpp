#include <bits/stdc++.h>

using namespace std;
bool Possibility_maxim(int64_t maxim, vector<int64_t> greutati, int k, int n) {
    // grupeaza masinile pe feriboturi in asa fel incat sa vada
    // daca depaseste acel indice de maxim
    int vase = 0;
    int64_t Cost;
    int64_t i = 0;
    while (vase != k) {
        Cost = 0;
        for ( ; i < n; i++) {
            if (greutati[i] + Cost > maxim) {
                break;
            } else {
                Cost += greutati[i];
            }
        }
        vase++;
    }
    if (i < n)
        return false;
    else
        return true;
}

int64_t binary(int64_t max, int64_t sum, vector < int64_t > greutati, int k) {
  int n = greutati.size();
  int64_t min = 9223372036854775807;
  int64_t left = max, right = sum - max, mid;

  while (left <= right) {
    mid = (left + right) / 2;
    // ii dau mijlocul si daca poate grupa toate masinile pe feriboturi in asa
    // fel incat sa nu depaseasca acel mijloc stiu ca e posibil si
    // il compar cu minimul
    if (Possibility_maxim(mid, greutati, k, n)) {
      if (mid < min)
        min = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return min;
}

int main() {
  ifstream fin("feribot.in");
  ofstream fout("feribot.out");
  // citire din fisier
  int n, k;
  fin >> n;
  fin >> k;

  vector < int64_t > greutati(n);
  int64_t max = 0;
  int64_t sum = 0;
  // citirea vectorului si calcularea sumei si a maximului
  for (int i = 0; i < n; i++) {
    fin >> greutati[i];
    sum += greutati[i];
    if (greutati[i] > max)
      max = greutati[i];
  }
  fin.close();

  // functie de cautare binar intre nr maxim si suma tuturor
  // functie ce-mi returneaza cel mai mic caz posibil
  int64_t final = binary(max, sum, greutati, k);

  fout << final << endl;
  return 0;
}
