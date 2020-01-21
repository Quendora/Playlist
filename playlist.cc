#include "playlist.h"

Playlist::Playlist(const std::string& playListName) {
  this->name = playListName;
  this->mode = std::make_shared<SequenceMode>();
}

void Playlist::add(const std::shared_ptr<Playable>& playable) {
  playables.push_back(playable);
}

void Playlist::add(const std::shared_ptr<Playable>& playable, unsigned int position) {
  playables.insert(playables.begin() + position, playable);
}

void Playlist::remove() {
  playables.pop_back();
}

void Playlist::remove(unsigned int position) {
  playables.erase(playables.begin() + position);
}

void Playlist::setMode(std::shared_ptr<PlayMode> playMode) {
  //czy tutaj moze byc move
  this->mode = std::move(playMode);
}

void Playlist::play() {
  mode->play_mode(playables);
}