# Dining Philosophers Problem

## Uruchomienie
```sh
g++ main.cpp -o projekt
./projekt (liczba_filozofów)
```

## Opis Problemu
Symulacja klasycznego problemu ucztujących filozofów, gdzie filozofowie muszą zdobywać dostęp do wspólnych zasobów (widelców) w celu jedzenia, unikając zakleszczeń (deadlock).

## Wątki
- Każdy filozof to osobny wątek, który cyklicznie myśli, staje się głodny i próbuje jeść.

## Sekcje Krytyczne
- **Uzyskanie dostępu do widelców**: Synchronizacja za pomocą `mutex` i `condition_variable`, aby zapewnić, że sąsiedzi nie jedzą jednocześnie.
- `condition_variable` sprawia że filozof nie musi ciągle sprawdzac dostępnosci widelca tylko jest powiadamiany
- **Unikanie zakleszczeń**: Filozof czeka, aż oba widelce będą dostępne i dopiero wtedy podnosi a, po zakończeniu jedzenia powiadamia sąsiadów o zwolnieniu zasobów.

# Serwer Czatu

##Uruchomienie
```sh
g++ Server.cpp -o Server -lws2_32
g++ Client.cpp -o Client -lws2_32
./Server
./Client
```

## Opis Problemu
Prosty czat Klient-Serwer z wykorzystaniem socektow TCP. Pozwala na komunikacje wielu klientów jednoczesnie dzięki wielkowątkowsci i synchronizacji do zasobów współdzielonych.

## Wątki
- Wątek główny (serwer): nasłuchuje na połączenia i tworzy nowe wątki dla klientów.
- Wątek klienta (dla każdego połączenia): obsługuje komunikację z jednym klientem.
- Wątek klienta (aplikacja kliencka) nasłuchujący: obsługuje odbieranie danych z serwera.
- Wątek klienta główny: obsługuje wysyłanie danych do serwera.

## Sekcje Krytyczne
- Odczytywanie historii czatu
- Dodawanie wiadomosci do historii czatu
- Wysyłanie wiadomosci do klientów
- Dodawanie klientów
- Usuwanie klientów
## Unikanie zakleszczen
Kazda sekcja korzysta tylko z jednego mutexa, brak oczekiwania na zasoby.

