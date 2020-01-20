#include "playable.h"

#include <iostream>

Media::Media(const std::unordered_map<std::string, std::string>& metadata, const std::string& content) 
  : content(content), metadata(metadata) {}

Song::Song(const std::unordered_map<std::string, std::string>& metadata, const std::string& content)
  : Media(metadata, content) {}

Movie::Movie(const std::unordered_map<std::string, std::string>& metadata, const std::string& content)
  : Media(metadata, content) {}

void Song::play() {
  std::cout << "testing song: " << metadata["title"] << std::endl << content << std::endl;
}

void Movie::play() {
  std::cout << "testing movie: " << metadata["title"] << std::endl << content << std::endl;
}