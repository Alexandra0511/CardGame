Voicila Alexandra, grupa 312CD

	Am inceput cu un pointer la o lista head, ce are campurile corespunzatoare unei carti: culoare, numar, valoare si rank. Pentru initializarea pachetului, am introdus pe rand, la inceputul listei cate o carte, incepand cu 2 si terminand cu cartile speciale, respectiv mai mari de J(12).

	AMESTECARE
	Pentru functia de inversare, am facut o interschimbare intre elementele din prima jumatate si cele din a doua jumatate dupa regula: cartea de pe pozitia i isi va interschimba campurile cu cartea de pe pozitia dimensiune(pachet)-i+1.
	Pentru intercalare, am impartit pachetul in 2 jumatati si am mutat cate un element din jumatatea stanga intre 2 din jumatatea dreapta dupa regula din enunt.
	In mongean, am mutat doar elementele de pe pozitiile pare la inceputul listei.
	Pentru functia npiles, am utilizat un vectori de liste. Parcurgand lista, am populat acest vector cu subliste in numar de n-ul primit ca parametru in functie. apoi, am dorit sa reconstruiesc lista mea initiala head, asa ca i-am eliberat memoria si am reinitializat-o cu NULL. Apoi, am adaugat in ordinea specificata prin vectorul primit ca parametru, elementele din subliste. La sfarsit am eliberat memoria alocata acestora.
	
	RAZBOI
	Functia rezultatRazboi am facut-o de tip struct pentru a putea returna si castigatorul si cartea cu care acesta a castigat in cazul in care numarul mainilor depasea 100. Am luat pe rand cate un caz. Daca un jucator da o carte mai mare decat celalalt, acesta isi muta prima carte (cea cu care a castigat mana) la sfarsit (prin intermediul functiei MoveFirstToEnd), apoi adauga cartea adversarului, care ulterior va fi stearsa din pachetul acestuia. In cazul in care rankul cartilor este acelasi, am creat 2 liste ajutatoare listaR1 si listaR2 care contin cartile pe care cei doi le dau jos pentru a afla rezultatul razboiului. Ulterior, am adaugat ambele liste la pachetul castigatorului. In functie de modul in care s-a terminat jocul am intors rezultatul. Daca jocul s-a terminat dupa 100 de maini, am utilizat doi vectori de frecventa pentru a tine cont de scorurile jucatorilor.

	MAIN
	Am facut citirea din fisier si, in functie de cerinta, am afisat prin intermediul celor doua functii de afisare.
	
