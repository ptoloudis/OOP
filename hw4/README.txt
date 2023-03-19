 === Περιγραφή των tests της εργασίας ===

t1:  Ελέγχει την εισαγωγή μη αποδεκτής τιμής στον κατασκευαστή HashTable(int) OK
t2:  Ελέγχει τη μέθοδο HashTable::add OK
t3:  Ελέγχει τη μέθοδο HashTable::remove. OK
     Προϋπoθέσεις: HashTable::add(string &)
t4:  Ελέγχει τον copy constructor. OK
     Προϋπoθέσεις: HashTable::add(string &)
t5:  Ελέγχει τον τελεστή HashTable::operator=(HashTable &t) OK
     Προϋπoθέσεις: HashTable::add(string &)
t6:  Ελέγχει τον τελεστή HashTable::operator+=(string&)     OK
     Προϋπoθέσεις: HashTable::operator= 
t7:  Ελέγχει τον τελεστή HashTable::operator-=(string&).    OK
     Προϋπoθέσεις: HashTable::add(string &), HashTable::operator= 
t8:  Ελέγχει τον τελεστή HashTable::operator+(string&)       OK
     Προϋπoθέσεις: HashTable::operator= 
t9:  Ελέγχει τον τελεστή HashTable::operator-(string&)      OK
     Προϋπoθέσεις: HashTable::operator+(string&)
t10: Ελέγχει τον πίνακα μετά από αλλεπάλληλες εγγραφές και διαγραφές. OK

t11: Διατρέχει ένα κενό πίνακα.
t12: Διατρέχει και εκτυπώνει τα περιεχόμενα το πίνακα με τη βοήθεια ενός iterator.   OK, OK e
     Ελέγχει τoυς τελεστές τελεστή ++ (πριν και μετά τον τελεστέο) και !=
t13: Διατρέχει και εκτυπώνει τα περιεχόμενα το πίνακα με τη βοήθεια ενός iterator,  OK, OK e
     μετά από αρκετές προσθαφαιρέσεις περιεχομένου.
     Ελέγχει τoυς τελεστές τελεστή ++ (πριν και μετά τον τελεστέο) και !=  
t14: Ελέγχει τους τελστές =, ==, ++it, it++ . OK, OK e

t15: Ελέγχει τον τελεστή ExtHashTable::operator+=(string&)  OK
t16: Ελέγχει τον τελεστή ExtHashTable::operator-=(string&). OK
     Προϋπoθέσεις: ExtHashTable::add(string &)
t17: Ελέγχει τον copy constructor. OK
     Προϋπoθέσεις: ExtHashTable::operator+=(string &)  
t18: Ελέγχει τον τελεστή ExtHashTable::operator=(const ExtHashTable &t) OK   
     Προϋπoθέσεις: ExtHashTable::operator+=(string &)
t19: Ελέγχει τον τελεστή ExtHashTable::operator+(const ExtHashTable &t) OK
     Προϋπoθέσεις: ExtHashTable::operator+=(string &)
t20: Ελέγχει τον τελεστή ExtHashTable::operator+=(const ExtHashTable &t) OK
     Προϋπoθέσεις: ExtHashTable::operator+=(string &)

