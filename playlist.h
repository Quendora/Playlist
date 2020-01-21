#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <memory>
#include <vector>

#include "playable.h"
#include "playmode.h"

class Playlist : public Playable
{
public:

    explicit Playlist(const std::string& playListName);

    void add(const std::shared_ptr<Playable>& playable);
    void add(const std::shared_ptr<Playable>& playable, unsigned int position);
    void remove();
    void remove(unsigned int position);
    void setMode(std::shared_ptr<PlayMode> playMode);
    void play() override;

private:
    std::string name;
    std::vector<std::shared_ptr<Playable>> playables;
    std::shared_ptr<PlayMode> mode;
};

#endif