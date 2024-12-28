#include <switch.h>
#include <iostream>

// Placeholder (update for version of Mario Kart 8 Deluxe)
#define PLAYER_SPEED_OFFSET 0x1045AABC // change to actual speed memory address
#define NUM_PLAYERS_OFFSET  0x1045A100 // change to actual player count address

void modifyKartSpeed(float speedMultiplier) {
    // Accessing game memory (example offsets)
    uintptr_t* baseAddress = (uintptr_t*)PLAYER_SPEED_OFFSET;
    int numPlayers = *(int*)NUM_PLAYERS_OFFSET;

    for (int i = 0; i < numPlayers; i++) {
        float* playerSpeed = (float*)(baseAddress + (i * 0x100)); // change offset for each player
        *playerSpeed *= speedMultiplier; // change the multiplier
    }
    std::cout << "Kart speeds increased by " << speedMultiplier << "x!" << std::endl;
}

int main() {
    consoleInit(NULL);

    std::cout << "Mario Kart 8 Deluxe Mod Initialized!" << std::endl;

    // double the speed
    modifyKartSpeed(2.0f);

    std::cout << "Press + to exit." << std::endl;

    while (appletMainLoop()) {
        hidScanInput();
        if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) break; // Exit on "+" button press
        consoleUpdate(NULL);
    }

    consoleExit(NULL); // Clean up resources
    return 0;
}
