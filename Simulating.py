import numpy as np

# --------------------------
# Robot parameters
# --------------------------
R = 0.1   # Distance from center to wheel (meters)
r = 0.05  # Wheel radius (meters)

# Wheel placement angles in radians
psi = np.deg2rad([90, -30, 210])

# --------------------------
# Jacobian matrix
# --------------------------
J = np.array([
    [-np.sin(psi[0]), np.cos(psi[0]), R],
    [-np.sin(psi[1]), np.cos(psi[1]), R],
    [-np.sin(psi[2]), np.cos(psi[2]), R]
]) / r

print("Jacobian Matrix:")
print(J)

# --------------------------
# Desired chassis velocities
# --------------------------
Vx = 0.2   # Forward velocity (m/s)
Vy = 0.2   # Sideways velocity (m/s)
omega = 0.0  # Rotation (rad/s)

v_chassis = np.array([[Vx], [Vy], [omega]])

# --------------------------
# Compute wheel speeds
# --------------------------
v_wheels = np.dot(J, v_chassis)

print("\nWheel Linear Velocities (m/s):")
print(v_wheels)

# Convert to wheel angular velocity (rad/s)
omega_wheels = v_wheels * (1/r)

print("\nWheel Angular Velocities (rad/s):")
print(omega_wheels)
