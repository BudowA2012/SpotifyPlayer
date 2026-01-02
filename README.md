# SpotifyPlayer
🎵 ESP32 SpotifyPlayer to projekt biurkowego wyświetlacza muzycznego, który w czasie rzeczywistym pokazuje informacje o aktualnie odtwarzanym utworze ze Spotify. Urządzenie zostało zbudowane w oparciu o ESP32 oraz kolorowy ekran TFT 2.4" z kontrolerem ILI9341, zapewniający czytelny i estetyczny interfejs użytkownika inspirowany widżetem Spotify znanym z paska powiadomień w telefonach 📱✨

ESP32 łączy się z lokalną siecią Wi-Fi i komunikuje się z prostym serwerem napisanym w Pythonie (Flask), który obsługuje autoryzację Spotify API oraz przekazuje aktualne dane o utworze 🎧🌐. Na ekranie wyświetlany jest tytuł piosenki, wykonawca oraz pasek postępu pokazujący, ile utworu już minęło i ile pozostało – bez migania ekranu i zbędnych przeładowań UI ⏱️📊.

Projekt został zaprojektowany jako urządzenie stacjonarne, zasilane bezpośrednio przez port USB ESP32 🔌, bez użycia baterii. Całość może zostać zamknięta w drukowanej w 3D obudowie, która mieści zarówno ekran, jak i płytkę ESP32, z wyprowadzonym portem USB na zewnątrz obudowy 🖨️📦.
