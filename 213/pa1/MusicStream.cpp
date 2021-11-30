#include "MusicStream.h"

#include <iostream>

Profile *MusicStream::findUser(const std::string &email) {
    Node<Profile> *profile = profiles.getFirstNode();
    do {
        if (profile->data.getEmail() == email) 
            break;
        profile = profile->next;
    } while (profile != profiles.getFirstNode());
    return &profile->data;
}

Album *MusicStream::findAlbum(const int &albumId) {
    Node<Album> *album = albums.getFirstNode();
    do {
        if (album->data.getAlbumId() == albumId) 
            break;            
    } while (album != albums.getFirstNode());
    return &album->data;
}

Artist *MusicStream::findArtist(const int &artistId) {
    Node<Artist> *artist = artists.getFirstNode();
    do {
        if (artist->data.getArtistId() == artistId) 
            break;
    } while (artist != artists.getFirstNode());
    return &artist->data;
}


Song *MusicStream::findSong(const int &songId) {
    Node<Song> *song = songs.getFirstNode();
    do {
        if (song->data.getSongId() == songId) 
            break;
    } while (song != songs.getFirstNode());
    return &song->data;
}

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    Profile profile = Profile(email, username, plan);
    profiles.insertAtTheEnd(profile);
}

void MusicStream::deleteProfile(const std::string &email) {   
    Profile *profile_to_be_deleted = findUser(email);

    // Delete the profile from followers
    Node<Profile *> *follower = profile_to_be_deleted->getFollowers().getFirstNode();
    do {
        follower->data->getFollowings().removeNode(profile_to_be_deleted);
    } while (follower != profile_to_be_deleted->getFollowers().getFirstNode());

    // Delete the profile from followings' followers' 
    Node<Profile *> *following = profile_to_be_deleted->getFollowings().getFirstNode();
    do {
        following->data->getFollowers().removeNode(profile_to_be_deleted);
    } while (following != profile_to_be_deleted->getFollowings().getFirstNode());

    // Remove the profile from profiles
    profiles.removeNode(*profile_to_be_deleted);
}

void MusicStream::addArtist(const std::string &artistName) {
    Artist artist = Artist(artistName);
    artists.insertAtTheEnd(artist);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    Album album = Album(albumName);
    albums.insertAtTheEnd(album);

    // Also, insert the song to the album
    Artist *artist = findArtist(artistId);
    Album *selected_album = findAlbum(album.getAlbumId());
    artist->addAlbum(selected_album);
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    Song song = Song(songName, songDuration);
    songs.insertAtTheEnd(song);

    // Also, insert the song to the album
    Album *album = findAlbum(albumId);
    Song *selected_song = findSong(song.getSongId());
    album->addSong(selected_song);
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    Profile *user_1 = findUser(email1);
    Profile *user_2 = findUser(email2);

    user_1->followProfile(user_2);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    Profile *user_1 = findUser(email1);
    Profile *user_2 = findUser(email2);

    user_1->unfollowProfile(user_2);
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    Profile *user = findUser(email);
    user->createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    Profile *user = findUser(email);
    user->deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    Profile *user = findUser(email);
    Song *song = findSong(songId);

    Playlist *playlist = user->getPlaylist(playlistId);
    playlist->addSong(song);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    Profile *user = findUser(email);
    Song *song = findSong(songId);

    Playlist *playlist = user->getPlaylist(playlistId);
    playlist->dropSong(song);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    Profile *user = findUser(email);

    if (user->getPlan() == premium)
        return playlist->getSongs();

    Song *ad_song = &Song::ADVERTISEMENT_SONG;
    playlist->getSongs().insertAsEveryKthNode(ad_song, 2);
    return playlist->getSongs();
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    Profile *user = findUser(email);
    return user->getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    Profile *user = findUser(email);
    Node<Profile *> *following = user->getFollowings().getFirstNode();

    LinkedList<Playlist *> shared_playlists;
    
    do {
        LinkedList<Playlist *> shared_playlist = user->getSharedPlaylists();
        Node<Playlist *> *current_pl = shared_playlist.getFirstNode();
        do {
            shared_playlists.insertAtTheEnd(current_pl->data);
            current_pl = current_pl->next;
        } while (current_pl != shared_playlist.getFirstNode());
    } while (following != user->getFollowings().getFirstNode());

    return shared_playlists;
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    Profile *user = findUser(email);
    user->shufflePlaylist(playlistId, seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    Profile *user = findUser(email);
    user->sharePlaylist(playlistId);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    Profile *user = findUser(email);
    user->sharePlaylist(playlistId);
}

void MusicStream::subscribePremium(const std::string &email) {
    Profile *user = findUser(email);
    user->setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {
    Profile *user = findUser(email);
    user->setPlan(free_of_charge);
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
