# Techniki programowania 2023 - Projekt 4
## Łukasz Kubik 193178 (kjubig) & Mateusz Waszczuk 193666 (Matieusz56)

# _ZADANIE 3 - Wizualizacja windy_

## POLECENIE
### _Zadanie 3_
Napisz program symulujący działanie windy. Symulator powinien uwzględniać możliwość zatrzymywania się na poszczególnych piętrach oraz przywołania winda za pomocą przycisku na interfejsie użytkownika. Program powinien kolejkować wywołania. Prezentacja poruszania się windy powinna zostać przedstawiona na modelu osadzonym w przestrzeni dwuwymiarowej.
### _3.1_
Zasymuluj w aplikacji wożenie osób na poszczególne piętra. Użytkownik ma możliwość zdefiniowania ilości osób wchodzących i wychodzących na poszczególnych piętrach. Stwórz mechanizm kontrolujący maksymalny udźwig widny. Przyjmij, że średnia waga pasażera to 70kg, natomiast maksymalny udźwig windy to 600 kg.
### _3.2_
Stwórz mechanizm sprawdzający czy winda po zatrzymaniu się na określonym piętrze jest pusta. Jeśli tak odliczaj 5 sek. i zjeżdżaj windą na parter.
### _3.3_
Napisz program prezentujący na interfejsie użytkownika masę przewożonych pasażerów.

## ZALEŻNOŚCI PROJEKTU
- MINGW - WERSJA 11.2.0
- SFML - WERSJA 2.6.0
  
## KRÓTKO O PROJEKCIE
Celem naszego projektu jest stworzenie wirtualnej wizualizacji i działania windy. Aby to wykonać napisaliśmy program w języku cpp w sposób modułowy używając biblioteki SFML do spraw graficznych. Rozdrabniając problem na czynniki pierwsze doszliśmy do wniosku że najlepszym sposobem do wykonania polecenia jest kontrolowanie listy pięter do których winda ma iść kierunkiem jadącej windy oraz jej aktualna wysokością. Stąd najważniejsze dane projektu umieszczone są w zmiennych ```winda.nrpietra```, ```winda.cel```, ```winda.Kierunek``` oraz lista pięter, do których winda ma jechać w ```winda.oczekujący``` (piętra piorytetowe) oraz ```winda.drugorzedneOczekujace``` (piętra na później).

## PRZYKŁADOWY OPIS DZIAŁANIA PROGRAMU
Po odpaleniu programu winda stoi w spoczynku na piętrze zerowym, jej kierunek jest ustwaiony na "Idle". W tej pozycji czeka na działanie użytkownika. Użytkownik może wybrać jeden z pięciu guzików na każdym piętrze. Kiliknięcie danego guzika definiuje pojawienie się osoby na piętrze - numer piętra, na które ma jechać definuje numer guzika. Załóżmy, że użytkownik kilka guzik nr. 3 na 1 piętrze. W tym momencie piętro, na którym znajduje sie osoba - piętro 1 - zostaje dodane do kolejki. Pietro jest zgodne z kierunkiem ruchu windy, więc zostaje ono dodane do wektora ```winda.oczekujące```. Sortowany jest wektor oczekujących rosnąco i wybrany jest cel windy, czyli element pierwszy w kolejce, w tym przypadku 1 tj. numer piętra na kórym znajduje sie osoba. Winda sprawdza czy jest na celu, porównując numer piętra, na którym jest z celem - dowiaduje się, że nie jest na docelowym piętrze, dlatego rusza się w stonę tego pietra - 1 - do góry. Gdy poprzedni warunek zosatnie spełniony to znaczy, ze winda znajduje się na celu następuje wykonanie logiki windy, która opisana jest niżej. Dla kazdego pasażera sprawdzane jest czy chce wyjść, jesli tak to wychodzi, jesli nie to zostaje - w tym przypadku w windzie nie było pasażerów. To co nas intersuje to to, że dla kazdej osoby, która chce wejść do windy jest sprawdzana możliwość  wejscia - analizowana jest waga i ta osoba zostaje dodana do windy, a jej numer pietra zostaje dodany do wektora oczekujacych, ponieważ kilkamy pietro zgodne z kierunkiem - piętro 3. Usuwane jest piętro, na którym znajduje sie winda - piętro 1 i jako cel ustawiane jest piętro 3, które jest jak wcześniej powiedzieliśmy aktualnie pierwszym elementem wektora ```winda.oczekujące``` . Znowu porównywany jest numer piętra, na którym aktulanie znajduje się winda do celu do którgo jedzie. Gdy winda dojedzie do celu osoba usuwana jest z windy i następnei sprwadzana jest logika, a gdy nie ma juz zadnych elementów w oczekujących i drugorzędnychOczekujących winda po 5 sekundach wraca do pozycji początkowej, czyli na piętro zerowe. 

