#include "player.h"

Player::Player() {
  registerMediaTypes();
}

std::shared_ptr<Playlist> Player::createPlaylist(const std::string& name) {
  return std::make_shared<Playlist>(Playlist(name));
}

void Player::registerMediaTypes() {
  supportedMedia.insert({"audio", [](const auto& a, const auto& b){ return std::make_shared<Song>(a, b); }});
  supportedMedia.insert({"video", [](const auto& a, const auto& b){ return std::make_shared<Movie>(a, b); }});
}

std::shared_ptr<Media> Player::openFile(const File& file) {
  auto media = supportedMedia.find(file.getType());

  if(media == supportedMedia.end()) {
    //throw invalid type
  }

  return media->second(file.getMetadata(), file.getContent());
}