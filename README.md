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
- **Unikanie zakleszczeń**: Filozof czeka, aż oba widelce będą dostępne i dopiero wtedy podnosi a, po zakończeniu jedzenia powiadamia sąsiadów o zwolnieniu zasobów.

