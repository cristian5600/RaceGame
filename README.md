![alt text](https://github.com/cristian5600/RaceGame/blob/main/RaceGamePicture.PNG)

Generare geometrie pistă
Geometria pistei de curse trebuie generată prin asamblare din cod. Nu se poate crea geometria într-un software extern și importa în aplicație.

Explicația care urmează este o recomandare de generare a geometriei pistei, dar aceasta poate fi asamblată în orice fel, atât timp cât sunt respectate cele 2 restricții de mai sus.

Generarea pistei de curse se poate realiza conform pașilor de mai jos. O reprezentare vizuală a rezultatelor este prezentată în continuare.

Se creează punctele unui poligon ce definește pista de curse. Noi am folosit Geogebra.
Se creează două seturi de puncte suplimentare, în interiorul și exteriorul poligonului ce definește pista. Punctele se pot crea de-alungul perpendicularei fiecărui segment. Acest proces este detaliat mai jos.
Se creează muchiile dintre punctele poligoanului interior și exterior.
Se generează triunghiurile dintre punctele celor două poligoane. Triunghiurile se creează într-un singur obiect de tip mesh.


Pentru a genera geometria pistei (o suprafață 2D), este nevoie de 2 mulțimi de puncte una interioară și una exterioară. Fiecare segment exterior este (aproximativ) paralel cu omologul lui din interior.



Aceste 2 mulțimi se pot obține folosind tool-urile deja discutate, însă este destul de costisitor la nivel de timp. O soluție mai elegantă este prezentată în continuare, unde de la o mulțime de puncte putem genera oricâte mulțimi de puncte paralele cu mulțimea inițială (paralelism la nivel de segmente).

Să presupunem că avem 2 puncte consecutive P1(x1, 0, z1), P2(x2, 0, z2) din mulțimea de puncte care definește traseul

Se determină vectorul direcție de la P1 către P2 notat D (negru in poza).
Se determină vectorul perpendicular pe D notat P (verde in poza) P = cross(D, UP), UP fiind vectorul perpendicular pe planul XOZ.
Folosind vectorul P și poziția P1 putem să obținem punctele exterioare  interioare (Roșu și Albastru) R = P1 + distRoșu  P, A = P1 - distAlbastru  P.
P1(x1,0,z1)P2(x2,0,z2)D⃗ =P2−P1P⃗ =cross(D⃗ ,UP→),UP→=(0,1,0)R=P1+distRoșu∗P⃗ A=P1−distAlbastru∗P⃗ 


Astfel, dacă aplicăm același lucru pentru toate segmentele, obținem noile mulțimi de puncte exterioare  interioare



Având cele 2 mulțimi (exterioară și interioară), putem să construim suprafața pistei. Presupunem că avem punctele exterioare r1, r2, r3 și cele interioare a1, a2, a3. Trebuie să se construiască cele 4 triunghiuri (r1, a1, a2), (r1, a2, r2), (r2, a2, a3). (r2, a3, r3).



Astfel, dacă aplicăm același lucru pentru toate punctele din ambele mulțimi obținem pista.

O posibilă generare mai bună utilizează media perpendicularelor pe 2 segmente consecutive pentru a crea punctele de pe cele două poligoane, interior și exterior.

Deplasare obstacole dinamice
Pe pistă, pe lângă mașina jucătorului, trebuie să se deplaseze și alte mașini (adversari). Aceștia se deplasează pe un traseu predefinit paralel cu mulțimea generatoare de pistă. Acest traseu se poate obține cu tehnica prezentată mai sus.

Generare copăcei lângă pistă
Pe lângă pistă se află copăcei cu scop decorativ. Constant pe ecran trebuie să se vadă cel puțin un copac (necesită densitate mare de copaci). Copacii nu trebuie să blocheze pista.

Control mașină
Dintre toate mașinile create pe pistă, pe una dintre ele va trebui să o alegeți ca fiind mașina jucătorului. Aceasta poate fi controlată folosind tastele W, A, S, D, unde W-S reprezintă mișcarea față-spate, iar A-D va schimba orientarea mașinii (detaliat mai jos).

Control cameră
Perspectiva jucătorului va fi una third-person, deci vom avea camera poziționată în spatele mașinii, uitându-se spre aceasta. Pentru un control cât mai fluid, vom dori ca mașina să rămână centrată pe direcția camerei, deci la apăsarea tastelor A-D se va face atât o rotație a mașinii, cât și o rotație a camerei



Pentru a păstra poziția camerei la aceeași distanță în spatele mașinii, la mișcarea față-spate (W-S), două alternative ar fi

Actualizarea poziției camerei odată cu cea a mașinii, la fiecare input valid.
Actualizarea constantă (deci în Update(), fără verificări) a poziției camerei ca fiind poziția mașinii la care se adaugă un offset (acel offset fiind distanța pe care camera o păstrează față de mașină).
Deplsarea față-spate (W-S) va implica mișcarea mașinii în funcție de rotația camerei, astfel încât comportamentul dorit să fie asemănător cu exemplul de mai jos



Hint
1) Calculele de deplasare și rotație pot deveni destul de complicate destul de repede, de aceea vă recomandăm să lucrați cu vectori, pornind de la exemplele și teoria din Laboratorul 4.

