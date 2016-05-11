# README #

Tämän repon koodi on vielä keskeneräistä ja valmistuu ennen tämän modulin alkamista.

Harjoitustyö OhRa:n kirjastot ja API:t osuuteen. Paljon tästä koodista saavat valmiina, tässä on koko kokonaisuus, mutta opiskelijat tekevät tästä osia. Teemat:

* dynaamiset C++ kirjastot ja niiden binäärinen yhteensopivuus (demo)
* API headerit, kirjastojen kääntäminen ja jakelu
* nettipohjainen API käyttäen udp socket/boost ja JSON; näiden APIen intro
*

Opiskelijat saavat valmiina dynaamisen simppelin salauskirjaston (.dylib) koodit. Aloitusseminaarissa demoan kahta vaihtoehtoista APIa, ja näytän miten pieni API-muutos rikkoo toisessa tapauksessa binääristä yhteensopivuutta ja miten toinen versio APIsta ei sitä tee. Jatkossa käytetään sitten sitä hyvää APIa.

Tehtävänä on suunnitella JSON API ja toteuttaa simppeli udp server ja client jolla voidaan konsolipohjaisella sovelluksella pyytää serveriä salaamaan merkkijonoja ja purkamaan salaus käyttäen ko. APIa ja dynaamista kirjastoa. Myös iso osa serverin ja clientin verkkokoodista annetaan valmiina, koska aikataulu ja osaamistaso. Tärkeintä on että API ja kirjastoajattelu tulee tutuksi.