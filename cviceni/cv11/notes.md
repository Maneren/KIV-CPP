## Opravy

- import `uint8_t` a `size_t`
- `virtual ~IAnalyzer()`
- `#include "Drawing.h"` → `#include "drawing.h"`
- chybějící `Color &operator=`
- `DummyAnalyzer::Save_Image` nepoužitý argument

## Vylepšení

- RAII `vector` místo new/delete pole
- `Histogram` je flat vector
- iterace pomocí `ranges` a adaptérů
- if-not-continue, místo try-catch pro bounds check
- `vector.resize` místo opakovaného `push_back`
- `reinterpret_cast` místo C-castu
- maximum pomocí `ranges`
- `PPMDrawing` ukládá pixely v jednom vectoru a vypisuje najednou

## Další možnosti

- lepší interface mezi `Histogram` a `PPMDrawing` - odpadla by zbytečná konverze
  `index` -> `x`,`y` -> `index` a potenciálně i vůbec potřeba kopírovat data

## Výsledek

- `-Wall` nehlásí žádné varování
- ASAN/valgrind nehlásí žádné problémy
- zrychlení 3300 ms → 850 ms (oboje s optimalizacemi), většina času už je IO
