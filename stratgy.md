```md
# ESP-IDF Watch Projekt – Gesamtüberblick, Regeln & Erkenntnisse

Dieses Dokument fasst **alle wichtigen Erkenntnisse, Design-Entscheidungen und Regeln** aus dem bisherigen Chat zusammen.  
Ziel: **mentale Klarheit**, **saubere Architektur**, **keine Überforderung**, **skalierbar für viele ESPs mit Display**.

---

## 1. Ziel des Projekts (klar definiert)

Wir bauen:

- eine **Embedded Watch / Device Firmware**
- mit **grafischer UI direkt auf dem Gerät**
- basierend auf **ESP-IDF + LVGL**
- die **offline funktioniert**
- und **auf vielen ESPs mit Display portierbar ist**

Nicht Ziel:
- kein eigenes OS
- keine Drittanbieter-Apps
- keine automatische Display-Erkennung
- kein Overengineering

---

## 2. Das große Architektur-Bild (essentiell)

Das Projekt besteht aus **drei klar getrennten Ebenen**:

```

[ Hardware (ESP + Display + Touch) ]
↓
[ BSP – Board Support Package ]
↓
[ Core – App + UI + Logik ]

````

### Bedeutung:
- **Core** = dein Produkt → bleibt IMMER gleich
- **BSP** = Hardware-Adapter → austauschbar pro Board/Display
- **Hardware** = konkrete ESP + Display-Kombination

👉 Portabilität entsteht durch **Trennung**, nicht durch Magie.

---

## 3. Zentrale Design-Regel (wichtigste Erkenntnis)

### ❗ Es gibt genau EINE Wahrheit:
```c
app_state_t state;
````

* Die **Logik** ändert den State
* Die **UI** zeigt den State
* Die **UI denkt nicht**
* Die **UI entscheidet nichts**

Kein direkter UI-Zugriff aus der Logik:
❌ `lv_label_set_text(...)` irgendwo in App-Code
✅ `state.xyz = ...; ui_bind_all(&state);`

---

## 4. Datenfluss (mentales Modell)

### Beispiel: Start/Stop Button

1. User tippt Button
2. LVGL ruft Event-Callback
3. Callback ruft `app_on_start_stop()`
4. Logik ändert `state.is_running`
5. `ui_bind_all()` aktualisiert das UI

👉 UI ist ein **Spiegel**, kein Akteur.

---

## 5. Ordnerstruktur (revidiert & sinnvoll)

ESP-IDF-native Struktur mit Components:

```
/CMakeLists.txt
/sdkconfig
/main
  main.c

/components
  /core
    CMakeLists.txt
    include/
      app.h
      app_state.h
    app.c
    app_state.c
    ui/
      ui.h
      ui_create.c
      ui_styles.c
      ui_bindings.c
      ui_events.c

  /bsp
    CMakeLists.txt
    include/
      bsp.h
    bsp.c
    boards/
      generic_spi/
        board_config.h
        display_spi.c
        touch_none.c
```

---

## 6. Erklärung der Hauptbestandteile

### `/main/main.c`

* Minimaler Einstiegspunkt
* Ruft:

  * `bsp_init()`
  * `app_init()`
* Startet LVGL Loop (`lv_timer_handler()`)

❗ Keine Pins, kein UI-Code hier.

---

### `/components/core` – das Produkt

#### `app_state.c/h`

* Single Source of Truth
* Enthält:

  * Session-Status
  * Zeiten
  * Battery
  * Connection
  * History-Daten

#### `app.c`

* App-Logik:

  * Start/Stop
  * Timer
  * Session-Verwaltung
* Ändert nur State, nie direkt UI

#### `/ui/`

UI ist bewusst in 4 Teile getrennt:

* `ui_create.c`
  → Baut Screens & Layout (einmalig)

* `ui_styles.c`
  → Farben, Fonts, Spacing, Buttons

* `ui_bindings.c`
  → Schreibt `app_state` in UI (lebt hier)

* `ui_events.c`
  → Button-Callbacks → rufen App-Funktionen

---

### `/components/bsp` – Hardware-Abstraktion

#### `bsp.h`

Minimales Interface:

* `void bsp_init(void);`

#### `bsp.c`

* Registriert LVGL Display- & Input-Driver
* Wählt Treiber anhand Board-Konfiguration

#### `/boards/generic_spi`

Ein **Board-Pack**:

* `board_config.h`

  * Pins
  * Auflösung
  * Rotation
  * Display-Typ

* `display_spi.c`

  * Display-Init
  * LVGL flush callback

* `touch_none.c`

  * Dummy-Touch (für Boards ohne Touch)

👉 Neues Board = neues Board-Pack
👉 Core bleibt unverändert

---

## 7. Was „universell für jeden ESP“ wirklich heißt

* Es gibt **keine** Firmware, die automatisch jedes Display erkennt
* Universalität entsteht durch:

  * klare BSP-Schicht
  * austauschbare Board-Packs

Realistisch:

* 1–2 Dateien pro neuem Board
* keine Änderungen im Core

---

## 8. LVGL-spezifische Regeln

* LVGL läuft nur, wenn:

  * Display-Treiber korrekt registriert
  * `lv_timer_handler()` regelmäßig läuft
* UI-Objekte:

  * werden **einmal** erstellt
  * werden **nicht** ständig neu erzeugt
* Dynamik passiert nur über Bindings

---

## 9. Reihenfolge der Umsetzung (kritisch)

### Phase 1 – Fundament

* ESP-IDF Projekt
* BSP für EIN Display
* „Hello UI“

### Phase 2 – UI-Struktur

* Styles
* Screens (Home / Session / History)

### Phase 3 – State + Bindings

* app_state
* Timer
* sichtbare Dynamik

### Phase 4 – Events

* Start/Stop
* Navigation

### Phase 5 – erst dann:

* Storage
* BLE
* Sync

👉 **Nie** UI + BLE + Storage gleichzeitig anfangen.

---

## 10. Was explizit vermieden wird

* Business-Logik im UI
* Hardware-Zugriffe im Core
* Globale UI-Objekte überall
* Frühzeitige Optimierung
* „Wir machen das später sauber“-Code

---

## 11. Entscheidungs-Status (final)

* Framework: **ESP-IDF**
* UI: **LVGL**
* Ziel: **on-device UI**
* Portabilität: **BSP + Board-Packs**
* Architektur: **State-driven UI**

Diese Entscheidungen sind konsistent, sinnvoll und skalierbar.

---

## 12. Aktueller Stand / Nächstes To-do

**Aktuell:**
To-do 1 – ESP-IDF Projekt anlegen (Hello World)

**Als Nächstes:**
To-do 2 – Projektstruktur + erstes BSP (ein Display)

---

## 13. Mentale Leitlinie (zum Schluss)

> „Erst sichtbar, dann interaktiv, dann komplex.“

Wenn du UI siehst, bist du auf dem richtigen Weg.



```
```
