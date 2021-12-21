# Threaded Interpretation 

Here we will see if we can minimize some of the performance cost for a simple decode-and-dispatch interpreter. 

There's just a ton of branches that we would have to deal with, so let's try to minimize it as they tend to reduce performance. 

So with threaded interpreter, we can elimnate a needed loop. 

The control flow of such is much easier than a dispatch loop where we have to fetch and decode instructions. 


