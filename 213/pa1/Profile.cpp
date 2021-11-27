#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    // Update `profile` followers as well
    LinkedList<Profile *> p_followers = profile->getFollowers();
    p_followers.insertAtTheEnd(this);

    // Add to current user's followings
    following.insertAtTheEnd(profile);
}

void Profile::unfollowProfile(Profile *profile) {
    // Update `profile` followers as well
    LinkedList<Profile *> p_followers = profile->getFollowers();
    p_followers.removeNode(this);

    // Remove also from curret user's following 
    following.removeNode(profile);
}

void Profile::createPlaylist(const std::string &playlistName) {
    Playlist new_playlist = Playlist(playlistName);
    playlists.insertAtTheEnd(new_playlist);
}

void Profile::deletePlaylist(int playlistId) {
    Node<Playlist> *selected_playlist = playlists.getNodeAtIndex(playlistId);
    playlists.removeNode(selected_playlist->data);
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    Node<Playlist> *selected_playlist = playlists.getNodeAtIndex(playlistId-1);
    selected_playlist->data.addSong(song);
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    Node<Playlist> *selected_playlist = playlists.getNodeAtIndex(playlistId-1);
    selected_playlist->data.dropSong(song);
}

Playlist *Profile::getPlaylist(int playlistId) {
    Node<Playlist> *selected_playlist = playlists.getNodeAtIndex(playlistId-1);
    return &selected_playlist->data;
}

LinkedList<Playlist *> Profile::getSharedPlaylists() {
    LinkedList<Playlist *> *shared_playlist = new LinkedList<Playlist *>;
    Node<Playlist> *current_pl = playlists.getFirstNode();

    do {
        if (current_pl->data.isShared()) 
            shared_playlist->insertAtTheEnd(&current_pl->data);
        current_pl = current_pl->next;
    } while (current_pl != playlists.getFirstNode());
    return *shared_playlist;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    Node<Playlist> *selected_playlist = playlists.getFirstNode();
    selected_playlist->data.shuffle(seed);
}

void Profile::sharePlaylist(int playlistId) {
    Node<Playlist> *selected_playlist = playlists.getNodeAtIndex(playlistId-1);
    selected_playlist->data.setShared(true);
}

void Profile::unsharePlaylist(int playlistId) {
    Node<Playlist> *selected_playlist = playlists.getNodeAtIndex(playlistId-1);
    selected_playlist->data.setShared(false);
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
