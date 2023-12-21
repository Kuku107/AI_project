#include <bits/stdc++.h>
#include <ctime>
using namespace std;

class BFS{
    public:
        BFS();
        void print();
        void findPath();
    private:
        char character[100][100];
        int numRow = 0, numCol = 0;
        pair<int, int> start, end;
};

int main(){
    clock_t start = clock();
    freopen("input4.txt", "r", stdin);
    BFS a;
    a.findPath();
    clock_t end = clock();
    double timeUsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    cout << "Time used: " << timeUsed << "s" << endl;
return 0;
}

BFS::BFS(){
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
}

void BFS::print(){
    for(int i = 0; i < numRow; i++){
        for(int j = 0; j < numCol; j++){
            cout << character[i][j];
        }
        cout << endl;
    }
}

void BFS::findPath(){
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    pair<int, int> parent[100][100];
    bool visited[100][100] = {false};
    queue<pair<int, int>> q;
    q.push(start);
    visited[start.first][start.second] = true;
    parent[start.first][start.second] = {-1, -1};
    while(!q.empty()){
        pair<int, int> cur = q.front();
        q.pop();
        for(int i = 0; i < 4; ++i){
            int x = cur.first + dx[i];
            int y = cur.second + dy[i];
            if (x < 0 || y < 0 || x >= numRow || y >= numCol || character[x][y] == '#') continue;
            if (visited[x][y]) continue;
            visited[x][y] = true;
            q.push({x, y});
            parent[x][y] = cur;
        }
        if (visited[end.first][end.second])
            break;
    }
    if (!visited[end.first][end.second]){
        cout << "No path found" << endl;
        return;
    }
    pair<int, int> cur = end;
    while(cur != make_pair(-1, -1)){
        character[cur.first][cur.second] = '*';
        cur = parent[cur.first][cur.second];
    }
    character[start.first][start.second] = 'A';
    character[end.first][end.second] = 'B';
    print();
}