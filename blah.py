with open('beh.txt', 'r') as f:
    for line in f:
        print(line.strip(), end='')
        print(', ', end='')