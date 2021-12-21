# Predecoding and Direct Threaded Interpretation 

So, moving the a threaded interpreation ends up taking out the naively dispatch loop but we still have some sort of centralized dispatch table. 

Looking up this still requires a memory access, and it would be great if we could elimnate that. 

The notion, of precoding...

-- Notes at page 34 at this point. 
