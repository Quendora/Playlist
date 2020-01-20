#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <memory>
#include <vector>

#include "playable.h"
#include "playmode.h"

class Playlist : public Playable
{
public:

    explicit Playlist(const std::string& playListName)
    {
        this->name = playListName;
        this->mode = std::make_shared<SequenceMode>();
    }

    void add(const std::shared_ptr<Playable>& playable)
    {
        playables.push_back(playable);
    }

    void add(const std::shared_ptr<Playable>& playable, unsigned int position)
    {
        playables.insert(playables.begin() + position, playable);
    }

    void remove()
    {
        playables.pop_back();
    }

    void remove(unsigned int position)
    {
        playables.erase(playables.begin() + position);
    }

    void setMode(std::shared_ptr<PlayMode> playMode)
    {
        //czy tutaj moze byc move
        this->mode = std::move(playMode);
    }

    void play() override
    {
        mode->play_mode(playables);
    }

private:
    std::string name;
    std::vector<std::shared_ptr<Playable>> playables;
    std::shared_ptr<PlayMode> mode;
};

#endif