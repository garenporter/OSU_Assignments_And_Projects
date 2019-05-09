group_wrestlers(graph){

    //used to keep track of visited wrestlers
    visited = new list with size of total number of wrestlers
    //used to keep track of graph level of each wrestler
    level = new list with size of total number of wrestlers
    //used to know when each vertex has been looked at
    queue = new queue

    //initialze data structures
    s = 0
    visited[s] = 0
    level[s] = 0
    push s onto queue

    //loop until queue is empty (no more wrestler vertices)
    while queue is not empty{
        s = front of queue
        pop queue
        j = 0   //used to check for first iteration
        for each wrestler i connected to wrestler s{
            if i has been not been visited{
                set i to have been visited
                set i's level to be that of its parent'
                push i onto queue
            }
            //if child vertex has same level as it's parent's
            //level, and this is not the first iteration of
            //the for loop, then the graph is not bipartite
            //and the wrestlers cannot be put in 2 groups
            else if s's level == i's level and j == 0{
                //graph is not bipartite, so return
                return
            }
            j++
        }
    }

    //at this point, we know wrestlers can be put in 2 groups
    //parse graph and group wrestlers into babyfaces and heels
    for each row i in graph{
        for each column j in each row{
            if j == 0 && graph[i][j] is not grouped
                graph[i][j] = babyface
            
            else if graph[i][j] is not grouped
                graph[i][j] = oppisite group as graph[i][0]
        }
    }
}