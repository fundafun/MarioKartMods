#include <switch.h>
#include <iostream>

// Placeholder memory 
#define LAP_STATUS_OFFSET 0x1045B300  // current lap
#define PLAYER_SPEED_OFFSET 0x1045AABC //  player speed

// (speed multiplier)
#define BOOST_MULTIPLIER 1.5f

void applyLapBoost(int currentLap) {
    // if new lap, then apply boost
    if (currentLap > 0) {
        uintptr_t* baseAddress = (uintptr_t*)PLAYER_SPEED_OFFSET;
        float* playerSpeed = (float*)baseAddress;
        *playerSpeed *= BOOST_MULTIPLIER;
        std::cout << "Boost applied for lap " << currentLap << "!" << std::endl;
    }
}

int main() {
    consoleInit(NULL);

    std::cout << "Mario Kart 8 Deluxe Boost Every Lap Mod Initialized!" << std::endl;

    // Run the mod while the game is running
    while (appletMainLoop()) {
        hidScanInput();
        
        // Get the current lap (this offset needs to be identified and updated)
        int* currentLap = (int*)LAP_STATUS_OFFSET;
        
        // Apply boost every lap
        applyLapBoost(*currentLap);

        // Exit on "+" button press
        if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) break;

        consoleUpdate(NULL);  // Update console output
    }

    consoleExit(NULL); // Clean up resources
    return 0;
}
