#include <iostream>
#include <stdexcept>
#include <AL/AL.h>
#include <AL/ALC.h>

namespace {  // Don't pollute the global namespace.
/* Use an object to manage the device and context with RAII.
 * We want to clean up even if an exception is thrown, so doing
 * it in the destructor makes it super clean.
 */
struct AlContext {
    ALCdevice* device = nullptr;
    ALCcontext* context = nullptr;

    AlContext() {
        device = alcOpenDevice(nullptr);
        if (device == nullptr) {
            throw std::runtime_error{"Couldn't open OpenAL device."};
        }
        context = alcCreateContext(device, nullptr);
        if (context == nullptr) {
            throw std::runtime_error{"Couldn't open OpenAL context."};
        }
    }

    ~AlContext() {
        alcDestroyContext(context);
        alcCloseDevice(device);
    }
};
}

int main(int, char**) {
    AlContext alContext;
    std::cout << "Hello world.\n";
    return 0;
}