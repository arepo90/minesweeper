/*
    Project in C++: Buscaminas
    Miguel Esteban Martinez Villegas | 12-2
*/

#ifdef __unix__         
    #define CLEAR "clear"
#elif defined(_WIN32)
    #define CLEAR "cls"
#endif

#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

vector<vector<pair<int, bool>>> mp;
set<pair<int, int>> flags;
int valid_flags = 0, total_flags = 0, N, M;
vector<pair<int, int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

void populate(){
    srand(time(0));
    vector<pair<int, bool>> temp(N, {0, false});
    for(int i = 0; i < N; i++){
        mp.push_back(temp);
    }
    set<pair<int, int>> s;
    for(int i = 0; i < M; i++){
        int x = rand() % N, y = rand() % N;
        if(s.count({x, y}) > 0) i--;
        else{
            s.insert({x, y});
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

void draw(int x, int y, bool mode = false){
    system(CLEAR);
    cout << " ____                                _\n"
            "|  _ \\                              (_)\n"
            "| |_) |_   _ ___  ___ __ _ _ __ ___  _ _ __   __ _ ___ \n"
            "|  _ <| | | / __|/ __/ _` | '_ ` _ \\| | '_ \\ / _` / __|\n"
            "| |_) | |_| \\__ \\ (_| (_| | | | | | | | | | | (_| \\__ \\ \n"
            "|____/ \\__,_|___/\\___\\__,_|_| |_| |_|_|_| |_|\\__,_|___/\n\n";
    cout << "Controles:\nArriba: W\tIzquierda: A\tAbajo: S\tDerecha: D\nCavar: Q\tBandera: E\tSalir: X\n\nBanderas: " << total_flags << "/" << M << "\n\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i == 0 && j == 0) cout << char(969) << char(973) << char(973) << char(973);
            else if(j == 0) cout << char(972) << char(973) << char(973) << char(973);
            else if(i == 0) cout << char(971) << char(973) << char(973) << char(973);
            else cout << char(974) << char(973) << char(973) << char(973);
            if(i == 0 && j == N-1) cout << char(955) << '\n';
            else if(j == N-1) cout << char(953) << '\n';
        }
        for(int j = 0; j < N; j++){
            cout << char(954) << ((i == y && j == x) ? ">" : " ");
            if(mp[i][j].second) cout << (mp[i][j].first == 0 ? " " : (mode && mp[i][j].first == -1 ? "X" : to_string(mp[i][j].first)));
            else{
                bool temp = true;
                for(auto it = flags.begin(); it != flags.end(); it++){
                    if(i == it->second && j == it->first){
                        cout << '!';
                        temp = false;
                        break;
                    }
                }
                if(temp) cout << '+';
            }
            cout << (i == y && j == x ? "<" : " ");
            if(j == N-1) cout << char(954) << '\n';
        }
    }
    for(int i = 0; i < N; i++){
        if(i == 0) cout << char(968) << char(973) << char(973) << char(973);
        else cout << char(970) << char(973) << char(973) << char(973);
        if(i == N-1) cout << char(956) << '\n';
    }
}

void bfs(int x, int y){
    queue<pair<int, int>> q;
    q.push({x, y});
    mp[y][x].second = true;
    while(!q.empty()){
        int cx = q.front().first, cy = q.front().second;
        q.pop();
        mp[cy][cx].second = true;
        if(mp[cy][cx].first != mp[y][x].first) continue;
        for(int i = 0; i < 8; i++){
            int xx = cx + directions[i].first, yy = cy + directions[i].second;
            if(xx >= 0 && xx < N && yy >= 0 && yy < N && !mp[yy][xx].second) q.push({xx, yy});
        }
    }
}

void end_game(bool win){
    if(win){
        draw(-1, -1, true);
        cout << "\nGanaste let's goooo\n";
    }
    else{
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(mp[i][j].first == -1){
                    mp[i][j].second = true;
                }
            }
        }
        draw(-1, -1, true);
        cout << "\nPerdiste xd\n";
    }
}

int main(){
    system(CLEAR);
    cout << " ____                                _\n"
            "|  _ \\                              (_)\n"
            "| |_) |_   _ ___  ___ __ _ _ __ ___  _ _ __   __ _ ___ \n"
            "|  _ <| | | / __|/ __/ _` | '_ ` _ \\| | '_ \\ / _` / __|\n"
            "| |_) | |_| \\__ \\ (_| (_| | | | | | | | | | | (_| \\__ \\ \n"
            "|____/ \\__,_|___/\\___\\__,_|_| |_| |_|_|_| |_|\\__,_|___/\n\n";
    cout << "Tama" << char(932) << "o del mapa: ";
    cin >> N;
    cout << "\nCantidad de minas (max. " << N*N << "): ";
    cin >> M;
    populate();
    int x = 0, y = 0;
    while(true){
        draw(x, y);
        char op = _getch();
        switch(op){
            case 'w':
                y = max(0, y-1);
                break;
            case 'a':
                x = max(0, x-1);
                break;
            case 's':
                y = min(N-1, y+1);
                break;
            case 'd':
                x = min(N-1, x+1);
                break;
            case 'q':
                if(mp[y][x].first == -1){
                    end_game(false);
                    return 0;
                }
                else if(mp[y][x].first == 0) bfs(x, y);
                else mp[y][x].second = true;
                if(flags.find({x, y}) != flags.end()){
                    flags.erase({x, y});
                    total_flags--;
                }
                break;
            case 'e':
                if(mp[y][x].second) continue;
                else if(flags.find({x, y}) == flags.end()){
                    flags.insert({x, y});
                    total_flags++;
                    if(mp[y][x].first == -1) valid_flags++;
                }
                else{
                    flags.erase({x, y}); 
                    total_flags--;
                    if(mp[y][x].first == -1) valid_flags--; 
                }
                break;
            case 'x':
                return 0;
            default:
                break;
        }
        if(total_flags == valid_flags && valid_flags == M){
            end_game(true);
            return 0;
        }
    }
}