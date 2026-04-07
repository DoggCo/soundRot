#include <chrono>
#include <thread>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>

#include "soloud.h"
#include "soloud_wav.h"

struct AudioSystem {
    SoLoud::Soloud engine;
    SoLoud::Wav waterphone;
    SoLoud::Wav metalpipe;

    void init() {
        engine.init();
        waterphone.load("Audio/waterphone.wav");
        metalpipe.load("Audio/metalpipe.wav");
    }

    void playWaterphone() {
        engine.play(waterphone);
            while (engine.getActiveVoiceCount() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    void playMetalpipe() {
        engine.play(metalpipe);
            while (engine.getActiveVoiceCount() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    ~AudioSystem() {
        engine.deinit();
    }
};

int main() {
    bool exitProgram = false;
    while (true) {

        std::cout << "Welcome to this sound mess\n\n";
        int choice = 0;
        int frequency = 0;
    
        AudioSystem audio;
        audio.init();
    
        std::vector<std::string> effects = {
            "Waterphone",   // 1
            "Metal Pipe"    // 2
        };
        std::vector<std::vector<std::string>> selected;
        std::vector<bool> active = { true, true };
    
        while (true) {
            std::cout << "Select audio (0 to finish):\n";
            for (int i = 0; i < effects.size(); i++) {
                if (active[i]) {
                    std::cout << (i + 1) << " - " << effects[i] << "\n";
                }
            }
            std::cin >> choice;
            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(9999, '\n');
                std::cout << "Invalid input\n";
                continue;
            }
            if (choice == 0) {
                exitProgram = true;
                break;
            }
            if (choice < 1 || choice > effects.size() || !active[choice - 1]) {
                std::cout << "Invalid choice\n";
                continue;
            }
            std::cout << "Select frequency (PROPORTIONATE TO YOUR CHOICES) please: ";
            std::cin >> frequency;

            selected.push_back({ effects[choice - 1], std::to_string(frequency) });
            //audio.playWaterphone(); //TODO: remove later.
    
            active[choice - 1] = false;
        }

        int total = 0;
        for (int i = 0; i < selected.size(); i++) {
            total += std::stoi(selected[i][1]);
        }
        std::vector<double> percentages;
        for (int i = 0; i < selected.size(); i++) {
            int value = std::stoi(selected[i][1]);
            double percent = (static_cast<double>(value) / total) * 100.0;
            percentages.push_back(percent);
        }

        for (int i = 0; i < percentages.size(); i++) {
            std::cout << percentages[i] << "\n";
        }
        while(true) {
            int sleeptime = (rand() % 30) + 5;
            std::this_thread::sleep_for(std::chrono::seconds(sleeptime));

            int roll = (rand() % total) + 1;
            int cumulative = 0;
    
            for (int i = 0; i < selected.size(); i++) {
                cumulative += std::stoi(selected[i][1]);
    
                if (roll <= cumulative) {
                    if (selected[i][0] == "Waterphone") audio.playWaterphone();
                    if (selected[i][0] == "Metal Pipe") audio.playMetalpipe();
                    break;
                }
            }
        }
    }

    return 0;
}
