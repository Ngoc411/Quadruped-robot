import numpy as np
import matplotlib.pyplot as plt
import math

a = 62
b = 62
c = 70



X = []
x = -36
for i in range(11):
    x += 6
    X.append(x)

Y = []
for x in X:
    y = (-1/90)*x**2 + 10
    Y.append(y)
# print(Y)

alphaArr = []
alphaMainArr = []
alphaBaseArr = []
betaArr = []
betaBottomArr = []
palAlphaGaitTIM = []
palBetaGaitTIM = []

def cal_alpha_main(x, y):
    return math.degrees(math.acos((a*a + (c - y)**2 + x*x - b*b)/(2*a*math.sqrt((c - y)**2 + x*x))))

def cal_alpha_base(x, y):
    return math.degrees(math.atan(x/(c - y)))

def cal_beta(x, y):
    return math.degrees(math.acos((a*a + b*b - (c - y)**2 - x*x)/(2*a*b)))

def cal_point_beta(x, y, deg):
    x_beta = x + b*math.cos(math.radians(deg))
    y_beta = y + b*math.sin(math.radians(deg))
    return x_beta, y_beta

def cal_point_alpha(x, y, deg):
    x_alpha = x + a*math.cos(math.radians(deg))
    y_alpha = y + a*math.sin(math.radians(deg))
    XAlphaArr.append(x_alpha)
    YAlphaArr.append(y_alpha)

def convert_to_time(value):
    return (value / 90) + 0.5

def convert_to_TIM(value):
    return round((1000 * (value / 20)))

def check_continuity(arr):
    n = len(arr)
    if n < 2:
        return []  # Không có đủ phần tử để kiểm tra

    results = []
    start = 0

    for i in range(1, n):
        # Kiểm tra nếu đoạn hiện tại không còn liên tục tăng hoặc giảm
        if (arr[i] > arr[i - 1] and arr[start] > arr[start + 1]) or \
           (arr[i] < arr[i - 1] and arr[start] < arr[start + 1]):
            results.append((arr[start], arr[i - 1]))  # Lưu đoạn liên tục trước đó
            start = i - 1  # Bắt đầu đoạn mới

    # Thêm đoạn cuối cùng
    results.append((arr[start], arr[-1]))
    return results


for i in range(len(X)):
    alphaMain = cal_alpha_main(X[i], Y[i])
    alphaBase = cal_alpha_base(X[i], Y[i])
    beta = (cal_beta(X[i], Y[i])) # use for opposite motor: 180 - (cal_beta(X[i], Y[i]))
    alpha = (90 - (alphaMain - alphaBase)) # use for opposite motor: 180 - (90 - (alphaMain - alphaBase))
    betaBottom = 180 - abs(beta - alpha)
    alphaTIM = convert_to_TIM(convert_to_time(alpha))
    betaTIM = convert_to_TIM(convert_to_time(beta))

    alphaMainArr.append(alphaMain)
    alphaBaseArr.append(alphaBase)
    betaArr.append(beta)
    alphaArr.append(alpha)
    betaBottomArr.append(betaBottom)
    palAlphaGaitTIM.append(alphaTIM)
    palBetaGaitTIM.append(betaTIM)

# print(alphaMainArr)
# print()
# print(alphaBaseArr)
# print()
# print(alphaArr)
# print()
# print(betaArr)
# print()
# print(betaBottomArr)
print(f"int palAlphaGaitTIM[] = {palAlphaGaitTIM}")
print()
print(f"int palBetaGaitTIM[] = {palBetaGaitTIM}")
print()

# Kiểm tra tính liên tục
alpha_continuity = check_continuity(palAlphaGaitTIM)
beta_continuity = check_continuity(palBetaGaitTIM)

# In kết quả
print("Liên tục của palAlphaGaitTIM:")
for segment in alpha_continuity:
    print(f"Từ {segment[0]} đến {segment[1]}")

print("\nLiên tục của palBetaGaitTIM:")
for segment in beta_continuity:
    print(f"Từ {segment[0]} đến {segment[1]}")

XAlphaArr = []
YAlphaArr = []

XBetaArr = []
YBetaArr = []

for i in range(len(X)): 
    x_beta, y_beta = cal_point_beta(X[i], Y[i], betaBottomArr[i])
    cal_point_alpha(x_beta, y_beta, alphaArr[i])
    XBetaArr.append(x_beta)
    YBetaArr.append(y_beta)

# print(XAlphaArr) 
# print()
# print(YAlphaArr)
# print()
# print(XBetaArr) 
# print()
# print(YBetaArr)


# colors = np.linspace(0, 1, len(X))  # Linearly spaced values for the colormap

# # Create a scatter plot with the colormap
# plt.scatter(XBetaArr, YBetaArr, c=colors, cmap='viridis')  # `c` specifies color, `cmap` specifies the colormap

# # Label the axes
# plt.xlabel("X values")
# plt.ylabel("Y values")

# # Add a title
# plt.title("Scatter Plot with Unique Colors")

# plt.axis("equal")

# # Show colorbar
# plt.colorbar(label='Index Value')

# # Show grid
# plt.grid(True)

# # Show the plot
# plt.show()



plt.figure(figsize=(15, 8))

colors = plt.colormaps["tab10"]

# Plotting connections
for i in range(len(X)):
    color = colors(i / len(X))

    # Connect (X[i], Y[i]) to (XAlphaArr[i], YAlphaArr[i])
    plt.plot([X[i], XBetaArr[i]], [Y[i], YBetaArr[i]], color=color, marker='o')
    
    # Connect (XAlphaArr[i], YAlphaArr[i]) to (XBetaArr[i], YBetaArr[i])
    plt.plot([XAlphaArr[i], XBetaArr[i]], [YAlphaArr[i], YBetaArr[i]], color=color, marker='x')

# Label the axes
plt.xlabel("X axis")
plt.ylabel("Y axis")
plt.title("Connecting Points X, Xalpha, Xbeta")

plt.axis("equal")

# Display the plot
plt.grid(True)
plt.show()




# A = []
# a = 30

# for i in range(10):
#     a += 3
#     A.append(a)

# print(A)