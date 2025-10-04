import numpy as np

R = 0.1
r = 0.05

#Create robot geometry
w1_angle = 0*(3.1415/180)
w2_angle = 120*(3.1415/180)
w3_angle = 240*(3.1415/180)




#From ps4
Vx = float(input("Velocity of chasis in x direction: "))
Vy = float(input("Velocity of chasis in y direction: "))
W = float(input("Angular velocity of Bot around centre of chasis: "))


#Jacobian
J = np.array((
    [-np.sin(w1_angle), np.cos(w1_angle), R],
    [-np.sin(w2_angle), np.cos(w2_angle), R],
    [-np.sin(w3_angle), np.cos(w3_angle), R]
    ))/r

v_chasis = np.array([Vx, Vy, W])
v_wheels = np.dot(J, v_chasis)
print("Vx, Vy W = ", end = ' ')
print(v_wheels)
for i in v_wheels:
    print(v_wheels, end = ' ')
