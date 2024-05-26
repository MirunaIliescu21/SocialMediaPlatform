### Echipa tema 3 SD:
* robert_fabian.tudor
* miruna.iliescu

<br />

## Tema 3

### Descriere:

* Scopul acestei teme este de a înțelege și de a dezvolta o platformă de social media care combină funcționalități de stocare în cloud, gestionarea rețelelor de prieteni și partajarea postărilor. Aceasta presupune implementarea unor structuri de date arborescende, dar și a unor algoritmi specific realizați pentru a permite utilizatorilor să adauge și să gestioneze prieteni, să creeze și să interacționeze cu postări și să genereze un feed de social media personalizat.

<br />

## __Explicații:__

## Task 1 - Rețea de prietenie
* Acest task implică implementarea funcționalităților necesare pentru gestionarea unei rețele de prietenie într-o platformă de social media
(adăugarea unui prieten, eliminarea unui prieten, calcularea distanței minime din graf dintre 2 prieteni, generarea de sugestii de prieteni, afișarea prietenilor comuni, afișarea numărului de prieteni al unui utilizator sau afișarea prietenului cu cele mai multe conexiuni dintre utilizatorul dat și prietenii săi).

### suggestions 
* Această funcție identifică prietenii prietenilor utilizatorului primti ca parametru care nu sunt deja prieteni cu acesta.
* La început, se obține ID-ului unic asociat utilizatorului pe baza numelui său. Se alocă apoi un vector de frecvență pentru a ține evidența potențialelor sugestii de prieteni. Se accesează lista de prieteni a utilizatorului, iar pentru fiecare prieten din această listă, se obține la rândul său lista de prieteni, marcând astfel toți prietenii pritenilor utilizatorului în array-ul de frecvență.
* La final, utilizatorul și prietenii săi curenți sunt excluși din aceste sugestii, iar dacă există sugestii valide, acestea sunt afișate, în caz contrar, se indică faptul că nu există sugestii disponibile pentru utilizatorul respectiv.

### get_distance
* Această funcție are rolul de a calcula și de a afișa distanța cea mai scurtă între doi utilizatori dintr-o rețea socială. Aceasta utilizează algoritmul de căutare în lățime pentru a determina numărul minim de pași necesari pentru a ajunge de la un utilizator la celălalt.
* La început se obțin identificatorii unici pentru cei doi utilizatori, pe baza numelor acestora. Apoi, funcția min_path este apelată pentru a calcula distanța cea mai scurtă dintre cei doi utilizatori.(Funcția min_path este cea realizată în cadrul laboratorului 7 de SDA, la care am fost adăugate mici modificări; comenatrii legate de funcționalitatea ei se găsesc în fișierul graph.h). Dacă există un drum între cei doi utilizatori, distanța este afișată. În caz contrar, se indică faptul că nu există o cale de la primul utilizator la cel de-al doilea.

### most_popular_friend
* Această funcție identifică și afișează prietenul cel mai popular al unui utilizator(adică prietenul cu cei mai mulți prieteni), pe baza numărului de prieteni pe care îi are fiecare prieten al utilizatorului respectiv.
* La început se obține identificatorul unic asociat utilizatorului primit ca parametru, utilizând numele acestuia. Se accesează lista de prieteni a utilizatorului din graf și se inițializează variabilele de maxim(max_num_friends, max_id) pentru a reține prietenul cu cei mai mulți prieteni. Funcția parcurge fiecare prieten din lista utilizatorului, accesând la rândul său lista de prieteni a fiecăruia și numărând câți prieteni are fiecare utilizând funcția count_friends(mai multe detalii despre implementarea acestei funcții se găsesc în fișierul friends.h).
* La fiecare iterare, dacă un prieten are mai mulți prieteni decât maximul curent(max_num_friends), acesta devine noul prieten cel mai popular, iar în caz de egalitate, este ales prietenul cu ID-ul mai mic.
* La final, funcția afișează prietenul cel mai popular, iar dacă utilizatorul are cei mai mulți prieteni sau are număr egal de prieteni cu un alt utilizator, iar ambii au cei mai mulți prieteni, se indică faptul că utilizatorul însuși este cel mai popular(această abordare a fost precizată în enunțul temei).

