#include "playlist.h"
#include "exception.h"

#include <iostream>

Playlist::Playlist(const std::string& playListName) {
  this->name = playListName;
  this->mode = std::make_shared<SequenceMode>();
}

void Playlist::add(const std::shared_ptr<Playable>& playable) {
  if (checkForCycleBeforeAdding(playable)) {
    throw CycleFound();
  }

  playables.push_back(playable);
}

void Playlist::add(const std::shared_ptr<Playable>& playable, unsigned int position) {
  if (position > playables.size()) {
    throw PlaylistOutOfRange();
  }
  if (checkForCycleBeforeAdding(playable)) {
    throw CycleFound();
  }
  playables.insert(playables.begin() + position, playable);
}

void Playlist::remove() {
  playables.pop_back();
}

void Playlist::remove(unsigned int position) {
  if (position >= playables.size()) {
    throw PlaylistOutOfRange();
  }
  playables.erase(playables.begin() + position);
}

void Playlist::setMode(const std::shared_ptr<PlayMode> playMode) {
  this->mode = playMode;
}

void Playlist::play() {
  std::cout << "Playlist [" + name + "]\n";
  mode->play_mode(playables);
}

bool Playlist::checkForCycleBeforeAdding(const std::shared_ptr<Playable>& playable) {
  return playable->checkForCycle(this);
}

bool Playlist::checkForCycle(const Playable* const playable) const {
  if (this == playable) {
    return true;
  }

  for (const auto& el : playables) {
    if (el->checkForCycle(playable)) {
      return true;
    }
  }

  return false;
}
