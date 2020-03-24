Vertex <- setRefClass("Vertex", fields = list(index = "numeric", degree = "numeric", neighbors = "vector"))

Vertex$methods(
  
  addNeighbor = function(vert = "numeric"){ 
    neighbors <<- c(neighbors, vert)
    degree <<- degree+1 
    
  },
  
  removeNeigh = function(vert = "numeric") {
    neighbors <<- neighbors[!neighbors %in% vert]
    degree <<- degree-1
    
  },
  
  removeFewNei = function(vec = "vector"){
    neighbors <<- setdiff(neighbors, vec)
    degree <<- length(neighbors)
  }
  
)