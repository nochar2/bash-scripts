base = 1667
interest = 0.06
years = 40

print(base * sum((1.0 + (interest/12))**i for i in range(12*years)))
