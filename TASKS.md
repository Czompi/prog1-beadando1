# Program jelenlegi állása

> ### Alapvető tulajdonságok
> - :heavy_check_mark: Legyenek külön állományban tárolva a progi függvényei, a függvények típusai (".h-s" állomány) és a "főprogram", a main, továbbá minden blokk jelezze, ha hiba történt, s biztosítsa az újbóli próba lehetőségét!
> - :heavy_check_mark: Nem kötelező, csak választható részfeladat, hogy parancssorban indítva kapja meg a kezelendo állomány nevét
> - :heavy_check_mark: Allapítsa meg, hány személy adatai vannak a táblán, s ennek megfelelően foglaljon helyet a memóriában egy, az adatokat majdan tároló, dinamikus helyfoglalású struktúratömbnek
> - :heavy_check_mark: Töltse föl a szöveges állományból a struktúratömböt tudósítsa a felhasználót a történtekrol

> ### Program funkciói
> - :heavy_check_mark: taglista megtekintése
> - :heavy_check_mark: új tag hozzáadása a listához
> - :heavy_check_mark: vércsoportra keresés
> - :heavy_check_mark: az adott vércsoportú tagok számára névre szóló, véradásra felkérő emailek összeállítása, fájlba írása, ahol a fájl(ok) neve(i) a címzett(ek) email címe(i)
> - :recycle: megelőlegezvén a bizalmat, véradás-számuk és legutóbbi véradás dátumuk felülírása a program és a nyilvántartást dokumentáló fájl listájában is // működőnek tűnik, csak összeomlik még.

> ### Program működése futás közben
> - :heavy_check_mark: a választott opció végrehajtása
> - :heavy_check_mark: program folytatásának felajánlása, igen válasz esetén a lehetőségek újbóli kilistázása, stb.
> - :heavy_check_mark: Az e-mail címet ellenőriznie kell: beíráskor csak olyat fogad el, amiben szerepelnek a `.` és a `@` jelek, egyikük sem a cím végein vagy közvetlenül egymás mellett. Ha a fájlban talál hibásat, azt jeleznie kell a listázáskor!
> - :heavy_check_mark: a dátumot egy darab karakterláncban kell tárolnia, megadás formátuma: `2020.11.07.` . Csak ilyen formátumot fogadhat el! Ha a fájlban talál hibásat, azt jeleznie kell a listázáskor!
> - :heavy_check_mark: Amikor véradásra van szükség és megfelelő vércsoportot keres, a találatok közül csak azok adhatnak vért, akik utoljára 90 napnál régebben voltak véradáson! Ehhez nyilván ki kell számolni az aktuális dátum és a legutóbbi véradás dátuma közötti difit, amihez a karakterlánc ponttal elválasztott részeit (év.hó.nap) nyilván számmá kell alakítanunk. Vehetünk minden évet 365, s minden hónapot 30 naposnak. Nem használhatunk beépített, karakterláncokat kezelő függvényeket. (Tehát: se `string.h`, se `math.h`)

> ### Jelmagyarázat
> | Kód | Jelentés |
> | :-: | :-: |
> | :heavy_check_mark: | Kész, *valószínűleg* működik |
> | :recycle: | WIP |
> | :x: | Tervezett feature |