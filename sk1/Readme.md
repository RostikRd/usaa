# Domáca skúška - Riadny termín: Kompressor

## Znenie úlohy:
Naprogramuj nástroj na kompresiu a dekompresiu.

Na kompresiu použite aspoň dva kompresné algoritmy, napr. : Huffmanovo kódovanie, LZ77, LZ78, Run Length kódovanie alebo iný. Môžete vymyslieť aj vlastný algoritmus.

Kompresor a dekompresor by mal byť schopný pracovať s ľubovoľným binárnym súborom do 10 MB. Súbor by mal byť po skomprimovaní menší minimálne o 10 percent a po dekomprimovaní by mal byť zhodný s pôvodným súborom.

Na otestovanie kompresora a dekompresora použite súbory z Canterbury corpus.

Riešenie nesmie využívať inú ako štandardnú knižnicu. Riešenie sa môže inšpirovať voľne dostupným cudzím riešením za predpokladu že uvediete zdroj, ste podrobne oboznámený so zdrojovým kódom a viete odpovedať na otázky týkajúce sa kódu. Vaše riešenie nemôže kopírovať cudzie riešenie. V prípade, že použijete generatívny model, napíšte ktorý a napíšte aj prompt ktorý ste použili.

Program by mal mať takéto rozhranie pri spustení z príkazového riadka:
# skomprimuje infile do súboru outfile
./compressor -c infile outfile
# dekomprimuje sUbor compressed a zapise do suboru uncompressed.
./compressor -d compressed uncompressed
./compressor -h  # Vypíše pomoc

Meno vstupného a výstupného súboru načítajte ako argument príkazového riadka. V zadaní by mali byť implementované tieto štyri funkcie:

/**
 * Skomprimuje súbor s názvom input_file_name pomocou kompresného algoritmu 1
 * a zapíše do súboru s názvom output_file_name
 * @arg input_file_name vstupný súbor (na čítanie)
 * @arg output_file_nameout výstupný súbor (na zápis)
 * @return počet bajtov skomprimovaného súboru v prípade úspechu. Zápornú hodnotu v prípade chyby.
 */
int compress_1(const char* input_file_name, const char* output_file_name);
/**
 * Dekomprimuje súbor skomprimovaný pomocou algoritmu 1 in a zapíše do súboru out. 
 * @arg input_file_name vstupný súbor (na čítanie)
 * @arg output_file_nameout výstupný súbor (na zápis)
 * @return počet bajtov deomprimovaného súboru v prípade úspechu. Zápornú hodnotu v prípade chyby.
 */
int decompress_1(const char* input_file_name, const char* output_file_name);
/**
 * Skomprimuje súbor s názvom input_file_name pomocou kompresného algoritmu 2
 * a zapíše do súboru s názvom output_file_name
 * @arg input_file_name vstupný súbor (na čítanie)
 * @arg output_file_nameout výstupný súbor (na zápis)
 * @return počet bajtov skomprimovaného súboru v prípade úspechu. Zápornú hodnotu v prípade chyby.
 */
int compress_2(const char* input_file_name, const char* output_file_name);
/**
 * Dekomprimuje súbor skomprimovaný pomocou algoritmu 2 in a zapíše do súboru out. 
 * @arg input_file_name vstupný súbor (na čítanie)
 * @arg output_file_nameout výstupný súbor (na zápis)
 * @return počet bajtov deomprimovaného súboru v prípade úspechu. Zápornú hodnotu v prípade chyby.
 */
int decompress_2(const char* input_file_name, const char* output_file_name);

##Stručný opis funkčnosti

- Program skompilujte pomocou príkazu

    ````c
     make
    ````
- 1)Spustite program pomocou príkazu pre algoritmus RLE:
    
    * compresia
    ````c
     ./compressor -c1 input_file_name output_file_name
    ````

    * decompresia
    ````c
     ./compressor -d1 input_file_name output_file_name
    ````

- 2)Spustite program pomocou príkazu pre algoritmus LZ77:
    
    * compresia
    ````c
     ./compressor -c2 input_file_name output_file_name
    ````

    * decompresia
    ````c
     ./compressor -d2 input_file_name output_file_name
    ````
- 2)Vypíše zoznam prikazov:

    ````c
     ./compressor -h
    ````

##Stručný opis riesenia

###funkcie
-Funkcia read_file_in_memory otvorí súbor v binárnom režime, prečíta jeho obsah do vyhradeného dynamického buffera a vráti ukazovateľ na      	tento buffer. Veľkosť súboru je uložená v premennej, na ktorú ukazuje size. Ak sa súbor nepodarilo otvoriť, alokovať alebo 	prečítať, funkcia vráti NULL.

-Funkcia write_memory_in_file otvorí súbor v binárnom režime na zápis, zapíše do neho obsah vyrovnávacej pamäte inf s veľkosťou size 	bajtov a súbor uzavrie. V prípade úspechu vráti 0, ak sa súbor nepodarilo otvoriť, vráti -1.

