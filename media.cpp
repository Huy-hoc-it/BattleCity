#include "media.h"
#include <iostream>

SoundManager::SoundManager(Mix_Chunk* _startButtonSound, Mix_Chunk* _exitButtonSound,
                           Mix_Chunk* _hitEnemySound, Mix_Chunk* _winSound, Mix_Chunk* _loseSound)
    : startButtonSound(_startButtonSound), exitButtonSound(_exitButtonSound),
      hitEnemySound(_hitEnemySound), winSound(_winSound), loseSound(_loseSound)
{
    startButtonSoundPlayed = false;
    exitButtonSoundPlayed = false;
    winSoundPlayed = false;
    loseSoundPlayed = false;

    // Tăng số kênh âm thanh
    Mix_AllocateChannels(16);

    // Điều chỉnh âm lượng
    if (startButtonSound) Mix_VolumeChunk(startButtonSound, MIX_MAX_VOLUME / 2);
    if (exitButtonSound) Mix_VolumeChunk(exitButtonSound, MIX_MAX_VOLUME / 2);
    if (hitEnemySound) Mix_VolumeChunk(hitEnemySound, MIX_MAX_VOLUME / 2);
    if (winSound) Mix_VolumeChunk(winSound, MIX_MAX_VOLUME / 2);
    if (loseSound) Mix_VolumeChunk(loseSound, MIX_MAX_VOLUME / 2);
}

void SoundManager::playStartButtonSound()
{
    if (!startButtonSoundPlayed && startButtonSound != nullptr)
    {
        Mix_PlayChannel(-1, startButtonSound, 0);
        startButtonSoundPlayed = true;
    }
}

void SoundManager::playExitButtonSound()
{
    if (!exitButtonSoundPlayed && exitButtonSound != nullptr)
    {
        Mix_PlayChannel(-1, exitButtonSound, 0);
        exitButtonSoundPlayed = true;
    }
}

void SoundManager::playHitEnemySound()
{
    if (hitEnemySound != nullptr)
    {
        Mix_PlayChannel(-1, hitEnemySound, 0);
    }
}

void SoundManager::playWinSound()
{
    if (!winSoundPlayed && winSound != nullptr)
    {
        Mix_PlayChannel(-1, winSound, 0);
        winSoundPlayed = true;
    }
}

void SoundManager::playLoseSound()
{
    if (!loseSoundPlayed && loseSound != nullptr)
    {
        Mix_PlayChannel(-1, loseSound, 0);
        loseSoundPlayed = true;
    }
}

void SoundManager::resetSoundStates()
{
    startButtonSoundPlayed = false;
    exitButtonSoundPlayed = false;
    winSoundPlayed = false;
    loseSoundPlayed = false;
}
