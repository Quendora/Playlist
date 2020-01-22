#ifndef PLAYMODE_H
#define PLAYMODE_H

#include <vector>
#include <memory>
#include <algorithm>
#include <random>

#include "playable.h"

class PlayMode
{
public:
    virtual void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) = 0;
};

class SequenceMode : public PlayMode
{
public:
    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override;
};

class ShuffleMode : public PlayMode
{
public:
    ShuffleMode(int seed);
    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override;

private:
    std::default_random_engine random_engine;
};

class OddEvenMode : public PlayMode
{
public:
    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override;
};

std::shared_ptr<PlayMode> createShuffleMode(int seed);
std::shared_ptr<PlayMode> createOddEvenMode();
std::shared_ptr<PlayMode> createSequenceMode();

#endif