#include <utility>
#include <vector>
#include <random>
#include <memory>
#include <algorithm>
#include <regex>
#include <unordered_map>

//TODO (INFO) IMPLEMENTUJEMY ZAIMPLEMENTOWAC WZORZEC 'COMPOSITE'

class PlayerException : std::exception
{
public:
    //FIXME Jak zamiast override wpisze virtual to Clang krzyczy
    [[nodiscard]] const char *what() const noexcept override = 0;
};

class Playable
{
public:
    virtual void play() = 0;
};

class PlayMode
{
public:
    virtual void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) = 0;
};


class SequenceMode : public PlayMode
{
public:
    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override
    {
        for (const std::shared_ptr<Playable>& playable: playables)
        {
            playable->play();
        }
    }
};

class ShuffleMode : public PlayMode
{
public:
    ShuffleMode(int seed) : random_engine(seed) {}

    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override
    {   
        std::vector<size_t> indexes(playables.size());
        std::iota(indexes.begin(), indexes.end(), 0);

        std::shuffle(indexes.begin(), indexes.end(), random_engine);
        for(const auto& i: indexes) {
            playables[i]->play();
        }
    }

private:
    std::default_random_engine random_engine;
};

class OddEvenMode : public PlayMode
{
public:
    void play_mode(const std::vector<std::shared_ptr<Playable>> &playables) override
    {
        for (unsigned long i = 1; i < playables.size(); i += 2)
        {
            playables[i]->play();
        }

        for (unsigned long i = 0; i < playables.size(); i += 2)
        {
            playables[i]->play();
        }
    }
};

class File
{
public:
    File(std::string& fileString) {
        if(validateFileString(fileString)) {
            //jakies lepsze exception?
            //throw PlayerException();
        }
        extractData(fileString);
    }

private:
    enum MediaType {
        VIDEO,
        AUDIO
    };

    std::string getSupportedMediaType() {     
        static std::string audio = "audio"; //czy to mozna zrobic jakos lepiej? cos jak ala styczne pole w klasie? potem potrzebuje to samo przy extract data
        static std::string video = "video";
          
        static std::string supportedMediaType = audio + "|" + video;
        return supportedMediaType;        
    }

    bool validateFileString(std::string& fileString) {
        static std::regex rgx("^(video|audio)\\|([^\\|]+:[^|]*\\|){2,}[^\\|]+$"); //czy w metadanych moze byc ':' (w nazwie albo wartosci)?
        return std::regex_match(fileString, rgx);
    }

    void extractData(std::string fileString) { //przekazujemy string przez wartość, poniewaz bedziemy go niszczyc
        static std::string audio = "audio";
        static std::string video = "video";
        static std::string delimiter = "|";
        static std::string metadataDelimiter = ":";
        size_t pos = 0, metaPos = 0;

        //extracting media type
        pos = fileString.find(delimiter);
        std::string media_type_str = fileString.substr(0, pos);
        if(media_type_str.compare(audio)) {
            media_type = AUDIO;
        }
        else if(media_type_str.compare(video)) {
            media_type = VIDEO;
        }
        fileString.erase(0, pos + delimiter.length());

        //extracting metadata
        std::string meta;
        while((pos = fileString.find(delimiter)) != std::string::npos) {
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

    bool validateMetadata() {
        static std::string title = "title";
        static std::string artist = "artist";
        static std::string year = "year";

        switch (media_type)
        {
        case AUDIO:
            if(metadata.find(title) == metadata.end() || metadata.find(artist) == metadata.end()) {
                return false;
            }
            break;
        case VIDEO:
            if(metadata.find(title) == metadata.end() || metadata.find(year) == metadata.end()) {
                return false;
            }
            break;
        }
        return true;
    }

    MediaType media_type;
    std::unordered_map<std::string, std::string> metadata;
    std::string content;
};

class Song : public Playable
{
public:
    void play() override
    {

    }
};

class Movie : public Playable
{
public:
    void play() override
    {

    }
};

class Playlist : public Playable
{
public:

    explicit Playlist(std::string playListName)
    {
        // czy tutaj moze byc move
        this->name = std::move(playListName);
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

class Player
{
public:
    //File openFile(File file);

    std::shared_ptr<Playlist> createPlaylist(std::string name)
    {
        //tczy tutaj moze byc move
        return std::make_shared<Playlist>(Playlist(std::move(name)));
    }
};

std::shared_ptr<ShuffleMode> createShuffleMode(int seed)
{
    return std::make_shared<ShuffleMode>(seed);
}

std::shared_ptr<OddEvenMode> createOddEvenMode()
{
    //to samo co w seq?
    return std::make_shared<OddEvenMode>();
}

std::shared_ptr<SequenceMode> createSequenceMode()
{
    //statyczna zmienna i ja zwracac?
    return std::make_shared<SequenceMode>();
}