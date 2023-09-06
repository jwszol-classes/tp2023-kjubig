# Techniki programowania 2023 - Projekt 4
## Łukasz Kubik 193178 (kjubig) & Mateusz Waszczuk 193666 (Matieusz56)

### _ZADANIE 3 - Wizualizacja windy_

## KRÓTKO O PROJEKCIE

Przy tworzeniu projektu stwierdziliśmy, żeby modułowo dzielić projekt na klasy - odpowiadające za inne elementy projektu (osoby, piętra, windę, działanie windy itd.). Zaczęliśmy od właśnie takiego podziału i uzupełnienia wymaganych danych (np. o osobach - waga, piętro docelowe itd.). Dalej przeszliśmy do początkowej realizacji graficznej, którą opraliśmy na teksturach. Wraz z pracą nad projektem dodawaliśmy kolejne elemnty np. dodatkowe tło dla polepszenia walorów esteycznych. Przyciski dodaliśmy normalnie wykorzystując kształty. Całą kwestię graficzną opraliśmy na bibliotece SFML. Środkowa i końcowa cześć projektu oprała się na pracy nad logiką i porszuaniem się windy oraz dodania ostatnich potrzebnych elementów takich jak np. przemieszczanie się osób. Na końcu naprawiliśmy ewentualne błędy oraz dopracowliśmy wszelkie niedociągnięcia. 'POLECENIE 3 (1)'
> Do osoby przypisana jest waga (70kg) w logice sprawdzane jest łączna waga nie przekracza 600kg - wtedy winda nie zabiera osób. 'POLECENIE 3.1'
> Graficznie prezentowana jest aktualna waga pasażerów w windzie na zasadzie kreatywnej reklamy. 'POLECENIE 3.3' 

## DZIAŁANIE WINDY - LOGIKA

Winda sortuje oczekujących w zależności od kierunku - malejąco lub rosnąco - i wybiera jako cel pierwszy element w wektorze (kolejce, zbiorze). Gdy winda dojedzie do celu usuwa dane piętro z oczekujących i wybiera następny cel tzn. pierwszy element, który wcześniej był drugim elementem kolejki. Taki proces się powtarza. Natomiast jeśli nowa osoba chce wejść lub wyjść na pietrze, które nie jest po drodze kierunku windy jest dodawana do drugiej kolejki (drugorzedneOczekujace). Gdy skończą się pietra w wektorze oczekujący następuje przeniesienie pięter/celów z wektora drugorzedneOczekujace do oczekujących i druga kolejka jest czyszczona. Dalej wyżej opisany proces się powtarza. 'POLECENIE 3 (2)'
> Gdy osoby/piętra/cele są po drodze dodwane są normalnie do oczekujących i wektor ten jest sortowany względem kierunku (jak wyżej).
> Gdy osoby wchodzą do windy ich pietroDo zostaje dodane do jednego z wektorów -> w zaleznoci czy cel jest po drodze. 
> Gdy zabranie osób w oczekujących i drugorzedneOczekujacych znaczy to, że winda może wrócić na pozycję początkową po 5s. 'POLECENIE 3.2'
> Gdy winda osiągnie cel usatwiany jest timer na 1s, który powoduje zatrzymanie sie windy na piętrach. 'POLECENIE 3 (3)' 

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

