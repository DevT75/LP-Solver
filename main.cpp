#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <unordered_map>
#include <sstream>
#include <ios>
#include <limits>
using namespace std;

int n,m;
vector<string> variables;
vector<vector<double>> tableau;
vector<double> solution;
map<int, string> basic_variables, mp, slack;

void initialize() {
  // cout << n << " " << m << endl;
  cin.ignore(numeric_limits<streamsize>::max(),'\n');
  int j = 0;
  tableau[0][j] = 1;
  for (j = 1;j <= n;j++) {
    int t;cin >> t;
    tableau[0][j] = -t;
  }
  cin.ignore(numeric_limits<streamsize>::max(),'\n');
  for (int i = 1;i < m + 1;i++) {
    // cout << i + 1 << "\n";
    string s, t;
    getline(cin, s);
    stringstream ss(s);
    int j = 1;
    while (getline(ss, t, ' ')) {
      if (j > n) {
        solution[i] = stoi(t);
        break;
      }
      tableau[i][j++] = stoi(t);
    }
  }

  for (int i = n + 1;i < n + m + 1;i++) {
    tableau[i - n][i] = 1;
  }


  for (int i = 0;i <= n;i++) {
    if (i == 0) {
      mp[i] = "Z";
      continue;
    }
    string t = "X" + to_string(i);
    mp[i] = t;
  }

  for (int i = 0;i <= m;i++) {
    if (i == 0) {
      basic_variables[i] = "Z";
      continue;
    }
    string t = "S" + to_string(i);
    slack[i] = t;
    mp[n + i] = t;
    basic_variables[i] = t;
  }
}

void printTable() {
  for(int i = 0; i < m + 1; i++) {
    if (i == 0) {
      cout << "\t";
      for (int j = 0;j <= n + m;j++) cout << mp[j] << "\t";
      // for (int j = 1;j <= m;j++) cout << slack[j] << "\t";
      cout << "SOLn" << endl;
    }
    cout << basic_variables[i] << "\t";
    for(const double j : tableau[i]) {
      cout << setprecision(2) << j << "\t";
    }
    cout << solution[i] << endl;
  }
}

int getEnteringIndex() {
  int index = -1;
  double mini = numeric_limits<double>::max();
  for (int i = 1;i < n + m + 1;i++) {
    if (tableau[0][i] < mini) {
      mini = tableau[0][i];
      index = i;
    }
  }
  if (mini >= 0) return -1;
  return index;
}

int getLeavingIndex(int enteringIndex) {
  double mini = numeric_limits<double>::max(), index = -1, dd;
  for (int i = 1;i < m + 1;i++) {
    if (tableau[i][enteringIndex] <= 0) continue;
    if (double ratio = solution[i] / tableau[i][enteringIndex]; ratio < mini) {
      mini = ratio;
      dd = ratio;
      index = i;
    }
  }
  cout << dd << endl;
  return index;
}

void GaussJordanRowOperation(int entering, int leaving) {
  double divisor = tableau[leaving][entering];
  for (int j = 0;j < n + m + 1;j++) {
      tableau[leaving][j] /= divisor;
  }
  solution[leaving] /= divisor;
  for (int i = 0;i < m + 1;i++) {
    if (i == leaving) continue;
    double localCoefficient = tableau[i][entering];
    for (int j = 0;j < n + m + 1;j++) {
      tableau[i][j] = tableau[i][j] - localCoefficient * tableau[leaving][j];
    }
    solution[i] = solution[i] - localCoefficient * solution[leaving];
  }
  basic_variables[leaving] = mp[entering];
}

void solve() {
  int i  = 10;
  while (i--) {
    // find entering variable
    int entering_i = getEnteringIndex();
    cout << entering_i << endl;
    if (entering_i == -1) {
      break;
    }
    // find leaving variable
    int leaving_i = getLeavingIndex(entering_i);
    // cout << mp[entering_i] << "\t" << basic_variables[leaving_i] << "\n";

    // swap leaving variable with entering variable
    // and apply Gauss-Jordan Row Operations
    GaussJordanRowOperation(entering_i, leaving_i);
  }
}

int main(){
  // std::cout << "Hello World!\n";
  cin >> n >> m;
  variables.resize(n + m + 1);
  tableau.resize(m + 1, vector<double>(n + m + 1));
  solution.resize(m + 1);
  initialize();
  printTable();
  solve();

  return 0;
}