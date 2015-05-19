#include "common.h"

#include <al.h>
#include <alc.h>

#include <sndfile.h>

using namespace std;

ALuint LoadSound(const std::string& Filename)
{
  SF_INFO FileInfos;
  SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
  if (!File)
    return 0;

  ALsizei NbSamples = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
  ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);
  vector<ALshort> Samples(NbSamples);
  if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
    return 0;
  sf_close(File);
  ALenum Format;
  switch (FileInfos.channels)
  {
  case 1:  Format = AL_FORMAT_MONO16;   break;
  case 2:  Format = AL_FORMAT_STEREO16; break;
  default: return 0;
  }
  ALuint Buffer;
  alGenBuffers(1, &Buffer);
  alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

  if (alGetError() != AL_NO_ERROR)
    return 0;

  return Buffer;
}

ALuint Source;

void init_sound() {
  ALCdevice* Device = alcOpenDevice(NULL);
  ALCcontext* Context = alcCreateContext(Device, NULL);
  alcMakeContextCurrent(Context);

  ALuint buffer = LoadSound(sourcePath() + "/data/sound/" + "boing.wav");

  alGenSources(1, &Source);
  alSourcei(Source, AL_BUFFER, buffer);
}

void play_sound(){
  alSourcePlay(Source);
 
}

void rewind_sound() {
  alSourceRewind(Source);
}
