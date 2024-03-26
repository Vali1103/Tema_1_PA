#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {
    // Inițializăm tabelul de programare dinamică
    vector <vector <int> > dp(m + 1, vector <int>(n * x + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= n * x; ++j) {
            // Nu luăm în considerare acest tip de sushi
            dp[i][j] = dp[i - 1][j];

            // Dacă avem suficienți bani pentru a cumpăra acest tip de sushi
            if (j >= p[i - 1]) {
                // Calculăm suma notelor pentru toate tipurile de sushi
                int sum_grades = 0;
                for (int k = 0; k < n; ++k) {
                    sum_grades += g[k][i - 1];
                }
                // Alegem să luăm acest tip de sushi dacă ne aduce
				// mai multă satisfacție
                dp[i][j] = max(dp[i][j], dp[i - 1][j - p[i - 1]] + sum_grades);
            }
        }
    }

    // Rezultatul final va fi în celula dp[m][n * x]
    return dp[m][n * x];
}

int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
    // Inițializăm tabelul de programare dinamică
    vector <vector <int> > dp(m + 1, vector <int>(n * x + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= n * x; ++j) {
            // Nu luăm în considerare acest tip de sushi
            dp[i][j] = dp[i - 1][j];

            // Calculăm suma notelor pentru toate tipurile de sushi
            int sum_grades = 0;
            for (int k = 0; k < n; ++k) {
                sum_grades += g[k][i - 1];
            }

            // Dacă avem suficienți bani pentru a cumpăra acest tip de sushi
            if (j >= p[i - 1]) {
                // Alegem să luăm acest tip de sushi dacă ne aduce mai multă
				// satisfacție
                dp[i][j] = max(dp[i][j], dp[i - 1][j - p[i - 1]] + sum_grades);
            }

            // Adaugăm cazul în care putem lua 2 platouri din același
			// tip de sushi
            if (j >= 2 * p[i - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 2 * p[i - 1]]
				 + 2 * sum_grades);
            }
        }
    }

    // Rezultatul final va fi în celula dp[m][n * x]
    return dp[m][n * x];
}


int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
    // Inițializăm tabelul de programare dinamică cu 3 dimensiuni
    vector <vector <vector <int> > > dp(m + 1,
	vector <vector <int> >(n * x + 1, vector <int>(n + 1, 0)));

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= n * x; ++j) {
            for (int k = 0; k <= n; ++k) {
                // Nu luăm în considerare acest tip de sushi
                dp[i][j][k] = dp[i - 1][j][k];

                // Calculăm suma notelor pentru toate tipurile de sushi
                int sum_grades = 0;
                for (int l = 0; l < n; ++l) {
                    sum_grades += g[l][i - 1];
                }

                // Dacă avem suficienți bani pentru a cumpăra
				// acest tip de sushi și nu am depășit numărul maxim de platouri
                if (j >= p[i - 1] && k >= 1) {
                    // Alegem să luăm acest tip de sushi dacă
					// ne aduce mai multă satisfacție
                    dp[i][j][k] = max(dp[i][j][k],
					dp[i - 1][j - p[i - 1]][k - 1] + sum_grades);
                }

                // Adaugăm cazul în care putem lua
				// 2 platouri din același tip de sushi
                if (j >= 2 * p[i - 1] && k >= 2) {
                    dp[i][j][k] = max(dp[i][j][k],
					dp[i - 1][j - 2 * p[i - 1]][k - 2] + 2 * sum_grades);
                }
            }
        }
    }

    // Căutăm răspunsul în tabelul de programare
	// dinamică și găsim valoarea maximă
    int ans = 0;
    for (int i = 0; i <= n * x; ++i) {
        for (int j = 0; j <= n; ++j) {
            ans = max(ans, dp[m][i][j]);
        }
    }

    return ans;
}


int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
