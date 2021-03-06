/*
 *
 * This file is part of JAG, Puzzle game where the goal is to break all
 * the target pieces in each level and do this before the time runs out.
 *
 * Many thanks to XlabSoft & Ind. Infosystems, the originals authors of JAG.
 *
 * Copyright holder 2009-2012 Developed by XlabSoft & Industrial Infosystems
 * Work continued by 2017 Carlos Donizete Froes [a.k.a coringao]
 *
 * JAG is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * JAG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JAG. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "gamesound.h"
#include "gamewidget.h"

#include <QDebug>

GameSound* sndEngine = 0;

GameSound::GameSound()
{
  // load sounds
  QString sndpath = GameWidget::getResourcePath() + "sounds/";

  loadSound(sndpath + "disappear.wav");
  loadSound(sndpath + "smallhammer.wav");
  loadSound(sndpath + "unblock.wav");
  loadSound(sndpath + "hammer.wav");
  loadSound(sndpath + "bighammer.wav");
  loadSound(sndpath + "bomb.wav");
  loadSound(sndpath + "row.wav");
  loadSound(sndpath + "randomkill.wav");
  loadSound(sndpath + "mixer.wav");
  loadSound(sndpath + "twin.wav");
  loadSound(sndpath + "clock.wav");
  loadSound(sndpath + "bonusend.wav");
  loadSound(sndpath + "newitem.wav");
  loadSound(sndpath + "target.wav");
  loadSound(sndpath + "levelstart.wav");
  loadSound(sndpath + "levelfail.wav");
  loadSound(sndpath + "levelwon.wav");
  loadSound(sndpath + "beep.wav");
  loadSound(sndpath + "bonus.wav");
  loadSound(sndpath + "newtool.wav");

  // music
  music = 0;
  musicEnabled = false;
  musicPlaying = false;

  myTimer = new QTimer(this);
  myTimer->setInterval(1000);
  connect(myTimer, SIGNAL(timeout()), this, SLOT(checkPlayMusic()));
  myTimer->stop();

  // setup volume
  setChannelVolume(MIX_MAX_VOLUME);
  setMusicVolume(MIX_MAX_VOLUME/4);
}

GameSound::~GameSound()
{
  Mix_HaltMusic();

  for (int i = 0; i < m_sounds.count(); i++)
  {
    Mix_FreeChunk(m_sounds.at(i));
  }

  Mix_FreeMusic(music);
}

Mix_Chunk* GameSound::loadSound(const QString &filename)
{
  Mix_Chunk *sound = Mix_LoadWAV(filename.toLocal8Bit().constData());

  if(sound == NULL)
  {
    qDebug() << "Unable to load WAV file: " << Mix_GetError();
  }

  m_sounds.append(sound);

  return sound;
}

void GameSound::playSound(int index, int /*loops*/)
{
    if (index >= 0 && index < m_sounds.count())
    {
      Mix_Chunk *chunk = m_sounds.at(index);
      if (!chunk)
        return;

      Mix_VolumeChunk(chunk, channel_vol);

      int channel = Mix_PlayChannel(-1, chunk, 0);
      if(channel == -1)
      {
        //qDebug() << "Unable to play sound file: " << Mix_GetError();
        //return;
      }
      else
        Mix_Volume(channel, channel_vol);
    }
}

void GameSound::stopSound(int /*index*/)
{
//    if (index >= 0 && index < m_sounds.count())
//        m_sounds.at(index)->stop();
}

void GameSound::stopAllSounds()
{
//    for (int i = 0; i <  m_sounds.count(); i++)
//        m_sounds.at(i)->stop();
}

void GameSound::setChannelVolume(int val, int ch)
{
//  if (ch < 0)
//    for (int i = 0; i < 8; i++)
//      Mix_Volume(i, val);
//  else
    Mix_Volume(ch, val);
//
//  if (ch==-1)
    channel_vol = val;
}

void GameSound::loadMusic(const QString &filename)
{
  if (music)
    Mix_FreeMusic(music);

  music = Mix_LoadMUS(filename.toLocal8Bit().constData());

  if(music == NULL)
  {
    qDebug() << "Music not loaded: " << Mix_GetError();
    return;
  }

}

void GameSound::playMusic()
{
  musicPlaying = true;

  if (!musicEnabled)
    return;

  int channel = Mix_PlayMusic(music, 0);
  if(channel == -1)
  {
    qDebug() << "Unable to play music file: " << Mix_GetError();
    return;
  }

  Mix_VolumeMusic(music_vol);
  myTimer->start();
}

void GameSound::stopMusic()
{
  Mix_HaltMusic();
  musicPlaying = false;
  myTimer->stop();
}

void GameSound::enableMusic(bool on)
{
  musicEnabled = on;
  if (musicEnabled)
  {
    if (musicPlaying)
      playMusic();
  }
  else
  {
    Mix_HaltMusic();
    myTimer->stop();
    // do NOT set musicPlaying to false!
  }
}

void GameSound::checkPlayMusic()
{
  // just rewind
  if (!Mix_PlayingMusic())
    //playMusic();
    emit musicFinished();
}

void GameSound::setMusicVolume(int val)
{
  music_vol = val;
  Mix_VolumeMusic(val);
}