2) Pentru deplasarea față-spate (W-S), vă recomandăm folosirea vectorilor camerei (în cazul acesta, vectorul forward) pentru a afla direcția de deplasare a mașinii.

Exemplu Din moment ce camera își schimbă vectorul de forward la rotația pe OY (lab 5), o soluție ar fi folosirea acesteia pentru direcția de deplasare.

Utilizând ambele tehnici (rotația mașinii și deplasarea folosind vectorul forward al camerei), rezultatul final arată așa



Verificare mașină dacă se află pe pistă
Pentru a verifica dacă mașina se află pe pistă, avem la dispoziție mai multe posibilități. Pentru simplitate, vom considera suficient dacă se verifică doar centrul mașinii să se afle în interiorul pistei. Orice soluție ce oferă o verificare corectă a acestei informații este bună.

Noi recomandăm oricare dintre următoarele 2 opțiuni

Verificarea dacă poziția mașinii (doar (x, z)) se află în cel puțin unul din triunghiurile ce definesc geometria pistei. Câteva resurse bune pentru acest proces se pot găsi aici httpswww.baeldung.comcscheck-if-point-is-in-2d-triangle, httpsblackpawn.comtextspointinpoly.
Verificarea dacă poziția mașinii (doar (x, z)) se află la o distanță mai mică de jumătate din lățimea pistei față de cel puțin un segment ce definește pista. O resursă buna pentru acest proces este aici httppaulbourke.netgeometrypointlineplane.
Atenție!
Pentru a avea un comportament asemănător celui din demo-ul video, trebuie ca mașina să nu se blocheze dacă se lovește de exteriorul pistei. Pentru a preveni acest blocaj, o strategie ar fi următoarea

În locul unei verificări constante în Update(), se poate face acest check la fiecare încercare de input;
Exemplu Dacă se ține apăsat W, trebuie verificat mai întâi dacă cumva poziția nouă obținută în urma deplasării nu face coliziune. Dacă face, atunci inputul trebuie ignorat, altfel executat în mod normal.

Verificare coliziuni obstacole dinamice
Pentru a avea niște interacțiune cu mașiniile inamice, va trebui să le puteți “detecta”. Această detectare presupune o verificare a poziției mașinii jucătorului în raport cu fiecare mașină inamică. Pentru a realiza acest lucru, cel mai simplu mod pe care vi-l recomandăm este o verificare de coliziune sferă-sferă



În cazul nostru particular, sferele ar avea centrul în centrul mașinii, iar raza acesteia presupune distanță de verificare de coliziune.

În momentul în care este dectată intersecția dintre mașina controlată de jucător și un obstacol dinamic, mașina jucătorului trebuie să se oprească. Orice tastă apasată pentru controlul deplasării sau rotației nu mai trebuie să modifice poziția sau orientarea mașinii. Acest efect de oprire dispare în momentul în care nu mai există intersecție.

