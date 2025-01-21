#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>



using namespace std;
using namespace sf;

typedef Vector2f vec2;

RenderWindow window(VideoMode(512,512), "pathfinding");
Event e;
/*
vector<vector<int>> mat = {
{1,1,1,1,1,1,1,1,1},
{1,2,1,0,0,0,0,0,1},
{1,0,1,0,0,0,1,0,1},
{1,0,1,0,1,0,1,0,1},
{1,0,0,0,1,0,1,0,1},
{1,0,1,0,1,1,1,0,1},
{1,0,1,0,0,0,1,0,1},
{1,0,0,0,1,0,1,3,1},
{1,1,1,1,1,1,1,1,1}
};*/
vector<vector<int>> mat = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,2,1},
{1,0,0,1,0,0,0,0,1,1,0,0,1,0,0,0,0,1},
{1,0,0,1,0,0,1,0,0,1,0,1,1,0,0,0,0,1},
{1,0,0,1,0,0,1,1,1,1,0,0,0,1,0,0,0,1},
{1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,1,0,0,0,0,1,1,0,0,1,0,1},
{1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,1},
{1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,1},
{1,0,0,0,0,0,1,0,0,1,1,0,0,0,1,1,0,1},
{1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,0,0,1},
{1,0,0,1,1,0,0,0,1,0,0,0,0,1,1,0,0,1},
{1,3,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
float ratioSize = 512 / mat.size();
vec2 start = vec2(16, 1);
vec2 endPos = vec2(1, 16);

vector<vec2> solve(vector<vector<int>> mat, vec2 pos)
{
    vector<int> dists;
    vector<vec2> movements = {vec2(0, -1), vec2(1, 0), vec2(0, 1), vec2(-1, 0)};
    vector<vec2> safePos;
    vector<vec2> actions;
    vector<vector<int>> mapArr = mat;
    vector<int> lastUnsureIndex;

    bool isSolved = false;
    int iterations = 0;
    while(!isSolved)
    {
        iterations ++ ;
        static int time = clock();
        static int index = 0;
        /*if(clock() - time > 200)
        {
        time = clock();
        CircleShape circle(ratioSize/2);
        circle.setPosition(pos * ratioSize);
        window.clear(Color::Black);
        window.draw(circle);
        window.display();*/
        vector<int> possibleMoves;
        if(mapArr[pos.y - 1][pos.x] != 1) possibleMoves.push_back(0);
        if(mapArr[pos.y][pos.x + 1] != 1) possibleMoves.push_back(1);
        if(mapArr[pos.y + 1][pos.x] != 1) possibleMoves.push_back(2);
        if(mapArr[pos.y][pos.x - 1] != 1) possibleMoves.push_back(3);
        int moveCount = possibleMoves.size();
        if(moveCount == 0)
        {
            mapArr[pos.y][pos.x] = 1;
            int diff = actions.size() - lastUnsureIndex[lastUnsureIndex.size() - 1];
            for(int i = 0; i < diff; i++)
                actions.pop_back();
            lastUnsureIndex.pop_back();
            pos = safePos[safePos.size() - 1];
            mapArr[pos.y][pos.x] = 0;
            safePos.pop_back();
        }
        else if(moveCount == 1)
        {
            mapArr[pos.y][pos.x] = 1;
            vec2 movement = movements[possibleMoves[0]];
            pos += movement;
            actions.push_back(movement);
        }
        else
        {
            mapArr[pos.y][pos.x] = 1;
            safePos.push_back(pos);
            lastUnsureIndex.push_back(actions.size());
            /*vector<float> distancesFromEnd;
            for(auto& p : possibleMoves)
            {
                vec2 diff = endPos -  pos + movements[p];
                float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
                distancesFromEnd.push_back(dist);
            }
            auto it = max_element(distancesFromEnd.begin(), distancesFromEnd.end());
            int index = distance(distancesFromEnd.begin(), it);
            vec2 movement = movements[possibleMoves[index]];*/
            vec2 movement = movements[possibleMoves[rand()%possibleMoves.size()]];
            pos += movement;
            actions.push_back(movement);
        }
        if(mapArr[pos.y][pos.x] == 3)
            isSolved = true;
        //}
    }
    return actions;
}

vector<vec2> getClosest(vector<vector<int>> mat, vec2 pos)
{
    vector<vec2> actions = solve(mat, pos);
    int currentSize = actions.size();
    bool shouldRepeat = true;
    while(shouldRepeat)
    {
        shouldRepeat = false;
        for(int i = 0; i < 100; i++)
        {
            vector<vec2> possibility = solve(mat, pos);
            if(possibility.size() < currentSize)
            {
                cout << currentSize << endl;
                actions = possibility;
                currentSize = possibility.size();
                shouldRepeat = true;
            }
        }
    }

    return actions;
}

int main()
{
    window.setVerticalSyncEnabled(true);
    vector<vec2> actions = getClosest(mat, start);
    while(window.isOpen())
    {
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed) window.close();
        }
        window.clear(Color::Black);
        for(int i = 0; i < mat.size(); i++)
            for(int j = 0; j < mat[i].size(); j++)
            {
               RectangleShape rect(vec2(ratioSize, ratioSize));
               rect.setPosition(vec2(j * ratioSize, i * ratioSize));
               switch(mat[i][j])
               {
                case(0):
                    break;
                case(1):
                    rect.setFillColor(Color::White);
                    window.draw(rect);
                    break;
                case(2):
                    rect.setFillColor(Color::Green);
                    window.draw(rect);
                    break;
                case(3):
                    rect.setFillColor(Color::Red);
                    window.draw(rect);
                    break;
               }
            }
        static int time = clock();
        static int index = 0;
        if(clock() - time > 200 && index < actions.size())
        {
            time = clock();
            start += actions[index];
            index++;
        }
        CircleShape player(ratioSize / 2);
        player.setPosition(start * ratioSize);
        window.draw(player);
        window.display();
    }
    return 0;
}
