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
    float amplitude = 32600;

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
    float amplitude = 30000;  

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
    float duration = 0.07f; 
    int samples = (int)(sampleRate * duration);
    short* data = malloc(samples * sizeof(short));
    float freq = 660.0f;    
    float amplitude = 12000;

    for (int i = 0; i < samples; i++) {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.005f)
            envelope = t / 0.005f;            
        if (t > duration - 0.01f)
            envelope = (duration - t) / 0.01f;

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
    float note_dur = 0.05f;          
    float gap = 0.02f;               
    float total_dur = note_dur * 2 + gap;
    int samples = (int)(sampleRate * total_dur);
    short* data = calloc(samples, sizeof(short));

    float freqs[] = {550.0f, 720.0f};
    float amplitude = 10000;

    float start_time = 0.0f;
    for (int n = 0; n < 2; n++)
      {
        int start_sample = (int)(start_time * sampleRate);
        int end_sample = start_sample + (int)(note_dur * sampleRate);
        if (end_sample > samples) end_sample = samples;

        float freq = freqs[n];
        for (int i = start_sample; i < end_sample; i++)
	  {
            float t = (float)(i - start_sample) / sampleRate;
            float envelope = 1.0f;
            if (t < 0.003f)
                envelope = t / 0.003f;
            if (t > note_dur - 0.005f)
                envelope = (note_dur - t) / 0.005f;

            float value = sinf(2.0f * PI * freq * t) * envelope * amplitude;
            data[i] = (short)value;
        }
        start_time += note_dur + gap;
    }

    int fade_start = samples - (int)(0.01f * sampleRate);
    for (int i = fade_start; i < samples; i++)
      {
        float fade = (float)(samples - i) / (samples - fade_start);
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
Sound create_pause_sound(void)
{
    int sampleRate = 44100;
    float duration = 0.02f;  
    int samples = (int)(sampleRate * duration);
    short* data = malloc(samples * sizeof(short));

    float freq = 1000.0f;    
    float amplitude = 11000; 

    for (int i = 0; i < samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.002f)
            envelope = t / 0.002f;             
        if (t > duration - 0.002f)
            envelope = (duration - t) / 0.002f;

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
Sound create_victory_sound(void)
{
    int sampleRate = 44100;
    float note_dur = 0.11f;
    float gap = 0.015f;
    float freqs[] = {261.63f, 329.63f, 392.00f, 523.25f}; //C4, E4, G4, C5
    int note_count = 4;
    float total_dur = note_dur * note_count + gap * (note_count - 1);
    int samples = (int)(sampleRate * total_dur);
    short* data = calloc(samples, sizeof(short));

    float amplitude = 20000;

    for (int n = 0; n < note_count; n++)
      {
        float start_time = n * (note_dur + gap);
        int start_sample = (int)(start_time * sampleRate);
        int end_sample = start_sample + (int)(note_dur * sampleRate);
        if (end_sample > samples) end_sample = samples;

        float freq = freqs[n];
        for (int i = start_sample; i < end_sample; i++)
	  {
            float t = (float)(i - start_sample) / sampleRate;
            float envelope = 1.0f;
            if (t < 0.005f)
                envelope = t / 0.005f;
            if (t > note_dur - 0.02f)
                envelope = (note_dur - t) / 0.02f;

            float value = 0.0f;
            float period = 1.0f / freq;
            float phase = fmod(t, period) / period;
            value = (phase < 0.5f) ? 1.0f : -1.0f;

            value *= amplitude * envelope;
            data[i] += (short)value;
        }
    }

    int last_note_start = (note_count - 1) * (note_dur + gap) * sampleRate;
    int echo_samples = (int)(0.1f * sampleRate);
    for (int i = last_note_start; i < samples && i - last_note_start < echo_samples; i++)
      {
        data[i] = (short)(data[i] * 0.7f + data[i - (int)(0.05f * sampleRate)] * 0.3f);
      }

    int fade_start = samples - (int)(0.05f * sampleRate);
    for (int i = fade_start; i < samples; i++)
      {
        float fade = (float)(samples - i) / (samples - fade_start);
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
Sound create_game_over_sound(void)
{
    int sampleRate = 44100;
    float impact_dur = 0.06f;
    float descend_dur = 0.4f;
    int samples = (int)(sampleRate * (impact_dur + descend_dur));
    short* data = calloc(samples, sizeof(short));

    int impact_samples = (int)(sampleRate * impact_dur);
    float noise_amp = 8000;
    float tone_amp = 10000;
    float impact_freq = 180.0f;

    for (int i = 0; i < impact_samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.005f)
            envelope = t / 0.005f;
        if (t > impact_dur - 0.01f)
            envelope = (impact_dur - t) / 0.01f;

        float noise = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        float tone = sinf(2.0f * PI * impact_freq * t);

        float value = (noise * noise_amp + tone * tone_amp) * envelope;
        if (value > 32767) value = 32767;
        if (value < -32768) value = -32768;
        data[i] = (short)value;
    }

    int descend_samples = (int)(sampleRate * descend_dur);
    float start_freq = 220.0f;
    float end_freq = 80.0f;
    float amp = 25000;

    for (int i = 0; i < descend_samples; i++)
      {
        float t = (float)i / sampleRate;
        float envelope = 1.0f;
        if (t < 0.01f)
            envelope = t / 0.01f;
        if (t > descend_dur - 0.04f)
            envelope = (descend_dur - t) / 0.04f;

        float freq = start_freq - (start_freq - end_freq) * (t / descend_dur);
        float value = 0.0f;
        float period = 1.0f / freq;
        float phase = fmod(t, period) / period;
        if (phase < 0.25f)
            value = phase * 4.0f;
        else if (phase < 0.75f)
            value = 1.0f - (phase - 0.25f) * 4.0f;
        else
            value = (phase - 1.0f) * 4.0f;

        value *= amp * envelope;
        data[impact_samples + i] = (short)value;
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
