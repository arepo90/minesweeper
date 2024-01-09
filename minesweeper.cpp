#include <bits/stdc++.h>
using namespace std;
#define N 10
#define M 10

/*
        ╔═══╦═══╦═══╦═══╦═══╗
        ║>1<║ 0 ║ 0 ║ 0 ║ 0 ║
        ╠═══╬═══╬═══╬═══╬═══╣
        ║ 1 ║ 0 ║ 0 ║ 0 ║ 0 ║
        ╠═══╬═══╬═══╬═══╬═══╣
        ║ 1 ║ 0 ║ 0 ║ 0 ║ 0 ║
        ╠═══╬═══╬═══╬═══╬═══╣
        ║ 1 ║ 0 ║ 0 ║ 0 ║ 0 ║
        ╠═══╬═══╬═══╬═══╬═══╣
        ║ 1 ║ 0 ║ 0 ║ 0 ║ 0 ║
        ╚═══╩═══╩═══╩═══╩═══╝
*/

vector<pair<int, int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
vector<vector<pair<int, bool>>> mp;
set<pair<int, int>> flags;

void init(){
    srand(time(0));
    vector<pair<int, bool>> temp;
    for(int i = 0; i < N; i++){
        temp.push_back(make_pair(0, false));
    }
    for(int i = 0; i < N; i++){
        mp.push_back(temp);
    }
    set<pair<int, int>> s;
    for(int i = 0; i <= M; i++){
        int x = rand() % N, y = rand() % N;
        if(s.count({x, y}) > 0) i--;
        else{
            s.insert(make_pair(x, y));
            mp[y][x].first = -1;
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(mp[i][j].first == -1) continue;
            for(int k = 0; k < 8; k++){
                int cx = j + directions[k].first, cy = i + directions[k].second;
                if(cx >= 0 && cx < N && cy >= 0 && cy < N && mp[cy][cx].first == -1) mp[i][j].first++;
            }
        }
    }
}


void draw(int x, int y){
    system("clear");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i == 0 && j == 0) cout << "╔═══";
            else if(j == 0) cout << "╠═══";
            else if(i == 0) cout << "╦═══";
            else cout << "╬═══";
            if(i == 0 && j == N-1) cout << "╗\n";
            else if(j == N-1) cout << "╣\n";
        }
        for(int j = 0; j < N; j++){
            cout << "║" << ((i == y && j == x) ? ">" : " ");
            if(mp[i][j].second) cout << (mp[i][j].first == 0 ? " " : to_string(mp[i][j].first));
            else{
                bool check = true;
                for(auto it = flags.begin(); it != flags.end(); it++){
                    if(i == it->second && j == it->first){
                        cout << '!';
                        check = false;
                    }
                }
                if(check) cout << '+';
            }
            cout << (i == y && j == x ? "<" : " ");
            if(j == N-1) cout << "║\n";
        }
    }
    for(int i = 0; i < N; i++){
        if(i == 0) cout << "╚═══";
        else if(i == N-1) cout << "╩═══╝\n";
        else cout << "╩═══";
    }
}

void check(int x, int y){
    queue<pair<int, int>> q;
    q.push(make_pair(x, y));
    mp[y][x].second = true;
    while(!q.empty()){
        int cx = q.front().first, cy = q.front().second;
        q.pop();
        mp[cy][cx].second = true;
        if(mp[cy][cx].first != 0) continue;
        for(int i = 0; i < 8; i++){
            int xx = cx + directions[i].first, yy = cy + directions[i].second;
            if(xx >= 0 && xx < N && yy >= 0 && yy < N && !mp[yy][xx].second && mp[yy][xx].first == 0) q.push(make_pair(xx, yy));
        }
    }
}

int main(){
    init();
    int cx = 0, cy = 0;
    while(1){
        draw(cx, cy);
        char op; cin >> op;
        switch(op){
            case 'w':
                cy = max(0, cy-1);
                break;
            case 'a':
                cx = max(0, cx-1);
                break;
            case 's':
                cy = min(N-1, cy+1);
                break;
            case 'd':
                cx = min(N-1, cx+1);
                break;
            case 'q':
                if(mp[cy][cx].first != 0) mp[cy][cx].second = true;
                else check(cx, cy);
                break;
            case 'e':
                flags.insert(make_pair(cx, cy));
                mp[cy][cx].second = false;
                break;
            default:
                break;
        }
        //cin >> op;
    }
    draw(0, 0);
    return 0;
}
