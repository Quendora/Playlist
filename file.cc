#include "file.h"

File::File(const std::string &fileString) {
  if (!validateFileString(fileString)) {
    //jakies lepsze exception?
    //throw PlayerException();
  }
  extractData(fileString);

  //if (!validateMetadata()) { //lol gdzies to zgubiłem xd
    //thron exception
  //}
}

std::shared_ptr<Media> File::generateMedia() {
  std::shared_ptr<Media> media;

  switch (media_type)
  {
  case VIDEO:
    //zrobic ROT13
    media = std::make_shared<Movie>(metadata, content);
    break;

  case AUDIO:
    media = std::make_shared<Song>(metadata, content);
    break;
  }

  return media;
}

std::string File::getSupportedMediaType() const {
  static std::string audio = "audio"; //czy to mozna zrobic jakos lepiej? cos jak ala styczne pole w klasie? potem potrzebuje to samo przy extract data
  static std::string video = "video";

  static std::string supportedMediaType = audio + "|" + video;
  return supportedMediaType;
}

bool File::validateFileString(const std::string &fileString)
{
  static std::regex rgx("^(video|audio)\\|([^\\|]+:[^|]*\\|){2,}[^\\|]+$"); //czy w metadanych moze byc ':' (w nazwie albo wartosci)?
  return std::regex_match(fileString, rgx);
}

void File::extractData(std::string fileString) { //przekazujemy string przez wartość, poniewaz bedziemy go niszczyc
  static std::string audio = "audio";
  static std::string video = "video";
  static std::string delimiter = "|";
  static std::string metadataDelimiter = ":";
  size_t pos = 0, metaPos = 0;

  //extracting media type
  pos = fileString.find(delimiter);
  std::string media_type_str = fileString.substr(0, pos);
  if (media_type_str.compare(audio)) {
    media_type = AUDIO;
  }
  else if (media_type_str.compare(video)) {
    media_type = VIDEO;
  }
  fileString.erase(0, pos + delimiter.length());

  //extracting metadata
  std::string meta;
  while ((pos = fileString.find(delimiter)) != std::string::npos) {
    meta = fileString.substr(0, pos);
    metaPos = meta.find(metadataDelimiter);

    std::string name = meta.substr(0, metaPos);
    std::string data = meta.substr(metaPos + metadataDelimiter.length(), meta.length() - 1);
    metadata.insert({name, data});

    fileString.erase(0, pos + delimiter.length());
  }

  //remaining string is content
  content = fileString;
}