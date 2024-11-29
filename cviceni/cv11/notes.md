## Opravy

- import `uint8_t` a `size_t`
- `virtual ~IAnalyzer()`, chybějící virtuální destruktor v `IDrawing`
- `#include "Drawing.h"` → `#include "drawing.h"`, hodně přebytečných include
- chybějící `Color &operator=`
- chybějící `const` u metod
- `DummyAnalyzer::Save_Image` nepoužitý argument
- odstranit zbytečné `virtual` a přidat chybějící `override`
- manuální implementace constructorů místo ekvivalentního `= default`
- `reinterpret_cast` místo C-castu

## Vylepšení

- RAII `vector` místo new/delete pole
- `Histogram` je flat vector
- iterace pomocí `ranges` a adaptérů
- if-not-continue, místo try-catch pro bounds check
- `vector.resize` místo opakovaného `push_back`
- maximum pomocí `ranges`
- `PPMDrawing` ukládá pixely v jednom vectoru a vypisuje najednou

## Další možnosti

- lepší interface mezi `Histogram` a `PPMDrawing` - odpadla by zbytečná konverze
  `index` -> `x`,`y` -> `index` a potenciálně i vůbec potřeba kopírovat data

## Výsledek

- `-Wall` nehlásí žádné varování
- ASAN/valgrind nehlásí žádné problémy
- zrychlení 3300 ms → 850 ms (oboje s optimalizacemi), většina času už je IO

Všechny změny oproti výchozímu kódu (vyjma formátovaní) jsou v `cv11.diff`.
