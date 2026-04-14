#include<raylib.h>
#include<stdlib.h>
#include<stdbool.h>
#include"constants.h"
#include"gb_palette.h"
#include"game.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

static bool audio_init = false;
void resume_web_audio(void)
{
    EM_ASM({
        var ctx = null;        
        if (typeof GL !== 'undefined' && GL.context && GL.context.audioContext)
	  {
            ctx = GL.context.audioContext;
	  }
        if (!ctx && typeof window !== 'undefined')
	  {
            if (window.audioContext) ctx = window.audioContext;
            else if (window.AudioContext && window.audioContextInstance) ctx = window.audioContextInstance;
	  }
        if (!ctx && typeof Module !== 'undefined' && Module.audioContext)
	  {
            ctx = Module.audioContext;
	  }
        
        if (ctx && ctx.state === 'suspended')
	  {
            ctx.resume().then(function()
			      {
				console.log('[Audio] Context resumed');
			      }).catch(function(e) {
				  console.error('[Audio] Resume failed:', e);
				});
        }
	else if (ctx)
	  {
            console.log('[Audio] Context state:', ctx.state);
	  }
	else
	  {
            console.warn('[Audio] No AudioContext found');
	  }
    });
}
#endif


void run(void);
int main()
{
  srand(time(0));
  qsort(google_words, google_words_len, sizeof(char*), str_cmp);

  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Scrabrix");
#ifndef  __EMSCRIPTEN__
  InitAudioDevice();
#endif  
  SetExitKey(KEY_NULL);
  SetTargetFPS(30);
  
  init_map();
  init_game();
  load_fonts();
#ifndef __EMSCRIPTEN  
  load_audio();
#endif  
  while(!WindowShouldClose())
    {
     #ifdef __EMSCRIPTEN__
      if(!audio_init && (GetKeyPressed() != 0 || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
	{
	  InitAudioDevice();
	  resume_web_audio();     
	  load_audio();
	  audio_init = true;
	}
     #endif

      run();

#if PRINT_FPS== 1     
      static double last_time = 0;
      double now = GetTime();
      double dt = now - last_time;
      if (dt > 0.0)
	{
	  printf("FPS: %.1f\n", 1.0 / dt);
	}
      last_time = now;
#endif
      WaitTime(0);
    }
  free_game();
  unload_fonts();
  unload_audio();
  UnloadTexture(vignette_tex);
  UnloadTexture(scanlines_tex);
  CloseWindow();
  CloseAudioDevice();
  return 0;
}
void run()
{  
  if(IsKeyReleased(KEY_ESCAPE))
    {
      PlaySound(pause_sound);
      _pause = !_pause;
    }
  
  if(!_pause && !victory && !game_over)
    run_game();

  if(game_over  && IS_GAME_OVER_TIMER_DONE)
    {
      if(IsKeyReleased(KEY_R))
	{
	  reset_game();
	}
    }
  if(victory && victory_timer >= VICTORY_PROMPT_START)
    {
      if(IsKeyReleased(KEY_R))
	{
	  reset_game();
	}
    }
  
  BeginDrawing();
  ClearBackground(GB_DMG_DARKEST);
  draw_game();
  if(game_over)
    draw_game_over();
  if(victory)
    draw_victory();
  EndDrawing();

}
