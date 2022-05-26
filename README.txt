 === Περιγραφή των tests της εργασίας ===

t1:  Ελέγχει την εισαγωγή μη αποδεκτής τιμής στον κατασκευαστή HashTable(int) OK

t2:  Ελέγχει τη μέθοδο HashTable::add

t3:  Ελέγχει τη μέθοδο HashTable::remove. 
     Προϋπoθέσεις: HashTable::add(string &)
     
t4:  Ελέγχει τον copy constructor.
     Προϋπoθέσεις: HashTable::add(string &)
     
t5:  Ελέγχει τον τελεστή HashTable::operator=(HashTable &t)
     Προϋπoθέσεις: HashTable::add(string &)
     
t6:  Ελέγχει τον τελεστή HashTable::operator+=(string&)
     Προϋπoθέσεις: HashTable::operator= 
     
t7:  Ελέγχει τον τελεστή HashTable::operator-=(string&). 
     Προϋπoθέσεις: HashTable::add(string &), HashTable::operator= 
     
t8:  Ελέγχει τον τελεστή HashTable::operator+(string&)
     Προϋπoθέσεις: HashTable::operator= 
     
t9:  Ελέγχει τον τελεστή HashTable::operator-(string&)
     Προϋπoθέσεις: HashTable::operator+(string&)
     
t10: Ελέγχει τον τελεστή HashTable::operator+(HashTable&)
     Προϋπoθέσεις: HashTable::operator+=(string&)
     
t11: Διατρέχει ένα κενό πίνακα.

t12: Διατρέχει και εκτυπώνει τα περιεχόμενα το πίνακα με τη βοήθεια ενός iterator.
     Ελέγχει τoυς τελεστές τελεστή ++ (πριν και μετά τον τελεστέο) και !=
     
t13: Διατρέχει και εκτυπώνει τα περιεχόμενα το πίνακα με τη βοήθεια ενός iterator, 
     μετά από αρκετές προσθαφαιρέσεις περιεχομένου.
     Ελέγχει τoυς τελεστές τελεστή ++ (πριν και μετά τον τελεστέο) και !=
     
t14: Ελέγχει τους τελστές =, ==, ++it, it++ .

t15: Ελέγχει τον τελεστή ExtHashTable::operator+=(string&)

t16: Ελέγχει τον τελεστή ExtHashTable::operator-=(string&). 
     Προϋπoθέσεις: ExtHashTable::add(string &)
     
t17: Ελέγχει τον copy constructor.
     Προϋπoθέσεις: ExtHashTable::operator+=(string &)
     
t18: Ελέγχει τον τελεστή ExtHashTable::operator=(const ExtHashTable &t)
     Προϋπoθέσεις: ExtHashTable::operator+=(string &)
     
t19: Ελέγχει τον τελεστή ExtHashTable::operator+(const ExtHashTable &t)
     Προϋπoθέσεις: ExtHashTable::operator+=(string &)
     
t20: Ελέγχει τον τελεστή ExtHashTable::operator+=(const ExtHashTable &t)
     Προϋπoθέσεις: ExtHashTable::operator+=(string &)

