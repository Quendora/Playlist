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
    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override
    {
        for (const std::shared_ptr<Playable>& playable: playables)
        {
            playable->play();
        }
    }
};

class ShuffleMode : public PlayMode
{
public:
    ShuffleMode(int seed) : random_engine(seed) {}

    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override
    {   
        std::vector<size_t> indexes(playables.size());
        std::iota(indexes.begin(), indexes.end(), 0);

        std::shuffle(indexes.begin(), indexes.end(), random_engine);
        for(const auto& i: indexes) {
            playables[i]->play();
        }
    }

private:
    std::default_random_engine random_engine;
};

class OddEvenMode : public PlayMode
{
public:
    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override
    {
        for (unsigned long i = 1; i < playables.size(); i += 2)
        {
            playables[i]->play();
        }

        for (unsigned long i = 0; i < playables.size(); i += 2)
        {
            playables[i]->play();
        }
    }
};

/*std::shared_ptr<ShuffleMode> createShuffleMode(int seed)
{
    return std::make_shared<ShuffleMode>(seed);
}

std::shared_ptr<OddEvenMode> createOddEvenMode()
{
    //to samo co w seq?
    return std::make_shared<OddEvenMode>();
}

std::shared_ptr<SequenceMode> createSequenceMode()
{
    //statyczna zmienna i ja zwracac?
    return std::make_shared<SequenceMode>();
}*/

#endif