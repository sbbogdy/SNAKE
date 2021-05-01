# Descriere
Snake.\
Un sarpe se plimba, mancand mere, pentru fiecare mar, el creste. Scopul este simplu: Ajuta sarpele sa cresca cat de lung posibil.\
Jocul are 2 moduri de joc:\
1. Tu il controlezi pe sarpe, participand astfel in aventura de mancat mere.\
2. Lasi sarpele la mana calculatorului, care stie sa il controleze pe sarpe probabil mai bine ca un om de rand.\
Un simplu cod in c++ pentru un simplu joc.

# Interfata
Pentru GUI m-am folosit de pachetul SFML. Astfel am reusit sa ii ofer jocului un aspect simplistic, desi snake ca joc ar putea fi jucat si in consola.\
Din SFML am preluat librariile:\
opengl32.lib\
sfml-system-d.lib\
sfml-window-d.lib\
sfml-graphics-d.lib\
sfml-main-d.lib

# Modul 1: Play yourself
Tu il controlezi pe sarpe. Acesta este modul in care jocul este un joc, si nu o lunga animatie.\
Este controlata directia in care sarpele merge, cu scopul de a ajunge la un mar. Putem considera miscarea sarpelui ca miscare capului, restul corpului urmarind capul. Cand sarpele mananca un mar, lungimea acestuia creste cu 1, iar un nou mar va aparea intr-o pozitie aleatorie.
Jocul tot merge asa pana cand capul sarpelui iese afara din teren sau cand capul intra in contact cu corpul.\
Controalele sunt: W-sus, A-stanga, S-jos si D-dreapta.

# Modul 2: Watch it play
Jocul se joaca singur. Pentru a realiza asta, am generat un graf, fiecare patratel al terenului reprezentand un nod. pentru acest graf, am generat un ciclu Hamiltonian.
Acest ciclu ii permite sarpelui sa mearga prin fiecare patratel unu cate unu, fara sa intercaleze propriul sau corp pe drum, garantand un scor maxim.
