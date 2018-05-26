# Cars_game

https://github.com/MasaKilibarda/Cars_game

Da bi se projekat izbildovao i pokrenuo potreban je Visual Studio i Sfml,biblioteka C++.
U Visual Studio-ju u delu Project/Property/Configuration_Properties potrebno je postaviti:

  -C/C++ /General/Additional_Include_Directories na folder include od sfml-a

  -Linker/General/Additionl_Library_Directories na folder lib od sfml-a

  -Linker/Input/Additional_Dependencies na sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-network-d.lib;sfml-audio-d.lib;

Kopirati .dll fajlove iz SFML/bin u folder u kome je projekat.

Igrica se bazira na pomerajima levo-desno kako bi se izbegi automobili koji nadolaze i skupilo gorivo koji se neprestano
smanjuje,cilj igrice je preci sto duzu razdaljinu tj. ostavariti sto veci score.

Izvrsni fajl napravljen je za operativni sistem Windows.

Autori:
 -Masa Kilibarda,371/2015,mashakilibarda@gmail.com
 -Andjela Milanovic,222/2015,andjelammatf@gmail.com
 -Tamara Despotovic,130/2013,tamaradespotovic@hotmail.com