<br />

## Task 2 - Postări și reposturi
* Acest task implică implementarea funcționalităților necesare pentru gestionarea postărilor și repostărilor dintr-o platformă de social media(crearea unei postări, repostarea unei postări sau a unei repostări, găsirea primului repost comun pentru două reposturi date, aprecierea unei postări, ștergerea unei postări, afișarea numărului de like-uri pentru o postare etc.).
* În implementarea acestui task am folosit structurile de arbore generic împreună cu funcționalitățile acestuia implementate în fișierele generic_tree.c și generic_tree.h(mai multe detalii despre acestea se găsesc în fișierul generic_tree.h unde am explicat utilizarea lor).

### common_repost
* Această funcție identifică primului repost comun între două reposturi ale aceleiași postări.
* La început, funcția localizează arborele postării corespunzător ID-ului primit ca parametru(post_id). Apoi, se inițializează vectorii necesari pentru reprezentarea turului Eulerian și nivelurile fiecărui nod din arbore(am folosit metoda turului Eulerian pentru căutarea primului strămoș comun, metodă ce a fost explicată în cadrul cursului de SDA; pentru mai multe detalii despre funcționalitatea acestui algoritm exită comentarii în fișierul posts.h sau pe [linkul](https://www.infoarena.ro/problema/lca) prezentat la curs).
* Se realizează reprezentarea turului Eulerian a arborelui postării și a vectorului de niveluri, folosind o metodă recursivă pentru traversarea arborelui. Apoi, se aplică algoritmul de căutare a celui mai mic strămoș comun pe baza turului Eulerian și a nivelurilor fiecărui nod, determinând astfel ID-ul primului repost comun între cele două reposturi date.
* La final, după ce s-a găsit LCA, se eliberează memoria alocată anterior pentru vectorii Euler și nivel. 

### like_post
* Această funcție este responsabilă pentru gestionarea acțiunilor de like sau unlike a postărilor și repostărilor.
* La început, funcția caută arborele corespunzător postării identificate prin post_id în structura post_manager. Dacă postarea nu există, funcția se încheie.
* În caz contrar, funcția determină ID-ul utilizatorului care dă like-ul și titlul postării asupra căruia se efectuează acțiunea(dacă este cazul).
* În funcție de existența sau absența parametrului repost_id, funcția adaugă sau elimină like-ul utilizatorului la nivelul postării sau a repostării.
* Se caută în lista de like-uri a postării sau repostării ID-ul utilizatorului, iar dacă utilizatorul a dat deja like la respectiva postare sau repostare, se realizează eliminarea acestui like, iar dacă nu, se adaugă(în esență, se elimină sau se adaugă un nod în listă utilizând funcții special implementate în acest sens).
* De asemenea, funcția ajustează numărul total de like-uri asociate postării sau repostării(schimbă valoarea variabilei n_likes), iar la final afișează un mesaj corespunzător.

### ratio
* Această funcție are rolul de a găsi postarea sau repostarea cu cel mai mare număr de like-uri.
* La început, funcția caută arborele corespunzător postării cu ID-ul post_id, primit ca parametru, în structura post_manager. Dacă postarea nu există, funcția se încheie.
* Apoi, se inițializează variabile pentru a stoca numărul maxim de like-uri și ID-ul postării sau repostării cu cele mai multe like-uri(max_likes, max_likes_id), ce au în primă fază valorile postării originale.
* Se traversează recursiv arborele pentru a găsi nodul cu cel mai mare număr de like-uri și se actualizează variabilele de maxim la fiecare iterație, iar în caz de egalitate se alege postarea/repostarea cu Id-ul mai mic(acest lucru se realizează cu ajutorul funcției *find_max_likes_recursively* mai multe detalii despre această funcție se găsesc în fișierul posts.h).
* La final, se compară ID-ul postării cu cele mai multe like-uri cu ID-ul postării originale, iar dacă postarea originală are și ea max_likes, se alege această postare ca fiind cea cu cele mai multe like-uri, indiferent de ID găsit până atunci pentru cea mai apreciată postare(această abordare este precizată în enunțul temei) și se afișează un mesaj corespunzător rezultatului obținut.

<br />

## Task 3 - Social Media
* Acest task implică implementarea unor funcționalități pentru gestionarea și afișarea postărilor și interacțiunilor într-o rețea socială
(afișarea celor mai recente postări făcute de un utilizator și prietenii săi, afișarea tuturor postărilor și repostărilor unui utilizator, afășarea tuturor prietenilor unui utilizator care au dat repost la postarea cu un anumit id și afișarea celui mai mare grup de prieteni în care se află un anumit utilizator).

### common_groups
* Această funcție are scopul de a identifica și afișa cea mai mare clică de prieteni(în care se ală și utilizatorul primit ca parametru) formată pe baza modificării unui graf dintre un utilizator și prietenii săi.
* Se obține user_id pentru numele de utilizator dat, folosind funcția get_user_id și se accesează lista de prieteni a utilizatorului, utilizând funcția lg_get_neighbours.
* Se inițializează un vector frequency pentru a asigura faptul că doar prietenii utilizatorului sunt luați în considerare în calcule. De asemenea, se alocă memorie pentru un vector de prieteni (friends_vector), care va stoca informații despre fiecare prieten, inclusiv ID-ul și numărul de conexiuni cu celalte persoane din graf(n_connections). 
* Inițializăm variabila n_friends care stochează numărul total de persoane din graf case se actualizează pe măsură ce se iterează prin lista de prieteni.
* Se traversează lista de prieteni a utilizatorului, adăugând ID-urile acestora în friends_vector și marcându-i în vectorul frequency. 
Apoi, se calculează numărul de conexiuni pentru fiecare persoană din friends_vector astfel: Pentru fiecare prieten din friends_vector, funcția preia lista prietenilor asociată acestuia și numără conexiunile cu prietenii utilizatorului. 
* După aceea, friends_vector este sortat în ordine descrescătoare în funcție de numărul de conexiuni, utilizând funcția sort_friends_by_connections(mai multe detalii despre această funcție se găsesc în fișierul feed.h).
* Pentru calcularea clicii se iterează în ordine descrescătoare prin friends_vector; pentru fiecare element se verifică dacă are un număr de conexiuni necesar pentru a face parte din clică. Dacă această condiție este îndeplinită nu mai continuăm iterarea deoarece, fiind ordonați după numărul de conexiuni, restul prietenilor îndeplinesc cu siguranță condiția. În caz contrar, considerăm prietenul ca fiind eliminat din clică, recalculăm numărul de conexiuni și resortăm vectorul(de fiecare dată când un prieten e eliminat din vector conexiunile dintre restul persoanelor din vector și el trebuie eliminate).
* La final sortăm vectorul friends_vector în ordine crescătoare după ID folosind funcția sort_friends_by_id(mai multe detalii despre această funcție se găsesc în fișierul feed.h) și afișăm persoanele rămase în clică.

<br />

## Comentarii asupra temei:

### Ce ați învățat din realizarea acestei teme?

* Cum funcționează în background o platformă de social media.

* Să realizăm o mai bună înțelegere și implementare a unor structuri de date(*Grafuri, Arbori generici*).

* Să înțelegem și să implementăm un algoritm optim de LCA pentru arbori care folosește reprezentarea Euler a acestuia.

<br />

<h2 style="color: red; font-weight: bold;">Observație:</h2>

### Comentariile Doxygen ale structurilor și funcțiilor implementate sunt incluse în fișierele ".h". Am ales această abordare pentru a menține codul cât mai lizibil posibil.




