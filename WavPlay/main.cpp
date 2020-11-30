#include <cstdio>
#include <vector>
#include <AL/AL.h>
#include <AL/ALC.h>
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

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

    drwav wav;
    if (!drwav_init_file(&wav, "C:/Code/Games/Rile/Rile/data/sound/MenuConfirm.wav", nullptr)) {
        fprintf(stderr, "Couldn't load file for reading.\n");
        return 1;
    }

    // Read the PCM data, and then load that into the buffer.

    std::vector<int16_t> sampleData;
    sampleData.resize(wav.totalPCMFrameCount * wav.channels);
    const auto framesRead = drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, sampleData.data());
    if (framesRead != wav.totalPCMFrameCount) {
        fprintf(stderr, "Couldn't read file.\n");
    }

    printf("Channels: %d\n", wav.channels);
    printf("Bits Per Sample: %d\n", wav.bitsPerSample);
    printf("Sample Rate: %u\n", wav.sampleRate);

    const ALenum format = wav.channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    alBufferData(buffer, format, sampleData.data(), static_cast<ALsizei>(sampleData.size() * sizeof(int16_t)), wav.sampleRate);
    if (alGetError() != AL_NO_ERROR) {
        fprintf(stderr, "Could not buffer data.\n");
        return 1;
    }

    alSourcei(source, AL_BUFFER, buffer);
    int sourceState;
    alSourcePlay(source);
    do {
        alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
    } while (sourceState == AL_PLAYING);

    drwav_uninit(&wav);
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcDestroyContext(context);
    alcCloseDevice(device);

    return 0;
}