import numpy as np
import matplotlib.pyplot as plt
import math
from math import sqrt

center = (25, 85) #(-25, 85) for the opposite leg
radius = math.sqrt(25**2 + 15**2)

x1 = [-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10] # for full stra
x2 = [-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0] # for half inside
x3 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10] # for half outside

x_third = x3
y_third = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]


def generate_optimal_point(center, radius, x_c, y_c, x_range=(-30, 30), y_range=(50, 90), step=0.001, target_angle=121):
    best_point = None
    min_diff = float('inf')
    best_angle = None
    
    for angle in np.arange(0, 2 * np.pi, step):
        x = center[0] + radius * np.cos(angle)
        y = center[1] + radius * np.sin(angle)
        
        if x_range[0] <= x <= x_range[1] and y_range[0] <= y <= y_range[1]:
            b = (x, y)
            ba = (center[0] - b[0], center[1] - b[1])
            bc = (x_c - b[0], y_c - b[1])
            
            angle = vector_angle(ba, bc)
            if angle is not None:
                diff = abs(angle - target_angle)
                if diff < min_diff:
                    min_diff = diff
                    best_point = (round(b[0]), round(b[1]))
                    best_angle = angle
    
    return best_point, best_angle

def vector_angle(v1, v2):
    dot_product = np.dot(v1, v2)
    mag_v1 = np.linalg.norm(v1)
    mag_v2 = np.linalg.norm(v2)
    if mag_v1 == 0 or mag_v2 == 0:
        return None
    cos_theta = np.clip(dot_product / (mag_v1 * mag_v2), -1.0, 1.0)
    return np.degrees(np.arccos(cos_theta))

def distance(x1, y1, x2, y2):
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

def convert_to_time(value):
    return (value / 90) + 0.5

def convert_to_TIM(value):
    return round((1000 * (value / 20)))

fig, ax = plt.subplots(figsize=(8, 8))  # Set a reasonable figure size

circle = plt.Circle(center, radius, color='blue', fill=False, label='Circle')
ax.add_patch(circle)

ax.scatter(center[0], center[1], color='red', label='Center')

ax.scatter(x_third, y_third, color='green', label='Third Points')

C = []
shoulderAngle = []
shoulderAngleTIM = []

vertical = ((-25 + 25), (0 -85))
horizontal = ((25), (85 - 85))

for i in range(len(x_third)):
    x3 = x_third[i]
    y3 = y_third[i]
    
    best_point, best_angle = generate_optimal_point(center, radius, x3, y3)
    ab = ((best_point[0] + 25), (best_point[1] - 85))

    # dot_product = np.dot(vertical, ab)
    # vertical_length = np.linalg.norm(vertical)

    dot_product = np.dot(horizontal, ab) # use for opposite motor
    vertical_length = np.linalg.norm(horizontal)

    ab_length = np.linalg.norm(ab)

    cos_shoulder_angle = np.clip(dot_product / (vertical_length * ab_length), -1.0, 1.0)
    # shoulder_angle = round(np.degrees(np.arccos(cos_shoulder_angle))) + 31
    shoulder_angle = round(np.degrees(np.arccos(cos_shoulder_angle))) + 59 # use for opposite motor
    shoulder_angle_TIM = convert_to_TIM(convert_to_time(shoulder_angle))

    shoulderAngle.append(shoulder_angle) 
    shoulderAngleTIM.append(shoulder_angle_TIM)


    # print(f"Tọa đô tối ưu nhất: {best_point}")
    # print(f"Góc gần 121 độ nhất: {best_angle:.2f} độ")
    # print()
    c_length = sqrt((best_point[0] - x3) ** 2 + (best_point[1] - y3) ** 2)
    C.append(round(c_length))

    ax.plot([center[0], best_point[0]], [center[1], best_point[1]], color='orange', linestyle='-', label='Edge 1' if i == 0 else "")
    ax.plot([best_point[0], x3], [best_point[1], y3], color='purple', linestyle='--', label='Edge 2' if i == 0 else "")

print(f"c_length = {C}")
print(f"int fullStraShoulderTIM2[] = {{{', '.join(map(str, shoulderAngleTIM))}}};")

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_title('Circle and Movement Process')
ax.set_aspect('equal')  # Ensure equal aspect ratio
ax.legend()
ax.grid(True)

# Show plot
plt.show()

