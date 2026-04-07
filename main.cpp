#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <csignal>

#include "soloud.h"
#include "soloud_wav.h"

volatile sig_atomic_t interrupted = 0;

void handleSigint(int) {
    interrupted = 1;
}

struct AudioSystem {
    SoLoud::Soloud engine;
    SoLoud::Wav waterphone;
    SoLoud::Wav metalpipe;
    SoLoud::Wav foxy;
    SoLoud::Wav correct;
    SoLoud::Wav incorrect;
    SoLoud::Wav smoke;
    SoLoud::Wav cloaker;

    void init() {
        engine.init();
        waterphone.load("Audio/waterphone.wav");
        metalpipe.load("Audio/metalpipe.wav");
        foxy.load("Audio/foxy.wav");
        correct.load("Audio/correct.wav");
        incorrect.load("Audio/incorrect.wav");
        smoke.load("Audio/smokealarm.wav");
        cloaker.load("Audio/cloaker.wav");
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
    void playFoxy() {
        engine.play(foxy);
            while (engine.getActiveVoiceCount() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    void playCorrect() {
        engine.play(correct);
            while (engine.getActiveVoiceCount() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    void playIncorrect() {
        engine.play(incorrect);
            while (engine.getActiveVoiceCount() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    void playSmoke() {
        engine.play(smoke);
            while (engine.getActiveVoiceCount() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    void playCloaker() {
        engine.play(cloaker);
            while (engine.getActiveVoiceCount() > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    ~AudioSystem() {
        engine.deinit();
    }
};

int main() {
    signal(SIGINT, handleSigint);
    bool exitProgram = false;
    while (true) {

        std::cout << "Welcome to this sound mess\n";
        std::cout << "Please write -1 to exit.\n\n";
        int choice = 0;
        int frequency = 0;
    
        AudioSystem audio;
        audio.init();
    
        std::vector<std::string> effects = {
            "Waterphone",   // 1
            "Metal Pipe",   // 2
            "Foxy",         // 3
            "Correct",      // 4
            "Incorrect",    // 5
            "Smoke Alarm",  // 6
            "Cloaker"       // 7
        };
        std::vector<std::vector<std::string>> selected;
        std::vector<bool> active(effects.size(), true);
    
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
                break;
            }
            if (choice == -1) {
                return 0;
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

        /*for (int i = 0; i < percentages.size(); i++) {
            std::cout << percentages[i] << "\n";
        }*/
        int max;
        int min;
        std::cout << "CTRL+C and enter to exit after audio plays.\n\n";
        std::cout << "Please enter max frequency (seconds): ";
        std::cin >> max;
        std::cout << "Please enter min frequency (seconds): ";
        std::cin >> min;
        while(!interrupted) {
            int sleeptime = (rand() % (max - min + 1)) + min;
            std::this_thread::sleep_for(std::chrono::seconds(sleeptime));

            int roll = (rand() % total) + 1;
            int cumulative = 0;
    
            for (int i = 0; i < selected.size(); i++) {
                cumulative += std::stoi(selected[i][1]);
    
                if (roll <= cumulative) {
                    if (selected[i][0] == "Waterphone") audio.playWaterphone();
                    if (selected[i][0] == "Metal Pipe") audio.playMetalpipe();
                    if (selected[i][0] == "Foxy") audio.playFoxy();
                    if (selected[i][0] == "Correct") audio.playCorrect();
                    if (selected[i][0] == "Incorrect") audio.playIncorrect();
                    if (selected[i][0] == "Smoke Alarm") audio.playSmoke();
                    if (selected[i][0] == "Cloaker") audio.playCloaker();
                    break;
                }
            }
        }
        interrupted = 0;
    }
    return 0;
}
