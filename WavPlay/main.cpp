#include <cstdio>
#include <AL/AL.h>
#include <AL/ALC.h>

int main(int, char**) {
    // Initialise OpenAL device & context.

    ALCdevice* const device = alcOpenDevice(nullptr);
    if (device == nullptr) {
        fprintf(stderr, "Couldn't open OpenAL device.");
        return 1;
    }

    ALCcontext* const context = alcCreateContext(device, nullptr);
    if (context == nullptr) {
        fprintf(stderr, "Couldn't create OpenAL context.\n");
        return 1;
    }
    if (alcMakeContextCurrent(context) != ALC_TRUE) {
        fprintf(stderr, "Couldn't make OpenAL context current.\n");
        return 1;
    }

    // Create a buffer and source.

    ALuint buffer = 0;
    alGenBuffers(1, &buffer);
    if (alGetError() != AL_NO_ERROR) {
        fprintf(stderr, "Couldn't generate buffer.\n");
        return 1;
    }

    ALuint source = 0;
    alGenSources(1, &source);
    if (alGetError() != AL_NO_ERROR) {
        fprintf(stderr, "Couldn't generate source.\n");
        return 1;
    }

    // Open the WAV file.

    FILE* fp = nullptr;
    fopen_s(&fp, "C:/Code/Games/Rile/Rile/data/sound/MenuConfirm.wav", "rb");
    if (fp == nullptr) {
        fprintf(stderr, "Could not open file for reading.\n");
        return 1;
    }

    printf("Hey, I survived initialisation!\n");

    fclose(fp);
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}