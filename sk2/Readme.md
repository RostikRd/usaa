# Domáca skúška - Opravný termín - Kalkulačka
------------
## Zadanie
Naprogramuj vedeckú kalkulačku. Kalkulačka by mala vyhodnocovať aj zložitejšie výrazy v infixnej notácii.

Kalkulačka by mala podporovať tieto operácie:

- načítanie a prácu s číslami s presnosťou min. 2 desatinné miesta.
- sčítanie, odčítanie, násobenie, delenie, zátvorky.
- sinus, cosinus, odmocnina, druhá mocnina, logaritmus.

Pri riešené môžete využiť prepis infixovej formy zápisu do postfixovej. Potom môžete problém riešiť ako "zásobníkovú" kalkulačku.

------------
## Príklad použitia
| Priklad  | Výsledok  |
| ------------ | ------------ |
| (2 + 3) * 2  |10 |
|  (10 * 2) + (6 / 2) |   23|
|  sin(30) |   0.5|
| sqrt(25)  |  5 |
|log(10)| 1|

------------
## Opis funkčnosti
Táto vedecká kalkulačka umožňuje vykonávať základné matematické operácie a funkcie vrátane:
- Základných operácií: +, -, *, /.
- Podporuje zátvorky na správne vyhodnotenie poradia operácií.
- Matematické funkcie: sin(), cos(), sqrt(), log().
- Spracovanie chýb: delenie nulou, odmocnina záporného čísla, logaritmus nenulového čísla.

------------
## Opis riešenia
Program používa rekurzívny zostup (Recursive Descent Parsing) na analýzu a vyhodnotenie infixových výrazov.
Hlavné kroky:
- Spracovanie čísiel a funkcií (`double reading_num()`, `double calculation_trigonometry()`).
- Spracovanie exponentov (mocnina) (`double calculation_exponent()`).
- Spracovanie násobenia/delenia (`double calculation_divide_multi()`).
- Spracovanie sčítania/odčítania (`double main_calculation(const char* input)`).

------------
## Hlavná funkcia
`double main_calculation(const char* input)`
Táto funkcia vykonáva spracovanie a vyhodnotenie matematického výrazu zadaného používateľom.
- Vstup: reťazec obsahujúci matematický výraz.
- Výstup: výsledok výpočtu (ako double).
- Použitie:
    char input[length_of_exercise];
    fgets(input, length_of_exercise, stdin);
    printf("Result: %.2lf\n", main_calculation(input));
------------
## Podmienky správneho fungovania
1. Správne uzatvorené zátvorky.
2. Čísla musia byť v korektnom formáte (napr. 2.5, ale nie 2..5).
3. Funkcie musia byť zadané správne (sin(30), nie sin30).

------------
## Súbory v projekte
- `calculator.h` - hlavičkový súbor s prototypmi funkcií.
- `calculator.c` - implementácia funkcií kalkulačky.
- `main.c` - obsahuje funkciu main().
- `Makefile` - pravidlá na kompiláciu programu.

------------
## Kompilácia a spustenie
Preloženie programu pomocou Makefile:
***`make calculator`***

Spustenie programu:
***`./calculator`***

------------
## Zdroje
Math.h -> https://devdocs.io/c/numeric/math

Recursive descent parser -> https://en.wikipedia.org/wiki/Recursive_descent_parser

Readme.md -> https://pandao.github.io/editor.md/en.html
