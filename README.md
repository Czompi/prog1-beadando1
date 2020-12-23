# Progi 1: beadandó feladat

A program jelenlegi állása a [TASKS.md](TASKS.md) fájlban olvasható.

> ## FIGYELEM!
> - A program használatához nélülözhetetlen az `email_template.html` fájl (ez alapján fogja generálni az elküldendő e-mailt).
> - A program Linux, macOS és Windows rendszerekkel kompatibilis, `Windows 10 20H2` (insider változat) és `Ubuntu 20.04.2 LTS` rendszereken tesztelt.


> ## Parancssori paraméterek
> Jelenleg 3 paraméter áll rendelkezésre, melyekkel a program javarészt automatizálható, melyek az alábbiak:
> 1. Forrásfájl neve (pl.: `veradok.csv`). Ha a fájl nem létezik, bekér egy másik nevet.
> 2. Program álatal használt "aktuális" dátum (pl.: `2020.12.12.`). Ezt egyenlőre még nem ellenőrzöm és nem is lehet máshogy beállítani (remélem holnapra sikerül megoldani).
> 3. Végrehajtandó művelet (pl.: `3`) Az alábbi műveletek érhetőek el:
> `1`. Véradók listájának megtekintése  
> `2`. Új véradó felvitele  
> `3`. vércsoportra keresés és műveletek azon adatokkal (például email növelés)  
> &nbsp;
> ### Windows alatti használat
> #### Forrásfájl beállítása
> ```batch
> beadando1.exe veradok.csv
> ```
> #### Forrásfájl és "aktuális" dátum beállítása
> ```batch
> beadando1.exe veradok.csv 2020.12.12.
> ```
> #### Forrásfájl, "aktuális" dátum és végrehajtandó művelet beállítása
> ```batch
> beadando1.exe veradok.csv 2020.12.12. 3
> ```
> &nbsp;
> ### *Linux és macOS* alatti használat
> #### Forrásfájl beállítása
> ```bash
> ./beadando1 veradok.csv
> ```
> #### Forrásfájl és "aktuális" dátum beállítása
> ```bash
> ./beadando1 veradok.csv 2020.12.12.
> ```
> #### Forrásfájl, "aktuális" dátum és végrehajtandó művelet beállítása
> ```bash
> ./beadando1 veradok.csv 2020.12.12. 3
> ```
> &nbsp;

