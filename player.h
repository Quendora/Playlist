#pragma once

#include <memory>
#include <unordered_map>

#include "file.h"
#include "playable.h"
#include "playlist.h"

class Player {
public:
  Player();

  std::shared_ptr<Media> openFile(const File& file);

  std::shared_ptr<Playlist> createPlaylist(const std::string& name);

private:
  void registerMediaTypes();

  std::unordered_map<std::string, std::function<std::shared_ptr<Media>(const MetadataMap&,
                                                                       const std::string&)>> supportedMedia;
};