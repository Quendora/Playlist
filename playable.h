#ifndef PLAYABLE_H
#define PLAYABLE_H

#include <unordered_map>
#include "playlist.h"

using MetadataMap = std::unordered_map<std::string, std::string>;

class Playable
{
public:
    virtual void play() = 0;
    virtual bool checkForCycle(Playlist* playlist) = 0;
};

class Media : public Playable
{
public:
  Media(const MetadataMap& metadata, const std::string& content);
  virtual void play() = 0;

protected:
  std::string content;
  MetadataMap metadata;
  bool checkForCycle(Playlist* playlist) override;
};

class Song : public Media
{
public:
    Song(const MetadataMap& metadata, const std::string& content);
    void play() override;
};

class Movie : public Media
{
public:
    Movie(const MetadataMap& metadata, const std::string& content);
    void play() override;

private:
  std::string ROT13(const std::string& source);  
};

#endif