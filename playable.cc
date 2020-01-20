#include "playable.h"

#include <iostream>

Media::Media(const MetadataMap& metadata, const std::string& content) 
  : content(content), metadata(metadata) {}

Song::Song(const MetadataMap& metadata, const std::string& content)
  : Media(metadata, content) {
    if(this->metadata.find("title") == this->metadata.end() || this->metadata.find("year") == this->metadata.end()) {
      //throw exception
    }
  }

Movie::Movie(const MetadataMap& metadata, const std::string& content)
  : Media(metadata, content) {
    if(this->metadata.find("title") == this->metadata.end() || this->metadata.find("year") == this->metadata.end()) {
      //throw exception
    }
  }

void Song::play() {
  std::cout << "testing song: " << metadata["title"] << std::endl << content << std::endl;
}

void Movie::play() {
  std::cout << "testing movie: " << metadata["title"] << std::endl << content << std::endl;
}