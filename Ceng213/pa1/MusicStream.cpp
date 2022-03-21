#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
    Profile temp(email, username, plan);

    profiles.insertAtTheEnd(temp);
}

void MusicStream::deleteProfile(const std::string &email) {
    /* TODO */
    Node<Profile> *curr = profiles.getFirstNode();
    Node<Profile *> *temp, *head;
    Profile a = curr -> data;

    while(a.getEmail() != email) {
        curr = curr -> next;
        a = curr -> data;
    }

    
    temp = head = ((curr -> data).getFollowings()).getFirstNode();
        
    if(temp != NULL)
    {
        do
        {
            ((*(temp -> data)).getFollowers()).removeNode(&(curr -> data));
            temp = temp -> next;
        }while(temp != head);
    }


    temp = head = ((curr -> data).getFollowers()).getFirstNode();
        
    if(temp != NULL)
    {
        do
        {
            ((*(temp -> data)).getFollowings()).removeNode((&(curr -> data)));
            temp = temp -> next;
        }while(temp != head);
    }

    profiles.removeNode(curr);
}

void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
    Artist artist(artistName);

    artists.insertAtTheEnd(artist);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
    Node<Artist> *curr = artists.getFirstNode();
    Album *album = new Album(albumName);

    while((curr -> data).getArtistId() != artistId) curr = curr -> next;

    albums.insertAtTheEnd(*album);
    (curr -> data).addAlbum(&(albums.getLastNode() -> data));
    delete album;
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
    Node<Album> *album = albums.getFirstNode();
    Song *song = new Song(songName, songDuration);

    while((album -> data).getAlbumId() != albumId) album = album -> next;

    songs.insertAtTheEnd(*song);
    (album -> data).addSong(&(songs.getLastNode() -> data));
    delete song;
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile> *user1, *user2, *curr = profiles.getFirstNode();
    Profile a, b, c;

    user1 = user2 = curr;
    a = b = c = curr -> data;

    while(a.getEmail() != email1 || b.getEmail() != email2)
    {
        if(c.getEmail() == email1) {
            user1 = curr;
            a = curr -> data;
        }

        else if(c.getEmail() == email2){ 
            user2 = curr;
            b = curr -> data;
        }

        curr = curr -> next;
        c = curr -> data;
    }

    (user1 -> data).followProfile(&(user2 -> data));

}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    Node<Profile> *user1, *user2, *curr = profiles.getFirstNode();
    Profile a, b, c;

    user1 = user2 = curr;
    a = b = c = curr -> data;

    while(a.getEmail() != email1 || b.getEmail() != email2)
    {
        if(c.getEmail() == email1) {
            user1 = curr;
            a = curr -> data;
        }

        else if(c.getEmail() == email2){ 
            user2 = curr;
            b = curr -> data;
        }

        curr = curr -> next;
        c = curr -> data;
    }

    (user1 -> data).unfollowProfile(&(user2 -> data));
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();

    while((profile -> data).getEmail() != email) profile = profile -> next;

    (profile -> data).createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();

    while((profile -> data).getEmail() != email) profile = profile -> next;

    (profile -> data).deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();
    Playlist *playlist;
    Node<Song> *song = songs.getFirstNode();

    while((song -> data).getSongId() != songId) song = song -> next;

    while((profile -> data).getEmail() != email) profile = profile -> next;

    playlist = (profile -> data).getPlaylist(playlistId);

    (*playlist).addSong(&(song -> data));
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();
    Playlist *playlist;
    Node<Song *> *song;

    while((profile -> data).getEmail() != email) profile = profile -> next;

    playlist = (profile -> data).getPlaylist(playlistId);

    song = ((*playlist).getSongs()).getFirstNode();

    while((*(song -> data)).getSongId() != songId) song = song -> next;

    (*playlist).dropSong(song -> data);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();
    LinkedList<Song *> list;

    while((profile -> data).getEmail() != email) profile = profile -> next;

    list = (*playlist).getSongs();

    if((profile -> data).getPlan() == free_of_charge) list.insertAsEveryKthNode(&(Song::ADVERTISEMENT_SONG), 2);

    return list;
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();

    while((profile -> data).getEmail() != email) profile = profile -> next;

    return (profile -> data).getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();

    while((profile -> data).getEmail() != email) profile = profile -> next;

    return (profile -> data).getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();

    while((profile -> data).getEmail() != email) profile = profile -> next;

    (profile -> data).shufflePlaylist(playlistId, seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();
    Profile a = profile -> data;

    while(a.getEmail() != email) 
    {
        profile = profile -> next;
        a = profile -> data;
    }

    (profile -> data).sharePlaylist(playlistId);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();
    Profile a = profile -> data;

    while(a.getEmail() != email) 
    {
        profile = profile -> next;
        a = profile -> data;
    }

    (profile -> data).unsharePlaylist(playlistId);
}

void MusicStream::subscribePremium(const std::string &email) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();

    while((profile -> data).getEmail() != email) profile = profile -> next;

    (profile -> data).setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {
    /* TODO */
    Node<Profile> *profile = profiles.getFirstNode();

    while((profile -> data).getEmail() != email) profile = profile -> next;

    (profile -> data).setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
