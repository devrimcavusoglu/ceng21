#include "MusicStream.h"

#include <iostream>

Profile *findUser(const std::string &email) {
    Profile *profile = profiles.head;
    do {
        if (profile->email == email) 
            return profile;
        profile = profile->next;
    } while (profile != profiles.head);
    return NULL;
}

Album *findAlbum(const int &albumId) {
    Album *album = albums.head;
    do {
        if (album.getAlbumId() == albumId) 
            return album;
    } while (album != albums.head);
    return NULL;
}

Artist *findArtist(const int &artistId) {
    Artist *artist = artists.head;
    do {
        if (artist.getArtistId() == artistId) 
            return artist;
    } while (artist != artists.head);
    return NULL;
}


Song *findSong(const int &songId) {
    Song *song = songs.head;
    do {
        if (song.getSongId() == songId) 
            return song;
    } while (song != songs.head);
    return NULL;
}

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    Profile *profile = new Profile(email, username, plan);
    profiles.insertAtTheEnd(profile);   
}

void MusicStream::deleteProfile(const std::string &email) {   
    Profile *profile_to_be_deleted = find(email);

    if (!profile_to_be_deleted)
        return;

    // Delete the profile from followers
    Profile *follower = profile_to_be_deleted.followers.head;
    do {
        follower.following.removeNode(profile_to_be_deleted);
    } while (follower != profile_to_be_deleted.followers.head);

    // Delete the profile from followings' followers' 
    Profile *following = profile_to_be_deleted.following.head;
    do {
        following.followers.removeNode(profile_to_be_deleted);
    } while (following != profile_to_be_deleted.following.head);

    // Remove the profile from profiles
    profiles.removeNode(profile_to_be_deleted);   
}

void MusicStream::addArtist(const std::string &artistName) {
    Artist *artist = new Artist(artistName);
    artists.insertAtTheEnd(artist);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    Album *album = new Album(albumName);
    albums.insertAtTheEnd(album);

    // Also, insert the song to the album
    Artist *artist = findArtist(artistName);
    if (!artist)
        return;
    artist.addAlbum(album);
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    Song *song = new Song(songName, songDuration);
    songs.insertAtTheEnd(song);

    // Also, insert the song to the album
    Album *album = findAlbum(albumId);
    if (!album)
        return;
    album.addSong(song);
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    Profile *user_1 = findUser(email1);
    Profile *user_2 = findUser(email2);

    user1.followProfile(user_2);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    Profile *user_1 = findUser(email1);
    Profile *user_2 = findUser(email2);

    user1.followProfile(user_2);
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    Profile *user = findUser(email);
    user.createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    Profile *user = findUser(email);
    user.deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    Profile *user = findUser(email);
    Song *song = findSong(songId);

    Playlist *playlist = user.getPlaylist(playlistId);
    playlist.addSong(song);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    Profile *user = findUser(email);
    Song *song = findSong(songId);

    Playlist *playlist = user.getPlaylist(playlistId);
    playlist.dropSong(song);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    Profile *user = findUser(email);
    Playlist *playlist = user.getPlaylist(playlistId);

    if (user.getPlan() == SubscriptionPlan::premium)
        return playlist;

    Song *advertisement = new Song.ADVERTISEMENT_SONG;
    playlist.songs.insertAsEveryKthNode(2, advertisement);
    return playlist;
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    Profile *user = findUser(email);
    return user.getPlaylist(playlistId);
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
