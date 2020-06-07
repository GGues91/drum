#ifndef WAVE_H
#define WAVE_H
#include <stdint.h>

typedef struct  wave_spec_t  wave_spec_t;
typedef struct       wave_t       wave_t;
typedef struct wave_mixer_t wave_mixer_t;

int wave_read (wave_t *wave, char *name);
int wave_write(wave_t *wave, char *name);
int wave_domix(wave_mixer_t *dest, wave_t *src);

struct wave_spec_t{
  int rate;     //rate of sampling
  int depth;    //  bit per sample
  int channels; //count of channel
};
struct wave_t{
  int8_t     *samples;
  uint32_t    length;
  wave_spec_t spec;
};
/*
  comments about struct??
*/
struct wave_mixer_t{
  wave_t      wave;
  wave_spec_t spec; //what's this spec for? i don't find how it is to be used...
                    //i see wave_read() and wave_write() use it wave_domix() does not
                    //so it's the spec of the wave?? no no no that's wave_t not wave_mixer_t nevermind
                    //i think this member is unused...
  uint32_t    allocated; //true length of wave.samples, length being from 0th index to last sample's index
  uint32_t    offset; //TODO: make offset an uint32_t (noiser: easier arithmetic)
                   //DONE: but look here if bug occurs, made changes in wmix() (previous int8_t *)
}; //chunk of data written to at arbitrary locations denoted by offset

#endif
