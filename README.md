# Techniki programowania 2023 - Projekt 4
## Łukasz Kubik 193178 (kjubig) & Mateusz Waszczuk 193666 (Matieusz56)

# _ZADANIE 3 - Wizualizacja windy_

## POLECENIE
_Zadanie 3_
Napisz program symulujący działanie windy. Symulator powinien uwzględniać możliwość zatrzymywania się na poszczególnych piętrach oraz przywołania winda za pomocą przycisku na interfejsie użytkownika. Program powinien kolejkować wywołania. Prezentacja poruszania się windy powinna zostać przedstawiona na modelu osadzonym w przestrzeni dwuwymiarowej.
_3.1_
Zasymuluj w aplikacji wożenie osób na poszczególne piętra. Użytkownik ma możliwość zdefiniowania ilości osób wchodzących i wychodzących na poszczególnych piętrach. Stwórz mechanizm kontrolujący maksymalny udźwig widny. Przyjmij, że średnia waga pasażera to 70kg, natomiast maksymalny udźwig windy to 600 kg.
_3.2_
Stwórz mechanizm sprawdzający czy winda po zatrzymaniu się na określonym piętrze jest pusta. Jeśli tak odliczaj 5 sek. i zjeżdżaj windą na parter.
_3.3_
Napisz program prezentujący na interfejsie użytkownika masę przewożonych pasażerów.

## ZALEŻNOŚCI PROJEKTU
- MINGW - WERSJA 11.2.0
- SFML - WERSJA 2.6.0
  
## KRÓTKO O PROJEKCIE
Celem naszego projektu jest stworzenie wirtualnej wizualizacji i działania windy. Aby to wykonać napisaliśmy program w języku cpp w sposób modułowy używając biblioteki SFML do spraw graficznych. Rozdrabniając problem na czynniki pierwsze doszliśmy do wniosku że najlepszym sposób do wykonania polecenia jest kontrolowanie listy pięter do których winda ma iść kierunkiem jadącej windy oraz jej aktualna wysokością. Stąd najważniejsze dane projektu umieszczone są w zmiennych ```winda.nrpietra``` ```winda.cel``` ```winda.Kierunek``` oraz lista pięter, do których winda ma jechać w ```winda.oczekujący``` (piętra piorytetowe) oraz ```winda.drugorzedneOczekujace``` (piętra na później).

## GRAFIKA PROJEKTU
Grafika składa się z okienka SFML RenderWindow, na którym znajdują się wszyskie elementy - winda, piętra, osoby, tło, przyciski itd. 
Windę, szyb windy, piętra, tła, reklamę oparliśmy o wykorzystanie tekstur - grfaiki wektorowej dla walorów estetycznych, natomiast przyciski i wyświetlające się liczby są stworzone przy wykorzystaniu kształtów i tekstu z biblioteki SFML.
Dla dodatkowego smaku pokusiliśmy się o stworzenie reklamy, która ma informować o aktualnej wadzę osób w windzie. ```POLECENIE 3.3```
Wszystkie wykorzystane grafiki są na publicznej licencji. 

## ZASADY I ZAŁOŻENIA WINDY
 a. Gdy osoby/piętra/cele są po drodze dodawane są normalnie do oczekujących i wektor ten jest sortowany względem kierunku (jak wyżej).
 b. Gdy osoby wchodzą do windy ich pietroDo (piętro docelowe dla osoby) zostaje dodane do jednego z wektorów -> w zależnoci czy cel jest po drodze. 
 c. Gdy zabranie osób w oczekujących i drugorzedneOczekujacych znaczy to, że winda może wrócić na pozycję początkową po 5s. ```[POLECENIE 3.2]```
 d. Gdy winda osiągnie cel usatawiany jest timer na 1s, który powoduje zatrzymanie się windy na piętrach. ```[POLECENIE 3 (3)]```
 e. 

1. dakdna
2. nadjak
   
## LOGIKA WINDY
Winda sortuje oczekujących w zależności od kierunku - malejąco lub rosnąco - i wybiera jako cel pierwszy element w wektorze (kolejce, zbiorze). Gdy winda dojedzie do celu usuwa dane piętro z oczekujących i wybiera następny cel tzn. pierwszy element, który wcześniej był drugim elementem kolejki. Taki proces się powtarza. Natomiast jeśli nowa osoba chce wejść lub wyjść na piętrze, które nie jest po drodze kierunku windy jest dodawana do drugiej kolejki (drugorzedneOczekujace). Gdy skończą się pietra w wektorze oczekujący następuje przeniesienie pięter/celów z wektora drugorzedneOczekujace do oczekujących i druga kolejka jest czyszczona. Dalej wyżej opisany proces się powtarza. ```[POLECENIE 3 (2)]```

 
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

