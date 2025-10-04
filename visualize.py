import numpy as np
import matplotlib.pyplot as plt

# Robot geometry
R = 0.1   # Distance from center to wheel (m)
r = 0.05  # Wheel radius (m)



#Create robot geometry
w1_angle = 0*(3.1415/180)
w2_angle = 120*(3.1415/180)
w3_angle = 240*(3.1415/180)


#From ps4
Vx = float(input("Velocity of chasis in x direction: "))
Vy = float(input("Velocity of chasis in y direction: "))
W = float(input("Angular velocity of Bot around centre of chasis: "))


# Jacobian 
J = np.array([
    [-np.sin(w1_angle), np.cos(w1_angle), R],
    [-np.sin(w2_angle), np.cos(w2_angle), R],
    [-np.sin(w3_angle), np.cos(w3_angle), R]
]) / r

v_chassis = np.array([Vx, Vy, W])
v_wheels = np.dot(J, v_chassis)


# Visualization

fig, ax = plt.subplots(figsize=(6, 6))
ax.set_aspect('equal')
ax.set_xlim(-0.15, 0.15)
ax.set_ylim(-0.15, 0.15)
ax.set_title("3-Wheel Omni Drive Visualization", fontsize=14)
ax.set_xlabel("X axis (m)")
ax.set_ylabel("Y axis (m)")

# Draw robot center
ax.plot(0, 0, 'ko', markersize=8)
ax.text(0.005, 0.005, 'Center', fontsize=9)

# Draw X and Y axes
ax.arrow(0, 0, 0.1, 0, head_width=0.01, color='r', label='X axis')
ax.arrow(0, 0, 0, 0.1, head_width=0.01, color='b', label='Y axis')

# Plot wheels
for i, angle in enumerate(angles):
    # Wheel position
    x = R * np.cos(angle)
    y = R * np.sin(angle)

    # Wheel direction (tangent)
    dx = -np.sin(angle)
    dy = np.cos(angle)

    # Scale arrow length for visualization
    arrow_scale = 0.05

    ax.plot(x, y, 'ko', markersize=8)
    ax.arrow(x, y, dx * arrow_scale, dy * arrow_scale, 
             head_width=0.01, color='g', length_includes_head=True)

    ax.text(x + 0.02 * dx, y + 0.02 * dy, f"W{i+1}", fontsize=9)

# Add wheel velocity labels
for i, v in enumerate(v_wheels):
    ax.text(-0.14, 0.12 - i * 0.04, f"Wheel {i+1} speed: {v:.2f} rad/s", fontsize=9)
for i, v in enumerate(v_wheels, start=1):
    print(f"Wheel {i}: {v:.3f}")
ax.legend()
plt.grid(True)
plt.show()
