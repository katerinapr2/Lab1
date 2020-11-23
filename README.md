# Αρχιτεκτονική Υπολογιστών
## Εργαστήριακή Άσκηση 1 

#### _Παπαδόπουλος Γρηγόρης - 9441_
#### _Πρόκου Κατερίνα - 9476_  

##### ~~~ Αναλυτική αναφορά ~~~

**1.** _Βασικά χαρακτηριστικά συστήματος από το αρχείο starter_se.py_:  
 * cache_line size: 64bytes
 * voltage domain: 3.3V
 * clock domain: 1GHz
 * type of CPU: minor 
 * CPU_frequency: 4GHz
 * number of cores: 1
 * CPU_voltage: 1.2V
 * memory type: DDR3_1600_8x8
 * memory channels: 2
 * memory ranks per channel: none
 * memory size: 2GB
	
**2.** 
 _α)_   _config.ini_:  
        [ _system_ ]   cache_line_size=64  
	[ _system.voltage_domain_ ] voltage=3.3  
	[ _system.clk_domain_ ]	clock=1000  
	[ _system.cpu_cluster.cpus_ ] type=MinorCPU  
	[ _system.cpu_cluster.clk_domain_ ] clock=250  
	[ _system.cpu_cluster.cpus_ ] 	numThreads=1   
	[ _system.cpu_cluster.voltage_domain_ ] voltage=1.2  
	[ _system.mem_ctrls0.dram_ ] και αντίστοιχα [ _system.mem_ctrls1.dram_ ]    
	type=DRAMInterface    
    	banks_per_rank=8    
    	devices_per_rank=8  
    	ranks_per_channel=2  
        range=0:2147483648  

  _b)_ Το συνολικό νούμερο των _committed εντολών_ από το _stats.txt_: _system.cpu_cluster.cpus.committedInsts_  είναι 5028. 
  Στο αρχείο _config.ini_ παρουσιάζονται οι εντολές που χρειάζονται για να προσομοιωθεί το σύστημα, ενώ στο αρχείο _stats.txt_ παρουσιάζονται ο αριθμός των συνολικών εντολών που χρειάστηκαν για ολοκληρωθεί το πρόγραμμα "Hello World".

  c)Οι προσπελάσεις της L2 cache από το _stats.txt_: _system.cpu_cluster.l2.overall_accesses::total_ είναι 479.  Αν δεν παρεχόταν από τον εξομοιωτή οι προσπελάσεις της L2 Cache, θα μπορούσαμε να τις υπολογίσουμε προσθέτοντας τα misses της cache(332) και dcache (179).

