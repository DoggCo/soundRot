#include <chrono>
#include <thread>

#include "soloud.h"
#include "soloud_wav.h"

int main() {
    SoLoud::Soloud soloud;
    soloud.init();

    SoLoud::Wav sound;
    sound.load("Audio/waterphone.wav");

    soloud.play(sound);

    while (soloud.getActiveVoiceCount() > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    soloud.deinit();
    return 0;
}
