#include <iostream>

#include "MusicStream.h"

int main() {
    MusicStream ms;

    ms.print();

    ms.addProfile("john@doe.com", "john_doe", free_of_charge);

    //ms.print();

    ms.addProfile("abc@def", "abc", free_of_charge);
    ms.addProfile("g", "1", free_of_charge);
    ms.addProfile("h", "2", free_of_charge);
    ms.addProfile("i", "3", free_of_charge);
    ms.followProfile("abc@def", "john@doe.com");
    ms.followProfile("g", "john@doe.com");
    ms.followProfile("h", "john@doe.com");
    ms.followProfile("i", "john@doe.com");
    ms.followProfile("john@doe.com", "g");
    ms.followProfile("john@doe.com", "h");
    ms.followProfile("john@doe.com", "i");
    //ms.followProfile("abc@def", "john@doe.com");


    ms.addArtist("The Beatles");

    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Night", 1);

    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);

    ms.print();

    ms.deleteProfile("abc@def");
    ms.unfollowProfile("g", "john@doe.com");
    ms.unfollowProfile("john@doe.com", "i");
    ms.unfollowProfile("john@doe.com", "h");
    ms.deleteProfile("john@doe.com");

    ms.print();

    Profile a("123", "a", free_of_charge);
    Profile b("456", "b", free_of_charge);
    Profile c("789", "c", free_of_charge);

    a.followProfile(&b);
    c.followProfile(&b);
    b.followProfile(&a);
    a.unfollowProfile(&b);
    c.unfollowProfile(&b);
    std::cout << a.getEmail() << std::endl;//                           debug
    std::cout << b.getEmail() << std::endl;//                           debug
    std::cout << c.getEmail() << std::endl;//                           debug
    (b.getFollowers()).print();

    return 0;
}
