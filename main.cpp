#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>



using namespace std;
using namespace sf;

typedef Vector2f vec2;

RenderWindow window(VideoMode(512,512), "pathfinding");
Event e;
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
};
float ratioSize = 512 / mat.size();
vec2 start = vec2(1, 1);
bool solve(vector<vector<int>> mat, vec2 pos)
{
    vector<vec2> movements = {vec2(0, -1), vec2(1, 0), vec2(0, 1), vec2(-1, 0)};
    vector<vec2> safePos;
    vector<vector<int>> mapArr = mat;
    bool isSolved = false;
    //while(!isSolved)
    //{
        vector<int> possibleMoves;
        if(mapArr[pos.y - 1][pos.x] == 0) possibleMoves.push_back(0);
        if(mapArr[pos.y][pos.x + 1] == 0) possibleMoves.push_back(1);
        if(mapArr[pos.y + 1][pos.x] == 0) possibleMoves.push_back(2);
        if(mapArr[pos.y][pos.x - 1] == 0) possibleMoves.push_back(3);
        int moveCount = possibleMoves.size();
    return true;
    //}
}
int main()
{
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
        solve(mat, start);
        window.display();
    }
    return 0;
}