**3.** 
**SimpleCPU**:
	Είναι ένα λειτουργικό, in-order μοντέλο, το οποίο είναι κατάλληλο  
    για περιπτώσεις όπου δεν είναι απαραίτητο ένα λεπτομερές μοντέλο. Περιλαμβάνει
	περιόδους προθέρμανσης, συστήματα πελατών που οδηγούν έναν κεντρικό υπολογιστή
	ή ελέγχους για το αν λειτουργεί ένα πρόγραμμα. Προκειμένου να υποστηρίξει 
	το νέο σύστημα μνήμης, ξαναγράφτηκε και αποτελείται από τις παρακάτω κατηγορίες:
	
   *  **BaseSimpleCPU**:
	Η συγκεκριμένη έκδοση δεν μπορεί να εκτελεστεί μόνη της.
	Πρέπει να εκτελεστεί μια από τις κλάσεις που κληρονομεί μια από τις
	κλάσεις που κληρονομεί από το BaseSimpleCPU, είτε το AtomicSimpleCPU
	ή το TimingSimpleCPU.

   * **AtomicSimpleCPU**:
	Χρησιμοποιεί προσβάσεις ατομικής μνήμης καθώς και τις καθυστερήσεις
	που έχουν υπολογιστεί στις ατομικές προσβάσεις, για να εκτιμήσει 
	το συνολικό χρόνο πρόσβασης στην cache.
   
   * **TimingSimpleCPU**:
	Χρησιμοποιεί προσβάσεις μνήμης χρονισμού. Σταματά στις cache accesses, 
	και περιμένει να ανταποκριθεί το σύστημα μνήμης, πριν προχωρήσει.
	Οι δύο τελευταίες εκδόσεις προέρχονται από το BaseSimpleCPU και εφαρμόζουν το 
	ίδιο σύνολο λειτουργιών. 

   * **MinorCPU**:
	Είναι ένα in-order μοντέλο επεξεργαστή με δυνατότητα pipelining. Είναι 
	πιο περίπλοκο στην αρχιτεκτονική του και βοηθά στο να προσομοιώνουμε 
	την μικρο-αρχιτεκτονική επεξεργαστών με αντίστοιχες δυνατότητες. 

   _a)_ _TimingSimpleCPU_:  
        final_tick 39989000                    
        host_seconds 0.09  
        sim_seconds 0.000040   
        
  _MinorCpu_: 
	 final_tick 34104000  
	 host_seconds 0.23  
	 sim_seconds 0.000034  
   
   _b)_ Eπειδή το TimingSimpleCPU δεν χρησιμοποιεί pipeline είναι πιο αργό από το minor, κάτι που φαίνεται και στους χρόνους.
	
   _c)_  
* Αλλαγή στο **cpu-clock**=1GHz:

	_TimingSimpleCPU_ :   
	    final_ticks 54995000    
     	host_seconds 0.04    
	    sim_seconds 0.000055      
  
	_MinorCPU_ :    
    	final_ticks 41480000    
    	host_seconds 0.10    
      sim_seconds 0.000041   
      
  Παρατηρούμε πως μειώνοντας το cpu-clock αυξάνεται ο χρόνος εκτέλεσης.	

* Αλλαγή στην **συχνότητα λειτουργίας συστήματος**=500MHz:
	
 	_TimingSimpleCPU_:  
	final_ticks 46159000  
	host_seconds 0.05  
	sim_seconds 0.000046  
	
    _MinorCPU_:     
    final_ticks  40024000  
    host_seconds 0.13  
    sim_seconds 0.000040  
    
Παρατηρούμε πως με την μείωση της συχνότητας λειτουργίας συστήματος, αυξάνεται ο χρόνος εκτέλεσης.
      
* Αλλαγή στην **τεχνολογία μνήμης** = DDR3_2133_8x8 :
	
	_TimingSimpleCPU_:     
            final_tick 38458000  
	    host_seconds 0.04  
	    sim_seconds 0.000038  
	
    _MinorCPU_:   
    final_tick 32931000  
    host_seconds 0.13  
    sim_seconds 0.000033  
    
Παρατηρούμε πως σε σχέση με την DDR3_1600_8x8, η DDR3_2133_8x8 είναι πιο γρήγορη.

##### Κριτική εργασίας:   
Η συγκεκριμένη εργασία, πιστεύουμε πως ήταν μια καλή πρώτη επαφή με το αντικείμενο του εργαστηρίου. Οι οδηγίες ήταν αρκετά κατατοπιστικές και για την εγκατάσταση του gem5, αλλά και για την εκπόνηση της εργασίας. Ήταν σχετικά εύκολη, καθώς στόχευε κυρίως στην κατανόηση του προγράμματος. Παρόλα αυτά χάσαμε αρκετή ώρα σε κομμάτια που εν τέλει δεν χρειαζόταν, όπως στο ερώτημα 3(a). Αξίζει να σημειωθεί, ακόμη, η σημασία των διάφορων εργαλείων που χρησιμοποιήθηκαν, καθώς είχαμε την ευκαιρία να δουλέψουμε και να εξοικειωθούμε με αυτά.

Πηγές: [gem5.org](https://www.gem5.org/)