-Funkcia compress_1 realizuje compressing algoritmu RLE:

	1) Číta súbor do vyrovnávacej pamäte.

	2) Analyzuje postupnosť znakov a nahradí duplicitné znaky dvojicami (čítač, znak).

	3) Uloží komprimované údaje do výstupného súboru.

	4) Vráti veľkosť komprimovaných údajov alebo -1 v prípade chyby.

-Funkcia decompress_1 realizuje uncompressing algoritmu RLE:

	1) Číta komprimovaný súbor do vyrovnávacej pamäte.

	2) Dekomprimuje každú dvojicu (čítač, znak) a pridá požadovaný počet znakov do výstupného buffera.

	3) Uloží dekomprimované údaje do súboru.

	4) Vráti veľkosť dekomprimovaných údajov alebo -1, ak nastala chyba.

-Funkcia compress_2 realizuje compressing algoritmu LZ77:

	1) Číta vstupný súbor do vyrovnávacej pamäte.

	2) Analyzuje aktuálny znak a nájde najdlhšiu zhodu s predchádzajúcimi údajmi v rámci posuvného okna (SIZE).

	3) Ak sa nájde zhoda s dĺžkou ≥ 3, zakóduje ju ako trojicu (vzdialenosť, dĺžka, znak).

	4) Ak je zhoda kratšia, zapíše znak tak, ako je.

	5) Uloží komprimované údaje do výstupného súboru.

	6) Vráti veľkosť komprimovaných údajov alebo -1 v prípade chyby.

-Funkcia decompress_2 realizuje uncompressing algoritmu LZ77:

	1) Číta komprimovaný súbor do vyrovnávacej pamäte.

	2) Analyzuje každý záznam:
		2.1) Ak ide o trojicu (vzdialenosť, dĺžka, znak), skopíruje opakovanú sekvenciu do výstupného buffera.

		2.2) Ak je to jeden znak, pridá ho do výstupného buffera.

	3) Uloží rozbalené údaje do súboru.

	4) Vráti veľkosť rozbalených údajov alebo -1 v prípade chyby.

##Podmienky za ktorých funguje
- Správne volanie funkcie: Kód predpokladá, že kompresné a dekompresné funkcie (Compress a Decompress) sú volané s platnými názvami vstupných a výstupných súborov.

- Dostupnosť vstupného súboru: Pre kompresiu (Compress) by mal vstupný súbor špecifikovaný menom vstupného_súboru existovať a byť prístupný na čítanie v binárnom režime ("rb").

- Dostupnosť výstupného súboru: Výstupný súbor špecifikovaný názvom výstupného súboru by buď nemal existovať, alebo by mal byť prístupný na zápis v binárnom režime ("wb"). Ak existuje, jeho obsah sa prepíše.

- Kompatibilita formátu hlavičky: Funkcie kompresie a dekompresie sa spoliehajú na špecifický formát hlavičky. Ak sa súbor komprimovaný touto implementáciou pokúsi dekomprimovať iný program alebo iná verzia kódu, nemusí fungovať správne.

- Rozsah reprezentácie symbolov: Kód predpokladá, že symboly vo vstupných údajoch sú reprezentované ako celé čísla v rozsahu [0, 255]. Tento predpoklad sa odráža v podmienkach cyklu a indexovaní poľa.

- Úspešná alokácia pamäte: Kód používa funkcie dynamickej alokácie pamäte (malloc) na alokáciu pamäte polia.


##Zoznam použitých zdrojov

https://www.geeksforgeeks.org/run-length-encoding/

https://en.wikipedia.org/wiki/Run-length_encoding

https://www.youtube.com/watch?v=jVcTrBjI-eE

https://en.wikipedia.org/wiki/LZ77_and_LZ78

https://moodle.tuke.sk/moodle/pluginfile.php/92479/mod_resource/content/1/2016-02-Subory-2.pdf



Dodatočné informácie:
Nemohol som napísať program tak, aby spúšťal dva algoritmy súčasne, preto som najprv na webovej stránke Traktor skontroloval algoritmus RLE a potom algoritmus LZ77. Na otestovanie algoritmu RLE som v súbore main.c zmenil argumenty pre compressor_1 na -c a pre decompressor_1 na -d (ako je uvedené v podmienke). To isté som urobil aj pri testovaní algoritmu LZ77. Pre oba algoritmy v programe Traktor mám dve rôzne percentá vykonávania: 
RLE - 100 %.  
LZ77 - 85 % (1 súbor neprešiel testom). Pri ručnej kontrole úlohy však môžete program otestovať aj s inými argumentmi, sú uvedené v Stručnom opise funkčnosti.


Použil som preklad Google, ospravedlňujem sa za čudné slová.












