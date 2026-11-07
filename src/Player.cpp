#include <utility>
#include <vector>
using namespace std;
struct Player {
    vector<int> Vector2 = {0,0}; //The players X and Y position.
    int speed;
    int jump_height;
    bool detected;
    int vision; //how far they can see
    Player(vector<int> Vector2, int speed, int jump_height, bool detected,int vision){
        this->Vector2 = std::move(Vector2);
        this->speed = speed;
        this->jump_height = jump_height;
        this->detected = detected;
        this->vision = vision;
    }

};
