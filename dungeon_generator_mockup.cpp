#include <iostream>
#include <array>
#include <random>
#include <vector>
using namespace std;

// Thank you, Reddit, for this function
int random_in_range(int a, int b){
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(a, b); // define the range

    return distr(gen); // generate numbers
}

bool validate_room(int COLS, int ROWS, int positionX, int positionY, int height, int width, std::array<std::array<int, 50>, 50> dungeonGrid){
    
    // Out of Y boundaries
    if (positionY+height > ROWS){
        return false;
    }
    
    // Out of Y boundaries
    if (positionX+width > COLS){
        return false;
    }

    for (int i = positionY; i < positionY + height; i++) {
        for (int j = positionX; j < positionX + width; j++) {
            if (dungeonGrid[i][j] == 0) {
                return false;  // Rooms can't EVER overlap
            }
        }
    }
    return true;
    return true;
}

void createCorridor(std::array<std::array<int, 50>, 50>& dungeonGrid, int x1, int y1, int x2, int y2) {
    // Step 1: Move horizontally from x1 to x2
    int stepX = (x2 > x1) ? 1 : -1;
    for (int x = x1; x != x2; x += stepX) {
        dungeonGrid[y1][x] = 0;  // Carve floor tile
    }

    // Step 2: Move vertically from y1 to y2
    int stepY = (y2 > y1) ? 1 : -1;
    for (int y = y1; y != y2; y += stepY) {
        dungeonGrid[y][x2] = 0;  // Carve floor tile
    }

    // That should connect it
}


int main() {
        
    const int ROWS = 50;
    const int COLS = 50;

    std::array<std::array<int, COLS>, ROWS> dungeonGrid;

    for (int i = 0; i < dungeonGrid.size(); i++){
        for (int j = 0; j < dungeonGrid[i].size(); j++ ){
            // It's all walls at first
            dungeonGrid[i][j] = 1;
        }
    }

    // Generate random rooms
    srand(time(0));
    int attempts = 150;

    vector<int> roomCenterX = {};
    vector<int> roomCenterY = {};

    while (attempts > 0){
        attempts--;
        // Random room size
        int height = random_in_range(2,7);
        int width = random_in_range(2,7);

        int positionX = random_in_range(1, COLS - width - 1);
        int positionY = random_in_range(1, ROWS - height - 1);

        if (validate_room(COLS, ROWS, positionX, positionY, height, width, dungeonGrid)) {
            // Save room centers
            roomCenterX.push_back(positionX + width/2);
            roomCenterY.push_back(positionY + height/2);

            // Mark as floor
            for (int i = positionY; i < positionY + height; i++) {
                for (int j = positionX; j < positionX + width; j++) {
                    dungeonGrid[i][j] = 0;  // Mark as floor cell
                }
            }
        }

    }
    

    // Draw random corridors to connect them.
    for (int i = 0; i < roomCenterX.size()-1; i++){
        createCorridor(dungeonGrid, roomCenterX[i], roomCenterY[i], roomCenterX[i+1], roomCenterY[i+1]);
    }

    for (int i = 0; i < dungeonGrid.size(); i++){
        for (int j = 0; j < dungeonGrid[i].size(); j++ ){
            if (dungeonGrid[i][j] == 0){
                cout << " ";
            } else {
                cout << "0";
            };
        }
        cout << endl;
    }
}
