# README #

Tämän repon koodi on vielä keskeneräistä ja valmistuu ennen tämän modulin alkamista.

Harjoitustyö OhRa:n kirjastot ja API:t osuuteen. Paljon tästä koodista saavat valmiina, tässä on koko kokonaisuus, mutta opiskelijat tekevät tästä osia. Teemat:

* dynaamiset C++ kirjastot ja niiden binäärinen yhteensopivuus (demo)
* API headerit, kirjastojen kääntäminen ja jakelu
* nettipohjainen API käyttäen udp socket/boost ja JSON; näiden APIen intro


Opiskelijat saavat valmiina dynaamisen simppelin salauskirjaston (.dylib) koodit. Aloitusseminaarissa demoan kahta vaihtoehtoista APIa, ja näytän miten pieni API-muutos rikkoo toisessa tapauksessa binääristä yhteensopivuutta ja miten toinen versio APIsta ei sitä tee. Jatkossa käytetään sitten sitä hyvää APIa.

Tehtävänä on suunnitella JSON API ja toteuttaa simppeli udp server ja client jolla voidaan konsolipohjaisella sovelluksella pyytää serveriä salaamaan merkkijonoja ja purkamaan salaus käyttäen ko. APIa ja dynaamista kirjastoa. Myös iso osa serverin ja clientin verkkokoodista annetaan valmiina, koska aikataulu ja osaamistaso. Tärkeintä on että API ja kirjastoajattelu tulee tutuksi.

## TODO

* Laita vaatimus testeistä clientin päässä tehtävänantoon.
    * Itse asiassa, tee clientista yksikkötestausta (vaikka Catch) käyttävä, ei ns. user app. 
    * Testit .json -tiedostoina luetaan, ainakin osin?
* Toteuta kukin salausmenetelmä boost.DLL:n plugineilla
* Aloitusseminaarissa suunnitellaan yhteinen JSON API serverille, jonka minä toteutan serverin päähän >> yhteinen serveri testeille, kullakin oma client?
    * Mihin serveri asennetaan..?
    * Tähän liittyen, kunkin oma salausplugin (jokaiselle uniikki nimi) asennetaan serverille myös.
* Lisäpainotusta API:n dokumentaatioon
* Myös versiointiin lisäpainotusta, mm. Version -luokan koodaus.
* lib:iin tuki Win-DLL:lle
* Tämä käyttöön? https://github.com/nlohmann/json
* Serveristä todellinen async -versio
* Perustele paremmin kielivalinta - C++ on ainoa kieli jolla voi tehdä alustariippumatonta koodia kaikkiin yleisiin käyttiksiin sekä desktop, server että mobiilipuolella, ja että C++ on kuitenkin yleisimpien kielten joukossa, ei mikään marginaalikieli.