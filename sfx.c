#include "sfx.h"

Sound create_move_sound(void)
{
    int sampleRate = 44100;
    float duration = 0.05f;
    int samples = (int)(sampleRate * duration);
    short* data = malloc(samples * sizeof(short));

    float freq = 600.0f;   
    float amplitude = 25000;

    for (int i = 0; i < samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.005f)
            envelope = t / 0.005f;
        if (t > duration - 0.005f)
            envelope = (duration - t) / 0.005f;

        float value = sinf(2.0f * PI * freq * t) * envelope * amplitude;
        data[i] = (short)value;
    }

    Wave wave =
      {
        .data = data,
        .frameCount = samples,
        .sampleRate = sampleRate,
        .sampleSize = 16,
        .channels = 1
    };

    Sound sound = LoadSoundFromWave(wave);
    free(data);
    return sound;
}
Sound create_hard_drop_sound(void)
{
    int sampleRate = 44100;
    float duration = 0.12f; 
    int samples = (int)(sampleRate * duration);
    short* data = malloc(samples * sizeof(short));

    float start_freq = 150.0f;
    float end_freq = 80.0f; 
    float amplitude = 20000;

    for (int i = 0; i < samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.01f)
            envelope = t / 0.01f;
        if (t > duration - 0.02f)
            envelope = (duration - t) / 0.02f;
        float freq = start_freq - (start_freq - end_freq) * (t / duration);
        float value = sinf(2.0f * PI * freq * t) * envelope * amplitude;
        data[i] = (short)value;
    }

    Wave wave =
      {
        .data = data,
        .frameCount = samples,
        .sampleRate = sampleRate,
        .sampleSize = 16,
        .channels = 1
    };

    Sound sound = LoadSoundFromWave(wave);
    free(data);
    return sound;
}
Sound create_soft_land_sound(void)
{
    int sampleRate = 44100;
    float duration = 0.08f;   
    int samples = (int)(sampleRate * duration);
    short* data = malloc(samples * sizeof(short));

    float start_freq = 200.0f;
    float end_freq = 100.0f;
    float amplitude = 12000;  

    for (int i = 0; i < samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.008f)
            envelope = t / 0.008f;
        if (t > duration - 0.01f)
            envelope = (duration - t) / 0.01f;

        float freq = start_freq - (start_freq - end_freq) * (t / duration);
        float value = sinf(2.0f * PI * freq * t) * envelope * amplitude;
        data[i] = (short)value;
    }

    Wave wave =
      {
        .data = data,
        .frameCount = samples,
        .sampleRate = sampleRate,
        .sampleSize = 16,
        .channels = 1
    };

    Sound sound = LoadSoundFromWave(wave);
    free(data);
    return sound;
}
Sound create_word_found_sound(void)
{
    int sampleRate = 44100;
    float duration = 0.2f;
    int samples = (int)(sampleRate * duration);
    short* data = malloc(samples * sizeof(short));

    float start_freq = 400.0f;
    float end_freq = 800.0f;
    float amplitude = 20000;

    for (int i = 0; i < samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.02f)
            envelope = t / 0.02f;
        if (t > duration - 0.02f)
            envelope = (duration - t) / 0.02f;

        float freq = start_freq + (end_freq - start_freq) * (t / duration);
        float value = sinf(2.0f * PI * freq * t) * envelope * amplitude;
        data[i] = (short)value;
    }

    Wave wave =
      {
        .data = data,
        .frameCount = samples,
        .sampleRate = sampleRate,
        .sampleSize = 16,
        .channels = 1
    };

    Sound sound = LoadSoundFromWave(wave);
    free(data);
    return sound;
}
Sound create_word_erase_sound(void)
{
    int sampleRate = 44100;
    float duration = 0.18f; 
    int samples = (int)(sampleRate * duration);
    short* data = malloc(samples * sizeof(short));

    float start_freq = 550.0f;
    float end_freq = 80.0f;
    float sine_amp = 18000; 
    float noise_amp = 4000; 

    for (int i = 0; i < samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.01f)
            envelope = t / 0.01f;
        if (t > duration - 0.04f)
            envelope = (duration - t) / 0.04f;

        float freq = start_freq - (start_freq - end_freq) * (t / duration);
        float sine = sinf(2.0f * PI * freq * t) * sine_amp;

        float noise = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        noise *= noise_amp;

        float value = (sine + noise) * envelope;
        if (value > 32767) value = 32767;
        if (value < -32768) value = -32768;
        data[i] = (short)value;
    }

    Wave wave =
      {
        .data = data,
        .frameCount = samples,
        .sampleRate = sampleRate,
        .sampleSize = 16,
        .channels = 1
    };

    Sound sound = LoadSoundFromWave(wave);
    free(data);
    return sound;
}
Sound create_perfect_clear_sound(void)
{
    int sampleRate = 44100;
    float duration = 0.9f;
    int samples = (int)(sampleRate * duration);
    short* data = calloc(samples, sizeof(short));

    float freqs[] = {261.63f, 329.63f, 392.00f, 523.25f};
    int note_count = 4;
    float note_dur = 0.12f;
    float gap = 0.02f;     
    float total_note_time = note_dur + gap;
    float start_time = 0.0f;

    for (int n = 0; n < note_count; n++)
      {
        int start_sample = (int)(start_time * sampleRate);
        int end_sample = start_sample + (int)(note_dur * sampleRate);
        if (end_sample > samples) end_sample = samples;

        float freq = freqs[n];
        float amplitude = 20000;

        for (int i = start_sample; i < end_sample; i++)
	  {
            float t = (float)(i - start_sample) / sampleRate;
            float envelope = 1.0f;
            if (t < 0.01f)
                envelope = t / 0.01f;                
            else
                envelope = expf(-5.0f * (t - 0.01f));

            float value = sinf(2.0f * PI * freq * t) * envelope * amplitude;
            data[i] += (short)value;
        }
        start_time += total_note_time;
    }

    for (int i = samples - (int)(0.2f * sampleRate); i < samples; i++)
      {
        float t = (float)(i - (samples - (int)(0.2f * sampleRate))) / (0.2f * sampleRate);
        float fade = 1.0f - t; 
        data[i] = (short)(data[i] * fade);
    }

    Wave wave =
      {
        .data = data,
        .frameCount = samples,
        .sampleRate = sampleRate,
        .sampleSize = 16,
        .channels = 1
    };

    Sound sound = LoadSoundFromWave(wave);
    free(data);
    return sound;
}
Sound create_combo_sound(void)
{
    int sampleRate = 44100;
    float duration = 0.35f;
    int samples = (int)(sampleRate * duration);
    short* data = calloc(samples, sizeof(short));

    float bass_freq = 120.0f;
    float bass_amp = 12000;

    float chime_start = 400.0f;
    float chime_end = 800.0f;
    float chime_amp = 18000;

    for (int i = 0; i < samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.01f)
            envelope = t / 0.01f;
        else if (t > duration - 0.05f)
            envelope = (duration - t) / 0.05f;
        else
            envelope = 1.0f;
	
        float bass = sinf(2.0f * PI * bass_freq * t) * bass_amp;

        float chime_freq = chime_start + (chime_end - chime_start) * (t / duration);
        float chime = sinf(2.0f * PI * chime_freq * t) * chime_amp;

        float value = (bass * 0.6f + chime) * envelope;
        if (value > 32767) value = 32767;
        if (value < -32768) value = -32768;
        data[i] = (short)value;
    }

    Wave wave =
      {
        .data = data,
        .frameCount = samples,
        .sampleRate = sampleRate,
        .sampleSize = 16,
        .channels = 1
    };
    Sound sound = LoadSoundFromWave(wave);
    free(data);
    return sound;
}
