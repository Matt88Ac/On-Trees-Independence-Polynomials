install.packages("R6")
library(R6)






TreeGraph <- setRefClass("TreeGraph",  fields = list(  size_v = "numeric", size_e = "numeric", V = "vector", E = "matrix", 
                                                       max_deg_index = "numeric", origin_size="numeric"    )  )


TreeGraph$methods( 
  init = function(size = "numeric" ){
    size_v <<- size
    size_e <<- size-1
    to_stop <- FALSE
    origin_size <<- size
    
    while(to_stop == FALSE) {
     
      E <<- matrix(FALSE,size,size)
      
      much_left <-size_e
     
     sA <- round(runif(1,1,size-1))
     sB <- size-sA
     
     max_deg_index <<- 1 
     max <- 0
     
     A_index <- 1
     B_index <-sA+1
     
     for(i in 1:size_v){
       V <<- c(V, Vertex(index=i, degree=0))
       
     }
     
     if(sA>=sB) {
      
       for(B_index in (sA+1):size) {
         
         if(A_index == B_index){ next }
         
         V[[A_index]]$addNeighbor(vert = B_index)
         V[[B_index]]$addNeighbor(vert = A_index)
         
         
         E[A_index, B_index] <<- TRUE
         E[B_index, A_index] <<- TRUE
         
         A_index <-A_index+1
         
         much_left = much_left-1
         
         if(max < V[[A_index]]$degree){
           max = V[[A_index]]$degree
           max_deg_index <<-A_index
         }
         
        }
       
       
       while(much_left != 0){
         
         if(A_index > sA){ A_index = 1 }
         
         rndB <- round(runif(1,sA,size))
         
         if(A_index == rndB){ next }
         
         if(E[A_index, rndB] == TRUE){
           A_index <-A_index+1
           next
          }
         
         V[[A_index]]$addNeighbor(vert = rndB)
         V[[rndB]]$addNeighbor(vert = A_index)
         
         E[A_index, rndB] <<- TRUE
         E[rndB, A_index] <<- TRUE
         
         
         if(max < V[[A_index]]$degree){
           max = V[[A_index]]$degree
           max_deg_index <<-A_index
         }
         
         if(max < V[[rndB]]$degree){
           max = V[[rndB]]$degree
           max_deg_index <<-rndB
         }
         
         A_index <-A_index+1
         much_left <- much_left-1
       }
       
    }
     
     
     
     else {
       
       for(A_index in 1:sA) {
         
         V[[A_index]]$addNeighbor(vert = B_index)
         V[[B_index]]$addNeighbor(vert = A_index)
         
         if(A_index == B_index){ next }
         
         E[A_index, B_index] <<- TRUE
         E[B_index, A_index] <<- TRUE
         
         B_index <-B_index+1
         
         much_left <- much_left-1
       }
       
       
       while(much_left != 0){
         
         if(B_index > size){ B_index <- sA+1 }
         
         rndA <- round(runif(1,1,sA))
         
         if(rndA == B_index){ next }
         
         if(E[B_index, rndA] == TRUE){
           B_index <-B_index+1
           next
          }
         
         V[[B_index]]$addNeighbor(vert = rndA)
         V[[rndA]]$addNeighbor(vert = B_index)
         
         E[B_index, rndA] <<- TRUE
         E[rndA, B_index] <<- TRUE
         
         if(max < V[[B_index]]$degree){
           max = V[[B_index]]$degree
           max_deg_index <<-B_index
         }
         
         if(max < V[[rndA]]$degree){
           max = V[[rndA]]$degree
           max_deg_index <<-rndA
         }
         
         B_index <-B_index+1
         
         much_left = much_left-1
       }
       
     }
     
     
      to_stop = BFS()
       if( to_stop == FALSE){
         V <<- c()
       }
    
     }
  
  },
  
  
  BFS = function(){
    number_of_nil <- size_v
    number_of_e <-0
    
    color <- rep(0, size_v)
    color[1] = 1
    
    myQ <- c(1)

    
    while(length(myQ)!=0){
      
      tmpo <- V[[color[ myQ[1] ]]]$neighbors
      
      for(ind in tmpo){
        if(color[ind] == 0){
          color[ind] = 1
          number_of_nil = number_of_nil-1
          number_of_e = number_of_e+1
          append(myQ,ind)
          
        }
        
        myQ <- myQ[(-1)]
      }
      
      
    }
    
    if (number_of_nil != 1 | number_of_e!= size_e) {
      returnValue(FALSE)
    }
    returnValue(TRUE)
  },
  
  subTreeforIndep = function(which_one = "numeric" ,x_or_nx = "numeric"){
    subt <- TreeGraph()
    max_d <-0
    
    if(x_or_nx == TRUE){
      
      subt$size_v <- size_v -1
      subt$origin_size <- origin_size
      subt$size_e <- size_e
      subt$V <- V[!V$index %in% which_one]
      subt$E <- E
      
      subt$E[which_one] <- rep(FALSE, origin_size)
      subt$E[,which_one] <- rep(FALSE, origin_size)
      
      for(v in subt$V){
        if(E[which_one, v$index] == TRUE){
          v$removeNeigh(which_one)
          subt$size_e <- subt$size_e -1
        }
        
        if( max_d < v$degree){
          subt$max_deg_index <- v$index
          max_d <- v$degree
        }
        
      }
      
      returnValue(subt)
    }
    
    else{
      
       tmpo_removes <- c(which_one, V[which_one]$neighbors)
      
        subt$size_v <- size_v -1 - V[which_one]$degree
        subt$origin_size <- origin_size
        subt$size_e <- size_e
        subt$V <- V[!V$index %in% tmpo_removes]
        subt$E <- E
      
        subt$E[,tmpo_removes] <- rep(FALSE, origin_size)
        subt$E[tmpo_removes] <- rep(FALSE, origin_size)
      
        for (ver in subt$V) {
          ver$neighbors <- setdiff(ver$neighbors, tmpo_removes)  
          ver$degree <- length(ver$neighbors)
        
          subt$size_e <- subt$size_e - intersect(ver$neighbors, tmpo_removes)
        
          if( max_d < ver$degree){
            subt$max_deg_index <- ver$index
            max_d <- ver$degree
          }
        
        
         }
      
        returnValue(subt)
      }
    
  
  },
  
  
  isKn = function(){
    if (size_e == size_v*(size_v-1/2)) { 
      returnValue(TRUE)
    }
    
    returnValue(FALSE)
  },
  
  print.tree = function(){
    print(paste("|V| =", size_v )) 
    print("{ ")
    for(i in 1:size_v){
      for( j in i:size_v){
        
        if(E[i,j] == TRUE)
        print(paste("( V",i,", V",j," ), ", sep = ""))
      }
      
      
    }
     print(" }")
  }
) 


