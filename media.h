#ifndef MEDIA_H
#define MEDIA_H

#include <SDL.h>
#include <SDL_mixer.h>

struct SoundManager {
    Mix_Chunk* startButtonSound;
    Mix_Chunk* exitButtonSound;
    Mix_Chunk* hitEnemySound;
    Mix_Chunk* winSound;
    Mix_Chunk* loseSound;

    // Biến để kiểm soát việc phát âm thanh một lần
    bool startButtonSoundPlayed;
    bool exitButtonSoundPlayed;
    bool winSoundPlayed;
    bool loseSoundPlayed;

    SoundManager(Mix_Chunk* _startButtonSound, Mix_Chunk* _exitButtonSound,
                 Mix_Chunk* _hitEnemySound, Mix_Chunk* _winSound, Mix_Chunk* _loseSound);

    void playStartButtonSound();
    void playExitButtonSound();
    void playHitEnemySound();
    void playWinSound();
    void playLoseSound();

    void resetSoundStates();
};

#endif // MEDIA_H