## GRAFIKA PROJEKTU
Grafika składa się z okienka SFML RenderWindow, na którym znajdują się wszyskie elementy - winda, piętra, osoby, tło, przyciski itd. 
Windę, szyb windy, piętra, tła, reklamę oparliśmy o wykorzystanie tekstur - grfaiki wektorowej dla walorów estetycznych, natomiast przyciski i wyświetlające się liczby są stworzone przy wykorzystaniu kształtów i tekstu z biblioteki SFML. ```POLECENIE 3```. Dla dodatkowego smaku pokusiliśmy się o stworzenie reklamy, która ma informować o aktualnej wadzę osób w windzie. ```POLECENIE 3.3```. Wszystkie wykorzystane grafiki są na publicznej licencji. 

## ZASADY, ZAŁOŻENIA I LOGIKA WINDY
 ### Założenia
- Dodawania ludzi na pietra jest kontrolowane guzikami z liczbami po bokach pieter, które uzytkownik moze wcisnąć.
- Przy kliknieciu przycisku dodawana jest osoba do kolejki i ```dzieje się mechanizm opisany poniżej w logice i zasadach```.
- Liczba wyswietlona na czlowieku jest pietrem, na które wybiera sie czlowiek.
- Ludzie czekaja w kolejce na pietrach aż winda przyjedzie, a potem czekaja na wyjscie, aż beda na pietrze na którym chcą wyjść.
  
### Logika i zasady
 1. Gdy osoby wchodzą do windy ich pietroDo (piętro docelowe dla osoby) zostaje dodane do jednego z wektorów -> w zależnoci czy piętro docelowe tej osoby jest po drodze. Ustawiamy również wagę. 
 2. Gdy dodajemy osobę, której piętro docelowe jest są po drodze dodawana jest normalnie do kolejki/wektora oczekujących i wektor ten jest sortowany względem kierunku.
 3. Gdy dodajemy osobę, której piętro docelowe nie jest są po drodzenie dodawana jest do kolejki/wektora drugorzędnychOczekujących i wektor ten jest sortowany względem kierunku.
 4. Sortowanie kolejki oczekujących/drugorzędnychOczekujących następuję rosnąco jeśli kierunek windy jest do góry i malejąco jeśli winda jedzie w dół.
 5. Gdy winda dojedzie do piętra docelowego, na którym osoba ma wysiąść - usuwana jest ona z wektora oczekujących, zmieniana jest waga oraz zostaje dodana do wektora wysiadających (kwestie graficzne).
 6. Winda jedzie po piętrach zgodnie z kolejką oczekujących, gdy wektor ten zostanie opróżniony następuje zastąpienie go wektorem drugorzędnychOczekujących i proces powtarza się.
- (1. -> 6.) ```POLECENIE 3 i 3.1```
7. Gdy winda osiągnie cel - winda dojedzie do piętra docelowego - usatawiany jest timer na 1s, który powoduje zatrzymanie się windy na piętrach. ```POLECENIE 3```
8. Gdy zabranie osób w oczekujących i drugorzedneOczekujacych znaczy to, że winda może wrócić na pozycję początkową po 5s. ```POLECENIE 3.2```
9. System sprawdza również na bierząco aktulaną wagę osób w windzie i jeśli jest ona maksymalna osoby dodwana są do wektora drugorzędnychOczekujących. ```POLECENIE 3.1```

### Opis zastosowania 
Użytkownik użwya przycisków do dodania osoby na danym piętrze, jednocześnie ustawiając piętro, do którego dana osoba ma jechać. W zależności od liczby osób w windzie wykonwaywane są kroki (1. 2. 3. 4.). Gdy winda dojedzie na piętro, do którgo dana osoba miała jechać następuję krok (5.) i w zależności od ilości osób krok (7. lub 8.). Cały czas też kontorlowana jest waga jak w punkcie (9.). Zależnie ten logiczny proces powtarza się.

## Osoba odpowiedzialna za sprawozdanie - Łukasz Kubik
 
## COMMITY
> OPISANE SĄ DOKŁADNIE PRZY ICH DODAWANIU
- MODUŁOWY PODZIAŁ NA ELEMENTY
- DODANIE ELEMENTÓW GRAFICZNYCH
- DODAWANIE ELEMENTÓW GRAFICZNYCH - 2
- OSTATECZNA WERSJA WIZUALNA + DODANIE PRZYCISKÓW I RUCHU
- FUNKCJONALNOŚĆ PRZYCISKÓW I PŁYNNY RUCHU
- KOŃCOWE DODANIE OSÓB I PRACA NAD LOGIKĄ RUCHU WINDY
- ZMIANA LOGIKI WINDY - SORTOWANIE OSÓB
- LOGIKA WINDY - SORTOWANIE OSÓB (2)
- LOGIKA WINDY + OSOBY W WINDZIE - SORTOWANIE OSÓB - DWA WEKTORY
- LOGIKA WINDY + RUCH OSOÓB - DOPRACOWYWANIE
- WERSJA OSTATCZNA V1 - WAGA/POZYCJE - LOGIKA DO DOPRACOWANIA
- WERSJA OSTATCZNA V2 - WYŚWIETLANIE WAGI - LOGIKA DO DOPRACOWANIA
- WERSJA KOŃCOWA

