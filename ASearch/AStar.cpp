#include <bits/stdc++.h>
#include <ctime>
using namespace std;

double distance(const pair<int, int> &a, const pair<int, int> &b){
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

class aStar{
    public:
        aStar();
        void print();
        void findPath();
    private:
        char character[100][100];
        int numRow = 0, numCol = 0;
        double h[100][100];
        pair<int, int> start, end;
};

int main(){
    clock_t start = clock();
    freopen("input4.txt", "r", stdin);
    aStar a;
    a.findPath();
    clock_t end = clock();
    double timeUsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    cout << "Time used: " << timeUsed << "s" << endl;
return 0;
}

aStar::aStar(){
    string s;
    while(getline(cin, s)){
        for(int i = 0; i < s.length(); i++){
            character[numRow][i] = s[i];
            if(s[i] == 'A'){
                start.first = numRow;
                start.second = i;
            }
            if(s[i] == 'B'){
                end.first = numRow;
                end.second = i;
            }
        }
        numCol = s.length();
        numRow++;
    }
    // heuristic
    for(int i = 0; i < numRow; i++)
        for(int j = 0; j < numCol; j++){
            h[i][j] = distance({i, j}, end);
        }
}

void aStar::print(){
    for(int i = 0; i < numRow; i++){
        for(int j = 0; j < numCol; j++){
            cout << character[i][j];
        }
        cout << endl;
    }

    cout << "start: " << start.first << " " << start.second << endl;
    cout << "end: " << end.first << " " << end.second << endl;
}

void aStar::findPath(){

    //initialize
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    double g[100][100];
    double dist[100][100];
    for(int i = 0; i < numRow; i++)
        for(int j = 0; j < numCol; j++)
            g[i][j] = 0, dist[i][j] = 1e9;
    using dcoor = pair<double, pair<int, int>>;
    priority_queue<dcoor, vector<dcoor>, greater<dcoor>> frontier;
    frontier.push({0, start});
    g[start.first][start.second] = 0;
    pair<int, int> parent[100][100];
    parent[start.first][start.second] = {-1, -1};

    //dijsktra
    while(!frontier.empty()){
        pair<int, int> v = frontier.top().second;
        double d_v = frontier.top().first;
        frontier.pop();
        if(v == end) break;
        if (d_v > dist[v.first][v.second]) continue;
        for(int i = 0; i < 4; ++i){
            int x = v.first + dx[i];
            int y = v.second + dy[i];
            if(x < 0 || x >= numRow || y < 0 || y >= numCol) continue;
            if(character[x][y] == '#') continue;
            g[x][y] = g[v.first][v.second] + 1;
            double f = g[x][y] + h[x][y];
            if(f < dist[x][y]){
                dist[x][y] = f;
                parent[x][y] = v;
                frontier.push({f, {x, y}});
            }
        }
    }
    parent[start.first][start.second] = {-1, -1};

    //print path
    pair<int, int> cur = end;
    while(cur != make_pair(-1, -1)){
        character[cur.first][cur.second] = '*';
        cur = parent[cur.first][cur.second];
    }
    character[start.first][start.second] = 'A';
    character[end.first][end.second] = 'B';

    print();
}