D <- TreeGraph()
D$init(size=10)
D$print.tree()

p <- Indepen_Polynomial()
p$init(D)



pol <-  polynomial(coef = c(5,2,4))
polyroot(pol)
plot(pol, xlim = c(-40, 40), ylim = c(-40, 40), col = "blue", lwd = 5)
