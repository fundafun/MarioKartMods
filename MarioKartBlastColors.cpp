#include <switch.h>
#include <iostream>

// placeholder memory offsets 
#define PROJECTILE_COLOR_OFFSET 0x1045B000  // projectile color
#define NUM_PROJECTILES_OFFSET 0x1045A200  // number of projectiles

// Define RGB color values 
#define RED_COLOR 0xFF0000FF // ARGB format: Red
#define GREEN_COLOR 0x00FF00FF // ARGB format: Green
#define BLUE_COLOR 0x0000FFFF // ARGB format: Blue

void modifyProjectileColor(uint32_t color) {
    // Accessing game memory to change color
    uintptr_t* baseAddress = (uintptr_t*)PROJECTILE_COLOR_OFFSET;
    int numProjectiles = *(int*)NUM_PROJECTILES_OFFSET;

    for (int i = 0; i < numProjectiles; i++) {
        uint32_t* projectileColor = (uint32_t*)(baseAddress + (i * 0x100)); // Adjust for each projectile
        *projectileColor = color; // Set the new color
    }
    std::cout << "Projectile color changed!" << std::endl;
}

int main() {
    consoleInit(NULL); // Initialize the console

    std::cout << "Mario Kart 8 Deluxe Mod Initialized!" << std::endl;

    // Change the projectile color to red
    modifyProjectileColor(RED_COLOR);

    std::cout << "Press + to exit." << std::endl;

    while (appletMainLoop()) {
        hidScanInput();
        if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) break; // Exit on "+" button press
        consoleUpdate(NULL);
    }

    consoleExit(NULL); // Clean up resources
    return 0;
}
