first_fit(cap, items[]){
    bins = empty list of integers   //each int represents a bin
    bins[0] = cap   //add empty bin to start

    for each item i in items{
        for each bin b in bins{
            if i <= b       //if i fits in b
                b = b - i   //pack i in b
        }
        if i did not fit in any bins
            add new bin to bins         
            place i in newly added bin   
    }
    return bins.size    //total bins needed
}

first_fit_decreasing(cap, items[]){
    sort items in decreasing order  //merge sort

    return first_fit(cap, items[])  //perform first fit to get number of bins used
}

best_fit(cap, items[]){
    bins = empty list of integers   //each int represents a bin
    bins[0] = cap   //add empty bin to start

    for each item i in items{
        room = 0    //smallest leftover room
        room_loc = 0    //bin with smallest leftover room
        for each bin b in bins{
            if i <= b  {     //if i fits in b
                if i is the first item to fit in a bin{
                    room = b-1  //set smallest leftover room
                    room_loc = b
                    continue
                }
                //check if packing i in b leaves less room than room
                if b - i < room {  
                    room = b - i    
                    room_loc = b    //set b as new best-fit bin
                }
            }
        }
        if i did not fit in any bins{
            add new bin to bins         
            place i in newly added bin   
        }
        //place i in best-fit bin
        else
            bins[room_loc] = bins[room_loc] - i

    }
    return bins.size    //total bins needed
}