> ## Program működése
> ### Beolvasás és adatfeldolgozás
> > ##### Megjelenés
> > ![data_acquisition-and-processing.png](https://cdn.czompisoftware.hu/img/3efebfb5a4cb0f61f93b239fa508e76600da056d/data_acquisition-and-processing.png)
> > ##### Működés
> > 1. A program beolvassa a megadott forrásfájlt
> > 2. A program ellenőrzi a beolvasott adatokat, majd feltölti ezeket a dinamikus helyfoglalású struktúrába.
> ### Opciók
> > #### Főképernyő (műveletek listája)
> > ##### Megjelenés
> > ![action.png](https://cdn.czompisoftware.hu/img/3efebfb5a4cb0f61f93b239fa508e76600da056d/action.png)
> > ##### Működés
> > 1. A program bekér egy opciót a felhasználótól megadott határon belül, amennyiben a megadott szám nagyobb, mint az elfogadott értek, akkor újra bekéri, egészen addig, ameddig a határértéken belüli számot ad meg.
> > 2. A bekért opció számához tartozó művelet(ek)et végrehatja.
> > 3. A művelet(ek) végrehajtása után megkérdezi, hogy folytatni akarja-e a program futtatását.
> > ##### Előforduló hibák 
> > - `N/A`
> > #### `1` Tagok megtekintése.
> > ##### Megjelenés
> > ![display_members.png](https://cdn.czompisoftware.hu/img/3efebfb5a4cb0f61f93b239fa508e76600da056d/display_members.png)
> > ##### Működés
> > 1. A dinamikus struktúrában lévő adatokat ellenőrzni
> > 1.1 Amennyiben hibát talál, a hibás adatot kicseréli a megjelenítendő adat helyett `hibás adat` szövegre.
> > 1.2 Amennyiben nem talál hibát, nem alakít át semmiféle adatot.
> > 2. Kiírja a struktúrában lévő adatokat az előbbi művelet függvényében
> > ##### Előforduló hibák 
> > - `hibás adat` a **Vércsoport** oszlopban
> > &nbsp; - Nem megfelelő vércsoport került megadásra, ezért a rendszer jelezte, hogy hibás az adat és felül kéne vizsgálni ezt a sort a forrásfájlban.
> > - `hibás adat` az **Email** oszlopban
> > &nbsp; - Nem megfelelő formátumú email cím került megadásra, ezért a rendszer jelezte, hogy hibás az adat és felül kéne vizsgálni ezt a sort a forrásfájlban.
> > - `hibás adat` a **Legutolsó** oszlopban
> > &nbsp; - Nem megfelelő formátumú dátum került megadásra, ezért a rendszer jelezte, hogy hibás az adat és felül kéne vizsgálni ezt a sort a forrásfájlban.
> > #### `2` Új tag felvitele
> > ##### Megjelenés
> > ![add_new_member.png](https://cdn.czompisoftware.hu/img/3efebfb5a4cb0f61f93b239fa508e76600da056d/add_new_member.png)
> > ##### Működés
> > 1. Bekéri a felhasználótól a véradó **nev**ét.
> > 2. Bekéri a felhasználótól a véradó **vércsoport**ját, majd ellenőrzi, hogy helyes-e, amennyiben nem, bekéri ismét. Ezt egészen addig ismétli, ameddig helyes adat nem került be, vagy a felhasználó meg nem unta és ki nem lépett.
> > 3. Bekéri a felhasználótól a véradó **email címé**t, majd ellenőrzi, hogy helyes-e, amennyiben nem, bekéri ismét. Ezt egészen addig ismétli, ameddig helyes adat nem került be, vagy a felhasználó meg nem unta és ki nem lépett.
> > 4. Bekéri a felhasználótól a véradó **véradásainak számá**t, majd ellenőrzi, hogy helyes-e, amennyiben nem, bekéri ismét. Ezt egészen addig ismétli, ameddig helyes adat nem került be, vagy a felhasználó meg nem unta és ki nem lépett.
> > 5. Bekéri a felhasználótól a véradó **legutolsó véradás**ának **időpontjá**t, majd ellenőrzi, hogy helyes-e, amennyiben nem, bekéri ismét. Ezt egészen addig ismétli, ameddig helyes adat nem került be, vagy a felhasználó meg nem unta és ki nem lépett.
> > 6. A bekért adatokat hozzáadja a véradók listájához. A program bezárásakor ajánlja föl a mentés lehetőségét (nem a legjobb design, de ez nem egy ténylegesen működő környezethez készül).
> > 7. Ezek után felajánlja a lehetőséget további véradók felvitelére.
> > ##### Előforduló hibák
> > **Érvénytelen vércsoport!**
> > > Nem megfelelő vércsoport került megadásra, ezért a rendszer jelezte, hogy hibás az adat és felül kéne vizsgálni ezt a sort a forrásfájlban.
> >
> > **Érvénytelen email cím formátum. Az email címnek tartalmaznia kell egy `.` és egy `@` karaktert!**
> > > Nem megfelelő formátumú email cím került megadásra, ezért a rendszer jelezte, hogy hibás az adat és felül kéne vizsgálni ezt a sort a forrásfájlban.
> >
> > **Ezen mező csak számokat fogad el!**
> > > Nem (csak) számot adott meg egy olyan mezőben, ahol számot kell megadni.
> >
> > **Érvénytelen dátum formátum! Elfogadott dátum formátum: `yyyy.mm.dd.`**
> > > Nem megfelelő formátumú dátum került megadásra, ezért a rendszer jelezte, hogy hibás az adat és felül kéne vizsgálni ezt a sort a forrásfájlban.
> > #### `3` Vércsoportra keresés, az adott vércsoportú ...
> > ##### Megjelenés
> > ###### Vércsoport kiválasztása
> > ![select_members_by_blood_type-1](https://cdn.czompisoftware.hu/img/3efebfb5a4cb0f61f93b239fa508e76600da056d/select_members_by_blood_type-1.png)
> > ###### Vércsoportban lévő véradók listája és lehetőségek
> > ![select_members_by_blood_type-2](https://cdn.czompisoftware.hu/img/3efebfb5a4cb0f61f93b239fa508e76600da056d/select_members_by_blood_type-2.png)
> > ##### Működés
> > 1. A felhasználó [megad egy létező vércsoportot](#vércsoport-kiválasztása) (amennyiben nem létező vércsoportot ad meg, a program addig fogja kérni, ameddig meg nem ad egy létezőt).
> > 2. Ezután megjelenik az [adott vércsoportú véradók listája](#vércsoportban-lévő-véradók-listája-és-lehetőségek) lap. Itt kiválaszthatja, hogy szeretne-e emailt küldeni ezen véradóknak.
> > ##### Előforduló hibák 
> > **Érvénytelen vércsoportot adott meg!**
> > > Nem megfelelő vércsoport került megadásra, ezért a rendszer jelezte, hogy hibás az adat és felül kéne vizsgálni ezt a sort a forrásfájlban.
> > ### Adatok mentése kilépés előtt
> > #### Működés
> > > A program megkérdezi, hogy menteni akarja-e a módosításokat kilépés előtt. Amennyiben igen - `y` -, akkor elmenti, amennyiben nem - `n` -, akkor nem fogja.
> > #### Megjelenés
> > ![changes_were_made](https://cdn.czompisoftware.hu/img/3efebfb5a4cb0f61f93b239fa508e76600da056d/changes_were_made.png)
> > &nbsp;

> A product of [Czompi Software](https://czompisoftware.hu).