Minimap
În unul din colțurile ecranului (nu contează ce colț, noi am ales dreapta-jos pentru a fi mai ușor de vizualizat dar puteți alege orice poziție), va trebui să randați și un minimap.

În esență, un minimap nu reprezintă altceva decât un alt viewport unde trebuie să randați aceeași scenă iarăși.

Modul în care se poate crea un nou viewport in OpenGL (aveți un exemplu și in scheletul laboratorului 4) este folosind funcția

glViewport(GLint x, GLint y, GLint width, GLint height)
Pentru a putea vedea de sus scena (cum este prezentat și în exemplul de mai jos), ar trebui să se întâmple următoarele lucruri

Mutarea poziției camerei deasupra mașinii (și prin urmare și poziția centrului camerei);
Din moment ce se dorește o vedere de ansamblu asupra unei bucăți din traseu, se va trece camera într-o proiecție ortografică folosind funcția
glmortho(float left, float right, float bottom, float top, float zNear, float zFar)


Atenție! Observați că rotația camerei nu se mai păstrează, dar deplasarea ei în funcție de jucător da!
Curbură teren
Crearea curburii din shader
Realizeaza curburii terenului se realizează la pasul de desenare a obiectelor din scenă. Acest efect se creează prin modificarea componentei y a coordonatelor pentru toți vertecșii obiectelor din scenă. Procesul este realizat în vertex shader. Componenta y a tuturor vertecșilor se modifică după cum urmează.

Posvy=Posvy−∥Poscar−Posv∥2⋅scaleFactor
Posv
 - poziția în spațiul lume a vertexului procesat de vertex shader
Poscar
 - poziția în spațiul lume a mașinii controlate de jucător
Posvy
 - componenta y a poziției vertexului
scaleFactor
 - un factor de scalare ce controlează curbura terenului
Factorul de scalare este proporțional cu dimensiunea obiectelor din scenă. Pentru demo-ul de mai sus, unde lățimea mașinii este de 1 unitate, a fost folosit un factor de scalare de 0.02.



Densitate de triunghiuri teren
Deoarece realizarea curburii terenului este un proces ce modifică pozițiile vertecșilor, rezultatul vizual este influențat de densitatea de triunghiuri ale terenului. Cu cât terenul are o densitate mai mare de triunghiuri, cu atât efectul de curbura este mai natural. O densitate mică produce un rezultat vizual mai 'pătrățos'. O comparație între rezultatele celor două poate fi vizualizată mai jos. În stânga este prezentat rezultatul pentru o densitate mică și în dreapta pentru o densitate mare.



În plus, geometria terenului de iarbă poate trece prin geometria pistei pentru o densitate mică de triunghiuri, așa cum se poate vedea mai sus în stânga.

Pentru a elimina aceste artefacte vizuale, este necesară generarea terenului de iarbă și a pistei cu o densitate mare de triunghiuri. De exemplu, o comparație între geometria celor două rezultate de mai sus este după cum urmează. Geometria pistei a fost generată conform descrierii de mai sus.



Funcționalități obligatorii (150 puncte)
Teren 40p
Generare geometrie teren iarbă și pistă 30p
Generare copăcei lângă pistă 10p
Generare locații copăcei 7.5p
Desenare copăcei 2.5p
Obstacole dinamice 20p
Generare trasee diferite 7.5p
Desenare obstacole 2.5p
Deplasare obstacole 10p
Control mașină 30p
Control deplasare și rotație 15p
Poziționare corectă cameră în spatele mașinii 10p
Oprire mașină la coliziunea cu obstacolele dinamice 2.5p
Oprire mașină la părăsirea pistei 2.5p
Verificare corectă mașină dacă este pe pistă 15p
Verificare corectă mașină dacă intersectează obstacolele dinamice 5p
Minimap 20p
Calculare corectă proiecție ortografică 15p
Desenare într-o altă poartă de vizualizare 5p
Curbură teren 20p
Efect de curbură din shader 10p
Generare geometrie teren cu o densitate mare de triunghiuri 10p
