# POO_Tema8

Pizzeria X testează un nou soft, dezvoltat în maniera OOP, pentru gestionarea
activității sale. Codul propriu-zis contine o clasa abstracta care contine doar metoda virtuala
pura de calcul al prețului unui produs, iar din aceasta clasa deriva clasa Pizza. În realizarea
oricărui produs intra un anumit număr de ingrediente pentru care se cunosc denumirile,
cantitatile și prețul unitar. Prețul unui produs finit este data de prețul ingredientelor plus
manopera (o suma constanta fixată de producător). Daca pizza este comandata OnLine, la
preț se mai adaugă și 5% din pret la fiecare 10 km parcursi de angajatul care livrează la
domiciliu.

Structura de date: unordered_map sau unordered_set <id_pizza, list sau vector
<ingredient>>

Cerința suplimentară:

- Să se adauge toate campurile relevante pentru modelarea acestei probleme.

- Să se construiască clasa template Meniu care sa gestioneze tipurie de pizza comercializate.

Clasa trebuie sa contina indexul unui produs (incrementat automat la vanzarea unui produs
prin supraincarcarea operatorului +=) și o structură de date, alocata dinamic.

- Să se construiască o specializare pentru tipul Comanda_Online care sa trateze tipurile de
pizza vegetariana într-un document contabil separat din care sa rezulte valoarea totala
incasata din vanzarea acestora.

# Cerințe comune tuturor temelor:
1. utilizarea sabloanelor

2. utilizarea STL

3. utilizarea variabilelor, funcțiilor statice, constantelor și a unei functii const

4. utilizarea conceptelor de RTTI raportat la template-uri

5. tratarea excepțiilor

6. citirea informațiilor complete a n obiecte, memorarea și afișarea acestora


● cerințe generale aplicate fiecărei teme din acest fișier:

- să se identifice și să se implementeze ierarhia de clase;

- clasele să conțină constructori, destructori, =, funcție prietena de citire a datelor;

- clasa de baza sa conțină funcție virtuala de afisare, rescrisa în clasele derivate, iar
operatorul de citire să fie implementat ca funcție prieten (în clasele derivate să se facă
referire la implementarea acestuia în clasa de baza).
