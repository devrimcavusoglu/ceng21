#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
}

void MusicStream::deleteProfile(const std::string &email) {
    /* TODO */
}

void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    /* TODO */
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    /* TODO */
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    /* TODO */
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    /* TODO */
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    /* TODO */
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    /* TODO */
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
}

void MusicStream::subscribePremium(const std::string &email) {
    /* TODO */
}

void MusicStream::unsubscribePremium(const std::string &email) {
    /* TODO */
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getSize() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of artists is " << artists.getSize() << ":" << std::endl;
    artists.print();

    std::cout << "# Number of albums is " << albums.getSize() << ":" << std::endl;
    albums.print();

    std::cout << "# Number of songs is " << songs.getSize() << ":" << std::endl;
    songs.print();

    std::cout << "# Printing is done." << std::endl;
}
