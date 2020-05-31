
Library(polynom)

Indepen_Polynomial <- setRefClass("IndeP", fields = list(the_poly = "S3", the_t = "TreeGraph"))

Indepen_Polynomial$methods(
  
  init = function(Tr = "TreeGraph"){
    the_t <<- Tr
    the_poly <<- calc_tree_pol(Tr)
  },
  
  calc_tree_pol = function(Tt = "TreeGraph") {
    
    
    if(Tt$size_v == 0){
        returnValue(polynomial(coef = c(1)))
      
    }
    
    if(Tt$isKn()){
      returnValue(polynomial(coef = c(1,Tt$size_v)))
    }
    
    tmp <- calc_tree_pol(Tt$subTreeforIndep(Tt$max_deg_index, TRUE))
    
    tmp <- tmp + polynomial(coef = c(0,1))*calc_tree_pol(Tt$subTreeforIndep(Tt$max_deg_index, FALSE))
    
    print(tmp)
    returnValue(tmp)
  },
  
  plotpoly = function(xlimit = 1, ylimit = 1){
    if(!is.null(the_poly)){
      plot(x = the_poly, xlim = c(-xlimit,xlimit), ylim = c(-ylimit,ylimit), col = "blue") 
    }
    
  },
  
  findRoots = function(){
    if (is.null(the_poly)) {
      returnValue()
    }
    returnValue(polyroot(the_poly))
    
  }
)


