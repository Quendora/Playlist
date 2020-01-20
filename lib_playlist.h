#include <utility>
#include <vector>
#include <memory>

#include "playable.h"
#include "playlist.h"
#include "playmode.h"
#include "file.h"

class PlayerException : std::exception
{
public:
    //FIXME Jak zamiast override wpisze virtual to Clang krzyczy
    [[nodiscard]] const char *what() const noexcept override = 0;
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